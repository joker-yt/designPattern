#ifndef __23_VISITOR_H__
#define __23_VISITOR_H__

class Iacceptor;
class Ivisitor;
class Cacceptor1;
class Cacceptor2;

class Iacceptor {
private:
protected:
  std::string *_pname;

public:
  Iacceptor(){};
  virtual ~Iacceptor(){};
  virtual void accept(Ivisitor *p);
  virtual std::string getname() { return *_pname; }
};

class Ivisitor {
private:
public:
  Ivisitor(){};
  virtual ~Ivisitor(){};
  virtual void visit(Iacceptor *p) {
    std::cout << "acceptor is ->" << p->getname() << std::endl;
  };
  virtual void visit(Cacceptor1 *p){};
  virtual void visit(Cacceptor2 *p){};
};

////////////////////////////////////
void Iacceptor::accept(Ivisitor *p) { p->visit(this); };

class Cacceptor1 : public Iacceptor {
private:
public:
  Cacceptor1() { _pname = new std::string(__func__); };
  virtual ~Cacceptor1(){};
  void accept(Ivisitor *p) { p->visit(this); };
};

class Cacceptor2 : public Iacceptor {
private:
public:
  Cacceptor2() { _pname = new std::string(__func__); };
  virtual ~Cacceptor2(){};
  void accept(Ivisitor *p) { p->visit(this); };
};
////////////////////////////////////

class Cvisitor : public Ivisitor {
private:
public:
  Cvisitor(){};
  virtual ~Cvisitor(){};
  void visit(Iacceptor *p) {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    Ivisitor::visit((Iacceptor *)p);
  };
  void visit(Cacceptor1 *p) {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    Ivisitor::visit((Iacceptor *)p);
  };
  void visit(Cacceptor2 *p) {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    Ivisitor::visit((Iacceptor *)p);
  };
};

////////////////////////////////////

#endif /* end of include guard: __23_VISITOR_H__ */
