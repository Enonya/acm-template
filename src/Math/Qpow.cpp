int Qpow(int a, int b) {
	int ret = 1 % mod;
	for(; b; b >>= 1) {
		if(b & 1) ret = ret * a % mod;
		a = a * a % mod;
	}
	return ret % mod;
} 
