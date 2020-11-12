//项目：链表和循环链表
//创建时间：2018/7/14 16:25
//完成时间：2018/7/14 17:50
//最后一次修改时间：2018/7/16 15:16
//修改次数：3
//修改原因：
//增加循环链表及其相关操作
//修复小bug，增加析构函数针对循环链表的情况
//将头结点的创建放到构造函数，使空链表与非空链表操作一致
//
//作者：CenJieTeng
//QQ: 2271369683
#pragma once
#ifndef LINKLIST_H
#define LINKLIST_H
#include <iostream>
#include "SLinkList.h"
#include "SeqList.h"

namespace cjt 
{
	typedef int DataType;
	typedef struct  Node
	{
		DataType data;
		Node *next;
	}ListNode;

	class LinkList
	{
	public:
		enum LinkListType { SINGLE, CIRCULAR }; //0单链表，1循环链表
	public:
		LinkList(LinkList::LinkListType t = SINGLE);
		~LinkList();

		//运算符重载
	public:
		LinkList & operator=(const LinkList &list) {

			//防止自赋值
			if (this != &list) {

				//先析构自身的空间
				Clear();

				//创建头结点
				head = new ListNode;
				head->next = nullptr;

				//如果是循环链表，把最后一个节点的next指向头结点
				if (type == CIRCULAR)
					head->next = head;

				//从list拷贝数据
				ListNode *p = list.head;
				ListNode *q = head;
				while (p && p->next)
				{
					q->next = (ListNode*)malloc(sizeof(ListNode));
					q->data = p->data;
					q = q->next;
					p = p->next;
				}
			}

			return *this;
		}


	public:
		void CreateLiskList();            //创建链表(带头结点尾插法)
		void Clear();                     //清除链表
		void insert(int, DataType);       //插入元素
		void erase(DataType);             //删除元素(这里指的是删除给定某个数据x的节点，而不是某位置的元素)
		ListNode* find(DataType) const;   //查找元素返回结点
		void display() const;             //输出链表
		ListNode* prior(ListNode *) const;//循环链表找前驱结点

	private:
		ListNode * head;
		LinkListType type;
	};
}

#endif // !LINKLIST_H
