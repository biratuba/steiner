#include <bits/stdc++.h>

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'

typedef long long ll;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

// Steiner Tree
//
// encontra a arvore de menor peso que cobre os vertices S
// para todos os vertices
// se ao final do algoritmo d[i] = LINF,
// entao x nao alcanca i
//
// k = |S|
//  O(3^k * n + 2^k * m log m)

const int K = 8;
const int MAX = 30;

int n,m;
vector<int> S;
vector<pair<int, long long>> g[MAX]; // {vizinho, peso}
long long d[1 << K][MAX]; //[2^k][n]

ll steiner(){
    int k = S.size();
    for(int mask = 0; mask < (1 << k); mask++)for(int v = 0; v < n; v++) d[mask][v] = LINF;
    for(int i = 0; i < k; ++i) {
        d[1 << i][S[i]] = 0;
    }
    for(int mask = 1; mask < (1 << k); ++mask) {
        for(int a = mask; a > 0; a = (a-1) & mask){//itera sobre as submaskaras
            int b = mask ^ a;
            if(b > a) break;
            for(int v = 0; v < n; ++v) {
                d[mask][v] = min(d[mask][v], d[a][v] + d[b][v]);
            }
        }
        priority_queue<pair<ll, int>> pq;
        for(int v = 0; v < n; ++v) {
            if(d[mask][v] == LINF) continue;
            pq.emplace(-d[mask][v], v);
        }
        while (pq.size()) {
            auto [ndist, u] = pq.top(); pq.pop();
            if (-ndist > d[mask][u]) continue;
            for (auto [idx, w] : g[u]) if (d[mask][idx] > d[mask][u] + w) {
                d[mask][idx] = d[mask][u] + w;
                pq.emplace(-d[mask][idx], idx);
            }
        }
    }
    ll ans = LINF;
    for(int v = 0; v < n; v++) {
        ans = min(ans, d[(1 << k) - 1][v]);
    }
    return ans;
}


int main() { _
    while(true){
        cin >> n >> m;
        if(n==0)exit(0);
        map<string,int> idx;
        for(int i = 0; i < n; i++){
            string s;
            cin >> s;
            idx[s] = i;
        }
        for(int i = 0; i < m; i++){
            string u, v;
            int w;
            cin >> u >> v >> w;
            g[idx[u]].emplace_back(idx[v],w);
            g[idx[v]].emplace_back(idx[u],w);
        }
        pair<int,int> assignment[4];
        for(int i = 0; i < 4; i++){
            string u, v;
            cin >> u >> v;
            assignment[i] = {idx[u],idx[v]};
        }
        int dp[1<<4];
        dp[0] = 0;
        for(int mask = 1;mask < 1<<4; mask++){
            for(int i = 0; i < 4; i++){
                if((mask >> i)&1){
                    S.push_back(assignment[i].first);
                    S.push_back(assignment[i].second);
                }
            }
            dp[mask] = steiner();
            S.clear();
            for(int a = mask; a > 0; a = (a-1) & mask){//itera sobre as submaskaras
                int b = mask ^ a;
                if(b > a) break;
                dp[mask] = min(dp[mask],dp[a]+dp[b]);
            }
        }
        cout << dp[(1 << 4) -1] << '\n';
        
    }
	exit(0);
}
