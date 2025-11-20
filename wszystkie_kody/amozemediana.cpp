#include <bits/stdc++.h>
using namespace std;
bool czy(vector<vector<int> >ciag,int cos,int n){
    vector<vector<int> >bule(n+1,vector<int>(n+1)); 
    vector<vector<int> >dp(n+1,vector<int>(n+1)); 
    for(int i=0;i<n;++i){
        for(int j=0;j<n;++j){
            if(ciag[i+1][j+1]>=cos)
                bule[i+1][j+1]=1;
        }
    }
    /*for(int i=0;i<n;++i){
        for(int j=0;j<n;++j){
            cout << bule[i+1][j+1] << ' ';
        }
        cout << endl;
    }
    */
    for(int i=0;i<n;++i){
        for(int j=0;j<n;++j){
            dp[i+1][j+1]=min(dp[i][j+1],dp[i+1][j])+bule[i+1][j+1];
        }
    }
    /*cout << "-------" << endl;
    for(int i=0;i<n;++i){
        for(int j=0;j<n;++j){
            cout << dp[i+1][j+1] << ' ';
        }
        cout << endl;
    }
    */
    if(dp[n][n]==n-1)
        return true;
    else
        return false;
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n,maks=INT_MIN,minn=INT_MAX,sr;
    cin >> n;
    vector<vector<int> >ciag(n+1,vector<int>(n+1));
    for(int i=0;i<n;++i){
        for(int j=0;j<n;++j){
            cin >> ciag[i+1][j+1];
            maks=max(ciag[i+1][j+1],maks);
            minn=min(ciag[i+1][j+1],minn);
        }
    }
    while(minn!=maks){
        sr=(maks+minn)/2;
        if(czy(ciag,sr,n))
            minn=sr+1;
        else
            maks--;
        cout << minn << ' ' << maks << endl;
    }
    cout << maks;
    return 0;
}
//g++ -o amozemediana amozemediana.cpp && ./amozemediana < test.in