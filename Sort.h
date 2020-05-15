//项目：排序相关的算法
//创建时间：2019/1/6  20:45
//完成时间：2019/1/15 14:46
//最后一次修改时间：
//修改次数：
//修改原因：
//
//作者：CenJieTeng
//QQ: 2271369683
#pragma once
#ifndef SORT_H
#define SORT_H
#include <iostream>
#include <limits>
#include "SeqList.h"
#include "SLinkList.h"
#include "BiTree.h"
#include "SeqBiTree.h"
#include "LinkList.h"
#include "DLinkList.h"
#define EQ(a,b) ((a)==(b))
#define LT(a,b) ((a)<(b))    //!LT  等价于 a >= b
#define LQ(a,b) ((a)<=(b))   //!LQ  等价于 a > b

namespace cjt
{
//--------------------------------------------插入排序------------------------------------------------

	//--直接插入排序
	//时间复杂度O(n^2)
	template<typename _Type>
	void InsertSort(SeqList<_Type> &list) {

		for (int i = 2; i <= list.size(); ++i) {
			if (LT(list[i], list[i - 1])) {
				list[0] = list[i]; //list[i]保存哨兵位置

				//元素向后移动，让出空间
				list[i] = list[i - 1];
				int j;
				for (j = i - 1; LT(list[0], list[j]); --j)
					list[j+1] = list[j];
				list[j + 1] = list[0];
			}
		}
	}


	//--折半插入排序
	//时间复杂度O(n^2)
	template<typename _Type>
	void BInsertSort(SeqList<_Type> &list) {

		for (int i = 2; i <= list.size(); ++i) {
			list[0] = list[i]; //list[i]保存哨兵位置

			//由于前面已经排序好是一个 有序表，可以用折半查找
			int low = 1, high = i - 1, m;
			while (low <= high) {
				m = (low + high) / 2;
				if (LT(list[0], list[m])) high = m - 1;
				else
					low = m + 1;
			}

			//元素向后移动，让出空间
			int j;
			for (j = i-1; j >= high + 1; --j)
				list[j + 1] = list[j];
			list[high + 1] = list[0];
		}
	}


	//--2-路插入排序
	template<typename _Type>
	void TwoInsertSort(SeqList<_Type> &list) {

		//元素数量少于2，无需排序
		if (list.size() < 2)
			return;

		//辅助空间
		_Type *tmp = new _Type[list.size()]();
		tmp[0] = list[1]; //把tmp当做一个循环向量
		int First = 0, Final = 0;

		for (int i = 2; i <= list.size(); ++i) {

			if (LT(tmp[Final], list[i])) {
				//比最大值大，在Final后插入
				tmp[++Final] = list[i];
			}
			else if (LT(list[i], tmp[First])) {
				//比最小值小，在First前插入
				First = (First - 1 + list.size()) % list.size();
				tmp[First] = list[i];
			}
			else {
				//在中间插入

				if (LT(tmp[0], list[i])) {
					//在前半部分插入
					int j = Final++;
					while (LT(list[i], tmp[j])){
						tmp[j + 1] = tmp[j];
						j--;
					}
					tmp[j + 1] = list[i];
				}
				else {
					//在后半部分插入
					int j = First--;
					while (LT(tmp[j], list[i])){
						tmp[j - 1] = tmp[j];
						j++;
					}
					tmp[j - 1] = list[i];
				}
			}
		}

		//把tmp的数据输入到原来的数组中
		for (int k = 1; k <= list.size(); ++k)
			list[k] = tmp[(First++) % list.size()];

		//释放辅助空间地址
		delete[] tmp;
		tmp = nullptr;
	}


	//--表插入排序
	//参数说明：静态链表
	//时间复杂度：O(n^2)
	template<typename  _Type>
	void TableInsertSort(SLinkList<_Type> &list)
	{
		//元素数量少于2，无需排序
		if (list.size() < 2)
			return;

		list[0].next = 1;
		list[1].next = -1;
		
		for (int i = 2; i <= list.size(); ++i) {

			int cur = 0;
			int nx = list[0].next;
			while (LT(list[nx].data, list[i].data))
			{
				cur = nx;
				nx = list[nx].next;
			}

			list[i].next = list[cur].next;
			list[cur].next = i;
		}			
	}

