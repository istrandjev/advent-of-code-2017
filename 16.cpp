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
    string current;
    for (char c = 'a'; c <= 'p'; ++c) {
        current.push_back(c);
    }
    string s;
    getline(cin, s);
    regex rotate("s(\\d+)");
    regex exchange("x(\\d+)/(\\d+)");
    regex partner("p([a-p])/([a-p])");
    vector<string> commands = split(s, ',');
    smatch match;
    unordered_map<string, int> visited;
    vector<string> olds;
    olds.push_back(current);
    visited.insert({current, 0});
    int target_number = 1000 * 1000 * 1000;
    for (int i = 1; i <= target_number; ++i) {
        for (auto command : commands) {
            if (regex_match(command, match, rotate)) {
                int number = stoi(match.str(1));
                int rem = (int)current.size() - number;
                current = current.substr(rem) + current.substr(0, rem);
            } else if (regex_match(command, match, exchange)) {
                int x = stoi(match.str(1));
                int y = stoi(match.str(2));
                swap(current[x], current[y]);
            } else if (regex_match(command, match, partner)) {
                int xi, yi;
                for (int i = 0; i < (int)current.size(); ++i) {
                    if (current[i] == match.str(1)[0]) {
                        xi = i;
                    } 
                    if (current[i] == match.str(2)[0]) {
                        yi = i;
                    }
                }
                swap(current[xi], current[yi]);
            } else {
                cout << "Could not parse command " << command << endl;
                exit(1);
            }
        }
        if (i == 1) {
            cout << "Part 1 " << current << endl;
        }
        auto it = visited.find(current);
        if (it != visited.end()) {
            int cycle_len = i - it->second;
            int target = (target_number - it->second) % cycle_len;
            cout << "Part 2 " << olds[it->second + target] << endl;
            break;
        }
        visited.insert({current, i + 1});
        olds.push_back(current);
    }
    return 0;
}