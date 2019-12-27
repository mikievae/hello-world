#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;
/**
第九章、顺序容器
vector			可变大小数组，支持快速随机访问，在尾部之外地方插入或删除元素可能很慢
deque			双端队列，支持快速随机访问，在头尾插入 / 删除的速度很快
list			双向链表，只支持双向顺序访问，在任意位置插入 / 删除的速度都很快
forward_list	单向链表，单项顺序访问，任意位置插入 / 删除速度都很快
array           固定大小数组，支持快速随机访问，不能删除添加元素。与内置数组相似。但更安全。
string          与vector类似，存放字符。//写一个string 类
迭代器的范围是左闭右开的。 [begin,end)
除array外，其他容器的默认构造函数都会创建一个指定类型的空容器，且都可以接受指定容器大小和元素初始值参数。
初始化
C c;
C c1(c2);
C c1=c2;
C c{a,b,c,d};
C c = {a,b,c,d};
C c(b,e); 迭代器be之间的元素，且类型必须与C的元素相同。
以下是只有顺序容器才有的是初始化操作：
C seq(n);seq有n个元素，默认初始化。
C seq(n,val); n个值为val的元素。
容器赋值运算符
c1 = c1
c={a,b,c}
swap(c1,c2)
c1.swap(c2)
以下仅适用于顺序容器
seq.assign(b,e) 将seq中的元素替代为be迭代器中间的元素
seq.assign(il) 将seq中的元素替代为初始化列表il中的元素
seq.assign(n,t)  将seq中的元素替代为n个值为t的元素
*/

/**
第十章、泛型算法
泛型算法是执行在迭代器基础上的算法，不会执行容器操作。算法永远不会改变底层容器的大小。
lambda表达式
[capture list] (parameter list) -> return type { function body }
capture list:是一个lambda所在函数中定义的局部变量的列表，通常为空，只用于局部非static变量，可以直接使用局部static变量和它所在函数之外声明的名字。尽量保持变量捕获的简单化，以确保捕获对象是正确且存在的。
其余三个为参数列表，返回值类型，函数体。lambda必须使用尾置返回；
我们可以忽略参数列表和返回类型，但必须永远包含capture list和function body
lambda不能有默认参数
bind函数： auto newCallable = bind(callable, arg_list);
*/
void elimDups(vector<string> &words)
{
	sort(words.begin(), words.end());
	auto end_unique = unique(words.begin(), words.end());
	words.erase(end_unique, words.end());
}

void sort(vector<string>::iterator begin, vector<string>::iterator end)
{
	for (vector<string>::iterator first1 = begin,  last1 = end; first1 != last1; last1--)
	{
		for (vector<string>::iterator first2 = begin, last2 = last1; first2 != last2 - 1 ; first2++)
		{
			auto tmp = *(first2 + 1);
			if (*first2 > *(first2 + 1))
			{
				swap(*first2, *(first2 + 1));
			}
		}
	}
}

void biggies(vector<string> &words,
			 vector<string>::size_type sz)
{
	elimDups(words);
	stable_sort(words.begin(), words.end(), [](const string &a, const string &b) {return a.size() < b.size(); });
	auto wc = find_if(words.begin(), words.end(), [sz](const string &a) {return a.size() >= sz; }); //如果想要使用所在函数的局部变量需要先捕获。
	auto count = words.end() - wc;
	for_each(wc, words.end(), [](const string &s) { cout << s << " "; }); //可以直接使用cout是因为cout定义在函数之外。
	cout << endl;
}

int fcn1()
{
	int v1 = 42;
	auto f = [v1] {return v1; };//被捕获的变量值，实在lambda创建时拷贝，而不是调用时拷贝。
	v1 = 0;
	auto j = f(); 
	return j;
}

int fcn2()
{
	int v1 = 42;
	auto f = [&v1] {return v1; };//可以用引用的方式捕获变量
	v1 = 0;
	auto j = f();
	return j;
}

int fcn3()
{
	int v1 = 42;
	auto f = [&] {return v1; };//隐式捕获&或者=
	v1 = 0;
	auto j = f();
	return j;
}

int fcn4()
{
	int v1 = 42;
	int v2 = 2;
	auto f = [&,v2] {return v1 + v2 ; };//混合使用显示和隐式。第一个元素必须是&或=；且显示变量和隐式变量必须是不同的捕捉方式（值或引用）；
	v1 = 0;
	auto j = f();
	return j;
}

int fcn5()
{
	int v1 = 42;
	auto f = [v1] () mutable {return ++v1; };//想要改变捕获列表里的值必须用mutable
	v1 = 0;
	auto j = f();
	return j;
}

int fcn6()
{
	int v1 = -42;
	auto f = [v1] {return v1 < 0 ? -v1 : v1; };//函数体只有一句，lambda表达式可以自己判断返回类型。
	v1 = 0;
	auto j = f();
	return j;
}

int fcn7()
{
	int v1 = -42;
	auto f = [v1]()-> int { if (v1 > 0) return v1; else return -v1; };//函数体有多句，lambda会默认判定为void返回类型，需要明确指定返回值类型。
	v1 = 0;
	auto j = f();
	return j;
}

//int main()
//{
	//vector<string> words1{ "a","b","cd","d","a" };
	//vector<string> words2 = { "fac","qbc","dcc","sdc" };
	//vector<string> words3(words1);
	//vector<string> words4(10, "sdsefewse");
	//biggies(words1, 0);
	//biggies(words2, 2);
	//biggies(words3, 2);
	//biggies(words4, 5);
//-----------------------------------------------------------------
	//auto i = fcn1();
	//cout << "value of i in fcn1 is :" << i << endl;
	//i = fcn2();
	//cout << "value of i in fcn2 is :" << i << endl;
	//i = fcn3();
	//cout << "value of i in fcn3 is :" << i << endl;
	//i = fcn4();
	//cout << "value of i in fcn4 is :" << i << endl;
	//i = fcn5();
	//cout << "value of i in fcn5 is :" << i << endl;
	//i = fcn6();
	//cout << "value of i in fcn6 is :" << i << endl;
	//i = fcn7();
	//cout << "value of i in fcn7 is :" << i << endl;
//-----------------------------------------------------------------
	//using namespace std::placeholders;
	//auto check1 = std::bind(sort, std::placeholders::_1, std::placeholders::_2);//使用这种参数的时候需要添加placeholders
	//auto check2 = std::bind(sort, std::placeholders::_2, std::placeholders::_1);//可以用bind重排参数顺序
	//vector<string> words1{ "a","b","cd","d","a" };
	//auto begin = words1.begin();
	//auto end = words1.end();
	//check1(begin, end);
	//for (auto i : words1)
	//	cout << i << " ";
	//cout << endl;
	//vector<string> words2{ "a","b","cd","d","a" };
	//check2(end, begin);
	//for (auto i : words1)
	//	cout << i << " ";
	//cout << endl;
//-------------------------------------------------------------------

	/*return 0;*/
//}

