#include"ksmartpointuni.cpp"

int main() {
	KSmartPointUni<int>obj(new int(210));
	KSmartPointUni<int>obj2(new int(10000));
	//obj2 = obj;		//�����д˲���ʱ��������һ���������������³����쳣��ֱ�Ӹ��ƵĻ�ʵ����ֻ������һ���ռ䣬�������������Σ�
	//KSmartPointUni<int>obj3(obj);		// ����ִ�У�obj�����Ͳ����ϲ���Ҫ��
	obj2.display();
	return 0;
}