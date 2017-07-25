#include <string>
#include <iostream>
#include "23_visitor.h"

int main(int argc, char const *argv[]) {
  Ivisitor *pvisitor = new Cvisitor;
  Cacceptor1 *pacc1 = new Cacceptor1();
  Cacceptor2 *pacc2 = new Cacceptor2();
  pacc1->accept(pvisitor);
  pacc2->accept(pvisitor);

  return 0;
}
