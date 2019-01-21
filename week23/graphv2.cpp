#include <iostream>
#include <vector>

using namespace std;

class Graph {
public:
    /// init
    Graph(){};
    int vertices();
    int edges();
    bool adjacent(node, node);
    vector<node> neighbours(node, node);
    bool connect(node, node, D);
    bool disconnect(node, node);
    D get_node_value(node);
    bool set_node_value(node, D);
    D get_edge_value(node, node);
    bool set_edge_value(node, node, D);
};

template <class node>
class PriorityQueue {
public:
    void chgPriority(node);
    node minPriority();
    bool contains(node);
    bool insert(node);
    node top();
    int size();
};

template <class node, class D>
class ShortestPath {
public:
    vector<node> listVertices();
    vector<node> path(node, node);
    D path_size(node, node);
};
