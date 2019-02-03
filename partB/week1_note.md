# 1.2 enum class

## enum class

```cpp
enum class Color{RED,GREEN,BLUE};
enum class Stoplight{RED,YELLOW,GREEN};
```

`::`->scope resolution operator

in c++11, we can use `Stoplight::RED` and `Color::RED` int the same scope without collision.

The new syntex for enum class:
```cpp
enum class IDENTIFIER: Integral_type{enumerator list};

/// example would be
enum class Color:short{RED, BLUE, GREEN};

/// another example
enum class WiredLogic:unsigned int{
    NO, //0
    MAYBE=5;
    YES=10;
};
```

By default, Integral_type is `int`.

# 1.3 standard templete library
consists
- containers
    - sequential container (vectors, dqueue, list)
    - associative container (set, map)
- iterators (navigation tool -> pointers)
- algorithms

Some new features in c++11
- regex
- thread (multi-core, multi-processing)
- unordered_map
- array (fix sized array)
- forward_list (single linked list)


# 1.4 iterators
- forward iterator
- bidirectional iterator
- random access iterator

forward iterator:
- search forward direction one-by-one
- operator (++, advance the operator; dereferencing operator: * and ->)
- == and != may be compared.

```cpp
/// replace iterator
template< class T>
void replace(ForwardIterator first,
            ForwardIterator last,
            const T&x, const T&y);
/// this algorithm relace x by y int the specified iterator range.
```
Example of using iterator
```cpp
#include <iostream>
#include <iterator>
#include <fstream>
#include <vector>

using namespace std;

template<typename ForwardIterator>
void square(ForwardIterator first, ForwardIterator last){
    for(;first != last; first++){
        *first = (*first)*(*first);
    }
}

int main(){
    ...
    square(w.begin(), w.end());
    for(auto i:w){ /// for range statement
        cout << i<<"\t";
        cout << end;;
    }
}
```

# 1.5 poker probability
Calculate probability of card flush

```cpp
enum class suit:short{SPADE, HEART, DIAMOND, CLUB};

class pips{
public:
    pips(int val):v(val){assert(v>0&&v<14);}
    friend ostream& operator<<(ostream& out, const pips&p)
    int get_pips(){return v;}

private:
    int v;
};

class card{
public:
    card():s(suit::SPADE),v(1){}
    card(suit s, pips v):s(s),v(v){}
    friend ostream& operator<<(ostream& out, const card& c){};
    /// Why ostream need to be a friend function
    ///
    /// if we change this ad a member function, that means the ostream
    /// must be a member of class. However, ostream is not a member of
    /// the class. Thus we need to make it as a friend function.
    suit get_suit()const{return s;}
    pips get_pips()const{return v;}
private:
    suit s;
    pips v;
};

ostream& operator<<(ostream& out, const card& c){
    cout<<c.v<<c.p;
    return out;
}

void init_deck(vector<card> &d){
    for(int i =1; i< 14;++i){
        card c(suit::SPADE,i);
        d[i-1]=c;
    }
    for(int i =1; i< 14;++i){
        card c(suit::HEART,i);
        d[i+12]=c;
    }
    for(int i =1; i< 14;++i){
        card c(suit::DIAMOND,i);
        d[i+25]=c;
    }
    for(int i =1; i< 14;++i){
        card c(suit::CLUB,i);
        d[i+38]=c;
    }
}

void print(vector<card> &deck){
    for(auto p=deck.begin();p!=deck.end();++p){
        cout<<*p;
        cout<<endl;
    }
}

bool is_flush(vector<card> &hand){
    suit s = hand[0].get_suit();
    for (auto p=hand.begin()+1;p!=hand.end();++p){
        if(s!=p->get_suit()){
            return false;
        }
    }
    return true;
}

bool is_straight(vector<card> &hand){
    int pip_v[5], i = 0;

    for(auto p=hand.begin(); p!= hand.end(); ++p){
        pips_v[i++]=(p->get_pips()).get_pips();
    }
    sort(pips_v, pips_v+5);
    if(pips_v[0]!=1){
        return (pips_v[0] == pips_v[1]-1 && pips_v[1] == pips_v[2]-1 && pips_v[2] == pips_v[3]-1 && pips_v[3] == pips_v[4]-1 && pips_v[4] == pips_v[5]-1)
    }else{
        return (pips_v[0] == pips_v[1]-1 && pips_v[1] == pips_v[2]-1 && pips_v[2] == pips_v[3]-1 && pips_v[3] == pips_v[4]-1 && pips_v[4] == pips_v[5]-1) || (pips_v[1] == 10 && pips_v[2] = 11 && pips_v[3] == 12 && pips_v[4] == 13)
    }
}

bool is_straight_flush(vector<card> &hand){
    return is_flush(hand)&&is_straight(&hand);
}

/// set up simulation
int main(){
    vector<card> deck(52);
    srand(time(0));
    init_deck(deck);
    int how_many;
    int flush_count =0;
    int str_count = 0;
    int str_flush_count =0;
    cout<< "how many shuffles";
    cin >> how_many;

    /// shuffle
    for(int loop = 0;loop<how_many;++loop){
        random_shuffle(deck.begin(),deck.end());
        vector<card> hand(5);
        int i =0;
        for(auto p=deck.begin();i<5;++p){
            hand[i++] = *p;
        }

        if(is_flush(hand)){
            flush_count++;
        }
        if(is_straight(hand)){
            str_count++;
        }
        if(is_straight_flush(hand)){
            str_flush_count++;
        }
    }
    cout<< "Flush "<<flush_count<< " out of "<< how_many<<endl;
    cout<< "Straights "<<str_count<< " out of "<< how_many<<endl;
    cout<< "Straight Flushes"<<str_flush_count<< " out of "<< how_many<<endl;
}
```

