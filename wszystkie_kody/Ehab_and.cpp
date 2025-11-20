#include <bits/stdc++.h>
using namespace std;

int a, b, pytania = 0;
int ask(int c, int d)
{
    cout << "? " << c << ' ' << d << endl;
    cout.flush(); // ✅ konieczne przy interaktywnych
    int odpowiedz;
    cin >> odpowiedz;
    return odpowiedz;
}


int main()
{
    long long k = 1;
    for (int i = 0; i < 30; ++i)
    {
        k *= 2;
    }
    // cout << k << endl;
    // int seed = 2;
    // //cin >> seed;
    // mt19937 mt(seed);
    // a = mt() % k;
    // b = mt() % k;
    // a = mt() % 1000;
    // b = mt() % 1000;
    //cout << a << ' ' << b << endl;
    k /= 2;
    int c = 0, d = 0, zgadnij1 = 0, zgadnij2 = 0, odp, essa = -2;
    if (ask(0, 0) == 1)
    {
        while (k > 0)
        {
            if (essa == -2)
                odp = ask(c, d);
            else
            {
                odp = essa;
                essa = -2;
            }
            if (odp == -1)
            {
                // cout << k << endl;
                c += k;
                d += k;
                odp = ask(c, d);
                // cout << c << ' '<< d;
                if (odp == 1)
                {
                    c -= k;
                    zgadnij2 += k;
                    // cout << c << endl;
                }
                else
                {
                    essa = -1;
                    c -= k;
                    odp = ask(c, d);
                    if (odp == 1)
                    {
                        zgadnij1 += k;
                        zgadnij2 += k;
                        c += k;
                    }
                    else
                    {
                        d -= k;
                    }
                }
            }
            else if (odp == 0)
            {
                int odp2;
                while (k > 0)
                {
                    d += k;
                    odp2 = ask(c, d);
                    // cout << k << endl;
                    if (odp2 == 1)
                    {
                        // cout << 123;
                        zgadnij1 += k;
                        zgadnij2 += k;
                        c += k;
                    }
                    else
                    {
                        // cout << 456;
                        d -= k;
                    }
                    k /= 2;
                }
            }
            else if (odp == 1)
            {
                // cout << k << endl;
                c += k;
                d += k;
                // cout << c << ' ' << d << endl;
                odp = ask(c, d);
                if (odp == -1)
                {
                    zgadnij1 += k;
                    d -= k;
                }
                else
                {
                    essa = 1;
                    d -= k;
                    odp = ask(c, d);
                    if (odp == -1)
                    {
                        d += k;
                        zgadnij1 += k;
                        zgadnij2 += k;
                    }
                    else
                        c -= k;
                }
            }
            // cout << c << ' '<< d << endl;
            k /= 2;
        }
    }

    else
    {
        while (k > 0)
        {
            if (essa == -2)
                odp = ask(c, d);
            else
            {
                odp = essa;
                essa = -2;
            }
            if (odp == -1)
            {
                // cout << k << endl;
                c += k;
                d += k;
                odp = ask(c, d);
                // cout << c << ' '<< d;
                if (odp == 1)
                {
                    c -= k;
                    zgadnij2 += k;
                    // cout << c << endl;
                }
                else
                {
                    essa = -1;
                    c -= k;
                    odp = ask(c, d);
                    if (odp == 1)
                    {
                        zgadnij1 += k;
                        zgadnij2 += k;
                        c += k;
                    }
                    else
                    {
                        d -= k;
                    }
                }
            }
            else if (odp == 0)
            {
                int odp2;
                while (k > 0)
                {
                    d += k;
                    odp2 = ask(c, d);
                    // cout << k << endl;
                    if (odp2 == 1)
                    {
                        // cout << 123;
                        zgadnij1 += k;
                        zgadnij2 += k;
                        c += k;
                    }
                    else
                    {
                        // cout << 456;
                        d -= k;
                    }
                    k /= 2;
                }
            }
            else if (odp == 1)
            {
                // cout << k << endl;
                c += k;
                d += k;
                // cout << c << ' ' << d << endl;
                odp = ask(c, d);
                if (odp == -1)
                {
                    zgadnij1 += k;
                    d -= k;
                }
                else
                {
                    essa = 1;
                    d -= k;
                    odp = ask(c, d);
                    if (odp == -1)
                    {
                        d += k;
                        zgadnij1 += k;
                        zgadnij2 += k;
                    }
                    else
                        c -= k;
                }
            }
            // cout << c << ' '<< d << endl;
            k /= 2;
        }
    }
    cout << "! " << zgadnij1 << ' ' << zgadnij2 << endl;
    //cout << zgadnij1 << ' ' << zgadnij2 << endl;
    // cout << pytania << endl;
    return 0;
}