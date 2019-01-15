//项目：二叉树(顺序存储结构)
//创建时间：2019/1/13 14:13
//完成时间：?
//最后一次修改时间：
//修改次数：
//修改原因：
//
//
//作者：CenJieTEng
//QQ: 2271369683
#pragma once
#ifndef SEQBITREE_H
#define SEQBITREE_H
#include <math.h>

namespace cjt
{
	template <typename T>
	class SeqBiTree
	{
		//--友元区
		template <typename _Type>
		friend void TreeSelectSort(SeqList<_Type> &list);
	public:
		using DataType = T;
		struct SeqBiTreeNode
		{
			DataType data;
		};
	public:
		SeqBiTree();
		~SeqBiTree();

	public:
		void CreateSeqBiTree(const SeqList<T> &list);            //根据顺序表创建二叉树
		void CreateDataInLeaf(const SeqList<T> &list);           //根据顺序表，创建一颗至少有list.size()个叶子的完全二叉树
		bool Empty() const;                                      //判空
		int  GetDepth() const;                                   //获取深度
		int  GetNodeNumber() const;                              //获取结点个数
		int  GetLeafNodeNumber() const;                          //获取叶子节点个数
		SeqBiTreeNode Root() const;                              //获取根结点
		void ClearSeqBiTree();                                   //清除树
		SeqBiTreeNode* GetNode(int index) const;                 //返回下标对应的结点

	private:
		int length;
		SeqBiTreeNode *root;
	};

#endif // !SeqBiTree


	//---------------------------------------华丽的分割线-------------------------------------------------

	template <typename T>
	SeqBiTree<T>::SeqBiTree() : length(0), root(nullptr)
	{
	}

	template <typename T>
	SeqBiTree<T>::~SeqBiTree()
	{
		ClearSeqBiTree();
	}

	template <typename T>
	void SeqBiTree<T>::CreateSeqBiTree(const SeqList<T> &list)
	{
		root = (SeqBiTreeNode*)malloc(list.size() * sizeof(SeqBiTreeNode));

		for (int i = 0; i < list.size(); ++i) {
			root[i].data = list[i + 1];
		}
		length = list.size();
	}

	//根据顺序表，创建一颗至少有list.size()个叶子的完全二叉树
	template <typename T>
	void SeqBiTree<T>::CreateDataInLeaf(const SeqList<T> &list)
	{
		if (list.empty())
			return;

		//计算深度为多少才能把list的元素全部保存在叶子节点
		int depth = 1;
		while (true)
		{
			if (pow(2, depth - 1) >= list.size())
				break;

			++depth;
		}

		//分配内存空间，深度为depth满二叉树
		length = (int)(pow(2, depth) - 1);
		root = (SeqBiTreeNode*)malloc(length * sizeof(SeqBiTreeNode)); 

		//把数据存放在叶子节点
		int n = 1;
		for (int i = (length-1) / 2; i < length; ++i) {

			if (n <= list.size())
				root[i].data = list[n++];
			else
				root[i].data = INT_MAX;
		}
	}

	//判空
	template <typename T>
	bool SeqBiTree<T>::Empty() const
	{
		return root == nullptr;
	}

	//获取深度
	template <typename T>
	int  SeqBiTree<T>::GetDepth() const
	{
		if (Empty())
			return 0;

		int depth = 1;
		while (true)
		{
			if (pow(2, depth) - 1 >= length)
				return depth;

			++depth;
		}
	}

	//获取结点个数
	template <typename T>
	int  SeqBiTree<T>::GetNodeNumber() const
	{
		return length;
	}

	//获取叶子节点个数
	template <typename T>
	int  SeqBiTree<T>::GetLeafNodeNumber() const
	{
		int iCount = 0;

		for (int i = 0; i < length; ++i) {
			if ((2 * i + 1) >= length)
				++iCount;
		}

		return iCount;
	}

	//获取根结点
	template <typename T>
	typename SeqBiTree<T>::SeqBiTreeNode SeqBiTree<T>::Root() const
	{
		return *root;
	}

	//清除树
	template <typename T>
	void SeqBiTree<T>::ClearSeqBiTree()
	{
		free(root);
	}

	//返回下标对应的结点
	template <typename T>
	typename SeqBiTree<T>::SeqBiTreeNode* SeqBiTree<T>::GetNode(int index) const
	{
		if (index < 0 || index > length)
			return nullptr;

		return &root[index];
	}

}
