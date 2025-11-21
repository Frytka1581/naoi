#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    int n;
    cin >> n;

    set<int> zly = {1, 2, 4, 5, 7, 10, 13};

    if (zly.count(n))
        cout << "NIE\n";
    else
        cout << "TAK\n";

    return 0;
}