# 1.6 bidirection iterator

- operator ++ and --

Example of using bidirection iterator
- reverse()
```cpp
template<typename T>
void reverse(BidirectionalIterator first, BidirectionalIterator last){};
```

how does this work

move both front and end
```cpp
a , b, c, d, e, f, g
^                  ^
|                  |
 -------swap-------
++                 --
```

use cases:
```cpp
///isPalindrome
template<typename Bidirectional>
bool isPalindrome(Bidirectional first, Bidirectional second){
    while(true){
        last--; // because last is off by one
        if(first == last){
            break; //exit point
        }
        if(*first != *last){
            return false;
        }
        first++;
        if(first == last){
            break; //exit point
        }
    }
    return true;
}
```

only forward iterator will cause this algorithm to be O(n^2);

We want weekest iterator for most efficient algorithm possible.

# 1.7 Random access iterator
- Think indexed array

STL sort used this iterator

```cpp
template<class RandomAccessIterator>
void sort(RandomAccessIterator first, RandomAccessIterator last)
```

- quick sort
```cpp
pivot
(3), 6, 2, 9, -6, 15, 3 ,-2
-> 2 -6, 3, -2,(3),6 9, 15
then we recursively call left set[2, -6,3,-2] && right set[6, 9, 15]
```

```cpp
template<typename RandomAccess>
RandomAccess pickRandEI(RandomAccess first, RandAccess last){
    ptrdiff_t temp =last-first;
    return first+rand()%temp;// general pointer arithematic
}
```

`ptrdiff_t` -> `#include <cstddef>` pointer substraction to get integer value;

# 1.8 STL: overiview of containers
STL
- work efficiently
- work parametrically
- work orthogonally (consist but percise)

containers
- sequential container
    - deque
    - list
    - forward list c++11
    - vector
    - array
- associative container
    - set
    - multiset
    - map
    - multimap
    - hashmap( unordered_map, unordered_set) c++11

typical container interfaces
- constructor
- element access/ insertion/ emplacement(c++11)/deletion
- destructor
- Iterators

# 1.9 Associate container

key based access element
- map
- set
tree based implementation

hash base set/map
- unordered_map
- unordered_set
O(1) look up

```cpp
//<map>
for(auto p=worker.begin();p!=worker.end();++p){
    cout<< (*p).first<<" "<< (*p).second<<"\n";
}

// associate(first, second)
// (id no, name)
```

# 1.10 STL Algorithm library
- sorting
- non mutating sequence algorithm
- mutating sequence algorithm
- numerical algorithm
- generally use iterators to access container instantiated on given type

Soring algorithm prototype
```cpp
template<class RandAcc>
void sort(RandAcc b, RandAcc e);

template<class RandAcc>
void stable_sort(RandAcc b, RandAcc e);
// element remain in their relative same position
// eg 1(a) 2(a) 1(b) 2(b) 1(c) 2(c)
// if we sort by number
// stable sort will always give us
// 1(a) 1(b) 1(c) 2(a) 2(b) 2(c)
// where as quick sort may change the order and get:
// 1(b) 1(a) 1(c) 2(c) 2(b) 2(a)
```

