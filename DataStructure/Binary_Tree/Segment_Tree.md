---
sort: 3
---

# Segment Tree



세그먼트 트리란 





**Code**

```c++
#include <iostream>
using namespace std;
#pragma warning(disable:4996)
const int N = 1e5 + 1;
#define INF 1000000000

int seg[4 * N];
int start = 1;
int L, R;

int get_sum(int node, int leftnode, int rightnode) {
	if (L > rightnode || R < leftnode) return 0;
	if (L <= leftnode && rightnode <= R) return seg[node];
	int mid = (leftnode + rightnode) >> 1;
	return get_sum(2 * node, leftnode, mid) + get_sum(2 * node + 1, mid + 1, rightnode);
}

int get_min(const int &L, const int &R, const int &node, const int &leftnode, const int &rightnode)
{
	if (L > rightnode || R < leftnode)
		return INF;
	if (L <= leftnode && rightnode <= R)
		return seg[node];
	int mid = (leftnode + rightnode) >> 1;
	return min(get_min(L, R, 2 * node, leftnode, mid), get_min(L, R, 2 * node + 1, mid + 1, rightnode));
}

void update(int idx, int val) {
	int index = start + idx - 1;
	seg[index] = val;
	while (index) {
		index /= 2;
		seg[index] = seg[2 * index] + seg[2 * index + 1];
	}
}

int main() {
	int n, q;
	scanf("%d %d", &n, &q);
	while (n > start) start *= 2;
	for (int i = start - 1; i > 0; i--) seg[i] = seg[2 * i] + seg[2 * i + 1];  // construct
	int x, y, a, b;
	L = start + x - 1, R = start + y - 1; // range

	for (int i = 0; i < q; i++) {
		get_sum(1, start, 2 * start - 1);
		update(a, b);
	}
}

```

