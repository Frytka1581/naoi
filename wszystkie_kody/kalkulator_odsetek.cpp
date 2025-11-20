#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    double kasa;
    double odestki;
    cout << "Podaj ile masz pieniedzy: ";
    cin >> kasa;
    cout << "Podaj ile masz odsetek: ";
    cin >> odestki;
    double poprzedni=15500;
    for(int i=0;i<50;++i){
        kasa+=kasa*(double)(odestki/100);
        cout << "rok: " << i+1 << ' ' << kasa << ' ' << kasa-poprzedni << endl;
        poprzedni=kasa;
    }
    return 0;
}