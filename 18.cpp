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

/*
snd X plays a sound with a frequency equal to the value of X.
set X Y sets register X to the value of Y.
add X Y increases register X by the value of Y.
mul X Y sets register X to the result of multiplying the value contained in register X by the value of Y.
mod X Y sets register X to the remainder of dividing the value contained in register X by the value of Y (that is, it sets X to the result of X modulo Y).
rcv X recovers the frequency of the last sound played, but only when the value of X is not zero. (If it is zero, the command does nothing.)
jgz X Y jumps with an offset of the value of Y, but only if the value of X is greater than zero. (An offset of 2 skips the next instruction, an offset of -1 jumps to the previous instruction, and so on.)
*/
regex snd("snd ([a-z]|-?\\d+)");
string get_modify_reg_regex_str(const string& command) {
    return command + " ([a-z]) ([a-z]|-?\\d+)";
}
regex set_value(get_modify_reg_regex_str("set"));
regex add_value(get_modify_reg_regex_str("add"));
regex mul_value(get_modify_reg_regex_str("mul"));
regex mod_value(get_modify_reg_regex_str("mod"));
regex recover("rcv ([a-z]|-?\\d+)");
regex jump_nz("jgz ([a-z]|-?\\d+) ([a-z]|-?\\d+)");

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
        blocked = false;
    }
    bool do_action() {
        if (program_pointer < 0 || program_pointer >= (int)commands.size()) {
            return false;
        }
        int cp = program_pointer;
        blocked = false;
        (this->*commands[program_pointer].fn)(commands[program_pointer].lhs, commands[program_pointer].rhs);
        if (!blocked && program_pointer == cp) {
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

    void do_send(const string & lhs, const string& rhs) {
        receiver->input_queue.push(get_value(lhs));
    }

    void do_set(const string & lhs, const string& rhs) {
        register_values[lhs[0]] = get_value(rhs);
    }

    void do_add(const string & lhs, const string& rhs) {
        register_values[lhs[0]] += get_value(rhs);
    }

    void do_mul(const string & lhs, const string& rhs) {
        register_values[lhs[0]] *= get_value(rhs);
    }
    void do_mod(const string & lhs, const string& rhs) {
        register_values[lhs[0]] %= get_value(rhs);
    }

    void do_recover(const string & lhs, const string& rhs) {
        if (get_value(rhs) != 0) {
            if (input_queue.size() > 0) {
                register_values[lhs[0]] = input_queue.front();
                input_queue.pop();
            } else {
                blocked = true;
            }
        }
    }

    void do_jump(const string & lhs, const string& rhs) {
        if (get_value(lhs) > 0) {
            program_pointer += get_value(rhs);
        }
    }
    void add_command(CommandFnType fn, const string& lhs, const string& rhs) {
        commands.emplace_back(fn, lhs, rhs);
    }
    queue<ll> input_queue;
    vector<Command> commands;
    vector<ll> register_values;
    Program* receiver;
    int program_pointer;
    bool blocked;
};

int main() {
    string s;
    smatch match;
    vector<Command> commands;
    Program part1, part2_1, part2_2;
    part1.receiver = &part1;

    while (getline(cin, s)) {
        if (regex_match(s, match, snd)) {
            part1.add_command(&Program::do_send, match.str(1), match.str(1));
            part2_1.add_command(&Program::do_send, match.str(1), match.str(1));
            part2_2.add_command(&Program::do_send, match.str(1), match.str(1));
        } else if (regex_match(s, match, set_value)) {
            part1.add_command(&Program::do_set, match.str(1), match.str(2));
            part2_1.add_command(&Program::do_set, match.str(1), match.str(2));
            part2_2.add_command(&Program::do_set, match.str(1), match.str(2));
        } else if (regex_match(s, match, add_value)) {
            part1.add_command(&Program::do_add, match.str(1), match.str(2));
            part2_1.add_command(&Program::do_add, match.str(1), match.str(2));
            part2_2.add_command(&Program::do_add, match.str(1), match.str(2));
        } else if (regex_match(s, match, mul_value)) {
            part1.add_command(&Program::do_mul, match.str(1), match.str(2));
            part2_1.add_command(&Program::do_mul, match.str(1), match.str(2));
            part2_2.add_command(&Program::do_mul, match.str(1), match.str(2));
        } else if (regex_match(s, match, mod_value)) {
            part1.add_command(&Program::do_mod, match.str(1), match.str(2));
            part2_1.add_command(&Program::do_mod, match.str(1), match.str(2));
            part2_2.add_command(&Program::do_mod, match.str(1), match.str(2));
        } else if (regex_match(s, match, recover)) {
            part1.add_command(&Program::do_recover, match.str(1), match.str(1));
            part2_1.add_command(&Program::do_recover, match.str(1), "1");
            part2_2.add_command(&Program::do_recover, match.str(1), "1");
        } else if (regex_match(s, match, jump_nz)) {
            part1.add_command(&Program::do_jump, match.str(1), match.str(2));
            part2_1.add_command(&Program::do_jump, match.str(1), match.str(2));
            part2_2.add_command(&Program::do_jump, match.str(1), match.str(2));
        } else {
            cout << "Uknown command " << s << endl;
            exit(1);
        }
    }

    while (true) {
        int current_size = part1.input_queue.size();
        part1.do_action();
        if (part1.input_queue.size() < current_size) {
            cout << "Part 1 " << part1.input_queue.back() << endl;
            break;
        }
    }
    part2_1.receiver = &part2_2;
    part2_2.receiver = &part2_1;
    part2_1.register_values['p'] = 0;
    part2_2.register_values['p'] = 1;
    int result2 = 0;
    while (true) {
        bool part1_worked = part2_1.do_action();
        if (part2_1.blocked) {
            part1_worked = false;
        }

        int current_size = part2_1.input_queue.size();
        bool part2_worked = part2_2.do_action();
        if (part2_1.input_queue.size() > current_size) {
            result2++;
        }
        if (part2_2.blocked) {
            part2_worked = false;
        }
        if (!part1_worked && !part2_worked) {
            break;
        }
    }
    cout << "Part 2 " << result2 << endl;
    return 0;     
}