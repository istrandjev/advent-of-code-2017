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
#define all(x) x.begin(), x.end()
using namespace std;
typedef long long ll;

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

int main() {
    string s;
    int cnt1 = 0;
    int cnt2 = 0;
    while (getline(cin, s)) {
        vector<string> tokens = split(s);
        unordered_set<string> met;
        unordered_set<string> met_sorted;
        bool valid = true;
        bool valid2 = true;
        for (auto token : tokens) {
            met.insert(token);
            sort(all(token));
            met_sorted.insert(token);
        }
        cnt1 += (met.size() == tokens.size());
        cnt2 += (met_sorted.size() == tokens.size());
    }
    cout << "Part 1 " << cnt1 << endl;
    cout << "Part 2 " << cnt2 << endl;
    return 0;
}