#define int long long
int crt(std::vector<int> &r, std::vector<int> &m) {
    int n = 1, ans = 0;
    for(int i = 0; i < (int)m.size(); ++i) 
        n = n * m[i];
    for(int i = 0; i < (int)m.size(); ++i) {
        int mi = n / m[i], b, y;
        exgcd(mi, m[i], b, y);
        ans = (ans + r[i] * mi * b % n) % n;
    }
    return (ans % n + n) % n;
}
