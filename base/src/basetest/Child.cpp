#include "Child.h"

//����Ҫ��ʾ�ص��û��������������ϵͳ���Զ���ʽ����
//���������ĵ��ô����빹�캯���෴��
Child::~Child()
{
	std::cout << "~Child()" << std::endl;
}


//����ʹ�ó�ʼ���б���������
//1.�̳��вε���
//2.�����ж��������Ա����,����ָ��
//3.�����Ա�к���һ��const����ʱ��������һ������ʱ������Ҳ����Ҫͨ����Ա��ʼ���б���г�ʼ������Ϊ�����ֶ���Ҫ�����������ϳ�ʼ�������ڹ��캯���У������Ƕ����ǵĸ�ֵ�������ǲ�������ġ�

//C++�涨������ĳ�Ա�����ĳ�ʼ�����������ڽ��빹�캯������֮ǰ������ʹ�ó�ʼ���б�ķ�ʽ����һ����ֵ��Ч�ʸ���
Child::Child(std::string name, std::string country, std::string sex, int &age) : Parent(country), sex(sex), 
																					age(age), school("lz")
{
	//this->sex = sex;	//Error,����ʹ�ó�ʼ���б�ʽ
	this->name = name;	//����Ǹ�ֵ������nameʹ�ó�ʼ���б�����Ч
	Parent::sayHello();
}


void Child::pureVitual(){
    //�������ʵ�ִ��麯��
}


std::string Child::getName() const {
	return this->name;
}

void Child::sayHello() {
	std::cout << "I'm a Child , Hello !" << std::endl;
}