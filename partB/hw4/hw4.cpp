#include <exception>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;
enum class nodestatus : short { BLANK, RED, BLUE };

struct HexNode {
    /// Node does not know what position it is,
    /// it only know and care about its status.
    /// thus, the position info is not stored in the node object
    nodestatus current;
    HexNode() : current(nodestatus::BLANK) {}
    void move(unsigned int move) {
        switch (move) {
            case 1:
                current = nodestatus::RED;
                break;
            case 2:
                current = nodestatus::BLUE;
                break;
            default:
                break;
        }
    }
    void print() {
        switch (current) {
            case nodestatus::BLUE:
                cout << "X";
                break;
            case nodestatus::RED:
                cout << "O";
                break;
            default:
                cout << ".";
                break;
        }
    }
};

class HexBoard {
public:
    /// I define a modified disjointset as a member of hexboard class as it
    /// needs to access the hex position to determin whether two nodes are
    /// connected.
    struct disjointset;

    /// @pram n use 1-d array to store all the nodes
    /// nodes can be accessed through x*grid_+y
    HexBoard(unsigned int n) : nodes(n * n, HexNode()), grid_(n), turns(true) {}
    nodestatus get_node_status(unsigned int x, unsigned int y) {
        return nodes[index_of(x, y)].current;
    }

    /// if node is still blank, then it's a valid move
    /// @pram x,y node position
    bool check_move(unsigned int x, unsigned int y) {
        return get_node_status(x, y) == nodestatus::BLANK;
    }

    vector<unsigned int> get_neibours(unsigned int x, unsigned int y) {}

    void draw() {
        /// The draw include draw the node and the connection between nodes
        /// the number of connections between nodes has 1 less than number of
        /// nodes
        ///
        /// eg: if we have 7 nodes, we will have 6 lines connect all these nodes
        /// we can do this by having 7*2-1 = 13, and draw line when we have odd
        /// indexes
        bool even_row = true;
        auto l = grid_ * 2 - 1;
        for (int i = 0; i < l; ++i) {
            if (even_row) {
                for (int j = 0; j < i; ++j) {
                    cout << " ";  /// white spaces used for aligning the rows
                }
                /// print the row with nodes
                bool even = true;
                for (int j = 0; j < l; ++j) {
                    if (even) {
                        nodes[index_of(i / 2, j / 2)].print();
                    } else {
                        cout << " - ";
                    }
                    even = !even;
                }
            } else {
                /// print the seperation row
                /// print the blank space to align the graph
                for (int j = 0; j < i; ++j) {
                    cout << " ";
                }
                bool even = true;
                for (int j = 0; j < l; ++j) {
                    if (even) {
                        cout << "\\ ";
                    } else {
                        cout << "/ ";
                    }
                    even = !even;
                }
            }
            even_row = !even_row;
            cout << endl;
        }
    }

private:
    vector<HexNode> nodes;
    unsigned int grid_;
    bool turns;  /// Indicate the current turn player : true->Blue ; false->Red
    unsigned int index_of(unsigned int x, unsigned int y) {
        if (x > grid_ || y > grid_) {
            throw invalid_argument("input out of bound.");
        };
        return x * grid_ + y;
    }
};

class HexBoard ::disjointset {
    /// use disjointset datastructure to store the graph for keeping track of
    /// each player's state
    ///

    unordered_map<unsigned int, unsigned int> parent;

    /// @pram find the element in disjoint set
    /// if the element is not in the set
    /// insert this element into set
    /// and set its parent as itself
    ///
    /// parent will always larger or equal to node's value
    unsigned int find(unsigned int x, unsigned int y) {
        /// all neighbors
        /// (x-1,y),(x-1,y+1)
        /// (x,y-1),(x,y+1)
        /// (x+1,y-1),(x+1,y)
    }

    /// Union two sets, if x,y in the same set, it will not do anything
    /// when this function is executed, x and y should already in the set now
    void Union(unsigned int x, unsigned int y) { return; }

    /// Use print for debuging
    void print() {
        cout << "parent list:\n";
        for (auto e : parent) {
            cout << "(" << e.first << " , " << e.second << ");";
        }
        cout << endl;
    }
};

int main() {
    HexBoard hb(7);
    hb.draw();
    // disjointset df;
    // df.find(3);
    // df.find(4);
    // df.find(5);
    // df.Union(3, 4);
    // df.Union(4, 5);
    // df.Union(1, 6);
    // df.Union(1, 5);
    // df.print();
}