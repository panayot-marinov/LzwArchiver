#pragma once
#ifndef COMMANDEXECUTOR_HPP
#define COMMANDEXECUTOR_HPP

#include "../../compressor/directory/DirectoryCompressor.hpp"
#include <iostream>
#include <string>

using std::string;

class CommandExecutor {
    DirectoryCompressor directoryCompressor;
    bool exitCommand;

    
public:
    CommandExecutor();
    void executeCommand(const string& commandType,
        const vector<string>& arguments);
    bool isExitCommand();

private:
    void printHelp();
    bool fileExists(const string& path);
    void readAnswer(std::istream& in, string& answer, const char* message) const;
};

#endif /*COMMANDEXECUTOR_H*/