#include <bits/stdc++.h>
using namespace std;

vector<vector<long long>> ciag;
long long ts = 1;

void dodaj(long long index, long long wartosc)
{
    ciag[index] = {wartosc};
    index /= 2;
    while (index > 0)
    {
        vector<long long> merged;
        merged.reserve(ciag[index * 2].size() + ciag[index * 2 + 1].size());
        merge(ciag[index * 2].begin(), ciag[index * 2].end(),
              ciag[index * 2 + 1].begin(), ciag[index * 2 + 1].end(),
              back_inserter(merged));
        if (merged.size() > 32)
            merged.resize(32);
        ciag[index] = merged;
        index /= 2;
    }
}

vector<long long> zwroc(long long lq, long long rq, long long l, long long r, long long k)
{
    if (lq > r || rq < l)
    {
        return {};
    }
    else if (l >= lq && r <= rq)
    {
        return ciag[k];
    }
    else
    {
        long long sr = (l + r) / 2;
        vector<long long> p1 = zwroc(lq, rq, l, sr, k * 2),
                          p2 = zwroc(lq, rq, sr + 1, r, k * 2 + 1);
        vector<long long> merged;
        merged.reserve(p1.size() + p2.size());
        merge(p1.begin(), p1.end(),
              p2.begin(), p2.end(),
              back_inserter(merged));
        while (merged.size() > 32) merged.pop_back();

        return merged;
    }
}

long long para(long long l, long long r)
{
    vector<long long> ciag1 = zwroc(l, r, 1, ts, 1);
    long long minn = INT64_MAX;
    for (long long i = 0; i < (long long)ciag1.size(); ++i)
    {
        for (long long j = i + 1; j < (long long)ciag1.size(); ++j)
        {
            minn = min(minn, (ciag1[i] | ciag1[j]));
        }
    }
    //cout << minn << ' ' << l << ' ' << r << endl;
    return minn;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    long long n, k, q, l, r;
    cin >> n;
    //cout << n << endl;

    while (ts < n)
    {
        ts *= 2;
    }
    ciag.resize(ts * 2);

    for (long long i = 0; i < n; ++i)
    {
        cin >> k;
        dodaj(i + ts, k);
    }

    // for (long long i = 0; i < (long long)ciag.size(); ++i)
    // {
    //     for (long long j = 0; j < (long long)ciag[i].size(); ++j)
    //     {
    //         cout << ciag[i][j] << ' ';
    //     }
    //     if (!ciag[i].empty())
    //     {
    //         cout << i;
    //         cout << endl;
    //     }
    // }

    // cout << "-----------" << endl;

    cin >> q;
    for (long long i = 0; i < q; ++i)
    {
        cin >> l >> r;
        cout << para(l, r) << endl;
    }

    return 0;
}
