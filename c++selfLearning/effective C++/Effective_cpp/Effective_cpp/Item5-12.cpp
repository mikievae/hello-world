#include <iostream>
#include <string>

using namespace std;
/*
二、构造/析构/赋值运算

Item 5: Know what functions C++ silently writes and calls
编译器会为class创建default的构造，copy, copy assignment操作符。
成员变量有引用或者const时，也不会产生默认拷贝赋值运算符,默认构造函数。如果base class将拷贝赋值运算符声明为private的，那么drived class不会产生默认拷贝赋值运算符。

Item 6: Explicitly disallow the use of compiler-generated functions you do not want
如果想阻止某个default函数的使用，可以把它声明为private的，且只声明，不定义。或者将基类的函数声明为private的，子类就不会产生对应的默认构造函数。

Item 7: Declare destructors virtual in polymorphic base classes;
如果基类析构函数不是虚函数，那么Base *b = getBase(); delete b;如果b指向的时派生类的对象，但是delete时用的是基类的析构函数，这样就这能删除基类部分，不能删除派生类资源。
如果class带有任何virtual函数，它就该拥有一个virtual析构函数。
如果class的设计目的不是作为基类，或者不是为了多态，就不该声明virtual析构函数。
如果错误的将函数声明为virtual函数，会导致函数对象的体积增大，因为虚函数隐式含有虚函数列表指针。

Item 8: Prevent exceptions from leaving destructors
如果析构函数有异常，可能会导致资源释放不完全。比如一个vector中包含多个对象，第一个对象抛出异常，后面的对象也不会进行析构。
析构函数不要吐出异常，如果一个被析构函数调用的函数可能抛出异常，析构函数应捕捉任何异常，然后吞下他们（不传播）或结束程序。
如果客户需要对某个操作函数运行期间抛出的一场做出反应，那么class应该提供一个普通函数（不是在析构函数中）执行该操作

Item 9: Never call virtual functions during construction or destruction.
不仅构造函数和析构函数不能调用虚函数，被他们所调用的函数也不能。

Item 10: Have assignment operators return a reference to *this
不仅时=，当使用+=，-+， *=的时候也适用。

Item 11: Handle assignment to self in operator=
有些时候时直接自赋值，有些时候时潜在的自赋值，比如赋值指针时，如果两个指针指向同一个对象。造成这类事情发生的原始是因为别名。
处理自赋值的方法可以用证同测试，也就是先判断参数是不是自己，如果是自己直接返回*this.但这样会导致一个问题，虽然解决了自赋值问题，但是没有解决异常安全问题。
可以使用如下代码
Widget& Widget::operator=(const Widget& rhs)
{
	Bitmap* tmp = pb;//也就是*this.pb;
	pb = new Bitmap(*rhs.pb);
	delete tmp;
	return *this;
}

Item 12: Copy all parts of an object.
拷贝函数应该确保赋值对象内所有的成分，如果是派生类，还需要拷贝基类的成分。
不要尝试用拷贝构造函数调用拷贝赋值运算符，或者返过来。如果两者代码十分相似，可以把公共部分放在第三个函数中，由两个函数分别调用。

Resource Management

Item 13: Use objects to manage resources.

Item 14: Think carefully about copying behavior in resource-managing classes.

Item 16: Use the same form in corresponding uses of new and delete.
如果再new表达式中使用[]，把需再相应的delete表达式中也是用[],如果再new表达式中不使用[]，也不要在相对应的delete表达式中使用[]。

Item 17: Store newd objects in smart pointers in standalone statements.
void processWidget(shared_ptr<widget> pw, int fun);
int fun1();

precessWidget(shared_ptr<Widget> (new Widget), fun1());
上述是一个函数调用,precessWidget的实参是一个shared_ptr和一个函数fun1的返回值。做了以下三件事情：
1.调用fun
2.执行new Widget
3.调用shared_ptr的构造函数。
3永远都会在2后面，但是1的位置是不确定的，假如顺序是2，1，3；而且在1的时候发生了异常，那么new widget返回的指针会丢失。就有可以能引发资源泄露。
为解决这一问题，需要把23步骤放在另一条语句中执行。
shared_ptr<Widget> pw(new Widget);
processWidget(pw, fun1());

四、设计与声明

Item 18: Make interfaces easy to use correctly and hard to use incorrectly.

Item 19: Treat claass design as type design

Item 20: Prefer pass-by-reference-to-const to pass-by-value
缺省情况，c++以by value方式传递对象至函数。而调用端所获得的也是函数返回值的一个复件。这些复件都是由对象的copy构造函数产出。这就可能会使pass-by-value成为费时的操作。
尽量以pass-by-reference-to-const替换pass-by-value，前者比较高效，并且可以避免切割问题。
以上规则并不适用于内置类型以及STL的迭代器和函数对象。对他们而言，pass-by-value往往比较适当。

Item 21: Don't try to return a reference when you must return an object.
不要将指针或者引用指向local stack对象  离开区块时会失效
或返回引用指向heap-allocated对象  不能有效获得指针，从而释放资源
或返回指针或者引用指向local static对象，因为总是指向同一个对象。

Item 22: Declare data members private.

Item 23: Prefer non-member non-friend functions to member functions.
粗略的判断一个变量的封装性，越少的函数可以访问这个变量，那么这个变量的封装性就越好。

Item 24: Declare non-member functions when type conversions should apply to all parameters.
如果需要为某个函数的所有参数进行类型转换，那么这个函数必须是非成员的。

Item 25: Consider support for a non-throwing swap


*/
class NoConstuctor {
private:
	int & a;
};

