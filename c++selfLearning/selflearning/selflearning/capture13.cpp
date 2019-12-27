#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <functional>
#include <sstream>
#include <memory>
using namespace std;
/**
13、拷贝构造函数
如果一个构造函数的第一个参数时自身类类型的引用，且任何额外参数都有默认值，则此构造函数是拷贝构造函数。
拷贝构造函数通常不应该是explicit的。
对于某些类来说，合成拷贝构造函数用来阻止我们拷贝该类类型对象。而一般情况，合成的拷贝构造函数会将其参数的成员逐个拷贝到正在创建的对象中。编译器从给定对象中依次将每个非static成员拷贝到正在创建的对象中。
如果一个类有一个移动构造函数，则拷贝初始化有时会使用移动构造函数而非拷贝构造函数来完成。
拷贝构造函数自己的参数必须是引用类型（如果不是引用，调用时需要拷贝参数，就需要调用拷贝构造函数，造成死循环）
13.1析构函数
在一个构造函数中，首先进行成员的初始化是在函数体执行之前完成的，且按照它们在类中出现的顺序进行初始化。在析构函数中，首先执行函数体，然后销毁成员，成员按照初始化顺序的逆序进行销毁。
析构函数中不存在类似于构造函数中初始化列表的东西来控制成员如何销毁。析构部分是隐式的。成员销毁时发生什么完全依赖于成员的类型。销毁类类型的成员需要执行成员自己的析构函数。内置类型没有析构函数，因此销毁内置类型什么也不需要做。
如果一个类需要析构函数，我们几乎可以肯定它也需要一个拷贝构造函数和一个拷贝赋值运算符。
一个需要拷贝构造函数的类，也需要一个拷贝赋值运算符。反之亦然。
13.2 =default
我们可以通过将拷贝控制成员定义为=default来显示的要求编译器生成合成版本。如果我们在类内用=default修饰成员的声明时，合成的函数将隐式声明为内联的。如果不希望是内联，就在类外使用=default.
13.3阻止拷贝
可以通过将拷贝构造函数和拷贝赋值运算符定义为删除的函数(=delete)来阻止拷贝。与=defalut不同，
1。=delete必须出现在函数第一次声明的时候。
2。=delete可以对任何函数使用，=default只能对编译器可以合成的默认构造函数或拷贝控制成员使用。
struct NoCopy{
	NoCopy() = default;
	NoCopy(const NoCopy &) = delete;//阻止拷贝
	NoCopy &operator=(const NoCopy &) = delete;//阻止赋值
	~NoCopy() = default;
13.4析构函数是不能删除的
如果删除了，就无法销毁此类的对象，这样编译器就不允许定义改类型的变量或创建该类型的临时对象。
且，如果一个类有某个成员的类型删除了析构函数，我们也不定定义该类的变量或临时对象。因为成员无法销毁，导致对象整体也就无法销毁了。
对于删除了析构函数的类型，虽然不能定义这种类型的变量或者成员，但是可以动态分配这种类型的对象。但不能释放这些对象。
struct NoDtor{
	const string i;
	NoDtor() = default;
	~NoDtor() = delete;
};

NoDtor nd = nd2;//错误
NoDtor *p = new NoDtor();//正确
delete P; //不能删除，因为没有析构函数。
13.5 某些类，编译器将这些合成的成员定义为删除的函数
1.如果类的某个成员的析构函数是删除的或是不可访问的（例如，private的），则类合成的析构函数、拷贝构造函数和默认构造函数被定义为删除的。
2.如果类的某个成员的拷贝构造函数是删除的或是不可访问的，则类的合成拷贝构造函数被定义为删除的。
3.如果类的某个成员的拷贝赋值元算符是删除的或是不可访问的，或是类有一个const的或引用成员，则类的合成拷贝赋值运算符被定义为删除的。//对于const成员，不能重新赋值。对于引用，赋值之后仍然指向左侧对象的。而不是右侧对象。
4.如果类有一个引用成员，他没有类内初始化器，或是类有一个const成员，他没有类内初始化其且其类型未显示定义默认构造函数，则该类的默认构造函数定义为删除的。//对于有引用成员和无法默认构造的const成员的类，不能合成默认构造函数，因为这些成员必须在初始化的时候带上初值。
本质上这些规则的含义是：如果一个类有数据成员不能默认构造、拷贝、复制或销毁，则对应的成员函数将被定义为删除的。
13.6拷贝控制和资源管理
行为像值的类VHasPtr
行为像指针的类PHasPtr
13.7拷贝控制实例 Message, Folder
13.8对象移动
在旧版本中，没有直接的方法移动对象，因此容器中所保存的对象必须是可拷贝的。在新标准中可以保存不可拷贝的对象，只要他们能被移动即可。
P470-P484没看
*/

