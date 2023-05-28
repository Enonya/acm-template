// 定义 NULL 为 0，字符集为 a~z。
int tr[si][27];
bool exist[si];
int tot, root;

void init() {
    memset(tr, 0, sizeof tr);
    memset(exist, false, sizeof exist);
    tot = 0, root = ++tot;
}
void insert(string s) {
    int p = root;
    for(int i = 0; i < (int)s.size(); ++i) {
        int ch = (int) (s[i] - 'a') + 1;
        if(!tr[p][ch])
            tr[p][ch] = ++tot;
        p = tr[p][ch];
    }
    exist[p] = true;
}
bool query(string s) {
    int p = root;
    for(int i = 0; i < (int)s.size(); ++i) {
        int ch = (int) (s[i] - 'a') + 1;
        if(!tr[p][ch])
            return false;
        p = tr[p][ch];
    }
    return exist[p];
}
