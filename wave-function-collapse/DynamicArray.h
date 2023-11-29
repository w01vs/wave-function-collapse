#pragma once
template<typename T>
class DynamicArray
{
public:
	DynamicArray(int size);
	~DynamicArray();
	T& operator[](int index);
	DynamicArray(const DynamicArray& source);
	DynamicArray& operator=(const DynamicArray& other);
private:
	int size;
	T* ptr;
};


