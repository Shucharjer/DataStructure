#pragma once
#include<iostream>
/// <summary>
/// 链结点
/// 这一系列的结构都可以存储任意的数据
/// 需要动态使用内存
/// 所以对内存的操作会非常多
/// 而且几乎处处需要重写拷贝构造和赋值操作符
/// </summary>
/// <typeparam name="...Args"></typeparam>
template <class ...Args>
class LinkNode
{
private:
	// operator new与new的区别是：operator new只申请一块内存，new除了申请一块类型外，还会执行对应的构造函数
	// 因为在这个结点类中只使用了operator new
	// 而没使用new
	// 操作系统一旦确定，指针的大小就是固定的
	// 所以使用指向任何类型的指针都是可以的
	unsigned long long* data;
	unsigned short size;
	void initializeData()
	{
		do data = (unsigned long long*)operator new(size);
		while (data == nullptr);
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
	void readNPrintValue(unsigned long long* address)
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
		readNPrintValue((unsigned long long*)buffer, others...);
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