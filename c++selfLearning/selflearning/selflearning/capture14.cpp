#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <functional>
#include <sstream>

using namespace std;
/**
14、重载运算符与类型转换
1基本概念
除了重载函数调用运算符operator()之外，其他重载运算符不能含有默认实参。
对于一个运算符来说，它或者是类的成员，或者至少含有一个类类型的参数。也就是说不能改变内置类型的运算。
int operator+(int, int);//错误
不能被重载的运算符
::   .*   .   ? :
非成员运算符的等价调用
data1 + data2;
operator+(data1 , data2);
成员运算符的等价调用
data1 += data2;
data1.operator+=(data2);
某些运算符不应该被重载，如&&或||，重载之后就没有短路求值属性的功能了。
选择作为成员或者非成员
(=),([]),(()),(->)这四个运算符必须是成员。
具有对称性的运算符，如算数，相等性，关系和位运算符等，通常应该是非成员的。
列入：
string s = "world";
string t = s + "!";//正确，我们可以把一个const char*加到一个string 对象中
string u = "hello" + s;//如果+是string的成员则产生错误。 等价于“hi”.operator(s),而内置类型没有成员函数。 如果是非成员，等价于operator+("hi",s)。
2输入和输出运算符
输入输出运算符必须是非成员函数，IO运算符通常要读写类的非公有数据，所以IO运算符一般被声明为友元。
3函数调用运算符
3.1 lambda是函数对象，表达式产生的类不含默认构造函数，赋值运算符和默认析构函数。是否包含默认的拷贝/移动构造函数由需要捕获的数据成员类型而定。
3.2 标准库定义的函数对象。如 plus<Type> p; auto i = p( a, b);执行a加 b.可以在算法中使用标准库函数对象。
3.3可调用对象与function
c++由几种可调用对象：函数，函数指针，lambda表达式，bind创建的对象，以及重载了函数调用运算符的类。不同类型的可调用对象可能共享同一只调用形式。
int add(int i, int j) {return i + j}
auto mod = [](int i, int j) {return i % j}
struct divide{
	int operator() (int i, int j) { return i / j}
};
上面这些调用共享了一种调用形式 int (int, int)
map<string, function<int(int, int)>>> binops= {
	{"+", add},
	{"/", divide()},
	{"%", mod},
	{"*", [](int i, int j) {return i * j}}
};

bindops["+"] (10, 5); 调用add(10, 5);
不能将重载的函数名字直接放入function类型的对象中。
4.重载，类型转换和运算符
1.类型转换运算符 operator type() const;
可以在转换运算符之前加explicit，这样就不会隐式转换了。然后用static_cast<type>(val) 来进行显示的转换。

Best Regards,
*/

class time {
friend ostream& operator<<(ostream & os, const time & t);
friend istream& operator>>(istream &is, time &t);
public:
	time() :hour(0), minute(0), second(0) { cout << hour << ":" << minute << ":" << second << endl; }
	void operator()(const int, const int, const int);
	time(int h, int m, int s)  :hour(h), minute(m), second(s)  { cout << hour << ":" << minute << ":" << second << endl; }
private: 
	int hour;
	int minute;
	int second;
};

void time::operator()(const int i, const int j, const int k)
{
	hour = i;
	minute = j;
	second = k;
	cout << *this;
}

ostream& operator<<(ostream & os, const time & t)
{
	os << t.hour << ":" << t.minute << ":" << t.second << endl;
	return os;
}

istream& operator>>(istream &is, time &t)
{
	is >> t.hour >> t.minute >> t.second;
	if (is)
		cout << "read successfully" << endl;
	else
	{
		cout << "read failed" << endl;
		t = time();
	}
	return is;
}

//int main()
//{
//	time t(1,1,1);
//	t(1, 2, 3);
//	return 0;
//}