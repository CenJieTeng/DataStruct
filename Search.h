//项目：查找相关的算法
//创建时间：？
//完成时间：2019/1/2
//最后一次修改时间：
//修改次数：
//修改原因：
//
//作者：CenJieTeng
//QQ: 2271369683
#pragma once
#ifndef SEARCH_H
#define SEARCH_H
#include <iostream>
#include <math.h>
#include <stack>
#include "BiTree.h"
#include "SeqList.h"
#define EQ(a,b) ((a)==(b))
#define LT(a,b) ((a)<(b))    //!LT  等价于 a >= b
#define LQ(a,b) ((a)<=(b))   //!LQ  等价于 a > b


namespace cjt
{
//----------------------------------------静态表查找--------------------------------------------------


	//--顺序查找
	//参数说明：输入范围（迭代器），要查找元素的key
	//平均查找时间：(n + 1) / 2
	template <typename _Titer,
		typename _Tkey>
		int Search_Seq(_Titer begin, _Titer end, _Tkey key) {

		if (begin == end) //输入范围为空
			return 0;

		*begin = key; //0下标不存放数据，把key赋值给它，作为查找结束依据。--“哨兵”免去检查是否超过范围
		_Titer iterCur = --end; //当前所比较元素的游标，默认指向最后一个元素

		for (; !EQ(*iterCur,key); --iterCur); //向前迭代寻找与key相等的元素，如果找不到iterCur == begin

		return iterCur - begin;
	}

	//--折半查找
	//参数说明：输入范围（迭代器），要查找元素的key
	//限制：1、有序表，2、顺序存储结构
	//平均查找时间：(log (n + 1) / log 2) - 1
	template <typename _Titer,
		typename _Tkey>
		int Search_Bin(_Titer begin, _Titer end, _Tkey key) {

		int low = 1, high = end - begin; //标出查找范围

		while (high >= low) { //如果范围内还存在元素
			int mid = (low + high) / 2; //求中间元素下标，

			if (EQ(*(beg3in + mid),key)) return mid; //找到元素，返回下标
			else if (!LQ(key,*(begin + mid))) low = mid + 1; //如果key大于mid下标的元素，在[mid + 1,high] 范围内继续查找
			else
				high = mid - 1; //如果key小于mid下标的元素，在[low,mid - 1] 范围内继续查找
		}

		return 0;
	}

    //静态树表查找
	//--构造次优查找树<实现>
	//参数说明：二叉树根节点的地址，顺序表，累计权值表，list范围（1），list范围(list.size())
	template <typename _Type,
		typename _Tw>
	void SecondOptimal(typename BiTree<_Type>::BiTreeNode **T, SeqList<_Type> list, _Tw *sw, int low, int high) {

		int i, j;
		i = low;
		_Tw min = (_Tw)fabs(sw[high] - sw[low]); //初始化min为当前查找范围第一个元素的△Pi值
		_Tw dw  = sw[high] + sw[low - 1];

		// 选择最小的△Pi值
		for (j = low + 1; j <= high; ++j)
			if (fabs(dw - sw[j] - sw[j - 1]) < min) //如果找到新的△Pi值比当前最小值min小的元素
			{
				i = j; //保存当前元素的下标
				min = (_Tw)fabs(dw - sw[j] - sw[j - 1]); //更新最小值找到的新值
			}

		//构造根节点
		(*T) = (BiTree<_Type>::BiTreeNode*)malloc(sizeof(BiTree<_Type>::BiTreeNode));
		(*T)->data =list.find_n(i);

		if (i == low) (*T)->leftChild = nullptr;    //左子树为空
		else
			SecondOptimal(&(*T)->leftChild, list, sw, low, i - 1);   //构造左子树

		if (i == high) (*T)->rightChild = nullptr;	  //右子树为空
		else
			SecondOptimal(&(*T)->rightChild, list, sw, i + 1, high);   //构造右子树
	}

	//计算累计权值，sw[0] = 0;
	template <typename _Type>
	void findSW(SeqList<_Type> list, int *sw)
	{
		for (int i = 1; i <= list.size() ; ++i)
			sw[i] = sw[i - 1] + list.find_n(i).weight;
	}

