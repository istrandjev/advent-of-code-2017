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

const int limit = 256;

int main() {
    vector<int> a(limit);
    iota(all(a), 0);
    regex number("(\\d+)");
    string s;
    getline(cin, s);
    string original_input = s;
    smatch match;
    vector<int> lengths;
    while (regex_search(s, match, number)) {
        lengths.push_back(stoi(match.str(1)));
        s = match.suffix().str();
    }
    for (int il = 0, current = 0, skip_size = 0; il < (int)lengths.size(); current = (current + lengths[il] + skip_size) % limit, ++il, skip_size++) {
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
    cout << "Part 1 " << a[0] * a[1] << endl;
    iota(all(a), 0);
    lengths.clear();
    for (auto c : original_input) {
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
    cout << "Part 2 ";
    for (int bi = 0; bi < 256; bi += 16) {
        int res = 0;
        for (int i = 0; i < 16; ++i) {
            res ^= a[bi + i];
        }
        printf("%02x", res);
    }
    cout << endl;
    return 0;
}