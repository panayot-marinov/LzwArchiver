#pragma once
#ifndef COMMANDPARSER_HPP
#define COMMANDPARSER_HPP

#include<iostream>
#include <string>
#include <cstddef>
#include <vector>

using std::string;
using std::vector;

class CommandParser {
    string commandType;
    vector<string> arguments;

    public:
        void parseCommand(std::istream& in);
        const char* getCommandType() const;
        const char* getArgument(const size_t at) const;
        vector<string> getCopyOfArguments() const;
        size_t getNumberOfArguments() const;
    private:
        void readCommand(std::istream& in, char* s) const;
        void splitCommand(const char* command);
        size_t extractCommandType(const char* command, const size_t length);
        void extractArguments(const char* command, size_t endOfCommandType, size_t length);
        size_t findNextDelimeterInd(
            const char* command, size_t startIndex, bool isQuoted = false) const;
        bool checkArgumentsLengths(size_t argumentsMaxLengths[]);
        size_t maxArgumentLength(size_t argumentLengths[], size_t arrLength) const;
};

#endif /*COMMANDPARSER_H */