//项目：静态链表
//创建时间：2019/1/7 13:30
//完成时间：2017/1/7 23:46
//最后一次修改时间：
//修改次数：
//修改原因：
//改为模板类
//
//
//作者：CenJieTeng
//QQ: 2271369683
#pragma once
#ifndef SLINKLIST_H
#define SLINKLIST_H
#include <iostream>
#include <vector>
#include "SeqList.h"
#define MAXSIZE 100
#define NULL_NEXT -1;

namespace cjt
{
	template <typename T>
	class SLinkList
	{
		//--友元区
		template <typename _Type>
		friend void RadixSort(SeqList<_Type> &list);

	public:
		using DataType = T;
		struct SListNode
		{
			DataType data;
			int next;
		};

	public:
		SLinkList();
		~SLinkList();

	public:
		SListNode & operator[](int index) {
			if (index < 0 || index > length)
				throw std::out_of_range("访问超出范围");

			return list[index];
		}

	public:
		void CreateSLiskList();           //创建静态链表(带头结点的尾插法)
		int size() const { return length; };  //返回当前表长
		void insert(int pos, DataType x); //插入元素
		void erase(DataType x);           //删除元素(这里指的是删除给定某个数据x的节点，而不是某位置的元素)
		SListNode* find(DataType x);      //查找元素返回结点
		void Arrange();                   //调整静态链表，使得元素按关键字非递减排序
		void display();                   //输出链表

	private:
		int Malloc();                     //返回第一个可以用空间下标，如果没有空间返回-1

	private:
		SListNode list[MAXSIZE];
		int length;
		std::vector<int> vec; //保存可以存放数据空间的下标
	};

//---------------------------------------华丽的分割线-------------------------------------------------

	using std::cin; using std::cout; using std::endl;

	template<typename T>
	SLinkList<T>::SLinkList() : length(0)
	{
		list[0].next = NULL_NEXT;
		vec.resize(MAXSIZE - 1);
		for (int i = 0; i < MAXSIZE - 1; ++i)
			vec[i] = MAXSIZE - 1 - i;
	}


	template<typename T>
	SLinkList<T>::~SLinkList()
	{
	}


	//创建静态链表
	template <typename T>
	void SLinkList<T>::CreateSLiskList()
	{
		cout << "输入元素的个数: ";
		int n;
		cin >> n;

		DataType d;
		for (int i = 1; i <= n; ++i)
		{
			cout << "请输入第" << i << "个元素的值" << endl;
			cin >> d;
			list[i].data = d;
			list[i].next = NULL_NEXT;

			if (i != 0)
				list[i - 1].next = i;
		}

		//可用空间调整
		vec.erase(vec.end() - n, vec.end());

		length = n;
	}

	//插入元素
	template<typename T>
	void SLinkList<T>::insert(int pos, DataType x)
	{
		//插入位置不合法
		if (pos < 1 || pos > length + 1)
			return;

		//分配空间
		int L = Malloc();
		if (L == -1)
			return;

		list[L].data = x;

		int cur = 0;
		for (int i = 1; i < pos; ++i)
			cur = list[cur].next;

		list[L].next = list[cur].next;
		list[cur].next = L;
		++length;
	}

	//删除元素(这里指的是删除给定某个数据x的节点，而不是某位置的元素)
	template <typename T>
	void SLinkList<T>::erase(DataType x)
	{
		int cur = 0;
		for (int i = 0; i < length; ++i) {

			int nx = list[cur].next;
			if (list[nx].data == x) {
				//找到要删除的结点
				list[cur].next = list[nx].next;
				vec.push_back(nx); //相当于释放内存
				break;
			}
			cur = nx;
		}
		--length;
	}

	//查找元素返回结点
	template<typename T>
	typename SLinkList<T>::SListNode* SLinkList<T>::find(DataType x)
	{
		int cur = list[0].next;
		SListNode *p = nullptr;
		while (cur != -1)
		{
			if (list[cur].data == x) {
				//找到要查找的元素
				p = &list[cur];
				break;
			}
			cur = list[cur].next;
		}

		return p;
	}

	//调整静态链表，使得元素按关键字非递减排序
	template<typename T>
	void SLinkList<T>::Arrange()
	{
		int cur = list[0].next;
		for (int i = 1; i <= length; ++i)
		{
			while (cur < i) cur = list[cur].next;
			int nx = list[cur].next;

			if (cur != i)
			{
				SListNode tmp = list[i];
				list[i].data = list[cur].data;
				list[i].next = cur;
				list[cur] = tmp;
			}
			cur = nx;
		}
		list[0].next = 1;
	}

	//输出链表
	template<typename T>
	void SLinkList<T>::display()
	{
		int cur = 0;
		while (list[cur].next != -1)
		{
			cur = list[cur].next;
			cout << list[cur].data << " --> ";
		}
		cout << "Nul.";
	}



	//返回第一个可以用空间下标，如果没有空间返回-1
	template<typename T>
	int SLinkList<T>::Malloc()
	{
		if (vec.size() != 0)
		{
			int re = *(--vec.end());
			vec.erase(--vec.end());
			return re;
		}

		return -1;
	}
}

#endif // !SLINKLIST
