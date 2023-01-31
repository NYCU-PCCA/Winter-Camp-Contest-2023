#include<iostream>
#include<algorithm>
using namespace std;
char table[128];
static inline void init(){
    table['A']='T',table['T']='A';
    table['C']='G',table['G']='C';
}
#define endl '\n'
static inline void solve(){
    int n;string str;cin>>n>>str;
    reverse(str.begin(),str.end());
    for(auto& i:str)
        i=table[(int)i];
    cout<<str<<endl;
}
signed main(){
    init();
    int T=1;
    cin>>T;
    while(T--)
        solve();
    return 0;
}
