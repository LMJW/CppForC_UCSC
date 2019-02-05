#include <exception>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
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
                current = nodestatus::BLUE;
                break;
            case 2:
                current = nodestatus::RED;
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
    /// @pram n use 1-d array to store all the nodes
    /// nodes can be accessed through r*grid_+c
    HexBoard(unsigned int n) : nodes(n * n, HexNode()), grid_(n), turns(true) {}
    nodestatus get_node_status(unsigned int r, unsigned int c) {
        return nodes[index_of(r, c)].current;
    }

    /// if node is still blank, then it's a valid move
    /// @pram r,c node position
    bool check_blank(unsigned int r, unsigned int c) {
        return get_node_status(r, c) == nodestatus::BLANK;
    }

    bool check_is_blue(unsigned int idx) {
        return nodes[idx].current == nodestatus::BLUE;
    }

    bool check_is_red(unsigned int idx) {
        return nodes[idx].current == nodestatus::RED;
    }

    /// To determine if one player win, I will use a DFS search to find a path
    /// from one edge to opposite edge. If I can find, then that means this
    /// player did not win.
    ///
    /// Assume the first player, BLUE, needs to find a path from top to bottom.
    /// And the second player, RED, needs to go from left to right.
    ///
    /// To check if player blue win, we need to start from left side, do a dfs
    /// search to see if we can get to the right side of grid. If we cannot,
    /// that means the player blue wins. Conversely, we need to start from top
    /// edge to do dfs and see if we can get to the bottom edge.

    /// @pram using int to indicate which player we are talking about
    /// @return true if this player wins
    bool check_win(int player) {
        vector<unsigned int> start_nodes;
        unordered_set<unsigned int> end_nodes;
        switch (player) {
            case 1:  /// if player blue wins, that means no path from left to
                     /// right edge
                for (unsigned int i = 0; i < grid_; ++i) {
                    if (!check_is_blue(index_of(i, 0))) {
                        /// the start point can only be no blue hex
                        start_nodes.push_back(index_of(i, 0));
                    }
                    if (!check_is_blue(index_of(i, grid_ - 1))) {
                        /// the end point must not be blue point
                        end_nodes.insert(index_of(i, grid_ - 1));
                    }
                }
                break;

            case 2:  /// if player red wins, that means no path from top to
                     /// bottom
                for (unsigned int i = 0; i < grid_; ++i) {
                    if (!check_is_red(index_of(0, i))) {
                        start_nodes.push_back(index_of(0, i));
                    }
                    if (!check_is_red(index_of(grid_ - 1, i))) {
                        end_nodes.insert(index_of(grid_ - 1, i));
                    }
                }
                break;
        }
        unordered_set<unsigned int> has_gone;
        return _dfs_(start_nodes, end_nodes, has_gone, player);
    }

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

    /// @pram r, c the index of grid where player want to place their hex
    /// @return boolean to confirm whether player's move is successful
    /// if the move is not a valid move, a false will returned and the reason
    /// will be printed on the stdout
    bool place_hex(unsigned int r, unsigned int c) {
        unsigned int position;
        try {
            position = index_of(r, c);
        } catch (invalid_argument e) {
            cout << e.what() << endl;
            cout << "please re-enter a correct move:\n";
            return false;
        }
        if (check_blank(r, c)) {
            if (turns) {
                nodes[index_of(r, c)].move(1);
            } else {
                nodes[index_of(r, c)].move(2);
            }
            return true;
        }
        return false;
    }

    void start_game() {
        cout << "Game started. Press Ctrl+C if you want to quit game\n";
        cout << "the grid is a " << grid_ << "x" << grid_ << " grid.\n";
        cout << "The index starts from up left corner with index 0,0, and the "
                "down right corner with index "
             << grid_ - 1 << "," << grid_ - 1 << ".\n";
        cout << "You need to enter the index r c seperate with space to place "
                "your hex on the grid\n";

        auto bluewin = check_win(1);
        auto redwin = check_win(2);
        unsigned int r, c;
        while (!bluewin && !redwin) {
            if (turns) {
                cout << "Now is Blue player's turn:\n";
            } else {
                cout << "Now is Red player's turn:\n";
            }
            cin >> r >> c;
            /// check if the input is valid, if it is not valid, player need to
            /// reenter the next move
            while (!place_hex(r, c)) {
                cout << "(" << r << "," << c
                     << ") is invalid, please re-enter:\n";
                cin >> r >> c;
            }
            turns = !turns;
            draw();
            bluewin = check_win(1);
            redwin = check_win(2);
        }
        cout << "Game over!!!\nThe winner is ";
        if (bluewin) {
            cout << "BLUE\n!";
        } else if (redwin) {
            cout << "RED\n!";
        }
    }

