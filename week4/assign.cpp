#include <algorithm>
#include <exception>
#include <fstream>
#include <iostream>
#include <iterator>
#include <ostream>
#include <random>
#include <string>
#include <vector>

using namespace std;

/// define a triplet struct to store the edge length
/// as we are going to use Kruskal Minimum Spanning Tree Algorithm
/// store in a vector of triplet is more convient for computation
struct mytriplet {
    unsigned int v1;
    unsigned int v2;
    double edge_length;
    mytriplet(unsigned int x, unsigned int y, double d)
        : v1(x), v2(y), edge_length(d) {}
    ~mytriplet(){};

    /// overload operator to be able to use for sorting
    friend bool operator<(const mytriplet& t1, const mytriplet& t2) {
        return t1.edge_length < t2.edge_length;
    }

    friend bool operator>(const mytriplet& t1, const mytriplet& t2) {
        return t2 < t1;
    }

    friend ostream& operator<<(ostream& out, const mytriplet& t) {
        out << "vertices: (" << t.v1 << "," << t.v2 << ") | "
            << "edge_length: " << t.edge_length << " ;";
        return out;
    }
};

class Graph {
public:
    Graph() {}
    ~Graph() {}
    Graph(unsigned int v)
        : vertices_(v), adjcent_m(v * v, false), cost_m(v * v, 0) {}

    Graph(string path) : path_(path) { load_graph(); }

    /// publice member functions
    /// @pram x, y unsigned int for indict the vertices
    /// @pram dis to indicate the edge length
    void set_edge(unsigned int x, unsigned int y, double dis) {
        adjcent_m[index_for(x, y)] = true;
        cost_m[index_for(x, y)] = dis;
        mytriplets.push_back(mytriplet(x, y, dis));
    }

    bool isconnected(unsigned int x, unsigned int y) {
        return adjcent_m[index_for(x, y)];
    }

    double get_edge(unsigned int x, unsigned int y) {
        return cost_m[index_for(x, y)];
    }

    /// @return number of vertices in the graph
    unsigned int V() const { return vertices_; }

    /// get neighbors
    vector<unsigned int> get_neighbors(unsigned int v1) {
        vector<unsigned int> res;
        for (unsigned int i = 0; i < vertices_; ++i) {
            if (isconnected(v1, i)) {
                res.push_back(i);
            }
        }
        return res;
    }

    /// Print out the cost matrix and adjcent matrix
    void print() {
        cout << "\nCost matrix of the graph: \n";
        for (int i = 0; i < vertices_; ++i) {
            for (int j = 0; j < vertices_; ++j) {
                cout << cost_m[index_for(i, j)] << " ";
            }
            cout << "\n";
        }
        cout << "\nConnectivity matrix of the graph:\n";
        for (int i = 0; i < vertices_; ++i) {
            for (int j = 0; j < vertices_; ++j) {
                cout << adjcent_m[index_for(i, j)] << " ";
            }
            cout << "\n";
        }
    }

    /// check if the connectivity matrix matches the cost matrix
    /// eg. whether cost[i,j]> 0 && adjcent_m[i,j] = true
    ///
    /// For easy debug purposes
    void check() {
        int idx = 0;
        while (idx < adjcent_m.size()) {
            if (adjcent_m[idx] && cost_m[idx] > 0) {
                ++idx;
                continue;
            } else if (!adjcent_m[idx] && cost_m[idx] == 0) {
                ++idx;
                continue;
            } else {
                throw invalid_argument("mismatch graph internal data");
            }
        }
        cout << "\nCorrect graph data\n";
    }

    /// @return a vector of triplets for Minimum spanning tree to calculate
    vector<mytriplet> get_triplets() { return mytriplets; }

protected:
    unsigned int index_for(unsigned int x, unsigned int y) {
        if (x >= vertices_ || y >= vertices_) {
            throw invalid_argument("Out of bound error");
        }
        return x * vertices_ + y;
    }

    /// load the graph data from file
    void load_graph() {
        fstream graph_file(path_);
        istream_iterator<int> start(graph_file), end;

        vertices_ = *start;
        ++start;

        adjcent_m = vector<bool>(vertices_ * vertices_, false);
        cost_m = vector<double>(vertices_ * vertices_, 0);

        while (start != end) {
            auto v1 = *start;
            ++start;
            auto v2 = *start;
            ++start;
            auto v3 = *start;
            ++start;
            set_edge(v1, v2, v3);
            mytriplets.push_back(mytriplet(v1, v2, v3));
        }
    }

private:
    /// use two matrices to store the connectivity && distance of the edge
    unsigned int vertices_;
    vector<bool> adjcent_m;
    vector<double> cost_m;
    vector<mytriplet> mytriplets;
    string path_;
    /// TODO: Add color int the graph class
};