	//构造次优二叉树<外部接口>
	//参数说明：二叉树，顺序表
	template <typename _Type>
	void CreateSOSTree(BiTree<_Type> &T, SeqList<_Type> list){

		if (list.size() == 0)
			return;
		else{
			int sw[10]; //累计权值列表
			memset(sw, 0, sizeof(sw)); //初始化sw
			findSW(list, sw); //计算累计权值

			SecondOptimal(&(T.root), list, sw, 1, list.size()); //构造次优二叉树
		}
	}

	//--有序树的查找<接口>
	//（有序：左子树的所有节点都比根节点小，右子树则都比根节点大）
	//参数说明：有序的二叉树，要查找元素的key
	//类似折半查找，次优查找树是针对查找概率不相等的查找问题
	template <typename _Type,
		typename _Tkey>
	bool Search_OrderedTree(const BiTree<_Type> &T, _Tkey key)
	{
		return Search_OrderedTree<_Type>(T.root, key); //这Search_OrderedTree<_Type>帮助函数推导类型
	}

	//--有序树的查找<接口>
	//参数说明：有序树根节点，要查找元素的key
	template <typename _Type,
		typename _Tkey>
	bool Search_OrderedTree(typename const BiTree<_Type>::BiTreeNode *T, _Tkey key)
	{
		while (T){
			if (T->data == key)
				return true;

			if (LT(key, T->data))
				T = T->leftChild;  //如果key 小于 T->data 在左子树中继续查找
			else
				T = T->rightChild; //如果key 大于 T->data 在右子树中继续查找
		}

		return false;
	}
	
	//--索引顺序表查找
	template <typename _Tlist,
		typename _Tkey>
	int Search_IndexSeqList(_Tlist list, _Tkey key) {

		//折半查找，找到key可能所在的索引表块
		int n = 0, low = 1, high = list.lenght - 1;
		while (high >= low){
			int mid = (low + high) / 2;
			if (EQ(list.table[mid].data, key)){
				n = mid; break;
			}
			else if (!LQ(key, list.table[mid].data)) low = mid + 1;
			else high = mid - 1;
		}
		if (n == 0)
			n = low > high ? low : high;

		//索引表块的范围
		int left = list.table[n - 1].index;
		int right = list.table[n].index;

		for (int i = left; i < right; ++i)
			if (list.data[i] == key)
				return i;

		return 0;
	}


	
//----------------------------------------动态表查找--------------------------------------------------

	//二叉排序树的查找<接口>
	template <typename _Type,
		typename _Tkey>
	bool Search_BST(BiTree<_Type> &T, _Tkey key, typename BiTree<_Type>::BiTreeNode *&p){
		return Search_BST<_Type>(T.root, key, nullptr, p);
	}

	//二叉排序树的查找<实现>
	template <typename _Type,
		typename _Tkey>
	bool Search_BST(typename BiTree<_Type>::BiTreeNode *T, _Tkey key, 
			typename BiTree<_Type>::BiTreeNode *f, typename BiTree<_Type>::BiTreeNode *&p){
		//如果查找成功，p指向查的找结点，否则p指向最后一个查找的元素
		while (T) {
			if (T->data == key){ //查找成功
				p = T;
				return true;
			}

			f = T;
			if (LT(key, T->data)) T = T->leftChild;  //如果key 小于 T->data 在左子树中继续查找
			else 
				T = T->rightChild; //如果key 大于 T->data 在右子树中继续查找
		}

		//查找不成功
		p = f;
		return false;
	}


