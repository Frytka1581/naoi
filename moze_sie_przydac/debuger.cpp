#include <iostream>
using namespace std;
int main() {
    freopen("input.txt", "r", stdin); // Przekierowanie wejścia na początku
    cout << "Wpisz liczbę: " << flush;
    int x;
    cin >> x; // Wczytanie wartości po freopen
    cout << "Wpisano: " << x << endl;
    return 0;
}