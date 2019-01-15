#include "DLinkList.h"

using std::cout; using std::cin; using std::endl;
using namespace cjt;

DLinkList::DLinkList(DLinkList::DLinkListType t) : head(nullptr), type(t)
{
	head = new DListNode; //创建头结点
	head->next = nullptr;

	//如果是循环链表，把最后一个节点的next指向头结点,head的prior指向最后一个节点
	if (type == DCIRCULAR)
	{
		head->next = head;
		head->prior = head;
	}
}

DLinkList::~DLinkList()
{
	DListNode *r = head->next;
	DListNode *k = nullptr;
		if (type == DCIRCULAR)
			k = head;

	while (r != k)
	{
		auto temp = r->next;
		delete r;
		r = temp;
	}

	delete head;
	head = nullptr;
}

//创建双链表(带头结点尾插法)
void DLinkList::CreateDLiskList()
{
	DListNode *p, *r;
	r = head;

	cout << "请输入数据，用空格分隔，9999结束输入" << endl;
	DataType d;
	cin >> d;

	while (d != 9999)
	{
		p = new DListNode;
		p->data = d;

		p->prior = r;
		r->next = p;
		r = p;
		r->next = nullptr;

		cin >> d;
	}

	//如果是循环链表，把最后一个节点的next指向头结点
	if (type == DCIRCULAR)
	{
		r->next = head;
		head->prior = r;
	}
}

//插入元素
void DLinkList::insert(int i, DataType x)
{
	int n = 1;
	auto r = head;

	while (r->next && n < i)
	{
		r = r->next;
		++n;
	}

	if (n == i)
	{
		auto p = new DListNode;
		p->data = x;

		p->next = r->next;
		p->prior = r;
		r->next->prior = p;
		r->next = p;
	}
}

//删除元素(这里指的是删除给定某个数据x的节点，而不是某位置的元素)
void DLinkList::erase(DataType x)
{
	auto p = head->next;

	DListNode *k = nullptr;
	if (type == DCIRCULAR)
		k = head;

	while (p != k)
	{
		if (p->data == x)
		{
			p->prior->next = p->next;
			p->next->prior = p->prior;
			delete p;                   //释放元素所占用的空间
			break;
		}
		p = p->next;
	}
}

//查找元素返回结点
DListNode* DLinkList::find(DataType x)
{
	auto p = head->next;

	DListNode *k = nullptr;
	if (type == DCIRCULAR)
		k = head;

	while (p != k)
	{
		if (p->data == x)
			return p;

		p = p->next;
	}

	return nullptr;
}

//输出链表
void DLinkList::display()
{
	auto p = head->next;

	DListNode *k = nullptr;
	if (type == DCIRCULAR)
		k = head;

	cout << "head ---> ";
	while (p != k)
	{
		cout << p->data << " ---> ";
		p = p->next;
	}

	if (type == DCIRCULAR)
		cout << "head" << endl;
	else
		cout << "NULL" << endl;
}
