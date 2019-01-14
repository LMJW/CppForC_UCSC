#include <iostream>
#include <vector>

using std::vector;

class graph {
   public:
    // initialize the number of vertices in the graph.
    // the graph is stored in a 2-d vector
    // initialize all the value as -1 for no connection
    // distance can be value that equals or greater than 0
    graph(int vertices, bool graphtype = false)
        : size(vertices), gtype(graphtype) {
        data = vector<vector<int>>(size, vector<int>(size, -1));
        // initial the distance from vertice i to i as 0;
        for (int i = 0; i < size; ++i) {
            data[i][i] = 0;
        }
    };

    ~graph() { release(); }

    void release(){};

    void print() {
        std::cout << "This graph is ";
        if (gtype) {
            std::cout << "directed graph." << std::endl;
        } else {
            std::cout << "undirected graph." << std::endl;
        }
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                std::cout << data[i][j] << " ";
            }
            std::cout << std::endl;
        }
    };

    // Set a single edge distance by giving vertice a, b and distance
    // return true if the distance is set successfully
    bool set_single_edge(int vertice_a, int vertice_b, int distance) {
        if (is_not_outbound(vertice_a, vertice_b)) {
            if (gtype) {
                data[vertice_a][vertice_b] = distance;
            } else {
                data[vertice_a][vertice_b] = distance;
                data[vertice_b][vertice_a] = distance;
            }
            return true;
        } else {
            return false;
        }
    };

    // Get the distance between two vertices
    int getdistance(int vertice_a, int vertice_b) {
        if (is_not_outbound(vertice_a, vertice_b)) {
            return data[vertice_a][vertice_b];
        } else {
            throw("Outbound error: vertices not exist!");
        }
    };

   private:
    // size is the length of square matrix
    int size;
    // gtype indicate the graph type
    // false -> undirected graph
    // true -> directed graph
    bool gtype;

    // declare a 2-d vector to store graph
    vector<vector<int>> data;

    // is_not_outbound:
    // check the given vertices number are not outbound of the 2d matrix
    // neither larger than the size and less than 0
    bool is_not_outbound(int vertice_a, int vertice_b) {
        if (0 <= vertice_a < size && 0 <= vertice_b < size) {
            return true;
        }
        std::cout << "\nVertice out of bound! " << std::endl;
        std::cout << "(" << vertice_a << "," << vertice_b << ") is larger than "
                  << size - 1 << "." << std::endl;

        return false;
    };
};

int main() {
    graph g = graph(10, true);
    g.print();
    g.set_single_edge(1, 2, 10);
    g.set_single_edge(3, 4, 5);
    std::cout << g.getdistance(3, 4) << "\n";
    std::cout << g.getdistance(4, 3) << "\n";
    g.print();
};