	//希尔排序<接口>
	template<typename _Type>
	void ShellSort(SeqList<_Type> &list, int dlta[], int t)
	{
		for (int i = 0; i < t; ++i){
			ShellInsert(list, dlta[i]);
			for (int i = 1; i <= list.size(); ++i)
			{
				cout << list[i] << " ";
			}
			cout << endl;
		}
	}

	//希尔排序<实现>
	template<typename _Type>
	void ShellInsert(SeqList<_Type> &list, int dk)
	{
		for (int i = dk+1; i <= list.size(); ++i) {
			if (LT(list[i], list[i - dk])) {
				list[0] = list[i];

				//元素向后移动，让出空间
				//list[i] = list[i - 1];
				int j;
				for (j = i - dk; j > 0 && LT(list[0], list[j]); j-=dk)
					list[j + dk] = list[j];
				list[j + dk] = list[0];
			}
		}
	}

//------------------------------------------“交换”排序------------------------------------------------

	//冒泡排序
	//时间复杂度：O(n^2)
	template<typename _Type>
	void BubbleSort(SeqList<_Type> &list)
	{
		for (int i = 1; i <= list.size(); ++i)
		{
			for (int j = i + 1; j <= list.size(); ++j)
			{
				if (LT(list[j], list[i]))
				{
					auto tmp = list[i];
					list[i] = list[j];
					list[j] = tmp;
				}
			}
		}
	}

	//--快速排序<接口>
	//时间复杂度：O(nlogn)
	template<typename _Type>
	void QuickSort(SeqList<_Type> &list)
	{
		int low = 1, high = list.size();
		QuickSort(list, low, high);
	}

	//--快速排序<实现1>
	template<typename _Type>
	void QuickSort(SeqList<_Type> &list,int low, int high)
	{
		if (low < high)
		{
			int pivot = Partition(list, low, high);

			QuickSort(list, low, pivot - 1);
			QuickSort(list, pivot + 1, high);
		}
	}

	//--快速排序<实现2>
	template<typename _Type>
	int Partition(SeqList<_Type> &list, int low, int high)
	{
		list[0] = list[low];  //保存轴位置元素
		int pivot = list[low];
		while (low < high)
		{
			while (low < high && list[high] >= pivot)high--;
			list[low] = list[high];

			while (low < high && list[low] <= pivot) low++;
			list[high] = list[low];
		}
		list[low] = list[0];  //还原轴位置元素

		return low;
	}


	//--简单选择排序
	//时间复杂度：O(n^2)
	template <typename _Type>
	void SimpleSelectSort(SeqList<_Type> &list)
	{
		
		for (int i = 1; i <= list.size(); ++i)
		{
			auto min = i;
			for (int j = i + 1; j <= list.size(); ++j) {
				if (LT(list[j], list[min]))
					min = j;
			}
				

			auto tmp = list[i];
			list[i] = list[min];
			list[min] = tmp;
		}
	}

	//--首次树形选择排序
	template <typename _Type>
	void FirstTreeSelectSort(SeqBiTree<_Type> &T)
	{
		int p = T.GetNodeNumber() / 2 - 1;  //指向最后一个内部节点
		int left, right;                    //p结点左、右孩子的下标
		_Type leftValue, rightValue;        //左、右孩子的值

		while (p >= 0){
			left = p * 2 + 1;
			right = left + 1;

			leftValue  = GetValue(T, p, left);  //获取左孩子的值
			rightValue = GetValue(T, p, right); //获取右孩子的值

			
			if (LT(leftValue, rightValue)){
				//左孩子的值 < 右孩子的值

				if ((2 * left + 1) >= T.GetNodeNumber()) {
					//p的孩子是叶子结点
					T.GetNode(p)->data = left;
				}
				else{
					//p的孩子不是叶子结点
					T.GetNode(p)->data = T.GetNode(left)->data;
				}
			}
			else {
				//左孩子的值 > 右孩子的值

				if ((2 * left + 1) >= T.GetNodeNumber()) {
					//p的孩子是叶子结点
					T.GetNode(p)->data = right;
				}
				else{
					//p的孩子不是叶子结点
					T.GetNode(p)->data = T.GetNode(right)->data;
				}
			}

			--p;
		}
	}

