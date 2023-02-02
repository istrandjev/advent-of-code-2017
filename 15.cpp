#include <iostream>
#include <string>
#include <cstdio>
#include <set>
#include <map>
#include <vector>
#include <cstring>
#include <cctype>
#include <algorithm>
#include <numeric>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <regex>
#define all(x) x.begin(), x.end()
using namespace std;
typedef long long ll;


struct MyGenerator {
    MyGenerator(int seed, int factor, int required_divisor = 1) : state(seed), multiply_by(factor), required(required_divisor) {
    }
    ll next() {
        do {
            state = (state * multiply_by) % module;
        } while (state % required);
        return state;
    }
    ll state;
    ll multiply_by;
    ll required;
    static const ll module = 2147483647;
};
const int a_start = 679, b_start = 771;
int main() {
    MyGenerator a(a_start, 16807), b(b_start, 48271);
    int mask = (1 << 16) - 1;
    int res1 = 0;
    for (int i = 0; i < 40000000; ++i) {
        if ((a.next() & mask) == (b.next() & mask)) {
            res1++;
        }       
    }
    cout << "Part 1 " << res1 << endl;
    MyGenerator a2(a_start, 16807, 4), b2(b_start, 48271, 8);
    int res2 = 0;
    for (int i = 0; i < 5000000; ++i) {
        if ((a2.next() & mask) == (b2.next() & mask)) {
            res2++;
        }       
    }
    cout << "Part 2 " << res2 << endl;
    return 0;
}