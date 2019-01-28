# Some basic c++ syntex

## Operator overloading

```cpp

class point{
public:
    point(double u):x(u), y(0){} /// Construct takes one argument. -> `Conversion constructor`

private:
    double x,y;
};

point s;
double d = 3.5;

s = d; // implicit conversion

```

**if you don't want implicit conversion, you need to add keyword `explict` to turn off inplicit conversion**

```cpp

class point{
public:
    explict point(double u):x(u), y(0){} /// Construct takes one argument. -> `Conversion constructor`

private:
    double x,y;
};

point s;
double d = 3.5;

s = d; // compile will fail because of explicit conversion

```

## How to convert a point to double?

We will not allowed to overload the double type operator. So, what we can do is by write a operator in point class to allow point to be converted to double.

```cpp

point::operator double(){
    return sqrt(x*x+y*y);
}

```

This is not always a good idea. Sometimes the meaning can be not clear.

For example, point to double? what's that mean. May not make a lot of sense.

## c++ `explicit` keyword can be used in front of a constructor to turn off the implicit conversion.

## function conversion

- exact match to signature
- try standard promotion: int -> double
- try standard type conversion : int -> short
- try user defined conversions
- use a match to ellipsis if found (...) (Worest situation)

```cpp

double sum ([]double){}
int sum([]int ){}
```

### `friend` function
Example of why friend function is useful

```cpp
class point{
    ...
private:
    double x,y;
};

ostream& operator<< (ostream&out, const point&p){
    out<<"("<< x << "," << y << ")";
    return out;
};

```

This problem can be solved by having a member function, however, the member function has to be default `point`.

We can break the limit by having a friend function

```cpp
class point{
public:
    friend ostream operator<< (ostream& out, point & this){
        ...
    }
private:
    double x,y;
}

```

### member function overload && friend function overload
```cpp
class point{
public:
    point operator+ (point &p){
        return point(x+p.x, y+p.y);
    }
private:
    double x,y;
}
```

### Operator overloading need to be very careful and comprehensive.

## Standard template library

- containers:
    * vector; list (sequential containers)
    * set, map (associative containers)

- iterators(think them as pointers)

- algorithms

### two ways of coding
1. normal c style coding
**second is perfered**
```cpp
for(int i= 0; i< 100; ++i){
    v[i] = i;
}

for(vector<int>::iterator p = v.begin();p!= v.end();++p){
    cout<< *p<< "\t";
}
```

2.`auto` keyword
```cpp
for(vector<int>::iterator p = v.begin();p!= v.end();++p){
    cout<< *p<< "\t";
}

// you can write as this
for(auto p = v.begin();p!= v.end();++p){
    cout<< *p<< "\t";
}

// more example
auto i = 3;
auto d = 3.5;
auto c = d;

auto i; // fail to compile
```

### `vector` method
```cpp
v.size()
v.resize(int size)

//constructor

vector<T> v;
vector<T> v(n);
vector<T> v(n, value);

```

### stl -> iterator method

`for range` => iterator

#### using `auto` for iterator
```cpp
for(auto it=data.begin();it!=data.end();++it){
    std::cin>>*it;
}
```
`segfaults usually means index out of value`

### use case for iterator

1. processing text file

```cpp

#include <iostream>
#include <iterator>
#include <fstream>
#include <vector>

int main(){
    ifstream data_file("data.txt");  // local data

    istream_iterator<int> start(data_file),end; //start pointer & end pointer

    vector<int> data(start, end);

    int sum = 0;
    for(auto it=data.start(); it!=data.end();++it){
        sum += *it;
    }
}

```

### STL feature :=> `for statement`

```cpp
for(declarition: expression){
    statement
}

//eg.
// for range statement
for(double d: data){
    sum += d;
}

for( auto &ele:data){
    ele += ele +2;
}
```

### STL input file
```cpp
//example of reading a words file
#include <fstream>
#include <iterator>
#include <algorithm>
#include <iterator>
#include <vector>
...

int main(){
    ifstream word_file("data.txt");
    istream_iterator<string> start(word_file),end;

    vector<string> words(start, end);

    for(auto str: words){ // for range statement
        cout<< str<<"\t";
    }

    sort(words.begin(),words.end());

    for(auto str:words){
        cout<< str<<"\t";
    }
}

```

### stl  sort algorithm
```cpp
sort(w.begin(), w.end()); // require random access
```

### STL iterators
Algorithm & iterators

iterator : start , pos, end (pos++, pos--)

iterator hierarchy:
- input iterator (lowest)
    * allow iterator move one by one

`numeric::accumulate( input, input, start_value )`

### output a random graph
```cpp
double prob(){
    return (static_cast<double>(rand()/RAND_MAX));
}
```

- connectivity matrix
- color matrix
- cost matrix