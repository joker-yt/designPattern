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
public:
  State(){};
  virtual ~State(){};
};

//#########################################
// State pattern implecated for each app
//#########################################
// @ interface
class IStateApp : public State {
private:
protected:
  static IStateApp *toStateA();
  static IStateApp *toStateB();

public:
  IStateApp() : State(){};
  virtual ~IStateApp(){};

  static IStateApp *Initialize();

  virtual IStateApp *EventA(CContext *ctx) = 0;
  virtual IStateApp *EventB(CContext *ctx) = 0;
};

//#########################################
// ConcreteStates
//#########################################
class State_A : public IStateApp {
private:
public:
  State_A() : IStateApp() { std::cout << "State_A::" << __FUNCTION__ << "\n"; };
  virtual ~State_A() { std::cout << "State_A::" << __FUNCTION__ << "\n"; };
  //-----------------------------
  IStateApp *EventA(CContext *ctx) {
    std::cout << "State_A::" << __func__ << std::endl;
    ctx->Context_Method_1();
    return toStateB();
  };
  //-----------------------------
  IStateApp *EventB(CContext *ctx) {
    std::cout << "State_A::" << __func__ << std::endl;
    return this;
  };
  //-----------------------------
};

class State_B : public IStateApp {
private:
public:
  State_B() : IStateApp() { std::cout << "State_B::" << __FUNCTION__ << "\n"; };
  virtual ~State_B() { std::cout << "State_B::" << __FUNCTION__ << "\n"; };
  //-----------------------------
  IStateApp *EventA(CContext *ctx) {
    std::cout << "State_B::" << __func__ << std::endl;
    return this;
  };
  //-----------------------------
  IStateApp *EventB(CContext *ctx) {
    std::cout << "State_B::" << __func__ << std::endl;
    ctx->Context_Method_2();
    return toStateA();
  };
  //-----------------------------
};

IStateApp *IStateApp::Initialize() { return toStateA(); };
IStateApp *IStateApp::toStateA() {
  static State_A state;
  return &state;
};
IStateApp *IStateApp::toStateB() {
  static State_B state;
  return &state;
};

//#########################################
// main
//#########################################
int main(int argc, char const *argv[]) {

  std::ofstream ofs{"output.log"};
  CHandler *hndl = new CTerminalHandler{ofs};
  CContext ctx{hndl};
  // IStateApp *p = new State_A(&ctx);
  std::cout << "-------" << std::endl;
  IStateApp *p = IStateApp::Initialize();
  std::cout << "-------" << std::endl;
  p = p->EventA(&ctx);
  std::cout << "-------" << std::endl;
  p = p->EventA(&ctx);
  std::cout << "-------" << std::endl;
  p = p->EventB(&ctx);
  std::cout << "-------" << std::endl;
  p = p->EventB(&ctx);
  std::cout << "-------" << std::endl;

  return 0;
}
