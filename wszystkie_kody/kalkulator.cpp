#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1e9 + 7;

long long oblicz(long long a, long long b) {
    return (2 * a % MOD + b % MOD) % MOD;
}

int main() {
    string wejscie;
    getline(cin, wejscie);

    stack<long long> liczby;
    stack<char> znaki;

    for (size_t i = 0; i < wejscie.size(); ++i) {
        char znak = wejscie[i];

        if (isspace(znak)) {
            continue;
        }

        if (isdigit(znak)) {
            long long liczba = 0;
            while (i < wejscie.size() && isdigit(wejscie[i])) {
                liczba = (liczba * 10 + (wejscie[i] - '0')) % MOD;
                ++i;
            }
            --i;
            liczby.push(liczba);
        } else if (znak == '(') {
            znaki.push(znak);
        } else if (znak == ')') {
            while (!znaki.empty() && znaki.top() != '(') {
                long long b = liczby.top(); liczby.pop();
                long long a = liczby.top(); liczby.pop();
                znaki.pop();
                liczby.push(oblicz(a, b));
            }
            znaki.pop();
        } else if (znak == '#') {
            while (!znaki.empty() && znaki.top() == '#') {
                long long b = liczby.top(); liczby.pop();
                long long a = liczby.top(); liczby.pop();
                znaki.pop();
                liczby.push(oblicz(a, b));
            }
            znaki.push(znak);
        }
    }

    while (!znaki.empty()) {
        long long b = liczby.top(); liczby.pop();
        long long a = liczby.top(); liczby.pop();
        znaki.pop();
        liczby.push(oblicz(a, b));
    }

    cout << liczby.top() << endl;
    return 0;
}
