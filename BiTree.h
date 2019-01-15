//项目：二叉树(链式存储结构，二叉链树)
//创建时间：2017/12/2 14:54
//完成时间：2017/12/9 20:23
//最后一次修改时间：2018/12/22
//修改次数：1
//修改原因：
//改为模板类
//
//
//作者：CenJieTeng
//QQ: 2271369683
#pragma once
#ifndef BITREE_H
#define BITREE_H
#include <iostream>
#include <stack>
#include <queue>
#include <string.h>
//#define THREADING //需要线索化二叉树时定义
#define AVL_TREE  //需要构造平衡二叉树时定义

namespace cjt
{
	template <typename T>
	class BiTree
	{
		//---友元区---
		template <typename _Type,
			typename _Tw >
		friend void SecondOptimal(typename BiTree<_Type>::BiTreeNode **T, SeqList<_Type> list, _Tw *sw, int low, int high);

		template <typename _Type>
		friend void CreateSOSTree(BiTree<_Type> &T, SeqList<_Type> list);

		template <typename _Type,
			typename _Tkey>
		friend bool Search_OrderedTree(const BiTree<_Type> &T, _Tkey key);

		template <typename _Type,
			typename _Tkey>
		friend bool Search_OrderedTree(const typename BiTree<_Type>::BiTreeNode *T, _Tkey key);

		template <typename _Type,
			typename _Tkey>
		friend bool Search_BST(BiTree<_Type> &T, _Tkey key, typename BiTree<_Type>::BiTreeNode *&p);

		template <typename _Type,
			typename _Tkey>
		friend bool Search_BST(typename BiTree<_Type>::BiTreeNode *T, _Tkey key, typename BiTree<_Type>::BiTreeNode *f, typename BiTree<_Type>::BiTreeNode *&p);

		template <typename _Type,
			typename _Tkey>
		friend bool Insert_BST(BiTree<_Type> &T, _Tkey key);

		template <typename _Type,
			typename _Tkey>
		friend bool Ernse_BST(BiTree<_Type> &T, _Tkey key);

		template <typename _Type,
			typename _Tkey>
		friend bool Insert_AVLTree(BiTree<_Type> &T, _Tkey key);

		template <typename _Type,
			typename _Tkey>
		friend bool Ernse_AVLTree(BiTree<_Type> &T, _Tkey key);

		template <typename _Type>
		friend void TreeSelectSort(SeqList<_Type> &list);

	public:
		//---类型定义 重命名区---
		using DataType = T;
		typedef enum { LINK, THREAD }PointerTag;

		struct BiTreeNode
		{
			DataType data;                       //数据
			BiTreeNode *leftChild, *rightChild;  //左右孩子指针 或是线索二叉树中的前驱后继
		#ifdef THREADING
			PointerTag LTag = LINK, RTag = LINK; //线索二叉树需要用到的标记
		#endif // THREADING
		#ifdef AVL_TREE
			int bf; //平衡因子
		#endif // AVL_TREE
		};

		//后序遍历(栈)要用到的结构体
		typedef enum { L, R }Tag;
		struct StkTreeNode
		{
			BiTreeNode *ptr;
			Tag tag;
		};

	public:
		BiTree();
		~BiTree();

	public:
		bool Empty() const;                                      //判空
		int  GetDepth() const;                                   //获取深度
		int  GetNodeNumber() const;                              //获取结点个数
		int  GetLeafNodeNumber() const;                          //获取叶子节点个数
		bool IsSameStruct(const BiTree &, const BiTree &) const; //判断两颗树是否有相同的结构
		void Mirror();                                           //求二叉树的镜像(交换左右子树)
		BiTreeNode* FindLCA(const BiTreeNode*, const BiTreeNode*)const;//寻找最低公共祖先结点
		BiTreeNode Root() const;                                 //获取根结点
		void ClearBiTree();                                      //清除树
		BiTreeNode* FindNode(const DataType x) const;            //获取值等于x的结点
		BiTreeNode* LeftChild(const DataType x) const;           //获取值等于x的结点的 左孩子
		BiTreeNode* RightChild(const DataType x) const;          //获取值等于x的结点的 右孩子
		BiTreeNode* Parent(const DataType x) const;              //获取值等于x的结点的 双亲(二叉链树比较吃力)
		BiTreeNode* RightSibling(const DataType x) const;        //获取值等于x的结点的 右兄弟<接口>
		void InsertChile(BiTreeNode *p, int LR, BiTreeNode *c);  //填加孩子(结点或树),LR是标记操作 左/右孩子 下同
		void DeletetChile(BiTreeNode *p, int LR);                //删除孩子(结点，或树)

