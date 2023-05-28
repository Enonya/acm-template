int inv[si], fact[si], invf[si];
void init(int n) {
    inv[1] = 1, fact[0] = invf[0] = 1;
    for(int i = 2; i <= n; ++i)
        inv[i] = 1ll * (mod - mod / i) * inv[mod % i] % mod;
    for(int i = 1; i <= n; ++i)
        fact[i] = 1ll * fact[i - 1] * i % mod,
        invf[i] = 1ll * invf[i - 1] * inv[i] % mod;
}
int C(int n, int m) {
    if(m < 0 || n < m) return 0;
    return 1ll * fact[n] * invf[n - m] % mod * invf[m] % mod;
}
int Catalan(int n) {
    return 1ll * C(n * 2, n) % mod * inv[n + 1] % mod;
}
