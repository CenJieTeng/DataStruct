#include "SeqStack.h"

using std::cout; using std::cin; using std::endl;

SeqStack::SeqStack() : top(-1)
{

}

SeqStack::~SeqStack()
{

}

//判栈空
bool SeqStack::empty()
{
	return top == -1;
}

//判栈满
bool SeqStack::full()
{
	return top == StackSize - 1;
}

//入栈
void SeqStack::push(DataType x)
{
	//判断是否非满
	if (!full())
	{
		top++;
		data[top] = x;
	}
	else
	{
		cout << "上溢" << endl;
	}
}

//出栈
DataType SeqStack::pop()
{
	//判断是否非空
	if (!empty())
	{
		return data[top--];
	}
	else
	{
		throw std::underflow_error("栈空，计算下溢");
	}
}

//取栈顶元素
DataType SeqStack::getTop()
{
	//判断是否非空
	if (!empty())
	{
		return data[top];
	}
	else
	{
		throw std::overflow_error("栈空，计算上溢");
	}
}
