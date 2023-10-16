int n,m;
vector<int> S;
vector<pair<int, long long>> g[MAX]; // {vizinho, peso}
long long d[1 << K][MAX]; //[2^k][n]

pair<ll,vector<pair<int,int>>> steiner(){
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
                
                pq.emplace(-d[mask][idx], idx);
            }
        }
    }
    ll ans = LINF;
    int u;
    for(int v = 0; v < n; v++) {
        ll sans = d[(1 << k) - 1][v];
        if(ans > sans)ans = sans,u = v;
        ans = min(ans, d[(1 << k) - 1][v]);
    }
    vector<pair<int,int>> edges;
    queue<pair<int, int>> q;
    pq.push_back({1<<k}-1,u);
    while(!q.empty()){
        bool cont = 0;
        auto [mask,u] = q.top();q.pop;
        if(!mask)continue;
        for (auto [idx, w] : g[u]){
            if(d[mask][idx] == d[mask][u] + w){
                cont = 1;
                edges.push_back({u,idx});//voce pode querer guardar o w em caso de arestas paralelas
                pq.push_back(mask,idx);
                break;
            }
        }
        if(cont)continue;
        for(int a = mask; a > 0; a = (a-1) & mask){//itera sobre as submaskaras
            int b = mask ^ a;
            if(d[mask][u] == d[a][u] + d[b][u]){
                pq.push_back(a,idx);
                pq.push_back(b,idx);
            }
        }
    }
    return {ans,edges};
}
