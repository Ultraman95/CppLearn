#pragma once
#include <iostream>

//在C++中，我们可以把只能用于被继承而不能直接创建对象的类设置为抽象类
//此为抽象类无法实例化
class Animal {
public:
	Animal() {}
	~Animal() {}
	//纯虚函数是在基类中声明的虚函数，它在基类中没有定义，但要求任何派生类都要定义自己的实现方法。
	//抽象类中至少存在一个纯虚函数；存在纯虚函数的类一定是抽象类。
	//此为纯虚函数
	virtual void doWork() = 0;
};



//此也为抽象类无法实例化
//父类是虚基类
class Person : virtual public Animal{	
public:
	//此种构造函数可以不写，编译器会自动添加默认构造函数
	Person();
	~Person();
	virtual void play() = 0;
	virtual void go() {}
};



class School
{
public:
	//构造函数要么都不写，写了就必须有实现，哪怕实现为空
	School() {}		//此处是空实现
	School(std::string name);
	~School();

private:
	std::string name;
};

//此类无法被继承
class finalClass final{};


class Teacher {
	//此类自带默认的无参构造函数
	//如果自己定义了构造函数（无论是有参还是无参），默认的就没有了
};

