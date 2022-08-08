#pragma once
#ifndef DIRECTORY_COMPRESSOR_HEADER_HPP
#define DIRECTORY_COMPRESSOR_HEADER_HPP

#include <vector>

using std::vector;

class DirectoryCompressor
{
public:
    void archive(vector<const char *> inputPaths, const char *outputPath,
                 const char *outputFilename, const char *outputFileExtension);
    void addFilesToArchive(vector<const char *> inputPaths, const char *archivePath);
    void unarchive(const char *inputPath, const char *outputPath);
    void printArchiveInfo(const char *inputPath) const;
    void unarchiveFile(const char *inputPath, const char *outputPath, const char *filename);
};

#endif