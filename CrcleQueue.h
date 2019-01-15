//项目：循环队列，包含顺序队列的代码
//创建时间：2018/8/16 17:12
//完成时间：2018/8/16 18:00
//最后一次修改时间：
//修改次数：
//修改原因：
//
//
//作者：CenJieTeng
//QQ: 2271369683
#pragma once
#ifndef CRCLEQUEUE_H
#define CRCLEQUEUE_H
#include <iostream>
#define QueueMaxSize 100

typedef int DataType;
class CrcleQueue
{
public:
	CrcleQueue();
	~CrcleQueue();

public:
	bool empty();              //判断队空
	bool full();               //判断队满
	void enQueue(DataType);    //入队
	DataType delQueue();       //出队
	DataType getHead();        //取队头元素

private:
	DataType data[QueueMaxSize];
	int front, rear;
};


#endif // !CRCLEQUEUE_H
