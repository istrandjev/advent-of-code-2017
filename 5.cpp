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
    vector<int> a;
    
    int offset;
    while (cin >> offset) {
        a.push_back(offset);
    }
    vector<int> b = a;
    int current = 0;
    int step1 = 0;
    for (step1 = 0; current >=0 && current < (int)a.size(); ++step1) {
        int new_current = current + a[current];
        a[current]++;
        current = new_current;
    }
    
    cout << "Part 1 " << step1 << endl;
    a = b;
    int step2 = 0;
    current = 0;
    for (step2 = 0; current >=0 && current < (int)a.size(); ++step2) {
        int new_current = current + a[current];
        if (a[current] >= 3) {
            a[current]--;
        } else {
            a[current]++;
        }
        current = new_current;
    }
    
    cout << "Part 2 " << step2 << endl;
    return 0;
}
