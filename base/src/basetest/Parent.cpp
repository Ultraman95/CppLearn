#include "Parent.h"

Parent::Parent()
{
	std::cout << "Parent() Default Constructor !" << std::endl;
}

Parent::Parent(std::string country) {
	this->country = country;
	//һ������麯�������Լ��Ĺ��캯�������������б����õ�ʱ�����Ǿͱ����ͨ�����ˣ������顱�ˡ�
	//Ҳ����˵�����ڹ��캯�����������������Լ�����̬����
	sayHello();
}

Parent::~Parent()
{
	int a = 0;
}

void Parent::normalVitual() {
	//�⺯��һ��Ҫʵ�ֵģ������ǿյ�
}

void Parent::sayHello() {
	std::cout << "I'm Parent, Hello !" << std::endl;
}