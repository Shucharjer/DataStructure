#include"LinkNode.h"
/// <summary>
/// 链队列
/// </summary>
/// <typeparam name="...Args">存储的数据</typeparam>
template <class ...Args>
class Queue
{
private:
	LinkNode<Args...>* head;
	LinkNode<Args...>* rear;
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
	Queue()
	{
		head = nullptr;
		rear = nullptr;
		singleSize = 0;
		length = 0;
		kinds = 0;
	}
	Queue<Args...>& operator = (const Queue<Args...>& obj)
	{
		// 直接从LinkList复制过来
		length = obj.length;
		singleSize = obj.singleSize;
		kinds = obj.kinds;
		while (head)
		{
			rear = head->next;
			delete head;
			head = rear;
		}
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
	Queue(const Queue<Args...>& obj)
	{
		length = obj.length;
		singleSize = obj.singleSize;
		kinds = obj.kinds;

		// 换了包装的链表（确信

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
	~Queue()
	{
		while (head)
		{
			rear = head->next;
			delete head;
			head = rear;
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
	bool enQueue(Args... args)
	{
		if (singleSize == 0)
		{
			singleSize = getSize(args...);
			kinds = sizeof...(args);
		}
		LinkNode<Args...>* newNode = new LinkNode<Args...>();
		newNode->setValue(singleSize, args...);
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
		return true;
	}
	bool deQueue(Args&... args)
	{
		if (length == 0) return false;
		head->getValue(args...);
		void* temp = head;
		head = head->next;
		delete temp;
		length--;
		return true;
	}
	bool getHead(Args&... args)
	{
		if (head == nullptr) return false;
		head->getValue(args...);
		return true;
	}
	bool getRear(Args&... args)
	{
		if (rear == nullptr) return false;
		rear->getValue(args...);
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