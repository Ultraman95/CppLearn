#pragma once
#include "Parent.h"
#include <string>


//子类继承父类的三种方式：pubic , protected , private
//public继承，父类的成员属性保持不变
//private继承，父类的成员属性全部变成private
//protected继承，父类的private成员属性保持不变，其他成员属性变为protected
//基本使用public，其他语言java，c#都只有public继承

class Child : public Parent
{
private:
    virtual void pureVitual();

	std::string name;

	const std::string sex;

	int &age;

	School school;
public:
	//析构函数只能有一个，无法重载
    ~Child();

	//构造原则如下：
	//1. 如果子类没有定义构造方法，则调用父类的无参数的构造方法。
	//2. 如果子类定义了构造方法，不论是无参数还是带参数，在创建子类的对象的时候, 首先执行父类无参数的构造方法，然后执行自己的构造方法。
	//3. 在创建子类对象时候，如果子类的构造函数没有显示调用父类的构造函数，则会调用父类的默认无参构造函数。
	//4. 在创建子类对象时候，如果子类的构造函数没有显示调用父类的构造函数且父类自己提供了无参构造函数，则会调用父类自己的无参构造函数。
	//5. 在创建子类对象时候，如果子类的构造函数没有显示调用父类的构造函数且父类只定义了自己的有参构造函数，则会出错（如果父类只有有参数的构造方法，则子类必须显示调用此带参构造方法）。
	//6. 如果子类调用父类带参数的构造方法，需要用初始化列表的方式。
	//结论：子类构造函数必须要调用父类的构造函数（无论显式还是隐式），本质原因在于继承的性质决定了必须先有父再有子
	
	//构造函数可以重载
	Child(std::string name, std::string country, std::string sex, int &age);

	//此函数只能调用const函数，同时不可以修改成员变量，所以是只读的概念
	std::string getName() const;

	//override要写在后面
	//override明确地表示一个函数是对基类中一个虚函数的重载。
	//更重要的是，它会检查基类虚函数和派生类中重载函数的签名不匹配问题。如果签名不匹配，编译器会发出错误信息。
	void sayHello() override;

	//void reply() override {}		//Error,没有重写任何基类需要重载的方法

	//override检查函数的签名匹配，包括const
	//final说明eat方法无法在被子类重载
	void eat() const override final {}


	void drive() override {}
};


//private成员属性，只能在本类中被调用，其他类和全部实例都无法调用
//protected成员属性，只能在本类和子类中被调用，其他类和全部实例都无法调用
//public成员属性，都可以被调用