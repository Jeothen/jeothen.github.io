---
sort: 7
---

# Union Find





**Code**

```c++
#include <iostream>
using namespace std;
#define node 50

int parent[node];
int nodesize[node];

int find(int u)
{
	if (u == parent[u]) return u;
	return parent[u] = find(parent[u]);
}

void _union(int a, int b) {
	int pa = find(a);
	int pb = find(b);
	if (pa == pb) return;
	if (nodesize[pa] > nodesize[pb]) swap(pa, pb); 
	printf("%d %d\n", a, b);
	parent[pa] = pb;
	nodesize[pb]++;
	return;
}

```



**DSU**

* DSU (Disjoint Set Union)는 Union과 Find 기능을 제공하는 Container
* 

```c++
#include <iostream>
using namespace std;
#define node 50

class dsu
{
public:
	int p[node];
	int n;
	dsu(int _n) : n(_n)
	{
		for (int i=0;i<n;i++) p[i] = i;
	}
	int get(int x)
	{
		return (x == p[x] ? x : (p[x] = get(p[x])));
	}
	bool unite(int x, int y)
	{
		x = get(x);
		y = get(y);
		if (x != y)
		{
			p[x] = y;
			return true;
		}
		return false;
	}
};
```

