const ldb eps = 1e-9;
const int mod1 = 39989;
const int mod2 = 1e9;
const int si = 1e5 + 10;

int n, tot = 0;
struct Line { double k, b; } a[si];
ldb calc(int idx, int x) { return (a[idx].k * x + a[idx].b); }
void add(int x, int y, int xx, int yy) {
    ++tot;
    if(x == xx) a[tot].k = 0, a[tot].b = max(y, yy);
    else a[tot].k = (ldb)((1.0 * (yy - y)) / (1.0 * (xx - x))), a[tot].b = y - a[tot].k * x;
}
int cmp(ldb x, ldb y) {
    if((x - y) > eps) return 1; // Greater.
    else if((y - x) > eps) return -1; // Less
    return 0;
}
pdi Max(pdi x, pdi y) { 
    if(cmp(x.first, y.first) == 1) return x;
    else if(cmp(y.first, x.first) == 1) return y;
    return (x.second < y.second) ? x : y;
}

struct LichaoTree {
    int id[si << 2];
    void modify(int p, int l, int r, int u) {
        int &v = id[p], mid = (l + r) >> 1;
        if(cmp(calc(u, mid), calc(v, mid)) == 1) 
            swap(u, v);
       Lich boundl = cmp(calc(u, l), calc(v, l));
        int boundr = cmp(calc(u, r), calc(v, r));
        if(boundl == 1 || (!boundl && u < v)) 
       Lich modify(p << 1, l, mid, u);
        if(boundr == 1 || (!boundr && u < v))
            modify(p << 1 | 1, mid + 1, r, u);
    } // 
    void update(int p, int nl, int nr, int l, int r, int u) {
        if(l <= nl && nr <= r) 
            return modify(p, nl, nr, u);
        int mid = (nl + nr) >> 1;
        if(l <= mid) 
            update(p << 1, nl, mid, l, r, u);
        if(r > mid) 
            update(p << 1 | 1, mid + 1, nr, l, r, u);
    } 
    pdi query(int p, int l, int r, int x) {
        if(x < l || r < x) 
            return {0.0, 0};
        ldb ret = calc(id[p], x), mid = (l + r) >> 1;
        if(l == r) 
            return {ret, id[p]};
        return Max({ret, id[p]}, Max(query(p << 1, l, mid, x), query(p << 1 | 1, mid + 1, r, x)));
    }
} tr;
// update: 
if(x > xx) swap(x, xx), swap(y, yy);
add(x, y, xx, yy), tr.update(1, 1, mod1, x, xx, tot);
// query:
tr.query(1, 1, mod1, k).second;
