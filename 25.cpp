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

struct Transition {
    int value;
    int delta_x;
    char next_state;
};

struct State {
    Transition rules[2];
    char name;
};

string parse_with_regex(const string& s, const string& re_str) {
    regex line_regex("\\s*" + re_str);
    smatch match;
    if (regex_match(s, match, line_regex)) {
        return match.str(1);
    } else {
        cout << "Could not parse " << s << " with regex " << re_str << endl;
        exit(1);
    }
}
char parse_name(const string& s) {
    string name = parse_with_regex(s, "In state ([A-Z]):");
    return name[0];
}

int parse_delta_x(const string& s) {
    string instruction = parse_with_regex(s, "- Move one slot to the (right|left).");
    return instruction == "left" ? -1 : 1;
}

int parse_transition(Transition& t) {
    string s;
    getline(cin, s);
    int return_value = stoi(parse_with_regex(s, "If the current value is (\\d):"));
    getline(cin, s);
    t.value = stoi(parse_with_regex(s, "- Write the value (\\d)."));
    getline(cin, s);
    t.delta_x = parse_delta_x(s);
    getline(cin, s);
    t.next_state = parse_with_regex(s, "- Continue with state ([A-Z]).")[0];    
    return return_value;
}

State parse_state() {
    State result;
    string s;
    getline(cin, s);
    result.name = parse_name(s);
    for (int i = 0; i < 2; ++i) {
        Transition transition;
        int tv = parse_transition(transition);
        result.rules[tv] = transition;
    }
    return result;
}

int main() {
    string s;
    getline(cin, s);
    char start_state = parse_with_regex(s, "Begin in state ([A-Z]).")[0];
    getline(cin, s);
    int steps = stoi(parse_with_regex(s, "Perform a diagnostic checksum after (\\d+) steps."));
    unordered_map<char, State> transitions;
    while (getline(cin, s)) {
        State current = parse_state();
        transitions[current.name] = current;
    }

    unordered_set<int> ones;
    int cx = 0;
    char current_state = start_state;
    for (int si = 0; si < steps; ++si) {
        int current_value = ones.count(cx);
        ones.erase(cx);
        auto it = transitions[current_state];

        int new_value = it.rules[current_value].value;
        if (new_value) {
            ones.insert(cx);
        }
        current_state = it.rules[current_value].next_state;
        cx += it.rules[current_value].delta_x;
    }
    cout << ones.size() << endl;
    return 0;
}