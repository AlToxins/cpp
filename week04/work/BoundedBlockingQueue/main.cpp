#include"boundedblockingqueue.h"

int main() 
{
	int maxSize = 6;
	BoundedBlockingQueue queue(maxSize);
	//ʹ��vector������������̣߳�ģ��ó����ڶ���߳��µ�ִ�����
	std::vector<std::thread> threadVector;
	int i = 0;
	while (i < maxSize+5) 
	{
		//�����������߳��Լ��������߳�
		std::thread threadAdd(&BoundedBlockingQueue::enqueue, std::ref(queue), i);
		std::thread threadDelete(&BoundedBlockingQueue::dequeue, std::ref(queue));
		//ֱ�ӽ��̶߳���ת��Ϊ��ֵ�����ⴴ����ʱ�̶߳��󣬽�ʡһ���ƶ�����
		threadVector.push_back(std::move(threadAdd));
		threadVector.push_back(std::move(threadDelete));
		i++;
	}
	//ʹ��ѭ���ȴ������߳̽���������vector�е���
	while (!threadVector.empty()) 
	{
		threadVector.back().join();
		threadVector.pop_back();
	}
	return 0;
}