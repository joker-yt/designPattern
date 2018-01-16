#include <iostream>

class GenderInterface {
public:
  virtual void action() const = 0;
};

class Male : public GenderInterface {
public:
  void action() const {
    std::cout << "Male"
              << "\n";
  }
};

class Female : public GenderInterface {
public:
  void action() const {
    std::cout << "Female"
              << "\n";
  }
};

enum class GenderType { MALE, FEMALE };
class GenderFactory {
public:
  static GenderInterface *const create(GenderType gender) {
    switch (gender) {
    case GenderType::MALE:
      return new Male();
      break;
    case GenderType::FEMALE:
      return new Female();
      break;
    default:
      break;
    }
    return nullptr;
  }
};

class GenderTypeWithStrategy {
public:
private:
  GenderType _type;
  GenderTypeWithStrategy *_inst;
};

int main(int argc, char *argv[]) {
  GenderInterface *const i = GenderFactory::create(GenderType::MALE);
  i->action();

  GenderInterface *const ii = GenderFactory::create(GenderType::FEMALE);
  ii->action();

  GenderFactory::create(GenderType::MALE)->action();

  return 0;
}
