#include "file/File.hpp"
#include "wordCode/WordCode.hpp"
#include "compressor/byte/ByteCompressor.hpp"
#include "compressor/file/FileCompressor.hpp"
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

const string path = "";

int main()
{
    FileCompressor fileCompressor;
    fileCompressor.archive("../InputFiles/a.txt", "../OutputFiles/e.txt");

    fileCompressor.unarchive("../InputFiles/e.txt", "../OutputFiles/f.txt");
}