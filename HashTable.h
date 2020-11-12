//项目：哈希表 (链地址法)
//创建时间：2019/1/5
//完成时间：2019/1/5
//最后一次修改时间：2020/11/9
//修改次数：
//修改原因: 
//改成模板类
//根据填充因子，自动增长
//
//作者：CenJieTeng
//QQ: 2271369683
#pragma once
#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <cmath>
#include <iostream>
#include <memory>
#include <functional>

template<typename KEY, typename VALUE>
struct HashNode
{
	HashNode() : link_(nullptr) {}

	KEY key_;
	std::shared_ptr<VALUE> data_ptr_;
	HashNode<KEY, VALUE> *link_;
};

template<typename KEY, typename VALUE>
class HashTable
{
public:
	typedef HashNode<KEY, VALUE> ValueType;
	typedef ValueType** TableType;

public:
	class Iterator
	{
	public:
		Iterator(HashTable<KEY, VALUE> *hash_table, ValueType **ptr, int index = 0)
		: hash_table_(hash_table), ptr_(ptr), index_(index) 
		{
			if (index_ < hash_table->bucket_count())
			{
				ptr_ = new ValueType*;
				(*ptr_) = new ValueType;
				(*ptr_)->key_ = (*ptr)->key_;
				(*ptr_)->data_ptr_ = (*ptr)->data_ptr_;
				(*ptr_)->link_ = (*ptr)->link_;
			}
		}

		~Iterator()
		{
			if (ptr_ && hash_table_ && index_ < hash_table_->bucket_count())
			{
				if (*ptr_)
				{
					delete (*ptr_);
				}
				delete ptr_;
			}
		}

		Iterator (const Iterator &other)
		: Iterator(other.hash_table_, other.ptr_, other.index_) {}

		Iterator& operator++()
		{
			if (*ptr_ && (*ptr_)->link_ != nullptr)
				*ptr_ = (*ptr_)->link_;
			else 
			{
				while (index_ < hash_table_->bucket_count())
				{
					++index_;
					ptr_ = hash_table_->table_+index_;
					if (index_ < hash_table_->bucket_count() && *ptr_ != nullptr)
						break;
				}
			}

			return *this;
		}

		const Iterator& operator++() const
		{
			return (Iterator(*this)).operator++();
		}

		VALUE& operator*()
		{
			return *(*ptr_)->data_ptr_;
		}

		VALUE& operator->()
		{
			return *(*ptr_)->data_ptr_;
		}

		const VALUE& operator*() const
		{
			return *(*ptr_)->data_ptr_;
		}

		const VALUE& operator->() const
		{
			return *(*ptr_)->data_ptr_;
		}

		bool operator==(const Iterator &other) const
		{
			return *(this->ptr_) == *(other.ptr_);
		}

		bool operator!=(const Iterator &other) const
		{
			return *(this->ptr_) != *(other.ptr_);
		}

	private:
		HashTable<KEY, VALUE> *hash_table_;
		mutable ValueType **ptr_;
		mutable int index_;
	};

public:
	HashTable(int bucket_size = 10, double factor = 0.75f);
	~HashTable();

public:
	int bucket_count() const;
	int size() const;
	double load_factor() const;
	double max_load_factor() const;
	bool Insert(KEY key, const VALUE &value); //插入元素
	void Rehash(); //增大表
	void ShowTable(bool not_nul = false) const; //打印哈希表
	Iterator Find(KEY key);
	//bool Find(KEY key); //查找key是否保存元素
	bool Find(KEY key, VALUE &value); //查找元素
	bool Erase(KEY key); //删除元素
	bool Erase(KEY key, VALUE &value); //删除元素
	void Clear(); //清除表

	int BucketSize(int index); //返回指定桶的元素个数

	Iterator begin();
	Iterator end();
	const Iterator cbegin() const;
	const Iterator cend() const;

private:
	int Hash(KEY key); //哈希函数
	int get_new_hash_table_size(); //寻找大于2*bucket_count的第一个素数
	int key_offset(KEY key);

private:
	TableType table_;
	int bucket_count_; //桶数量
	int size_; //元素数量
	double factor_; //装填因子
};

