---
sort: 2
---

# Kruskal

* 프림 알고리즘은 node를 기준으로 연결하지만, 크루스칼 알고리즘은 edge를 기준으로 연결

* edge를 기준으로 하기 때문에 union-find로 edge를 연결함

* 시간 복잡도는 edge로 우선순위 큐를 구성할 때 O($$ElogE$$)이다.

* 간선의 수가 적은 Sparse Matrix인 경우, Prim 알고리즘보다 크루스칼이 적합함

  

**Code**

```c++
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
#define nodecount 1001
int n, m;

struct node {
	int s, e, val;
};
vector <node> vc[nodecount];
priority_queue<node,vector<node>,greater<node>> pq;

int parent[nodecount];
int start, cnt, edgecount;

int find(int a) {
	if (parent[a] == a) return a;
	return find(parent[a]);
}

int kruskal() {

	for (int i=0; i<edgecount; i++) {
		node e;
		pq.push(e);
	}

	int ret = 0;
	while (!pq.empty()) {
		int value = pq.top().val, src = pq.top().s, tgt = pq.top().e;
		pq.pop();
		int p1 = find(src), p2 = find(tgt);
		if (p1 != p2) {
			// union
			ret += value;
			cnt++;
			parent[p1] = p2;
		}
		if (cnt == n) {
			cout << "cycle" << endl;
			return -1;
		}
	}
	if (cnt != nodecount-1) {
		cout << "all node not connected" << endl;
		return -2;
	}
	return ret;
}

```



