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

map<string, int> registers;


bool is_cond(const string& register_name, const string& comparison, int value) {
    if (registers.count(register_name) == 0) {
        registers[register_name] = 0;
    }
    int register_value = registers[register_name];
    if (comparison == "==") {
        return value == register_value;
    } else if (comparison == "!=") {
        return register_value != value;
    } else if (comparison == "<") {
        return register_value < value;
    } else if (comparison == ">") {
        return register_value > value;
    } else if (comparison == "<=") {
        return register_value <= value;
    } else if (comparison == ">=") {
        return register_value >= value;
    }
    cout << "Unknown comparison " << comparison << endl;
    return false;
}
void do_instruction(const string& register_name, bool is_inc, int amount, const string& cond_register, const string& comparison, int value) {
    if (!is_cond(cond_register, comparison, value)) {
        return;
    }

    if (registers.count(register_name) == 0) {
        registers[register_name] = 0;
    }
    auto it = registers.find(register_name);
    if (is_inc) {
        it->second += amount;
    } else {
        it->second -= amount;
    }
}
int main() {
    regex instruction("(\\w+) (inc|dec) (-?\\d+) if (\\w+) ([><=!]+) (-?\\d+)");
    string s;
    smatch match;
    int max_value_ever = 0;
    while (getline(cin, s)) {
        if (regex_match(s, match, instruction)) {
            do_instruction(match.str(1), match.str(2) == "inc", stoi(match.str(3)), match.str(4), match.str(5), stoi(match.str(6)));
        } else {
            cout << "Could not parse instruction " << s << endl; 
        }
        for (auto r : registers) {
            max_value_ever = max(max_value_ever, r.second);
        }
    }
    int max_value = 0;
    for (auto r : registers) {
        max_value = max(max_value, r.second);
    }
    cout << "Part 1 " << max_value << endl;
    cout << "Part 2 " << max_value_ever << endl; 
    return 0;
}