#include <bits/stdc++.h>
#include <bits/extc++.h>
//#include <atcoder/all>
#define IOS ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(nullptr);
#define pb push_back
#define UNIQUE(a) sort(ALL(a));a.resize(unique(ALL(a))-a.begin());
#define ALL(X) X.begin(),X.end()
#define F(i,n)  FF(i,0,(n))
#define F1(i,n)  FF(i,1,(n)+1)
#define FF(i,n,m) for(int i=(int)n;i<int(m);++i)
#define rF(i,a,b) for(int i=a;i>=(int)b;--i)
#define mkp(a,b) make_pair(a,b)
#define Fi first
#define Se second
#define fi first
#define se second
#define x first
#define y second
#define X first
#define Y second
#define int ll
//#define double long double
//#pragma GCC optimize("Ofast")//,unroll-loops
//#pragma GCC target("abm,bmi,bmi2,mmx,sse,sse2,sse3,ssse3,sse4,popcnt,avx,avx2,fma,tune=native")
using namespace std;
using ll=long long;
using ull=unsigned long long;
using int128= __int128_t;
using uint128= __uint128_t;
using pii =pair<int,int> ;
using vi=vector<int>; 
const double pi=acos(-1);
template<typename T> inline bool remax(T& a, const T b) {return b>a?a=b,1:0;}
template<typename T> inline bool remin(T& a, const T b) {return b<a?a=b,1:0;}
inline ostream& operator << (ostream& os,__int128_t a){if(a==0) {return (os<<'0');}bool flag=0;if(a<0) {a=-a,flag=1;}string s;while(a){s+=a%10+'0';a/=10;}s+=flag?"-":"";reverse(ALL(s));return os<<s;}
inline istream& operator >>(istream& is,__int128_t& a){string s;cin>>s;a=0;bool flag=0;for(auto c:s){if(c=='-') flag=1;else a=a*__int128_t(10)+__int128_t(c-'0');} if(flag) a*=-1;return is;}
template<typename T,typename P> inline ostream& operator << (ostream& os,pair<T,P> a){os<<a.first<<" "<<a.second; return os;}
template<typename T,typename P> inline istream& operator >> (istream& is,pair<T,P> &a){is>>a.first>>a.second; return is;}
template <typename T> void clear(T& a){T b;swap(a,b);return;}
template <typename T> inline ostream& operator <<(ostream& os,vector<T>& t){for(auto& x:t){os<<x<<' ';}os<<'\n';return os;}
template <typename T,size_t N> inline ostream& operator <<(ostream& os,array<T,N>& t){for(auto& x:t){os<<x<<' ';}os<<'\n';return os;}
template <typename T> inline ostream& operator <<(ostream& os,set<T>& t){for(auto& x:t){os<<x<<' ';}os<<'\n';return os;}
template <typename T,typename P> inline ostream& operator <<(ostream& os,map<T,P>& t){for(auto& [l,r]:t){os<<l<<"|"<<r<<'\n';}return os;}
template<typename T>using rbtree =__gnu_pbds::tree<T,__gnu_pbds::null_type,less<T>,__gnu_pbds::rb_tree_tag,__gnu_pbds::tree_order_statistics_node_update>;
template<typename T,typename P=less<T>> using PQ=__gnu_pbds::priority_queue<T,P,__gnu_pbds::pairing_heap_tag>;
template <int mod>struct Modint{
    int val;
    inline Modint(ll _val=0){val=_val%mod;if(val<0) val+=mod;}
    inline Modint operator +(const Modint& o) const {Modint res;res.val=val+o.val;if(res.val>=mod){res.val-=mod;} return res;}
    inline Modint operator +(const int& o) const {return Modint(val+o);}
    inline Modint operator -() const {Modint res;res.val=-val;if(res.val<0) {res.val+=mod;}return res;}
    inline Modint operator -(const Modint& o) const {Modint res;res.val=val-o.val;if(res.val<0) {res.val+=mod;}return res;}
    inline Modint operator -(const int& o) const {return Modint(val-o);}
    inline Modint operator *(const Modint& o) const {return Modint((ll)val*(ll)o.val);}
    inline Modint operator *(const int& o) const {return Modint((ll)val*(ll)(o%mod));}
    inline Modint operator +=(const Modint& o){*this=(*this)+o;return *this;}
    inline Modint operator -=(const Modint& o){*this=(*this)-o;return *this;}
    inline Modint operator *=(const Modint& o){*this=(*this)*o;return *this;}
    inline Modint Pow(int b) const {Modint tmp(val),ret(1);while(b){if(b&1){ret*=tmp;}b>>=1;tmp*=tmp;}return ret;}
    inline Modint Pow(const Modint& a, int b) const {return a.Pow(b);}
    inline Modint inv() const {return (*this).Pow(mod-2);}
    inline Modint operator /(const Modint& o) const {return *this*o.inv();}
    inline Modint operator /(const int& o) const {return *this*Modint(o).inv();}
    inline bool operator ==(const Modint& o) const {return val==o.val;}
    inline bool operator !=(const Modint& o) const {return val!=o.val;}
    inline friend ostream& operator << (ostream& o, Modint<mod> x){return o << x.val;}
    inline friend Modint<mod> operator +(const int& x, const Modint<mod>& y){return Modint<mod>(x+y.val);}
    inline friend Modint<mod> operator -(const int& x, const Modint<mod>& y){return Modint<mod>(x-y.val);}
    inline friend Modint<mod> operator *(const int& x, const Modint<mod>& y){return Modint<mod>(x%mod*y.val);}
};
int modpow (int x,int p,int md){if(x%md==0){return 0;}int re=1,t=x%md;while(p){if(p&1) {re=re*t%md;}p>>=1;t=t*t%md;}return (re%md+md)%md;}
using mint998244353=Modint<998244353>;
using mint1000000007=Modint<1000000007>;