using std::cin; using std::cout; using std::endl;

template<typename KEY, typename VALUE>
HashTable<KEY, VALUE>::HashTable(int bucket_size, double factor) 
: bucket_count_(bucket_size), size_(0), factor_(factor)
{
	Rehash();
}

template<typename KEY, typename VALUE>
HashTable<KEY, VALUE>::~HashTable()
{
	Clear();
}

template<typename KEY, typename VALUE>
int HashTable<KEY, VALUE>::bucket_count() const
{
	return bucket_count_;
}

template<typename KEY, typename VALUE>
int HashTable<KEY, VALUE>::size() const
{
	return size_;
}

template<typename KEY, typename VALUE>
double HashTable<KEY, VALUE>::load_factor() const
{
	return (double)size_ / bucket_count_;
}

template<typename KEY, typename VALUE>
double HashTable<KEY, VALUE>::max_load_factor() const
{
	return factor_;
}

//插入元素
template<typename KEY, typename VALUE>
bool HashTable<KEY, VALUE>::Insert(KEY key, const VALUE &value)
{
	if (Find(key) != end())
		return false;

	int index = Hash(key);
	ValueType *p = new HashNode<KEY, VALUE>();
	p->key_ = key;
	p->data_ptr_ = std::shared_ptr<VALUE>(new VALUE(value));

	p->link_ = table_[index];
	table_[index] = p;
	++size_;

	if (load_factor() > max_load_factor())
		Rehash();

	return true;
}

//增大表
template<typename KEY, typename VALUE>
void HashTable<KEY, VALUE>::Rehash()
{
	int old_bucket_count_ = bucket_count_;
	int new_bucket_count = get_new_hash_table_size();
	if (new_bucket_count < bucket_count_)
		return;
	bucket_count_ = new_bucket_count;

	TableType newTable_ = new ValueType*[new_bucket_count];
	for (int i = 0; i < new_bucket_count; ++i)
		newTable_[i] = nullptr;

	if (size_ > 0)
	{
		for (int i = 0; i < old_bucket_count_; ++i)
		{
			ValueType* p = table_[i];
			while (p)
			{
				ValueType* q = p->link_;
				int index = Hash(p->key_);
				p->link_ = newTable_[index];
				newTable_[index] = p;
				p = q;
			}
		}
		delete[] table_;
	}
	table_ = newTable_;
}

//打印哈希表
template<typename KEY, typename VALUE>
void HashTable<KEY, VALUE>::ShowTable(bool not_nul) const
{
	cout << "Table bucket_count = " << bucket_count_ << endl;
	cout << "Table size = " << size_ << endl;
	for (int i = 0; i < bucket_count_; ++i)
	{
		ValueType *p = table_[i];
		if (p == nullptr && not_nul == true)
			continue;
		cout << i << " : ";
		while (p)
		{
			cout << "<" << p->key_ << "," << *(p->data_ptr_) << ">" << " --> ";
			p = p->link_;
		}
		
		cout << "Nul." << endl;
	}
}

// template<typename KEY, typename VALUE>
// bool HashTable<KEY, VALUE>::Find(KEY key)
// {
// 	int index = Hash(key);
// 	ValueType *p = table_[index];
// 	while (p)
// 	{
// 		if (p->key_ == key)
// 			return true;
// 		p = p->link_;
// 	}

// 	return false;
// }

template<typename KEY, typename VALUE>
typename HashTable<KEY, VALUE>::Iterator HashTable<KEY, VALUE>::Find(KEY key)
{
	int index = Hash(key);
	ValueType *p = table_[index];
	int offset = 0;
	while (p)
	{
		if (p->key_ == key)
			return Iterator(this, &p, key_offset(key));
		p = p->link_;
		++offset;
	}

	return end();
}

