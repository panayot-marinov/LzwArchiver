#ifndef WORD_CODE_HPP
#define WORD_CODE_HPP

#include <bitset>

struct WordCode
{
    const static int BITS = 11;
    std::bitset<BITS> value;
    // uint16_t value : 12;

    WordCode()
    {
    }

    WordCode(std::bitset<BITS> value)
    {
        this->value = std::bitset<BITS>(value);
    }
};

#endif