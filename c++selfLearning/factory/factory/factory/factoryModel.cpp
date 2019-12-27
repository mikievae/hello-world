#include <iostream>

/**
简单工厂模式
*/

enum carType { benz, bmw };

//normal car------------------------------------------------------------
class Car {
public:
	virtual void makecar() = 0;
};

class BenzCar : public Car {
public:
	void makecar() { std::cout << "make Benz car" << std::endl; }
};

class BmwCar : public Car {
public:
	void makecar() { std::cout << "make BmwCar car" << std::endl; }
};

//simpleFactory -----------------------------------------------------
class SimpleFactory {
public:
	Car* creatCar(carType type)
	{
		switch (type) 
		{
			case benz:
				return new BenzCar();
				break;
			case bmw:
				return new BmwCar();
				break;
			default:
				return nullptr;
				break;				
		}
	}
};

//Factory--------------------------------------------------
class Factory {
public:
	virtual Car* creatCar() = 0;
};

class FactoryBenz : public Factory {
public:
	Car* creatCar() { return new BenzCar(); }
};

class FactoryBmw : public Factory {
public:
	Car* creatCar() { return new BmwCar(); }
};

//High car------------------------------------------------
class HighCar {
public:
	virtual void makecar() = 0;
};

class HighBenzCar : public HighCar {
public:
	void makecar() { std::cout << "make HighBenz car" << std::endl; }
};

class HighBmwCar : public HighCar {
public:
	void makecar() { std::cout << "make HighBmwCar car" << std::endl; }
};

//abstractFactory------------------------------------------
class AbstractFactory {
public:
	virtual Car* creatCar() = 0;
	virtual HighCar* creatHighCar() = 0;
};

class MultFactoryBenz : public AbstractFactory {
public:
	Car* creatCar() { return new BenzCar(); }
	HighCar* creatHighCar() { return new HighBenzCar(); }
};

class MultFactoryBmw : public AbstractFactory {
public:
	Car* creatCar() { return new BmwCar(); }
	HighCar* creatHighCar() { return new HighBmwCar(); }
};

//int main()
//{
////简单工厂模式返回对象，如果加新的car时需要修改factory类。
//	//SimpleFactory s;
//	//Car *ca = s.creatCar(benz);
//	//ca->makecar();
//	//Car *cb = s.creatCar(bmw);
//	//cb->makecar();
////---------------------------------------------------------
////一般工厂模式每个对象对应一个factory类，如果加新car时，不需要修改已有类，需要添加新的car类和新的factory类即可。
//	//Factory * f1 = new FactoryBenz();
//	//Car * benzcar = f1->creatCar();
//	//benzcar->makecar();
//	//Factory * f2 = new FactoryBmw();
//	//Car * bmwcar = f2->creatCar();
//	//bmwcar->makecar();
////---------------------------------------------------------
////抽象工厂模式一个factory类可以创建多个对应种类的car。
//	//AbstractFactory* ab1 = new MultFactoryBenz();
//	//Car* benzCar = ab1->creatCar();
//	//HighCar* highBenzCar = ab1->creatHighCar();
//	//benzCar->makecar();
//	//highBenzCar->makecar();
//
//	//AbstractFactory* ab2 = new MultFactoryBmw();
//	//Car* bmwCar = ab2->creatCar();
//	//HighCar* highBmwCar = ab2->creatHighCar();
//	//bmwCar->makecar();
//	//highBmwCar->makecar();
//
//	return 0;
//}