#include"factory.h"

Make* Factory::mk = nullptr;		//��̬��Ա����ֻ��һ��ʵ������ͷ�ļ����ܱ�����ļ������������Ҫ��Դ�ļ��ж���
Make* Factory::createProduct(std::string select_id) {
	mk = nullptr;
	if (select_id == "��") {
		mk = new MakeTrain();
	}
	else {
		mk = new MakePlane();
	}
	return mk;
}