//查找元素
template<typename KEY, typename VALUE>
bool HashTable<KEY, VALUE>::Find(KEY key, VALUE &value)
{
	int index = Hash(key);
	ValueType* p = table_[index];

	while (p != nullptr && p->key_ != key)
		p = p->link_;
	
	if (p == nullptr)
		return false;

	value = *(p->data_ptr_);
	return true;
}

//删除元素
template<typename KEY, typename VALUE>
bool HashTable<KEY, VALUE>::Erase(KEY key)
{
	int index = Hash(key);
	ValueType* p = table_[index];

	if (p && p->key_ == key)
	{
		table_[index] = p->link_;
		delete p;
		--size_;
		return true;
	}

	ValueType* q = p;
	while (p && p->key_ != key)
	{
		q = p;
		p = p->link_;
	}

	if (p == nullptr)
		return false;

	q->link_ = p->link_;
	delete p;
	--size_;
	return true;
}

//删除元素
template<typename KEY, typename VALUE>
bool HashTable<KEY, VALUE>::Erase(KEY key, VALUE &value)
{
	return Find(key, value) && Erase(key);
}

//清除表
template<typename KEY, typename VALUE>
void HashTable<KEY, VALUE>::Clear()
{
	for (int i = 0; i < bucket_count_; ++i)
	{
		ValueType* p = table_[i], *q = nullptr;
		table_[i] = nullptr;
		while (p)
		{
			q = p;
			p = p->link_;
			delete(q);
		}
	}
	delete[] table_;
	size_ = 0;
}

//返回特定桶元素个数
template<typename KEY, typename VALUE>
int HashTable<KEY, VALUE>::BucketSize(int index)
{
	if (0 <= index && index < bucket_count_)
	{
		ValueType *p = table_[index];
		int ret = 0;
		while (p)
		{
			p = p->link_;
			++ret;
		}
		return ret;
	}
	return 0;
}

//begin()
template<typename KEY, typename VALUE>
typename HashTable<KEY, VALUE>::Iterator HashTable<KEY, VALUE>::begin()
{
	int index = 0;
	for (int i = 0; i < bucket_count_; ++i)
	{
		if (table_[index] != nullptr)
		{
			break;
		}
		++index;
	}
	return Iterator(this, table_ + index, index);
}

//end()
template<typename KEY, typename VALUE>
typename HashTable<KEY, VALUE>::Iterator HashTable<KEY, VALUE>::end()
{
	return Iterator(this, table_ + bucket_count_, bucket_count_);
}

//cbegin()
template<typename KEY, typename VALUE>
const typename HashTable<KEY, VALUE>::Iterator HashTable<KEY, VALUE>::cbegin() const
{
	return ((HashTable<KEY, VALUE>*)(this))->begin();
}

//cend()
template<typename KEY, typename VALUE>
const typename HashTable<KEY, VALUE>::Iterator HashTable<KEY, VALUE>::cend() const
{
	return ((HashTable<KEY, VALUE>*)(this))->end();
}

//哈希函数
template<typename KEY, typename VALUE>
int HashTable<KEY, VALUE>::Hash(KEY key)
{
	return std::hash<KEY>{}(key) % bucket_count_;
}

 //寻找大于2*bucket_count的第一个素数
 template<typename KEY, typename VALUE>
 int HashTable<KEY, VALUE>::get_new_hash_table_size()
 {
	int new_bucket_count = bucket_count_ * 2 + 1, i, j;
	while(1)
	{
		j = sqrt(new_bucket_count);
		for (i = 2; i <= j; ++i)
		{
			if (new_bucket_count % i == 0)
				break;
		}

		if (i > j)
			return new_bucket_count;
		++new_bucket_count;
	}

	return 0;
}

//根据key计算index 当前桶下标 + 当前元素在桶中偏移量
template<typename KEY, typename VALUE>
int HashTable<KEY, VALUE>::key_offset(KEY key)
{
	int bucket_index = Hash(key);
	int offset = 0;
	ValueType *p = table_[bucket_index];
	while (p)
	{
		if (p->key_ == key)
			break;
		p = p->link_;
		++offset;
	}

	return bucket_index + offset;
}


#endif // !HASHTABLE_H
