#include <iostream>

class IFactory {
public:
	virtual void makePhone() {};
};

class MyFactory : public IFactory {
public:
	void makePhone() { std::cout << "make my own phone" << std::endl; }
};

class ProxyFactory : public IFactory {
public:
	ProxyFactory(IFactory * f_tmp) : f(f_tmp) {}
	void check() { std::cout << "check the component" << std::endl; }
	void makePhone() { check(); f->makePhone(); }
private:
	IFactory * f;
};

//int main()
//{
//	IFactory *mf = new MyFactory();
//	IFactory *pf = new ProxyFactory(mf);
//	pf->makePhone();
//	return 0;
//}