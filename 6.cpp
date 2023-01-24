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

vector<int> step(const vector<int>& a) {
    int maxi = 0;
    vector<int> res = a;
    for (int i = 1; i < (int)a.size(); ++i) {
        if (a[i] > a[maxi]) {
            maxi = i;
        }
    }
    int val = a[maxi];
    res[maxi] = 0;
    for (int j = 1; j <= val; ++j) {
        res[(maxi + j) % (int)res.size()]++;
    }
    return res;
}

int main() {
    vector<int> a;
    int temp;
    while (cin >> temp) {
        a.push_back(temp);
    }
    map<vector<int>, int> met;
    met.insert({a, 0});
    for (int answer = 1; ; answer++) {
        vector<int> b = step(a);
        auto it = met.find(b);
        if (it != met.end()) {
            cout << "Part 1 " << answer << endl;
            cout << "Part 2 " << answer - it->second << endl;
            break;
        }
        met.insert({b, answer});
        a = b;
    }
    
    return 0;
}