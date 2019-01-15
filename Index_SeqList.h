//项目：索引顺序表
//创建时间：2018/12/21 19:14
//完成时间：?
//最后一次修改时间：
//修改次数：
//修改原因：
//
//
//作者：CenJieTeng
//QQ: 2271369683
#pragma once
#ifndef INDEX_SEQLIST_H
#define INDEX_SRQLIST_H
#include <iostream>
#include "SeqList.h"
#include "Search.h"
#define TABLE_SIZE 10

typedef int DataType;

//索引结点
typedef struct TableNode
{
	DataType data;
	int index;
}Table[TABLE_SIZE];

template <typename T>
class Index_SeqList : 
	public cjt::SeqList<T>
{
	template <typename T,typename Tkey>
		friend int cjt::Search_IndexSeqList(T list, Tkey key);
public:
	Index_SeqList();
	~Index_SeqList();

public:
	void CreateIndexSeqList(); //创建索引顺序表&顺序表

private:
	Table table;		//表
	int lenght;			//表当前长度
};

#endif // !INDEX_SEQLIST_H

//-------------------------------------华丽的分割线-------------------------------------------------

using std::cout; using std::cin; using std::endl;

template <typename T>
Index_SeqList<T>::Index_SeqList() : lenght(0)
{
}

template <typename T>
Index_SeqList<T>::~Index_SeqList()
{
}

//创建索引顺序表
template <typename T>
void Index_SeqList<T>::CreateIndexSeqList()
{
	CreateSeqList(); //创建顺序表

					 //根据顺序表 创建 索引顺序表
	if (!empty()) {//顺序表非空
		int n = 0;
		cout << "请输入索引表的分块数, 建议是 " << (int)sqrt(size()) << endl;
		cin >> n;

		//限制n在一定范围内(1,2倍建议范围]
		if (n <= 1 || n > (int)sqrt(size())) {
			cout << "超出有效范围, 按照建议进行进行...." << endl;
			n = (int)sqrt(size());
		}

		//索引表第一个结点保存顺序表第一个元素
		table[0].data = find_n(1);
		table[0].index = 1;
		lenght = 1;

		cout << "请输入分块位置" << endl;
		int i;
		for (; n > 1; --n) {
			cin >> i;

			table[lenght].data = i;
			table[lenght].index = find(i);
			++lenght;
		}
	}

	//索引表最后一个结点保存顺序表最后一个个元素
	table[lenght].data = find_n(size());
	table[lenght].index = size();
	++lenght;
}
