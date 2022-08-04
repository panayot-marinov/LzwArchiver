#pragma once
#ifndef FILE_COMPRESSOR_HEADER_HPP
#define FILE_COMPRESSOR_HEADER_HPP

class FileCompressor
{
public:
    void archive(const char* inputPath, const char* outputPath);
    void unarchive(const char* inputPath, const char* outputPath);
};

const static char REGTYPE = '0';
const static char LNKTYPE = '1';
const static char DIRTYPE = '2';

#endif