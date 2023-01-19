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

int main() {
    string s;
    getline(cin, s);
    int sum = 0;
    int sum2 = 0;
    int n = (int)s.size();
    for (int i = 0; i < n; ++i) {
        if (s[i] == s[(i + 1) % n]) {
            sum += s[i] - '0';
        }
        if (s[i] == s[(i + n / 2) % n]) {
            sum2 += s[i] - '0';
        }
    }
    cout << "Part 1 " << sum << endl;
    cout << "Part 2 " << sum2 << endl;
    return 0;
}