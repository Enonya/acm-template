std::priority_queue<std::pair<int, int> > q;
void dijkstra(int s) {
	memset(dis, 0x3f, sizeof dis);
    memset(vis, false ,sizeof vis);
    dis[s] = 0, q.push({dis[s], s});
    while(!q.empty()) {
        int u = q.top().second; 
		q.pop();
        if(vis[u]) continue; 
		vis[u] = true;
        for(int i = head[u]; ~i; i = e[i].Next) {
            int v = e[i].ver, w = e[i].w;
            if(dis[v] > dis[u] + w) 
				dis[v] = dis[u] + w, q.push({-dis[v], v}); //利用相反数把大根堆->小根堆
            // 一定要先更新 dis[v] 再 q.push
        }
    }
}
