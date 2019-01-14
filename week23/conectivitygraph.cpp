/**
 * Home work Week 2 & Week 3
 * Basic requirement
 *
 *  - Write a set of constructors for declaring and initializing a graph.
 *
 *  - An edge will have a positive cost that is its distance.
 *
 *  - Have a procedure that produces a randomly generated set of edges with
 *    positive distances. Assume the graphs are undirected.
 *
 *  - The random graph procedure should have edge density as a parameter and
 *    distance range as a parameter. So a graph whose density is 0.1 would have
 *    10% of its edges picked at random and its edge distance would be selected
 *    at random from the distance range.
 *
 *  - The procedure should run through all possible undirected edges, say (i,j)
 *    and place the edge in the graph if a random probability calculation is
 *    less than the density.
 *
 *  - Compute for a set of randomly generated graphs an average shortest path.
 */

#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>

using std::vector;

class UndirectedGraph {
   public:
    UndirectedGraph(int vertices, float percentage, int max_distance, int seed);
    ~UndirectedGraph() { release(); };
    void release(){};
    void print();
    bool set_single_edge(int vertice_a, int vertice_b, int distance);
    int getdistance(int vertice_a, int vertice_b);

   private:
    int size, seed, maxdistance;
    float percentage;
    vector<vector<int>> data;
    bool is_not_outbound(int vertice_a, int vertice_b);
    bool prob();
    int rand_distance();
};

// Allow user to customize seed to generate reproducable result
// default seed equals to 0
// we use distance = -1 to represent no connectivity
UndirectedGraph::UndirectedGraph(int vertices,
                                 float p,
                                 int mdis = 100,
                                 int n = 0)
    : size(vertices), percentage(p), maxdistance(mdis), seed(n) {
    if (percentage < 0) {
        std::string errorMsg =
            std::string("percentage must not be negative number.\n");
        throw(std::runtime_error(errorMsg));
    } else if (percentage > 1) {
        std::string errorMsg =
            std::string("percentage must be less or equal to 1.\n");
        throw(std::runtime_error(errorMsg));
    }
    data = vector<vector<int>>(size, vector<int>(size, -1));
    for (int i = 0; i < size; ++i) {
        for (int j = i; j < size; ++j) {
            if (i == j) {
                data[i][j] = 0;
            } else if (prob()) {
                int t = rand_distance();
                data[i][j] = t;
                data[j][i] = t;
            }
        }
    }
}

void UndirectedGraph::print() {
    std::cout << "This graph is undirected graph." << std::endl;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            std::cout << data[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// Set a single edge distance by giving vertice a, b and distance
// return true if the distance is set successfully
bool UndirectedGraph::set_single_edge(int vertice_a,
                                      int vertice_b,
                                      int distance) {
    if (is_not_outbound(vertice_a, vertice_b)) {
        data[vertice_a][vertice_b] = distance;
        data[vertice_b][vertice_a] = distance;
        return true;
    }
    return false;
}

// Get the distance between two vertices
int UndirectedGraph::getdistance(int vertice_a, int vertice_b) {
    if (is_not_outbound(vertice_a, vertice_b)) {
        return data[vertice_a][vertice_b];
    } else {
        std::string errorMsg =
            std::string("Outbound error: vertice indexes are out of bound.");
        throw(std::runtime_error(errorMsg));
    }
};
// is_not_outbound:
// check the given vertices number are not outbound of the 2d matrix
// neither larger than the size and less than 0
bool UndirectedGraph::is_not_outbound(int vertice_a, int vertice_b) {
    if (0 <= vertice_a < size && 0 <= vertice_b < size) {
        return true;
    }
    std::cout << "\nVertice out of bound! " << std::endl;
    std::cout << "(" << vertice_a << "," << vertice_b << ") is larger than "
              << size - 1 << "." << std::endl;

    return false;
};

// generate random true value based on the probability input
// maximum percision is 4 digits after float operator
// such as 99.99%
//
// example: 0.1 means there will be 10% chance of get true
bool UndirectedGraph::prob() {
    float r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    return r < percentage;
}

int UndirectedGraph::rand_distance() {
    return rand() % maxdistance + 1;
}

int main() {
    UndirectedGraph g = UndirectedGraph(10, 0.3, 50);
    g.print();
};