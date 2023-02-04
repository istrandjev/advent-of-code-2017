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

int main() {
    vector<int> a;
    a.push_back(0);
    int current = 0;
    int step_size = 359;
    for (int i = 1; i <= 2017; ++i) {
        int target = (current + step_size) % a.size();
        a.insert(a.begin() + target + 1, i);
        current = target + 1;
    }
    cout << "Part 1 " << a[(current + 1) % a.size()] << endl;
    int target_size = 50000001;
    int answer = 0;
    current = 0;
    for (int i = 1; i <= target_size; ++i) {
        int target = (current + step_size) % i + 1;
        if (target == 1) {
            answer = i;
        }
        current = target;
    }
    cout << "Part 2 " << answer << endl;
    return 0;
}