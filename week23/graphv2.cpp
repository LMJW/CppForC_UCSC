#include <exception>
#include <iostream>
#include <limits>
#include <queue>
#include <tuple>
#include <vector>

using namespace std;

const double MAX_DIST = numeric_limits<double>::max();

struct NodeDist {
    unsigned int ver;
    double dis;
    NodeDist(unsigned int v, double d) : ver(v), dis(d) {}
    ~NodeDist() {}
    // Operator overload for less than
    friend bool operator<(const NodeDist& n1, const NodeDist& n2) {
        return n1.dis < n2.dis;
    }
    // Operator overload for greater than
    friend bool operator>(const NodeDist& n1, const NodeDist& n2) {
        return n2 < n1;
    }
};

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
        : g_(g), dist_(g.V(), MAX_DIST), startnode(start) {
        compute();
    }

    /// @pram t the target node
    /// @return the distance from source node to target node
    double operator[](unsigned int t) { return dist_[t]; }
    ~ShortestPath() {}

protected:
    void compute() {
        priority_queue<NodeDist, vector<NodeDist>,
                       less<vector<NodeDist>::value_type> >
            openset;
        openset.push(NodeDist(startnode, 0));
        while (!openset.empty()) {
            auto p = openset.top();

            openset.pop();

            if (dist_[p.ver] > p.dis) {
                dist_[p.ver] = p.dis;
            }
            // cout << p.ver << " " << p.dis << " \n";
            vector<unsigned int> neis = g_.neighbours(p.ver);

            for (size_t i = 0; i < neis.size(); ++i) {
                double t = dist_[p.ver] + g_.get_edge_value(p.ver, neis[i]);
                if (dist_[neis[i]] > t) {
                    openset.push(NodeDist(neis[i], t));
                }
            }
        }
    }

private:
    Graph g_;
    vector<double> dist_;
    unsigned int startnode;
};

int main() {}