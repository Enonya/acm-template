using i64 = long long;
using ldb = long double;

const int si = 50 + 10;
const ldb eps = 1e-5;

int n;
ldb c[si][si], d[si], x[si];

int Gauss() {
    for(int i = 1; i <= n; ++i) {
        int l = i;
        for(int j = i + 1; j <= n; ++j) 
            if(fabs(c[j][i]) > fabs(c[l][i]))
                l = j; // 找到最大的
        if(l != i) {
            for(int j = 1; j <= n; ++j) 
                swap(c[i][j], c[l][j]);
            swap(d[i], d[l]);
        } // 交换
        if(fabs(c[i][i]) >= eps) {
            for(int j = 1; j <= n; ++j) {
                if(j == i) continue;
                ldb rte = c[j][i] / c[i][i];
                for(int k = 1; k <= n; ++k)
                    c[j][k] -= rte * c[i][k];
                d[j] -= rte * d[i];
            }
        } // 消元
    }
    bool nosol = false, infsol = false;
    for(int i = 1; i <= n; ++i) {
        int j = 1;
        while(fabs(c[i][j]) < eps && j <= n)
            j ++;
        j += (fabs(d[i]) < eps);
        if(j > n + 1) infsol = true;
        if(j == n + 1) nosol = true;    
    } // 检查自由元
    if(nosol)  return 0;
    if(infsol) return 1;
    for(int i = n; i >= 1; --i) {
        for(int j = i + 1; j <= n; ++j)
            d[i] -= x[j] * c[i][j];
        x[i] = d[i] / c[i][i];
    } // 回代
    for(int i = 1; i <= n; ++i)
        cout << "x" << i << "=" << fixed << setprecision(2) << x[i] << endl;
    return 2;
}
