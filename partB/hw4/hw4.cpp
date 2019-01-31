#include <exception>
#include <iostream>
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

struct disjointset {
    /// use disjointset datastructure to store the graph for keeping track of
    /// each player's state
    ///
    /// we can define the rank of disjointset by the highest row number or
    /// highest col number
    ///
    /// we can use the parent and node distance to see if a player has win a
    /// game
};

class HexBoard {
public:
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

    /// @return 0 if nobody has win
    /// @return 1 is blue player win
    /// @return 2 if red player win
    int check_winner() {}

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

int main() {
    HexBoard hb(7);
    hb.draw();
}