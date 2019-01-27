#include <exception>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

using namespace std;

class Graph {
public:
    Graph() {}

    Graph(unsigned int v)
        : vertices_(v), adjcent_m(v * v, false), cost_m(v * v, 0) {}

    Graph(string path) : path_(path) { load_graph(); }

    /// publice member functions
    /// @pram x, y unsigned int for indict the vertices
    /// @pram dis to indicate the edge length
    void set_edge(unsigned int x, unsigned int y, double dis) {
        adjcent_m[index_for(x, y)] = true;
        cost_m[index_for(x, y)] = dis;
    }

    bool isconnected(unsigned int x, unsigned int y) {
        return adjcent_m[index_for(x, y)];
    }

    double get_edge(unsigned int x, unsigned int y) {
        return cost_m[index_for(x, y)];
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
    /// eg. whether cost[i,j]> 0 if adjcent_m[i,j] = true
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
        }
    }

private:
    /// use two matrices to store the connectivity && distance of the edge
    unsigned int vertices_;
    vector<bool> adjcent_m;
    vector<double> cost_m;
    string path_;
    /// TODO: Add color int the graph class
};

// class MinSpanningTree {
// }

// class Simulation {
// }

int main() {
    Graph g = Graph("data.txt");
    g.print();
    g.check();
}