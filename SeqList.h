//项目：顺序表
//创建时间：2018/7/12 15:00
//完成时间：2018/7/12 16:27
//最后一次修改时间：2018/12/22
//修改次数：3
//修改原因：
//添加begin，end函数
//改为动态开辟内存
//改为模板类
//
//
//作者：CenJieTeng
//QQ: 2271369683
#pragma once
#ifndef SEQLIST_H
#define SEQLIST_H
#include <iostream>
#include <stdexcept>
#define LIST_INIT_SIZE 10
#define LIST_GROW_SIZE 10

namespace cjt
{
	template <typename T>
	class SeqList
	{
		template <typename _Titer, typename _Tkey>
		friend int Search_Seq(_Titer begin, _Titer end, _Tkey key);
	public:
		using DataType = T;

	public:
		SeqList();
		SeqList(int n);                 //构造n个元素，元素采用默认构造
		SeqList(DataType *, int);       //传入数组初始化顺序表
		~SeqList();

		SeqList(const SeqList<T>&);     //拷贝构造函数

	//运算符重载
	public:
		DataType& operator[](int index)const {
			if (index < 0 || index > length)
				throw std::out_of_range("访问超出范围!");

			return data[index];
		}

	public:
		void InitSeqList();                    //初始化顺序表
		void CreateSeqList();                  //创建顺序表
		void ClearSeqList();                   //清除顺序表
		bool empty() const { return length == 0; };  //判断表是否为空
		int size() const { return length; };         //返回当前表长
		int capacity_() const { return capacity; }; //返回容量
		void insert(int, DataType);            //插入元素
		void erase(int);                       //删除元素
		int find(DataType);                    //查找元素，成功返回位置，失败返回0
		DataType find_n(int);                  //查找元素，成功返回元素，否则抛出异常
		DataType* begin();                     //返回首迭代器
		DataType* end();                       //返回尾后迭代器 
		const DataType* begin() const;         //返回首迭代器
		const DataType* end() const;           //返回尾后迭代器
		const DataType* cbegin() const;        //返回const首迭代器
		const DataType* cend() const;          //返回const尾后迭代器
		//DataType* rbegin();                    //返回首的 反向迭代器
		//DataType* rend();                      //返回尾的 反向后迭代器

	private:
		void check_listsize();                 //检查内存是否足够

	protected:
		DataType *data;

	private:
		int length;                     //当前表长度
		int capacity;                   //表内存空间
	};

#endif // SEQLIST

	//-------------------------------------华丽的分割线-------------------------------------------------

	using std::cout; using std::cin; using std::endl;

	template <typename T>
	SeqList<T>::SeqList() : data(nullptr)
	{
		InitSeqList();
	}

	//构造n个元素，元素采用默认构造
	template <typename T>
	SeqList<T>::SeqList(int n){
		InitSeqList();

		//分配足够的空间存放数组
		if (n > capacity)
		{
			int resize = ((n - capacity) / LIST_GROW_SIZE + 1) * LIST_GROW_SIZE;
			data = (DataType*)realloc(data, (capacity + resize) * sizeof(DataType));
			capacity += resize;
		}

		//for (int i = 1; i <= n; ++i)
			//data[i] = DataType();

		length = n;
	}

	template <typename T>
	SeqList<T>::SeqList(DataType *d, int n)
	{
		InitSeqList();

		//分配足够的空间存放数组
		if (n > capacity)
		{
			int resize = ((n - capacity) / LIST_GROW_SIZE + 1) * LIST_GROW_SIZE;
			data = (DataType*)realloc(data, (capacity + resize) * sizeof(DataType));
			capacity += resize;
		}

		for (int i = 1; i <= n; ++i)
			data[i] = *d++;

		length = n;
	}

	template <typename T>
	SeqList<T>::~SeqList()
	{
		ClearSeqList(); //清除顺序表
	}

