#include "ArrayUtils.hpp"
#include <cstddef>
#include <iostream>

template<typename T>
T* ArrayUtils<T>::assignArray(size_t size) {
	try {
		T* array = new T[size];
		return array;
	}
	catch (std::bad_alloc e) {
		std::cerr << "Memory fault!" << std::endl;
		throw e;
	}		
}

template<typename T>
void ArrayUtils<T>::copyArray(T* arr1, T* arr2, size_t size) {
	for (size_t i = 0; i < size; i++) {
		arr1[i] = arr2[i];
	}
}

template<typename T>
void ArrayUtils<T>::increaseCapacity(T* array, size_t capacity) {
    T* newArr = assignArray(capacity*2);
    copyArray(newArr, array, capacity);
    delete[] array;
    array = newArr;
}

template class ArrayUtils<char>;
template class ArrayUtils<size_t>;
