#pragma once
#include"LinkNode.h"
// 由于使用模板，继承比较困难，也不能很好地把声明与实现分开
template <class ...Args>
class LinkList
{
private:
	// 链表的长度
	unsigned short length;
	// 一个参数包的字节数
	unsigned short size;
	// 一个参数包中的参数个数
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
	// 赋值操作符
	LinkList<Args...>& operator = (const LinkList<Args...>& obj)
	{
		length = obj.length;
		size = obj.size;
		kinds = obj.kinds;

		// 先重置
		while (head)
		{
			rear = head->next;
			delete head;
			head = rear;
		}

		// 后面的内容与拷贝构造的拷贝部分相同
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
	// 拷贝构造
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
			// delete用于释放new在堆中动态生成的对象空间。
			// 释放时会自动调用类的析构函数，在析构函数中用于释放类内部动态分配的得到的资源
			// 因为在链结点的析构函数中delete掉了链结点new出来的内存
			// 所以不需要先delete掉链结点中new出来的内存
			rear = head->next;
			delete head;
			head = rear;
		}
		// 当跳出循环时
		// head为nullptr
		// 而head又是从rear那里赋值得到的
		// 所以rear也为nullptr
		// 不需要下面的两条语句也不会出现野指针
		// head = nullptr;
		// rear = nullptr;
		// 该析构可适用于其它拥有两个指针的结构中，如链栈和链队列
	}
	unsigned short getElementSize()
	{
		return size;
	}
	unsigned short getLength()
	{
		return length;
	}
	// 指定位置插入
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
	// 默认尾插
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
	// 数据索引从1开始
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
	// 获取最后一个参数包
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
	// 删除指定的参数包
	bool remove(unsigned short index, Args&... args)
	{
		if (length == 0 || length < index) return false;
		if (length == 1)
		{
			delete head;
			head = nullptr;
			rear = nullptr;
			return true;
		}
		LinkNode<Args...>* prev = new LinkNode<Args...>();
		void* addr = (void*)prev;
		// 问题来源：prev的值变了，而不是prev指向的值变了
		// 直接delete的话，prev本身的那块内存不会被释放掉
		// 所以需要记录一下prev的值，在结束时delete掉
		prev->next = head;
		for (int i = 1; i < index; i++)
		{
			prev = prev->next;
		}
		// prev指在要删除的结点的前一个结点
		prev->next->getValue(args...);
		if (prev->next == rear)
		{
			rear = prev;
			delete prev->next;
			prev->next = nullptr;
		}
		else if (prev->next == head)
		{
			head = prev->next->next;
			delete prev->next;
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
	bool remove(unsigned short index)
	{
		if (length == 0 || length < index) return false;
		if (length == 1)
		{
			delete head;
			head = nullptr;
			rear = nullptr;
			return true;
		}
		LinkNode<Args...>* prev = new LinkNode<Args...>();
		void* addr = (void*)prev;
		// 问题来源：prev的值变了，而不是prev指向的值变了
		// 直接delete的话，prev本身的那块内存不会被释放掉
		// 所以需要记录一下prev的值，在结束时delete掉
		prev->next = head;
		for (int i = 1; i < index; i++)
		{
			prev = prev->next;
		}
		// prev指在要删除的结点的前一个结点
		//prev->next->getValue(args...);
		if (prev->next == rear)
		{
			rear = prev;
			delete prev->next;
			prev->next = nullptr;
		}
		else if (prev->next == head)
		{
			head = prev->next->next;
			delete prev->next;
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
	void print(Args... args)
	{
		LinkNode<Args...>* node = head;
		while (node)
		{
			node->printValue(args...);
			node = node->next;
			//std::cout << '\n';
		}
	}
	unsigned short getKinds()
	{
		return kinds;
	}
	void getInput()
	{
		return;
	}
	// 统一获取输入，否则会需要大量的语句来协调输入的类型与次数
	template <class T, class ...OtherArgs>
	void getInput(T& value, OtherArgs&... others)
	{
		std::cin >> value;
		getInput(others...);
	}
	unsigned short find(Args... args)
	{
		if (length == 0) return 0;
		LinkNode<Args...>* temp = new LinkNode<Args...>();
		temp->setValue(size, args...);
		LinkNode<Args...>* node = head;
		for (int index = 1; index <= length; index++)
		{
			if ((*temp) == (*node))
			{
				return index;
			}
			node = node->next;
		}
		delete temp;
		return 0;
	}
	bool clear()
	{
		if (length == 0) return false;
		while (head)
		{
			rear = head->next;
			delete head;
			head = rear;
		}
		length = 0;
		return true;
	}
};