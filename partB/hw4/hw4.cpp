#include <iostream>
#include <vector>

using namespace std;
enum class nodestatus : short { BLANK, RED, BLUE };

class HexBoard {
    HexBoard(unsigned int n) : nodes(n * n) {}

protected:
    vector<HexNode> nodes;
};

struct HexNode {
    unsigned int x_, y_;
    nodestatus current;
    HexNode(unsigned int x, unsigned int y)
        : x_(x), y_(y), current(nodestatus::BLANK) {}

    void print() {
        switch (current) {
            case nodestatus::RED:
                cout << "X";
                break;
            case nodestatus::BLUE:
                cout << "O";
                break;
            default:
                cout << ".";
                break;
        }
    }
};
