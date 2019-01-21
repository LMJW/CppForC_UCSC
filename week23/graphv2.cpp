#include <exception>
#include <iostream>
#include <vector>

using namespace std;

class Graph {
public:
    /// initialize graph with number of vertices
    /// using adjacent matrix to store graph
    ///
    /// @pram n_v number of vertices
    /// @pram n_e number of edges
    /// @pram adj_ 1-D array to represent the adjcent matrix
    Graph(unsigned int v) : n_v(v), n_e(0), adj_(v * v, 0) {}

    /// @return number of vertices in graph
    unsigned int V() const { return n_v; }

    /// @return number of edges in graph
    unsigned int E() const { return n_e; }

    /// check whether two vertices has an edge
    /// @pram x, y vertice index
    /// @return true if two vertices are linked by an edge
    bool adjacent(unsigned int x, unsigned int y) const {
        return adj_[index_for(x, y)] > 0;
    }

    /// find all its neighbor vertices of the given vertice
    /// @pram vertice given vertice index
    /// @return a vector of vertices that are the neighbors of given vertices
    vector<unsigned int> neighbours(unsigned int vertice) const {
        vector<unsigned int> result;
        for (int i = 0; i < n_v; ++i) {
            if (adjacent(vertice, i)) {
                result.push_back(i);
            }
        }
        return result;
    }

    /// set the edge length between two nodes
    /// @pram v1, v2 indexes of two vertices
    /// @pram distance the edge length
    void set_edge(unsigned int v1, unsigned int v2, double distance) {
        adj_[index_for(v1, v2)] = distance;
        adj_[index_for(v2, v1)] = distance;
    }

    bool disconnect(node, node);
    D get_node_value(node);
    bool set_node_value(node, D);
    D get_edge_value(node, node);
    bool set_edge_value(node, node, D);

protected:
    /// @return the index of 1-d vector given two verices in adjcent matrix
    unsigned int index_for(unsigned int x, unsigned int y) const {
        /// have to consider the outbound error
        if (x >= n_v || y >= n_v) {
            throw invalid_argument("outbound of adjcent matrix!");
        }
        return x * n_v + y;
    }

private:
    const unsigned int n_v;
    unsigned int n_e;
    vector<double> adj_;
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
