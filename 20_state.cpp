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

//#########################################
// State pattern!!!
//#########################################
class State {
private:
protected:
  CContext *_ctx;

public:
  State(CContext *ctx) : _ctx(ctx){};
  virtual ~State(){};
};

//#########################################
// State pattern implecated for each app
//#########################################
// @ interface
class IStateApp : public State {
private:
public:
  IStateApp(CContext *ctx) : State(ctx){};
  virtual ~IStateApp(){};

  virtual IStateApp *toStateA(){};
  virtual IStateApp *toStateB(){};
  virtual void EventA() = 0;
  virtual void EventB() = 0;
};

//#########################################
// ConcreteStates
//#########################################
class State_A : public IStateApp {
private:
public:
  State_A(CContext *ctx) : IStateApp(ctx){};
  virtual ~State_A(){};
  void EventA() {
    std::cout << "State_A::" << __func__ << std::endl;
    _ctx->Context_Method_1();
  };
  void EventB() { std::cout << "State_A::" << __func__ << std::endl; };
  IStateApp *toStateA(CContext *ctx) {
    static IStateApp *state = new State_A{ctx};
    return state;
  };
};

class State_B : public IStateApp {
private:
public:
  State_B(CContext *ctx) : IStateApp(ctx){};
  virtual ~State_B(){};
  void EventA() { std::cout << "State_B::" << __func__ << std::endl; };
  void EventB() {
    std::cout << "State_B::" << __func__ << std::endl;
    _ctx->Context_Method_2();
  };
  IStateApp *toStateB(CContext *ctx) {
    static IStateApp *state = new State_B{ctx};
    return state;
  };
};

//#########################################
// main
//#########################################
int main(int argc, char const *argv[]) {

  std::ofstream ofs{"output.log"};
  CHandler *hndl = new CTerminalHandler{ofs};
  CContext ctx{hndl};
  IStateApp *p = new State_A(&ctx);
  p->EventA();
  p->EventB();
  delete (p);

  p = new State_B(&ctx);
  p->EventA();
  p->EventB();
  delete (p);

  return 0;
}
