#pragma once
#ifndef DIRECTORY_COMPRESSOR_HEADER_HPP
#define DIRECTORY_COMPRESSOR_HEADER_HPP

class DirectoryCompressor
{
public:
    void archive(const char *inputPath, const char *outputPath,
                 const char *outputFilename, const char *outputFileExtension);
    void unarchive(const char *inputPath, const char *outputPath);
    void unarchiveFile(const char *inputPath, const char *outputPath, const char* filename);
};

#endif