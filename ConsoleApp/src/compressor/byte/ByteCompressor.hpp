#pragma once
#ifndef BYTE_COMPRESSOR_HPP
#define BYTE_COMPRESSOR_HPP

#include "../../file/File.hpp"
#include "../../wordCode/WordCode.hpp"
#include <string>
#include <vector>
#include <unordered_map>
#include <utility>
#include <bitset>

using std::string;
using std::unordered_map;
using std::vector;

class ByteCompressor
{
public:
    void compressBytes(char *bytes, size_t size, vector<WordCode> *result);
    void decompressAndWriteBytes(vector<WordCode> &wordCodes, File& file);

private:
    void initCompressionDictionary(unordered_map<string, WordCode> &dictionary);
    void initDecompressionDictionary(unordered_map<std::bitset<WordCode::BITS>, string> &dictionary);
    char getChar(char input[], int &index);
};

#endif