// Convert this program to C++
// change to C++ io to one line comments
// change defines of constants to const
// change array to vector<>
// inline any short function

#include <iostream>
#include <vector>

using namespace std;

const int N = 40;

template <class summable>
inline summable sum(int n, vector<summable> d) {
    // input argument:
    // n: number of elements in the summable vector
    // d: the vector of summable
    //
    // Return: res
    summable res = 0;

    for (int i = 0; i < n; ++i) {
        res += d[i];
    }
    return res;
}

int main() {
    vector<int> data(N);

    for (int i = 0; i < N; ++i) {
        data[i] = i;
    }

    sum(N, data);

    cout << "sum is : " << sum(N, data) << endl;
    return 0;
}