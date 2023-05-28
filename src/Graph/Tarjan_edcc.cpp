int n, m, q;
// 原图
int head[si], tot1 = 0;
struct Edge { int ver, Next; }e[si << 2]; 
inline void add1(int u, int v) { e[tot1] = (Edge){v, head[u]}, head[u] = tot1++; }

// 缩完点之后的图
// 如果原来的图是连通图的话
// 可以证明缩完点之后必然是一棵树。
int Head[si], tot2 = 0;
struct Tree { int ver, Next; }t[si << 2];
inline void add2(int u, int v) { t[tot2] = (Tree){v, Head[u]}, Head[u] = tot2++; }

// E-dcc 的个数.
int cnt = 0; 
int dfn[si], low[si], tim = 0, c[si];
bool bridge[si << 2]; // 是否是桥

// in_edge 是用来消除重边的影响的。
// 表示当前状态是从哪一条边过来的。
void tarjan(int u, int in_edge) {
    dfn[u] = low[u] = ++tim;
    for(int i = head[u]; ~i; i = e[i].Next) {
        int v = e[i].ver;
        if(!dfn[v]) {
            tarjan(v, i);
            low[u] = min(low[u], low[v]);
            if(dfn[u] < low[v]) bridge[i] = bridge[i ^ 1] = true; 
        }
        else if((i ^ 1) != in_edge) low[u] = min(low[u], dfn[v]);
    }
}

// 去掉桥边的连通块染色
void dfs(int u, int col) {
    c[u] = col;
    for(int i = head[u]; ~i; i = e[i].Next) {
        int v = e[i].ver;
        if(c[v] || bridge[i]) continue;
        dfs(v, col);
    }
} 
void Construct() {
    for(int i = 1; i <= n; ++i){
        for(int j = head[i]; ~j; j = e[j].Next) {
            int v = e[j].ver;
            if(c[i] == c[v]) continue;
            // 只需要加一次，遍历到反向边的时候会自动补全成无向边
            add2(c[i], c[v]);
        }
    }
}

int main() {
    memset(head, -1, sizeof head);
    memset(Head, -1, sizeof Head);
    memset(bridge, false, sizeof bridge);
    cin >> n >> m;
    for(int i = 1; i <= m; ++i) {
        int u, v;
        cin >> u >> v;
        add1(u, v), add1(v, u);
    }
    for(int i = 1; i <= n; ++i) if(!dfn[i]) tarjan(i, -1);
    for(int i = 1; i <= n; ++i) if(!c[i]) ++cnt, dfs(i, cnt);
    Construct();
}
