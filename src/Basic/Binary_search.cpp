int l = 1, r = n; // 判无解则令 r = n + 1，这种写法 mid 永远不会取到 r
while(l < r) {
	int mid = (l + r) >> 1;
	if(a[mid] >= x) r = mid; // mid 也可能是答案，也要取。
	else l = mid + 1;
} 
ans = a[l];

int l = 1, r = n; // 判无解则令 l = 0，这种写法 mid 永远不会取到 l
while(l < r) {
    int mid =(l + r + 1) >> 1;
    if(a[mid] <= x) l = mid; // mid 也可能是答案，也要取。
    else r = mid - 1;
} 
ans = a[l];

double l = 0.0, r = (double)(1e9 + 7), ans;
while(l + eps < r){
    double mid = (l + r) / 2;
    if(valid(mid)) r = mid, ans = mid;
    else l = mid;
}
