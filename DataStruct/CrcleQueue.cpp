#include "CrcleQueue.h"

using std::cout; using std::cin; using std::endl;

////SeqQueue
//CrcleQueue::CrcleQueue() : front(-1), rear(-1)
//{
//
//}

CrcleQueue::CrcleQueue() : front(0), rear(0)
{

}

CrcleQueue::~CrcleQueue()
{

}

//判断队空
bool CrcleQueue::empty()
{
	return front == rear;
}

//判断队满
bool CrcleQueue::full()
{
	//return rear == QueueMaxSize - 1; //SeqQueue
	return front == (rear + 1) % QueueMaxSize;
}

//入队
void CrcleQueue::enQueue(DataType x)
{
	//判断非满
	if (!full())
	{
		//rear++;  //SeqQueue
		rear = (rear + 1) % QueueMaxSize;
		data[rear] = x;
	}
	else
	{
		cout << "上溢" << endl;
	}
}

//出队
DataType CrcleQueue::delQueue()
{
	//判断非空
	if (!empty())
	{
		//front++;   //SeqQueue
		front = (front + 1) % QueueMaxSize;
		return data[front];
	}
	else
	{
		cout << "下溢" << endl;
	}

	return NULL;
}

//取队头元素
DataType CrcleQueue::getHead()
{
	//判断非空
	if (!empty())
	{
		//return data[front+1]; //SeqQueue
		return data[(front + 1) % QueueMaxSize];
	}
	else
	{
		cout << "队空，无法取队头元素" << endl;
	}

	return NULL;
}
