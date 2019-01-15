//项目：树(孩子 兄弟表示法)
//创建时间：2017/12/6 20:15
//完成时间：?
//最后一次修改时间：
//修改次数：
//修改原因：
//
//
//作者：CenJieTeng
//QQ: 2271369683
#pragma once
#ifndef TREE_H
#define TREE_H
#include <iostream>

typedef int DataType;
struct TreeNode
{
	DataType data;
	TreeNode *Child, *Sibling;
};

class Tree
{
	friend class MGraph;
	template <typename T> friend class LinkGraph;
public:
	Tree();
	~Tree();

public:
	void CreateTree();                                   //创建树
	void ClearTree();                                    //清除树
	TreeNode* FindNode(const DataType x) const;          //获取值等于x的结点

	//树的遍历
	void PreOrderTraverse(void(*Visit)(DataType));       //前序遍历,和二叉树的前序遍历一样(递归)<接口>

private:
	void CreateTree(TreeNode* &t);                                  //创建树
	void Tree::ClearTree(TreeNode *t);                              //清除树
	TreeNode* FindNode(TreeNode *t, const DataType x) const;        //获取值等于x的结点
	void PreOrderTraverse(TreeNode *&t, void(*Visit)(DataType));    //前序遍历，递归法<实现>

private:
	TreeNode *root;
	char FinishFlag;
};


#endif // !TREE_H
