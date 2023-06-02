//------------------------------------------------------------------------------
//线程间通信：使用条件变量实现线程之间的通信
// 理由：条件变量可以让一个或多个线程等待某个条件成立，然后被另一个线程通知运行。
//		这样就可以实现生产者-消费者模式，即一个线程（或多个线程）生产数据并放入队
//		列中，然后通知一个或多个线程消费数据，从队列中取出。这种模式可以有效平衡
//		生产者和消费者之间的速度差异，避免队列过满或为空的情况。
//------------------------------------------------------------------------------
#ifndef __BOUNDEDBLOCKINGQUEUE_H__
#define __BOUNDEDBLOCKINGQUEUE_H__

#include<queue>
#include<iostream>
#include<mutex>
#include<thread>
#include<condition_variable>
#include<vector>

class BoundedBlockingQueue {
public:
	BoundedBlockingQueue(int capacity);

	// 禁止拷贝构造和运算符赋值，对象包含独占资源和状态，若被复制可能会导致逻辑错误
	BoundedBlockingQueue(const BoundedBlockingQueue&) = delete;
	BoundedBlockingQueue& operator=(const BoundedBlockingQueue&) = delete;

	void enqueue(int element);
	int dequeue();
	int size();
private:
	std::queue<int> m_queue;
	int m_maxSize;
	std::condition_variable m_empty;
	std::condition_variable m_full;
	std::mutex m_mtx;
};

#endif