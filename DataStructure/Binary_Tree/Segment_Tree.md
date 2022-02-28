---
sort: 3
---

### Segment Tree

* 





**Segment Tree Code**

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

### Lazy Segment Tree

* 기존의 Segment Tree에서 Update를 계속해서 진행하지 않고 lazy 배열에 저장
* query 진행 전, update 진행 전, lazy[node] 의 값이 변경이 있을 때 propagate 진행
  * leaf 노드에 도달하는 것이 아니면 lazy 배열에 값 저장
  * leaf 노드에 도달하면 lazy 배열이 아닌, seg 값에 반영



**Lazy Segment Tree Code**

```c++
template <typename T>
class segment
{
private:
    T height;
    vector<T> seg, lazy;

public:
    segment(T n)
    {
        height = (ceil(log2(n)));
        seg.assign(1 << (height + 1), 0);
        lazy.assign(1 << (height + 1), 0);
    }

    T create_seg(T node, T l, T r)
    {
        if (l == r)
            return seg[node] = arr[l];
        else
        {
            T mid = (l + r) >> 1;
            return seg[node] = create_seg(2 * node, l, mid) + create_seg(2 * node + 1, mid + 1, r);
        }
    }
    void propagate(T node, T l, T r)
    {
        if (lazy[node] != 0)
        {
            seg[node] += (r - l + 1) * lazy[node];
            if (l != r)
            {
                lazy[2 * node] += lazy[node];
                lazy[2 * node + 1] += lazy[node];
            }
            lazy[node] = 0;
        }
    }
    void update(T node, T s, T e, T l, T r, T val)
    {
        propagate(node, l, r);
        if (e < l || r < s)
            return;
        if (s <= l && r <= e)
        {
            lazy[node] += val;
            propagate(node, l, r);
            return;
        }
        T mid = (l + r) >> 1;
        update(2 * node, s, e, l, mid, val);
        update(2 * node + 1, s, e, mid + 1, r, val);
        seg[node] = seg[2 * node] + seg[2 * node + 1];
    }
    T query(T node, T s, T e, T l, T r)
    {
        propagate(node, l, r);
        if (e < l || r < s)
            return 0;
        if (s <= l && r <= e)
            return seg[node];
        T mid = (l + r) >> 1;
        return query(2 * node, s, e, l, mid) + query(2 * node + 1, s, e, mid + 1, r);
    }
};

```





### Persistent Segment Tree











**Persistent Segment Tree Code**



```
```

