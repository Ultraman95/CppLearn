#include "Child.h"

//不需要显示地调用基类的析构函数，系统会自动隐式调用
//析构函数的调用次序与构造函数相反。
Child::~Child()
{
	std::cout << "~Child()" << std::endl;
}


//必须使用初始化列表的三种情况
//1.继承有参的类
//2.当类中定义了类成员对象,不是指针
//3.当类成员中含有一个const对象时，或者是一个引用时，他们也必须要通过成员初始化列表进行初始化，因为这两种对象要在声明后马上初始化，而在构造函数中，做的是对他们的赋值，这样是不被允许的。

//C++规定，对象的成员变量的初始化动作发生在进入构造函数本体之前。所以使用初始化列表的方式会少一步赋值，效率更高
Child::Child(std::string name, std::string country, std::string sex, int &age) : Parent(country), sex(sex), 
																					age(age), school("lz")
{
	//this->sex = sex;	//Error,必须使用初始化列表方式
	this->name = name;	//这个是赋值，所以name使用初始化列表会更高效
	Parent::sayHello();
}


void Child::pureVitual(){
    //子类必须实现纯虚函数
}


std::string Child::getName() const {
	return this->name;
}

void Child::sayHello() {
	std::cout << "I'm a Child , Hello !" << std::endl;
}