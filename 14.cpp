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

string knot_hash(const string& input) {
    int limit = 256;
    vector<int> a(limit);
    iota(all(a), 0);
    vector<int> lengths;
    for (auto c : input) {
        lengths.push_back((int)c);
    }       
    lengths.insert(lengths.end(), {17, 31, 73, 47, 23});
    int current = 0, skip_size = 0;
    for (int round = 0; round < 64; ++round) {
        for (int il = 0; il < (int)lengths.size(); current = (current + lengths[il] + skip_size) % limit, ++il, skip_size++) {
            int l = lengths[il];
            if (l > limit) {
                continue;
            }
            int from = current;
            int to = (current + l - 1) % limit;
            for (int i = 0; i < l / 2; ++i) {
                swap(a[from], a[to]);
                from = (from + 1) % limit;
                to = (to - 1 + limit) % limit;
            }
        }
    }
    string result;
    for (int bi = 0; bi < limit; bi += 16) {
        int res = 0;
        for (int i = 0; i < 16; ++i) {
             res ^= a[bi + i];
        }
        for (int i = 7; i >= 0; --i) {
            result.push_back((res & (1 << i)) ? '#' : '.');
        }
    }
    return result;
}

int moves[4][2] = { { -1, 0 }, { 0, 1 }, { 1, 0 }, { 0, -1 } };
int main() {
    string input_key = "jzgqcdpd";
    vector<string> rows;
    for (int index = 0; index < 128; ++index) {
        rows.push_back(knot_hash(input_key + "-" + to_string(index)));
    }
    int res1 = 0;
    for (auto row : rows) {
        for (auto c : row) {
            res1 += (c == '#');
        }
    }
    cout << "Part 1: " << res1 << endl;
    vector<vector<int> > vis(128, vector<int>(128, -1));
    int res2 = 0;
    for (int i = 0; i <128; ++i) {
        for (int j = 0; j < (int)rows[i].size(); ++j) {
            if (vis[i][j] != -1 || rows[i][j] != '#') {
                continue;
            }
            queue<pair<int, int> > q;
            q.push({i, j});
            vis[i][j] = res2;
            while (!q.empty()) {
                pair<int, int> c = q.front();
                q.pop();
                for (int l = 0; l < 4; ++l) {
                    pair<int, int> t(c.first + moves[l][0], c.second + moves[l][1]);
                    if (t.first < 0 || t.second < 0 || t.first >= 128 ||t.second >= 128) {
                        continue;
                    }
                    if (vis[t.first][t.second] != -1 || rows[t.first][t.second] != '#') {
                        continue;
                    }
                    vis[t.first][t.second] = res2;
                    q.push(t);
                }
            }
            res2++;
        }
    }
    cout << "Part 2: " << res2 << endl;
    return 0;
}