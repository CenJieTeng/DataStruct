#include "LinkStack.h"

using std::cout; using std::cin; using std::endl;

LinkStack::LinkStack() : top(nullptr)
{

}

LinkStack::~LinkStack()
{

}

//判断栈是否为空
bool LinkStack::empty()
{
	return top == nullptr;
}

//入栈
void LinkStack::push(DataType x)
{
	auto p = new StackNode; //创建新结点

	p->data = x;
	p->next = top;
	top = p;
}

//出栈
DataType LinkStack::pop()
{
	//判断非空
	if (!empty())
	{
		auto p = top;       //p指向栈顶
		auto x = top->data; //x保存要返回的数据
		top = p->next;      //出栈
		free(p);            //释放栈顶

		return x;
	}
	else
	{
		cout << "下溢" << endl;
	}

	return NULL;
}

//取栈顶元素
DataType LinkStack::getTop()
{
	//判断非空
	if (!empty())
	{
		return top->data;
	}
	else
	{
		cout << "栈空，取不了元素" << endl;
	}

	return NULL;
}
