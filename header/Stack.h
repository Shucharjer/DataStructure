#pragma once
#include"LinkNode.h"

/// <summary>
/// Á´Õ»
/// </summary>
/// <typeparam name="...Args">´æ´¢µÄÊý¾Ý</typeparam>
template <class ...Args>
class Stack
{
private:
	// Õ»¶¥Ö¸Õë
	LinkNode<Args...>* top;
	// Õ»µ×Ö¸Õë
	LinkNode<Args...>* but;
	unsigned short singleSize;
	unsigned short length;
	unsigned short kinds;
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
	Stack()
	{
		top = nullptr;
		but = nullptr;
		singleSize = 0;
		length = 0;
		kinds = 0;
	}
	Stack<Args...>& operator = (const Stack<Args...>& obj)
	{
		length = obj.length;
		singleSize = obj.singleSize;
		kinds = obj.kinds;

		while (but)
		{
			top = but->next;
			delete but;
			but = top;
		}

		if (obj.but)
		{
			LinkNode<Args...>* source = obj.but;
			but = new LinkNode<Args...>();
			*but = *source;
			LinkNode<Args...>* prev = but;
			top = prev;
			while (source->next)
			{
				source = source->next;
				LinkNode<Args...>* node = new LinkNode<Args...>();
				*node = *source;
				prev->next = node;
				prev = prev->next;
				top = prev;
			}
		}
		else
		{
			but = nullptr;
			top = nullptr;
		}
		return *this;
	}
	Stack(const Stack<Args...>& obj)
	{
		length = obj.length;
		singleSize = obj.singleSize;
		kinds = obj.kinds;

		if (obj.but)
		{
			/*LinkNode<Args...>* source = obj.head;
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
			}*/
			LinkNode<Args...>* source = obj.but;
			but = new LinkNode<Args...>();
			*but = *source;
			LinkNode<Args...>* prev = but;
			top = prev;
			while (source->next)
			{
				source = source->next;
				LinkNode<Args...>* node = new LinkNode<Args...>();
				*node = *source;
				prev->next = node;
				prev = prev->next;
				top = prev;
			}
		}
		else
		{
			but = nullptr;
			top = nullptr;
		}
	}
	~Stack()
	{
		while (but)
		{
			top = but->next;
			delete but;
			but = top;
		}
	}
	bool getLength(unsigned short& length)
	{
		length = this->length;
		return singleSize != 0 ? true : false;
	}
	bool getKinds(unsigned short& kinds)
	{
		kinds = this->kinds;
		return kinds != 0 ? true : false;
	}
	bool getElementSize(unsigned short& elementSize)
	{
		elementSize = singleSize;
		return singleSize != 0 ? true : false;
	}
	bool push(Args... args)
	{
		if (singleSize == 0)
		{
			singleSize = getSize(args...);
			kinds = sizeof...(args);
		}
		LinkNode<Args...>* newNode = new LinkNode<Args...>();
		newNode->setValue(singleSize, args...);
		if (but == nullptr)
		{
			but = newNode;
			top = newNode;
		}
		else
		{
			top->next = newNode;
			top = newNode;
		}
		length++;
		return true;
	}
	bool pop(Args&... args)
	{
		if (length == 0) return false;
		LinkNode<Args...>* node = new LinkNode<Args...>();
		void* temp = node;
		node->next = but;
		while (node->next != top)
		{
			node = node->next;
		}
		node->next->getValue(args...);
		if (node->next == but)
		{
			top = nullptr;
			but = nullptr;
		}
		else
		{
			top = node;
		}
		delete node->next;
		node->next = nullptr;
		delete temp;
		length--;
		return true;
	}
	bool clear()
	{
		if (length == 0) return false;
		while (but)
		{
			top = but->next;
			delete but;
			but = top;
		}
		length = 0;
	}
	bool getTop(Args&... args)
	{
		if (length == 0) return false;
		top->getValue(args...);
		return true;
	}
	void print(Args&... args)
	{
		LinkNode<Args...>* node = but;
		while (node)
		{
			node->printValue(args...);
			node = node->next;
		}
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