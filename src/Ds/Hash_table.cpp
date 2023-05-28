const int si = 1e5 + 10;
int n, a[si], tot = 0;
int head[si], val[si], cnt[si], Next[si];

int H(int x) { return (x % p) + 1; }
bool insert(int x) {
    bool exist = false;
    int u = H(x); 
    for(int i = head[u]; ~i; i = Next[i]) {
        if(val[i] == x) {
            cnt[i]++, exist = true;
            break;
        }
    }
    if(exist) return true;
    ++tot, Next[tot] = head[u], val[tot] = x, cnt[tot] = 1, head[u] = tot;
    return false;
}
int query(int x) {
    int u = H(x);
    for(int i = head[u]; ~i; i = Next[i])
        if(val[i] == x) return cnt[i];
    return 0;
}
