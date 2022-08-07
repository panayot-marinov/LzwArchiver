#include "DirectoryCompressor.hpp"
#include "../file/FileCompressor.hpp"
#include "../../file/File.hpp"
#include "../../path/PathUtils.hpp"
#include <filesystem>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <unordered_map>
#include <vector>
#include <utility>

using std::pair;
using std::unordered_map;

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
        std::string currentFileArchivePath =
            currentFileInputPath.substr(strlen(inputPath));
        std::string currentFileOutputPath = outputPath;
        currentFileOutputPath += "/";
        currentFileOutputPath += currentFileArchivePath.substr(0, currentFileArchivePath.find_last_of('.')) + ".lzw";

        tableOfContents.push_back(std::make_pair(currentFileArchivePath, firstBytePos));
        std::cout << sizeof(' ') << std::endl
                  << currentFileArchivePath.length() << std::endl
                  << strlen(std::to_string(firstBytePos).c_str()) << std::endl;

        tableOfContentsBytes += (sizeof(' ') + currentFileArchivePath.length() + sizeof(' ') + strlen(std::to_string(firstBytePos).c_str()));
        firstBytePos +=
            fileCompressor.archive(currentFileInputPath.c_str(), currentFileArchivePath.c_str(), tempArchiveFile, isRegularFile);
    }
    tableOfContentsBytes += strlen(std::to_string(tableOfContents.size()).c_str());

    std::cout << "tableOfContents\n";
    for (size_t i = 0; i < tableOfContents.size(); i++)
    {
        int oldValue = strlen(std::to_string(tableOfContents[i].second).c_str());
        tableOfContents[i].second += tableOfContentsBytes;
        int newValue = strlen(std::to_string(tableOfContents[i].second).c_str());
        tableOfContents[i].second -= tableOfContentsBytes;
        tableOfContentsBytes += (newValue - oldValue);

        std::cout << tableOfContents[i].first << " " << tableOfContents[i].second << "\n";
    }

    tableOfContentsBytes += (strlen(std::to_string(tableOfContentsBytes).c_str()) + sizeof(' '));
    for (size_t i = 0; i < tableOfContents.size(); i++)
    {
        tableOfContents[i].second += (tableOfContentsBytes + 1); // TODO: why + 2

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
    string tableOfContentsStr = std::to_string(tableOfContentsBytes);
    tableOfContentsStr += ' ';
    archiveFile.appendBytes(tableOfContentsStr.c_str(), tableOfContentsStr.length());
    archiveFile.appendTableOfContents(tableOfContents);
    archiveFile.appendFile(tempArchiveFile);
}

void DirectoryCompressor::unarchive(const char *inputPath, const char *outputPath)
{
    const std::filesystem::path sandbox{"../OutputFiles/Archived"};

    File fileToUnarchive(inputPath);
    size_t fileSize = fileToUnarchive.getSize();

    size_t tableOfContentsByteSize = fileToUnarchive.readTableOfContentsByteSize();
    std::cout << "tbs:" << tableOfContentsByteSize << std::endl;
    fileToUnarchive.setReadingPosition(tableOfContentsByteSize + 1);
    // unordered_map<pair<string, int>> *result;
    // try
    // {
    //     result = new unordered_map<pair<string, int>>;
    // }
    // catch (std::bad_alloc e)
    // {
    //     throw std::runtime_error("Memory for table of contents cannot be initialized.");
    // }

    // fileToUnarchive.readTableOfContents(result);
    int readingPosition = fileToUnarchive.getReadingPosition();

    FileCompressor fileCompressor;
    while (readingPosition < fileSize)
    {
        std::cout << "readingPos= " << readingPosition << std::endl;
        fileCompressor.unarchive(fileToUnarchive, outputPath);
        readingPosition = fileToUnarchive.getReadingPosition();
    }
}

void DirectoryCompressor::unarchiveFile(const char *inputPath, const char *outputPath, const char *filename)
{
    const std::filesystem::path sandbox{"../OutputFiles/Archived"};

    File fileToUnarchive(inputPath);
    size_t fileSize = fileToUnarchive.getSize();

    unordered_map<string, int> *tableOfContents;
    try
    {
        tableOfContents = new unordered_map<string, int>;
    }
    catch (std::bad_alloc e)
    {
        throw std::runtime_error("Memory for table of contents cannot be initialized.");
    }

    fileToUnarchive.readTableOfContents(*tableOfContents);

    for (auto it = tableOfContents->cbegin(); it != tableOfContents->cend(); ++it)
    {
        std::cout << "{" << (*it).first << ": " << (*it).second << "}\n";
    }

    int resultFileFirstByte = tableOfContents->find(string(filename))->second;
    fileToUnarchive.setReadingPosition(resultFileFirstByte);
    int readingPosition = fileToUnarchive.getReadingPosition();

    FileCompressor fileCompressor;

    std::cout << "readingPos= " << readingPosition << std::endl;
    fileCompressor.unarchive(fileToUnarchive, outputPath);
    readingPosition = fileToUnarchive.getReadingPosition();
}