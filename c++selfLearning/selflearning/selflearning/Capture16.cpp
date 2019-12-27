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
/*
16、模板与泛型编程
1.定义模板
函数模板
template <typename T>//模板参数列表里面可以包含多个模板参数。
int fun(const T &v1, const T &v2){}
类型模板参数：上述是模板类型参数，可以看作类型说明符，就像内置类型说明符一样使用。类型参数前必须使用关键字class或typename，且两者含义相同，可以互换使用。
template <unsigned M, unsigned N>//
int compare(const char (&p1)[M], const char (&p2)[N]) {return strcmp(p1, p2); }
非类型模板参数：表示要给值而非一个类型。通过一个特定的类型名而非关键字class或typename来指定非类型实参。
当我们调用上述compare时， 
compare("hi","hello")//编译器会在字符串字面常量末尾插入一个空字符作为终结符。
编译器会使用字面量常量的大小来代替M和N，从而实例化模板。会实例化如下版本：int compare(const char (&p1)[3], const char (&p2)[6])
函数模板可以声明为Inline或者constexper的，放在模板参数列表之后，返回值之前。
当编译器遇到一个模板定义时，并不生成代码，只有当我们实例化模板的一个特定版本时，编译器才会生成代码。也就是当我们使用(而非定义)模板时，编译器才生成代码；
通常我们调用一个函数时，编译器只需要掌握函数的声明，类似的，使用一个类类型的对象时，类定义必须是可用的，但成员函数的定义不必已经出现。因此我们将类定义和函数声明放在头文件中，而普通函数和类的成员函数定义放在源文件中。
模板则不同，为了生成一个实例化版本，编译器通常需要知道定义。所以函数模板和类模板通常放在头文件里面，且头文件通常既包括声明也包括定义。
类模板
一个类模板的每个实例都形成一个独立的类，不会对其他实例的类型成员有任何特殊的访问权限。
我们可以在类模板内部或者外部定义其成员函数，且定义在类模板内部的函数被隐式声明为内联函数。
对于一个成员函数：ret-type StrBlob::member-name(parm-list);对应的成员如下
template <typename T>
ret-type StrBlob::member-name(parm-list) {}
类模板成员函数： 默认情况下，一个类模板的成员函数只有当程序用到它时才进行实例化。也就是说没有被使用的时候，则不会被实例化。
在类的代码内简化模板类名的使用： 在模板类自己的作用域当中，我们可以直接使用模板名而不提供实参。
在类模板外使用类模板名： 当在类模板外定义成员时，我们并不在类的作用域中，知道遇到类名才表示进入类的作用域。
模板参数：我可以使用任何名字来命名模板参数，其作用域在声明之后，模板声明或定义结束之前。模板参数会隐藏外层作用域的相同名字。但是，在模板内不能重用模板参数名。

T::size_type * p;//这里需要知道size_type是类型还是static成员。默认情况下，c++假定通过作用域运算符访问的名字不是类型，因此如果我们想使用一个模板类型参数的类型成员，就必须显示用typename告诉编译器。
模板参数可以有默认值，但是无论何时使用一个类模板，必须加上尖括号。特别的是，如果一个模板类所有模板参数都有默认值，且我们希望使用这些默认值，就必须在模板名后面跟上一对空的尖括号。
成员模板：一个类（普通类和模板类）可以包含本身是模板的成员函数。成员模板不能是虚函数。
如果我们在类模板外定义一个成员模板时，必须同时为类模板和成员模板提供参数列表，类模板的参数列表在前，成员模板参数列表在后。
tmplalte <typename T>
tmplalte <typename It>
	Blob::Blob()(It b, It e): data(make_shared<vector<T>>)(b, e) {}
控制实例化
	当模板被使用时才会进行实例化，这一特性意味着相同的实例可能出现在多个对象文件中。当两个或多个独立编译的源文件使用的了相同的模板，并提供了相同的模板参数时，每个文件中就会有该模板的要给实例。
	可以通过显示实例化来避免这种开销：
									extern template declaration; //实例化声明
									template declaration; //实例化定义。
	只需要定义一次，其他需要使用模板的时候只进行声明。
实例化定义会实例化所有成员。也就是说在一个类模板的实例化定义中，所用类型必须能用于模板的所有成员函数。

2 模板实参推断
	对于函数模板，编译器利用调用中的函数实参来确定其模板参数，这一过程被称为模板实参推断。
2.1 类型转换与模板类型参数
	当数组的引用作为函数的参数时，数组的维度也是参数的一部分。

3 重载与模板
	函数模板可以被另一个模板或一个普通非模板函数重载。
	如果有多个函数提供同样号的匹配，则：
	-如果同样好的函数中只有一个是非模板函数，则选择此函数。
	-如果同样好的函数中没有非模板函数，而是有多个函数模板，且其中一个模板比其他模板更特别，则选择此模板。
	-否则，此调用有歧义。

4 可变参数模板



*/

template <typename T> class Blob {

};

class A {
	friend void fun(A a);
private:
	int i;
};

void fun(A a)
{
	cout << a.i << endl;
}

typedef double C;
template <typename C, typename B>
void f(C c, B b)
{
	C tmp = c; //tmp的类型为模板参数A,而不是double。
	//double B; //不能重复声明模板参数B
}

template <typename T> T fobj(T, T);
template <typename T1, typename T2, typename T3> T1 fobj2(T2, T3);
template <typename T> T fref(const T &, const T &);
int main()
{
	int a[10], b[42];
	fobj(a, b);//数组的指针作为参数，都是指针所以可以。
	//fref(a, b);//错误，因为是引用，维度也是参数。
	fobj2<int, int*>(a, b);//只有尾部参数的显示模板参数才可以忽略，而且前提是他们可以从函数参数推断出来。
	auto i = vector<int>{ 2 };
	for (auto k : i) 
		cout << k << endl;;
	return 0;
}