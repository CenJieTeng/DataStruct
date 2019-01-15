#include "Tree.h"

using std::cout; using std::cin; using std::endl;

Tree::Tree() : root(nullptr), FinishFlag('#')
{
}

Tree::~Tree()
{
	ClearTree(root);
}

void Tree::CreateTree()
{
	CreateTree(root);
}

//创建树
void Tree::CreateTree(TreeNode *&t)
{
	DataType item;
	cin >> item;
	
	if (item == FinishFlag)
		t = nullptr;
	else
	{
		t = (TreeNode *)malloc(sizeof(TreeNode));
		t->data = item;
	
		CreateTree(t->Child);
		CreateTree(t->Sibling);
	}
}

//清除树
void Tree::ClearTree()
{
	ClearTree(root);
}

//清除树
void Tree::ClearTree(TreeNode *t)
{
	if (t == nullptr)
		return;
	else
	{
		ClearTree(t->Child);
		ClearTree(t->Sibling);
		free(t);
		t = nullptr;
	}
}

//获取值等于x的结点
TreeNode* Tree::FindNode(const DataType x) const
{
	return FindNode(root, x);
}

//获取值等于x的结点
TreeNode* Tree::FindNode(TreeNode *t, const DataType x) const
{
	if (t == nullptr)
		return nullptr;

	if (t->data == x)
		return t;

	TreeNode *result = nullptr;
	result = FindNode(t->Child, x);
	if (result != nullptr)
		return result;

	result = FindNode(t->Sibling, x);
	if (result != nullptr)
		return result;

	return nullptr;
}

//前序遍历(递归)<接口>
void Tree::PreOrderTraverse(void(*Visit)(DataType))
{
	cout << "前序遍历:";

	PreOrderTraverse(root, Visit);
}

//前序遍历(递归)<实现>
void Tree::PreOrderTraverse(TreeNode *&t, void(*Visit)(DataType))
{
	if (t != nullptr)
	{
		Visit(t->data);

		PreOrderTraverse(t->Child, Visit);
		PreOrderTraverse(t->Sibling, Visit);
	}
}
