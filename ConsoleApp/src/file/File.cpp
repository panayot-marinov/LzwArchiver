#include "File.hpp"
#include "../wordCode/reader/WordCodeReader.hpp"
#include "../wordCode/writer/WordCodeWriter.hpp"
#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstring>
#include <iostream>
//#include <filesystem>
#include <sys/stat.h>
#include <string>

using std::string;
using std::stringstream;

File::File(const string &path)
{
    this->path = path;
}

File::~File()
{
    close();
}

size_t File::getSize() const
{
    // std::ifstream in(path, std::ifstream::ate | std::ifstream::binary);
    // return in.tellg();

    struct stat stat_buf;
    int rc = stat(path.c_str(), &stat_buf);
    return rc == 0 ? stat_buf.st_size : -1;
}

const char *File::getLastModifiedTime() const
{
    /*fs::path p{path};
    fs::file_time_type ftime = fs::last_write_time(p);
    auto sctp = std::chrono::time_point_cast<std::chrono::system_clock::duration>(ftime);
    std::time_t tt = std::chrono::system_clock::to_time_t(sctp);

    std::tm *gmt = std::gmtime(&tt);
    stringstream buffer;
    buffer << std::put_time(gmt, "%A, %d %B %Y %H:%M");
    const char* formattedFileTime = buffer.str().c_str()

    return formattedFileTime;*/
    return "bc";
}

char File::readByte()
{
    if (!readStream.is_open())
    {
        readStream.open(path, std::ios::in);
        if (!readStream.good())
        {
            throw std::invalid_argument("Read stream cannot be opened");
        }
    }

    char byte;
    readStream.read(&byte, 1);

    return byte;
}

char *File::readBytes(const int bytesCount, int &bytesRead)
{
    if (!readStream.is_open())
    {
        readStream.open(path, std::ios::in);
        if (!readStream.good())
        {
            throw std::invalid_argument("Read stream cannot be opened");
        }
    }

    char *bytes = nullptr;
    try
    {
        bytes = new char[bytesCount];
    }
    catch (std::bad_alloc e)
    {
        throw std::runtime_error("Memory for compressed data cannot be initialized.");
    }

    readStream.read(bytes, bytesCount);
    bytesRead = readStream.gcount();

    return bytes;
}

pair<ArchiveHeader, vector<WordCode> *> File::readArchive()
{
    pair<size_t, ArchiveHeader> headerPair = this->readHeader();
    ArchiveHeader archiveHeader = headerPair.second;
    size_t archiveContentStartPos = headerPair.first;

    vector<WordCode> *wordCodes = nullptr;

    if (std::strcmp(archiveHeader.type, ArchiveHeader::TYPE_REGULAR_FILE) == 0 &&
        archiveHeader.size > 0)
    {
        WordCodeReader wordCodeReader;
        wordCodes = wordCodeReader.readCodes(*this, archiveContentStartPos, archiveHeader.size);
    }

    return std::make_pair(archiveHeader, wordCodes);
}

void File::readTableOfContents(vector<string> &result)
{
    if (!readStream.is_open())
    {
        readStream.open(path, std::ios::in);
        if (!readStream.good())
        {
            throw std::invalid_argument("Read stream cannot be opened");
        }
    }

    int tableOfContentsByteSize;
    readStream >> tableOfContentsByteSize;

    int tableOfContentsSize;
    readStream >> tableOfContentsSize;

    for (size_t i = 0; i < tableOfContentsSize; i++)
    {
        string entryName;
        int entryFirstBytePos;

        readStream >> entryName;
        readStream >> entryFirstBytePos;
        result.push_back(entryName);
    }
}

void File::readTableOfContents(unordered_map<string, int> &result)
{
    if (!readStream.is_open())
    {
        readStream.open(path, std::ios::in);
        if (!readStream.good())
        {
            throw std::invalid_argument("Read stream cannot be opened");
        }
    }

    int tableOfContentsByteSize;
    readStream >> tableOfContentsByteSize;

    int tableOfContentsSize;
    readStream >> tableOfContentsSize;

    for (size_t i = 0; i < tableOfContentsSize; i++)
    {
        string entryName;
        int entryFirstBytePos;

        readStream >> entryName;
        readStream >> entryFirstBytePos;
        result[entryName] = entryFirstBytePos;
    }
}

size_t File::readTableOfContentsByteSize()
{
    if (!readStream.is_open())
    {
        readStream.open(path, std::ios::in);
        if (!readStream.good())
        {
            throw std::invalid_argument("Read stream cannot be opened");
        }
    }

    int tableOfContentsByteSize;
    readStream >> tableOfContentsByteSize;

    return tableOfContentsByteSize;
}

void File::appendBytes(const char *bytes, const int bytesCount)
{
    fstream writeStream;

    writeStream.open(path, std::ios::out | std::ios::app);
    if (!writeStream.good())
    {
        throw std::invalid_argument("Write stream cannot be opened");
    }

    writeStream.write(bytes, bytesCount);

    writeStream.close();
}

