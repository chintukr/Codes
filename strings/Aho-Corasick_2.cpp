// Problem Link :-http://www.codechef.com/problems/FAVNUM
// Algo's used :- digit dp, Aho-Corasick and binary search
// Faster than the node version of Aho-Corasick :)

#include <bits/stdc++.h>
using namespace std;

//Uzumaki Naruto :)
#define TRACE

#ifdef TRACE
#define trace(a,n)   for(int i = 0; i < n; ++i) cerr << a[i] << " ";cerr << endl;
#define dbg(args...) {debug,args; cerr<<endl;}
#define pause()      cin.get();cin.get();

#else
#define trace(a,n)
#define dbg(args...)
#define pause()

#endif

struct debugger {
    template<typename T> debugger& operator , (const T& v) {
        cerr<<v<<" "; return *this;
    }
} debug;

template <typename T1, typename T2>
inline ostream& operator << (ostream& os, const pair<T1, T2>& p) {
    return os << "(" << p.first << ", " << p.second << ")";
}

template<typename T>
inline ostream &operator << (ostream & os,const vector<T>& v) {
    bool first = true; os << "[";
    for (typename vector<T>::const_iterator ii = v.begin(); ii != v.end(); ++ii) {
        if(!first) os << ", ";
        os << *ii; first = false;
    }
    return os << "]";
}

typedef long long LL;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int NN = 65;
const int MM = 20;

int nxt[NN*MM][10],ch[NN*MM];
int fail[NN*MM],p[NN*MM];

bool is_word[NN*MM];
int nodes = 1;

void add_str(string &temp){
    int no = 0, sz = (int)temp.size();
    for(int i = 0; i < sz; ++i){
        int c = (int)(temp[i]-'0');
        if (nxt[no][c] == -1){
            p[nodes] = no;
            ch[nodes] = c;
            nxt[no][c] = nodes++;
        }
        no = nxt[no][c];
    }
    is_word[no] = true;
}

int go(int k,int c);

int getLink(int k){
    if (fail[k] != -1)
        return fail[k];
    if (!p[k])
        return (fail[k] = 0);
    int c = ch[k];
    int x = p[k];
    return (fail[k] = go(getLink(x),c));
}

int go(int k,int c){
    if (nxt[k][c] != -1)
        return nxt[k][c];
    if (!k)
        return (nxt[k][c] = 0);
    int x = getLink(k);
    return (nxt[k][c] = go(x,c));
}

void build(){
    queue<int> q;
    q.push(0);
    while(!q.empty()){
        int no = q.front();
        q.pop();
        for(int i = 0; i <= 9; ++i) if (nxt[no][i] != -1)
            q.push(nxt[no][i]);
        fail[no] = getLink(no);
        is_word[no] |= is_word[fail[no]];
    }
}

LL dp[MM][NN*MM][2][2];
LL fpow[NN],num;

LL f(int cur,int match,bool tight,bool found){
    if (cur < 0)
        return found;
    LL &ans = dp[cur][match][tight][found];
    if (ans != -1) return ans;

    ans = 0LL;
    LL temp = num/fpow[cur];
    int v = temp%10;
    int mx = ((tight) ? v : 9);

    for(int i = 0; i <= mx; ++i){
        int nw = go(match,i);
        bool t = ((tight) ? (mx == i) : false);
        ans += f(cur-1,nw,t,found | is_word[nw]);
    }
    return ans;
}

LL func(LL temp){
    memset(dp,-1,sizeof(dp));
    num = temp;
    LL ans = f(18,0,1,0);
    return ans;
}

void solve(){
    memset(nxt,-1,sizeof(nxt));
    memset(fail,-1,sizeof(fail));
    p[0] = 0, fpow[0] = 1LL;
    for(int i = 1; i <= 18; ++i)
        fpow[i] = 10LL*fpow[i-1];

    LL L,R,K;
    cin >> L >> R >> K;

    int n; cin >> n;
    string temp;
    for(int i = 0; i < n; ++i)
        cin >> temp, add_str(temp);
    build();

    K += func(L-1);
    LL st = L, en = R;
    while(st < en){
        LL mid = (st+en)/2LL;
        if (func(mid) >= K) en = mid;
        else st = mid+1;
    }

    if (func(en) == K) cout << en << "\n";
    else puts("no such number\n");
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    solve();
    return 0;
}