		//树创建 & 线索化
		void CreateDataInLeaf(const SeqList<T> &list);         //根据顺序表，创建一颗至少有list.size()个叶子的完全二叉树
		void CreateBiTreeWithDepth(int depth);                 //创建深度为depth的完全二叉树<接口>
		void CreateBiTree_Preorder();                          //前序创建<接口>
		void CreateBiTree_Per_In(char *VLR, char *LVR, int n); //根据已知 前序 和 中序 序列创建二叉树
		void CreateBiTree_Post_In(char *LRV, char *LVR, int n);//根据已知 后序 和 中序 序列创建二叉树
	#ifdef THREADING
		void Threading_InOrder();                              //中序线索化<接口>
	#endif // THREADING

		

		//树遍历
		void PreOrderTraverse(void(*Visit)(DataType));     //前序遍历(递归)<接口>，中序、后序类似
		void PreOrderTraverse_1(void(*Visit)(DataType));   //前序遍历(栈)
		void InOrderTraverse_1(void(*Visit)(DataType));    //中序遍历(栈)
		void PostOrderTraverse_1(void(*Visit)(DataType));  //后序遍历(栈)
		void LevelOrderTraverse(void(*Visit)(DataType));   //层遍历(队列)


	private:
		void CreateBiTreeWithDepth(typename BiTree<T>::BiTreeNode *&T, int depth); //创建深度为depth的完全二叉树<接口>
		void CreateBiTree_Preorder(BiTreeNode* &t);                              //前序创建<实现>
	#ifdef THREADING
		void Threading_InOrder(BiTreeNode *p, BiTreeNode *&pre);                 //中序线索化<实现>
	#endif // THREADING
		void CreateBiTree_Per_In(BiTreeNode *&t, char *VLR, char *LVR, int n);   //根据已知 前序 和 中序 序列创建二叉树<实现>							 
		void CreateBiTree_Post_In(BiTreeNode *&t, char *LRV, char *LVR, int n);  //根据已知 后序 和 中序 序列创建二叉树<实现>
		void PreOrderTraverse(BiTreeNode *&t, void(*Visit)(DataType));           //前序遍历，递归法<实现>
		int  MaxDepth(BiTreeNode *p) const;                                      //计算深度									 
		int  GetNodeNumber(BiTreeNode *t) const;                                 //获取结点个数<实现>
		int  GetLeafNodeNumber(BiTreeNode *t) const;                             //获取叶子节点个数<实现>															 
		bool IsSameStruct(const BiTreeNode *, const BiTreeNode *) const;         //判断两颗树是否有相同的结构<实现>								 
		void Mirror(BiTreeNode *t);                                              //求二叉树的镜像<实现>
		BiTreeNode* FindLCA(BiTreeNode*, const BiTreeNode*, const BiTreeNode*)const;//寻找最低公共祖先结点<实现>
		void ClearBiTree(BiTreeNode* &t);                                        //清除树
		BiTreeNode* FindNode(BiTreeNode *t, const DataType x) const;             //寻找值等于x的结点																   
		BiTreeNode* Parent(BiTreeNode *t, const DataType x) const;               //获取值等于x的结点的 双亲<实现>
		BiTreeNode* RightSibling(BiTreeNode *const &T, const DataType x) const;        //获取值等于x的结点的右兄弟<实现>

