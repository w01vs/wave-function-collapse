#include "DynamicArray.h"

#include <new>

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
	if(this != &other)
	{
		size = other.size;
		delete[] ptr;
		try
		{
			ptr = new T[other.size];
			for (int i = 0; i < size; ++i)
				ptr[i] = other.ptr[i];
		}
		catch(std::bad_alloc &)
		{
			ptr = nullptr;
			throw;
		}
 	}
	return *this;
}

 