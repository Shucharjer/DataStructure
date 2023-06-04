#pragma once
#include<iostream>
/// <summary>
/// �����
/// ��һϵ�еĽṹ�����Դ洢���������
/// ��Ҫ��̬ʹ���ڴ�
/// ���Զ��ڴ�Ĳ�����ǳ���
/// ���Ҽ���������Ҫ��д��������͸�ֵ������
/// </summary>
/// <typeparam name="...Args"></typeparam>
template <class ...Args>
class LinkNode
{
private:
	// operator new��new�������ǣ�operator newֻ����һ���ڴ棬new��������һ�������⣬����ִ�ж�Ӧ�Ĺ��캯��
	// ��Ϊ������������ֻʹ����operator new
	// ��ûʹ��new
	// ����ϵͳһ��ȷ����ָ��Ĵ�С���ǹ̶���
	// ����ʹ��ָ���κ����͵�ָ�붼�ǿ��Ե�
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
	// ����ʹ��LinkList<Args...>�ȷ�װ�࣬��Ҫֱ��ʹ��LinkNode<Args...>
	LinkNode()
	{
		data = nullptr;
		size = 0;
		next = nullptr;
	}
	// ����ʹ��LinkList<Args...>�ȷ�װ�࣬��Ҫֱ��ʹ��LinkNode<Args...>
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
	// ����ʹ��LinkList<Args...>�ȷ�װ�࣬��Ҫֱ��ʹ��LinkNode<Args...>
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