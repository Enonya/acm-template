struct Edge {
    int x, y, z;
    bool operator < (const Edge &b)const {
        return z < b.z;
    }
} a[si_m];

for(int i = 1; i <= m; ++i)
	cin >> a[i].x >> a[i].y >> a[i].z;
sort(a + 1, a + 1 + m);
int ans = 0;
for(int i = 1; i <= m; ++i) {
	if(dsu.same(a[i].x, a[i].y))
		continue;
	dsu.Union(a[i].x, a[i].y), ans += a[i].z;
}
