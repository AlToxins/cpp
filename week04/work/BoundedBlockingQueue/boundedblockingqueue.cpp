#include"boundedblockingqueue.h"



BoundedBlockingQueue::BoundedBlockingQueue(int capacity) 
	:m_maxSize(capacity)
{
	std::cout << "Start BoundedBlockingQueue" << std::endl;
}

void BoundedBlockingQueue::enqueue(int element) 
{
	//����unique_lock������Ϊwait�ĵ�һ������ʹ�ã����ڶ�������Ϊ�٣�����wait�ڲ������unique_lock��unlock��������������Դ����ʹ��ǰ��������
	std::unique_lock<std::mutex>lk(m_mtx);
	//������Ϊ��������������m_full����wait����������������Ҫͨ�������̵߳���dequeue����������������е�Ԫ�أ���ͨ��notify_one������������m_full
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