void File::writeBytes(const char *bytes, const int bytesCount)
{
    fstream writeStream;

    writeStream.open(path, std::ios::out);
    if (!writeStream.good())
    {
        throw std::invalid_argument("Write stream cannot be opened");
    }

    writeStream.write(bytes, bytesCount);

    writeStream.close();
}

void File::clear()
{
    fstream writeStream;

    writeStream.open(path, std::ios::out);
    if (!writeStream.good())
    {
        throw std::invalid_argument("Write stream cannot be opened");
    }

    writeStream.close();
}

int File::appendCodes(const vector<WordCode> &wordCodes)
{
    fstream writeStream;

    writeStream.open(path, std::ios::out | std::ios::app | std::ios::binary);
    if (!writeStream.good())
    {
        throw std::invalid_argument("Write stream cannot be opened");
    }

    WordCodeWriter wordCodeWriter;
    wordCodeWriter.writeCodes(writeStream, wordCodes);
    // // writeStream << wordCode.value;

    int lastWrittenBytePos = writeStream.tellp();
    writeStream.close();
    return lastWrittenBytePos;
}

void File::appendTableOfContents(const vector<pair<string, int>> tableOfContents)
{
    fstream writeStream;

    writeStream.open(path, std::ios::out | std::ios::app);
    if (!writeStream.good())
    {
        throw std::invalid_argument("Write stream cannot be opened");
    }

    writeStream << tableOfContents.size() << ' ';
    for (size_t i = 0; i < tableOfContents.size(); i++)
    {
        writeStream << tableOfContents[i].first << ' ' << tableOfContents[i].second << ' ';
    }
}

void File::appendFile(File &file)
{
    fstream writeStream;

    writeStream.open(path, std::ios::out | std::ios::app | std::ios::binary);
    if (!writeStream.good())
    {
        throw std::invalid_argument("Write stream cannot be opened");
    }

    int bytesRead = 0;
    char *bytes = nullptr;
    try
    {
        bytes = new char[APPEND_FILE_TRANSFER_BYTES + 1];
    }
    catch (std::bad_alloc e)
    {
        throw std::runtime_error("Memory for compressed data cannot be initialized.");
    }

    file.setReadingPosition(0);
    bytes = file.readBytes(APPEND_FILE_TRANSFER_BYTES, bytesRead);
    std::cout << "bytesRead:" << bytes << std::endl;
    while (bytesRead != 0)
    {
        this->appendBytes(bytes, bytesRead);
        bytes = file.readBytes(APPEND_FILE_TRANSFER_BYTES, bytesRead);
        std::cout << "bytesRead:" << bytes << std::endl;
    }
}

// void File::writeCodes(const vector<WordCode> &wordCodes)
// {
//     fstream writeStream;

//     writeStream.open(path, std::ios::out | std::ios::binary);
//     if (!writeStream.good())
//     {
//         throw std::invalid_argument("Write stream cannot be opened");
//     }

//     for (WordCode wordCode : wordCodes)
//     {
//         writeStream << wordCode.value;
//     }

//     writeStream.close();
// }

pair<size_t, ArchiveHeader> File::readHeader()
{
    if (!readStream.is_open())
    {
        readStream.open(path, std::ios::in);
        if (!readStream.good())
        {
            throw std::invalid_argument("Read stream cannot be opened");
        }
    }

    ArchiveHeader archiveHeader;
    readStream >> archiveHeader.chksum;
    readStream >> archiveHeader.name;
    readStream >> archiveHeader.size;
    readStream >> archiveHeader.mtime;
    readStream.ignore(1); // Ignore whitespace
    readStream.read(archiveHeader.type, 1);
    archiveHeader.type[1] = '\0';
    int streamPos = readStream.tellg();

    return std::make_pair(streamPos, archiveHeader);
}

int File::appendHeader(const ArchiveHeader &archiveHeader)
{
    fstream writeStream;

    writeStream.open(path, std::ios::out | std::ios::app);
    if (!writeStream.good())
    {
        throw std::invalid_argument("Write stream cannot be opened");
    }

    writeStream << archiveHeader.chksum << ' ' << archiveHeader.name << ' ' << archiveHeader.size << ' '
                << archiveHeader.mtime << ' ' << archiveHeader.type;

    int lastWrittenBytePos = writeStream.tellp();
    writeStream.close();
    return lastWrittenBytePos;
}

int File::getReadingPosition()
{
    if (!readStream.is_open())
    {
        readStream.open(path, std::ios::in);
        if (!readStream.good())
        {
            throw std::invalid_argument("Read stream cannot be opened");
        }
    }

    return readStream.tellg();
}

void File::setReadingPosition(size_t position)
{
    readStream.seekg(position);
}

void File::close()
{
    readStream.close();
}
