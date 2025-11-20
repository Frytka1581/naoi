#include <iostream>
#include <string>
using namespace std;

bool czyjest(long long number) {
    string napis = to_string(number);
    int n = napis.length();
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            
            bool czyjest = true;
            int l = i, p = j;
            while (l < p) {
                if (napis[l] != napis[p]) {
                    czyjest = false;
                    break;
                }
                l++;
                p--;
            }
            if (czyjest && (j - i + 1) > 1) {
                return false;
                
            }
        }
    }
    return true; 
}

long long wynik(long long a, long long b) {
    long long wypisz = 0;
    for (long long i = a; i <= b; i++) {
        if (czyjest(i)) {
            wypisz++;
        }
    }
    return wypisz;
}

int main() {
    long long a, b;
    cin >> a >> b;

    long long result = wynik(a, b);

    cout << result << endl;

    return 0;
}