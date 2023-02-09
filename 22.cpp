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

int moves[4][2] = { { -1, 0 }, { 0, 1 }, { 1, 0 }, { 0, -1 } };

ll encode(int x, int y) {
    return (ll)x * 1000000000LL + (ll)y;
}

int main() {
    unordered_set<ll> infected;
    vector<string> a;
    string s;
    while (getline(cin, s)) {
        a.push_back(s);
    }
    int n = (int)a.size();
    int m = (int)a[0].size();
    int by = n / 2, bx = m / 2;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (a[i][j] == '#') {
                infected.insert(encode(i - by, j - bx));
            }
        }
    }
    int cy = 0, cx = 0;
    int res1 = 0;
    int bursts = 10000;
    int dir = 0;
    for (int it = 0; it < bursts; ++it) {
        ll cell_code = encode(cy, cx);
        bool is_infected = infected.count(cell_code);
        if (is_infected) {
            dir = (dir + 1) % 4;
        } else {
            dir = (dir + 3) % 4;
        }
        if (is_infected) {
            infected.erase(cell_code);
        } else {
            infected.insert(cell_code);
            res1++;
        }
        cy += moves[dir][0];
        cx += moves[dir][1];
    }

    cout << "Part 1 " << res1 << endl;
    unordered_map<ll, int> state;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (a[i][j] == '#') {
                state.insert({encode(i - by, j - bx), 3});
            }
        }
    }
    bursts = 10000000;
    cx = cy = 0;
    dir = 0;
    int res2 = 0;
    for (int iter = 0; iter < bursts; ++iter) {
        ll cell_code = encode(cy, cx);
        auto it = state.find(cell_code);
        if (it == state.end()) {
            dir = (dir + 3) % 4;
            state[cell_code] = 1;
        } else if (it->second == 1) {
            state[cell_code] = 3;
            res2++;
        } else if (it->second == 3) {
            dir = (dir + 1) % 4;
            state[cell_code] = 2;
        } else {
            dir = (dir + 2) % 4;
            state.erase(cell_code);
        }
        cy += moves[dir][0];
        cx += moves[dir][1];
    }
    cout << "Part 2 " << res2 << endl;
    return 0;
}