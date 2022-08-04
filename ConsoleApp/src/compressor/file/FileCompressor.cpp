#include "../byte/ByteCompressor.hpp"
#include "FileCompressor.hpp"
#include "ArchiveHeader.hpp"
#include "../../file/File.hpp"
#include <iostream>
#include <cmath>
#include <cstring>
#include <utility>
#include <vector>

using std::pair;

void FileCompressor::archive(const char *inputPath, const char *outputPath)
{
    File inputFile(inputPath);

    // header
    ArchiveHeader archiveHeader;
    strcpy(archiveHeader.name, inputPath);
    // std::sprintf(archiveHeader.size, "%d", inputFile.getSize());
    strcpy(archiveHeader.mtime, inputFile.getLastModifiedTime());
    strcpy(archiveHeader.type, "1");
    archiveHeader.calculateChecksum();

    // data
    int bytesRead = 0;
    char *bytes = inputFile.readBytes(100, bytesRead);

    vector<WordCode> *result;
    try
    {
        result = new vector<WordCode>;
    }
    catch (std::bad_alloc e)
    {
        throw std::runtime_error("Memory for compressed data cannot be initialized.");
    }

    while (bytesRead > 0)
    {
        ByteCompressor byteCompressor;
        byteCompressor.compressBytes(bytes, bytesRead, result);
        archiveHeader.size = std::ceil((result->size() * 11.0) / 8.0);

        bytes = inputFile.readBytes(100, bytesRead);
    }

    File outputFile(outputPath);
    std::cout << archiveHeader.chksum << " " << archiveHeader.name << " " << archiveHeader.size << " " << archiveHeader.mtime << " " << archiveHeader.type << '\n';
    outputFile.writeHeader(archiveHeader);
   // std::cout << outputFile.getSize() << std::endl;
    outputFile.appendCodes(*result);
   // std::cout << outputFile.getSize() << std::endl;

    // std::cout << "Archived wordcodes:\n";
    // for (WordCode code : *result)
    // {
    //     std::cout << code.value.to_ulong() << " ";
    // }
    // std::cout << std::endl;

    delete result;
}

void FileCompressor::unarchive(const char *inputPath, const char *outputPath)
{
    File inputFile("../OutputFiles/e.txt");
    pair<ArchiveHeader, vector<WordCode> *> archivePair = inputFile.readArchive();
    // std::cout << "UnArchived wordcodes:\n";
    // for (WordCode code : *archivePair.second)
    // {
    //     std::cout << code.value.to_ulong() << " ";
    // }
    // std::cout << std::endl;
    // std::cout << "----------------------------" << std::endl;

    File outputFile("../OutputFiles/f.txt");

    // std::cout << archivePair.first.chksum << " " << archivePair.first.name << " " << archivePair.first.size << " " << archivePair.first.mtime << " " << archivePair.first.type << "\n";
    // std::cout << archivePair.first.type;
    // std::cout << "\n";

    //outputFile.writeHeader(archivePair.first);
    //std::cout << outputFile.getSize() << std::endl;
    ByteCompressor byteCompressor;
    byteCompressor.decompressAndWriteBytes(*archivePair.second, outputFile);

    // outputFile.appendCodes(*archivePair.second);
    // std::cout << outputFile.getSize() << std::endl;
}