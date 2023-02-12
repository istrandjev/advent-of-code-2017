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

vector<pair<int, int> > parts;
vector<char> vis;
vector<vector<pair<int, int> > > ne;

int current;
int best;
int longest, longest_score;
int length;
void dfs(int v) {
    for (int i = 0; i < (int)ne[v].size(); ++i) {
        if (vis[ne[v][i].second]) {
            continue;
        }

        current += v + ne[v][i].first;
        length++;
        best = max(current, best);
        if (length >= longest) {
            longest = length;
            longest_score = max(current, longest_score);
        }
        vis[ne[v][i].second] = 1;
        dfs(ne[v][i].first);
        length--;
        vis[ne[v][i].second] = 0;
        current -= v + ne[v][i].first;
    }
}

int main() {
    pair<int, int> temp;
    int maxv = 0;
    while(scanf("%d/%d", &temp.first, &temp.second) != EOF) {
        if (temp.first > temp.second) {
            swap(temp.first, temp.second);
        }
        maxv = max(maxv, temp.first);
        maxv = max(maxv, temp.second);
        parts.push_back(temp);
    }
    sort(all(parts));
    ne.resize(maxv + 1);
    vis.resize(parts.size());
    for (int i = 0; i < (int)parts.size(); ++i) {
        const pair<int, int>& p = parts[i];
        ne[p.first].push_back({p.second, i});
        ne[p.second].push_back({p.first, i});
    }

    best = 0;
    current = 0;
    longest = 0;
    longest_score= 0;
    length = 0;
    dfs(0);
    cout << "Part 1 " << best << endl;
    cout << "Part 2 " << longest_score << endl;
    return 0;
}