#include "file/File.hpp"
#include "wordCode/WordCode.hpp"
#include "command/parser/CommandParser.hpp"
#include "compressor/byte/ByteCompressor.hpp"
#include "compressor/directory/DirectoryCompressor.hpp"
#include "compressor/file/FileCompressor.hpp"
#include "command/executor/CommandExecutor.hpp"
#include <iostream>
#include <vector>

#include <filesystem>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

const string path = "";

int main()
{
    CommandExecutor commandExecutor;
    CommandParser commandParser;

    do
    {
        commandParser.parseCommand(std::cin);
        commandExecutor.executeCommand(commandParser.getCommandType(), commandParser.getCopyOfArguments());
    }
    while(!commandExecutor.isExitCommand());

    //     DirectoryCompressor directoryCompressor;

    //     vector<const char *> inputPaths{"../InputFiles/fold1", "../InputFiles/fold2"};
    //     directoryCompressor.archive(inputPaths, "../OutputFiles/Archived", "archive", "lzw");
    //     vector<const char *> inputPaths2{"../InputFiles/fold3"};
    //     vector<const char *> inputPaths3{"../InputFiles/fold2"};

    //     directoryCompressor.addFilesToArchive(inputPaths2, "../OutputFiles/Archived/archive.lzw");
    //    // directoryCompressor.addFilesToArchive(inputPaths2, "../OutputFiles/Archived/archive.lzw");

    //     directoryCompressor.removeFilesFromArchive(inputPaths3, "../OutputFiles/Archived/archive.lzw");
    //     directoryCompressor.unarchive("../OutputFiles/Archived/archive.lzw", "../OutputFiles/Unarchived");

    //-----------------------

    // vector<const char *> inputPaths4{"../InputFiles/fold2/a.txt"};
    // directoryCompressor.archive(inputPaths4, "../OutputFiles/Archived", "archive2", "lzw");
    // vector<const char *> inputPaths5{"../InputFiles/fold1/b.txt"};
    // directoryCompressor.addFilesToArchive(inputPaths5, "../OutputFiles/Archived/archive2.lzw");
    // directoryCompressor.removeFilesFromArchive(inputPaths4, "../OutputFiles/Archived/archive2.lzw");
    // directoryCompressor.unarchive("../OutputFiles/Archived/archive2.lzw", "../OutputFiles/Unarchived");

    // directoryCompressor.printArchiveInfo("../OutputFiles/Archived/archive.lzw");

    // CommandParser commandParser;
    // commandParser.parseCommand(std::cin);
    // std::cout<<commandParser.getCommandType()<<" ";
    // std::cout<<commandParser.getNumberOfArguments()<<" ";
    // std::cout<<commandParser.getArgument(0)<<" \n";

    // directoryCompressor.unarchiveFile("../OutputFiles/Archived/archive.lzw", "../OutputFiles/Unarchived", "/fold1\\a.txt");
    // directoryCompressor.unarchiveFile("../OutputFiles/Archived/archive.lzw", "../OutputFiles/Unarchived", "/fold1\\b.txt");
    // directoryCompressor.unarchiveFile("../OutputFiles/Archived/archive.lzw", "../OutputFiles/Unarchived", "/fold1\\c.txt");

    // directoryCompressor.unarchiveFile("../OutputFiles/Archived/archive.lzw", "../OutputFiles/Unarchived", "/fold1\\fold\\d.txt");
    // directoryCompressor.unarchiveFile("../OutputFiles/Archived/archive.lzw", "../OutputFiles/Unarchived", "/fold1\\fold\\e.txt");
    // directoryCompressor.unarchiveFile("../OutputFiles/Archived/archive.lzw", "../OutputFiles/Unarchived", "/fold1\\fold\\foldInt\\f.txt");
    // directoryCompressor.unarchiveFile("../OutputFiles/Archived/archive.lzw", "../OutputFiles/Unarchived", "/fold1\\foldd");
}