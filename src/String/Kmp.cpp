Next[1] = 0;
for(int i = 2, j = 0; i <= n; ++i) {
    while(j > 0 && s[i] != s[j + 1]) j = Next[j];
    if(s[i] == s[j + 1]) j ++;
    Next[i] = j;
}
for(int i = 1, j = 0; i <= m; ++i) {
    while(j > 0 && (j == n || s[i] != s[j + 1])) j = Next[j];
    if(t[i] == s[j + 1]) ++j;
    f[i] = j;
    if(f[i] == n) orc[++cnt] = i - n + 1;
}
