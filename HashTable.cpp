#include "HashTable.h"

using std::cin; using std::cout; using std::endl;

HashTable::HashTable()
{
	for (int i = 0; i < P; ++i)
		table[i] = nullptr;
}

HashTable::~HashTable()
{
	Clear();
}

//插入元素
bool HashTable::Insert(DataType key)
{
	int index = Hash(key);
	HashNode *p = (HashNode*)malloc(sizeof(HashNode));
	p->data = key;

	p->link = table[index];
	table[index] = p;

	return true;
}

//打印哈希表
void HashTable::ShowTable() const
{
	for (int i = 0; i < P; ++i)
	{
		cout << i << " : ";
		HashNode *p = table[i];
		while (p)
		{
			cout << p->data << " --> ";
			p = p->link;
		}
		cout << "Nul." << endl;
	}
}

//查找元素
HashNode* HashTable::Search(DataType key)
{
	int index = Hash(key);
	HashNode *p = table[index];

	while (p != nullptr && p->data != key)
		p = p->link;

	return p;
}

//删除元素
bool HashTable::Erase(DataType key)
{
	HashNode *p = Search(key);
	if (p == nullptr)
		return false;

	int index = Hash(key);
	HashNode *q = table[index];
	if (q == p)
	{
		table[index] = p->link;
		free(p);
		return true;
	}

	while (q->link != p)
		q = q->link;
	q->link = p->link;
	free(p);
	return true;
}

//清除表
void HashTable::Clear()
{
	for (int i = 0; i < P; ++i)
	{
		HashNode *p = table[i], *q = nullptr;
		table[i] = nullptr;
		while (p)
		{
			q = p;
			p = p->link;
			free(q);
		}
	}
}

//哈希函数
int HashTable::Hash(DataType key)
{
	return key % P;
}
