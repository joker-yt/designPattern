#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string>
#include <algorithm>
#include <vector>

//######################################
class Iproduct
{
public:
    Iproduct(){};
    virtual ~Iproduct(){};

	virtual void UseProduct(){};
};

class Cproduct1 : public Iproduct
{
public:
    Cproduct1(){};
    virtual ~Cproduct1(){};

	void UseProduct(){
		std::cout << __func__ << ":Cproduct1 is used." << std::endl;
	}
};

class Cproduct2 : public Iproduct
{
public:
    Cproduct2(){};
    virtual ~Cproduct2(){};

	void UseProduct(){
		std::cout << __func__ << ":Cproduct2 is used." << std::endl;
	}
};


//######################################
class Ifactory
{
public:
    Ifactory(){};
    virtual ~Ifactory(){};

	virtual Iproduct* create(){};
};

class Cfactory1 : public Ifactory
{
private:
	Cfactory1(){
		
	};

public:
	static Ifactory* m_instance;
	
    virtual ~Cfactory1(){};
	static Ifactory* getInstance(){
		if (m_instance == 0)
			m_instance = new Cfactory1();
		return m_instance;
	}

	Iproduct* create(){
		return new Cproduct1();
	}
};

class Cfactory2 : public Ifactory
{
private:
    Cfactory2(){};

public:
	static Ifactory* m_instance;
	
    virtual ~Cfactory2(){};

	static Ifactory* getInstance(){
		if (m_instance == 0)
			m_instance = new Cfactory2();
		return m_instance;
	}

	Iproduct* create(){
		return new Cproduct2();
	}
};

Ifactory* Cfactory1::m_instance = 0;
Ifactory* Cfactory2::m_instance = 0;

class FactoryMethod : public Ifactory
{
private:
	Ifactory* m_factory[2];
	Iproduct* m_product[2];

public:
    FactoryMethod(){
		m_factory[0] = Cfactory1::getInstance();
		m_product[0] = m_factory[0]->create();
		m_factory[1] = Cfactory2::getInstance();
		m_product[1] = m_factory[1]->create();
	};
    virtual ~FactoryMethod(){};
	
	void UseProduct(){
		for (int i = 0; i < 2; i++)
		{
			m_product[i]->UseProduct();
		}
	}

};


//######################################


int main(int argc, char const *argv[]) {

	FactoryMethod fm;

	fm.UseProduct();
	

	return 0;
}
