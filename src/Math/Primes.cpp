bool is_prime(int n) {
    if(n < 2) return false;
    for(int i = 2; i * i <= n; ++i) 
        if(n % i == 0) return false;
    return true;
}

int vis[si];
int m, prime[si];
// O(n log log n)
void get_primes(int n) {
    m = 0;
    memset(vis, 0, sizeof vis);
    for(int i = 2; i <= n; ++i) {
        if(!vis[i]) prime[++m] = i;
        for(int j = i * i; j <= n; ++j) 
            vis[j] = 1;
    }
}

// Euler O(n)
void get_primes(int n) {
    m = 0;
    memset(vis, 0, sizeof vis);
    for(int i = 2; i <= n; ++i) {
        if(vis[i] == 0) { 
            vis[i] = i;
            prime[++m] = i;
        }
        for(int j = 1; j <= m; ++j) {
            if(prime[j] > vis[i] || prime[j] * i > n) 
                break;
            vis[prime[j] * i] = prime[j];
        }
    }
}

int c[si]; // exponential
int m = 0, p[si]; // prime factor
void divide(int n) {
    m = 0;
    for(int i = 2; i * i <= n; ++i) {
        if(n % i == 0) {
            p[++m] = i, c[m] = 0;
            while(n % i == 0) n /= i, c[m]++;
        }
    }
    if(n > 1) p[++m] = n, c[m] = 1;
}
