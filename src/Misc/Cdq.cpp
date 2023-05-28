// author : black_trees

#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

#define endl '\n'

using namespace std;
using i64 = long long;

const int si = 2e5 + 10;
const int inf = 0x3f3f3f3f;

struct Node {
	int a, b, c, cnt, res;
	bool operator != (const Node &rhs) const {
		if(a != rhs.a) return true;
		if(b != rhs.b) return true;
		if(c != rhs.c) return true;
		return false;
	}
} e[si], v[si];

bool cmpa(const Node &lhs, const Node &rhs) {
	if(lhs.a == rhs.a) {
		if(lhs.b == rhs.b) return lhs.c < rhs.c;
		return lhs.b < rhs.b;
	}
	return lhs.a < rhs.a;
}
bool cmpb(const Node &lhs, const Node &rhs) {
	if(lhs.b == rhs.b) return lhs.c < rhs.c;
	return lhs.b < rhs.b;
}

int n, m, V, d;
class Fenwick {
	private:
		int t[si];
		inline int lowbit(int x) { return x & -x; }
	public:
		void add(int x, int va) { while(x <= V) t[x] += va, x += lowbit(x); }
		int que(int x) { int ret = 0; while(x) ret += t[x], x -= lowbit(x); return ret; }
		void init(int n) { for(int i = 0; i <= n; ++i) t[i] = 0ll; }		
} tr;

void solve(int l, int r) {
	if(l == r) return;
	int mid = (l + r) >> 1;
	solve(l, mid), solve(mid + 1, r);
	sort(v + l, v + 1 + mid, cmpb);
	sort(v + 1 + mid, v + 1 + r, cmpb);
	int i = l, j = mid + 1;
	while(j <= r) {
		while(i <= mid && v[i].b <= v[j].b) {
			tr.add(v[i].c, v[i].cnt);
			++i;
		}
		v[j].res += tr.que(v[j].c);
		++j;
	}
	for(int k = l; k < i; ++k) 
		tr.add(v[k].c, -v[k].cnt);
}

int ans[si];
int main() {

	cin.tie(0) -> sync_with_stdio(false);
	cin.exceptions(cin.failbit | cin.badbit);

	cin >> n >> d;
	for(int i = 1; i <= n; ++i) {
		cin >> e[i].a >> e[i].b >> e[i].c;
		e[i].cnt = 1, V = max(V, e[i].c);
	}
	sort(e + 1, e + 1 + n, cmpa);
	v[0] = {0, 0, 0, 0, 0};
	for(int i = 1; i <= n; ++i) {
		if(e[i] != v[m]) v[++m] = e[i];
		else v[m].cnt += 1;
	}
	solve(1, m);
	for(int i = 1; i <= m; ++i) 
		ans[v[i].res + v[i].cnt - 1] += v[i].cnt;
	for(int i = 0; i < n; ++i)
		cout << ans[i] << endl;

	return 0;
}
