int n, m, root;

int head[si], tot1 = 0;
int Head[si], tot2 = 0;
struct Edge { int ver, Next; }e[si << 2], g[si << 2];
void add1(int u, int v) { e[tot1] = (Edge){v, head[u]}, head[u] = tot1++; }
void add2(int u, int v) { g[tot2] = (Edge){v, Head[u]}, Head[u] = tot2++; }

// Vdcc 的个数
int cnt = 0;
int dfn[si], low[si], c[si], tim;
int new_id[si]; // 割点的新编号
bool cut[si]; // 是否是割点
std::stack<int> s;
std::vector<int> vdcc[si];

void tarjan(int u) {
    dfn[u] = low[u] = ++tim;
    s.push(u);
    // 孤立点
    if(u == root && head[u] == -1) {
        vdcc[++cnt].emplace_back(u);
        return;
    }
    int flag = 0;
    for(int i = head[u]; ~i; i = e[i].Next) {
        int v = e[i].ver;
        if(!dfn[v]) {
            tarjan(v), low[u] = min(low[u], low[v]);
            if(dfn[u] <= low[v]) {
                ++flag;
                // 根节点特判
                if(u != root || flag > 1) { // 注意这里是短路运算符，不要打反了。
                    cut[u] = true;
                }
                int x; ++cnt;
                do {
                    x = s.top(), s.pop();
                    vdcc[cnt].emplace_back(x);
                } while(v != x);
                // 注意这里要是 v 不是 u
                // 如果 u 被弹出了，之后的连通块就会少 u。
                vdcc[cnt].emplace_back(u);
            }
        }
        else low[u] = min(low[u], dfn[v]);
    }
}

int num;
void Construct() {
    num = cnt;
    for(int u = 1; u <= n; ++u)
        if(cut[u]) new_id[u] = ++num;
    for(int i = 1; i <= cnt; ++i) {
        for(int j : vdcc[i]) {
            if(cut[j]) add2(i, new_id[j]), add2(new_id[j], i);
            else c[j] = i;
        }
        // 如果是割点，就和这个割点所在的 v-Dcc 连边
        // 反之染色。
    }
    // 编号 1~cnt 的是 v-Dcc, 编号 > cnt 的是原图割点
}

int main() {
    memset(head, -1, sizeof head);
    memset(Head, -1, sizeof Head);

    cin >> n >> m;
    for(int i = 1; i <= m; ++i) {
        int u, v;
        cin >> u >> v;
        // 判重边
        if(u == v) continue;
        add1(u, v), add1(v, u);
    }
    for(int i = 1; i <= n; ++i)
        if(!dfn[i]) root = i, tarjan(i);
    Construct();
    return 0;
} 
