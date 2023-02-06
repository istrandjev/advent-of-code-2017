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
int main() {
    vector<string> a;
    string s;
    while (getline(cin, s)) {
        a.push_back(s);
    }
    pair<int, int> c;
    for (int i = 0; i < (int)a[0].size(); ++i) {
        if (a[0][i] == '|') {
            c = {0, i};
            break;
        }
    }
    int dir = 2;
    queue<pair<int, int> > q;
    q.push(c);
    string answer;
    auto is_valid = [&](const pair<int, int>& c){return c.first >= 0 && c.first < (int)a.size() && c.second >= 0 && c.second < (int)a[0].size();};
    int steps;
    for (steps = 1; !q.empty(); ++steps) {
        c = q.front();
        q.pop();
        pair<int, int> nxt{c.first + moves[dir][0], c.second + moves[dir][1]};
        if (!is_valid(nxt) || a[nxt.first][nxt.second] == ' ') {
            break;
        }
        q.push(nxt);
        if (isalpha(a[nxt.first][nxt.second])) {
            answer.push_back(a[nxt.first][nxt.second]);
        }
        if (a[nxt.first][nxt.second] == '+') {
            int ndir = (dir + 1) % 4;
            pair<int, int> t{nxt.first + moves[ndir][0], nxt.second + moves[ndir][1]};
            if (!is_valid(t) || a[t.first][t.second] == ' ') {
                ndir = (ndir + 2) % 4;
            }
            dir = ndir;

        }
    }
    cout << "Part 1 " << answer << endl;
    cout << "Part 2 " << steps << endl;
    return 0;
}