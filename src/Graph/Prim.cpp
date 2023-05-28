void Prim() {
	memset(dis, 0x3f, sizeof dis);
    memset(vis, false, sizeof vis), dis[1] = 0;
    for(int i = 1; i < n; ++i) {
        int x = 0;
        for(int j = 1; j <= n; ++j)
            if(!vis[j] && (x == 0 || dis[j] < dis[x]))
                x = j;
        vis[x] = true;
        for(int y = 1; y <= n; ++y)
            if(!vis[y]) dis[y] = min(dis[y], a[x][y]);
    }
}

memset(a, 0x3f, sizeof a);
for(int i = 1; i < n; ++i) {
	a[i][i] = 0;
	for(int j = 1; j <= n; ++j) {
		int value;
		cin >> value;
		a[i][j] = a[j][i] = min(a[i][j], value);
	}
}
Prim();
int ans = 0;
for(int i = 2; i <= n; ++i)
	ans += dis[i];