	private:
		BiTreeNode *root;        //根结点
	#ifdef THREADING
		BiTreeNode *ThreadHead;  //线索二叉树的头结点
	#endif // THREADING
		char FinishFlag;         //结束标记'#'
	};

#endif // !BITREE_H

//---------------------------------------华丽的分割线-------------------------------------------------


	using std::cout; using std::cin; using std::endl; using std::stack; using std::queue;

	template <typename T>
	BiTree<T>::BiTree() : root(nullptr), FinishFlag('#')
	{
	#ifdef THREADING
		ThreadHead(nullptr)
	#endif // THREADING
	}

	template <typename T>
	BiTree<T>::~BiTree()
	{
		ClearBiTree(root);
	}

	//根据顺序表，创建一颗至少有list.size()个叶子的完全二叉树
	template <typename T>
	void BiTree<T>::CreateDataInLeaf(const SeqList<T> &list)
	{
		int leafCount = 1;  //当前叶子节点数
		int depth = 1;
		while (leafCount < list.size())
		{
			leafCount *= 2;
			++depth;
		}

		CreateBiTreeWithDepth(depth);

		//寻找第一个叶子节点
		BiTreeNode *p = root;
		while (p->leftChild)
			p = p->leftChild;

		for (int i = 1; i <= leafCount; ++i)
		{
			if (i <= list.size())
				p->data = list[i];
			else
				p->data = INT_MAX;

			p = RightSibling(p->data);
		}
	}

	//创建深度为depth的完全二叉树<接口>
	template <typename T>
	void BiTree<T>::CreateBiTreeWithDepth(int depth)
	{
		CreateBiTreeWithDepth(root, depth);
	}

	//创建深度为depth的完全二叉树<实现>
	template <typename T>
	void BiTree<T>::CreateBiTreeWithDepth(typename BiTree<T>::BiTreeNode *&T, int depth)
	{
		if (depth != 0)
		{
			T = (BiTreeNode*)malloc(sizeof(BiTreeNode));
			T->leftChild = T->rightChild = nullptr;

			CreateBiTreeWithDepth(T->leftChild, depth - 1);
			CreateBiTreeWithDepth(T->rightChild, depth - 1);
		}
	}

	//前序创建<接口>
	template <typename T>
	void BiTree<T>::CreateBiTree_Preorder()
	{
		if (root != nullptr)
			ClearBiTree(root);

		CreateBiTree_Preorder(root);
	}

	//前序创建<实现>
	template <typename T>
	void BiTree<T>::CreateBiTree_Preorder(BiTreeNode* &t)
	{
		char temp;
		cin >> temp;

		DataType item = DataType(temp);

		if (item == (DataType)FinishFlag)
			t = nullptr;
		else
		{
			if (strcmp(typeid(T).name(), "int") == 0)
				item -= 48;

			t = (BiTreeNode *)malloc(sizeof(BiTreeNode));
			t->data = item;
			t->LTag = t->RTag = LINK;

			CreateBiTree_Preorder(t->leftChild);
			CreateBiTree_Preorder(t->rightChild);
		}
	}

	//根据已知 前序 和 中序 序列创建二叉树<接口>
	template <typename T>
	void BiTree<T>::CreateBiTree_Per_In(char *VLR, char *LVR, int n)
	{
		if (n != 0)
		{
			if (root != nullptr)
				ClearBiTree(root);

			CreateBiTree_Per_In(root, VLR, LVR, n);
		}
	}

	//根据已知 前序 和 中序 序列创建二叉树<实现>
	template <typename T>
	void BiTree<T>::CreateBiTree_Per_In(BiTreeNode *&t, char *VLR, char *LVR, int n)
	{
		t = nullptr;
		if (n != 0)
		{
			t = (BiTreeNode *)malloc(sizeof(BiTreeNode));
			t->data = VLR[0];
			t->LTag = t->RTag = LINK;

			int k = 0;
			while (VLR[0] != LVR[k])
				k++;

			CreateBiTree_Per_In(t->leftChild, VLR + 1, LVR, k);
			CreateBiTree_Per_In(t->rightChild, VLR + k + 1, LVR + k + 1, n - k - 1);
		}
	}

