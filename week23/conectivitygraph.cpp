#include <iostream>
#include <vector>

using std::vector;

class graph {
   public:
    graph(int vertices) : size(vertices) {
        // initialize the number of vertices in the graph.
        // the graph is stored in a 2-d vector
        //
        // initialize all the value as -1 for no connection
        //
        // distance can be value that equals or greater than 0
        data = vector<vector<int>>(size, vector<int>(size, -1));
    };
    ~graph() { release(); }
    void release(){};
    void print() {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                std::cout << data[i][j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    };
    bool setedge(int vertice_a, int vertice_b, int distance) {
        if (is_not_outbound(vertice_a, vertice_b)) {
            data[vertice_a][vertice_b] = distance;
            return true;
        } else {
            return false;
        }
    };
    int getdistance(int vertice_a, int vertice_b) {
        if (is_not_outbound(vertice_a, vertice_b)) {
            return data[vertice_a][vertice_b];
        } else {
            return -2;
        }
    };

   private:
    int size;
    vector<vector<int>> data;
    bool is_not_outbound(int vertice_a, int vertice_b) {
        if (vertice_a < size && vertice_b < size) {
            return true;
        } else if (vertice_a >= size || vertice_b >= size) {
            std::cout << "\nVertice out of bound! " << std::endl;
            std::cout << "(" << vertice_a << "," << vertice_b
                      << ") is larger than " << size - 1 << "." << std::endl;
        }
        return false;
    };
};

int main() {
    graph g = graph(10);
    g.print();
    g.setedge(1, 2, 10);
    g.setedge(3, 4, 5);
    g.print();
};