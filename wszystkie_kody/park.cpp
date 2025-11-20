#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct Kolo {
    int x, y, r;
};

bool czyKoliduje(int cx, int cy, int r, const vector<Kolo>& drzewa, int w, int h) {
    if (cx - r < 0 || cx + r > w || cy - r < 0 || cy + r > h) {
        return true;
    }
    for (const auto& drzewo : drzewa) {
        int dx = cx - drzewo.x;
        int dy = cy - drzewo.y;
        if (sqrt(dx * dx + dy * dy) < r + drzewo.r) {
            return true;
        }
    }
    return false;
}

bool mozePrzejsc(int r, int bramaStart, int bramaKoniec, const vector<Kolo>& drzewa, int w, int h) {
    int x, y;

    if (bramaStart == 1) x = r, y = r;
    else if (bramaStart == 2) x = w - r, y = r;
    else if (bramaStart == 3) x = w - r, y = h - r;
    else x = r, y = h - r;

    if (czyKoliduje(x, y, r, drzewa, w, h)) return false;

    if (bramaKoniec == 1) return x - r >= 0 && y - r >= 0;
    if (bramaKoniec == 2) return x + r <= w && y - r >= 0;
    if (bramaKoniec == 3) return x + r <= w && y + r <= h;
    if (bramaKoniec == 4) return x - r >= 0 && y + r <= h;

    return false;
}

int main() {
    int n, m;
    cin >> n >> m;

    int w, h;
    cin >> w >> h;

    vector<Kolo> drzewa(n);
    for (int i = 0; i < n; ++i) {
        cin >> drzewa[i].x >> drzewa[i].y >> drzewa[i].r;
    }

    for (int i = 0; i < m; ++i) {
        int r, bramaStart;
        cin >> r >> bramaStart;

        string wynik;
        for (int bramaKoniec = 1; bramaKoniec <= 4; ++bramaKoniec) {
            if (mozePrzejsc(r, bramaStart, bramaKoniec, drzewa, w, h)) {
                wynik += to_string(bramaKoniec);
            }
        }
        cout << wynik << endl;
    }

    return 0;
}