	//--树形排序
	template <typename _Type>
	void TreeSelectSort(SeqBiTree<_Type> &T)
	{
		int index = T.GetNode(0)->data;  //获取上次排序结果结点所在下标
		int p = (int)ceil(index / 2.0 - 1);  //父节点，初始为上次结果的父节点，用于回溯

		int left, right;
		_Type leftValue, rightValue;
		while (p >= 0)
		{
			left = p * 2 + 1;
			right = left + 1;

			leftValue = GetValue(T, p, left);  //获取左孩子的值
			rightValue = GetValue(T, p, right); //获取右孩子的值


			if (LT(leftValue, rightValue)) {
				//左孩子的值 < 右孩子的值

				if ((2 * left + 1) >= T.GetNodeNumber()) {
					//p的孩子是叶子结点
					T.GetNode(p)->data = left;
				}
				else {
					//p的孩子不是叶子结点
					T.GetNode(p)->data = T.GetNode(left)->data;
				}
			}
			else {
				//左孩子的值 > 右孩子的值

				if ((2 * left + 1) >= T.GetNodeNumber()) {
					//p的孩子是叶子结点
					T.GetNode(p)->data = right;
				}
				else {
					//p的孩子不是叶子结点
					T.GetNode(p)->data = T.GetNode(right)->data;
				}
			}

			p = (int)ceil(p / 2.0 - 1);
		}
	}

	//--树形选择排序
	//时间复杂度：O(nlogn)
	template <typename _Type>
	void TreeSelectSort(SeqList<_Type> &list)
	{
		SeqBiTree<_Type> T;
		T.CreateDataInLeaf(list);  //生成一颗完全二叉树，list的元素都存放在叶子节点

		FirstTreeSelectSort<_Type>(T); //首次树形选择排序

		int index = T.GetNode(0)->data;
		list[1] = T.GetNode(index)->data;  //把第一次排序结果保存下来
		T.GetNode(index)->data = std::numeric_limits<int>().max();;  //把该元素所存放的数据置为INT_MAX

		//剩下的元素根据第一次排序后树的形态排序，只需要拿上次结果所在路径的元素比较即可
		for (int i = 2; i <= list.size(); ++i)
		{
			TreeSelectSort(T);  //树形排序

			index = T.GetNode(0)->data;
			list[i] = T.GetNode(index)->data;  //把第一次排序结果保存下来
			T.GetNode(index)->data = std::numeric_limits<int>().max();;  //把该元素所存放的数据置为INT_MAX
		}
	}

	//--返回所在下标的左、右孩子的值，如果左、右孩子不是叶结点则返回左、右孩子所存放的下标的值
	template <typename _Type>
	_Type GetValue(const SeqBiTree<_Type> &T, int p, int child)
	{
		
		if ((child * 2 + 1) >= T.GetNodeNumber()){
			//如果child下标的结点是叶子结点
			return T.GetNode(child)->data;
		}
		else{
			//child下标的结点不是叶子结点
			int index = T.GetNode(child)->data;
			return T.GetNode(index)->data;
		}
	}

	//--堆排序
	//时间复杂度：O(nlogn)
	template <typename _Type>
	void HeapSort(SeqList<_Type> &list)
	{
		//建立一个大顶堆，从最后一个非终端结点前反复"筛选"
		for (int i = list.size() / 2; i >= 1; --i){
			HeapAdjust(list, i, list.size());
		}

		int n = list.size();
		for (int i = list.size(); i > 1; --i) {

			auto tmp = list[1];
			list[1] = list[n];
			list[n] = tmp;

			//重新调整为大顶堆
			HeapAdjust(list, 1, --n);
		}
	}

	//--堆排序(筛选)
	template <typename _Type>
	void HeapAdjust(SeqList<_Type> &list, int pos, int len)
	{
		//当前需要筛选的结点不是叶子结点
		int left, right;
		while (pos * 2 <= len)
		{
			left = pos * 2;
			right = left + 1;

			if (right <= len){
			//右子树存在

				if (LT(list[left], list[right])) {
				//左孩子的值 < 右孩子的值
					if (LT(list[pos], list[right])) {
						//当前节点的值 < 右孩子的值
						auto tmp = list[pos];
						list[pos] = list[right];
						list[right] = tmp;

						pos = right;
					}
					else
						break;
				}
				else {
				//左孩子的值 > 右孩子的值
					if (LT(list[pos], list[left])) {
						//当前节点的值 < 左孩子的值
						auto tmp = list[pos];
						list[pos] = list[left];
						list[left] = tmp;

						pos = left;
					}
					else
						break;
				}
			}
			else{
			//右子树不存在
				if (LT(list[pos], list[left])) {
					//当前节点的值 < 左子树的值
					auto tmp = list[pos];
					list[pos] = list[left];
					list[left] = tmp;
				}
				break;
			}
		}
	}

