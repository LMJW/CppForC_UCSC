#include <iostream>

using namespace std;

class vA {
public:
    vA() {}
    virtual void print() { cout << "this is in vA" << endl; }
};

class A {
public:
    A() {}
    void print() { cout << "this is in A" << endl; }
};

class B : public A {
public:
    B() : A() {}

    void print() {
        // A::print();
        cout << "this is in B" << endl;
    }
};

class C : public vA {
public:
    C() {}
    void print() {
        // vA::print();
        cout << "this is in C" << endl;
    }
};

int main() {
    A a, *pa;
    vA v, *pv = &v;
    B b, *pb = &b;
    C c, *pc = &c;

    pa->print();
    pa = &b;
    pa->print();
    pb->print();

    pv->print();
    pv = &c;
    pv->print();
    pc->print();
}