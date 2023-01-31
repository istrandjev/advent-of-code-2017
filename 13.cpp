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

bool is_at_top(int x, int d) {
    return x % ((d - 1) * 2) == 0;
}

int main() {
    string s;
    vector<int> depth(100);
    while (getline(cin, s)) {
        int x, d;
        sscanf(s.c_str(), "%d: %d", &x, &d);
        depth[x] = d;
    }
    int res1 = 0;
    for (int i = 0; i < 100; ++i) {
        if (depth[i] == 0) {
            continue;
        }
        if (is_at_top(i, depth[i])) {
            res1 += i * depth[i];
        }
    }
    cout << "Part 1 " << res1 << endl; 
    int res2 = 0;
    for (;;res2++) {
        bool good = true;
        for (int i = 0; i < 100; ++i) {
            if (depth[i] == 0) {
                continue;
            }
            if (is_at_top(i + res2, depth[i])) {
                good = false;
                break;
            }
        }
        if (good) {
            break;
        }
    }
    cout << "Part 2 " << res2 << endl;
    return 0;
}