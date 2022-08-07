#include "DirectoryCompressor.hpp"
#include "../file/FileCompressor.hpp"
#include "../../file/File.hpp"
#include "../../path/PathUtils.hpp"
#include <filesystem>
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <utility>

using std::pair;

void DirectoryCompressor::archive(const char *inputPath, const char *outputPath,
                                  const char *outputFilename, const char *outputFileExtension)
{
    const std::filesystem::path sandbox{inputPath};

    std::string tempArchiveFilePath = outputPath;
    tempArchiveFilePath += "/";
    tempArchiveFilePath += outputFilename;
    tempArchiveFilePath += "Temp.";
    tempArchiveFilePath += outputFileExtension;

    File tempArchiveFile(tempArchiveFilePath.c_str());
    tempArchiveFile.clear();

    FileCompressor fileCompressor;
    vector<pair<string, int>> tableOfContents;
    int tableOfContentsBytes = 0;
    int firstBytePos = 0;
    for (auto const &dir_entry : std::filesystem::recursive_directory_iterator{sandbox})
    {
        std::cout << dir_entry.path() << '\n';
        bool isRegularFile = true;
        if (std::filesystem::is_directory(dir_entry))
        {
            isRegularFile = false;
        }

        std::string currentFileInputPath = dir_entry.path().u8string().c_str();
        std::cout << currentFileInputPath << "aa" << currentFileInputPath.find_last_of('.') << std::endl;
        std::string currentFileArchivePath =
            currentFileInputPath.substr(strlen(inputPath));
        std::string currentFileOutputPath = outputPath;
        currentFileOutputPath += "/";
        currentFileOutputPath += currentFileArchivePath.substr(0, currentFileArchivePath.find_last_of('.')) + ".lzw";

        tableOfContents.push_back(std::make_pair(currentFileInputPath, firstBytePos));
        tableOfContentsBytes += (sizeof(' ') + sizeof(currentFileInputPath) + sizeof(' ') + sizeof(firstBytePos));
        firstBytePos +=
            fileCompressor.archive(currentFileInputPath.c_str(), currentFileArchivePath.c_str(), tempArchiveFile, isRegularFile);
    }
    tableOfContentsBytes += sizeof(tableOfContents.size());

    std::cout << "tableOfContents\n";
    for (size_t i = 0; i < tableOfContents.size(); i++)
    {
        tableOfContents[i].second += tableOfContentsBytes;

        std::cout << tableOfContents[i].first << " " << tableOfContents[i].second << "\n";
    }
    std::cout << std::endl;

    std::string bigArchiveFilePath = outputPath;
    bigArchiveFilePath += "/";
    bigArchiveFilePath += outputFilename;
    bigArchiveFilePath += '.';
    bigArchiveFilePath += outputFileExtension;

    File archiveFile(bigArchiveFilePath);
    archiveFile.clear();
    archiveFile.appendTableOfContents(tableOfContents);
    archiveFile.appendFile(tempArchiveFile);
}

void DirectoryCompressor::unarchive(const char *inputPath, const char *outputPath)
{
    const std::filesystem::path sandbox{"../OutputFiles/Archived"};

    FileCompressor fileCompressor;
    File fileToUnarchive(inputPath);
    size_t fileSize = fileToUnarchive.getSize();

    vector<pair<string, int>> *result;
    try
    {
        result = new vector<pair<string,int>>;
    }
    catch (std::bad_alloc e)
    {
        throw std::runtime_error("Memory for table of contents cannot be initialized.");
    }

    fileToUnarchive.readTableOfContents(result);
    int readingPosition = fileToUnarchive.getReadingPosition();
    while (readingPosition < fileSize)
    {
        std::cout << "readingPos= " << readingPosition << std::endl;
        fileCompressor.unarchive(fileToUnarchive, outputPath);
        readingPosition = fileToUnarchive.getReadingPosition();
    }

    // for (auto const &dir_entry : std::filesystem::directory_iterator{sandbox})
    // {
    //     std::cout << dir_entry.path() << '\n';
    //     std::string outputPath = "../OutputFiles/Unarchived/";
    //     //std::string inputPath = dir_entry.path().u8string().c_str();

    //     fileCompressor.unarchive(fileToUnarchive, outputPath.c_str());
    // }
}