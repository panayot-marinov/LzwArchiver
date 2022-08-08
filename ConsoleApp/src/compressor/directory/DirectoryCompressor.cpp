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

void DirectoryCompressor::archive(vector<const char *> inputPaths, const char *outputPath,
                                  const char *outputFilename, const char *outputFileExtension)
{
    std::string bigArchiveFilePath = outputPath;
    bigArchiveFilePath += "/";
    bigArchiveFilePath += outputFilename;
    bigArchiveFilePath += '.';
    bigArchiveFilePath += outputFileExtension;

    File archiveFile(bigArchiveFilePath);
    archiveFile.clear();
    archiveFile.writeBytes("         ", sizeof(uint64_t) + 1);

    vector<pair<string, int>> tableOfContents;
    uint64_t firstBytePos = sizeof(uint64_t) + sizeof(' ');
    FileCompressor fileCompressor;

    for (size_t i = 0; i < inputPaths.size(); i++)
    {
        const std::filesystem::path sandbox{inputPaths[i]};
        std::string lastDirectoryName = sandbox.filename().u8string();

        for (auto const &dir_entry : std::filesystem::recursive_directory_iterator{sandbox})
        {
            std::cout << dir_entry.path() << '\n';
            bool isRegularFile = true;
            if (std::filesystem::is_directory(dir_entry))
            {
                isRegularFile = false;
            }

            std::string currentFileInputPath = dir_entry.path().u8string().c_str();
            std::string currentFileArchivePath = "/" + lastDirectoryName +
                                                 currentFileInputPath.substr(strlen(inputPaths[i]));
            std::string currentFileOutputPath = outputPath;
            currentFileOutputPath += "/";
            currentFileOutputPath += currentFileArchivePath.substr(0, currentFileArchivePath.find_last_of('.')) + ".lzw";

            tableOfContents.push_back(std::make_pair(currentFileArchivePath, firstBytePos));

            firstBytePos =
                fileCompressor.archive(currentFileInputPath.c_str(), currentFileArchivePath.c_str(), archiveFile, isRegularFile);
        }
    }
    std::cout << "tableOfContents\n";
    for (size_t i = 0; i < tableOfContents.size(); i++)
    {
        std::cout << tableOfContents[i].first << " " << tableOfContents[i].second << "\n";
    }

    archiveFile.insertTableOfContentsBytePointer();
    archiveFile.appendTableOfContents(tableOfContents);
}

void DirectoryCompressor::addFilesToArchive(vector<const char *> inputPaths, const char *archivePath)
{
    File archiveFile(archivePath);

    vector<pair<string, int>> tableOfContents;
    uint64_t tableOfContentsBytePointer = archiveFile.readTableOfContentsBytePointer();
    std::cout << "tbp:" << tableOfContentsBytePointer << std::endl;
    archiveFile.setReadingPosition(tableOfContentsBytePointer);

    archiveFile.readTableOfContents(tableOfContents);
    const std::filesystem::path archiveFileSandbox{archivePath};
    std::filesystem::resize_file(archiveFileSandbox, tableOfContentsBytePointer);
    std::cout << "tableOfContents*\n";
    for (size_t i = 0; i < tableOfContents.size(); i++)
    {
        std::cout << tableOfContents[i].first << " " << tableOfContents[i].second << "\n";
    }

    uint64_t firstBytePos = tableOfContentsBytePointer;
    FileCompressor fileCompressor;
    for (size_t i = 0; i < inputPaths.size(); i++)
    {
        const std::filesystem::path sandbox{inputPaths[i]};
        std::string lastDirectoryName = sandbox.filename().u8string();

        for (auto const &dir_entry : std::filesystem::recursive_directory_iterator{sandbox})
        {
            std::cout << dir_entry.path() << '\n';
            bool isRegularFile = true;
            if (std::filesystem::is_directory(dir_entry))
            {
                isRegularFile = false;
            }

            std::string currentFileInputPath = dir_entry.path().u8string().c_str();
            std::string currentFileArchivePath = "/" + lastDirectoryName +
                                                 currentFileInputPath.substr(strlen(inputPaths[i]));

            tableOfContents.push_back(std::make_pair(currentFileArchivePath, firstBytePos));
            firstBytePos =
                fileCompressor.archive(currentFileInputPath.c_str(), currentFileArchivePath.c_str(), archiveFile, isRegularFile);
        }
    }

    std::cout << "tableOfContents\n";
    for (size_t i = 0; i < tableOfContents.size(); i++)
    {
        std::cout << tableOfContents[i].first << " " << tableOfContents[i].second << "\n";
    }
    archiveFile.insertTableOfContentsBytePointer();
    archiveFile.appendTableOfContents(tableOfContents);
    // TODO: if table of contents contains file
}

