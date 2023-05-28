int cnt = 0;
std::queue<int> q;
for(int i = 1; i <= n; ++i) 
    if(!ind[i]) q.push(i);
while(!q.empty()) {
    int u = q.front(); q.pop();
    ord[u] = ++cnt; // topo 序
    for(auto v : G[u]) if(!(--ind[v])) q.push(v);
    // 删掉边，顺便判一下要不要入队。
}
