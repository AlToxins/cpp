#include"boundedblockingqueue.h"

int main() 
{
	int maxSize = 6;
	BoundedBlockingQueue queue(maxSize);
	//使用vector容器创建多个线程，模拟该程序在多个线程下的执行情况
	std::vector<std::thread> threadVector;
	int i = 0;
	while (i < maxSize+5) 
	{
		//创建生产者线程以及消费者线程
		std::thread threadAdd(&BoundedBlockingQueue::enqueue, std::ref(queue), i);
		std::thread threadDelete(&BoundedBlockingQueue::dequeue, std::ref(queue));
		//直接将线程对象转换为右值，避免创建临时线程对象，节省一次移动操作
		threadVector.push_back(std::move(threadAdd));
		threadVector.push_back(std::move(threadDelete));
		i++;
	}
	//使用循环等待所有线程结束，并从vector中弹出
	while (!threadVector.empty()) 
	{
		threadVector.back().join();
		threadVector.pop_back();
	}
	return 0;
}