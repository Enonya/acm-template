std::queue<int> q;
void spfa(int s) {
	memset(dis, 0x3f, sizeof dis);
    memset(vis, false, sizeof vis);
    dis[s] = 0, q.push(s), vis[s] = true;
    while(!q.empty()) {
        int u = q.front(); 
		q.pop(), vis[u] = false;
        for(int i = head[u]; ~i; i = e[i].Next) {
            int v = e[i].ver, w = e[i].w;
            if(dis[v] > dis[u] + w){
                dis[v] = dis[u] + w;
                if(!vis[v]) q.push(v), vis[v] = true;
            }
        }
    }
}

// Minus Ring Check
bool vis[si];
std::queue<int> Q;
int dis[si], cnt[si];
bool spfa(int s) {
    memset(dis, 0, sizeof dis);
	memset(cnt, 0, sizeof cnt);
	memset(vis, false, sizeof vis);
    for(int i = 1; i <= n; ++i)
        Q.push(i), vis[i] = true;
	cnt[s] = 0; // 全部入队，相当于建立一个超级源点。
    while(!Q.empty()) {
        int u = Q.front(); 
		Q.pop(), vis[u] = false;
        for(int i = head[u]; ~i; i = e[i].Next) {
            int v = e[i].ver, w = e[i].w;
            if(dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w, cnt[v] = cnt[u] + 1;
                if(cnt[v] >= n) return true;
                if(!vis[v]) Q.push(v), vis[v] = true;
            }
        }
    } 
	return false;
}

// SLF + Swap Optimize

struct Slfswap {
    std::deque<int> dq;
    Slfswap() { dq.clear(); }
    void push(int x) {
        if(!dq.empty()) {
            if(dis[x] < dis[dq.front()]) 
				dq.push_front(x);
            else dq.push_back(x);
            if(dis[dq.front()] > dis[dq.back()]) 
				swap(dq.front(), dq.back());
            // 这里的两重 if 可以保证只会在至少有两个元素的时候才交换。
        } else dq.push_back(x);
    }
    void pop() {
        dq.pop_front();
        if(!dq.empty() && dis[dq.front()] > dis[dq.back()]) 
			swap(dq.front(), dq.back());
    }
    int size() { return dq.size(); }
    int front() { return dq.front(); }
    bool empty() { return !dq.size(); }
} q;
