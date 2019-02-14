#include <array>
#include <iostream>
#include <vector>

using namespace std;

template <class T, int n>
class my_container {
public:
    my_container() { a = new T[n]; }
    ~my_container() { delete[] a; }
    explicit my_container(T* b) : my_container() {
        for (int i = 0; i < n; ++i) {
            a[i] = b[i];
        }
    }

private:
    T* a;
};

int main() {
    my_container<array<int, 20>, 15> data;
    vector<int> b{10, 1};
    // data(&b);
}