	//二叉排序树插入节点
	template <typename _Type,
		typename _Tkey>
	bool Insert_BST(BiTree<_Type> &T, _Tkey key){

		BiTree<_Type>::BiTreeNode *p = nullptr;
		if (!Search_BST(T, key, p)) { //树中不存在关键字为key的结点

			//创建结点
			auto tmp = (typename BiTree<_Type>::BiTreeNode*)malloc(sizeof(typename BiTree<_Type>::BiTreeNode));
			tmp->data = key;
			tmp->leftChild = tmp->rightChild = nullptr;

			if (p == nullptr) T.root = tmp; //树为空创建根节点，否则key值与p指向的结点比较
			else if (LT(key, p->data)) //p->data比key小
				p->leftChild = tmp;
			else
				p->rightChild = tmp;   //p->data比key大

			return true;
		}

		return false;
	}

	//构造二叉排序树
	template <typename _Type>
	void CreateBST(BiTree<_Type> &T,const SeqList<_Type> &list)
	{
		if (list.size() != 0)
		{
			if (!T.Empty()) //如果树不为空清空树
				T.ClearBiTree();

			//插入数据
			for each (const _Type value in list)
				Insert_BST(T, value);
		}
	}

	//二叉排序树删除节点<接口1>
	template <typename _Type,
		typename _Tkey>
	bool Ernse_BST(BiTree<_Type> &T, _Tkey key) {
		return Ernse_BST<_Type>(&T.root, key);
	}

	//二叉排序树删除节点<接口2>
	template <typename _Type,
		typename _Tkey>
	bool Ernse_BST(typename BiTree<_Type>::BiTreeNode **T, _Tkey key) {
		
		if (!T) return false;
		else
		{
			if (EQ(key, (*T)->data)) { Ernse_BST<_Type>(T); return true; }
			else if (LT(key, (*T)->data)) Ernse_BST<_Type>(&(*T)->leftChild, key);
			else
				Ernse_BST<_Type>(&(*T)->rightChild, key);
		}

		return false;
	}


	//二叉排序树删除节点<实现>
	template <typename _Type>
	bool Ernse_BST(typename BiTree<_Type>::BiTreeNode **T) {

		BiTree<_Type>::BiTreeNode *p, *q;
		p = q = nullptr;

		if ((*T)->leftChild != nullptr && (*T)->rightChild != nullptr){
			//情况1：p的两棵子树都不为空
			//寻找左树中最大的结点 或 寻找右树中的最小结点，代替该结点，找到的结点代替该结点被删除
			q = (*T); 
			auto s = q->leftChild;

			while (s->rightChild) { p = s; s = s->rightChild; }
			q->data = s->data;
			if (q != p) p->rightChild = s->leftChild;
			else
				q->leftChild = s->leftChild;
			free(s);
		}
		else{ //被删除的结点子树数为0或1
		
			q = (*T);

			if (!(*T)->leftChild) { //情况2：被删除节点没有左子树,重连右子树(子树为为零包括在这种情况内)
				(*T) = (*T)->rightChild;
			}
			else{ //情况3：被删除节点没有右子树，重连左子树
				(*T) = (*T)->leftChild;
			}

			free(q);
		}

		return true;
	}

	//插入平衡二叉树节点<接口>
	template <typename _Type,
		typename _Tkey>
	bool Insert_AVLTree(BiTree<_Type> &T, _Tkey key) {
		return Insert_AVLTree<_Tkey>(T.root, key);
	}

