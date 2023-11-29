#include "DynamicArray.h"

template <typename T>
DynamicArray<T>::DynamicArray(int size)
{
	this->size = size;
	ptr = new T[size];
}

template <typename T>
DynamicArray<T>::~DynamicArray()
{
	delete[] ptr;
	ptr = nullptr;
}

template <typename T>
T& DynamicArray<T>::operator[](int index)
{
	return ptr[index];
}

template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray& source)
{
	size = source.size;
	ptr = new T[source.size];
	for(int i = 0; i < size; ++i)
	{
		ptr[i] = source.ptr[i];
	}
}

template <typename T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray& other)
{
	if (this == &other)
		return *this;

	delete[] ptr;
	ptr = nullptr;

	ptr = new T[other.size];
	size = other.size;
	for (int i = 0; i < size; ++i)
	{
		ptr[i] = other.ptr[i];
	}

	return *this;
}

 