void DirectoryCompressor::removeFilesFromArchive(vector<const char *> inputPaths, const char *archivePath)
{
    File archiveFile(archivePath);

    uint64_t tableOfContentsBytePointer = archiveFile.readTableOfContentsBytePointer();
    std::cout << "tbp:" << tableOfContentsBytePointer << std::endl;
    archiveFile.setReadingPosition(tableOfContentsBytePointer);

    map<string, int> tableOfContents;
    archiveFile.readTableOfContents(tableOfContents);

    const std::filesystem::path archiveFileSandbox{archivePath};

    uint64_t firstBytePos;
    for (size_t i = 0; i < inputPaths.size(); i++)
    {
        const std::filesystem::path sandbox{inputPaths[i]};
        std::string lastDirectoryName = sandbox.filename().u8string();

        for (auto const &dir_entry : std::filesystem::recursive_directory_iterator{sandbox})
        {
            std::cout << dir_entry.path() << '\n';
            bool isRegularFile = true;
            if (std::filesystem::is_directory(dir_entry))
            {
                isRegularFile = false;
            }

            std::string currentFileInputPath = dir_entry.path().u8string().c_str();
            std::string currentFileArchivePath = "/" + lastDirectoryName +
                                                 currentFileInputPath.substr(strlen(inputPaths[i]));

            std::cout << "inputPaths[i] = " << inputPaths[i] << std::endl;
            std::string filePath = string(PathUtils::leftTrim(dir_entry.path().u8string().c_str()));

            while (tableOfContents.count("/" + filePath) == 0 && filePath.length() > 0)
            {
                size_t slashIndex = filePath.find_first_of("/\\");
                if (slashIndex == string::npos)
                {
                    break;
                }
                filePath = filePath.substr(slashIndex + 1);
                std::cout << "edited filepath = " << filePath << std::endl;
            }

            auto tableOfContentsEntry = tableOfContents.find("/" + filePath);
            if (tableOfContentsEntry == tableOfContents.end()) //entry not found
            {
                continue;
            }
            int resultFileFirstByte = tableOfContentsEntry->second;
            archiveFile.setReadingPosition(resultFileFirstByte);
            int readingPosition = archiveFile.getReadingPosition();

            FileCompressor fileCompressor;

            std::cout << "readingPos= " << readingPosition << std::endl;
            std::pair<size_t, ArchiveHeader> archiveHeaderPair = archiveFile.readHeader();
            unsigned int headerSize = archiveHeaderPair.first - resultFileFirstByte;
            unsigned int fileSize = archiveHeaderPair.second.size + headerSize;
            archiveFile.shiftLeftBytes(resultFileFirstByte, tableOfContentsBytePointer, fileSize);

            std::filesystem::resize_file(archiveFileSandbox, tableOfContentsBytePointer - fileSize);
            tableOfContents.erase(currentFileArchivePath);
        }
    }

    archiveFile.insertTableOfContentsBytePointer();
    archiveFile.appendTableOfContents(tableOfContents);
}

void DirectoryCompressor::unarchive(const char *inputPath, const char *outputPath)
{
    const std::filesystem::path sandbox{"../OutputFiles/Archived"};

    File fileToUnarchive(inputPath);
    uint64_t tableOfContentsBytePointer = fileToUnarchive.readTableOfContentsBytePointer();
    std::cout << "tbp:" << tableOfContentsBytePointer << std::endl;

    fileToUnarchive.setReadingPosition(sizeof(uint64_t));

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
    while (readingPosition < tableOfContentsBytePointer)
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

    uint64_t tableOfContentsBytePointer = fileToUnarchive.readTableOfContentsBytePointer();
    std::cout << "tbp:" << tableOfContentsBytePointer << std::endl;
    fileToUnarchive.setReadingPosition(tableOfContentsBytePointer);

    unordered_map<string, int> tableOfContents;

    fileToUnarchive.readTableOfContents(tableOfContents);

    for (auto it = tableOfContents.cbegin(); it != tableOfContents.cend(); ++it)
    {
        std::cout << "{" << (*it).first << ": " << (*it).second << "}\n";
    }

    int resultFileFirstByte = tableOfContents.find(string(filename))->second;
    fileToUnarchive.setReadingPosition(resultFileFirstByte);
    int readingPosition = fileToUnarchive.getReadingPosition();

    FileCompressor fileCompressor;

    std::cout << "readingPos= " << readingPosition << std::endl;
    fileCompressor.unarchive(fileToUnarchive, outputPath);
    readingPosition = fileToUnarchive.getReadingPosition();
}

void DirectoryCompressor::printArchiveInfo(const char *inputPath) const
{
    File fileToGetInfo(inputPath);

    uint64_t tableOfContentsBytePointer = fileToGetInfo.readTableOfContentsBytePointer();
    std::cout << "tbp:" << tableOfContentsBytePointer << std::endl;
    fileToGetInfo.setReadingPosition(tableOfContentsBytePointer);

    vector<string> *tableOfContents;
    try
    {
        tableOfContents = new vector<string>;
    }
    catch (std::bad_alloc e)
    {
        throw std::runtime_error("Memory for table of contents cannot be initialized.");
    }

    fileToGetInfo.readTableOfContents(*tableOfContents);

    std::cout << "----------- Archive info: -----------\n";
    for (size_t i = 0; i < tableOfContents->size(); i++)
    {
        std::cout << (*tableOfContents)[i] << '\n';
    }
    std::cout << "-------------------------------------" << std::endl;
}
