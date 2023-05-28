ull base[si];
ull pf[si], sf[si];
int index(char ch) { return (ch - 'a') % 131; }
void Init(int n, string s) {
    base[0] = 1, pf[0] = sf[n + 1] = 0;
    for(int i = 1; i <= n; ++i)
        base[i] = base[i - 1] * 131ll;
    for(int i = 1; i <= n; ++i)
        pf[i] = pf[i - 1] * 131ll + 1ll * index(s[i]);
    for(int i = n; i >= 1; --i) 
        sf[i] = sf[i + 1] * 131ll + 1ll * index(s[i]);
}
ull query_pf(int l, int r) {
    return pf[r] - pf[l - 1] * base[r - l + 1];
}
ull query_sf(int l, int r) {
    return sf[l] - sf[r + 1] * base[r - l + 1];
}
ull Merge(int l, int r, int n) {
    return pf[l] * base[n - r + 1] + query_pf(r, n);
}
