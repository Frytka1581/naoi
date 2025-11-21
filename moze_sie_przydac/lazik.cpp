#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n, m;
    cin >> n >> m;

    long long nwd = gcd(n, m);

    if (nwd == 1) {
        cout << 2 << "\nDP\n";
        return 0;
    }

    bool znaleziono = false;
    long long lewy = 0, prawy = 0;

    for (long long i = 1; i < nwd; ++i) {
        if (gcd(n, i) == 1 && gcd(m, nwd - i) == 1) {
            lewy = i;
            prawy = nwd - i;
            znaleziono = true;
            break;
        }
    }

    if (znaleziono) {
        cout << nwd << "\n";

        if ((n / nwd) % 2 == 0) {
            for (long long j = 0; j < prawy; ++j) cout << 'P';
            for (long long j = 0; j < lewy; ++j) cout << 'D';
        } else {
            for (long long j = 0; j < lewy; ++j) cout << 'D';
            for (long long j = 0; j < prawy; ++j) cout << 'P';
        }

        cout << "\n";
        return 0;
    }

    bool czy = false;
    string wynik;

    for (int kier = 0; kier < 2; ++kier) {
        bool czy_wiersz_glowny = (kier == 0 ? ((n / nwd) % 2 != 0) : !((n / nwd) % 2 != 0));
        long long zredukowane = czy_wiersz_glowny ? n / nwd : m / nwd;

        char znak_glowny = czy_wiersz_glowny ? 'D' : 'P';
        char znak_dodatni = czy_wiersz_glowny ? 'P' : 'D';
        char znak_ujemny = czy_wiersz_glowny ? 'L' : 'G';

        for (long long tyl = 0; tyl <= (nwd - 1) / 4; ++tyl) {
            long long net = nwd - 1 - 2 * tyl;
            if (net <= 0) continue;

            if (gcd(net, zredukowane) == 1 && gcd(net, nwd) == 1) {
                long long ile_glownych = nwd - (4 * tyl + 1);
                if (ile_glownych < 0) continue;

                string s = "";
                for (long long j = 0; j < ile_glownych; ++j) s += znak_glowny;

                for (long long j = 0; j < tyl; ++j) {
                    s += znak_dodatni;
                    s += znak_glowny;
                    s += znak_ujemny;
                    s += znak_glowny;
                }

                s += znak_dodatni;
                wynik = s;
                czy = true;
                break;
            }
        }

        if (czy) break;
    }

    if (czy) {
        cout << nwd << "\n" << wynik << "\n";
    } else {
        cout << (nwd + 1) << "\n";

        if ((n / nwd) % 2 == 0) {
            for (long long i = 0; i < nwd; i++) cout << 'P';
            cout << 'D';
        } else {
            for (long long j = 0; j < nwd; ++j) cout << "D";
            cout << "P";
        }
        cout << "\n";
    }

    return 0;
}