class MinSpanningTree {
public:
    MinSpanningTree() {}
    ~MinSpanningTree() {}
    MinSpanningTree(Graph& g) : _g(g) { kru_compute(); }

    void show_detail() {
        cout << "\nThe total cost of MST is : " << cost << ".\n";
        cout << "The edges are list as below:\n";
        for (auto e : edge_pairs) {
            cout << e << "\n";
        }
    }

    void show_overall() {
        cout << "\n The total cost of MST is: " << cost << ".\n";
    }

private:
    Graph _g;
    double cost = 0;
    vector<mytriplet> edge_pairs;
    void kru_compute() {
        /// Kruskal Minimum Spanning Tree Algorithm implementation
        auto tps = _g.get_triplets();

        sort(tps.begin(), tps.end());

        vector<bool> has_vertices(_g.V(), false);

        /// check if the two edges are in the set
        /// if both of them are in the set
        /// this will create loop, we will not add this edge in the vector
        /// else we will add new edge in the vector
        for (auto e : tps) {
            if (has_vertices[e.v1] && has_vertices[e.v2]) {
                continue;
            } else {
                edge_pairs.push_back(e);
                cost += e.edge_length;
                has_vertices[e.v1] = true;
                has_vertices[e.v2] = true;
            }
        }
    }
};

class Simulation {
public:
    /// @parm v number of vertices of graph
    /// @pram den_ graph density
    /// @pram min_d minimum distance of an edge
    /// @pram max_d maximum distance of an edge
    /// @pram t number of simulation time
    Simulation(unsigned int v = 50,
               double den = 0.4,
               double min_d = 1,
               double max_d = 10,
               unsigned int t = 3)
        : vertices_(v),
          density_(den),
          min_dis_(min_d),
          max_dis_(max_d),
          simulate_times(t),
          random_generator_(0),
          _distance_distribution(min_d, max_d),
          _existance_distribution(0, 1) {}
    ~Simulation() {
        for (int i = 1; i <= simulate_times; ++i) {
            cout << "\n***************************************\n";
            cout << "simulate No. " << i << " ...\n";
            simulate();
        }
    }

    /// Not optimized solution
    bool check_linked_graph(Graph& g_) {
        cout << "checking whether graph is linked ...\n";
        vector<bool> reference(g_.V(), false);

        vector<unsigned int> _mystack = {0};
        reference[0] = true;

        while (_mystack.size() > 0) {
            auto ver = _mystack.back();
            _mystack.pop_back();
            auto neibs = g_.get_neighbors(ver);  /// O(v) operation
            for (auto n : neibs) {
                if (!reference[n]) {
                    _mystack.push_back(n);
                    reference[n] = true;
                }
            }
        }

        for (auto r : reference) {
            if (!r) {
                return false;
            }
        }
        return true;
    }

private:
    unsigned int simulate_times;
    double density_;
    double min_dis_;
    double max_dis_;
    unsigned int vertices_;

    mt19937 random_generator_;
    uniform_real_distribution<double> _distance_distribution;
    uniform_real_distribution<double> _existance_distribution;

    /// simulate function;
    /// generate randomize graph to simulate the mst
    /// As our algorithm only works with linked graph(no isolated node or
    /// sub-graph), we need to check whether the graph is connected
    void simulate() {
        Graph g = Graph(vertices_);
        if (density_ <= 0) {
            throw invalid_argument("density should be larger than 0");
        } else if (density_ < 0.2) {
            cout << "\nDensity is small; random generated graph maybe "
                    "unlinked;\n";
            cout << "Program may run more iteration to get the linked graph;\n";
            cout << "You should set the density larger to get faster "
                    "simulation.\n";
        }
        cout << "generating random graph...\n";
        for (unsigned int i = 0; i < vertices_; ++i) {
            for (unsigned int j = i + 1; j < vertices_; ++j) {
                if (_existance_distribution(random_generator_) < density_) {
                    /// undirected graph
                    double d = _distance_distribution(random_generator_);
                    g.set_edge(i, j, d);
                    g.set_edge(j, i, d);
                }
            }
        }

        if (check_linked_graph(g)) {
            cout << "Graph is linked. processing minimum spanning tree "
                    "simulation ... \n";
            g.print();
            g.check();

            MinSpanningTree mst(g);
            mst.show_detail();
        } else {
            /// recursive regenerate graph to simulate the result if graph is
            /// not linked graph
            cout << "Graph is not linked. Regenerate graph ...\n";
            /// delete &g;
            /// ?DO I need to delete g?
            simulate();
        }
    };
};

int main() {
    cout << "Load sample graph data ....\n";
    Graph g = Graph("data.txt");
    g.print();
    g.check();
    MinSpanningTree mst(g);
    mst.show_detail();
    cout << "\n\n Start my simulation...\n";
    Simulation sl(10);
}