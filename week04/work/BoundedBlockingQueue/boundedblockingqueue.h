//------------------------------------------------------------------------------
//�̼߳�ͨ�ţ�ʹ����������ʵ���߳�֮���ͨ��
// ���ɣ���������������һ�������̵߳ȴ�ĳ������������Ȼ����һ���߳�֪ͨ���С�
//		�����Ϳ���ʵ��������-������ģʽ����һ���̣߳������̣߳��������ݲ������
//		���У�Ȼ��֪ͨһ�������߳��������ݣ��Ӷ�����ȡ��������ģʽ������Чƽ��
//		�����ߺ�������֮����ٶȲ��죬������й�����Ϊ�յ������
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

	// ��ֹ����������������ֵ�����������ռ��Դ��״̬���������ƿ��ܻᵼ���߼�����
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