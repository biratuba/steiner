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
