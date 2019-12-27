#include <iostream>
#include <memory>

class operation {
public:
	virtual int caculate(int, int) { return 0; }
};

class add : public operation {
public:
	int caculate(int a, int b) 
	{
		return (a + b);
	}
};

class del : public operation {
public:
	int caculate(int a, int b) 
	{
		return (a - b);
	}
};

class Caculator {
public:
	Caculator(char s)
	{
		switch(s) {
		case '+':
			op = std::make_shared<add>();
			break;
		case '-':
			op = std::make_shared<del>();
			break;
		default:
			break;
		}
	}

	int caculate(int a, int b)
	{
		return op->caculate(a, b);
	}

private:
	std::shared_ptr<operation>  op;
};

//int main()
//{
//	Caculator ca('+');
//	std::cout << ca.caculate(1, 2) << std::endl;
//	return 0;
//}