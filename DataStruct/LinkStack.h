//项目：链栈
//创建时间：2018/8/15 16:00
//完成时间：2018/8/15 16:49
//最后一次修改时间：
//修改次数：
//修改原因：
//
//
//作者：CenJieTeng
//QQ: 2271369683
#pragma once
#ifndef LINKSTACK_H
#define LINKSTACK_H
#include <iostream>

typedef int DataType;
typedef struct StackNode
{
	DataType data;
	StackNode *next;
}StackNode;

class LinkStack
{
public:
	LinkStack();
	~LinkStack();

public:
	bool empty();        //判断栈是否为空
	void push(DataType); //入栈
	DataType pop();      //出栈
	DataType getTop();   //取栈顶元素

private:
	StackNode *top;
};


#endif // !LINKSTSCK_H