private:
    vector<HexNode> nodes;
    unsigned int grid_;
    bool turns;  /// Indicate the current turn player : true->Blue ; false->Red
    unsigned int index_of(unsigned int r, unsigned int c) const {
        if (r > grid_ || c > grid_) {
            throw invalid_argument("input out of bound.");
        };
        return r * grid_ + c;
    }

    /// given a node index, find all its neighbors
    vector<unsigned int> get_neighbors(unsigned int idx) const {
        /// 1-d index to actual r, c index
        unsigned int r = idx / grid_;
        unsigned int c = idx % grid_;

        vector<unsigned int> neis;
        /// six possible neighbor options
        if (c + 1 < grid_) {
            if (r > 0) {
                neis.push_back(index_of(r - 1, c + 1));
            };
            neis.push_back(index_of(r, c + 1));
        };
        if (r + 1 < grid_) {
            neis.push_back(index_of(r + 1, c));
        };
        if (r > 0) {
            neis.push_back(index_of(r - 1, c));
        };
        if (c > 0) {
            if (r + 1 < grid_) {
                neis.push_back(index_of(r + 1, c - 1));
            };
            neis.push_back(index_of(r, c - 1));
        };

        return neis;
    }

    /// @pram start , a vector stores all the possible start points
    /// @pram end set, used to check if a node gets to the opposite edge
    /// @pram player, use to indicate the player. The reason for having this
    /// player is because in the DFS process, if a hex is occupied by other
    /// player, then the current search needs to eliminate this hex in search
    /// process. Player red and blue will not be able to reuse opponents' cell,
    /// that's why we need player index here;
    ///
    bool _dfs_(vector<unsigned int>& start,
               const unordered_set<unsigned int>& end,
               unordered_set<unsigned int>& has_gone,
               const unsigned int& player) {
        for (auto sn : start) {
            has_gone.insert(sn);
            auto iter = end.find(sn);
            if (iter != end.end()) {
                /// can find a path, thus player does not win
                return false;
            }
            const auto& nbs = get_neighbors(sn);
            vector<unsigned int> nextstart;

            if (player == 1) {  /// check player blue win or not
                /// so we check using all none blue hex to see if if connect
                /// from left to right
                for (auto e : nbs) {
                    auto it = has_gone.find(e);
                    if (it == has_gone.end() && !check_is_blue(e)) {
                        nextstart.push_back(e);
                    };
                }
            } else {
                /// check player red win or not
                /// so we need to use none-red hex
                for (auto e : nbs) {
                    auto it = has_gone.find(e);

                    if (it == has_gone.end() && !check_is_red(e)) {
                        nextstart.push_back(e);
                    };
                }
            }
            /// if we found a path, that means the current play does not win
            /// so we will directly return. Otherwise, we need to continue
            /// search untill all possible path are searched.
            if (!_dfs_(nextstart, end, has_gone, player)) {
                return false;
            };
        }
        return true;
    }
};

int main() {
    HexBoard hb(7);
    hb.start_game();
}