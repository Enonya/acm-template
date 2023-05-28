int k, a[si];
int stk[si], top = 0;
bool cmp(int x, int y) { return dfn[x] < dfn[y]; }
inline void ADD(int u, int v, int w) { E[Tot] = (Edge){v, Head[u], w}, Head[u] = Tot++; }
inline void Add(int u, int v) { int w = dist(u, v); ADD(u, v, w), ADD(v, u, w); }
void build() {
    sort(a + 1, a + 1 + k, cmp);
    stk[top = 1] = 1, Tot = 0, Head[1] = -1; // 这样清空复杂度才是对的。
    for(int i = 1, Lca; i <= k; ++i) {
        if(a[i] == 1) continue;
        Lca = lca(a[i], stk[top]);
        if(Lca != stk[top]) {
            while(dfn[Lca] < dfn[stk[top - 1]])
                Add(stk[top - 1], stk[top]), --top;
            if(dfn[Lca] > dfn[stk[top - 1]])
                Head[Lca] = -1, Add(Lca, stk[top]), stk[top] = Lca;
            else Add(Lca, stk[top--]); // Lca = stk[top - 1].
        }
        Head[a[i]] = -1, stk[++top] = a[i];
    }
    for(int i = 1; i < top; ++i)
        Add(stk[i], stk[i + 1]);
    return;
}
