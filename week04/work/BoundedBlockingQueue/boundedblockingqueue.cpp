#include"boundedblockingqueue.h"



BoundedBlockingQueue::BoundedBlockingQueue(int capacity) 
	:m_maxSize(capacity)
{
	std::cout << "Start BoundedBlockingQueue" << std::endl;
}

void BoundedBlockingQueue::enqueue(int element) 
{
	//创建unique_lock对象作为wait的第一个参数使用，若第二个参数为假，则在wait内部会调用unique_lock的unlock函数解锁队列资源，并使当前进程阻塞
	std::unique_lock<std::mutex>lk(m_mtx);
	//若队列为满，则条件变量m_full调用wait函数引发阻塞，需要通过其他线程调用dequeue函数，处理掉队列中的元素，并通过notify_one唤醒条件变量m_full
	m_full.wait(lk, [this] {return m_queue.size() != m_maxSize; });
	m_queue.push(element);
	std::cout << "Add element: "<< element << "; thread id is: " << std::this_thread::get_id() << std::endl;
	m_empty.notify_one();
}

int BoundedBlockingQueue::dequeue() 
{
	std::unique_lock<std::mutex>lk(m_mtx);
	m_empty.wait(lk, [this] {return !m_queue.empty(); });
	int temp = m_queue.front();
	std::cout << "Delete element: "<< temp << "; thread id is: " << std::this_thread::get_id() <<std::endl;
	m_queue.pop();
	m_full.notify_one();
	return temp;
}

int BoundedBlockingQueue::size() 
{
	std::unique_lock<std::mutex>lk(m_mtx);
	return m_queue.size();
}