	//根据已知 后序 和 中序 序列创建二叉树<接口>
	template <typename T>
	void BiTree<T>::CreateBiTree_Post_In(char *LRV, char *LVR, int n)
	{
		if (n != 0)
		{
			if (root != nullptr)
				ClearBiTree(root);

			CreateBiTree_Post_In(root, LRV, LVR, n);
		}
	}

	//根据已知 后序 和 中序 序列创建二叉树<实现>--关键点(先入右树)
	template <typename T>
	void BiTree<T>::CreateBiTree_Post_In(BiTreeNode *&t, char *LRV, char *LVR, int n)
	{
		t = nullptr;
		if (n != 0)
		{
			int k = 0;
			while (LRV[n - 1] != LVR[k])
				k++;

			t = (BiTreeNode *)malloc(sizeof(BiTreeNode));
			t->data = LVR[k];
			t->LTag = t->RTag = LINK;

			CreateBiTree_Post_In(t->rightChild, LRV + k, LVR + k + 1, n - k - 1);
			CreateBiTree_Post_In(t->leftChild, LRV, LVR, k);
		}
	}

#ifdef THREADING
	//中序线索化<接口>
	template <typename T>
	void BiTree<T>::Threading_InOrder()
	{
		if (root != nullptr)
		{
			if (ThreadHead != nullptr)
				free(ThreadHead);

			//创建头结点
			ThreadHead = (BiTreeNode *)malloc(sizeof(BiTreeNode));
			ThreadHead->leftChild = root; ThreadHead->LTag = LINK;          //左孩子指针指向 根
			ThreadHead->rightChild = ThreadHead; ThreadHead->RTag = THREAD; //右孩子指针 回指

			BiTreeNode *pre = ThreadHead; //保存头结点指针
			Threading_InOrder(root, pre); //索引化

											//最后一个结点索引化
			pre->rightChild = ThreadHead;  pre->RTag = THREAD;
			//头结点右孩子指针指向最后一个结点
			ThreadHead->rightChild = pre;
		}
	}

	//中序线索化<实现>
	template <typename T>
	void BiTree<T>::Threading_InOrder(BiTreeNode *p, BiTreeNode *&pre)
	{
		if (p)
		{
			Threading_InOrder(p->leftChild, pre); //线索化左子树
			if (!p->leftChild) { p->LTag = THREAD; p->leftChild = pre; }      //寻找前驱
			if (!pre->rightChild) { pre->RTag = THREAD; pre->rightChild = p; } //寻找后继

			pre = p;
			Threading_InOrder(p->rightChild, pre); //线索化右子树
		}
	}
#endif // THREADING

	//判空
	template <typename T>
	bool BiTree<T>::Empty() const
	{
		return root == nullptr;
	}

	//获取深度
	template <typename T>
	int  BiTree<T>::GetDepth() const
	{
		return MaxDepth(root);
	}

	//计算深度
	template <typename T>
	int  BiTree<T>::MaxDepth(BiTreeNode *p) const
	{
		if (p == nullptr)
			return 0;

		int lh = MaxDepth(p->leftChild);
		int rh = MaxDepth(p->rightChild);

		return lh > rh ? lh + 1 : rh + 1;
	}

	//获取结点个数<接口>
	template <typename T>
	int  BiTree<T>::GetNodeNumber() const
	{
		return GetNodeNumber(root);
	}

	//获取结点个数<实现>
	template <typename T>
	int  BiTree<T>::GetNodeNumber(BiTreeNode *t) const
	{
		if (t == nullptr)
			return 0;
		else
		{
			return GetNodeNumber(t->leftChild) + GetNodeNumber(t->rightChild) + 1;
		}
	}

	//获取叶子节点个数<接口>
	template <typename T>
	int  BiTree<T>::GetLeafNodeNumber() const
	{
		return GetLeafNodeNumber(root);
	}

