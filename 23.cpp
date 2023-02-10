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

string get_modify_reg_regex_str(const string& command) {
    return command + " ([a-z]) ([a-z]|-?\\d+)";
}
regex set_value(get_modify_reg_regex_str("set"));
regex sub_value(get_modify_reg_regex_str("sub"));
regex mul_value(get_modify_reg_regex_str("mul"));
regex jump_nz("jnz ([a-z]|-?\\d+) ([a-z]|-?\\d+)");

struct Program;
typedef void (Program::*CommandFnType)(const string& a, const string&b);

struct Command {
    CommandFnType fn;
    string lhs;
    string rhs;
    Command(CommandFnType action_fn, const string& l, const string& r): fn(action_fn), lhs(l), rhs(r) {};
};

struct Program {
    Program() {
        program_pointer = 0;
        register_values.resize(256);
        number_mul_called = 0;
    }
    bool do_action() {
        if (program_pointer < 0 || program_pointer >= (int)commands.size()) {
            return false;
        }
        int cp = program_pointer;
        (this->*commands[program_pointer].fn)(commands[program_pointer].lhs, commands[program_pointer].rhs);
        if (program_pointer == cp) {
            program_pointer++;
        }
        return program_pointer >= 0 && program_pointer < (int)commands.size();
    }
    ll get_value(const string& value_str) const {
        if (value_str.size() == 1 && isalpha(value_str[0])) {
            return register_values[value_str[0]];
        } else {
            return stoll(value_str);
        }
    }

    void do_set(const string & lhs, const string& rhs) {
        register_values[lhs[0]] = get_value(rhs);
    }

    void do_sub(const string & lhs, const string& rhs) {
        register_values[lhs[0]] -= get_value(rhs);
    }

    void do_mul(const string & lhs, const string& rhs) {
        register_values[lhs[0]] *= get_value(rhs);
        number_mul_called++;
    }
    
    void do_jump(const string & lhs, const string& rhs) {
        if (get_value(lhs) != 0) {
            program_pointer += get_value(rhs);
        }
    }
    void add_command(CommandFnType fn, const string& lhs, const string& rhs) {
        commands.emplace_back(fn, lhs, rhs);
    }
    vector<Command> commands;
    vector<ll> register_values;
    int program_pointer;
    int number_mul_called;
};


bool is_prime(ll x) {
    if (x != 2 && x % 2 == 0) {
        return false;
    }
    for (ll d = 3; d * d <= x; d += 2) {
        if (x % d == 0) {
            return false;
        }
    }
    return true;
}
int main() {
    string s;
    smatch match;
    vector<Command> commands;
    Program part1;

    while (getline(cin, s)) {
        if (regex_match(s, match, set_value)) {
            part1.add_command(&Program::do_set, match.str(1), match.str(2));
        } else if (regex_match(s, match, sub_value)) {
            part1.add_command(&Program::do_sub, match.str(1), match.str(2));
        } else if (regex_match(s, match, mul_value)) {
            part1.add_command(&Program::do_mul, match.str(1), match.str(2));
        } else if (regex_match(s, match, jump_nz)) {
            part1.add_command(&Program::do_jump, match.str(1), match.str(2));
        } else {
            cout << "Uknown command " << s << endl;
            exit(1);
        }
    }  
    while (part1.do_action());
    cout << "Part 1 " <<  part1.number_mul_called << endl;

    ll target = 124900;
    ll source = 107900;
    int res2 = 0;
    for (int i = 107900; i <= 124900; i += 17) {
        if (!is_prime(i)) {
            res2++;
        }
    }
    cout << "Part 2 " << res2 << endl;
    return 0;
}