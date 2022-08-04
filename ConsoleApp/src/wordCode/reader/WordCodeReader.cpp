#include "WordCodeReader.hpp"
#include "../WordCode.hpp"
#include "../WordCodeUtils.hpp"
#include <bitset>
#include <iostream>

using std::bitset;

vector<WordCode> *WordCodeReader::readCodes(File &file, size_t startPos, size_t bytesCount)
{
    //++startPos;
    vector<WordCode> *result;
    try
    {
        result = new vector<WordCode>;
    }
    catch (std::bad_alloc e)
    {
        throw std::runtime_error("Memory for compressed data cannot be initialized.");
    }

    const int bitsInWordCode = WordCode::BITS;
    file.setReadingPosition(startPos);

    bitset<bitsInWordCode> buffer;
    buffer.reset();
    int bufferCount = 0;
    size_t bytesRead = 0;
    while (bytesRead < bytesCount)
    {
        char currentByte = file.readByte();
        bytesRead++;
        // uint16_t wordCodeValue = wordCode.value.to_ulong();
        int leftBitsInCurrentByte = 8;
        while (leftBitsInCurrentByte > 0)
        {
            int bitsToAddCnt = std::min(bitsInWordCode - bufferCount, leftBitsInCurrentByte);
            buffer = buffer << bitsToAddCnt;
            int mask = WordCodeUtils::createOnesMask(bitsToAddCnt, 8);
            int bitsToAdd = currentByte & mask;
            leftBitsInCurrentByte -= bitsToAddCnt;

            int bitsToShiftRightBitsToAdd = 8 - bitsToAddCnt;
            bitsToAdd = bitsToAdd >> bitsToShiftRightBitsToAdd;
            // char bitsToAdd = bitsToAddInt >> (wordCode.BITS - bitsToAdd);
            buffer = buffer | (bitset<bitsInWordCode>)bitsToAdd;
            bufferCount += bitsToAddCnt;

            // int bitsInDeleteMask = sizeof(wordCodeValue) * 8 - (wordCode.BITS - bitsToAddCnt);
            // int deleteMask = WordCodeUtils::createZeroesMask(bitsInDeleteMask, wordCode.BITS);
            // wordCodeValue = wordCodeValue & deleteMask;

            int bitsToShiftCurrentByte = bitsToAddCnt;
            currentByte = currentByte << bitsToShiftCurrentByte;

            if (bufferCount == bitsInWordCode)
            {
                result->push_back(WordCode(buffer));
                buffer.reset();
                bufferCount = 0;
            }
        }
    }

    // for (WordCode code : *result)
    // {
    //     std::cout << code.value.to_ulong() << " ";
    // }
    // std::cout << std::endl;

    // if (bufferCount > 0)
    // {
    //     buffer = buffer << bitsInWordCode - bufferCount;
    //     result->push_back(WordCode(buffer));
    // }

    return result;
}