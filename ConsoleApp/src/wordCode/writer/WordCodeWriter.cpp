#include "WordCodeWriter.hpp"
#include "../WordCodeUtils.hpp"

void WordCodeWriter::writeCodes(fstream& writeStream, const vector<WordCode>& wordCodes) {
    unsigned char buffer = 0;
    int bufferCount = 0;
    for (WordCode wordCode : wordCodes)
    {
        uint16_t wordCodeValue = wordCode.value.to_ulong();
        // writeStream << reinterpret_cast<const char *>(&wordCodeValue), sizeof(wordCodeValue);
        // writeStream << reinterpret_cast<const char *>(&wordCodeValue), 12;

        int leftBitsInCurrentWord = wordCode.BITS;
        while (leftBitsInCurrentWord > 0)
        {
            int bitsToAddCnt = std::min(8 - bufferCount, leftBitsInCurrentWord);
            buffer = buffer << bitsToAddCnt;
            int mask = WordCodeUtils::createOnesMask(bitsToAddCnt, wordCode.BITS);
            int bitsToAdd = wordCodeValue & mask;
            leftBitsInCurrentWord -= bitsToAddCnt;
            int bitsToShiftRightBitsToAdd = wordCode.BITS - bitsToAddCnt;
            bitsToAdd = bitsToAdd >> bitsToShiftRightBitsToAdd;
            // char bitsToAdd = bitsToAddInt >> (wordCode.BITS - bitsToAdd);
            buffer = buffer | bitsToAdd;
            bufferCount += bitsToAddCnt;

            int bitsInDeleteMask = sizeof(wordCodeValue) * 8 - (wordCode.BITS - bitsToAddCnt);
            int deleteMask = WordCodeUtils::createZeroesMask(bitsInDeleteMask);
            wordCodeValue = wordCodeValue & deleteMask;

            int bitsToShiftWordCodeValue = bitsToAddCnt;
            wordCodeValue = wordCodeValue << bitsToShiftWordCodeValue;

            if (bufferCount == 8)
            {
                writeStream << buffer;
                buffer = 0;
                bufferCount = 0;
            }
        }
    }

    if (bufferCount > 0)
    {
        buffer = buffer << 8 - bufferCount;
        writeStream << buffer;
    }
}