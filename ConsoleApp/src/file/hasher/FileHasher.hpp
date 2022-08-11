#ifndef FILE_HASHER_HPP
#define FILE_HASHER_HPP

#include "../File.hpp"
#include <cstddef>


class FileHasher
{
public:
    uint64_t hashFile(File& file, int bytesStep, int totalBytesToRead);
};

#endif // filehasher.hpp