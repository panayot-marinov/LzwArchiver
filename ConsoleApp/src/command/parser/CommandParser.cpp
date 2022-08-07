#include "CommandParser.hpp"
#include "../utils/ArrayUtils.hpp"
#include "../utils/CharArrUtils.hpp"
#include "../utils/Constants.hpp"
#include <iostream>
#include <cstring>
#include <cstddef>

const char* CommandParser::getCommandType() const {
    return commandType.c_str();
}

const char* CommandParser::getArgument(const size_t at) const {
    if(at >= getNumberOfArguments() || at < 0)
        throw std::out_of_range("index out of range");
    
    return arguments[at].c_str();
}

vector<string> CommandParser::getCopyOfArguments() const {
    return arguments;
}

void CommandParser::parseCommand(std::istream& in) {
    commandType = "unknown";
    arguments.clear();
    char* commandArr = ArrayUtils<char>::assignArray(MAX_ROW_LENGTH);
    readCommand(in, commandArr);
    splitCommand(commandArr);

    bool commandRecognized = false, numberOfArgumentsCorrect = true;
    size_t* argumentsMaxLengths = 
        ArrayUtils<size_t>::assignArray(getNumberOfArguments());
    if(commandType == "zip") {
        //argumentsMaxLengths[0] = MAX_REGISTRATION_LENGTH;
        //argumentsMaxLengths[1] = MAX_DESCRIPTION_LENGTH;

        commandRecognized = true;
        numberOfArgumentsCorrect = 
            (getNumberOfArguments() > 0);
    }
    else if(commandType == "unzip") {
        //argumentsMaxLengths[0] = MAX_PERSON_NAME_LENGTH;
        //argumentsMaxLengths[1] = MAX_ID_LENGTH;

        commandRecognized = true;
        numberOfArgumentsCorrect = 
            (getNumberOfArguments() > 0);
    }
    else if(commandType =="info") {
        //argumentsMaxLengths[0] = MAX_ID_LENGTH;
        //argumentsMaxLengths[1] = MAX_REGISTRATION_LENGTH;

        commandRecognized = true;
        numberOfArgumentsCorrect = 
            (getNumberOfArguments() == 1);
    }
    else if(commandType == "refresh") {
        //argumentsMaxLengths[0] = MAX_ID_LENGTH;
        //argumentsMaxLengths[1] = MAX_REGISTRATION_LENGTH;

        commandRecognized = true;
        numberOfArgumentsCorrect = 
            (getNumberOfArguments() == 2); //TODO: ??
    }
    else if(commandType == "ec") {
        //argumentsMaxLengths[0] = MAX_REGISTRATION_LENGTH;

        commandRecognized = true;
        numberOfArgumentsCorrect = 
            (getNumberOfArguments() == 1);
    }
    else if(commandType == "exit") {
        commandRecognized = true;
        numberOfArgumentsCorrect = 
         (getNumberOfArguments() == 0);
    }
     bool correctArgumentLengths = true; //TODO: think about argument lengths
        //checkArgumentsLengths(argumentsMaxLengths);

    bool validCommand = 
        commandRecognized && 
        correctArgumentLengths && 
        numberOfArgumentsCorrect;

    if(!validCommand) {
        throw std::invalid_argument("Invalid command!");
    }
        
}

void CommandParser::readCommand(std::istream& in, char* commandArr) const {
    in.getline(commandArr, MAX_ROW_LENGTH+1);
    std::cout<<"COMMAND: "<<commandArr<<"\n"<<std::endl;
    if(in.eof()) {
        throw std::out_of_range("end of file");
    } 
    else if(in.fail()) {
        in.clear();
        throw std::invalid_argument("Invalid command!");
    }
}

void CommandParser::splitCommand(const char* command) {
    size_t length = strlen(command);

    size_t endOfCommandType = extractCommandType(command, length);
    extractArguments(command, endOfCommandType, length);
}

size_t CommandParser::extractCommandType(const char* command, const size_t length) {
    size_t startPos = 0;
    size_t endPos = findNextDelimeterInd(command, startPos);
    if(endPos == MAX_ROW_LENGTH)
        endPos = length;

    try{
        char* commandTypeArr = CharArrUtils::subArr(command, startPos, endPos);
        CharArrUtils::toLowerCharArr(commandTypeArr);

        commandType = commandTypeArr;
        delete[] commandTypeArr;
    }
    catch(std::bad_alloc e) {
        std::cerr<<"Command type is not extracted successfully."<<std::endl;
    }
    catch(std::exception e) {
        std::cerr<<e.what()<<std::endl;
    }
    return endPos;
}

void CommandParser::extractArguments(const char* command, size_t endOfCommandType, size_t length) {
    size_t startPos = endOfCommandType+1;
    size_t endPos = startPos;
    bool isQuoted = false;

    while(startPos < length) {
        if(command[startPos] == '"') {
            isQuoted = true;
            startPos++;
        }
        
        endPos = findNextDelimeterInd(command, startPos, isQuoted);

        if(endPos == MAX_ROW_LENGTH) 
            endPos = length;
            
        const char* argumentArr = CharArrUtils::subArr(command, startPos, endPos);
        arguments.push_back(argumentArr);

        startPos = (!isQuoted) ? (endPos+1) : (endPos+2);
        isQuoted = false;
    }
    
}

size_t CommandParser::getNumberOfArguments() const {
    return arguments.size();
}

size_t CommandParser::findNextDelimeterInd(
    const char* command, size_t startInd, bool isQuoted) const {
    //In case there are no delimeters
    size_t index = MAX_ROW_LENGTH; 
    size_t i = startInd;
    char delimeter =
        (isQuoted) ? '"' : COMMAND_DELIMETER;
    
    while(command[i] != '\0'){
        if(command[i] == delimeter) {
            index = i;
            break;
        }
        i++;
    }
    return index;
}

bool CommandParser::checkArgumentsLengths(size_t* argumentsMaxLengths) {
    bool valid = true;

    for (size_t i = 0; i < getNumberOfArguments(); i++) {
        if(arguments[i].length() > argumentsMaxLengths[i]) {
            valid = false;
            break;
        }
    }
    
    return valid;
}

 size_t CommandParser::maxArgumentLength(
     size_t argumentLengths[], size_t arrLength) const {
     size_t maxLength = 0;
     for (size_t i = 0; i < arrLength; i++) {
         if(argumentLengths[i] > maxLength)
            maxLength = argumentLengths[i];
     } 
    return maxLength;
 }
