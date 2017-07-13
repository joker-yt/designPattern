#include <iostream>

class IPartA {
private:
protected:
  int _n;

public:
  IPartA() : _n(0){};
  virtual ~IPartA(){};
  virtual int doSomething() = 0;
};

class IPartB {
private:
public:
  IPartB(){};
  virtual ~IPartB(){};
  virtual int doSomething(int n) = 0;
};
//#########################################
class CPartA_1 : public IPartA {
private:
public:
  CPartA_1() { _n = 10; };
  virtual ~CPartA_1(){};
  int doSomething() {
    std::cout << "CPartA_1::" << __FUNCTION__ << " -> return -> " << _n << "\n";
    return _n;
  };
};

class CPartA_2 : public IPartA {
private:
public:
  CPartA_2() { _n = 20; };
  virtual ~CPartA_2(){};
  int doSomething() {
    std::cout << "CPartA_2::" << __FUNCTION__ << " -> return -> " << _n << "\n";
    return _n;
  };
};
//#########################################
class CPartB_1 : public IPartB {
private:
public:
  CPartB_1(){};
  virtual ~CPartB_1(){};
  int doSomething(int n) {
    std::cout << "CPartB_1::" << __FUNCTION__ << " -> receive -> " << n << "\n";
    return n + 100;
  };
};

class CPartB_2 : public IPartB {
private:
public:
  CPartB_2(){};
  virtual ~CPartB_2(){};
  int doSomething(int n) {
    std::cout << "CPartB_2::" << __FUNCTION__ << " -> receive -> " << n << "\n";
    return n + 200;
  };
};
//#########################################

class IAbstractFactory {
private:
protected:
public:
  IAbstractFactory(){};
  virtual ~IAbstractFactory(){};
  virtual IPartA *CreatePartA() = 0;
  virtual IPartB *CreatePartB() = 0;
};

class CAbstractFactory1 : public IAbstractFactory {
private:
public:
  CAbstractFactory1(){};
  virtual ~CAbstractFactory1(){};
  IPartA *CreatePartA() { return new CPartA_1(); };
  IPartB *CreatePartB() { return new CPartB_1(); };
};

class CAbstractFactory2 : public IAbstractFactory {
private:
public:
  CAbstractFactory2(){};
  virtual ~CAbstractFactory2(){};
  IPartA *CreatePartA() { return new CPartA_2(); };
  IPartB *CreatePartB() { return new CPartB_2(); };
};

int main(int argc, char const *argv[]) {
  IAbstractFactory *abst1 = new CAbstractFactory1();
  IPartA *partA1 = abst1->CreatePartA();
  int m = partA1->doSomething();

  IPartB *partB1 = abst1->CreatePartB();
  int n = partB1->doSomething(m);

  std::cout << "CAbstractFactory1:: m -> " << m << " n -> " << n << "\n";

  IAbstractFactory *abst2 = new CAbstractFactory2();
  partA1 = abst2->CreatePartA();
  m = partA1->doSomething();

  partB1 = abst2->CreatePartB();
  n = partB1->doSomething(m);
  std::cout << "CAbstractFactory2:: m -> " << m << " n -> " << n << "\n";
  return 0;
}
