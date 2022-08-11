
#include "ArchiveHeader.hpp"
#include "FileCompressor.hpp"
#include "../byte/ByteCompressor.hpp"
#include "../../file/File.hpp"
#include "../../file/hasher/FileHasher.hpp"
#include "../../path/PathUtils.hpp"
#include <iostream>
#include <cmath>
#include <cstring>
#include <filesystem>
#include <utility>
#include <vector>

using std::pair;

uint64_t FileCompressor::archive(const char *inputPath, const char *inputArchivePath,
                                 File &outputFile, bool isRegularFile)
{
    std::cout << "inputPath = " << inputPath << std::endl;
    File inputFile(inputPath);
    uint64_t inputFileSize = inputFile.getSize();

    // header
    ArchiveHeader archiveHeader;
    strcpy(archiveHeader.name, inputArchivePath);
    // strcpy(archiveHeader.mtime, inputFile.getLastModifiedTime());

    uint64_t byteSize = 0;
    if (isRegularFile)
    {
        strcpy(archiveHeader.type, ArchiveHeader::TYPE_REGULAR_FILE);
        // archiveHeader.calculateChecksum();

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

        int firstHeaderBytePosition = outputFile.getSize();
        int lastHeaderBytePosition = outputFile.appendHeader(archiveHeader);
        int lastCodeBytePosition = outputFile.appendCodes(*result);

        outputFile.setReadingPosition(lastHeaderBytePosition);
        int totalBytesToHash = lastCodeBytePosition - lastHeaderBytePosition;
        uint64_t fileHash = fileHasher.hashFile(outputFile, 100, totalBytesToHash);
        outputFile.insertHashValue(fileHash, firstHeaderBytePosition);

        outputFile.setReadingPosition(firstHeaderBytePosition);
        std::cout<<outputFile.getReadingPosition()<<'\n';
        float archivedFileSize = lastCodeBytePosition - firstHeaderBytePosition;
        std::cout<<"input file size = "<<inputFileSize<<'\n'<<"archived file size ="<<archivedFileSize<<std::endl;
        float levelOfCompression = std::floor((archivedFileSize / inputFileSize) * 10.0) / 10.0;
        outputFile.insertLevelOfCompression(levelOfCompression);

        byteSize = lastCodeBytePosition;

        delete result;
    }
    else
    {
        strcpy(archiveHeader.type, ArchiveHeader::TYPE_DIRECTORY);
        archiveHeader.size = 0;
        int firstHeaderBytePosition = outputFile.getSize();
        byteSize = outputFile.appendHeader(archiveHeader);

        outputFile.setReadingPosition(firstHeaderBytePosition);
        float levelOfCompression = 0;
        outputFile.insertLevelOfCompression(levelOfCompression);

        outputFile.setReadingPosition(firstHeaderBytePosition);
        uint64_t filehash = 0;
        outputFile.insertHashValue(filehash, firstHeaderBytePosition);
    }

    return byteSize;
}

void FileCompressor::unarchive(File &inputFile, const char *outputPath)
{
    pair<ArchiveHeader, vector<WordCode> *> archivePair = inputFile.readArchive();

    std::string fileArchivePath = archivePair.first.name;
    // std::string fileArchiveDirectory = PathUtils::extractDirectoryName(fileArchivePath);

    // createDirectoryIfDoesNotExist(outputPath + fileArchiveDirectory);

    // if (PathUtils::extractFileName(fileArchivePath).find('.') == std::string::npos) //TODO:??
    // {
    //     createDirectoryIfDoesNotExist(outputPath + fileArchivePath);
    // }

    if (strcmp(archivePair.first.type, ArchiveHeader::TYPE_DIRECTORY) == 0)
    {
        createDirectoryIfDoesNotExist(outputPath + fileArchivePath);
    }
    else
    {
        std::string fileArchiveDirectory = PathUtils::extractDirectoryName(fileArchivePath);
        createDirectoryIfDoesNotExist(outputPath + fileArchiveDirectory);
    }

    if (std::strcmp(archivePair.first.type, ArchiveHeader::TYPE_REGULAR_FILE) == 0)
    {
        std::string outputArchivePath = outputPath;
        // outputArchivePath += "/";
        outputArchivePath += ("/" + PathUtils::leftTrim(fileArchivePath)); // TODO:??
        File outputFile(outputArchivePath);
        outputFile.clear();

        ByteCompressor byteCompressor;
        byteCompressor.decompressAndWriteBytes(*archivePair.second, outputFile);
    }
}

bool FileCompressor::isArchivedFileCorrupted(File &inputFile)
{
    pair<size_t, ArchiveHeader> headerPair = inputFile.readHeader();
    ArchiveHeader header = headerPair.second;
    uint64_t chksum = header.chksum;
    unsigned int contentSize = header.size;

    std::cout << "rpos=" << inputFile.getReadingPosition() << std::endl;
    uint64_t currentChksum = fileHasher.hashFile(inputFile, 100, contentSize);
    return chksum != currentChksum;
}

void FileCompressor::createDirectoryIfDoesNotExist(const string &path)
{
    const std::filesystem::path fileSandbox{path};
    bool directoryDoesNotExist = !std::filesystem::exists(fileSandbox);

    if (directoryDoesNotExist)
    {
        std::filesystem::create_directory(fileSandbox);
    }
}