class HasPtr {
public:
	HasPtr(const std::string &s = std::string()):
		ps(new std::string(s)), i(0){}
	~HasPtr() { delete ps; }
private:
	std::string *ps;
	int i;
};

HasPtr f(HasPtr hp)
{
	HasPtr ret = hp;
	return ret;
}//当f返回时，hp和ret都被销毁，都会调用HasPtr的析构函数，而这两个对象包含相同的指针，会导致此指针被delete两次。

class PrivateCopy{
	PrivateCopy(const PrivateCopy &); //class默认是private的。
	PrivateCopy &operator=(const PrivateCopy &);//因为拷贝成员是private的，所以用户代码不能拷贝这个类型的对象。因为只声明，没有定义，所以可以阻止友元和成员函数进行拷贝。
public:
	PrivateCopy() = default;
	~PrivateCopy();//因为析构函数的public的，所以可以定义该类型的对象。
};

class VHasPtr {//行为像值的类
public:
	VHasPtr(const std::string &s = std::string()) :
		ps(new std::string(s)), i(0) {}
	VHasPtr(const VHasPtr &p) :
		ps(new std::string(*p.ps)), i(p.i) {}
	VHasPtr & operator=(const VHasPtr &);
	~VHasPtr() { delete ps; }
private:
	std::string *ps;
	int i;
};

VHasPtr & VHasPtr::operator=(const VHasPtr &rhs)//要防止自赋值的情况
{
	auto newp = new std::string(*rhs.ps);//拷贝string，防止自赋值时把自己ps的内存给删了。
	delete ps;//释放旧的内存
	ps = newp;
	i = rhs.i;
	return *this;
}

class PHasPtr {//行为像指针的类
public:
	PHasPtr(const std::string &s = std::string()) :
		ps(new std::string(s)), i(0), use(new std::size_t(1)) {}
	PHasPtr(const PHasPtr &p) :
		ps(p.ps), i(p.i), use(p.use) { ++*use; }
	PHasPtr & operator=(const PHasPtr &);
	~PHasPtr();
private:
	std::string *ps;
	int i;
	std::size_t *use;//计数器，计算有多少个对象共享*ps的成员
};

PHasPtr::~PHasPtr()
{
	--*use;
	if (*use == 0)
	{
		delete ps;
		delete use;
	}
}

PHasPtr & PHasPtr::operator=(const PHasPtr &rhs)//要防止自赋值的情况
{
	++*rhs.use;
	if (--*use == 0) 
	{
		delete ps;
		delete use;
	}
	ps = rhs.ps;
	use = rhs.use;
	i = rhs.i;
	return *this;
}

