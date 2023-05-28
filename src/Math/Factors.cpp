int m, div[si];
void get_factors(int n) {
    m = 0;
    for(int i = 1; i * i <= n; ++i)
        if(n % i == 0) {
            div[++m] = i; 
            if(i * i != n) div[++m] = n / i;
        }
}

std::vector<int> fact[si];
void get_factors(int n) {
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n / i; ++j)
            fact[i * j].emplace_back(i);
}

int gcd(int a, int b) {
	return b ? gcd(b, a % b) : a;
}

int phi[si];
int m = 0, prime[si], vis[si];
void calc_euler_func(int n) {
  m = 0, phi[1] = 1;
  memset(vis, 0, sizeof vis);
  for(int i = 2; i <= n; ++i) {
      if(vis[i] == 0) 
          vis[i] = i, prime[++m] = i, phi[i] = i - 1; 
      for(int j = 1; j <= m; ++i) {
          if(prime[j] > vis[i] || prime[j] * vis[i] > n) break;
          vis[prime[j] * i] = prime[j];
          if(i % prime[j] == 0)
              phi[prime[j] * i] = phi[i] * prime[j]; 
          else 
              phi[prime[j] * i] = phi[i] * (prime[j] - 1);
      }
  }
}
