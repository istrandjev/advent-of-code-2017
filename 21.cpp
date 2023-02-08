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

struct rule {
    vector<string> input;
    vector<string> output;
};
vector<string> parse_pattern(const string& pattern) {
    return split(pattern, '/');
}

vector<string> rotate90(const vector<string>& patch) {
    int n = (int)patch.size();
    vector<string> result(n, string(n, '.'));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            result[j][n - 1 - i] = patch[i][j];
        }
    }
    return result;
}
vector<string> flip_patch(const vector<string>& patch) {
    int n = (int)patch.size();
    vector<string> result(n, string(n, '.'));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            result[i][n - 1 - j] = patch[i][j];
        }
    }
    return result;
}
bool match(const vector<string>& patch, const vector<string>& pattern) {
    vector<string> current = patch;
    for (int flip = 0; flip < 2; ++flip) {
        for (int rotation = 0; rotation < 4; ++rotation) {
            if (current == pattern) {
                return true;
            }
            current = rotate90(current);
        }
        current = flip_patch(current);
    }
    return false;
}
vector<string> apply_rule(const vector<string>& patch, const vector<rule>& rules) {
    for (const auto& rule: rules) {
        if (match(patch, rule.input)) {
            return rule.output;
        }
    }
    cout << "Could not find a matching rule! " << endl;
    return vector<string>();
}
vector<string> do_iteration(const vector<string>& grid, const vector<rule>& rules2, const vector<rule>& rules3) {
    vector<string> result;
    int n = (int)grid.size();
    int new_n;
    int step;
    if (n % 2 == 0) {
        new_n = (n / 2) * 3;
        step = 2;
    } else {
        new_n = (n / 3) * 4;
        step = 3;
    }
    result.resize(new_n, string(new_n, '.'));
    const vector<rule>& rules = (step == 2 ? rules2 : rules3);
    int n_step = (int)rules.back().output.size();
    for (int i = 0; i < n; i += step) {
        for (int j = 0; j < n; j += step) {
            vector<string> patch(step, string(step, '.'));
            for (int ii = 0; ii < step; ++ii) {
                for (int jj = 0; jj < step; ++jj) {
                    patch[ii][jj] = grid[i + ii][j + jj]; 
                }
            }
            vector<string> output = apply_rule(patch, rules);
            int base_i = (i / step) * n_step;
            int base_j = (j / step) * n_step;
            for (int ii = 0; ii < n_step; ++ii) {
                for (int jj = 0; jj < n_step; ++jj) {
                    result[base_i + ii][base_j + jj] = output[ii][jj];
                }
            }       
        }
    }
    return result;
}

int main() {
    regex rule_re("([.#/]+) => ([.#/]+)");
    string s;
    smatch match;
    vector<rule> rules3, rules2;
    while (getline(cin, s)) {
        if (regex_match(s, match, rule_re)) {
            auto rule_input = parse_pattern(match.str(1));
            auto rule_output = parse_pattern(match.str(2));
            if (rule_input.size() == 2) {
                rules2.push_back(rule{rule_input, rule_output});
            } else {
                rules3.push_back(rule{rule_input, rule_output});
            }
        } else {
            cout << "Could not parse rule " << s << endl;
        }
    }
    vector<string> grid{".#.", "..#", "###"};
    auto count_pixels = [&](int iterations) {
        for (int it = 0; it < iterations; ++it) {
            grid = do_iteration(grid, rules2, rules3);
        }
        int res = 0;
        for (auto row : grid) {
            for (auto cell : row) {
                res += (cell == '#');
            }
        }
        return res;
    };
    
    cout << "Part 1 " << count_pixels(5) << endl;
    cout << "Part 2 " << count_pixels(18 - 5) << endl;

    return 0;
}