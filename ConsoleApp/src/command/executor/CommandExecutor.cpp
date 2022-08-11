#include "CommandExecutor.hpp"
#include "../utils/ArrayUtils.hpp"
#include "../utils/CharArrUtils.hpp"
#include <fstream>
#include <cstring>
#include <stdexcept>

CommandExecutor::CommandExecutor()
{
    exitCommand = false;
}

void CommandExecutor::executeCommand(
    const string &commandType,
    const vector<string> &arguments)
{
    if (exitCommand)
    {
        throw std::logic_error("Cannot execute a command after 'exit'");
    }
    if (commandType == "zip")
    {
        vector<const char *> inputPaths;
        for (size_t i = 3; i < arguments.size(); i++)
        {
            inputPaths.push_back(arguments[i].c_str());
        }

        directoryCompressor.archive(inputPaths, arguments[0].c_str(), arguments[1].c_str(), arguments[2].c_str());
    }
    else if (commandType == "unzip")
    {
        directoryCompressor.unarchive(arguments[0].c_str(), arguments[1].c_str());
    }
    else if (commandType == "add")
    {
        vector<const char *> inputPaths;
        for (size_t i = 1; i < arguments.size(); i++)
        {
            inputPaths.push_back(arguments[i].c_str());
        }

        try
        {
            directoryCompressor.addFilesToArchive(inputPaths, arguments[0].c_str());
        }
        catch (std::logic_error e)
        {
            std::cout << e.what() << std::endl;
        }
    }
    else if (commandType == "remove")
    {
        vector<const char *> inputPaths;
        for (size_t i = 1; i < arguments.size(); i++)
        {
            inputPaths.push_back(arguments[i].c_str());
        }

        try
        {
            directoryCompressor.removeFilesFromArchive(inputPaths, arguments[0].c_str());
        }
        catch (std::logic_error e)
        {
            std::cout << e.what() << std::endl;
        }
    }
    else if (commandType == "refresh")
    {
        try
        {
            vector<const char *> inputPaths{arguments[1].c_str()};
            directoryCompressor.removeFilesFromArchive(inputPaths, arguments[0].c_str());
            directoryCompressor.addFilesToArchive(inputPaths, arguments[0].c_str());
        }
        catch (std::invalid_argument e)
        {
            std::cerr << e.what() << std::endl;
        }
    }
    else if (commandType == "info")
    {
        directoryCompressor.printArchiveInfo(arguments[0].c_str());
    }
    else if (commandType == "ec")
    {
        
    }
    else if (commandType == "help")
    {
        printHelp();
    }
    else if (commandType == "exit")
    {
        exitCommand = true;
    }
}

bool CommandExecutor::fileExists(const string &path)
{
    std::ifstream file(path);
    return file.is_open();
}

bool CommandExecutor::isExitCommand()
{
    return exitCommand;
}

void CommandExecutor::readAnswer(std::istream &in, string &answer, const char *userMessage) const
{
    while (answer != "Y" && answer != "N")
    {
        std::cout << userMessage << std::endl;
        in >> answer;
    }
    in.get();
}

void CommandExecutor::printHelp()
{
    std::cout << "ZIP <output_path> <output_filename> <output_file_extension> <input_path1> <input_path2> ...\n";
    std::cout << "UNZIP <archive_path> <output_path>\n";
    std::cout << "ADD <archive_path> <input_path1> <input_path2> ...\n";
    std::cout << "REMOVE <archive_path> <input_path1> <input_path2> ...\n";
    std::cout << "REFRESH <archive_path> <input_path> \n";
    std::cout << "ADD <archive_path> <input_path1> <input_path2> ...\n";
    std::cout << "INFO <archive_path>\n";
    std::cout << "EC <archive_path> (to be implemented)\n";
    std::cout << "EXIT";
    std::cout<<std::endl;
}