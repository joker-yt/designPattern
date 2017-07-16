designPattern
=============

Factory, FacoryMethod, AbstractFactory
--------------------------------------

### Factory

---

Obj factoryMethod(type){  
 switch(type){  
 case 1: return Obj1;  
 case 2: return Obj2;  
 }  
\}

int main(){  
 Obj obj = factoryMethod(type1);  
 obj = factoryMethod(type2);  
\}

---

### FactoryMethod

class IFactoryMethod {  
 Obj factoryMehod() = 0;  
}  
class CFactoryMethod1 : public IFactoryMethod{  
 Obj factoryMehod() {  
 return ObjectA(); }  
\}

class CFactoryMethod2 : public IFactoryMethod{  
 Obj factoryMehod() {  
 return ObjectB(); }  
\}

int main(){  
 IFactory \*factory = new CFactoryMethod1();  
 fatory->method();

IFactory \*factory = new CFactoryMethod2();  
fatory->method();\}

--

### AbstractFactory

class IAbstractFactory {  
 Obj1 createObj1() = 0;  
 Obj2 createObj2() = 0;  
\}

class CAbstractFactory1 : public IAbstractFactory {  
 Obj1 createObj1() { return AAAObj1;}  
 Obj2 createObj2() { return AAAObj2;}  
 }

class CAbstractFactory2 : public IAbstractFactory {  
 Obj1 createObj1() { return BBBObj1;}  
 Obj2 createObj2() { return BBBObj2;} }

int main(){  
 IAbstractFactory \*factory; Obj1 obj1;  
Obj2 obj2;

factory = new CAbstractFactory1();  
obj1 = factory->createObj1();  
obj2 = factory->createObj2();

factory = new CAbstractFactory2;  
obj1 = factory->createObj1();  
obj2 = factory->createObj2();

\}
