#pragma once
#include<iostream>
template <class ...Args>
class SeqList
{
private:
	char* data;
	unsigned short singleSize;
	unsigned short length;
	unsigned short capacity;
	unsigned short getSize()
	{
		return 0;
	}
	template <class T, class ...OtherArgs>
	unsigned short getSize(T value, OtherArgs... others)
	{
		return sizeof(value) + getSize(others...);
	}
	void checkSingleSize(Args... args)
	{
		if (singleSize == 0)
		{
			singleSize = getSize(args...);
		}
	}
	void checkData()
	{
		if (data == nullptr)
		{
			do data = (char*)operator new(singleSize * capacity);
			while (data == nullptr);
		}
	}
	void checkCapacity()
	{
		if (length == capacity)
		{
			char* newData;
			unsigned short newCapacity = capacity + 16;
			do newData = (char*)operator new(singleSize * newCapacity);
			while (newData == nullptr);
			memmove(newData, data, singleSize * capacity);
			operator delete(data, singleSize * capacity);
			data = newData;
			capacity = newCapacity;
		}
	}
	void writeValue(char* address)
	{
		return;
	}
	template <class T, class ...OtherArgs>
	void writeValue(char* address, T value, OtherArgs... others)
	{
		//if (address >= data + singleSize * (length + 2)) return;
		T* buffer = (T*)address;
		*buffer++ = value;
		writeValue((char*)buffer, others...);
	}
	void readValue(char* address, unsigned short index)
	{
		return;
	}
	template <class T, class ...OtherArgs>
	void readValue(char* address, unsigned short index, T& value, OtherArgs&... others)
	{
		//if (address >= data + singleSize * index) return;
		T* buffer = (T*)address;
		value = *buffer++;
		readValue((char*)buffer, index, others...);
	}
public:
	SeqList()
	{
		data = nullptr;
		singleSize = 0;
		length = 0;
		capacity = 32;
	}
	SeqList<Args...>& operator=(const SeqList<Args...>& obj)
	{
		singleSize = obj.singleSize;
		if (singleSize != 0)
		{
			// obj里装过东西，即需要复制内存
			if (capacity != obj.capacity)
			{
				if (data != nullptr)
				{
					operator delete(data, singleSize * capacity);
				}
				do data = (char*)operator new(singleSize * obj.capacity);
				while (data == nullptr);
				capacity = obj.capacity;
			}
			memmove(data, obj.data, singleSize * capacity);
		}
		length = obj.length;
		return *this;
	}
	SeqList(const SeqList<Args...>& obj)
	{
		singleSize = obj.singleSize;
		length = obj.length;
		capacity = obj.capacity;

		if (obj.singleSize == 0)
		{
			data = nullptr;
		}
		else
		{
			do data = (char*)operator new(singleSize * capacity);
			while (data == nullptr);

			if (length)
			{
				memmove(data, obj.data, singleSize * capacity);
			}
		}
	}
	~SeqList()
	{
		if (data != nullptr)
		{
			operator delete(data, singleSize * capacity);
			data = nullptr;
		}
	}
	bool add(unsigned short index, Args... args)
	{
		if (length + 1 < index) return false;
		checkSingleSize(args...);
		checkData();
		checkCapacity();
		unsigned long long addr = (unsigned long long)data;
		memmove((void*)(addr + singleSize * index), (void*)(addr + singleSize * (index - 1)), singleSize * (length - index + 1));
		addr += singleSize * (index - 1);
		writeValue((char*)addr, args...);
		length++;
		return true;
	}
	bool add(Args... args)
	{
		return add(length + 1, args...);
	}
	bool get(unsigned short index, Args&... args)
	{
		if (length < index || length == 0) return 0;
		char* addr = data + singleSize * (index - 1);
		readValue(addr, index, args...);
		return true;
	}
	bool get(Args&... args)
	{
		if (length == 0)
		{
			return false;
		}
		char* addr = data + singleSize * (length - 1);
		readValue(addr, length, args...);
		return true;
	}
	bool remove(unsigned short index, Args&... args)
	{
		if (length == 0 || length < index)
		{
			return false;
		}
		char* addr = data + singleSize * (index - 1);
		readValue(addr, index, args...);
		memmove(addr, addr + singleSize, singleSize * (length - index));
		memset(data + singleSize * (length - 1), 0, singleSize);
		length--;
		return true;
	}
	bool remove(unsigned short index)
	{
		if (length == 0 || length < index)
		{
			return false;
		}
		char* addr = data + singleSize * (index - 1);
		memmove(addr, addr + singleSize, singleSize * (length - index));
		memset(data + singleSize * (length - 1), 0, singleSize);
		length--;
		return true;
	}
	unsigned short getElementSize()
	{
		return singleSize;
	}
	unsigned short getLength()
	{
		return length;
	}
	unsigned short getCapacity()
	{
		return capacity;
	}
	void getInput()
	{
		return;
	}
	template <class T, class ...OtherArgs>
	void getInput(T& value, OtherArgs&... others)
	{
		std::cin >> value;
		getInput(others...);
	}
};