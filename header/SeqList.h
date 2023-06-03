#include<stdlib.h>
template <class ...Args>
class SeqList
{
private:
	unsigned long long* data;
	unsigned short length;
	unsigned short singlesize;
	unsigned short size;

	unsigned short getSize()
	{
		return 0;
	}
	template <class T, class ...OtherArgs>
	unsigned short getSize(T val, OtherArgs... others)
	{
		return sizeof(val) + getSize(others...);
	}
	void copyFrom(unsigned long long* sourceAddress)
	{
		if (this->data == nullptr)
		{
			return;
		}
		char* targetAddress = (char*)this->data;
		char* buffer = (char*)sourceAddress;
		for (int i = 0; i < this->size * this->singlesize; i++)
		{
			*targetAddress++ = *buffer++;
		}
	}
public:
	SeqList()
	{
		this->data = nullptr;
		this->length = 0;
		this->size = 32;
	}
	SeqList<Args...>& operator = (const SeqList<Args...>& obj)
	{
		if (obj.data == nullptr)
		{
			this->data = nullptr;
			this->length = 0;
			this->next = nullptr;
		}
		else
		{
			this->singlesize = obj.singlesize;
			this->data = (unsigned long long*)malloc(obj.size * this->singlesize);
			this->size = obj.size;
			copyFrom(obj.data);
			this->length = obj.length;
		}
	}
	SeqList(const SeqList<Args...>& obj)
	{
		this->singlesize = obj.singlesize;
		this->length = obj.length;
		this->size = obj.size;
		this->data = (unsigned long long*)malloc(this->size * this->singlesize);
		this->copyFrom(obj.data);
	}
	~SeqList()
	{
		if (this->data != nullptr)
		{
			free(data);
		}
	}
	void add(Args... args)
	{
		if (this->singlesize == 0)
		{
			this->singlesize = getSize(args...);
		}
		if (this->data == nullptr)
		{
			this->data = (unsigned long long*)malloc(this->singlesize * 32);
		}
		if (this->length == this->size)
		{
			free(this->data);

		}
	}
};