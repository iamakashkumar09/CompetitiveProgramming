//using Duval_algorithm to generate the lyndon in O(N)
//Lyndon Factorisation is a method to split the string into chunck of simple string in decreasing order 
//simple string are those string which are lexographically smaller than the suffix strings.
//this algo will give the simple string in Decreasing Order...

// For CSES : Minimal Rotation use str+=str and run this and find the index of the smallest lyndon run loop till n/2.
// and return ans=str.substr(idx,n/2);   here n/2 means total lenght of the string starting from the idx...

#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve() {
    string str; cin >> str;
    int n=str.size();
    vector<string>arr;
    int i=0;
    while(i<n){
        int j=i+1;
        int k=i;
        while(j<n && str[k]<=str[j]){
            if(str[k]<str[j]) k=i;
            else k++;
            j++;
        }
        while(i<=k){
            arr.push_back(str.substr(i,j-k));
            i+=j-k;
        }
    }    

    for(auto ch : arr) cout << ch << endl;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t=1;
    // cin >> t;
    while (t--) solve();
}
