int exgcd(int a, int b, int &x, int &y) {
    if(!b) { x = 1, y = 0; return a; }
    int d = exgcd(b, a % b, x, y);
    int z = x; x = y; y = z - y * (a / b);
}
