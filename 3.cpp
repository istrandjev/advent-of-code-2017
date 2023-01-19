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


int moves[4][2] = { { -1, 0 }, { 0, 1}, { 1, 0 }, { 0, -1} };
int moves8[8][2] = { { -1, 0 }, { -1, 1 }, { 0, 1 }, { 1, 1 }, { 1, 0 },
        { 1, -1 }, { 0, -1 }, { -1, -1 } };
ll solve(ll target) {
    int c = 1;
    int x = 0, y = 0;
    int dir = 1;
    int step = 1;
    int stepi = 0;
    while (c + step <= target) {
        c += step;
        stepi++;
        x += moves[dir][0] * step;
        y += moves[dir][1] * step;
        dir = (dir + 3) % 4;
        if (stepi == 2) {
            stepi = 0;
            step++;
        }
    }
    x += moves[dir][0] * (target - c);
    y += moves[dir][1] * (target - c);
    return abs(x) + abs(y);
}

int get_value(const vector<vector<int>> & a, int x, int y) {
    int sum = 0;
    for (int l = 0; l < 8; ++l) {
        int tx = x + moves8[l][0];
        int ty = y + moves8[l][1];
        sum += a[tx][ty];
    }
    return sum;
}
const int input = 361527;
int main() {
    
    cout << "Part 1 " << solve(input) << endl;
    
    vector<vector<int> > values(1000, vector<int>(1000, 0));
    int c = 1;
    int x = 500, y = 500;
    int dir = 1;
    int step = 1;
    int stepi = 0;
    bool found = false;
    values[x][y] = 1;
    while (!found) {
        for (int i = 0; i < step; ++i) {
            x += moves[dir][0];
            y += moves[dir][1];
            values[x][y] = get_value(values, x, y);
            if (values[x][y] > input) {
                cout << "Part 2 " << values[x][y] << endl;
                found = true;
                break;
            }                      
        }
        stepi++;
        dir = (dir + 3) % 4;
        if (stepi == 2) {
            stepi = 0;
            step++;
        }
    }
    return 0;
}