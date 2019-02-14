# 3.1 && 3.2 create c++ class

## Move sementic & delegate constructor

- In c++11, template is allowed to be array like, which allows us to be efficient

```cpp
        //parameter ; size
template <class T, int n>
class my_container{
public:
    my_container(){a= new T[n];} // should not be in parameter, it is in the template.
    ~my_container{delete[] a;}
    /// delete with [] means we are deleting an array object

    /// delegate constructor
    explicit my_container(T* b) : my_container() {
        for (int i = 0; i < n; ++i) {
            a[i] = b[i];
        }
    }

    /// copy constructor
    my_container(const my_container &b):my_constructor(){
        for (int i =0; i<n; ++i){
            a[i]= b.a[i];
        }
    }

private:
    T* a;
};

my_container data<int, 5>;
```

- default constructor `()`
- conversion constructor `1 argument`
- copy constructor `(const T &b)`

# 3.3 move constructor

```cpp
my_container(my_container &&b) noexcept{
    a = b.a;
    b.a = nullptr;
}
```

In this case, content are moved rather than copied.
`&&` to mean an rvalue address.

This is useful for the situation that the object is a temporary object and it may not be used again.

**Associated assignment**

```cpp
my_container& operator=(my_container&&b)noexcept{
    a = b.a;
    b.a = nullptr;
    return *this;
    // this is fixed const operations O(1)
    // right hand side got destroied
}
```

why use it?

```cpp
// efficient swap
void swap(my_container &b){
    my_container temp = move(b); // move is a operator indicate using operator=(  &&)
    b = move(*this);
    *this = move(temp);
}
```

## Min-max
move include
- legal
- plausiable

Plausible Move Generator

Evaluation

look ahead : -> min-max; alpha-beta; monte-carlo

Evaluating of static positions

  - chess/checker material count
  - points are made (count in the race)
  - In hex, how near it is to complete a path

Don Knuth

## 3.8 Polish notation

`(9+6)*(3-2)` => `9,6,+,3,2,-,*`(reverse polish notation)

Expression evaluation tree.

`(6(4+5)-25)/(2+3)` => `6 4 5 + * 25 - 2 3 + /`


## 3.9 Referential Garbage collection
- Rather than a full copy, we maintain pointers to an aggregate - and a use counter
- when use counter goes to zero, we actually call delete on an object
- When we create a new instance, use is initialized to 1

```cpp
class Node{
    friend class Tree;
    friend ostream& operator<<(ostream&, const Tree&);
    int use; //reference count gc
protected:
    Node(){use =1;}
    virtual void print(ostream&)=0; //pure virtual
    virtual ~Node(){}   // virtual destructor
    virtual int eval() = 0;
};
```

## 3.10 abstract base class

abstract base class =0 notation
-> undetermined method
```cpp
class LeafNode: public Node{
    friend class Tree;
    void print(ostream &o)=0;
    virtual int eval()=0;
}
```
LeafNode will have to overwrite the `eval` and `print` method with actual method.

```cpp
class IntNode:public LeafNode{
    friend class Tree;
    int n;
    void print(ostream & o){o<<n}; // print value
    IntNode(int k):n(k){}
public:
    int eval(){return n;} //evaluate value
};

class IdNode : public LeafNode{
    friend class Tree;
    char name;
    void print(ostream & o){o<<name}; // print value
    IntNode(char id):name(id){}
public:
    int eval(){return valtab[name];} //evaluate value os variable
};

class UnaryNode : public LeafNode{
    friend class Tree;
    char *op;
    Tree opnd;
    UnaryNode(char *a, Tree b): op(a), opnd(b){}
    void print(ostream & o){o<<"("<<op<<opnd<<")";}; // print value
public:
    int eval(){
        switch(op[0]){
            case "-":return (-opnd.eval());
            case "+":return (+opnd.eval());
            default:cerr<<"no operand\n"<<endl;
            return 0;
        }
    } //evaluate value
};

class BinaryNode : public LeafNode{
    friend class Tree;
    char *op;
    Tree left;
    Tree right;
    BinaryNode(char *a, Tree b, Tree c): op(a), left(b), right(c){}
    void print(ostream & o){o<<"("<<left<<op<<right<<")";}; // print value
public:
    int eval(){
        switch(op[0]){
            case "-":return (left.eval()-right.eval());
            case "+":return (left.eval()+right.eval());
            case "*":return (left.eval()*right.eval());
            default:cerr<<"no operand\n"<<endl;
            return 0;
        }
    } //evaluate value
};
```

This is also easily extensible.

## 3.9 Tree constructors
```cpp
Tree::Tree(int n){
    p = new IntNode(n);
};

Tree::Tree(char id){
    p = new CharNode(id);
};

Tree::Tree(char *op, Tree t){
    p = new UnaryNode(op, t);
};

Tree::Tree(char *op, Tree left, Tree right){
    p = new BinaryNode(op, left, right);
};

int main(){
    valtab['A'] = 3; valtab['B'] = 4;
    cout<<"A=3, B=4"<<endl;
    Tree t1=Tree("*", Tree("-",5), Tree("+", "A", 4));
    Tree t2=Tree("+", Tree("-","A",1), Tree("+", t1, "B"));

    cout<<"t1="<<t1<<";t2="<<t2<<endl; //parentsized version
    cout<<"t1:"<<t1.eval()<<"t2:"<<t2.eval()<<endl; // evaluation
}
```