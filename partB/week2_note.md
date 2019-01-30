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

# 2.4 traits and inheritance
- reuse code
- create shared code and interface

single inheritance & multiple inheritance

oop term
- isa : best expressed by public inheritance
- hasa : best expressed as a member

# 2.5 Virtual member function
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

# 2.6 c++ feature: final

final -> if you dont want this class to be a base class
```cpp
class point3d final:public point{}
```

# 2.7 topics on inheritance
- subtyping and code reuse
- typing conversions and visibility
- abstract base class
- multiple inheritance
- inheritance and design
- detailed c++ consideration
- new c++11 feature: final, default, delete ...