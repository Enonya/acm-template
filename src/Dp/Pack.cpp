
// 01
int dp[si];

memset(dp, 0, sizeof dp);
for(int i = 1; i <= n; ++i)
  for(int j = m; j >= v[i]; --j)
    dp[j] = max(dp[j], dp[j - v[i]] + w[i]);
  // 因为直接共用一个数组了，所以不用手动继承上一个阶段了。
cout << dp[m] << endl;

// Complete
memset(dp, 0, sizeof dp);
for(int i = 1; i <= n; ++i)
    for(int j = v[i]; j <= m; ++j)
        dp[j] = max(dp[j], dp[j - v[i]] + w[i]);
cout << dp[m] << endl;

// Multi
for(int i = 1; i <= n; ++i)
	scanf("%d%d%d", &v[i], &w[i], &c[i]); 
auto calc = [&](int u, int i, int k) - >int {
	return f[u + k * v[i]] - k * w[i]; }; 
for(int i = 1; i <= n; ++i) {
	for(int u = 0; u < v[i]; ++u) {
		int head = 1, tail = 0;  
		memset(q, 0, sizeof q); 
		int mxp = (m - u) / v[i]; 
		for(int k = mxp - 1; k >= max(mxp - c[i], 0); --k) {
			while(head <= tail && calc(u, i, q[tail]) <= calc(u, i, k)) tail -- ; 
			q[++tail] = k; 
		}
		for(int p = mxp; p >= 0; --p) {
			while(head <= tail && q[head]>p - 1) head++; 
			if(head <= tail) 
				f[u + p * v[i]] = max(f[u + p * v[i]], calc(u, i, q[head]) + p * w[i]); 
			if(p - c[i] - 1 >= 0) {
				while(head <= tail && calc(u, i, q[tail]) <= calc(u, i, p - c[i] - 1)) tail -- ; 
				q[++tail] = p - c[i] - 1; 
			}
		}
	}
}
// Group
for(int i = 1; i <= n; ++i) // 枚举组
	for(int j = m; j >= 0; --j) // 枚举给每一个组分多少空间
		// 需要保证每组只选一个，所以要像 01 背包一样倒序循环。
		for(int k = 1; k <= c[i]; ++k) { // 枚举这组选哪一个
			if(j >= v[i][k]) 
				dp[j] = max(dp[j], dp[j - v[i][k]] + w[i][k]);
// Tree
void dfs(int u, int fa) {
    for(int i = 0; i < (int)g[u].size(); ++i) {
        int ver = g[u][i];
        if(ver == fa) continue;
        dfs(ver, u);
    }
    for(int i = 0; i < (int)g[u].size(); ++i) {
        int ver = g[u][i];
        if(ver == fa) continue;
        for(int j = m - v[u]; j >= 0; --j) // 枚举排除 u 自己的，总共可以往下分配的空间
            for(int k = 0; k <= j; ++k) // 可以给当前子树分配的空间
                dp[u][j] = max(dp[u][j], dp[u][j - k] + dp[ver][k]);
    }
    // 上面的循环也可以放到 dfs 后面去
    for(int i = m; i >= v[u]; --i) // 强制选 u 的转移。
        dp[u][i] = dp[u][i - v[u]] + w[u];
    for(int i = 0; i < v[u]; ++i) // 连 u 的空间都无法满足，0
        dp[u][i] = 0;
}
