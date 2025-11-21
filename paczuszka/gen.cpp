#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll seed = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937 rng(seed);

ll rand_range(ll min_, ll max_)
{
    return rng() % (max_ - min_ + 1) + min_;
}

ll main()
{
    ll s;
    s = rand_range(1000000, 1100000);
    cout << s << "\n";
    cerr << seed << "\n";
    for(ll i = 1; i < s; i++){
        cout << i << " " << rand_range(i+1, s) << "\n";
    }
}
    