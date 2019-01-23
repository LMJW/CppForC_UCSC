#include <exception>
#include <iostream>
#include <queue>
#include <tuple>
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
        if (distance < 0) {
            throw invalid_argument("The edge length cannot be negative!");
        }

        adj_[index_for(v1, v2)] = distance;
        adj_[index_for(v2, v1)] = distance;
    }

    /// Remove edge
    /// @parm v1,v2 indexes of vertices
    void remove_edge(unsigned int v1, unsigned int v2) {
        adj_[index_for(v1, v2)] = 0;
        adj_[index_for(v2, v1)] = 0;
    }

    /// Get the edge length between two vertices
    /// @pram v1,v2 vertices
    /// @return length of edge
    double get_edge_value(unsigned int v1, unsigned int v2) const {
        return adj_[index_for(v1, v2)];
    }

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

/// we can use the priority queue module provided by standard library
/// In this case, we will just use the standard library

class ShortestPath {
public:
    /// ShortestPath takes an graph object and calculate the shortest distance
    /// from starting node to all other nodes
    ///
    /// @pram g Graph object
    /// @pram start unsigned int as starting vertices
    ShortestPath(Graph& g, unsigned int start)
        : g_(g), distances(g.V()), startnode(start) {
        compute();
    }

    /// @pram t the target node
    /// @return the distance from source node to target node
    double operator[](unsigned int t) { return distances[t]; }

protected:
    void compute() {
        priority_queue<NodeDist> openset;
        openset.push(make_tuple(startnode, 0));
        while (!openset.empty()) {
            auto p = openset.top();
            unsigned int v = get<0>(p);
            double d = get<1>(p);
            openset.pop();
            if (distances[v] > d) {
                distances[v] = d;
            }
            auto neis = g_.neighbours(v);
        }
    }

private:
    Graph g_;
    vector<double> distances;
    unsigned int startnode;

    using NodeDist = tuple<unsigned int, double>;
};

struct NodeDist {
    unsigned int ver;
    double dis;
    bool operator<(const NodeDist& n2) { return dis < n2.dis; };
};
