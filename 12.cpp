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
    regex vertex("(\\d+) <-> (((\\d+)(, )?)+)");
    unordered_map<int, vector<int> > ne;
    smatch match;
    string s;
    while (getline(cin, s)) {
        if (!regex_match(s, match, vertex)) {
            cout << "Could not parse " << s << endl; 
            exit(1);
        }
        int v = stoi(match.str(1));
        if (!ne.count(v)) {
            ne.insert({v, vector<int>()});
        }
        for (auto other_str : split(match.str(2))) {
            if (other_str.back() == ',') {
                other_str.pop_back();
            }
            int other = stoi(other_str);
            if (!ne.count(other)) {
                ne.insert({other, vector<int>()});
            }       
            ne[v].push_back(other);
            ne[other].push_back(v);
        }
    }

    unordered_set<int> vis;
    queue<int> q;
    auto bfs = [&](int v) {
        vis.insert(v);
        q.push(v);
        while (!q.empty()) {
            int c = q.front();
            q.pop();
            for (auto nxt : ne[c]) {
                if (vis.count(nxt)) {
                    continue;
                }
                vis.insert(nxt);
                q.push(nxt);
            }
        }
    };
    bfs(0);
    cout << "Part 1 " << vis.size() << endl;
    int res = 1;
    for (auto vd : ne) {
        int v = vd.first;
        if (vis.count(v)) {
            continue;
        }
        res++;
        bfs(v);
    }
    cout << "Part 2 " << res << endl;
    return 0;
}