const int N=1E6+5;
const ll M=7.5E5+5;
const ll INF_64=1E18;
const int INF_32=0x3f3f3f3f;
const int16_t INF_16=0x3f3f;
const int klog=20;
const ll MOD=(1LL<<61)-1;//1000000007;//998244353
const double eps=1E-8;
//using mint=mint998244353;
void gen(){
};
char a[N],b[N];
int ha[N],hb[N];
int P1[N];
const int p1=229;
int ans[N];
int ptr=0;
void test(int x){
	assert(x>=0&&x<MOD);
}
inline int Mul(int a,int b){
	test(a),test(b);
	int128 t=int128(a)*int128(b);
	t=(t>>61)+(t&MOD);
	if(t>=MOD) return t-MOD;
	return t;
}
inline int ValA(int L,int R){
	int t=ha[R]-Mul(ha[L-1],P1[R-L+1]);
	if(t<0) t+=MOD;
	return t;
}
inline int ValB(int L,int R){
	int t=hb[R]-Mul(hb[L-1],P1[R-L+1]);
	if(t<0) t+=MOD;
	return t;
}
void sol(){
	cin>>(a+1)>>(b+1);
	int n,m;n=strlen(a+1),m=strlen(b+1);
	ha[0]=hb[0]=0;P1[0]=1;
	F1(i,n){
		ha[i]=Mul(ha[i-1],p1)+(int)a[i];
		if(ha[i]>=MOD) ha[i]-=MOD;
	}
	F1(i,m){
		hb[i]=Mul(hb[i-1],p1)+(int)b[i];
		if(hb[i]>=MOD) hb[i]-=MOD;
	}
	F1(i,n){
		P1[i]=Mul(P1[i-1],p1);
	}
	F1(i,n-m+1){
		int va=ValA(i,i+m-1),vb=hb[m];
		if(va==vb) ans[ptr++]=i;
		else{	
			int L=0,R=m-1;
			while(L!=R){
				int mid=(L+R)/2;
				int va=ValA(i,i+mid),vb=hb[mid+1];
				if(va!=vb) R=mid;
				else L=mid+1;
			}
			va=ValA(i+L+1,i+m-1),vb=ValB(L+2,m);
			if(va==vb) ans[ptr++]=i;
		}
	}
	cout<<ptr<<"\n";
	F(i,ptr){
		cout<<ans[i]<<" ";
	}
}
int32_t main(){
    #ifdef LOCAL
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    #endif // LOCAL
    IOS;
    int t=1;
    //gen();
    //cin>>t;cin.ignore();
    FF(i,1,t+1){
        //cout<<"Case #"<<i<<": ";
        sol();
    }
}
