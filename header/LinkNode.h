#pragma once
#include<iostream>
/// <summary>
/// 链结点
/// 它是这一系列结构构筑的基础
/// 它之所以没有被继承还是因为参数包继承好像有点麻烦
/// 这一系列的结构都可以存储任意的数据
/// （当然你非要存其它动态分配内存的类型进去那也没什么办法，比如std::string，肯定会报错的，非要塞就只能想其它办法）
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
		//if (address >= data + size) return;
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
		//if (address >= data + size) return;
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
		//if (address >= data + size) return;
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
	// 重载等号为在内存中比较它们的值
	bool operator == (const LinkNode<Args...>& obj)
	{
		if (this->data != nullptr && obj.data != nullptr)
			return !memcmp(data, obj.data, size);
		else
			return false;
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
	// 传值，用值的引用，不改变原来的值的大小
	// 因为没有存储参数包中每个类型占的字节数，只是为了方便打印把参数包传进去
	// 在之后的其它结构中也会使用这种方式
	// （越写越感觉起初的代码写得很糟糕）
	void printValue(Args... args)
	{
		readNPrintValue(data, args...);
	}
};