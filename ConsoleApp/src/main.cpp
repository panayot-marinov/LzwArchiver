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

    //fileCompressor.unarchive("../OutputFiles/Archived/a.lzw", "../OutputFiles/Unarchived/a.txt");

    DirectoryCompressor directoryCompressor;
    directoryCompressor.archive("../InputFiles/fold2", "../OutputFiles/Archived", "archive", "lzw");
    directoryCompressor.unarchive("../OutputFiles/Archived/archive.lzw", "../OutputFiles/Unarchived");

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