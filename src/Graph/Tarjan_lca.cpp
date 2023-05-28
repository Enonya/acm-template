int pa[si];
int root(int x) {
    if(pa[x] != x)
        return pa[x] = root(pa[x]);
    return pa[x];
}

int n, q, s;
int lca[si];
bool vis[si];
std::vector<int> que[si], pos[si];
void tarjan(int u) {
    vis[u] = true;
    for(int i = head[u]; ~i; i = e[i].Next) {
        int v = e[i].ver;
        if(vis[v] == true) continue;
        tarjan(v), pa[v] = root(u);
    }
    for(int i = 0; i < (int)que[u].size(); ++i) {
        int v = que[u][i], po = pos[u][i];
        if(vis[v] == true) lca[po] = root(v);
    }
}

int main(){
	cin >> n >> q >> s;
    for(int i = 1; i <= n; ++i)
        pa[i] = i, vis[i] = false,
        que[i].clear(), pos[i].clear();
    for(int i = 1; i < n; ++i) {
        int u, v;
		cin >> u >> v;
        add(u, v), add(v, u);
    }
    for(int i = 1; i <= q; ++i) {
        int u, v;
		cin >> u >> v;
        if(u == v) lca[i] = u;
        else {
            que[u].pb(v), que[v].pb(u);
            pos[u].pb(i), pos[v].pb(i);
        }
    }
    tarjan(s);
    for(int i = 1; i <= q; ++i)
        cout << lca[i] << endl;
    return 0;
}
