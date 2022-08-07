#pragma once
#ifndef CHARARRUTILS_HPP
#define CHARARRUTILS_HPP

#include <cstddef>

class CharArrUtils {
public:
    static char* subArr(const char* arr, size_t start, size_t end);
    static void toLowerCharArr(char* arr);

private:
    static char toLower(char symbol);
};

#endif /*CHARARRUTILS_H*/