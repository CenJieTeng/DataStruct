#include "LinkList.h"

using std::cout; using std::cin; using std::endl;
using namespace cjt;

LinkList::LinkList(LinkList::LinkListType t) : head(nullptr), type(t)
{
	head = new ListNode; //创建头结点
	head->next = nullptr;

	//如果是循环链表，把最后一个节点的next指向头结点
	if (type == CIRCULAR)
		head->next = head;
}

LinkList::~LinkList()
{
	Clear();
}

//创建链表(带头结点尾插法)
void LinkList::CreateLiskList()
{
	ListNode *p, *r;
	r = head;

	cout << "请输入数据，用空格分隔，9999结束输入" << endl;
	DataType d;
	cin >> d;

	while (d != 9999)
	{
		p = new ListNode;
		p->data = d;

		r->next = p;
		r = p;
		r->next = nullptr;

		cin >> d;
	}

	//如果是循环链表，把最后一个节点的next指向头结点
	if (type == CIRCULAR)
		r->next = head;
}

//清除链表
void LinkList::Clear()
{
	ListNode *r = head->next;

	ListNode *k = nullptr;
	if (type == CIRCULAR)
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

//插入元素
void LinkList::insert(int i, DataType x)
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
		auto p = new ListNode;
		p->data = x;

		p->next = r->next;
		r->next = p;
	}
}

//删除元素(这里指的是删除给定某个数据x的节点，而不是某位置的元素)
void LinkList::erase(DataType x)
{
	auto q = head;
	auto p = q->next;

	ListNode *k = nullptr;
	if (type == CIRCULAR)
		k = head;

	while (p != k)
	{
		if (p->data == x)
		{
			q->next = p->next; //删除元素
			delete p;          //释放元素所占用的空间
			break;
		}
		q = q->next;
		p = p->next;
	}
}

//查找元素返回结点
ListNode* LinkList::find(DataType x) const
{
	auto p = head->next;

	ListNode *k = nullptr;
	if (type == CIRCULAR)
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
void LinkList::display() const
{
	auto p = head->next;

	ListNode *k = nullptr;
	if (type == CIRCULAR)
		k = head;

	cout << "head ---> ";
	while (p != k)
	{
		cout << p->data << " ---> ";
		p = p->next;
	}

	if (type == CIRCULAR)
		cout << "head" << endl;
	else
		cout << "NULL" << endl;
}

//循环链表找前驱结点
ListNode* LinkList::prior(ListNode *n) const
{
	//必须是循环链表
	if (type != CIRCULAR)
		return nullptr;

	auto p = n->next;

	while (p->next != n)
		p = p->next;

	return p;
}
