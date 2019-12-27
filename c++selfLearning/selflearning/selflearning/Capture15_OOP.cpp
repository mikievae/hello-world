﻿#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <functional>
#include <sstream>

using namespace std;
/*
15、面向对象程序设计
1.OOP:概述（object-oriented programming）
面向对象程序成绩的核心思想是：
数据抽象-将类的接口与实现分离
继承-可以定义相似的类型并对其相似关系建模
动态绑定-可以一定程度上忽略相似类型的区别，而以统一的方式使用他们的对象

2.定义基类和派生类
基类通过在其成员函数的声明语句之前加上关键字virtual使得该函数执行动态绑定。也就是说当我们使用指针或者引用来调用虚函数时，该调用将动态绑定。
任何构造函数之外的非静态函数都可以是虚函数。
关键字virtual只能出现在类内部的声明语句之前，而不能用于类的外部的函数定义。
protected访问说明符：派生类可以访问基类的protected成员，同时禁止其他用户访问。
private访问说明符，只有类自身可以访问，派生类和其他用户都不能访问。
public访问说明符，所有用户都可以访问。
如果派生类没有覆盖基类中的某个虚函数，则该虚函数的行为类似于其他普通成员，派生类会直接继承其在基类中的版本。
在派生类对象中含有与其基类对应的组成部分，这一事实是继承的关键所在，也是基类引用和指针可以指向派生类引用和指针的原因。
派生类构造函数，最好使用基类的构造函数初始化基类成员，自己初始化派生类成员。
被用作基类的类，如果想把某个类作为基类，则该类必须已经定义而非仅仅声明。也就是说派生类想要使用基类的成员，就必须知道它们是什么。同时也包含了一个隐藏关系，即一个类不能派生它本身。
防止继承的发生 可以在定义时在class名后面加final
静态类型：在编译时是已知的，它是变量声明时的类型或表达式生成的类型。
动态类型：动态类型则是变量或者表达式表示的内存中的对象的类型。动态类型知道运行时才可知；
如果表达式既不是指针也不是引用，那么动态类型和静态类型永远保持一致。
不存在基类向派生类的隐式类型转换，除非用static_cast来强制覆盖掉编译器的检查工作。
派生类向基类的自动类型转换只针对指针或引用类型。在派生类对象和基类对象中不存在这样的转换。使用构造/拷贝/移动操作（这些操作使用引用）传递一个派生类的对象，会调用基类的函数。而且只对基类部分有效，派生类部分被忽略掉。

3.虚函数
一个函数被声明称虚函数，则在所有派生类中它都是虚函数。一个派生类如果覆盖了某个继承而来的虚函数，则他的形参必须与基类一致。并且返回值也需要一致除非虚函数返回类型时类本身的引用或指针。
也就是说D由B派生，则基类中的虚函数可以返回B*而派生类对应函数可以返回D*，只不过这样的返回类型要求D到B的类型转换时可访问的。
override，只有虚函数才可以用override.
override和final在形参列表(包括const或引用修饰符)以及尾置返回类型之后。
和其他函数一样，虚函数也可以由默认实参，且实参值由调用的静态类型决定。也就是说我们用基类的引用或指针调用函数，则使用基类中定义的默认实参，即使实际运行的是派生类中的函数版本也是如此。

4.抽象基类（含有(或者未经覆盖直接继承)纯虚函数的类）
在函数体的尾置（声明语句分号之前）书写=0就可以将一个虚函数说明为纯虚函数。其中=0 也只能出现在类内部的虚函数声明语句处。我们可以为纯虚函数提供定义，不过函数体必须定义在类的外部。
不能创建抽象基类的对象。
我们不能直接创建一个抽象基类对象，因为不能定义该对象，但是可以定义抽象基类的派生类对象，前提是这些类覆盖了抽象基类的纯虚函数。(因为如果不覆盖的话，还是纯虚函数，还是抽象基类)

5.访问控制与继承
public, protected, private继承对于派生类的成员及友元能否访问直接基类的成员没有什么影响。对基类成员的访问权限只跟基类中的访问说明符有关。
派生访问说明符的目的是控制派生类用户对于基类成员的访问权限。
假定D继承自B:
-当D公有继承B时,用户代码才能使用派生类向基类的转换。否则用户代码不能使用。
-不论D怎样继承B,D的成员函数和友元都能使用派生类向基类的转换；
-如果D非私有继承B,则D的派生类的成员和友元可以使用D向B的类型转换；反之，D私有继承B则不能使用。
TIP:对于代码中的某个节点来说，如果基类的公有成员是可访问的，则派生类向基类的类型转换也是可访问的；反之则不行。
可以用using声明改变成员的可访问性。且在pubilc中声明，就相当于public的,以此类推。
using改变的必须是当前位置可以访问的对象。
struct的默认继承是public，class的默认继承是private；

6.继承中的类作用域
在存在继承关系时，派生类的作用域嵌套在其基类的作用域之内。也就是说当一个“名字”在派生类的作用域内无法正确解析时，则编译器将继续在外城的基类作用域中寻找该名字的定义。
一个对象、引用、指针的静态类型决定了该对象的哪些成员是可见的。即使静态类型和动态类型不一致时也是这样。
派生类的成员将隐藏同名的基类成员。即使派生类成员和基类成员的参数列表不一样，基类成员依然会被隐藏掉。
只有虚函数会动态绑定，一般函数都是静态绑定。也就是书如果用指针或引用调用非虚函数，实际调用的版本由指针或引用的静态类型决定。
成员函数无论是否是虚函数都能被重载，如果派生类希望所有的重载版本对它来收都是可见的，那么就需要覆盖所有的版本，或者一个也不覆盖。
如果想要重载基类中的重载集合的一部分函数，可以用using声明指定一个名字，而不指定参数列表，就可以把所有版本的重载实例添加到派生类作用域中了。这样就只需要定义其特有类就行了。

7.构造函数与拷贝控制
基类的析构函数通常为虚函数。之前介绍过一个准则，如果一个类需要析构函数，那么也需要拷贝和赋值操作。基类的析构函数并不遵循上述原则。
在构造函数和析构函数中调用虚函数时，我们应该执行与构造函数或析构函数所属类型相对应的虚函数版本。假如我们在基类的构造函数调用派生类的虚函数，这个时候派生类成员未初始化，可能会导致程序崩溃。
类只能“继承”(并非真的继承)直接基类的构造函数，类不能默认继承默认、拷贝和移动构造函数。如果派生类没有定义这些构造函数，编译器会自动合成。
派生类继承基类的构造函数的方式是提供了一条注明了直接基类名的using声明语句。和普通成员的using声明不同，构造函数的using声明不会改变构造函数的访问级别。

8.容器与继承
当我们使用容器存放继承体系中的对象时，通常必须采用间接存储的方式，也就是在容器中放置指针(一般是智能指针)而非对象。

9.文本查询程序再探(没看)

*/
class Base {
	friend class Pal;
public:
	Base() = default;
	virtual void fun1(int i = 1) { cout << "Base i =" << i << endl; }
protected:
	int j = 0;
private:
	int k = 0;
};

