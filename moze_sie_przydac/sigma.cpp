#include <bits/stdc++.h>
using namespace std;

using ll = long long;
ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }
ll lcm(ll a, ll b) { return a / gcd(a, b) * b; } // Uwaga: zakładamy brak overflow lub używaj __int128 jeśli potrzeba

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    string S;
    k = S.size();

    cin >> n >> m >> S;

    map<char, int> dx_map = {{'G', -1}, {'D', 1}, {'L', 0}, {'P', 0}};
    map<char, int> dy_map = {{'G', 0}, {'D', 0}, {'L', -1}, {'P', 1}};

    ll delta_x = 0, delta_y = 0;
    for (char s : S)
    {
        delta_x += dx_map[s];
        delta_y += dy_map[s];
    }

    ll g_x = gcd(abs(delta_x), (ll)n);
    ll g_y = gcd(abs(delta_y), (ll)m);

    ll ord_x = n / g_x;
    ll ord_y = m / g_y;
    ll h_size = lcm(ord_x, ord_y);

    vector<pair<int, int>> prefixes;
    int cur_x = 0, cur_y = 0;
    for (int i = 0; i < k; ++i)
    {
        prefixes.emplace_back(cur_x % n, cur_y % m);
        char s = S[i];
        cur_x += dx_map[s];
        cur_y += dy_map[s];
    }

    ll distinct_cosets;
    if (g_x == n && g_y == m)
    {
        // Special case: delta equivalent to (0,0) mod (n,m)
        set<pair<int, int>> unique_prefixes(prefixes.begin(), prefixes.end());
        distinct_cosets = unique_prefixes.size();
    }
    else
    {
        ll mod_d = gcd((ll)n * abs(delta_y), (ll)m * abs(delta_x));
        set<ll> keys;
        for (auto &p : prefixes)
        {
            int px = p.first, py = p.second;
            ll val = (ll)px * delta_y - (ll)py * delta_x;
            ll key = (val % mod_d + mod_d) % mod_d;
            keys.insert(key);
        }
        distinct_cosets = keys.size();
    }

    ll total_visited = distinct_cosets * h_size;

    if (total_visited == (ll)n * m)
    {
        cout << "TAK\n";
    }
    else
    {
        cout << "NIE\n";
    }

    return 0;
}
// PPPPPPPPPPPPP
// DDDDDDDDDDDDD
// PPPPPPPPPPPPPPPPP
// DDDDDDDDDDDDDDDDD