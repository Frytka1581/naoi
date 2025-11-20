#include<bits/stdc++.h>
#define para pair<int, int> 
using namespace std;
using ll = int64_t;
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
	ll n,o;
    char k;
	string znak;
	
	cin >> n;
	vector<pair<char,int>>ciag(n+10);
	ciag[0]={'.',-1};
	for(int i=1;i<=n;++i){
		cin >> znak;
		if(znak[0]=='d'){
			cin >> k;
			ciag[i].first = k;
			ciag[i].second = i-1;
		}
		if(znak[0] == 'b'){
			if(ciag[i-1].second<1) ciag[i]={'.',-1};
			else ciag[i]=ciag[ciag[i-1].second];
		}
		if(znak[0]=='c'){
			cin >> o;
			ciag[i]=ciag[i-o-1];
		}
        if(ciag[i].first >= 'a' && ciag[i].first <= 'z')
		    cout << ciag[i].first << endl;
        else
            cout << '.' << endl;
	}
    ll index=n;
    string napis;
    while(ciag[index].second!=-1){
        napis+=ciag[index].first;
        index = ciag[index].second;
        
    }
    reverse(napis.begin(),napis.end());
    cout << napis;
	return 0;
}