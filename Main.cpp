#include"header/LinkList.h"
#include<iostream>
int main() {
	LinkNode<int, int> node;
	node.setValue(8, 3, 9);
	int arg1, arg2;
	char arg3;
	//system("pause");
	std::cout << '\n';
	LinkList<int, int, char> list;
	list.add(1, 2, 3, '5');
	//list.add(2, 6, 8, '9');
	//list.add(4, 6, 8, '4');
	list.add(2, 5, '0');
	std::cout << "链表长度为：" << list.getLength() << '\n';
	std::cout << "元素大小为：" << list.getElementSize() << '\n';
	list.get(1, arg1, arg2, arg3);
	LinkList<int, int, char> list2 = list;
	list2.remove(2, arg1, arg2, arg3);
	std::cout << "链表长度为：" << list2.getLength() << '\n';
	std::cout << "元素大小为：" << list2.getElementSize() << '\n';
	list2.get(arg1, arg2, arg3);
	std::cout << arg1 << arg2 << arg3 << '\n';
}