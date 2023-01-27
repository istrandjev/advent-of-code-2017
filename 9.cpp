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
    string s;
    getline(cin, s);
    bool in_garbage = false;
    int depth = 0;
    int score1 = 0;
    int score2 = 0;
    for (int i = 0; i < (int)s.size(); ++i) {
        if (in_garbage) {
            if (s[i] == '!') {
                i++;
                continue;
            } else if (s[i] == '>') {
                in_garbage = false;
                continue;
            } else {
                score2++;
                continue;
            }
        } else if (s[i] == '{') {
            depth++;
            score1 += depth;
        } else if (s[i] == '}') {
            depth--;
        } else if (s[i] == '<') {
            in_garbage = true;
        }
    }
    cout << "Part 1 " << score1 << endl; 
    cout << "Part 2 " << score2 << endl; 
    return 0;
}