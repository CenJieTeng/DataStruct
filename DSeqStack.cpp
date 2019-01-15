#include "DSeqStack.h"

using std::cout; using std::cin; using std::endl;

DSeqStack::DSeqStack() : top1(-1), top2(StackSize)
{

}

DSeqStack::~DSeqStack()
{

}

//判断栈是否为空
bool DSeqStack::empty()
{
	auto i = tool1();

	if (i == 1)
	{
		return top1 == -1;
	}
	else
	{
		return top2 == StackSize;
	}
}

//判栈满
bool DSeqStack::full()
{
	return top1 + 1 == top2;
}

//入栈
void DSeqStack::push(DataType x)
{
	//判断非满
	if (!full())
	{
		auto i = tool1();

		if (i == 1)
		{
			top1++;
			data[top1] = x;
		}
		else
		{
			top2--;
			data[top2] = x;
		}
	}
	else
	{
		cout << "上溢" << endl;
	}
}

//出栈
DataType DSeqStack::pop()
{
	auto i = tool1();

	if (i == 1)
	{
		//判断非空
		if (top1 != -1)
		{
			return data[top1--];
		}
		else
		{
			cout << "下溢" << endl;
		}
	}
	else
	{
		//判断非空
		if (top2 != StackSize)
		{
			return data[top1++];
		}
		else
		{
			cout << "下溢" << endl;
		}
	}

	return NULL;
}

//取栈顶元素
DataType DSeqStack::getTop()
{
	auto i = tool1();

	if (i == 1)
	{
		//判断非空
		if (top1 != -1)
		{
			return data[top1];
		}
		else
		{
			cout << "栈空，取不了元素" << endl;
		}
	}
	else
	{
		//判断非空
		if (top2 != StackSize)
		{
			return data[top1];
		}
		else
		{
			cout << "栈空，取不了元素" << endl;
		}
	}

	return NULL;
}

//判断要操作哪个栈
int DSeqStack::tool1()
{
	cout << "输入想要操作的栈1/2" << endl;
	int i = 0;
	cin >> i;

	while (i != 1 && i != 2)
	{
		cout << "输入有误请重新输入" << endl;
		cin >> i;
	}

	return i;
}
