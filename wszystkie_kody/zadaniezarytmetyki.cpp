#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

int oblicz(string &wyrazenie) {
    stack<long long> liczby;
    stack<char> operatory;

    auto wykonaj = [&]() {
        long long b = liczby.top(); liczby.pop();
        long long a = liczby.top(); liczby.pop();
        char op = operatory.top(); operatory.pop();
        if (op == '+') liczby.push((a + b) % MOD);
        else if (op == '-') liczby.push((a - b + MOD) % MOD);
        else if (op == '*') liczby.push((a * b) % MOD);
    };

    for (int i = 0; i < wyrazenie.size(); ++i) {
        if (isdigit(wyrazenie[i])) {
            long long liczba = 0;
            while (i < wyrazenie.size() && isdigit(wyrazenie[i])) {
                liczba = (liczba * 10 + (wyrazenie[i] - '0')) % MOD;
                ++i;
            }
            liczby.push(liczba);
            --i;
        } else if (wyrazenie[i] == '(') {
            operatory.push(wyrazenie[i]);
        } else if (wyrazenie[i] == ')') {
            while (!operatory.empty() && operatory.top() != '(') {
                wykonaj();
            }
            operatory.pop();
        } else if (wyrazenie[i] == '+' || wyrazenie[i] == '-' || wyrazenie[i] == '*') {
            while (!operatory.empty() && operatory.top() != '(' &&
                   ((wyrazenie[i] == '+' || wyrazenie[i] == '-') || (operatory.top() == '*'))) {
                wykonaj();
            }
            operatory.push(wyrazenie[i]);
        }
    }

    while (!operatory.empty()) {
        wykonaj();
    }

    return liczby.top();
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    string wyrazenie;
    cin >> wyrazenie;
    cout << oblicz(wyrazenie) << '\n';
    return 0;
}
