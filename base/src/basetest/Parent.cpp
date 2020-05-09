#include "Parent.h"

Parent::Parent()
{
	std::cout << "Parent() Default Constructor !" << std::endl;
}

Parent::Parent(std::string country) {
	this->country = country;
	//一个类的虚函数在它自己的构造函数和析构函数中被调用的时候，它们就变成普通函数了，不“虚”了。
	//也就是说不能在构造函数和析构函数中让自己“多态”。
	sayHello();
}

Parent::~Parent()
{
	int a = 0;
}

void Parent::normalVitual() {
	//这函数一定要实现的，哪怕是空的
}

void Parent::sayHello() {
	std::cout << "I'm Parent, Hello !" << std::endl;
}