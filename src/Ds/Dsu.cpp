int root(int x) {
    if(pa[x] != x) pa[x] = root(pa[x]);
    return pa[x];
}
void Merge(int x, int y) {
    int rx = root(x), ry = rooot(y);
    if(rx == ry) return; 
    if(siz[rx] < siz[ry]) 
        pa[rx] = ry, siz[rx] += siz[ry];
    else pa[ry] = rx, siz[ry] += siz[rx];
}
// remember to init!