class Vir : public Base {
public:
	virtual void fun1(int i) = 0;
	int fun3() { return 1; }
};

void Vir::fun1(int i = 2)
{
	cout << "Virtual i =" << i << endl;
}

class Derived : public Vir {
	friend void fun2();
public:
	void fun1(int i = 3) { cout << "Derived i =" << i << endl; j = 1; } //隐式虚函数
private:
	int m;
};

struct Priv_Deri : private Base{
public:

};

struct Us : private Base {
	//using Base::k;//k是不可访问的，所以不能用using改变
	using Base::j;//可以，且默认权限是public的。
};

class Pal {
public:
	int f(Base b) { return b.k; } //可以
	//int f2(Derived d) { return d.m; } //不行，m是派生类中的独有部分。
	int f3(Derived d) { return d.j; } //可以，j是派生类中的基类部分。
};

struct Base2 {
	Base2() : mem(0) { cout << "Base2 construct" << endl; }
protected:
	int mem;
};

struct Derived2 : Base2 { //默认public继承
	Derived2(int i) : mem(i) { cout << "Derived2 construct" << endl; }
	int get_mem() { return mem; }
	int get_base_mem() { return Base2::mem; }//可以用作用域运算符来使用被隐藏的基类成员。会从Base2的作用域开始找mem。
protected:
	int mem;
};

struct Base3 {
	void fun() { cout<< "base3" << endl; }
};

struct Derived3 : Base3 { //默认public继承
	void fun(int i) { cout << "derived3 & " << i << endl; }
};

struct Base4 {//使用using只覆盖重载集合中的一个。
	void fun(int i) { cout << "int =" << i << endl; }
	void fun(string i) { cout << "string =" << i << endl; }
	void fun(bool i) { cout << "bool =" << i << endl; }
};

struct Derived4 : Base4 { //默认public继承
	using Base4::fun;//如果去掉就不行。
	void fun(int i) { cout << "derived int = " << i << endl; }
};

//int main()
//{
//-----------------------------------------------------------------
	//Base b;
	//Derived d;
	//Vir * b_tmp = &d;
	//b_tmp->fun1();
	//b_tmp->Vir::fun1();//可以加作用域运算符强制执行虚函数的某个特定版本。
	//Priv_Deri p;
	//d.fun1();
	////p.fun1();//private继承，派生类用户没有对基类成员的访问权限。
	//Us u;
	////u.fun1();//私有继承且没有用using不能使用基类的函数。
	//u.j = 1; //可以。
//-----------------------------------------------------------------
	//Derived d;
	//Base *b = &d;
	//Derived *d_p = &d;
	//d_p->fun3();
	////b->fun3();//错误。因为搜索是自下而上的，base是最上级且没有这个函数，所以失败。
	//Derived2 d2(42);
	//cout << d2.get_mem() << endl;
	//cout << d2.get_base_mem() << endl;
//-----------------------------------------------------------------
//	Base3 b; Derived3 d;
//	b.fun();
//	d.fun(10);
//	//d.fun();//错误，基类中fun被隐藏。
//	d.Base3::fun();//显示调用
//	Base4 b4; Derived4 d4;
//	string s = "zhenbang zhang";
//	bool bo = true;
//	d4.fun(s);
//	d4.fun(bo);
////-----------------------------------------------------------------
//-----------------------------------------------------------------
//-----------------------------------------------------------------
//-----------------------------------------------------------------
//-----------------------------------------------------------------
//	return 0;
//}