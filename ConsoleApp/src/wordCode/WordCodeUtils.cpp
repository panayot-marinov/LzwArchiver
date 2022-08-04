#include "WordCodeUtils.hpp"
#include <cmath>

size_t WordCodeUtils::createOnesMask(int numberOfMostSignificantOnes, int totalBits)
{
    int bitsToShiftResult = totalBits - numberOfMostSignificantOnes;
    int temp = std::pow(2, numberOfMostSignificantOnes) - 1;
    return (temp << bitsToShiftResult);
}

size_t WordCodeUtils::createZeroesMask(int numberOfMostSignificantZeroes)
{
    int result = std::pow(2, 16 - numberOfMostSignificantZeroes) - 1;
    return result;
}

size_t WordCodeUtils::bitsCount(int number)
{
    if (number == 0)
    {
        return 0;
    }

    int bitsCount = 0;
    while (number != 0)
    {
        bitsCount++;
        number /= 2;
    }

    return bitsCount;
}