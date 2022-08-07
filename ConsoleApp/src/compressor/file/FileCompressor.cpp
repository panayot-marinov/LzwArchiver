
#include "ArchiveHeader.hpp"
#include "FileCompressor.hpp"
#include "../byte/ByteCompressor.hpp"
#include "../../file/File.hpp"
#include "../../path/PathUtils.hpp"
#include <iostream>
#include <cmath>
#include <cstring>
#include <filesystem>
#include <utility>
#include <vector>

using std::pair;

int FileCompressor::archive(const char *inputPath, const char *inputArchivePath,
                            File &outputFile, bool isRegularFile)
{
    std::cout << "inputPath = " << inputPath << std::endl;
    File inputFile(inputPath);

    // header
    ArchiveHeader archiveHeader;
    strcpy(archiveHeader.name, inputArchivePath);
    strcpy(archiveHeader.mtime, inputFile.getLastModifiedTime());

    int lastBytePosition = -1;
    if (isRegularFile)
    {
        strcpy(archiveHeader.type, ArchiveHeader::TYPE_REGULAR_FILE);
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

        std::cout << archiveHeader.chksum << " " << archiveHeader.name << " " << archiveHeader.size << " " << archiveHeader.mtime << " " << archiveHeader.type << '\n';
        int lastHeaderBytePosition = outputFile.appendHeader(archiveHeader);
        int lastCodeBytePosition = outputFile.appendCodes(*result);
        lastBytePosition = lastHeaderBytePosition + lastCodeBytePosition;

        delete result;
    }
    else
    {
        strcpy(archiveHeader.type, ArchiveHeader::TYPE_DIRECTORY);
        archiveHeader.calculateChecksum();
        archiveHeader.size = 0;
        lastBytePosition = outputFile.appendHeader(archiveHeader);
    }

    return lastBytePosition;
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

void FileCompressor::createDirectoryIfDoesNotExist(const string &path)
{
    const std::filesystem::path fileSandbox{path};
    bool directoryDoesNotExist = !std::filesystem::exists(fileSandbox);

    if (directoryDoesNotExist)
    {
        std::filesystem::create_directory(fileSandbox);
    }
}