	//获取叶子节点个数<实现>
	template <typename T>
	int  BiTree<T>::GetLeafNodeNumber(BiTreeNode *t) const
	{
		if (t == nullptr)
			return 0;

		if (t->leftChild == nullptr && t->rightChild == nullptr)
			return 1;

		int left_LeafNum = GetLeafNodeNumber(t->leftChild);
		int right_leafNum = GetLeafNodeNumber(t->rightChild);

		return left_LeafNum + right_leafNum;
	}

	//判断两颗树是否有相同的结构<接口>
	template <typename T>
	bool BiTree<T>::IsSameStruct(const BiTree &t1, const BiTree &t2) const
	{
		return IsSameStruct(t1.root, t2.root);
	}

	//判断两颗树是否有相同的结构<实现>
	template <typename T>
	bool BiTree<T>::IsSameStruct(const BiTreeNode *t1, const BiTreeNode *t2) const
	{
		if (t1 == nullptr && t2 == nullptr)
			return true;
		else if (t1 == nullptr || t2 == nullptr)
			return false;
		
		bool left_result = IsSameStruct(t1->leftChild, t2->leftChild);
		bool right_result = IsSameStruct(t1->rightChild, t2->rightChild);

		return left_result && right_result;
	}

	//求二叉树的镜像<接口>
	template <typename T>
	void BiTree<T>::Mirror()
	{
		Mirror(root);
	}

	//求二叉树的镜像<实现>
	template <typename T>
	void BiTree<T>::Mirror(BiTreeNode *t)
	{
		if (t != nullptr)
		{
			//交换左右子树
			BiTreeNode *tmp = t->leftChild;
			t->leftChild = t->rightChild;
			t->rightChild = tmp;

			Mirror(t->leftChild);  //左子树镜像
			Mirror(t->rightChild); //右子树镜像
		}
	}

	//寻找最低公共祖先结点<接口>
	template <typename T>
	typename BiTree<T>::BiTreeNode* BiTree<T>::FindLCA(const BiTreeNode *tn1, const BiTreeNode *tn2)const
	{
		return FindLCA(root, tn1, tn2);
	}

	//寻找最低公共祖先结点<实现>
	//思路：
	    //我们可以用深度优先搜索，从叶子节点向上，标记子树中出现目标节点的情况。
		//如果子树中有目标节点，标记为那个目标节点，如果没有，标记为null。
		//显然，如果左子树、右子树都有标记，说明就已经找到最小公共祖先了。
		//如果在根节点为p的左右子树中找p、q的公共祖先，则必定是p本身。
	template <typename T>
	typename BiTree<T>::BiTreeNode* BiTree<T>::FindLCA(BiTreeNode *T, const BiTreeNode *tn1, const BiTreeNode *tn2)const
	{
		if (!T || T == tn1 || T == tn2)
			return T;

		BiTreeNode *left = FindLCA(T->leftChild, tn1, tn2);
		BiTreeNode *right = FindLCA(T->rightChild, tn1, tn2);
		if (left && right)
			return T;

		return left ? left : right;
	}

	//获取根结点
	template <typename T>
	typename BiTree<T>::BiTreeNode BiTree<T>::Root() const
	{
		return *root;
	}

	//清除树
	template <typename T>
	void BiTree<T>::ClearBiTree()
	{
		ClearBiTree(root);
	}

	//清除树
	template <typename T>
	void BiTree<T>::ClearBiTree(BiTreeNode* &t)
	{
		if (t == nullptr)
			return;
		else
		{
			ClearBiTree(t->leftChild);
			ClearBiTree(t->rightChild);
			free(t);
			t = nullptr;
		}
	}


	//寻找值等于x的结点<接口>
	template <typename T>
	typename BiTree<T>::BiTreeNode* BiTree<T>::FindNode(const DataType x) const
	{
		return FindNode(root, x);
	}

