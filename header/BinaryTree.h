
template <class ...Args>
class BinaryTree
{
private:
	char* data;
	unsigned short size;
	unsigned short kinds;
	BinaryTree<Args...>* leftChild;
	BinaryTree<Args...>* rightChild;
	int getSize()
	{
		return 0;
	}
	template <class T, class ...Others>
	int getSize(T type, Others... others)
	{
		return sizeof(type) + getSize(others...);
	}
	void writeValue(char* address)
	{
		return;
	}
	template <class T, class ...OtherArgs>
	void writeValue(char* address, T value, OtherArgs... others)
	{
		T* buffer = (T*)address;
		*buffer++ = value;
		writeValue((char*)buffer, others...);
	}
	void readValue(char* address)
	{
		return;
	}
	template <class T, class... OtherArgs>
	void readValue(char* address, T& value, OtherArgs&... others)
	{
		T* buffer = (T*)address;
		value = *buffer++;
		readValue((char*)buffer, others...);
	}
	void readNPrintValue(char* address)
	{
		return;
	}
	template <class T, class ...OtherArgs>
	void readNPrintValue(char* address, T value, OtherArgs... others)
	{
		T* buffer = (T*)address;
		value = *buffer++;
		std::cout << value << ' ';
		readNPrintValue((char*)buffer, others...);
	}
public:
	BinaryTree()
	{
		data = nullptr;
		size = 0;
		kinds = 0;
		leftChild = nullptr;
		rightChild = nullptr;
	}
	BinaryTree<Args...>& operator = (const BinaryTree<Args...>& obj)
	{
		size = obj.size;
		kinds = obj.kinds;

		// 先析构，后重构
		if (data != nullptr)
		{
			operator delete(data, size);
			data = nullptr;
		}
		if (leftChild != nullptr)
		{
			delete leftChild;
			leftChild = nullptr;
		}
		if (rightChild != nullptr)
		{
			delete rightChild;
			rightChild = nullptr;
		}

		if (obj.data != nullptr)
		{
			do data = (char*)operator new(size);
			while (data == nullptr);
			memmove(data, obj.data, size);

			if (obj.leftChild != nullptr)
			{
				leftChild = new BinaryTree<Args...>();
				*leftChild = *(obj.leftChild);
			}

			if (obj.rightChild != nullptr)
			{
				rightChild = new BinaryTree<Args...>();
				*rightChild = *(obj.rightChild);
			}
		}
		else
		{
			data = nullptr;
			leftChild = nullptr;
			rightChild = nullptr;
		}
		return *this;
	}
	BinaryTree(const BinaryTree<Args...>& obj)
	{
		size = obj.size;
		kinds = obj.kinds;


		if (obj.data != nullptr)
		{
			do data = (char*)operator new(size);
			while (data == nullptr);
			memmove(data, obj.data, size);

			if (obj.leftChild != nullptr)
			{
				leftChild = new BinaryTree<Args...>();
				*leftChild = *(obj.leftChild);
			}

			if (obj.rightChild != nullptr)
			{
				rightChild = new BinaryTree<Args...>();
				*rightChild = *(obj.rightChild);
			}
		}
		else
		{
			data = nullptr;
			leftChild = nullptr;
			rightChild = nullptr;
		}
	}
	~BinaryTree()
	{
		if (data != nullptr)
		{
			operator delete(data, size);
			data = nullptr;
		}
		// 左右孩子在创建时都是new出来的，在析构时应该使用delete
		// delete内部递归
		if (leftChild != nullptr)
		{
			delete leftChild;
			leftChild = nullptr;
		}
		if (rightChild != nullptr)
		{
			delete rightChild;
			rightChild = nullptr;
		}
	}
	bool setValue(Args... args)
	{
		if (size == 0)
		{
			size = getSize(args...);
		}
		if (kinds == 0)
		{
			kinds = sizeof...(args);
		}
		if (data == nullptr)
		{
			do data = (char*)operator new(size);
			while (data == nullptr);
		}
		writeValue(data, args...);
		return true;
	}
	bool getValue(Args&... args)
	{
		if (data == nullptr) return false;
		readValue(data, args...);
		return true;
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
	void print(Args... args)
	{
		readNPrintValue(data, args...);
		std::cout << '\n';
	}
	void createTree(Args... args)
	{
		if (data != nullptr)
		{
			operator delete(data, size);
			data = nullptr;
		}
		// 左右孩子在创建时都是new出来的，在析构时应该使用delete
		if (leftChild != nullptr)
		{
			delete leftChild;
			leftChild = nullptr;
		}
		if (rightChild != nullptr)
		{
			delete rightChild;
			rightChild = nullptr;
		}

		std::cout << "输入元素的值：\n";
		getInput(args...);
		setValue(args...);
		std::cout << "是否有左孩子？（输入y/else）\n";
		char flag;
		std::cin >> flag;
		if (flag == 'y')
		{
			leftChild = new BinaryTree<Args...>();
			leftChild->createTree(args...);
		}
		else
		{
			leftChild = nullptr;
		}
		std::cout << "是否有右孩子？（输入y/else）\n";
		std::cin >> flag;
		if (flag == 'y')
		{
			rightChild = new BinaryTree<Args...>();
			rightChild->createTree(args...);
		}
		else
		{
			rightChild = nullptr;
		}
	}
	void preOrderTreverse(Args... args)
	{
		print(args...);
		if (leftChild != nullptr) leftChild->preOrderTreverse(args...);
		if (rightChild != nullptr) rightChild->preOrderTreverse(args...);
	}
	void midOrderTreverse(Args... args)
	{
		if (leftChild != nullptr) leftChild->preOrderTreverse(args...);
		print(args...);
		if (rightChild != nullptr) rightChild->preOrderTreverse(args...);
	}
	void postOrderTreverse(Args... args)
	{
		if (leftChild != nullptr) leftChild->preOrderTreverse(args...);
		if (rightChild != nullptr) rightChild->preOrderTreverse(args...);
		print(args...);
	}
	// 寻找参数包的值为某一具体参数值的结点的双亲
	bool findParent(BinaryTree<Args...>& kid, BinaryTree<Args...>& parent)
	{
		bool flag = false;
		if (!memcmp(leftChild->data, kid.data, size))
		{
			flag = true;
			parent = *this;
		}
		if (!memcmp(rightChild->data, kid.data, size))
		{
			flag = true;
			parent = *this;
		}

		if (flag)
		{
			return true;
		}
		else
		{
			if (leftChild)
				flag = leftChild->findParent(kid, parent);
			if (rightChild)
				flag = leftChild->findParent(kid, parent);
		}
		return flag;
	}
	bool findChild(BinaryTree<Args...>& parent, BinaryTree<Args...>& left, BinaryTree<Args...>& right, bool findLeft, bool findRight)
	{
		bool flag = false;
		findLeft = false;
		findRight = false;
		if (!memcmp(data, parent.data, size))
		{
			// 这个结点就是双亲结点
			if (leftChild)
			{
				findLeft = true;
				left = *leftChild;
			}
			if (rightChild)
			{
				findRight = true;
				right = *rightChild;
			}	
			flag = true;
		}
		

		if (flag)
		{
			return true;
		}
		else
		{
			if (leftChild)
				flag = leftChild->findChild(parent, left, right, findLeft, findRight);
			if (rightChild)
				flag = rightChild->findChild(parent, left, right, findLeft, findRight);
		}
	}
	bool findBrother(BinaryTree<Args...>& kid, BinaryTree<Args...>& brother)
	{
		BinaryTree<Args...> sameParent = *this;
		if (findParent(kid, sameParent))
		{
			if (sameParent.leftChild != nullptr && !memcmp(sameParent.leftChild->data, kid.data, size))
			{
				brother = *sameParent.rightChild;
			}
			else if (sameParent.rightChild != nullptr && !memcmp(sameParent.rightChild->data, kid.data, size))
			{
				brother = *sameParent.leftChild;
			}
			else
			{
				return false;
			}
			return true;
		}
		else
		{
			return false;
		}
	}
};