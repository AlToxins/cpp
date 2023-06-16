#include"ksmartpointuni.cpp"

int main() {
	KSmartPointUni<int>obj(new int(210));
	KSmartPointUni<int>obj2(new int(10000));
	//obj2 = obj;		//当进行此操作时，会多调用一次析构函数，导致出现异常（直接复制的话实际上只申请了一处空间，但是析构了两次）
	//KSmartPointUni<int>obj3(obj);		// 不能执行，obj的类型不符合参数要求
	obj2.display();
	return 0;
}