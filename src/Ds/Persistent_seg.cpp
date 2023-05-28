// 静态区间第 K 大
const int si = 1e5 + 10;
int n, m, len;
int a[si], id[si];
int tot = 0;
int ls[si << 5], rs[si << 5];
int root[si << 5], dat[si << 5];
int build(int l, int r) {
    int p = ++tot;
    if(l == r) return p;
    int mid = (l + r) >> 1;
    ls[p] = build(l, mid), rs[p] = build(mid + 1, r);
    return p;
}
int insert(int last, int l, int r, int val) { // last 是上一个版本的 [l, r] 节点。
    int p = ++tot;
    dat[p] = dat[last] + 1;
    if(l == r) return p;
    int mid = (l + r) >> 1;
    if(val <= mid) 
        ls[p] = insert(ls[last], l, mid, val), rs[p] = rs[last];
    else 
        rs[p] = insert(rs[last], mid + 1, r, val), ls[p] = ls[last];
    return p;
}
int ask(int p, int q, int l, int r, int kth) {
    if(l == r) return l;
    int mid = (l + r) >> 1;
    int lcnt = dat[ls[q]] - dat[ls[p]];
    if(kth <= lcnt) 
        return ask(ls[p], ls[q], l, mid, kth);
    else 
        return ask(rs[p], rs[q], mid + 1, r, kth - lcnt);
}
int index(int val) {
    return lower_bound(id + 1, id + 1 + len, val) - id;
}
int main() {
    read(n), read(m);
    for(int i = 1; i <= n; ++i)
        read(a[i]), id[i] = a[i];
    sort(id + 1, id + 1 + n);
    len = unique(id + 1, id + 1 + n) - id - 1;
    root[0] = build(1, len);
    for(int i = 1; i <= n; ++i)
        root[i] = insert(root[i - 1], 1, len, index(a[i]));
    while(m--) {
        int l, r, k; read(l), read(r), read(k);
        write(id[ask(root[l - 1], root[r], 1, len, k)]);
        write(endl);
    }

    return 0;
}

// 单点修改
const int si = 2e5 + 10;

int n, m, len;
int a[si], id[si << 1];

int tot = 0;
int ls[si << 8], rs[si << 8];
int root[si << 8], dat[si << 8];

int cnt1, cnt2;
int tr1[si], tr2[si];

struct Query { char opt; int l, r, x; } q[si];
inline int lowbit(int x) { return x & -x; }
inline int getid(int val) { return lower_bound(id + 1, id + 1 + len, val) - id; }

int build(int l, int r) {
    int p = ++tot;
    if(l == r) return l;
    int mid = (l + r) >> 1;
    ls[p] = build(l, mid), rs[p] = build(mid + 1, r);
    return p;
}
void insert(int &p, int last, int l, int r, int val, int delta) {
    p = ++tot;
    dat[p] = dat[last] + delta, ls[p] = ls[last], rs[p] = rs[last];
    if(l == r) return;
    int mid = (l + r) >> 1;
    if(val <= mid) insert(ls[p], ls[last], l, mid, val, delta);
    else insert(rs[p], rs[last], mid + 1, r, val, delta);
}
int ask(int l, int r, int kth) {
    if(l == r) return l;
    int mid = (l + r) >> 1;
    int lcnt = 0;
    for(int i = 1; i <= cnt2; ++i) lcnt += dat[ls[tr2[i]]];
    for(int i = 1; i <= cnt1; ++i) lcnt -= dat[ls[tr1[i]]];
    if(kth <= lcnt) {
        for(int i = 1; i <= cnt1; ++i) tr1[i] = ls[tr1[i]];
        for(int i = 1; i <= cnt2; ++i) tr2[i] = ls[tr2[i]];
        return ask(l, mid, kth);
    }   
    else {
        for(int i = 1; i <= cnt1; ++i) tr1[i] = rs[tr1[i]];
        for(int i = 1; i <= cnt2; ++i) tr2[i] = rs[tr2[i]];
        return ask(mid + 1, r, kth - lcnt);
    }
}
void change(int x, int v) {
    int y = getid(a[x]);
    while(x <= n) {
        insert(root[x], root[x], 1, len, y, v);
        x += lowbit(x);
    }
}
int query(int l, int r, int kth) {
    l --, cnt1 = cnt2 = 0;
    while(l) tr1[++cnt1] = root[l], l -= lowbit(l);
    while(r) tr2[++cnt2] = root[r], r -= lowbit(r);
    return ask(1, len, kth);
}

int main() {    
    cin >> n >> m;
    int cnt = 0;
    for(int i = 1; i <= n; ++i)
        cin >> a[i], id[++cnt] = a[i];
    for(int i = 1; i <= m; ++i) {
        Query &p = q[i];
        cin >> p.opt;
        if(p.opt == 'C')
            cin >> p.l >> p.x, id[++cnt] = p.x;
        if(p.opt == 'Q')
            cin >> p.l >> p.r >> p.x;
    }
    sort(id + 1, id + 1 + cnt);
    len = unique(id + 1, id + 1 + cnt) - id - 1;
    for(int i = 1; i <= n; ++i) change(i, 1);
    for(int i = 1; i <= m; ++i) {
        Query &p = q[i];
        if(p.opt == 'C') change(p.l, -1), a[p.l] = p.x, change(p.l, 1);
        if(p.opt == 'Q') cout << id[query(p.l, p.r, p.x)] << endl;
    }

    return 0;
}
