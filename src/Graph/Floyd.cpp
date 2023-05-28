for(int k = 1; k <= n; ++k)
    for(int i = 1;i <= n; ++i)
        for(int j = 1; j <= n; ++j)
            dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
// 不要忘记初始化.

// 最小环：
std::vector<int> ans_path;
void gopath(int u, int v) {
    if(pos[u][v] == 0)
        return;
    gopath(u, pos[u][v]), ans_path.push_back(pos[u][v]), gopath(pos[u][v], v);
}

signed main() {
    cin >> n >> m;
    memset(a, 0x3f, sizeof a);
    for(int i = 1; i <= n; ++i)
        a[i][i] = 0;
    for(int i = 1; i <= m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        a[u][v] = min(a[u][v], w), a[v][u] = a[u][v];
    }
    memcpy(dis, a, sizeof a);
    int ans = 0x3f3f3f3f3f3f3f3f, tmp = ans;
    for(int k = 1; k <= n; ++k)
        for(int i = 1; i < k; ++i) // 注意是dp之前，此时 dis 还是 k-1 的时候的状态。
            for(int j = i + 1; j < k; ++j)
                if(a[j][k] < tmp / 2 && a[k][i] < tmp / 2 && ans > dis[i][j] + a[j][k] + a[k][i])
                    ans = dis[i][j] + a[j][k] + a[k][i],
                    ans_path.clear(), ans_path.push_back(i), gopath(i, j),
                    ans_path.push_back(j), ans_path.push_back(k);
                // 不判的话 a[j][k]+a[k][i] 有可能爆，导致答案出错。
        // 更新最小环取min的过程
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= n; ++j)
                if(dis[i][j] > dis[i][k] + dis[k][j])
                    pos[i][j] = k, dis[i][j] = dis[i][k] + dis[k][j];
        // 正常的 Floyd
    }
    if(ans == 0x3f3f3f3f3f3f3f3f)
        return puts("No solution."), 0;
    for(auto x : ans_path)
        cout << x << " ";
    return puts(""), 0;
}
