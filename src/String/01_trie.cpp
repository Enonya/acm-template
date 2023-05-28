using i64 = long long; 

const int si = 1e5 + 10; 
const int k = 32; 
int tr[k * si][2]; 
i64 value[k * si]; 
int tot = 0, root = ++tot; 

int newnode() {
    tr[++tot][0] = tr[tot][1] = value[tot] = 0;
    return tot;
}
int cacid(int num, int pos) {
    return (num >> pos) & 1; 
}
void insert(int num) {
    int p = root; 
    for(int i = 32; i >= 0; --i) {
        int ch = cacid(num, i); 
        if(!tr[p][ch]) 
            tr[p][ch] = newnode();
        p = tr[p][ch]; 
    }
    value[p] = num; 
}
// 查询异或 x 最大的一个。
i64 query(i64 num) {
    int p = root; 
    for(int i = 32; i >= 0; --i) {
        int ch = cacid(num, i); 
        if(tr[p][ch ^ 1])
            p = tr[p][ch ^ 1]; 
        else
            p = tr[p][ch]; 
    }
    return value[p]; 
}

// 维护异或和，全局加一。
const int si = 1e4 + 10;
const int MaxDepth = 21;

int tr[si * (MaxDepth + 1)][2];
int wei[si * (MaxDepth + 1)], xorv[si * (MaxDepth + 1)];
int tot = 0, root = ++tot;
// 其实这里 root 可以不用赋值，递归开点的时候会自动给编号的。

int newnode() {
    tr[++tot][0] = tr[tot][1] = wei[tot] = xorv[tot] = 0;
    return tot;
}
void maintain(int p) {
    wei[p] = xorv[p] = 0;
    // 为了应对不断的删除和插入，每次维护 p 的时候都令 wei, xorv = 0。
    // 也就是每次都**重新收集一次信息**，而不是从原来的基础上修改。
    if(tr[p][0]) {
        wei[p] += wei[tr[p][0]];
        xorv[p] ^= (xorv[tr[p][0]] << 1);
        // 因为儿子所维护的异或和实际上比 p 少一位，
        // 如果要按位异或就要让儿子的异或和左移一位，和 p 对齐。
    }
    if(tr[p][1]) {
        wei[p] += wei[tr[p][1]];
        xorv[p] ^= (xorv[tr[p][1]] << 1) | (wei[tr[p][1]] & 1);
        // 利用奇偶性计算。
    }
    wei[p] = wei[p] & 1;
    // 每插入一次或者删除一次，奇偶性都会变化。
}
// 类似线段树的 pushup，从底向上收集信息。
// 换种说法，是更新节点 p 的信息。
void insert(int &p, int x, int depth) {
    if(!p) 
        p = newnode();
    if(depth > MaxDepth) {
        wei[p] += 1;
        return;
    }
    insert(tr[p][x & 1], x >> 1, depth + 1);
    // 从低到高位插入，所以是 x >> 1。
    maintain(p);
}
// 插入元素 x。
void remove(int p, int x, int depth) {
    // 不知道是不是应该写 > MaxDepth - 1 还是 > MaxDepth ？
    if(depth == MaxDepth) {
        wei[p] -= 1;
        return;
    }
    remove(tr[p][x & 1], x >> 1, depth + 1);
    maintain(p);
}
// 删除元素 x，但是 x 不能是不存在的元素。
// 否则会访问空节点 0 然后继续往下，会出错。
void addall(int p) {
    swap(tr[p][0], tr[p][1]);
    if(tr[p][0]) 
        addall(tr[p][0]);
    maintain(p);
    // 交换后下面都被更改了，需要再次 maintain。
}
// 全部加一

int main() {
    int n;
    cin >> n;
    std::vector<int> v(n + 1);
    for(int i = 1; i <= n; ++i) {
        cin >> v[i],
        insert(root, v[i], 0);
    }
    cout << xorv[root] << endl;
    // 查询总异或和
    int m;
    cin >> m;
    for(int i = 1; i <= m; ++i) {
        int x, y;
        cin >> y >> x;
        if(y == 0)
            remove(root, x, 0);
            // remove 和 addall 混用时小心 remove 掉不存在的元素！
        else
            addall(root);
        cout << xorv[root] << endl;
    }
}

// merge
int merge(int p, int q) {
    if(!p) 
        return q;
    if(!q) 
        return p;
    wei[p] += wei[q], xorv[p] ^= xorv[q];
    tr[p][0] = merge(tr[p][0], tr[q][0]);
    tr[p][1] = merge(tr[p][1], tr[q][1]);
    return p;
}
