//项目：顺序栈
//创建时间：2018/7/17 13:20
//完成时间：2018/7/17 17:25
//最后一次修改时间：
//修改次数：
//修改原因：
//
//
//作者：CenJieTeng
//QQ: 2271369683
#pragma once
#ifndef SEQSTACK_H
#define SEQSTACK_H
#include <iostream>
#include <stdexcept>
#define StackSize 100

typedef int DataType;
class SeqStack
{
public:
	SeqStack();
	~SeqStack();

public:
	bool empty();        //判断栈是否为空
	bool full();         //判栈满
	void push(DataType); //入栈
	DataType pop();      //出栈
	DataType getTop();   //取栈顶元素

private:
	DataType data[StackSize];
	int top;             //栈顶
};



#endif // !STACK_H
