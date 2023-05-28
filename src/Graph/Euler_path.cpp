std::stack<int> s;
void dfs(int u) {
    for(int i = head[u]; ~i ; i = e[i].Next) {
        int v = e[i].ver;
        if(!vis[i]){ // 当前边没有访问过
            vis[i] = true; // 注意一定要访问到就直接标记，不然复杂度会假。
            dfs(v), s.push(v);
        }
    }
}

dfs(1); // 因为有欧拉回路，所以其实从哪个点开始都一样。
std::vector<int>ans; 
while(!s.empty()) 
	ans.push_back(s.top()), s.pop();
reverse(ans.begin(), ans.end()); 
for(auto x : ans) cout << x << " "; // 倒序输出。
