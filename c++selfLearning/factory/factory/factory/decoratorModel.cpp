#include <iostream>

class Phone {
public:
	Phone() = default;
	~Phone() = default;
	virtual void show() { std::cout << "phone" << std::endl; }
};

class iPhone : public Phone {
public:
	iPhone(Phone* ph_tmp) : ph(ph_tmp) {}
	void show() { ph->show(); }
private:
	Phone * ph;
};

class Mic : public iPhone {
public:
	Mic(Phone * ph_tmp) : iPhone(ph_tmp) {  }
	void set() { std::cout << "Mic" << std::endl; }
	void show() { iPhone::show(); set();}
};

class Spk : public iPhone {
public:
	Spk(Phone * ph_tmp) : iPhone(ph_tmp) {  }
	void set() { std::cout << "Spk" << std::endl; }
	void show() { iPhone::show(); set(); }
};

//int main()
//{
//	Phone *ph = new Phone();
//	Phone *m = new Mic(ph);
//	Phone *s = new Spk(m);
//	s->show();
//	return 0;
//}