int lowbit(int x) { return x & -x; }
class Fenwick {
	private:
		int t[si], V;
	public:
		void init(int n) { V = n + 1; memset(t, 0, sizeof t); }
		void add(int x, int v) { while(x <= V) t[x] += v, x += lowbit(x); }
		int que(int x) { int ret = 0; while(x > 0) ret += t[x], x -= lowbit(x); return ret; }
} tr;
