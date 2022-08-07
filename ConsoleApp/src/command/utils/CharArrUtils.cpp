#include "CharArrUtils.hpp"
#include "ArrayUtils.hpp"
#include <iostream>
#include <cstring>

char* CharArrUtils::subArr(
    const char* arr, size_t start, size_t end) {
    if(start > end) {
        throw std::invalid_argument("Start should be less or equal to end");
    }
    else if(start == end) {
        char* res = new char;
        *res = '\0';
        return res;
    }

    size_t length = strlen(arr);
    if(start > length) {
        throw std::invalid_argument("Start should be less or equal to the length of the array and greater than zero");
    }
    if(end > length) {
        throw std::invalid_argument("End should be less or equal to the length of the array and greater than zero");
    }

    char* result = ArrayUtils<char>::assignArray(end-start+10);

    for (size_t i = start; i < end; i++) {
        result[i-start]  = arr[i];
    }
    result[end-start] = '\0';
    
    return result;
}

void CharArrUtils::toLowerCharArr(char* arr) {
    size_t i = 0;
    while(arr[i] != '\0') {
        arr[i] = toLower(arr[i]);
        i++;
    }
}

char CharArrUtils::toLower(char symbol) {
    if(symbol >= 'A' && symbol <= 'Z') {
        return symbol-'A'+'a';
    }
    return symbol;
}
 