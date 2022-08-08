#ifndef FILE_HPP
#define FILE_HPP

#include <string>
#include <vector>
#include <fstream>
#include <utility>
#include <map>
#include <unordered_map>
#include "../compressor/file/ArchiveHeader.hpp"
#include "../wordCode/WordCode.hpp"

using std::fstream;
using std::map;
using std::pair;
using std::string;
using std::unordered_map;
using std::vector;

class File
{
private:
    const size_t APPEND_FILE_TRANSFER_BYTES = 100;
    const unsigned int BYTES_TO_SHIFT_STEP = 100;

    string path;
    fstream readStream;
    // fstream writeStream;

public:
    File(const string &path);
    ~File();

    uint64_t getSize() const;
    const char *getLastModifiedTime() const;
    char readByte();
    char *readBytes(const int bytesCount, int &bytesRead);
    pair<ArchiveHeader, vector<WordCode> *> readArchive();
    void readTableOfContents(vector<string> &result);
    void readTableOfContents(vector<pair<string, int>> &result);
    void readTableOfContents(map<string, int> &result);
    void readTableOfContents(unordered_map<string, int> &result);
    uint64_t readTableOfContentsBytePointer();
    void appendBytes(const char *bytes, const int bytesCount);
    void writeBytes(const char *bytes, const int bytesCount);
    void insertTableOfContentsBytePointer();
    void clear();
    int appendCodes(const vector<WordCode> &codes);
    void appendTableOfContents(const map<string, int> tableOfContents);
    void appendTableOfContents(const vector<pair<string, int>> tableOfContents);
    void appendFile(File &file);
    //   void writeCodes(const vector<WordCode> &codes);
    pair<size_t, ArchiveHeader> readHeader();
    int appendHeader(const ArchiveHeader &archiveHeader);
    int getReadingPosition();
    void setReadingPosition(size_t position);
    void shiftLeftBytes(unsigned int from, unsigned int to, unsigned int count);

private:
    size_t createOnesMask(int numberOfMostSignificantOnes, int totalBits);
    size_t createZeroesMask(int numberOfMostSignificantZeroes, int totalBits);
    size_t bitsCount(int number);
    void close();
};

#endif