	//寻找值等于x的结点<实现>
	template <typename T>
	typename BiTree<T>::BiTreeNode* BiTree<T>::FindNode(BiTreeNode *t, const DataType x) const
	{
		if (t == nullptr)
			return NULL;

		if (t->data == x)
			return t;

		BiTreeNode *result = nullptr;

		result = FindNode(t->leftChild, x);
		if (result != nullptr)
			return result;

		result = FindNode(t->rightChild, x);
		if (result != nullptr)
			return result;

		return result;
	}

	//获取值等于x的结点的左孩子
	template <typename T>
	typename BiTree<T>::BiTreeNode* BiTree<T>::LeftChild(const DataType x) const
	{
		BiTreeNode *p = FindNode(x);
		if (!p)
			return NULL;

		if (!p->leftChild)
			return NULL;

		return p->leftChild;
	}

	//获取值等于x的结点的右孩子
	template <typename T>
	typename BiTree<T>::BiTreeNode* BiTree<T>::RightChild(const DataType x) const
	{
		BiTreeNode *p = FindNode(x);
		if (!p)
			return NULL;

		if (!p->rightChild)
			return NULL;

		return p->leftChild;
	}

	//获取值等于x的结点的 双亲<接口>
	template <typename T>
	typename BiTree<T>::BiTreeNode* BiTree<T>::Parent(const DataType x) const
	{
		return Parent(root, x);
	}

	//获取值等于x的结点的 双亲<实现>
	template <typename T>
	typename BiTree<T>::BiTreeNode* BiTree<T>::Parent(BiTreeNode *t, const DataType x) const
	{
		if (t == nullptr)
			return NULL;

		if (t->leftChild != nullptr && t->leftChild->data == x ||
			t->rightChild != nullptr && t->rightChild->data == x)
			return t;

		BiTreeNode *result = nullptr;

		if (t->leftChild)
			result = Parent(t->leftChild, x);
		if (result != nullptr)
			return result;

		result = nullptr;
		if (t->rightChild)
			result = Parent(t->rightChild, x);
		if (result != nullptr)
			return result;


		return NULL;
	}

	//获取值等于x的结点的右兄弟<接口>
	template <typename T>
	typename BiTree<T>::BiTreeNode* BiTree<T>::RightSibling(const DataType x) const
	{
		return RightSibling(root, x);
	}

	//获取值等于x的结点的右兄弟<实现>
	template <typename T>
	typename BiTree<T>::BiTreeNode* 
		BiTree<T>::RightSibling(typename BiTree<T>::BiTreeNode *const &T, const DataType x) const
	{
		if (T != nullptr){

			if (T->leftChild && T->leftChild->data == x)
				return T->rightChild;

			if (T->rightChild && T->rightChild->data == x){
				BiTreeNode tmp;
				tmp.data = T->data;
				T->data = 9999;
				BiTreeNode *p = Parent(9999);
				T->data = tmp.data;

				BiTreeNode *p2 = T;
				int iCount = 0;
				while (p->leftChild != p2)
				{
					++iCount;
					tmp.data = p->data;
					p->data = 9999;
					p2 = p;
					p = Parent(9999);
					p2->data = tmp.data;
					if (!p)
						return nullptr;
				}

				if (p) {
					BiTreeNode *q = p->rightChild;
					while (iCount--)
					{
						if (q)
							q = q->leftChild;
						else
							return nullptr;
					}
					return q->leftChild;
				}
			}

			BiTreeNode *ret = nullptr;
			ret = RightSibling(T->leftChild, x);
			if (ret)
				return ret;

			ret = RightSibling(T->rightChild, x);
			if (ret)
				return ret;
		}

		return nullptr;
	}

	//添加孩子(结点或树),LR是标记操作 左/右孩子 下同
	template <typename T>
	void BiTree<T>::InsertChile(BiTreeNode *p, int LR, BiTreeNode *c)
	{
		//必须保证p指向本树的某个结点，不然将发生未定义行为

		if (p == nullptr || c == nullptr)
			return;

		switch (LR)
		{
			//添加 左 孩子、树
		case 0:
		{
			if (p->leftChild == nullptr)
				p->leftChild = c;
		}
		break;
		//添加 右 孩子、树
		case 1:
		{
			if (p->rightChild == nullptr)
				p->rightChild = c;
		}
		break;
		}
	}

