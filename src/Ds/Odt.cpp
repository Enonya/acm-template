struct node {
    int l, r;
    mutable int val; 
    node(const int &il, const int &ir, const int &iv) : l(il), r(ir), val(iv) {}
    bool operator < (const node &b) const { return l < b.l; }
}; std::set<node> odt;

std::set<node>::iterator split(int pos) {
    if(pos > n) return odt.end();
    std::set<node>::iterator it = 
		--odt.upper_bound((node){pos, 0, 0});
    if(it -> l == pos) return it; 
    int l = it -> l, r = it -> r, v = it -> val;
    odt.erase(it), odt.insert((node){l, pos - 1, v}); 
    return odt.insert((node){pos, r, v}).first;
} // split the node [l,r] to two smaller node [l,pos),[pos,r];
void assign(int l, int r, int v) {
    std::set<node>::iterator itr = split(r + 1), itl = split(l); 
    odt.erase(itl, itr), odt.insert((node){l, r, v});
} // change all element in the interval [l,r] to v;
void example(int l, int r, int v) {
    std::set<node>::iterator itr = split(r + 1), itl = split(l);
    for(; itl != itr; ++itl) {
        // blablabla...
    } 
	return;
}
