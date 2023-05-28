struct node {
	int value;
	node *next, *prev;
}, head, tail;
void init() {
    head = new node(), tail = new node();
    head -> next = tail, tail -> prev = head;
} 
void insert(node *p, int val) {
    node *q; q = new node();
    q -> val = val, p -> next -> prev = q;
    q -> next = p -> next, q -> prev = p, p -> next = q;
} 
void remove(node *p) {
    p -> prev -> next = p-> next,
	p -> next -> prev = p-> pre; delete p;
} 
