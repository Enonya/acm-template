// 求有多少个 s 在 t 中出现过。
namespace Ac_Automaton{
	const int si = 1e6 + 10; 
	int root = 0, tot = 0;
	int tr[si][27], End[si], fail[si]; 
	int cal(char ch) { return (int)(ch - 'a') + 1; }
	void init() {
		tot = 0; 
		memset(tr, 0, sizeof tr); 
		memset(End, 0, sizeof End); 
		memset(fail, 0, sizeof fail); 
	}
	void insert(char *s) {
		int u = 0; 
		for(int i = 1; s[i]; ++i) {
			if(!tr[u][cal(s[i])]) 
				tr[u][cal(s[i])] = ++ tot; 
			u = tr[u][cal(s[i])]; 
		} 
		++End[u]; 
	}
	std::queue<int>q; 
	void build() {
		for(int i = 1; i <= 26; ++i)
			if(tr[root][i]) q.push(tr[root][i]); 
		while(!q.empty()) {
			int u = q.front(); 
			q.pop(); 
			for(int i = 1; i <= 26; ++i) {
				if(tr[u][i]) 
					fail[tr[u][i]] = tr[fail[u]][i], q.push(tr[u][i]); 
				else tr[u][i] = tr[fail[u]][i]; 
			}
		}
	}
	int query(char *t) {
		int u = 0, res = 0; 
		for(int i = 1; t[i]; ++i) {
			u = tr[u][cal(t[i])]; 
			for(int j = u; j && End[j] != -1; j = fail[j])
				res += End[j], End[j] = -1; 
		}
		return res; 
	}
}
using namespace Ac_Automaton; 

// 求次数。
namespace Ac_Automaton {
	const int si = 2e6 + 10; 
	int root = 0, tot = 0, cnt_f = 0; 
	int tr[si][27], End[si], fail[si], cnt[si]; 
	int cal(char ch) { return (int)(ch - 'a') + 1; }
	void init() {
		tot = 0; 
		memset(tr, 0, sizeof tr); 
		memset(cnt, 0, sizeof cnt); 
		memset(End, 0, sizeof End); 
		memset(fail, 0, sizeof fail); 
	}
	void insert(char *s, int nu) {
		int u = 0; 
		for(int i = 1; s[i]; ++i) {
			if(!tr[u][cal(s[i])]) 
				tr[u][cal(s[i])] = ++ tot; 
			u = tr[u][cal(s[i])]; 
		}
		End[nu] = u; // 这里改为记录第 nu 个模式串的结尾的位置。
	}
	int head[si];
	struct Fail_Tree{ int ver, Next; }ft[si << 1]; 
	void add(int u, int v) { ft[cnt_f] = (Fail_Tree){v, head[u]}, head[u] = cnt_f++; }
	std::queue<int>q; 
	void build() {
		for(int i = 1; i <= 26; ++i)
			if(tr[root][i]) q.push(tr[root][i]); 
		while(!q.empty()) {
			int u = q.front(); 
			add(fail[u], u), q.pop();  // 构建 Fail 树
			for(int i = 1; i <= 26; ++i) {
				if(tr[u][i]) 
					fail[tr[u][i]] = tr[fail[u]][i], q.push(tr[u][i]); 
				else tr[u][i] = tr[fail[u]][i]; 
			}
		}
	}
	void dfs(int u, int fa) {
		for(int i = head[u]; ~i; i = ft[i].Next) {
			int v = ft[i].ver; 
			if(v == fa) continue; 
			dfs(v, u), cnt[u] += cnt[v]; 
		}  // 统计 
	}
	void query(char *t) {
		int u = 0; 
		for(int i = 1; t[i]; ++i)
			u = tr[u][cal(t[i])], ++cnt[u]; 
		// 记录每个状态被匹配多少次
		dfs(root, -1); 
		for(int i = 1; i <= n; ++i)
			printf("%d\n", cnt[End[i]]); 
	}
}
using namespace Ac_Automaton; 