class noCopy {
public:
	noCopy(int x) :a(x) { std::cout << "a :" << a << std::endl; } //也可以侧面证明初始化列表是初始化而非赋值。
private:
	int &a;
};

class CopyAssignment {
public:
	CopyAssignment() = default;//假如不显示声明，就不会产生默认拷贝构造函数。
private:
	CopyAssignment& operator=(const CopyAssignment&) = default;
	CopyAssignment(const CopyAssignment&) = default;
};

class CopyDrived : public CopyAssignment {

};

class DBConnection {
public:
	static DBConnection create();
	void close();
};

class DBManege1 {
public:
	~DBManege1()
	{
		try { db.close(); }
		catch (exception e){
			//记录
			//可以选择abort或者是吞下这一异常。
		}
	}
private:
	DBConnection db;
};

class DBManege2 {
public:
	void close()//可以现由用户自行定义关闭的操作，如果关闭失败，再调用默认的析构方法，这样可以给用户更自由的发挥空间。
	{
		//操作
		db.close();
		closed = true;
	}
	~DBManege2()
	{
		if (!closed)
		{
			try { db.close(); }
			catch (exception e) {
				//记录
				//可以选择abort或者是吞下这一异常。
			}
		}
	}
private:
	DBConnection db;
	bool closed;
};

class Base {
public:
	Base() { fun(); }
	virtual void fun() { cout << "Base fun" << endl; }
};

class Derived : public Base {
public:
	void fun() { cout << "Derived fun" << endl; }
};

class BasePass {
public:
	BasePass(const string &s) { fun(s); }
	void fun(const string &s) { cout << "Base fun " << s << endl; }
};

class DerivedPass : public BasePass {
public:
	DerivedPass(string s) :BasePass(creatString(s)) {}
private:
	static string creatString(string s)//使用static可以防止在使用构造函数的时候没有初始化完成
	{
		return s;
	}
};

class Person {
public:
	Person(string s) : name(s) {}
	Person(const Person& p) : name(p.name){ cout << "copy constructor" << endl; }
private:
	string name;
};

Person fun(Person &p)
{
	cout << "fun" << endl;
	return p;
}

int main()
{
	//NoConstuctor ca;
	noCopy nc(1);
	noCopy nc1 = nc;//可以产生默认拷贝构造函数。
	//nc = nc1;//不会产生默认拷贝赋值运算符
	CopyDrived cd1;
	CopyDrived cd2;
	//CopyDrived cd3(cd2);//父类的拷贝构造函数不可访问，子类不会产生默认拷贝赋值运算符。
	//cd1 = cd2;//父类的拷贝赋值运算符是不可访问的，子类不会产生默认拷贝赋值运算符。
	Derived b;//对于构造函数和析构函数，里面调用的函数都是静态绑定的。
	DerivedPass dp("test");//通过把值向上传递的方法来解决构造函数使用不同的版本的问题。

	Person mike("string");
	auto p = fun(mike);//先调用拷贝构造函数，用mike构造p，然后return的时候再调用拷贝构造函数。
	return 0;
}