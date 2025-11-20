#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    long long n, k, m;

    cin >> n >> k >> m;
    vector<long long> a(m);
    for (long long i = 0; i < m; ++i)
    {
        cin >> a[i];
    }
    if ((n - m) % (k - 1) != 0)
    {
        cout << "NIE";
        return 0;
    }
    long long s = 0, last = 0, wybrany = -1;
    for (long long i = 0; i < m; ++i)
    {

        s += a[i] - last - 1;
        if ((s >= (k - 1) / 2) && ((n - m - s) >= ((k - 1) / 2)) && wybrany == -1)
        {
            wybrany = i;
        }

        last = a[i];
    }
    if (wybrany == -1)
    {
        cout << "NIE";
        return 0;
    }
    
    wybrany = a[wybrany];
    long long index = 0;
    bool ktory = 0;
    priority_queue<long long> c1, c2;
    for (long long i = 1; i <= n; ++i)
    {
        if (index >= m || i != a[index])
        {
            if (!ktory)
                c1.push(i);
            else
                c2.push(i);
        }
        else
        {
            index++;
            if (wybrany == i)
                ktory = true;
        }
    }
    cout << "TAK" << endl;
    cout << (n - m) / (k - 1) << endl;
    if (c1.size() < c2.size())
        swap(c1, c2);
    long long ten = 0;
    while (c1.size() - c2.size() >= k - 1)
    {
        vector<long long> cos;
        for (long long i = 0; i < k; ++i)
        {
            cos.push_back(c1.top());
            if (i == (k - 1) / 2)
                ten = c1.top();
            c1.pop();
        }
        sort(cos.begin(), cos.end());
        for (long long ele : cos) {
            cout << ele << " ";
        }
        cout << endl;
        c1.push(ten);
    }
    if (c1.size() != c2.size())
    {
        vector<long long> cos;
        long long przewaga = c1.size() - c2.size();
        long long ten=0;
        for (long long i = 0; i < (k - 1 - przewaga) / 2 + przewaga+1; ++i)
        {
            cos.push_back(c1.top());
            if(i==(k+1)/2-1) ten=c1.top();
            c1.pop();
        }
        for (long long i = 0; i < (k - 1 - przewaga) / 2; ++i)
        {
            cos.push_back(c2.top());
            c2.pop();
        }
        sort(cos.begin(), cos.end());
        for (long long i = 0; i < cos.size(); ++i) {
            cout << cos[i] << ' ';
        }
        cout << endl;
        c1.push(ten);
    }
    
    while (c1.size() != 0)
    {
        vector<long long> cos;
        for (long long i = 0; i < (k - 1) / 2; ++i)
        {
            cos.push_back(c1.top());
            c1.pop();
        }
        cos.push_back(wybrany);
        for (long long i = 0; i < (k - 1) / 2; ++i)
        {
            cos.push_back(c2.top());
            c2.pop();
        }
        sort(cos.begin(), cos.end());
        for (long long i = 0; i < cos.size(); ++i) {
            cout << cos[i] << ' ';
        }
        cout << endl;
    }
    //3 5
    return 0;
}