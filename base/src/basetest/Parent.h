#pragma once
#include <iostream>
#include "Person.h"

class Parent : public Person
{
private:
	//˽���麯��Ҳ���Ա���������
	virtual void drive() {}

	std::string country;
public:
	Parent();
	Parent(std::string country);
	~Parent();

	//ֱ����ͷ�ļ��еĿ�ʵ�֣������ź��治Ҫ��ð��
	//�˷������Ա��������أ����ڲ����麯�������Լ�ʹ����Ҳ�޷�����ʱ��
	void reply() {}

	virtual void normalVitual();   //����麯�������ڱ�����ʵ��

	virtual void sayHello();

	virtual void eat() const {}

	virtual void pureVitual() = 0; //������麯�����������ʵ�֣�ͬʱ�����ǳ����࣬�޷�ʵ��������ͬjava�ӿڵ�����

	//����̳��˳����࣬��ȥʵ�ָ���Ĵ��麯�����������Ȼ�ǳ����࣬�޷�ʵ����
	void play() override {
		//��ʵ��
	}
	void doWork() override {
		//��ʵ��
	}
};



