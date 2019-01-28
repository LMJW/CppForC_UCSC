#include <iostream>

using namespace std;

class point {
public:
    point() {}                       // default constructor
    point(double u) : x(u), y(0){};  // conversion constructor

private:
    double x, y;
};

class explict_point {
public:
    explict_point() {}
    explicit explict_point(double u) : x(u), y(0){};

private:
    double x, y;
};

int main() {
    point s;
    double d = 3.5;

    s = d;

    cout << "this workds\n";

    explict_point ss;

    // ss = d;
    cout << "this will not work\n";
}
