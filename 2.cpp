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
    int sum1 = 0;
    int sum2 = 0;
    while (getline(cin, s)) {
        vector<string> tokens = split(s, '\t');
        vector<int> a;
        for (auto token: tokens) {
            a.push_back(stoi(token));
        }    
        sum1 += (*max_element(all(a)) - *min_element(all(a)));
        for (int i = 0; i < (int)a.size(); ++i) {
            for (int j = i + 1; j < (int)a.size(); ++j) {
                if (a[i] % a[j] == 0) {
                    sum2 += a[i] / a[j];
                }
                if (a[j] % a[i] == 0) {
                    sum2 += a[j] / a[i];
                }
            }
        }
    }
    
    cout << "Part 1 " << sum1 << endl;
    cout << "Part 2 " << sum2 << endl;
    return 0;
}