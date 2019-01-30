# Basics of inheritance

- pure polymorphism
- oop - inheritance

Design

- design apporiate object for the problem
- design in their relatedness
- use inheritance to share code among classes

```cpp
class classname: (public|protected|private) opt basename{}
               ^
               |
               "derive from"
```

most used inheritance is "public" inheritance => "subtyping"(~90%)
"private" inheritance is mainly for code reuse(<10%>)

- protected: -> give access for inheritance

```cpp
class point:class duo{}
/// point is a duo, but duo is not necessaryly a point
```

## 2.4 traits and inheritance

- reuse code
- create shared code and interface

single inheritance & multiple inheritance

oop term

- isa : best expressed by public inheritance
- hasa : best expressed as a member

## 2.5 Virtual member function

virtual member function

- a class defined in the base class and redefined in derived class (overidden)

using a pointer dynamic select (pure polymophism) at the run time which method is being executed.

```cpp
class point:class duo{
public:
    ...
    virtual double length(){
        return sqrt(first*first +second*second);
    }
}

class point3d: class duo{
public:
    ...
    double length(){
        return sqrt(first*first +second*second+z*z); // virtual
    }// overidden(operator is overload)
}
```

Dynamic selection at run time -> performance overhead

pure polymorphism:

- object being point must carry around type information so distinction can be made dynamically

oop -> maximum reuse of code
    -> natural modelling of problem

## 2.6 c++ feature: final

final -> if you dont want this class to be a base class

```cpp
class point3d final:public point{}
```

## 2.7 topics on inheritance

- subtyping and code reuse
- typing conversions and visibility
- abstract base class
- multiple inheritance
- inheritance and design
- detailed c++ consideration
- new c++11 feature: final, default, delete ...

## 2.10 inheritance

- deriving new class from existing class
- reuse existing code

```cpp
class student{
public:
    ...
    void print()const{}
protected: // derived class can seen this data
/// private solo => you can get it by using friend
    ...
}
```

## 2.11 Derived class

```cpp
class grad_student: public student{
    /// Inheritance has three types
    ///     public ~90% -> subtype relationship
    ///     private ~10%
    ///     protected
public:
    void print(){}
}

/// for grad student
/// both student::print() and grad_student::print() will be available
```

benefit

- code reuse (if student changed, grad_student will be updated)
- reflect relationship in problem domain
- A good OO design need to reflect the correct real life system

Typing conversion and visibility

- public derived class is a subtype of base
- variable of derived class treated as if it were base class type
- Pointer type pointer-to-base-class can point to objects of derived class type
  - subtle implicit conversions occur between base and derived type
  - difficult to follow what member is accessed if base and derived class overload the same member function

# 2.12 Students and Grad students

```cpp
student::student(char* nm, int id,
double g, year x):student_id(id),gpa(g),y(x){/// initialization
    strcpy(name, nm);
}

/// derived type
grad_student::grad_student(char* nm, int id, double g, year x, support t, char* d, char* th):student(nm, id, g, x), s(t){///base class constructor
    strcpy(dept, d);
    strcpy(thesis, th);
}

/// example of referencing it
grad_student gs("Morris Pohl", 200, 3.25, grad, ta, "Pharmacy", "Retail Pharmacy");

student &rs = gs;//
student *ps = ps;// pointer conversion. the graduate stuent pointer is converted to be student pointer
```

Overridden method

```cpp
void student::print(){
    cout<<name<<" " << ...
}

void grad_student::print(){
    student::print();//base class info
    //print(); will cause an infinite recursion
    cout<< "grad student" <<...
}
```

Example of the inheritance and its behavior

```cpp
#include "student.h"

main(){
    student s("M", 100, 3.2, fresh), *ps=&s;
    grad_student gs("MM", 200, 3.8, grad, ta, "Pharmacy", "retail pharmacy"), *pgs;

    ps->print();// print student
    ps=pgs=&gs;
    ps->print(); // student print
    pgs->print(); // grad_student print
    // this is the default behavior when overriden method is not virtual
}
// ps can point to both classes where as pgs can only point to grad_student otherwise will be a type error
```

Important
- `ps->print()` invoke `student::print()`
- `ps=pgs=&gs` both pointers pointing at object of type `grad_student` and assignment to `ps` invoke implicit conversion.
- second `ps->print()`; invokes `student::print()`; this is irrelevant that pointer points at `grad_student` variable gs;
- `pgs->print()` invoke `grad_student::print`

In summary, `ps` invoke the base class method even it is assigned to derived class; `pgs` invoke derived classed method.

SUMMARY

- Inheritance is a trade of between code reuse and efficiency.
- Inheritance requires thinking about three access boundaries.

## 2.13 virtual function

virtual function selection

what is virtual function selection?

as we can see before, the pointer of base class will always print base student infomation even after conversion.

So what is virtual function?

- typical base has virtual function and derived has their versions of function
- pointer to class can point as either base or derived class object
- member function selected depended on class of object being pointed at, not on pointer type.

virtual function will look up table of member functions at run time rather than select at compile time. The deduced the efficiency of the program.

the run time basically look up the instance, depends on the type of instance, and then go to the virtual function table and pick up the correct virtual function.

**overloading && overwritting**

- overloading : compile-time selected based on signature
- it can have distinct return types
- once it defined as `virtual`, it will persist in the derived class.

comments on virtual program

- different `print_i` is executed
  - Dynamically selected on the object pointed at
  - select corresponding version at run time
  - overhead in performance

## 2.14 Confusion with overloading

```cpp
class B{
public:
    virtual foo(int);
    virtual foo(double); // foo(double) overload foo(int) and can be recongised by compiler
    ...
};

class D:public B{
public:
    foo(int); // this is confusing
}
```

Restriction on virtual function

- non-static member function cannot be virtual
- virual characteristic is inherited
- constructor cannot be virtual
  - (factory pattern can produce code similar to virtual constructor)
- Destructor can be virtual