	//删除孩子(结点，或树)
	template <typename T>
	void BiTree<T>::DeletetChile(BiTreeNode *p, int LR)
	{
		//必须保证p指向本树的某个结点，不然将发生未定义行为

		if (p == nullptr)
			return;

		switch (LR)
		{
			//删除 左 孩子、树
		case 0:
		{
			if (p->leftChild != nullptr)
				ClearBiTree(p->leftChild);
		}
		break;
		//删除 右 孩子、树
		case 1:
		{
			if (p->rightChild != nullptr)
				ClearBiTree(p->rightChild);
		}
		break;
		}
	}

	//前序遍历(递归)<接口>
	template <typename T>
	void BiTree<T>::PreOrderTraverse(void(*Visit)(DataType))
	{
		cout << "前序遍历(递归):";
		PreOrderTraverse(root, Visit);
	}

	//前序遍历(递归)<实现>
	template <typename T>
	void BiTree<T>::PreOrderTraverse(BiTreeNode *& t, void(*Visit)(DataType))
	{
		if (t != nullptr)
		{
			Visit(t->data);

			PreOrderTraverse(t->leftChild, Visit);
			PreOrderTraverse(t->rightChild, Visit);
		}
	}

	//前序遍历(栈)--关键点(先入右树)
	template <typename T>
	void BiTree<T>::PreOrderTraverse_1(void(*Visit)(DataType))
	{
		cout << "前序遍历(栈):";

		if (root != nullptr)
		{
			BiTreeNode *p = root;
			stack<BiTreeNode*> Stack;
			Stack.push(p);

			while (!Stack.empty())
			{
				Visit(Stack.top()->data);
				p = Stack.top();
				Stack.pop();

				if (p->rightChild != nullptr) Stack.push(p->rightChild);
				if (p->leftChild != nullptr) Stack.push(p->leftChild);
			}
		}
	}

	//中序遍历(栈)
	template <typename T>
	void BiTree<T>::InOrderTraverse_1(void(*Visit)(DataType))
	{
		cout << "中序遍历(栈):";

		if (root != nullptr)
		{
			BiTreeNode *p = root;
			stack<BiTreeNode*> Stack;

			while (p || !Stack.empty())
			{
				if (p)
				{
					Stack.push(p);
					p = p->leftChild;
				}
				else
				{
					Visit(Stack.top()->data);
					p = Stack.top()->rightChild;
					Stack.pop();
				}
			}
		}
	}

	//后序遍历(栈)-借助标记Tag，右孩子返回才访问该结点
	template <typename T>
	void BiTree<T>::PostOrderTraverse_1(void(*Visit)(DataType))
	{
		cout << "后序遍历(栈):";

		if (root != nullptr)
		{
			BiTreeNode *p = root;
			stack<StkTreeNode> Stack;
			StkTreeNode sn;

			do
			{
				if (p != nullptr)
				{
					sn.ptr = p;
					sn.tag = L;
					Stack.push(sn);
					p = p->leftChild;
				}
				else
				{
					switch (Stack.top().tag)
					{
					case L:
						p = Stack.top().ptr->rightChild;
						Stack.top().tag = R;
						break;
					case R:
						Visit(Stack.top().ptr->data);
						Stack.pop();
						break;
					}
				}
			} while (!Stack.empty());
		}
	}

	//层遍历
	template <typename T>
	void BiTree<T>::LevelOrderTraverse(void(*Visit)(DataType))
	{
		cout << "层遍历(队列):";

		if (Empty())
			return;

		queue<BiTreeNode*> qe;
		qe.push(root);

		while (!qe.empty())
		{
			auto cur = qe.front();
			Visit(cur->data);
			qe.pop();

			if (cur->leftChild) qe.push(cur->leftChild);
			if (cur->rightChild) qe.push(cur->rightChild);
		}
	}

}
