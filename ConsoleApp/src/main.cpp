#include "file/File.hpp"
#include "wordCode/WordCode.hpp"
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

    vector<const char *> inputPaths {"../InputFiles/fold1", "../InputFiles/fold2"};
    directoryCompressor.archive(inputPaths, "../OutputFiles/Archived", "archive", "lzw");
    directoryCompressor.unarchive("../OutputFiles/Archived/archive.lzw", "../OutputFiles/Unarchived");
    // directoryCompressor.unarchiveFile("../OutputFiles/Archived/archive.lzw", "../OutputFiles/Unarchived", "\\a.txt");
    // directoryCompressor.unarchiveFile("../OutputFiles/Archived/archive.lzw", "../OutputFiles/Unarchived", "\\b.txt");
    // directoryCompressor.unarchiveFile("../OutputFiles/Archived/archive.lzw", "../OutputFiles/Unarchived", "\\c.txt");

    // directoryCompressor.unarchiveFile("../OutputFiles/Archived/archive.lzw", "../OutputFiles/Unarchived", "\\fold\\d.txt");
    // directoryCompressor.unarchiveFile("../OutputFiles/Archived/archive.lzw", "../OutputFiles/Unarchived", "\\fold\\e.txt");
    // directoryCompressor.unarchiveFile("../OutputFiles/Archived/archive.lzw", "../OutputFiles/Unarchived", "\\fold\\foldInt\\f.txt");
    // directoryCompressor.unarchiveFile("../OutputFiles/Archived/archive.lzw", "../OutputFiles/Unarchived", "\\foldd");

    // fstream writeStream;
    // writeStream.open("../OutputFiles/b.txt", std::ios::out);
    // writeStream.write("abc",4);

    // const std::filesystem::path sandbox{"../InputFiles"};

    // std::cout << "directory_iterator:\n";
    // // directory_iterator can be iterated using a range-for loop
    // for (auto const &dir_entry : std::filesystem::directory_iterator{sandbox})
    // {
    //     std::cout << dir_entry.path() << '\n';
    // }
}