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

/*
  \ n  /
nw +--+ ne
  /    \
-+      +-
  \    /
sw +--+ se
  / s  \
  */
int moves[6][2] = {{-1, 1}, {0, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, 0}};
unordered_map<string, int> dirs{{"n", 0}, {"ne", 1}, {"se", 2}, {"s", 3}, {"sw", 4}, {"nw", 5}};

vector<string> split(const string& s, char delim=' ') {
    vector<string> res;
    string cur;
    for (auto c : s) {
        if (c == delim) {
            res.push_back(cur);
            cur = "";
        } else {
            cur.push_back(c);
        }
    }
    if (s.back() != delim) {
        res.push_back(cur);
    }
    return res;
}
int get_steps_needed(int x, int y) {
    int steps_needed;
    if (x * y > 0) {
        steps_needed = abs(x) + abs(y);
    } else {
        steps_needed = max(abs(x), abs(y));
    }
    return steps_needed;
}
int main() {
    int x = 0, y = 0;
    string s;
    getline(cin, s);
    vector<string> steps = split(s, ',');
    int furthest = 0;
    for (const string& step: steps) {
        int mi = dirs[step];
        x += moves[mi][1];
        y += moves[mi][0];
        furthest = max(furthest, get_steps_needed(x, y));
    }
    
    cout << "Part 1 " << get_steps_needed(x, y) << endl;
    cout << "Part 2 " << furthest << endl;
    return 0;
}