//项目：双链表和双循环链表
//创建时间：2018/7/16 14:16
//完成时间：2018/7/16 18:45
//最后一次修改时间：
//修改次数：
//修改原因：
//
//
//作者：CenJieTeng
//QQ: 2271369683
#pragma once
#ifndef DLINKLIST_H
#define DLINKLIST_H
#include <iostream>
#include "SLinkList.h"

namespace cjt
{
	typedef int DataType;
	struct  DListNode
	{
		DataType data;
		DListNode *prior, *next;
	};

	class DLinkList
	{
		//--友元区
		template <typename _Type>
		friend void Collect(SLinkList<_Type> &list, int n, SeqList<DLinkList> &flist);
	public:
		enum DLinkListType { DSINGLE, DCIRCULAR }; //0双链表，1双循环链表
	public:
		DLinkList(DLinkListType t = DCIRCULAR);
		~DLinkList();

	public:
		void CreateDLiskList();           //创建双链表(带头结点尾插法)
		void insert(int, DataType);       //插入元素
		void erase(DataType);             //删除元素(这里指的是删除给定某个数据x的节点，而不是某位置的元素)
		DListNode* find(DataType);         //查找元素返回结点
		void display();                   //输出链表

	private:
		DListNode * head;
		DLinkListType type;
	};
}

#endif // !DLINKLIST_H
