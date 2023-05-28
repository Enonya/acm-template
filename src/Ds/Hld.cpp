// 处理重儿子,父亲,深度,子树大小
void dfs1(int u, int fa) {
    int kot = 0;
    hson[u] = -1, siz[u] = 1;
    fat[u] = fa, dep[u] = dep[fa] + 1;
    for(int i = head[u]; ~i; i = e[i].Next) {
        int v = e[i].ver;
        if(v == fa) continue;
        dfs1(v, u), siz[u] += siz[v];
        if(siz[v] > kot)
            kot = siz[v], hson[u] = v;
    } 
}
// 处理 dfn,rnk,并进行重链剖分。
void dfs2(int u, int tp) {
    top[u] = tp, dfn[u] = ++tim, rnk[tim] = u;
    if(hson[u] == -1) return;
    dfs2(hson[u], tp);
    // 先 dfs 重儿子,保证重链上 dfn 连续,维持重链的性质
    for(int i = head[u]; ~i; i = e[i].Next) {
        int v = e[i].ver;
        if(v == fat[u] || v == hson[u]) continue;
        dfs2(v, v);
    }
}
void add_subtree(int u, int value) {
    tr.update(1, dfn[u], dfn[u] + siz[u] - 1, value);
    // 子树代表的区间的左右端点分别是 dfn[u], dfn[u] + siz[i] - 1;
} 
int query_subtree(int u) {
    return tr.query(1, dfn[u], dfn[u] + siz[u] - 1) % mod;
}
// 类似倍增 LCA 的跳重链过程
void add_path(int u, int v, int value) {
    while(top[u] != top[v]) {
        if(dep[top[u]] < dep[top[v]])
            swap(u, v);
        // 让链顶深度大的来跳

        tr.update(1, dfn[top[u]], dfn[u], value);
        // 把 u 到链顶的权值全部修改。
        u = fat[top[u]];    
        // 跳到链顶的父亲节点。   
    }

    if(dep[u] > dep[v]) swap(u, v);
    tr.update(1, dfn[u], dfn[v], value);
    // 一条重链上的 dfn 是连续的。
}
int query_path(int u, int v) {
    int ret = 0;
    while(top[u] != top[v]) {
        if(dep[top[u]] < dep[top[v]])
            swap(u, v);
        ret = (ret + tr.query(1, dfn[top[u]], dfn[u])) % mod;
        u = fat[top[u]];
    }
    if(dep[u] > dep[v]) swap(u, v);
    ret = (ret + tr.query(1, dfn[u], dfn[v])) % mod;
    return ret % mod;
}
int lca(int u, int v) {
    while(top[u] != top[v]) {
        if(dep[top[u]] < dep[top[v]]) 
            swap(u, v);
        u = fat[top[u]];
    }
    if(dep[u] > dep[v]) swap(u, v);
    return u;
}
