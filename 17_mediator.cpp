#include <vector>
#include <algorithm>
#include <iostream>

class Icolleague;

class Imediator
{
public:
    Imediator(){};
    virtual ~Imediator(){};

	virtual void consultation(std::string colleague_name) = 0;

private:
	virtual void createColleague() = 0;

protected:
	std::vector<Icolleague *> m_colleague;
};


class Icolleague
{
public:
    Icolleague(Imediator*);
    virtual ~Icolleague(){};

	virtual void run() = 0;
	virtual void advise() = 0;

private:
	void needsAcvice();

protected:
	Imediator* m_mediator;
};

class Colleague1 : public Icolleague
{
public:
    Colleague1(Imediator* mediator) : Icolleague(mediator){};
    virtual ~Colleague1(){};

	
	void run();
	void advise();

private:
	void needsAcvice();
};

class Colleague2 : public Icolleague
{
public:
    Colleague2(Imediator* mediator) : Icolleague(mediator){};
    virtual ~Colleague2(){};

	void run();
	void advise();

private:
	void needsAcvice();
};



class Mediator : public Imediator
{
public:
    Mediator();
    virtual ~Mediator(){};

	void consultation(std::string colleague_name);

	void run();

private:
	void createColleague();
};

Mediator::Mediator()
{
	createColleague();
}

void Mediator::createColleague()
{
	Icolleague *co1 = new Colleague1(this);
	Icolleague *co2 = new Colleague2(this);

	m_colleague.push_back(co1);
	m_colleague.push_back(co2);
}

void Mediator::run()
{
	std::vector<Icolleague*>::iterator it = m_colleague.begin();

	while (it != m_colleague.end())
	{
		(*it)->run();
		it++;
	}
	
}

void Mediator::consultation(std::string colleague_name)
{
	std::vector<Icolleague*>::iterator it = m_colleague.begin();

	while (it != m_colleague.end())
	{
		std::cout << "Mediator is consultaed from " << colleague_name << std::endl;
		std::cout << "Mediator advised to  " << colleague_name << std::endl;
		(*it)->advise();
		it++;
	}
}
//####################################

Icolleague::Icolleague(Imediator* mediator)
{
	m_mediator = mediator;
}
//:::::::::::::::::::::




void Colleague1::run()
{
	std::cout << "Colleague1::" << __func__ << std::endl;	
	needsAcvice();
}

void Colleague1::advise()
{
	std::cout << "Colleague1::" << __func__ << " received the advices" << std::endl;
}

void Colleague1::needsAcvice()
{
	m_mediator->consultation("Colleague1");
}



void Colleague2::run()
{
	std::cout << "Colleague2::" << __func__ << std::endl;	
	needsAcvice();
}

void Colleague2::advise()
{
	std::cout << "Colleague2::" << __func__ << " received the advices" << std::endl;
}

void Colleague2::needsAcvice()
{
	m_mediator->consultation("Colleague2");
}

int main(int argc, char *argv[])
{
    Mediator *mediator = new Mediator();

	mediator->run();

    return 0;
}

