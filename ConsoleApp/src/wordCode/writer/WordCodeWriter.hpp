#ifndef WORD_CODE_WRITER_HPP
#define WORD_CODE_WRITER_HPP

#include "../WordCode.hpp"
#include <fstream>
#include <vector>

using std::fstream;
using std::vector;

class WordCodeWriter
{
public:
    void writeCodes(fstream& writeStream, const vector<WordCode>& wordCodes);
};

#endif