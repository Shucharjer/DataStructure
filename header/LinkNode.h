#pragma once
#include<iostream>
template <class ...Args>
class LinkNode
{
private:
	// unsigned __int64刚好是一个64位指针的大小
	unsigned long long* data;
	unsigned short size;
	void initializeData()
	{
		do
		{
			data = (unsigned long long*)operator new(size);
		} while (data == nullptr);
	}
	void writeValue(unsigned long long* address)
	{
		return;
	}
	template <class T, class ...OtherArgs>
	void writeValue(unsigned long long* address, T value, OtherArgs... others)
	{
		if (address >= data + size) return;
		T* buffer = (T*)address;
		*buffer++ = value;
		writeValue((unsigned long long*)buffer, others...);
	}
	void readValue(unsigned long long* address)
	{
		return;
	}
	template <class T, class ...OtherArgs>
	void readValue(unsigned long long* address, T& value, OtherArgs&... others)
	{
		if (address >= data + size) return;
		T* buffer = (T*)address;
		value = *buffer++;
		readValue((unsigned long long*)buffer, others...);
	}
	void readNPrintValue()
	{
		std::cout << '\n';
		return;
	}
	template <class T, class ...OtherArgs>
	void readNPrintValue(unsigned long long* address, T& value, OtherArgs&... others)
	{
		if (address >= data + size) return;
		T* buffer = (T*)address;
		value = *buffer++;
		std::cout << value << ' ';
		readNPrintValue((unsigned long long*)buffer, others);
	}
public:
	LinkNode<Args...>* next;
	// 尽量使用LinkList<Args...>等封装类，不要直接使用LinkNode<Args...>
	LinkNode()
	{
		data = nullptr;
		size = 0;
		next = nullptr;
	}
	// 尽量使用LinkList<Args...>等封装类，不要直接使用LinkNode<Args...>
	LinkNode(unsigned short size, Args... args)
	{
		this->size = size;
		initializeData();
		writeValue(data, args...);
		next = nullptr;
	}
	LinkNode<Args...>& operator = (const LinkNode<Args...>& obj)
	{
		if (size == 0)
		{
			size = obj.size;
			initializeData();
			memmove(data, obj.data, size);
		}
		else
		{
			memmove(data, obj.data, size);
		}
		//next = obj.next;
		return *this;
	}
	// 尽量使用LinkList<Args...>等封装类，不要直接使用LinkNode<Args...>
	LinkNode(const LinkNode<Args...>& obj)
	{
		size = obj.size;
		//next = obj.next;
		next = nullptr;
		initializeData();
		memmove(data, obj.data, size);
	}
	~LinkNode()
	{
		if (data != nullptr)
		{
			operator delete(data, size);
			data = nullptr;
		}
		next = nullptr;
	}
	void setValue(unsigned short size, Args... args)
	{
		if (this->size == 0) this->size = size;
		if (data == nullptr)initializeData();
		writeValue(data, args...);
	}
	bool getValue(Args&... args)
	{
		if (data == nullptr) return false;
		readValue(data, args...);
		return true;
	}
	void remove()
	{
		if (data != nullptr)
		{
			operator delete(data, size);
		}
		data = nullptr;
	}
	void printValue(Args... args)
	{
		readNPrintValue(data, args...);
	}
};