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

#include <iostream>
#include <vector>

using std::vector;

class UndirectedGraph {
   public:
    UndirectedGraph(int vertices);
    ~UndirectedGraph() { release(); }
    void release(){};
    void print();
    bool set_single_edge(int vertice_a, int vertice_b, int distance);
    int getdistance(int vertice_a, int vertice_b);

   private:
    int size;
    vector<vector<int>> data;
    bool is_not_outbound(int vertice_a, int vertice_b);
};

// initialize the number of vertices in the graph.
// the graph is stored in a 2-d vector
// initialize all the value as -1 for no connection
// distance can be value that equals or greater than 0
UndirectedGraph::UndirectedGraph(int vertices) : size(vertices) {
    data = vector<vector<int>>(size, vector<int>(size, -1));
    // initial the distance from vertice i to i as 0;
    for (int i = 0; i < size; ++i) {
        data[i][i] = 0;
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
        throw("Outbound error: vertices not exist!");
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

int main() {
    UndirectedGraph g = UndirectedGraph(10);
    g.print();
    g.set_single_edge(1, 2, 10);
    g.set_single_edge(3, 4, 5);
    std::cout << g.getdistance(3, 4) << "\n";
    std::cout << g.getdistance(4, 3) << "\n";
    g.print();
};