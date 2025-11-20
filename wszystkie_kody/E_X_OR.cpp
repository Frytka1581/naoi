#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> v(n);
    // wypełnij wektor liczbami od 0 do n-1
    for (int i = 0; i < n; ++i)
        v[i] = i;

    // generator liczb losowych
    random_device rd;
    mt19937 g(rd());

    // permutacja (mieszanie)
    shuffle(v.begin(), v.end(), g);

    cout << "Losowa permutacja: ";
    for (int x : v)
        cout << x << " ";
    cout << endl;
    for(int i=1;i<v.size();++i){
        cout << (v[i]|v[0]) << ' ';
    }
    return 0;
}