	//2-路归并排序<接口>
	//时间复杂度：O(nlogn)
	template <typename _Type>
	void MergeSort(SeqList<_Type> &list)
	{
		SeqList<_Type> tmp(list.size()); //和list相同大小的辅助空间
		MergeSort(list, tmp, 1, list.size());
	}

	//2-路归并排序<实现>
	template <typename _Type>
	void MergeSort(SeqList<_Type> &SR, SeqList<_Type> &TR, int L, int R)
	{
		if (L >= R)
			return;

		int mid = (L + R) / 2;     //以mid划分，分别对左、右进行归并排序
		MergeSort(SR, TR, L, mid);
		MergeSort(SR, TR, mid + 1, R);
		Merge(SR, TR, L, mid, R);  //左、右归并排序后，对其进行合并
	}

	//--归并
	template <typename _Type>
	void Merge(SeqList<_Type> &SR, SeqList<_Type> &TR, int L, int mid, int R)
	{
		if (L == R)
			return;

		//把要归并的元素拷贝到辅助空间TR
		for (int i = L; i <= R; ++i)
			TR[i] = SR[i];

		int i = L;
		int j = mid + 1;
		int k = L;
		while (i <= mid && j<= R){

			if (LT(TR[i], TR[j]))
				SR[k++] = TR[i++];
			else
				SR[k++] = TR[j++];
		}

		while (i <= mid)
			SR[k++] = TR[i++];

		while (j <= R)
			SR[k++] = TR[j++];
	}


	//--链式基数排序<接口>
	//时间复杂度：O(d(n+rd))
	//基数排序需要按照实际情况，进行不同的辅助空间的分配、数据的分配和收集，这里只是针对整形进行实现
	template <typename _Type>
	void RadixSort(SeqList<_Type> &list)
	{
		//把顺序表的数据保存在静态链表中
		SLinkList<_Type> linklist;
		for (int i = 1; i <= list.size(); ++i)
			linklist.insert(i, list[i]);

		RadixSort(linklist);  //进行基数排序

		//把数据迁移回顺序表
		int index = linklist[0].next;
		for (int i = 1; i <= list.size(); ++i) {
			list[i] = linklist[index].data;
			index = linklist[index].next;
		}
	}

	//--链式基数排序<实现>
	template <typename _Type>
	void RadixSort(SLinkList<_Type> &list)
	{
		//创建辅助空间(链队列)，用于分配和收集
		//创建的辅助空间看情况而定，例如排序的是数字0-9，则分配大小为10的链队列

		int keynum = 3; //关键字的个数，3表示以个、十、百位进行分配
		for (int i = 0; i < keynum; ++i)
		{
			//初始化辅助空间
			SeqList<DLinkList> flist(10);

			Distribute(list, i, flist);  //分配
			Collect(list, i, flist);     //收集
		}
	}

	//--分配
	template <typename _Type>
	void Distribute(SLinkList<_Type> &list, int n, SeqList<DLinkList> &flist)
	{
		//计算权值，用于分离要操作的位
		int weight = (int)pow(10, n);

		//按照位，把数据分配到辅助空间对应的位置
		for (int i = 1; i <= list.size(); ++i) {

			//分离出要操作的位
			int bit = list[i].data / weight % 10;
			flist[bit].insert(1, list[i].data);
        }
	}

	//--收集
	template <typename _Type>
	void Collect(SLinkList<_Type> &list, int n, SeqList<DLinkList> &flist)
	{
		//把flist的链表串连起来
		int k = 1;
		for (int i = 0; i <= flist.size(); ++i) {

			DListNode *p = flist[i].head;
			DListNode *head = flist[i].head;

			while (p->prior != head) {
				p = p->prior;
				list[k++].data = p->data;
			}
		}
	}

}

#endif //SORT_H
