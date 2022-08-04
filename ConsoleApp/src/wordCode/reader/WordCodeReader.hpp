#ifndef WORD_CODE_READER_HPP
#define WORD_CODE_READER_HPP

#include "../WordCode.hpp"
#include "../../file/File.hpp"
#include <vector>

using std::fstream;
using std::vector;

class WordCodeReader
{
public:
    vector<WordCode>* readCodes(File& file, size_t startPos, size_t bytesCount);
};

#endif