# 1.11 Non-mutating sequence algorithm

- Do not mutate contents of the container they work on
- typical operation is searching container for particular element and return its position.

```cpp
template<class InputIter, Class T> // weakest iterator
InputIter find(InputIter b,
                InputIter e,
                const T&t); // standard
// find position of t in range b to e

template<class InputIter, Predicate p>
InputIter find_if(InputIter b,
                InputIter e,
                Predicate &p); // functor
// Find position of first element that makes predicate true in range b to e, otherwise position e return.

template<class InputIter, Class Function>
InputIter for_each(InputIter b,
                InputIter e,
                Function f); // control structure
// apply f to each value found in range b to e
```
Example of using `find`

```cpp
int main(){
    string myword[5] = {"my", "hop", "mop", "hop", "cope" }
    string* where;

    where = find(myword, myword+5, "hop");
    cout<<*++where<<endl; // "mop"
    sort(words, words+5);

    where = find(words, words+5,"hop");
    cout<<*++where<<endl; //"hope"
}
```

# 1.12 Lambda expression
- unnamed function in place

```cpp

/// Old way to do for_each & operation
#include ...

void incr(int &i){static int n = 1; i = n++;}
/// static means when the call is end, the value retains
/// similar to closure in golang
/// if I call second time, n starts with 2
/// another time, n starts with 3

void outvec(int i){cout<<i<<endl;}

int main(){
    vector<int> v(6);
    for_each(v.begin(), v.end(), incr);
    /// this will mutate the vector value

    for_each(v.begin(), v.end(), outvec);
}
```

- Lambda syntex
```cpp
[](int i){cout<<i <<endl;}

[](int n){return n*5.5} // return double

[](int n) -> int {return ++n;} // explict notation '-> type'
```

- mutating functions

```cpp
template<class InputIter, class OutputIter>
OutputIter copy(InputIter b1, InputIter e1, OutputIter b2);

/// copying algorithm over element b1 to e1
/// copy is placed starting at b2
/// Position returned is end of copy
```

# 1.13 Numerical algorithm
- sums
- inner product
- adjacent difference
- numerical algorithm functions behave as expected on numerical type where '+' and '*' are defined.

```cpp
accumulate(...);
inner_product(...);
```

example of how to utilize stl
```cpp
template<class InputIter, class T>
T accumulate(InputIter b, InputIter e, T t);


/// new usage
template<class InputIter, class T, class BinOp>
T accumulate(InputIter b, InputIter e, T t, BinOp bop);
/// BinOp -> functor
/// sum = bop(sum, element)
```


# 1.14 functional object

- Function object
    - function object are classes that have operator() defined

```cpp
int main(){
    double v[3] = {1.0, 2.5,4.6};
    sum = accumulate(v1, v1+3, 0.0, minus<int>());
    cout<< sum<<endl;
    //sum =-7;
    // how?
    // minus<int> convert double to int
    // -1 - 2 - 3 = -7
}
```

- Generator object
```cpp
class gen{
public:
    gen(double x_zero, double increment):x(x_zero),incr(increment){}
    double operator()(){x+= incr; return x*x;}
    /// This means we are overloading function '()' operator
    /// the prameter list is void

private:
    double x, incr;
};

double integrate(gen g, int n){
    vector<double> fx(n);

    generate(fx.begin(), fx.end(), g);

    return (accumulate(fx.begin(), fx.end(), 0.0)/n);
}

int main(){
    const int n = 10000;

    gen g(0.0, 1.0/n);
    cout<<integrate(g,n)<< endl;
}
```

# 1.15 Function object class; function adapter
- Arithmetic objects
- Comparison objects
- Logical objects

```cpp
template<class T>
struct plus<T>

template<class T>
struct minus<T>

template<class T>
struct times<T>

template<class T>
struct divide<T>

template<class T>
struct modulus<T>

template<class T>
struct negate<T>
```

- Function Adapters
    - creation of function objects using adaption
    - negators for negating predicate objects
    - Binders for binding a function argument
    - Adapters for pointer to function

```cpp
int main(){
    ind data[3] = {9, 10, 11};

    transform(data, data+3, data, bind2nd(times<int>(), 2));
    ///        \iterator/   oper  bindfunction
    /// {9*2, 10*2, 11*2}
}
```