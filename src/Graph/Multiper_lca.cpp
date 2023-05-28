int dep[si_n],f[si_n][20];
void dfs(int u, int fa) {
    dep[u] = dep[fa] + 1, f[u][0] = fa;
    for(int i = 1; i <= 19; ++i) 
        f[u][i] = f[f[u][i - 1]][i - 1];
    for(int i = head[u]; ~i; i = e[i].Next) {
        int v = e[i].ver; 
        if(v == fa) continue;
        dfs(v, u);
    }
}
int lca(int x, int y) {
    if(dep[x] < dep[y]) swap(x,y);
    for(int i = 19; i >= 0; --i) 
        if(dep[f[x][i]] >= dep[y]) x = f[x][i];
    if(x == y) return x;
    for(int i = 19; i >= 0; --i) 
        if(f[x][i] != f[y][i]) x = f[x][i], y = f[y][i];
    return f[x][0];
}
