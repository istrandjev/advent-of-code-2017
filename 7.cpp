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

struct node {
    string name;
    vector<string> children;
    int number;
};
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

int get_weight(const map<string, node>& graph, const string& node_name) {
    auto it = graph.find(node_name);
    int result = it->second.number;
    for (auto c : it->second.children) {
        result += get_weight(graph, c);
    }
    return result;
}
const int inf = -100000;
int solve_part2(const map<string, node>& graph, const string& node_name) {
    auto it = graph.find(node_name);
    if (it->second.children.size() == 0) {
        return inf;
    }

    set<int> weights;
    int repeated = -1;
    for (auto c : it->second.children) {
        int w = get_weight(graph, c);
        if (weights.count(w)) {
            repeated = w;
        }
        weights.insert(w);
    }

    if (weights.size() == 1) {
        return inf;
    }
    weights.erase(repeated);
    for (auto c : it->second.children) {
        int w = get_weight(graph, c);
        if (w != repeated) {
            int temp = solve_part2(graph, c);
            if (temp != inf) {
                return temp;
            } else {
                auto v_it = graph.find(c);
                return v_it->second.number - (w - repeated);
            }
        }
    }
    return inf;
}

int main() {
    string s;
    regex node_data("(\\w+) \\((\\d+)\\)( -> ((([a-z]+)(, )?)*))?");
    smatch match;
    map<string, node> nodes;
    set<string> has_parent;
    while (getline(cin, s)) {
        if (regex_match(s, match, node_data)) {
            node current;
            current.name = match.str(1);
            current.number = stoi(match.str(2));
            if (match.str(3).size() > 0) {
                for (auto s : split(match.str(4))) {
                    if (s.back() == ',') {
                        s.pop_back();
                    }
                    has_parent.insert(s);
                    current.children.push_back(s);
                }
            }
            nodes[current.name] = current;
        }
    }
    string root;
    for (auto s : nodes) {
        if (has_parent.count(s.first) == 0) {
            root = s.first;
            break;
        }
    }
    cout << "Part 1 " << root << endl;
    cout << "Part 2 " << solve_part2(nodes, root) << endl;
    return 0;
}