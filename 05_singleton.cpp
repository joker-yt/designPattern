#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string>
#include <algorithm>
#include <vector>

//#########################################
// Context (parameter for instance)
//#########################################
class CContext {
private:
  int _n;

public:
  CContext() : _n(0){};
  virtual ~CContext(){};
  void AddCount() {
    _n++;
    std::cout << " -> " << __FUNCTION__ << " : " << _n << "\n";
  }
};

//#########################################
// Singleton
//#########################################
class ISingleton {

private:
  static CContext *_ctx;
  ISingleton() {
    std::cout << "ISingleton::" << __func__ << " create instance" << std::endl;
  };
  virtual ~ISingleton(){};

  static ISingleton *m_instance;

public:
  static ISingleton *getInstance(CContext *ctx) {
    if (m_instance == 0) {
      m_instance = new ISingleton();
    }
    _ctx = ctx;
    return m_instance;
  };

  void method() {
    std::cout << "this is method" << std::endl;
    _ctx->AddCount();
  };
};
ISingleton *ISingleton::m_instance = nullptr;
CContext *ISingleton::_ctx = nullptr;

int main(int argc, char const *argv[]) {
  // constructor is private, so you can't create the instance freely, and
  // need to use "getInstance()"
  // ISingleton *p = new ISingleton();

  CContext *ctx = new CContext;
  ISingleton::getInstance(ctx)->method();
  ISingleton::getInstance(ctx)->method();
  ISingleton::getInstance(ctx)->method();

  return 0;
}
