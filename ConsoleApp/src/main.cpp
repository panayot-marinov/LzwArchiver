#include "file/File.hpp"
#include "wordCode/WordCode.hpp"
#include "command/parser/CommandParser.hpp"
#include "compressor/byte/ByteCompressor.hpp"
#include "compressor/directory/DirectoryCompressor.hpp"
#include "compressor/file/FileCompressor.hpp"
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
    FileCompressor fileCompressor;
    // fileCompressor.archive("../InputFiles/a.txt", "../OutputFiles/e.txt");

    // fileCompressor.unarchive("../OutputFiles/Archived/a.lzw", "../OutputFiles/Unarchived/a.txt");

    DirectoryCompressor directoryCompressor;

    vector<const char *> inputPaths{"../InputFiles/fold1", "../InputFiles/fold2"};
    directoryCompressor.archive(inputPaths, "../OutputFiles/Archived", "archive", "lzw");
    directoryCompressor.unarchive("../OutputFiles/Archived/archive.lzw", "../OutputFiles/Unarchived");
    //directoryCompressor.printArchiveInfo("../OutputFiles/Archived/archive.lzw");

    // CommandParser commandParser;
    // commandParser.parseCommand(std::cin);
    // std::cout<<commandParser.getCommandType()<<" ";
    // std::cout<<commandParser.getNumberOfArguments()<<" ";
    // std::cout<<commandParser.getArgument(0)<<" \n";

    // directoryCompressor.unarchiveFile("../OutputFiles/Archived/archive.lzw", "../OutputFiles/Unarchived", "\\a.txt");
    // directoryCompressor.unarchiveFile("../OutputFiles/Archived/archive.lzw", "../OutputFiles/Unarchived", "\\b.txt");
    // directoryCompressor.unarchiveFile("../OutputFiles/Archived/archive.lzw", "../OutputFiles/Unarchived", "\\c.txt");

    // directoryCompressor.unarchiveFile("../OutputFiles/Archived/archive.lzw", "../OutputFiles/Unarchived", "\\fold\\d.txt");
    // directoryCompressor.unarchiveFile("../OutputFiles/Archived/archive.lzw", "../OutputFiles/Unarchived", "\\fold\\e.txt");
    // directoryCompressor.unarchiveFile("../OutputFiles/Archived/archive.lzw", "../OutputFiles/Unarchived", "\\fold\\foldInt\\f.txt");
    // directoryCompressor.unarchiveFile("../OutputFiles/Archived/archive.lzw", "../OutputFiles/Unarchived", "\\foldd");
}