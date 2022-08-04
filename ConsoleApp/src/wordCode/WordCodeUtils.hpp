#ifndef WORD_CODE_UTILS_HPP
#define WORD_CODE_UTILS_HPP

#include <cstddef>

class WordCodeUtils
{
public:
    static size_t createOnesMask(int numberOfMostSignificantOnes, int totalBits);
    static size_t createZeroesMask(int numberOfMostSignificantZeroes);
    static size_t bitsCount(int number);
};

#endif