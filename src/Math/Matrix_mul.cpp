struct Matrix {
    int a[si][si];
    Matrix() { memset(a,0,sizeof a); }
    Matrix operator * (const Matrix &B) const {
        Matrix C, A = *this;
        for(int i = 1; i <= cnt; ++i)
            for(int j = 1; j <= cnt; ++j)
                for(int k = 1; k <= cnt; ++k)
                    C.a[i][j] += A.a[i][k] * B.a[k][j];
        return C;
    }
};
// 循环的时候最好不要用 si。
// 用一个设定好的常数或者题目给的变量会比较好。
// 但是如果乘法不止需要适用于一对 n,m,k，那么就最好用 si - 1。
// 为啥不会有影响呢？因为构造函数里把没有用到的设置成 0 了。
