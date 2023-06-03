#pragma once
#include"LinkNode.h"
#include<iostream>
template <class ...Args>
class LinkList
{
private:
	unsigned short length;
	unsigned short size;
	unsigned short kinds;
	LinkNode<Args...>* head;
	LinkNode<Args...>* rear;
	int getSize()
	{
		return 0;
	}
	template <class T, class ...Others>
	int getSize(T type, Others... others)
	{
		return sizeof(type) + getSize(others...);
	}
public:
	LinkList()
	{
		length = 0;
		size = 0;
		kinds = 0;
		head = nullptr;
		rear = nullptr;
	}
	LinkList<Args...>& operator = (const LinkList<Args...>& obj)
	{
		length = obj.length;
		size = obj.size;
		kinds = obj.kinds;

		// ������
		while (head)
		{
			rear = head->next;
			delete head;
			head = rear;
		}

		// ����������뿽������Ŀ���������ͬ
		if (obj.head)
		{
			LinkNode<Args...>* source = obj.head;
			head = new LinkNode<Args...>();
			*head = *source;
			LinkNode<Args...>* prev = head;
			rear = prev;
			while (source->next)
			{
				source = source->next;
				LinkNode<Args...>* node = new LinkNode<Args...>();
				*node = *source;
				prev->next = node;
				prev = prev->next;
				rear = prev;
			}
		}
		else
		{
			head = nullptr;
			rear = nullptr;
		}
		return *this;
	}
	LinkList(const LinkList<Args...>& obj)
	{
		length = obj.length;
		size = obj.size;
		kinds = obj.kinds;
	

		if (obj.head)
		{
			LinkNode<Args...>* source = obj.head;
			head = new LinkNode<Args...>();
			*head = *source;
			LinkNode<Args...>* prev = head;
			rear = prev;
			while (source->next)
			{
				source = source->next;
				LinkNode<Args...>* node = new LinkNode<Args...>();
				*node = *source;
				prev->next = node;
				prev = prev->next;
				rear = prev;
			}
		}
		else
		{
			head = nullptr;
			rear = nullptr;
		}
	}
	~LinkList()
	{
		while (head)
		{
			// delete�����ͷ�new�ڶ��ж�̬���ɵĶ���ռ䡣 �ͷ�ʱ���Զ�����������������������������������ͷ����ڲ���̬����ĵõ�����Դ
			rear = head->next;
			delete head;
			head = rear;
		}
		head = nullptr;
		rear = nullptr;
	}
	unsigned short getElementSize()
	{
		return size;
	}
	unsigned short getLength()
	{
		return length;
	}
	void add(unsigned short index, Args... args)
	{
		if (size == 0)
		{
			size = getSize(args...);
			kinds = sizeof...(args);
		}
		if (index > length + 1) return;
		LinkNode<Args...>* newNode = new LinkNode<Args...>(size, args...);
		if (head == nullptr)
		{
			head = newNode;
			rear = newNode;
		}
		LinkNode<Args...>* prev = new LinkNode<Args...>();
		prev->next = head;
		for (int i = 1; i < index; i++)
		{
			prev = prev->next;
		}
		newNode->next = prev->next;
		prev->next = newNode;
		delete prev;
		prev = nullptr;
		length++;
	}
	void add(Args... args)
	{
		if (size == 0)
		{
			size = getSize(args...);
			kinds = sizeof...(args);
		}
		LinkNode<Args...>* newNode = new LinkNode<Args...>(size, args...);
		if (head == nullptr)
		{
			head = newNode;
			rear = newNode;
		}
		else
		{
			rear->next = newNode;
			rear = newNode;
		}
		length++;
	}
	// ����������1��ʼ
	bool get(unsigned short index, Args&... args)
	{
		if (length == 0 || length < index) return false;
		LinkNode<Args...>* node = head;
		for (int i = 1; i < index; i++)
		{
			node = node->next;
		}
		node->getValue(args...);
		return true;
	}
	// ��ȡ���һ��������
	bool get(Args&... args)
	{
		if (length == 0)
		{
			return false;
		}
		else
		{
			this->rear->getValue(args...);
		}
		return true;
	}
	// ɾ��ָ���Ĳ�����
	bool remove(unsigned short index, Args&... args)
	{
		if (length == 0 || length < index) return false;
		if (length == 1)
		{
			delete head;
			head = nullptr;
			rear = nullptr;
		}
		LinkNode<Args...>* prev = new LinkNode<Args...>();
		void* addr = (void*)prev;
		// ������Դ��prev��ֵ���ˣ�������prevָ���ֵ����
		// ֱ��delete�Ļ���prev������ǿ��ڴ治�ᱻ�ͷŵ�
		// ������Ҫ��¼һ��prev��ֵ���ڽ���ʱdelete��
		prev->next = head;
		for (int i = 1; i < index; i++)
		{
			prev = prev->next;
		}
		// prevָ��Ҫɾ���Ľ���ǰһ�����
		prev->next->getValue(args...);
		if (prev->next == rear)
		{
			rear = prev;
			delete prev->next;
			prev->next = nullptr;
		}
		else
		{
			void* temp = (void*)prev->next;
			(*prev).next = (*prev).next->next;
			delete temp;
		}
		delete addr;
		
		length--;
		return true;
	}
	void print(Args&... args)
	{
		LinkNode<Args...>* node = head;
		while (node)
		{
			node->printValue(args...);
			node = node->next;
		}
	}
};