	//插入平衡二叉树节点<实现>
	template <typename _Type,
		typename _Tkey>
	bool Insert_AVLTree(typename BiTree<_Type>::BiTreeNode *&T, _Tkey key) {

		if (T == nullptr) { //根结点为空时，创建根结点
			T = (typename BiTree<_Type>::BiTreeNode*)malloc(sizeof(typename BiTree<_Type>::BiTreeNode));
			T->data = key;
			T->leftChild = T->rightChild = nullptr;
			T->bf = 0;
			return true;
		}

		//保存寻找插入位置所经过的路径
		std::stack<typename BiTree<_Type>::BiTreeNode**>Stack;

		auto **pCur = &T;
		decltype(pCur) pParent = nullptr;
		//寻找插入位置
		while (*pCur){
			if (EQ(key, (*pCur)->data)) { //树中存在关键值为key的结点
				return false;
			}
			else{
				Stack.push(pCur);
				if (LT(key, (*pCur)->data)) //在该结点的左子树继续查找
					pCur = &((*pCur)->leftChild);
				else //在该结点的左子树继续查找
					pCur = &((*pCur)->rightChild);
			}
		}
		pParent = Stack.top();

		//创建新结点
		auto p = (typename BiTree<_Type>::BiTreeNode*)malloc(sizeof(typename BiTree<_Type>::BiTreeNode));
		p->data = key;
		p->leftChild = p->rightChild = nullptr;
		p->bf = 0;
		//插入节点
		if (LT(key, (*pParent)->data))
			(*pParent)->leftChild = p;
		else
			(*pParent)->rightChild = p;

		//调整BF(平衡因子)，默认BF=右子树高度 - 左子树高度
		while (!Stack.empty()) //保存查找路径的栈非空
		{
			pParent = Stack.top(); //取栈顶元素
			Stack.pop(); //栈顶元素出栈

			//修改parent的BF
			if ((*pParent)->leftChild == (*pCur)) //如果当前节点在parent的左子树
				(*pParent)->bf--;
			else //如果当前节点在parent的右子树
				(*pParent)->bf++;

			if ((*pParent)->bf == 0) //已经平衡，不需要向上调整
				break;
			else if ((*pParent)->bf == 1 || (*pParent)->bf == -1) //继续向上调整
				pCur = pParent; //回溯
			else{
				//此时parent的BF为2或者-2，失衡需要旋转
				if ((*pParent)->bf * ((*pCur))->bf > 0) { //同符号，单旋转
					if ((*pParent)->bf < 0)
						RotateR<_Type>(*pParent);//右单旋，插入左树的左子树导致的失衡
					else
						RotateL<_Type>(*pParent);//左单旋，插入右树的右子树导致的失衡
				}
				else { //双旋
					if ((*pParent)->bf < 0)
						RotateLR<_Type>(*pParent);//先左后右双旋，插入左树的右子树导致的失衡
					else
						RotateRL<_Type>(*pParent);//先右后左双旋，插入右树的左子树导致的失衡
				}
				break; //旋转后不需要向上调整
			}
		}

		return true;
	}

	//左单旋
	template <typename _Type>
	void RotateL(typename BiTree<_Type>::BiTreeNode *&T)
	{
		auto subL = T;
		T = T->rightChild;

		subL->rightChild = T->leftChild;
		T->leftChild = subL;
		subL->bf = T->bf = 0;
	}

	//右旋转
	template <typename _Type>
	void RotateR(typename BiTree<_Type>::BiTreeNode *&T)
	{
		auto subR = T;
		T = T->leftChild;

		subR->leftChild = T->rightChild;
		T->rightChild = subR;
		subR->bf = T->bf = 0;
	}

	//先左后右旋转
	template <typename _Type>
	void RotateLR(typename BiTree<_Type>::BiTreeNode *&T)
	{
		auto subR = T;
		auto subL = T->leftChild;
		T = subL->rightChild;

		//左旋
		subL->rightChild = T->leftChild;
		T->leftChild = subL;
		if (T->bf <= 0)
			subL->bf = 0;
		else
			subL->bf = 1;

		//右旋
		subR->leftChild = T->rightChild;
		T->rightChild = subR;
		if (T->bf == -1)
			subR->bf = 1;
		else
			subR->bf = 0;

		T->bf = 0;
	}

	//先右后左旋转
	template <typename _Type>
	void RotateRL(typename BiTree<_Type>::BiTreeNode *&T)
	{
		auto subL = T;
		auto subR = T->rightChild;
		T = subR->leftChild;

		//右旋
		subR->leftChild = T->rightChild;
		T->rightChild = subR;
		if (T->bf >= 0)
			subR->bf = 0;
		else
			subR->bf = 1;

		//左旋转
		subL->rightChild = T->leftChild;
		T->leftChild = subL;
		if (T->bf == -1)
			subL->bf = 0;
		else
			subL->bf = -1;

		T->bf = 0;
	}