	//拷贝构造函数
	template <typename T>
	SeqList<T>::SeqList(const SeqList<T> &list)
	{
		//data = (DataType*)malloc(list.capacity * sizeof(DataType)); //分配和list相同大小的内存空间
		data = new DataType[list.capacity];

		for (int i = 1; i <= list.length; ++i)
			data[i] = list.data[i]; //从list拷贝数据

		length = list.length;       //初始化length
		capacity = list.capacity;   //初始化listsize
	}

	//初始化顺序表
	template <typename T>
	void SeqList<T>::InitSeqList()
	{
		//data = (DataType*)malloc((LIST_INIT_SIZE + 1) * sizeof(DataType)); //0下标，不存放数据
		data = new DataType[LIST_INIT_SIZE + 1];
		length = 0;
		capacity = LIST_INIT_SIZE; //初始存储大小
	}

	//创建顺序表
	template <typename T>
	void SeqList<T>::CreateSeqList()
	{
		cout << "请输入数据，用空格分隔，9999结束输入" << endl;
		int n = 1;
		DataType d = 0;
		cin >> d;
		while (d != 9999)
		{
			//如果没有存储空间，分配空间
			check_listsize();

			data[n] = d;
			++n;
			++length;

			cin >> d;
		}
	}

	//销毁顺序表
	template <typename T>
	void SeqList<T>::ClearSeqList()
	{
		//free(data);
		delete[] data;
		data = nullptr;
	}

	//插入元素
	template <typename T>
	void SeqList<T>::insert(int i, DataType x)
	{
		//判断插入位置是否合法
		if (i < 1 || i > length + 1)
			return;

		//检查内存是否足够
		check_listsize();

		//移动元素
		for (int j = length; j >= i; --j)
			data[j] = data[j - 1];

		//插入元素
		data[i] = x;

		//改变length
		++length;
	}

	//删除元素
	template <typename T>
	void SeqList<T>::erase(int i)
	{
		//判断是否非空
		if (empty())
			return;

		//判断删除位置是否合法
		if (i < 1 || i > length)
			return;

		//移动元素(这部也完成了删除元素的工作)
		for (int j = i; j <= length; ++j)
			data[j - 1] = data[j];

		//改变length
		--length;
	}

	//查找元素，成功返回位置，失败返回0
	template <typename T>
	int SeqList<T>::find(DataType d)
	{
		for (int i = 1; i < length; ++i)
			if (data[i] == d)
				return i;

		return 0;
	}

	//查找元素，成功返回元素，否则抛出异常
	template <typename T>
	typename SeqList<T>::DataType SeqList<T>::find_n(int i)
	{
		if (i < 0 || i > length - 1)
			throw std::out_of_range("访问超出范围!");

		return data[i+1];
	}

	//返回首迭代器
	template <typename T>
	typename SeqList<T>::DataType* SeqList<T>::begin()
	{
		return data + 1;
	}

	//返回尾后迭代器
	template <typename T>
	typename SeqList<T>::DataType* SeqList<T>::end()
	{
		return begin() + length;
	}

	//返回首迭代器
	template <typename T>
	const typename SeqList<T>::DataType* SeqList<T>::begin() const
	{
		return data + 1;
	}

	//返回尾后迭代器
	template <typename T>
	const typename SeqList<T>::DataType* SeqList<T>::end() const
	{
		return begin() + length;
	}

	//返回const首迭代器
	template <typename T>
	const typename SeqList<T>::DataType* SeqList<T>::cbegin() const
	{
		return data + 1;
	}

	//返回const尾后迭代器
	template <typename T>
	const typename SeqList<T>::DataType* SeqList<T>::cend() const
	{
		return cbegin() + length;
	}

	//检查内存是否足够
	template <typename T>
	void SeqList<T>::check_listsize()
	{
		if (length >= capacity)
		{
			data = (DataType*)realloc(data, (capacity + LIST_GROW_SIZE) * sizeof(DataType));
			capacity += LIST_GROW_SIZE;
		}
	}
}
