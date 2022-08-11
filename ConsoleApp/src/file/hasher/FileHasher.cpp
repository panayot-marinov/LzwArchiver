#include "FileHasher.hpp"
#include <functional>
#include <string>

using std::hash;
using std::string;

uint64_t FileHasher::hashFile(File &file, int bytesStep, int totalBytesToRead)
{
    uint64_t hash = 0;

    int bytesAlreadyRead = 0;
    int currentIterationBytesRead = 1;
    int bytesToRead = std::min(totalBytesToRead - bytesAlreadyRead, bytesStep);

    while (bytesToRead > 0 && currentIterationBytesRead > 0)
    {
        char *bytes = file.readBytes(bytesToRead, currentIterationBytesRead);
        bytes[bytesToRead] = '\0';
        std::string stringToHash = std::to_string(hash) + string(bytes);
        hash = std::hash<string>{}(stringToHash);

        bytesAlreadyRead += currentIterationBytesRead;
        bytesToRead = std::min(totalBytesToRead - bytesAlreadyRead, bytesStep);
    }

    return hash;
}