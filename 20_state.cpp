#include <iostream>
#include <string>
#include <fstream>

//#########################################
class CHandler {
private:
  /* data */
public:
  CHandler() { std::cout << __FUNCTION__ << "\n"; };
  virtual ~CHandler() { std::cout << __FUNCTION__ << "\n"; };
  virtual void output(std::string str){};
  virtual void finalize(){};
};

class CTerminalHandler : public CHandler {
private:
  std::ofstream &_ofs;

public:
  CTerminalHandler(std::ofstream &ofs) : _ofs(ofs) {
    std::cout << __FUNCTION__ << "\n";
  };
  virtual ~CTerminalHandler() { std::cout << __FUNCTION__ << "\n"; };
  void output(std::string str) {
    std::cout << "CTerminalHandler::" << __FUNCTION__ << "\n";

    _ofs << str << std::endl;
  };
  void finalize() {
    std::cout << "CTerminalHandler::" << __FUNCTION__ << "\n";
    _ofs.close();
  };
};

//#########################################
class CContext {
private:
  int _condition;
  CHandler *_hndl;

public:
  CContext(CHandler *hndl) : _condition(0) {
    _hndl = hndl;
    std::cout << __FUNCTION__ << "\n";
  };
  virtual ~CContext() { std::cout << __FUNCTION__ << "\n"; };
  void Context_Method_1() {
    _condition = 1;
    std::cout << __FUNCTION__ << " : [condition] ->" << _condition << "\n";
    _hndl->output(std::string{__FUNCTION__});
  }
  void Context_Method_2() {
    _condition = 2;
    std::cout << __FUNCTION__ << " : [condition] ->" << _condition << "\n";
    _hndl->output(std::string{__FUNCTION__});
  }
};

class State {
private:
protected:
  CContext *_ctx;

public:
  State(CContext *ctx) : _ctx(ctx){};
  virtual ~State(){};
  virtual void methodA(){};
  virtual void methodB(){};
};

class State_A : public State {
private:
public:
  State_A(CContext *ctx) : State(ctx){};
  virtual ~State_A(){};
  void methodA() {
    std::cout << "State_A::" << __func__ << std::endl;
    _ctx->Context_Method_1();
  };
  void methodB() { std::cout << "State_A::" << __func__ << std::endl; };
};

class State_B : public State {
private:
public:
  State_B(CContext *ctx) : State(ctx){};
  virtual ~State_B(){};
  void methodA() { std::cout << "State_B::" << __func__ << std::endl; };
  void methodB() {
    std::cout << "State_B::" << __func__ << std::endl;
    _ctx->Context_Method_2();
  };
};

int main(int argc, char const *argv[]) {

  std::ofstream ofs{"output.log"};
  CHandler *hndl = new CTerminalHandler{ofs};
  CContext ctx{hndl};
  State *p = new State_A(&ctx);
  p->methodA();
  p->methodB();
  delete (p);

  p = new State_B(&ctx);
  p->methodA();
  p->methodB();
  delete (p);

  return 0;
}
