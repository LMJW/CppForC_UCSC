#include <iostream>
#include <ostream>
#include <vector>

using namespace std;

class Tree {
private:
    /* data */
public:
    Tree(/* args */);
    ~Tree();
};

class Node {
    friend class Tree;
    friend ostream& operator<<(ostream&, Tree&);
    int use;

protected:
    Node() { use = 1; }
    virtual void print(ostream&);
    virtual ~Node() {}
    virtual int eval();
};

class LeafNode : Node {
    void print(ostream& o) = 0;
    virtual int eval() = 0;
};

int main() {}