/**
 * Home work Week 2 & Week 3
 * Basic requirement:
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
 *
 *
 * Turn in:
 *  - Printout of program, 200 words on what you learned, and output
 *    showing the average path length calculation. Use densities: 20% and 40% on
 *    a graph of 50 nodes with a distance range of 1.0 to 10.0. To get an
 *    average path length, compute the 49 paths:
 *                         1 to 2, 1 to 3, 1 to 4, …, 1 to 50.
 *    [In an instance where there is no path between 1 and n, omit that value
 *    from the average. This should be very rare for the chosen density and size
 *    in this homework.]
 */

#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <map>
#include <set>
#include <vector>

using std::map;
using std::set;
using std::vector;

class UndirectedGraph {
   public:
    UndirectedGraph(int, float, int, int);
    ~UndirectedGraph() { release(); };
    void release(){};
    void print();
    float average_path_length();

   private:
    int size, seed;
    float maxdistance, percentage;
    vector<vector<float>> data;

    int find_min_dist(int, map<int, float>&, set<std::pair<int, int>>&);
    bool prob();
    float rand_distance();
};

// Allow user to customize seed to generate reproducable result
// default seed equals to 0
// we use distance = -1 to represent no connectivity
UndirectedGraph::UndirectedGraph(int vertices,
                                 float p,
                                 int mdis = 50,
                                 int n = 0)
    : size(vertices), percentage(p), maxdistance(mdis), seed(n) {
    // throw error if percentage is less than 0 or greater than 1
    if (percentage < 0) {
        std::string errorMsg =
            std::string("percentage must not be negative number.\n");
        throw(std::runtime_error(errorMsg));
    } else if (percentage > 1) {
        std::string errorMsg =
            std::string("percentage must be less or equal to 1.\n");
        throw(std::runtime_error(errorMsg));
    }
    data = vector<vector<float>>(size, vector<float>(size, -1));
    for (int i = 0; i < size; ++i) {
        for (int j = i; j < size; ++j) {
            if (i == j) {  // self distance should be 0
                data[i][j] = 0;
            } else if (prob()) {
                float t = rand_distance();
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

int UndirectedGraph::find_min_dist(int n,
                                   map<int, float>& close,
                                   set<std::pair<int, int>>& open) {
    float next_dist = maxdistance * size + 1;  // initial the distance to be max
    std::pair<int, int> p;
    int idx;  // index of the end node
    for (auto e : open) {
        int start = e.first;
        int end = e.second;

        float d = close[start] + data[start][end];
        if (d < next_dist) {
            next_dist = d;
            // idx = end;
            p = e;
        }
    }
    idx = p.second;
    open.erase(p);
    close[idx] = next_dist;
    return idx;
};

// Get the distance between two vertices
float UndirectedGraph::average_path_length() {
    map<int, float> closeset;
    set<std::pair<int, int>> openset;

    int c_node = 0;
    closeset[c_node] = 0;

    for (int j = 1; j < size; ++j) {
        if (data[c_node][j] != -1) {
            openset.insert(std::make_pair(c_node, j));
        }
    }
    while (openset.size() > 0) {
        // given current node & close set & open set
        // find the minimum & add to close set
        c_node = find_min_dist(c_node, closeset, openset);
        for (int j = 0; j < size; ++j) {
            if (data[c_node][j] > 0 && closeset.find(j) == closeset.end()) {
                openset.insert(std::make_pair(c_node, j));
            }
        }
    };
    float total = 0;
    for (auto e : closeset) {
        total += e.second;
    }
    if (closeset.size() < 2) {  // no node is connected to node 0
        return 0;
    }
    // In closeset, we store the distance from node 0 to node 0, in order to
    // calculate the average distance, we need to reduce closeset.size by 1
    return total / (closeset.size() - 1);
}

// generate random true value based on the probability input when construct
// the class. e.g: 0.1 means there will be 10% chance of get true
bool UndirectedGraph::prob() {
    // randomly generate a float number from 0 to 1
    float r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    return r < percentage;
}

float UndirectedGraph::rand_distance() {
    // random generate a distance from 1 to maximum distance.
    float r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    if (r == 0) {
        return rand_distance();
    }
    return r * maxdistance;
}

/**
 * What I've learned.
 *
 * I have learned that chooing a correct data structure can be essentially
 * important in solving the problem. For example, I was trying to use vector to
 * store the open and close set, but it turns out they are not good enough for
 * this purpose, as we need to insert and delete a node very often(as in
 * openset). Such operations on an vector is not efficient and can be hard to
 * write.
 *
 * I was thinking to use unordered_map and unordered_set to store both openset
 * and closeset. But I need to define custome hash function to be able to use it
 * as I am using std::pair to store start and end node. So I eventually choosed
 * std::set and std::map which has slight slow performance in search O(logN) but
 * relative easy to implement and relative fast in inserting and deleting nodes.
 */

int main() {
    // int n, d;
    // float f;
    // std::cin >> n >> f >> d;
    // UndirectedGraph g = UndirectedGraph(n, f, d);
    for (int i = 1; i < 11; ++i) {
        UndirectedGraph g = UndirectedGraph(50, 0.2, i);
        std::cout << "Average edge length for graph with 50 nodes, 20% prob of "
                     "having an edge and maximum distance of "
                  << i << " is: " << g.average_path_length() << "\n";
        g = UndirectedGraph(50, 0.4, i);
        std::cout << "Average edge length for graph with 50 nodes, 40% prob of "
                     "having an edge and maximum distance of "
                  << i << " is: " << g.average_path_length() << "\n";
    }
};