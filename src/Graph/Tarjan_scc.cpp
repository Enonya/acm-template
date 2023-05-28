
bool ins[si]; 
std::stack<int> s; 
std::vector<int> scc[si]; 
int n, m, cnt_t = 0, tot = 0; 
int dfn[si], low[si], c[si]; 

void tarjan(int u) {
    dfn[u] = low[u] = ++cnt_t; 
    s.push(u), ins[u] = true; 
    for(int i = head[u]; ~i; i = e[i].Next) {
        int v = e[i].ver; 
        if(!dfn[v]) 
			tarjan(v), low[u] = min(low[u], low[v]); 
        // 没有访问过，递归搜索然后更新 low。
        else if(ins[v]) low[u] = min(low[u], dfn[v]); 
        // 已经在栈中了，用 dfn[v] 来更新 low[u]。
    }
    if(dfn[u] == low[u]) {
        ++tot; int x; 
        do {
            x = s.top(), s.pop(), ins[x] = false; 
            c[x] = tot, scc[tot].pb(x); 
        } while(u! = x); 
    } // 出现了一个 SCC。
}

Edge edag[si << 1]; 
void contract() {
    for(int u = 1; u <= n; ++u) {
        for(int i = head[u]; ~i; i = e[i].Next) {
            int v = e[i].ver; 
            if(c[u] == c[v]) continue; 
            add_n(c[u], c[v]); 
        }
    } // 缩点。
}

for(int i = 1; i <= n; ++i)
	if(!dfn[i]) tarjan(i);
