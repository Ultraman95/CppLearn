#pragma once
#include <iostream>

//��C++�У����ǿ��԰�ֻ�����ڱ��̳ж�����ֱ�Ӵ��������������Ϊ������
//��Ϊ�������޷�ʵ����
class Animal {
public:
	Animal() {}
	~Animal() {}
	//���麯�����ڻ������������麯�������ڻ�����û�ж��壬��Ҫ���κ������඼Ҫ�����Լ���ʵ�ַ�����
	//�����������ٴ���һ�����麯�������ڴ��麯������һ���ǳ����ࡣ
	//��Ϊ���麯��
	virtual void doWork() = 0;
};



//��ҲΪ�������޷�ʵ����
//�����������
class Person : virtual public Animal{	
public:
	//���ֹ��캯�����Բ�д�����������Զ����Ĭ�Ϲ��캯��
	Person();
	~Person();
	virtual void play() = 0;
	virtual void go() {}
};



class School
{
public:
	//���캯��Ҫô����д��д�˾ͱ�����ʵ�֣�����ʵ��Ϊ��
	School() {}		//�˴��ǿ�ʵ��
	School(std::string name);
	~School();

private:
	std::string name;
};

//�����޷����̳�
class finalClass final{};


class Teacher {
	//�����Դ�Ĭ�ϵ��޲ι��캯��
	//����Լ������˹��캯�����������вλ����޲Σ���Ĭ�ϵľ�û����
};

