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

struct particle {
    ll p[3];
    ll v[3];
    ll a[3];

    ll dist_at_time(ll t) {
        ll res = 0;
        for (int i = 0; i < 3; ++i) {
            res += abs(p[i] + v[i] * t + ((t * (t + 1)) / 2LL) * a[i]);
        }
        return res;
    }
    bool collides(ll t, const particle& other) {
        for (int i = 0; i < 3; ++i) {
            ll x =  p[i] + v[i] * t + ((t * (t + 1)) / 2LL) * a[i];
            ll ox = other.p[i] + other.v[i] * t + ((t * (t + 1)) / 2LL) * other.a[i];
            if (x != ox) {
                return false;
            }
        }
        return true;
    }
};
int main() {
    string three_values = "(-?\\d+),(-?\\d+),(-?\\d+)";
    regex particle_re("p=<" + three_values + ">, v=<" + three_values + ">, a=<" + three_values + ">");
    string s;
    smatch match;
    vector<particle> particles;
    while (getline(cin, s)) {
        if (regex_match(s, match, particle_re)) {
            vector<ll> ctr_args;
            for (int i = 1; i <= 9; ++i) {
                ctr_args.push_back(stoll(match.str(i)));
            }
            particles.push_back(particle{
                {ctr_args[0], ctr_args[1], ctr_args[2]}, 
                {ctr_args[3], ctr_args[4], ctr_args[5]}, 
                {ctr_args[6], ctr_args[7], ctr_args[8]}}
            );
        } else {
            cout << "Could not parse " << s << endl;
        }
    }
    int best = 0;
    ll target_t = 1000000;
    ll bestd = particles[0].dist_at_time(target_t);
    for (int i = 1; i < (int)particles.size(); ++i) {
        ll temp = particles[i].dist_at_time(target_t);
        if (temp < bestd) {
            bestd = temp;
            best = i;
        }
    }
    cout << "Part 1 " << best << endl;
    for (int second = 1; second < 1000; ++second) {
        vector<char> good(particles.size(), 1);
        for (int i = 0; i < (int)particles.size(); ++i) {
            for (int j = i + 1; j < (int)particles.size(); ++j) {
                if (particles[i].collides(second, particles[j])) {
                    good[i] = good[j] = 0;
                }
            }
        }
        vector<particle> filtered;
        for (int i = 0; i < (int)good.size(); ++i) {
            if (good[i]) {
                filtered.push_back(particles[i]);
            }
        }
        particles = filtered;
    }
    cout << "Part 2 " << particles.size() << endl; 
    return 0;
}