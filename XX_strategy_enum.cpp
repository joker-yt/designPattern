#include <iostream>

enum class Enum1 { Default, First, Second };

enum class Enum2 { Default, First, Second };

int main(int argc, char *argv[]) {
  Enum1 e1 = Enum1::Default;

  // e1 = Enum2::First;
  return 0;
}
