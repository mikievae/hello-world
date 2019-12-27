#include <iostream>
#include <vector>
using namespace std;

class TemplateIf{
public:
	virtual void fun1() {};
	virtual void fun2() {};
	virtual void fun3() {};
	virtual void fun4() {};
	void run() { fun1(); fun2(); fun3(); fun4(); }
};

class Tmplate1 : public TemplateIf {
public:
	void fun1() { cout << "Tmplate1" << endl; }
	void fun2() { cout << "Tmplate2" << endl; }
	void fun3() { cout << "Tmplate3" << endl; }
	void fun4() { cout << "Tmplate4" << endl; }
};

class AbstractBuilder {
public:
	virtual void buildPartA() = 0;
	virtual void buildPartB() = 0;
	virtual void buildPartC() = 0;
	virtual void buildPartD() = 0;
	virtual void createProduct() = 0;
};

class Builder : public AbstractBuilder {
public:
	void buildPartA() { cout << "buildPartA" << endl; }
	void buildPartB() { cout << "buildPartB" << endl; }
	void buildPartC() { cout << "buildPartC" << endl; }
	void buildPartD() { cout << "buildPartD" << endl; }

};

int main()
{
	TemplateIf *tmp = new Tmplate1();
	tmp->run();
	if (tmp) delete tmp;
	return 0;
}