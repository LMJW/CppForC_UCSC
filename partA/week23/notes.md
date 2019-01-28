# Graph

## K4 graph
```
*----*
|\  /|
| \/ |
| /\ |
|/  \|
*----*
```
`*` represent a node.
The **degree** of a node represented by the number of edges that this node connected to.

The above graph has an average degree of `3` because each node has 3 connections.

## Graph representation
    - connectivity matrix
    - edge list representation

### When to use which representation?
    - sparse graph(average degree much smaller than the number of nodes[eg: degree 4, ~ 100s nodes])
    - dense graph(average degree is comparable to the number of nodes [eg: degree 50, ~ 100 nodes])

RULE of Thumb:
    - edge list representation is better to represent **sparse graph**
    - connectivity matrix is good for **dense graph**

Example of a directed graph:

- Matrix representation
```
x | 1 2 3 4
------------
1 | 1 1 1 1
2 | 1 0 0 0
3 | 0 1 0 1
4 | 0 1 1 0

```
- List representation
```
1 -> 1->2->3->4
2 -> 1
3 -> 2->4
4 -> 2->3
```

## Class initialization syntax
```c++
// Method 1 -> assignment
class point{
    public:point(){x = y = 0.0};
    private:
        double x,y;
};

//Method 2 -> assignment
class point{
    public:point(){this->x=0.0;this->y=0.0};
    private:
        double x,y;
};

//Method 3 ->Initialization ->(BEST ! Recommanded!)
// Good for initialize const variable
//
// This method only allowed in constructor!
class point{
    public:point():x(0.0),y(0.0){}
    private:
        double x,y;
}
```

**member** && **argument**
eg:

```cpp
class point{
    public:
        point(double x, double y){this->x = x; this->y = y;}
        //                        ---|---  ---
        //                           |      |
        //                           |      |
        //                         member   argument
    private:
        double x,y;
};

//However, the initialization method is better
//
class point{
    public:point(double x, double y):x(x),y(y){}
    //                              /   \
    //                             /     \
    //                            /       \
    //                         member    expression(argument)
    private:
        double x,y;
};
```
## C++ **new** use cases
```cpp
char* s = new char[size]; //get off heap
int* p = new int(9); //single int initialization
delete [] s; //delete an array
delete p; //delete single element
```
**NOTE: every time we use new, we need to think about delete**
**otherwise, memory leak**

## destructor
```~classname(){...}```
destructor always has void signature. It doesn't called with argument.

Example:
```cpp
struct slistelem{char data; slistelem* next;}

class slist{
    public:
        slist():h(0){} //empty list (0 is used as null pointer here.)
        ~slist(){release();} // destructor
        //...
        void prepend(char *c){
            slistelem* temp = new slistelem;
            temp -> next = h;
            temp -> data = c;
            h = temp; //update h
        }
    private:
        slistelem* h; // list head
}
```

we can also declare method outside class scope
```cpp
slist::~slist(){
    cout<< "destructor is called"<<endl;
    // just for demonstration -debug
    release(); // auxialy function
               // will be taught latter
}
```
## Graph

Generate a random graph can be thought as generating a random matrix.

```cpp
bool** graph;
srand(time(0)); // seed rand()
graph = new bool*[size];

for(int i; i<size;++i){
    graph[i] = new bool[size];
}//heap create 2-d array of bool

for(int i=0; i< n;++i){
    for(int j=0; j<m;++j){
        if (i==j){
            graph[i][j] = false; // No self loop
        }else{
            graph[i][j] = (prob()<0.19);
        }
    }
}
```

Check whether a node is connected to the graph.
```cpp
bool is_connected(bool *graph[], int size){
    int old_size = 0, c_size = 0;
    bool* close = new bool[size];
    bool* new = new bool[size];
    for(int i =0; i <size;++i){
        open[i]=close[i]=false;
    }
    open[0] = true;

    while(c_size<size){
        for(int i =0;i<size;++i){
            old_size = c_size;
            if(open[i]&&(close[i]==false)){
                close[i]=true;
                c_size++;
            }
        }
    }
}
```

### (3-9) More elaborate list

```cpp
class list{
public:
    list():head(0),cursor(0){} // Default constructor
    list(const int* arr, int n); // transfer data from one const array to list
    list(const list& lst); // copy constructor
    ...
    ~list();//delete; destructor
private:
    list_element* head;
    list_element* cursor;
};

```

### Deep copy VS referential copy

```cpp
list::list(const list&lst){
    if(lst.head == nullptr){
        head = nullptr;
        cursor = nullptr;
    }
    else{
        //setup
        cursor = lst.head;
        list_element *h = new list_element();
        list_element* previous;
        head = h;
        h ->d = lst.head->d;
        previous = h;
    }
    for(cursor = lst.next; cursor != nullptr){
        h = new list_element();
        h->d = cursor->d;
        previous->next = h;
        cursor = cursor->next;
        previous = h;
    }
    cursor = head;
}
```

### Destructor

C++ good community member:
    - every time use a new, create de-allocation method

```cpp
list::~list(){
    for (cursor = head; cursor != nullptr){
        cursor = cursor->next;
        delete head;
        head = cursor;
    }
}
```

**Valgrind** can be used for checking the memory leak;

A example.
```cpp
int main(){
    list a, b;
    int data[10] = {3, 4, 5,6,7,8};
    list d(data, 6);
    list d(data, 10);
    a.prepend(9);
    a.prepend(8);
    cout << "list a" << endl;
    a.print();
}
```