	//删除平衡二叉树结点<接口1>
	template <typename _Type,
		typename _Tkey>
	bool Ernse_AVLTree(BiTree<_Type> &T, _Tkey key) {
		return Ernse_AVLTree<_Type>(T.root, key);
	}

	//删除平衡二叉树结点<接口2>
	template <typename _Type,
		typename _Tkey>
	bool Ernse_AVLTree(typename BiTree<_Type>::BiTreeNode *&T, _Tkey key) {

		if (!T) return false;
		else{
			stack<typename BiTree<_Type>::BiTreeNode**> Stack;
			auto **pCur = &T;
			decltype(pCur) pParent = nullptr;
			BiTree<_Type>::BiTreeNode *p = nullptr, *q = nullptr;

			while (*pCur){
				if (EQ(key, (*pCur)->data)){
					p = q = nullptr;

					if ((*pCur)->leftChild != nullptr && (*pCur)->rightChild != nullptr) {
						//情况1：p的两棵子树都不为空
						//寻找左树中最大的结点 或 寻找右树中的最小结点，代替该结点，找到的结点代替该结点被删除
						p = q = (*pCur);
						auto s = q->leftChild;

						Stack.push(pCur);
						while (s->rightChild) { 
							p = s;
							Stack.push(&p);
							s = s->rightChild; 
						}
						q->data = s->data;
						if (q != p) p->rightChild = s->leftChild;
						else
							q->leftChild = s->leftChild;
						free(s);
						break;
					}
					else { //被删除的结点子树数为0或1

						q = (*pCur);

						if (!(*pCur)->leftChild) { //情况2：被删除节点没有左子树,重连右子树(子树为为零包括在这种情况内)
							(*pCur) = (*pCur)->rightChild;
						}
						else { //情况3：被删除节点没有右子树，重连左子树
							(*pCur) = (*pCur)->leftChild;
						}

						free(q);
						break;
					}
				}
				else if (LT(key, (*pCur)->data))
				{
					Stack.push(pCur);
					pCur = &((*pCur)->leftChild);
				}
				else
				{
					Stack.push(pCur);
					pCur = &((*pCur)->rightChild);
				}
			}

			//调整BF
			int first = true; //第一个进入循环时特殊处理
			while (!Stack.empty()) {
				pParent = Stack.top();
				Stack.pop();

				if (first) //第一次进入循环
				{
					first = false;

					if (LT(key, (*pParent)->data))
						(*pParent)->bf++;
					else
						(*pParent)->bf--;

					pCur = pParent;
				}
				else
				{
					if ((*pParent)->leftChild == (*pCur))
						(*pParent)->bf++;
					else
						(*pParent)->bf--;
				}

				if ((*pParent)->bf == 1 || (*pParent)->bf == -1)
					break;
				else if ((*pParent)->bf == 0)
					pCur = pParent;
				else {
					int flag;
					typename BiTree<_Type>::BiTreeNode *ptr = nullptr;
					if ((*pParent)->bf < 0) {
						flag = -1;
						ptr = (*pParent)->leftChild;
					}
					else {
						flag = 1;
						ptr = (*pParent)->rightChild;
					}

					if (ptr->bf == 0) //单旋转,并调整平衡因子
					{
						if (flag == -1)//右旋转
						{
							RotateR<_Type>(*pParent);
							(*pParent)->bf = 1;
							(*pParent)->rightChild->bf = -1;
						}
						else//左旋转
						{
							RotateL<_Type>(*pParent);
							(*pParent)->bf = -1;
							(*pParent)->leftChild->bf = 1;
						}
					}
					else
					{
						if (ptr->bf * flag > 0) { //同符号，单旋转
							if ((*pParent)->bf < 0)
								RotateR<_Type>(*pParent);//右单旋
							else
								RotateL<_Type>(*pParent);//左单旋
						}
						else { //双旋
							if ((*pParent)->bf < 0)
								RotateLR<_Type>(*pParent);//先左后右双旋
							else
								RotateRL<_Type>(*pParent);//先右后左双旋
						}
					}
					//break;
				}
			}
		}

		return false;
	}

}

#endif // !SEARCH_H
