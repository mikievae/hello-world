#include <iostream>
#include <string>

/*
Item 1:View C++ as a federation of languates;
C++可以分为四个大块
--c:,说到底c++仍然是以C为基础的语言。
--Object-Oriented C++,这部分也就是C with Classes所诉求的：calss,封装，继承，多态，虚函数，等等
--Template C++,这部分是C++的泛型编程。
--STL,STL是个template程序库。
C++并不是一个带有一组守则的一体语言，它是从四个次语言组成的联邦政府，每个次语言都有自己的规约。
C++的搞笑编程守则视情况状态而变化，取决于你使用c++的哪一个部分。

Item 2:Prefer consts,enums, and inlines to #defines.
-对于单纯常量，最好用const对象或者enums替换defines
-对于形似函数的宏，最好用inline函数替换defines
#defines MAX = 100.0 可以替换为 const double Max = 100.0;//宏使用大写，因此这里改变写法。
当需要在class的作用域中使用常量值时可以用 enum{ Max = 100.0};

Item 3:Use const whenever possible.
迭代器的作用就像一个T*,声明迭代器为const就像声明T* const指针，表示这个迭代器不得指向其他东西，但是所指向的东西的值是可以改变的。如果你希望的是指向的东西不变，需要用const_iterator.
令函数返回一个常量值可以降低因客户错误而造成的意外。如重载某个类的乘号。 (a * b) = c；这样就会避免这种情况的发生。
如果想在const函数中改变某个变量，需要把这个变量声明为mutable。
如果一个函数既需要const版本，也需要一般版本，可以用非const函数调用另一个const函数的方式，减少代码重复。反过来调用则不行，不能保证const函数不改变对象。

Item 4:Make sure that objects are initialized before they're used
对于内置类型，你必须在使用之前手动完成初始化
对于内置类型以外的其他对象，初始化责任落在构造函数身上。
在构造函数的函数体内进行的赋值并不是初始化，只是赋值。在构造函数的初始化列表替换赋值动作会更好。
总是使用成员初始化列表的方式，因为有时候必须这样做，而且往往比赋值更高效。
成员初始化的次序是固定的，总是以其声明的次序被初始化。即使在初始化列表中的顺序不同，也不会有任何影响。所以初始化列表要按照声明的次序为次序。
为免除“跨编译单元的初始化次序”的问题，请用local static 对象替换non-local static对象。
*/

class A {
	enum{ i = 5 }; //i不可被引用或者取地址，这样就不会又其他人拥有这个变量了。这种方式也就是所谓的enum hack
	int scores[i];
	const int j = 0;
};

//const int A::i;//const 值可以在函数外定义

void fun(int i)
{
	std::cout << i << std::endl;
}

#define CALL_WITH_MAX(a, b) fun((a) > (b) ? (a) : (b)) //繁琐且麻烦，而且易出错。可在fun1中看到错误。

void fun1()
{
	int a = 5, b = 0;
	CALL_WITH_MAX(++a, b); //a被累加两次
	CALL_WITH_MAX(++a, b + 10); //a被累加一次
}

template<typename T>
inline void callWithMax(const T& a, const T& b)
{
	fun(a > b ? a : b);
}

class InitClass {
public:
	InitClass(int x, std::string y) 
	{ 
		std::cout << " a :" << a << std::endl;
		std::cout << " b :" << b << std::endl;
		a = x;
		b = y;
		std::cout << " a :" << a << std::endl;
		std::cout << " b :" << b << std::endl;
	}//在函数体内的是赋值，会先调用成员变量的默认构造函数然后进行赋值。
	//InitClass(int x, int y):a(x), b(y) {} //在初始化列表里面的是初始化。
private:
	int a;
	std::string b;
};

class ClassOrder {
public:
	ClassOrder(int a) : x(a), y(x) { std::cout << "x:" << x <<std::endl; std::cout << "y:" << y << std::endl;}
	ClassOrder(int a, int b) : y(a), x(y + b) { std::cout << "x:" << x << std::endl; std::cout << "y:" << y << std::endl; }
private:
	int x;
	int y;
};

class FileSystem {//如果这个对象是在其他编译单元
public:
	std::size_t numDisks() const { return 0; }
};

FileSystem& local_tfs()
{
	static FileSystem fs;//用Local static对象代替none local static对象。
	return fs;
}

extern FileSystem tfs;//必须已经定义而不是声明，如果把下一句的定义去掉，就是编译失败。
FileSystem tfs;//如果是多个文件且这个对象在使用之后定义就是编译失败。
class Directory {
public:
	Directory();
	Directory(int i);
};

Directory::Directory()
{
	std::size_t disk = tfs.numDisks();
}

Directory::Directory(int i)
{
	std::size_t disk = local_tfs().numDisks();
}

int num;//全局变量未初始化会进行值初始化。

//int main()
//{
//	//fun1();
//	//变量初始化
//	int x;//成员变量没有初始化时不会有默认值。
//	//std::cout << x << std::endl;//未初始化
//	std::cout << "num is" << num << std::endl;
//
//	//构造函数初始化
//	InitClass ic(1, "string");
//	ClassOrder co1(1);
//	ClassOrder co2(1, 2);//列表初始化的顺序是按照成员变量声明的顺序。所以两者顺序要保持一致。
//	
//	//不同编译单元的non-local-static对象的初始化次序
//	Directory tempDir;//这里必须保证ths对象在tempDir对象之前被初始化。否则tempDir的构造函数就会调用尚未初始化的tfs.
//	Directory local_tempDir(1);//这里会保证你用到这个对象的时候，对象已经被初始化，并且如果没有使用这个对象，就不会引发构造和析构成本。
//
//	return 0;
//}

