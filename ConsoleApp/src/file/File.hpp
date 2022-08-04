#ifndef FILE_HPP
#define FILE_HPP

#include <string>
#include <vector>
#include <fstream>
#include <utility>
#include "../compressor/file/ArchiveHeader.hpp"
#include "../wordCode/WordCode.hpp"

using std::fstream;
using std::pair;
using std::string;
using std::vector;

class File
{
private:
    string path;
    fstream readStream;

public:
    File(const string &path);
    ~File();

    size_t getSize() const;
    const char *getLastModifiedTime() const;
    char readByte();
    char *readBytes(const int bytesCount, int &bytesRead);
    pair<ArchiveHeader, vector<WordCode> *> readArchive();
    void appendBytes(const char *bytes, const int bytesCount);
    void writeBytes(const char *bytes, const int bytesCount);
    void clear();
    void appendCodes(const vector<WordCode> &codes);
    //   void writeCodes(const vector<WordCode> &codes);
    pair<size_t, ArchiveHeader> readHeader();
    void writeHeader(const ArchiveHeader &archiveHeader);
    void setReadingPosition(size_t position);

private:
    size_t createOnesMask(int numberOfMostSignificantOnes, int totalBits);
    size_t createZeroesMask(int numberOfMostSignificantZeroes, int totalBits);
    size_t bitsCount(int number);
    void close();
};

#endif