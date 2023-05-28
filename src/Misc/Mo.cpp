int n, Q, unit;
int a[si];
struct Query {
    int l, r, id;
    bool operator < (const Query &b) const {
        if((l / unit) != (b.l / unit)) 
            return l < b.l;
        if((l / unit) & 1) 
            return r < b.r;
        return r > b.r; 
    } 
}ask[si];
void add(int pos) { }
void sub(int pos) { }

int main() {    
    std::vector<int> v; v.clear();
    cin >> n, unit = sqrt(n);
    for(int i = 1; i <= n; ++i)
        cin >> a[i], v.emplace_back(a[i]);
    sort(v.begin(), v.end()), v.erase(unique(v.begin(), v.end()), v.end());
    for(int i = 1; i <= n; ++i)
        a[i] = lower_bound(v.begin(), v.end(), a[i]) - v.begin();

    cin >> Q;
    for(int i = 1; i <= Q; ++i) 
        cin >> ask[i].l >> ask[i].r,
        ask[i].id = i;
    sort(ask + 1, ask + 1 + Q);

    int l = 1, r = 0;
    for(int i = 1; i <= Q; ++i) {
        Query &q = ask[i];
        while(l > q.l) add(--l);
        while(r < q.r) add(++r);
        while(l < q.l) sub(l++);
        while(r > q.r) sub(r--);
        res[q.id] = ans;
    }

    for(int i = 1; i <= Q; ++i)
        cout << res[i] << endl;
    return 0;
}
