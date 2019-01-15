//项目：哈希表
//创建时间：2019/1/5 ?
//完成时间：2019/1/5 ?
//最后一次修改时间：
//修改次数：
//修改原因：
//
//作者：CenJieTeng
//QQ: 2271369683
#pragma once
#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <iostream>
#define P 13 //表长度

typedef int DataType;
struct HashNode
{
	DataType data;
	HashNode *link;
};

class HashTable
{
public:
	HashTable();
	~HashTable();

public:
	bool Insert(DataType key); //插入元素
	void ShowTable() const;    //打印哈希表
	HashNode* Search(DataType key); //查找元素
	bool Erase(DataType key);  //删除元素
	void Clear();              //清除表

private:
	int Hash(DataType key); //哈希函数

private:
	HashNode* table[P];
};

#endif // !HASHTABLE_H
