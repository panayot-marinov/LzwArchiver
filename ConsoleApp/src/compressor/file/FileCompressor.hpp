#pragma once
#ifndef FILE_COMPRESSOR_HEADER_HPP
#define FILE_COMPRESSOR_HEADER_HPP

#include "../../file/File.hpp"
#include "../../file/hasher/FileHasher.hpp"

class FileCompressor
{
private:
    FileHasher fileHasher;

public:
    uint64_t archive(const char *inputPath, const char *inputArchivePath, File &outputFile, bool isRegularFile);
    void unarchive(File &inputFile, const char *outputPath);
    bool isArchivedFileCorrupted(File& inputFile);

private:
    void createDirectoryIfDoesNotExist(const string &path);
};

#endif