//class Folder;
//
//class Message {
//	friend class Folder;
//public:
//	explicit Message(const string &str = ""):
//		contents(str) {}
//	Message(const Message&);
//	Message operator= (const Message&);
//	~Message();
//	void save(Folder&);
//	void remove(Folder&);
//private:
//	string contents;
//	set<Folder*> folders;
//	void add_to_Folders(const Message&);
//	void remove_from_Folders();
//};
//
//void Message::save(Folder& f)
//{
//	folders.insert(&f);
//	f.addMsg(this);
//}
//
//void Message::remove(Folder &f)
//{
//	folders.erase(&f);
//	f.remMsg(this);
//}
//
//void Message::add_to_Folders(const Message& m)
//{
//	for (auto i: m.folders)
//	{
//		i->addMsg(this);
//	}
//}
//
//void Message::remove_from_Folders()
//{
//	for (auto i : folders)
//	{
//		i->remMsg(this);
//	}
//}
//
//Message::Message(const Message& m):
//	contents(m.contents), folders(m.folders)
//{
//	add_to_Folders(m);
//}
//
//Message::~Message()
//{
//	remove_from_Folders();
//}
//
//Message Message::operator= (const Message& rhs)
//{
//	remove_from_Folders();
//	contents = rhs.contents;
//	folders = rhs.folders;
//	add_to_Folders(rhs);
//	return *this;
//}
//
//class Folder {
//friend class Message;
//public:
//	Folder() = default;
//	Folder(const Folder&);
//	Folder& operator=(const Folder&);
//	~Folder();
//	void addMsg(Message*);
//	void remMsg(Message*);
//private:
//	set<Message*> msg;
//};
//
//void Folder::addMsg( Message *m)
//{
//	msg.insert(m);
//}
//
//void Folder::remMsg(Message *m)
//{
//	msg.erase(m);
//}
//
//Folder::Folder(const Folder&)
//{
//
//}

class StrVec {
public:
	StrVec() :elements(nullptr), first_free(nullptr), cap(nullptr) {}
	StrVec &operator=(const StrVec &);
	StrVec(const StrVec&);
	~StrVec();
	void push_back(const string &);
	size_t size() { return first_free - elements; }
	size_t capacity() { return cap - elements; }
	string* begin() const { return elements; }
	string* end() const { return first_free; }
private:
	allocator<string> alloc;
	void chk_n_alloc() { if (size() == capacity()) reallocate(); } //如果没有空间了，就重新分配内存
	pair<string*, string*> alloc_n_copy(const string*, const string*);//分配内存，并拷贝一个给定范围中的元素
	void free();//销毁构造的元素并释放内存。
	void reallocate();//重新分配内存
	string *elements;//第一个元素的位置。
	string *first_free;//最后一个元素之后的位置
	string *cap;//分配内存末尾之后的位置
};

void StrVec::push_back(const string &s)
{
	chk_n_alloc();
	alloc.construct(first_free++, s);
}

pair<string*, string*> StrVec::alloc_n_copy(const string* s1, const string* s2)
{
	auto data = alloc.allocate(s2 - s1);
	return {data, uninitialized_copy(s1, s2, data)};
}

void StrVec::free()
{
	for (auto tmp = first_free; elements != tmp;)
		alloc.destroy(--tmp);
	alloc.deallocate(elements, capacity());
}

StrVec::~StrVec()
{
	free();
}

void StrVec::reallocate()
{
	auto tmp = size() ? 2 * size() : 1;
	auto b = alloc.allocate(tmp);
	auto e = uninitialized_copy(elements, cap, b);
	free();
	elements = b;
	first_free = e;
	cap = b + tmp;
}

StrVec::StrVec(const StrVec& vec)
{
	pair<string*, string*> p1 = alloc_n_copy(vec.elements, vec.first_free);
	cout << "copycopy" << endl;
	elements = p1.first;
	first_free = cap = p1.second;
}

StrVec & StrVec::operator=(const StrVec & vec)
{
	pair<string*, string*> p1 = alloc_n_copy(vec.elements, vec.first_free);
	cout << "=======" << endl;
	free();
	elements = p1.first;
	first_free = cap = p1.second;
	return *this;
}

//int main()
//{
//	StrVec st;
//	StrVec tmp(st);
//	st.push_back("a");
//	for (auto a = st.begin(); a != st.end(); a++)
//	{
//		cout << *a << endl;
//	}
//
//	return 0;
//}