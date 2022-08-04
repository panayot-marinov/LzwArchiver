#include "ByteCompressor.hpp"
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

void ByteCompressor::compressBytes(char *bytes, size_t size, vector<WordCode> *result)
{
    unordered_map<string, WordCode> dictionary;
    initCompressionDictionary(dictionary);

    int index = 0;

    char ch = getChar(bytes, index);
    string str(1, ch);

    int bytesRead = 0;
    // while (ch != '\0')
    while (bytesRead < size)
    {
        ch = getChar(bytes, index);
        string key = str + ch;

        if (dictionary.find(key) == dictionary.end())
        {
            WordCode foundValue = dictionary.find(str)->second;
            result->push_back(foundValue);

            WordCode newValue{(uint16_t)dictionary.size()};
            dictionary[key] = newValue;
            str = ch;
        }
        else
        {
            str = key;
        }

        ++bytesRead;
    }
    // result->push_back(dictionary.find(str)->second);
}

void ByteCompressor::decompressAndWriteBytes(vector<WordCode> &wordCodes, File &file)
{
    string result;
    size_t resultSize = 0;

    unordered_map<std::bitset<WordCode::BITS>, string> dictionary;
    initDecompressionDictionary(dictionary);

    file.clear();
    for (size_t i = 0; i < wordCodes.size() - 1; i++)
    {
        WordCode current = wordCodes[i];
        WordCode next = wordCodes[i + 1];

        string currentValue = dictionary.find(current.value)->second;
        string nextValue = dictionary.find(next.value)->second;
        string newValue = currentValue + nextValue;

        dictionary[(std::bitset<WordCode::BITS>)dictionary.size()] = newValue;

        string valueToWrite = dictionary.find(current.value)->second;
        file.appendBytes(valueToWrite.c_str(), valueToWrite.length());
        // resultSize += dictionary.find(current)->second.size();
    }

    WordCode current = wordCodes[wordCodes.size() - 1];
    string currentValue = dictionary.find(current.value)->second;
    string valueToWrite = dictionary.find(current.value)->second;
    file.appendBytes(valueToWrite.c_str(), valueToWrite.length());

    //++resultSize;
}

void ByteCompressor::initCompressionDictionary(unordered_map<string, WordCode> &dictionary)
{
    for (int i = 0; i < 256; i++)
    {
        string key(1, (char)i);
        WordCode currentWordCode(i);
        dictionary[key] = currentWordCode;
    }
}

void ByteCompressor::initDecompressionDictionary(unordered_map<std::bitset<WordCode::BITS>, string> &dictionary)
{
    for (int i = 0; i < 256; i++)
    {
        string value(1, (char)i);
        std::bitset<WordCode::BITS> currentBitset = std::bitset<WordCode::BITS>(i);
        dictionary[currentBitset] = value;
    }
}

char ByteCompressor::getChar(char input[], int &index)
{
    if (input[index] != '\0')
    {
        return input[index++];
    }

    return '\0';
}
