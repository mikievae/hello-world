#include <iostream>

using namespace std;

/*
5 Implementations

Item 26: Postpone variable definitions as long as possible.
尽可能晚的定义要使用的变量，也就是在使用前再定义，且最好直接赋值而不是先默认初始化再赋值。

Item 27: Minimize casting.
尽量不使用转型，特别是dynamic_cases.
如果转型是必要的，试着将它隐藏在某个函数背后，客户随后可以调用该函数，而不需要将转型放在他们自己的代码里。
使用c++ style的转型，不要使用旧式转型。

Item 28-31: to be continue

6 Inheritance and Boject-Oriented Design

Item 32: Make sure public inheritance models "is-a".

Item 33: Avoid hiding inherited names.

Item 34: Differentiate between inheritance of interface and inheritance of implementation
接口继承和实现继承不同，在public继承下，derived classes总是继承base class的接口。
pure virtual函数只具体指定接口继承
impure virtual函数具体指定接口继承和缺省实现继承。
non-virtual函数具体指定接口继承和强制性实现继承。

Item 35: Consider alternatives to virtual functions

Item 36: Never redefine an inherited non-virtual function.
non-virtual函数有“不变性凌驾特异性”的性质，也就是说如果不需要这个性质，就应该声明为virtual函数。

Item 37: Never redefine a function's inherited default parameter value
virtual函数时动态绑定，而缺省参数却是静态绑定。c++使用这种方式是为了提高运行效率。如果缺省参数是动态的，那么会比目前实行的“”

Item 38: Model "has-a" or "is-implemented-in-terms-of" through compositon
复合(composition)的意义和public继承完全不同，在应用域，复合意味着has-a，在实现域，复合意味着is-implemented-in-terms-of(根据某物实现出)。

Item 39: Use private inheritance judiciously
private继承而来的所有成员都会变成private的，即使在base class中是protected或public的。
private继承意味着"is-implemented-in-terms-of".只有实现部分被继承，接口部分应略去。




*/

class Base {
public:
	virtual void mf1() = 0;
	virtual void mf1(int i) {}
	virtual void mf2() {}
	void mf3() {}
	void mf3(double d) {}
private:
	int x;
};

class Derived : public Base {
public:
	//using Base::mf1;
	//using Base::mf3;
	virtual void mf1() {}
	void mf3() {}
	void mf4() {}
};

class shape {
public:
	virtual void draw() const = 0 { cout << "shape draw" << endl; }
	void fun1() { cout << "fun1" << endl; }
private:
	int i;
};

class rectangle : public shape {
public:
	void draw() const { cout << "rectangle draw" << endl; }
};



//int main()
//{
//	int x = 0;
//	double y = 0;
//	Derived d;
//	d.mf1();
//	//d.mf1(x);
//	d.mf2();//如果重载的话，需要重载基类中所有的同名函数。否则，派生类会隐藏基类中的同名函数。或者可以用using声明达成目标。
//	d.mf3();
//	//d.mf3(y);
//	//------------------------------------------------------------------------------------------------------------------------------------------
//	shape * s = new rectangle;
//	s->shape::draw(); //纯虚函数可以通过派生类来调用。
//	s->fun1();
//	//------------------------------------------------------------------------------------------------------------------------------------------
//
//	return 0;
//}