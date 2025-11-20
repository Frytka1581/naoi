#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << "Zrobione" << endl;

    /*
    #include <bits/stdc++.h>
using namespace std;

#define fastio                   \
    ios::sync_with_stdio(false); \
    cin.tie(nullptr);
#define s(x) x.size()
#define all(x) (x).begin(), (x).end()
#define pb push_back
#define fi first
#define se second
#define INF 2000000000
#define INFL 1e18

using ll = long long;
using pii = pair<int, int>;

void solve()
{
    freopen("angry.in", "r", stdin);
    freopen("angry.out", "w", stdout);

    int n;
    cin >> n;
    vector<int> pozycje(n);
    for (int i = 0; i < n; i++)
    {
        cin >> pozycje[i];
        pozycje[i] *= 2;
    }

    sort(all(pozycje));
    pozycje.resize(unique(all(pozycje)) - pozycje.begin());
    n = pozycje.size();

    vector<int> dp[2];
    for (int iter = 0; iter < 2; iter++)
    {
        int ostj = 0;
        dp[iter].resize(n, INF);
        dp[iter][0] = -2;
        for (int i = 1; i < n; i++)
        {
            while (ostj + 1 < i && abs(pozycje[i] - pozycje[ostj + 1]) > dp[iter][ostj + 1] + 2)
                ostj++;
            dp[iter][i] = min(abs(pozycje[i] - pozycje[ostj]), dp[iter][ostj + 1] + 2);
        }
        reverse(all(pozycje));
    }

    reverse(all(dp[1]));

    int lewy = 0, prawy = n - 1;
    int wynik = INF;
    while (lewy < prawy)
    {
        wynik = min(wynik, max((pozycje[prawy] - pozycje[lewy]) / 2, 2 + max(dp[0][lewy], dp[1][prawy])));
        if (dp[0][lewy + 1] < dp[1][prawy - 1])
            lewy++;
        else
            prawy--;
    }

    if (wynik % 2) {
        cout << wynik / 2 << ".5\n";
    } else {
        cout << wynik / 2 << ".0\n";
    }

}

int main()
{
    fastio;
    int t = 1;
    // cin >> t;
    while (t--)
        solve();
    return 0;
}

*/

    return 0;
}