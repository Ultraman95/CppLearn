#pragma once
#include <iostream>
#include "Person.h"

class Parent : public Person
{
private:
	//私有虚函数也可以被子类重载
	virtual void drive() {}

	std::string country;
public:
	Parent();
	Parent(std::string country);
	~Parent();

	//直接在头文件中的空实现，大括号后面不要加冒号
	//此方法可以被子类重载，由于不是虚函数，所以即使重载也无法运行时绑定
	void reply() {}

	virtual void normalVitual();   //这个虚函数必须在本类中实现

	virtual void sayHello();

	virtual void eat() const {}

	virtual void pureVitual() = 0; //这个纯虚函数，子类必须实现，同时本类是抽象类，无法实例化，等同java接口的作用

	//如果继承了抽象类，不去实现父类的纯虚函数，则此类依然是抽象类，无法实例化
	void play() override {
		//空实现
	}
	void doWork() override {
		//空实现
	}
};



