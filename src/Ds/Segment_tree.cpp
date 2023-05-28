// {Lazytag} = {+}
class Segment_Tree {
    private : 
        struct Node {
            int l, r;
            i64 dat, tag;
        }t[si << 2];
        inline void pushup(int p) {
            t[p].dat = t[p << 1].dat + t[p << 1 | 1].dat; 
        }
        inline void pushdown(int p) {
            if(!t[p].tag) return;
            t[p << 1].dat += 1ll * t[p].tag * (t[p << 1].r - t[p << 1].l + 1);
            t[p << 1 | 1].dat += 1ll * t[p].tag * (t[p << 1 | 1].r - t[p << 1 | 1].l + 1);
            t[p << 1].tag += t[p].tag, t[p << 1 | 1].tag += t[p].tag, t[p].tag = 0;
        }
    public :
        void build(int p, int l, int r) {
            t[p].l = l, t[p].r = r, t[p].tag = 0;
            if(l == r) {
                t[p].dat = a[l];
                return;
            }
            int mid = (l + r) >> 1;
            build(p << 1, l, mid), build(p << 1 | 1, mid + 1, r);
            pushup(p); return;
        }
        void update(int p, int l, int r, int v) {
            if(l <= t[p].l && t[p].r <= r) {
                t[p].dat += v * (t[p].r - t[p].l + 1);
                t[p].tag += v; return;
            }
            pushdown(p); // 没到可以直接返回的时候，马上要递归子树了，也要 pushdown。
            int mid = (t[p].l + t[p].r) >> 1;
            if(l <= mid) 
                update(p << 1, l, r, v);
            if(r > mid) 
                update(p << 1 | 1, l, r, v);
            pushup(p); return;
        } 
        i64 query(int p, int l, int r) {
            i64 res = 0;
            if(l <= t[p].l && t[p].r <= r)
                return t[p].dat;
            pushdown(p); // 查询要查值，需要子树信息，必然要 pushdown。
            int mid = (t[p].l + t[p].r) >> 1;
            if(l <= mid) 
                res += query(p << 1, l, r);
            if(r > mid)
                res += query(p << 1 | 1, l, r);
            return res;
        }
};

// {Lazytag} = {+, *}
class Segment_Tree {
    private : 
        struct Node {
            int l, r;
            i64 dat, add, mul;
        }t[si << 2];
        inline void pushup(int p) {
            t[p].dat = (t[p << 1].dat + t[p << 1 | 1].dat) % mod;
        }
        inline void pushdown(int p) {
            if(!t[p].add && t[p].mul == 1) return;
            t[p << 1].dat = (t[p << 1].dat * t[p].mul + t[p].add * (t[p << 1].r - t[p << 1].l + 1)) % mod   ;
            t[p << 1 | 1].dat = (t[p << 1 | 1].dat * t[p].mul + t[p].add * (t[p << 1 | 1].r - t[p << 1 | 1].l + 1)) % mod;

            t[p << 1].mul = (t[p << 1].mul * t[p].mul) % mod;
            t[p << 1 | 1].mul = (t[p << 1 | 1].mul * t[p].mul) % mod;

            t[p << 1].add = (t[p << 1].add * t[p].mul + t[p].add) % mod;
            t[p << 1 | 1].add = (t[p << 1 | 1].add * t[p].mul + t[p].add) % mod;

            t[p].add = 0, t[p].mul = 1;
        }
    public : 
        void build(int p, int l, int r) {
            t[p].l = l, t[p].r = r, t[p].mul = 1ll, t[p].add = 0ll;
            if(l == r) {
                t[p].dat = a[l] % mod;
                return;
            }
            int mid = (l + r) >> 1;
            build(p << 1, l, mid), build(p << 1 | 1, mid + 1, r);
            pushup(p); return;
        }
        void update_add(int p, int l, int r, i64 v) {
            if(l <= t[p].l && t[p].r <= r) {
                t[p].add = (t[p].add + v) % mod;
                t[p].dat = (t[p].dat + v * (t[p].r - t[p].l + 1)) % mod;
                return;
            }
            pushdown(p);
            int mid = (t[p].l + t[p].r) >> 1;
            if(l <= mid)
                update_add(p << 1, l, r, v);
            if(r > mid)
                update_add(p << 1 | 1, l, r, v); 
            pushup(p); return;
        }
        void update_mul(int p, int l, int r, i64 v) {
            if(l <= t[p].l && t[p].r <= r) {
                t[p].add = (t[p].add * v) % mod;
                t[p].mul = (t[p].mul * v) % mod;
                t[p].dat = (t[p].dat * v) % mod;
                return;
            }
            pushdown(p);
            int mid = (t[p].l + t[p].r) >> 1;
            if(l <= mid) 
                update_mul(p << 1, l, r, v);
            if(r > mid)
                update_mul(p << 1 | 1, l, r, v);
            pushup(p); return;
        }
        i64 query(int p, int l, int r) {
            i64 res = 0ll;
            if(l <= t[p].l && t[p].r <= r)
                return t[p].dat % mod;
            pushdown(p);
            int mid = (t[p].l + t[p].r) >> 1;
            if(l <= mid) 
                res = (res + query(p << 1, l, r)) % mod;
            if(r > mid)
                res = (res + query(p << 1 | 1, l, r)) % mod;
            return res;
        }
};

Segment_Tree tr;
// 不要到主函数里定义，容易爆栈。

// Merge
int merge(int p, int q, int l, int r) {
    if(!p) return q; 
    if(!q) return p;
    if(l == r){
        t[p].mx += t[q].mx;
        return p;
    }
    int mid = (l + r) >> 1;
    t[p].ls = merge(t[p].ls, t[q].ls, l, mid);
    t[p].rs = merge(t[p].rs, t[q].rs, mid + 1, r);
    pushup(p); return p;
}

// SweepLine
void change(int p, int l, int r, int v) {
    int nl = t[p].l, nr = t[p].r;
    if(l <= nl && nr <= r) {
        t[p].cnt += v;
        if(t[p].cnt == 0) 
            t[p].len = (nl == nr) ? 0 : t[p << 1].len + t[p << 1 | 1].len;
            // 虽然当前区间直接被覆盖的次数等于 0 了，但还是要考虑下面的子树，因为它们有可能没被修改完。
        else t[p].len = raw[nr + 1] - raw[nl];
        return;
    }
    int mid = (nl + nr) >> 1;
    if(l <= mid) change(p << 1, l, r, v);
    if(r > mid) change(p << 1 | 1, l, r, v);
    if(t[p].cnt > 0) t[p].len = raw[nr + 1] - raw[nl];
    else t[p].len = t[p << 1].len + t[p << 1 | 1].len;
} 

