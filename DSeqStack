//项目：双栈
//创建时间：2018/8/14 21:20
//完成时间：2018/8/14 22:28
//最后一次修改时间：
//修改次数：
//修改原因：
//
//
//作者：CenJieTeng
//QQ: 2271369683
#pragma once
#ifndef DSEQSTACK
#define DSEQSTACK
#include <iostream>
#define StackSize 100

typedef int DataType;
class DSeqStack
{
public:
	DSeqStack();
	~DSeqStack();

public:
		bool empty();        //判断栈是否为空
		bool full();         //判栈满
		void push(DataType); //入栈
		DataType pop();      //出栈
		DataType getTop();   //取栈顶元素

private:
	int tool1();             //判断要操作哪个栈

private:
	DataType data[StackSize];
	int top1, top2;
};

#endif // !DSEQSTACK
