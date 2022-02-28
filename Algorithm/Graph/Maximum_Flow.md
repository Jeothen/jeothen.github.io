---
sort: 1
---

# Maximum Flow

* There's a cost on the edge. not only the weights
* The Flow of each edges must not exceed the capacity of each edges
* Excepts source and target node, Every node has the same input and output flow
* If cost is negative value, It flows in the reverse way



* there's a many maximum flow algorithm

**Ford-Fulkerson Algorithm**

* If the flow is already flowing, reverse way flow is possible.

  * It doesn't actually applied, but it decreased by the reverse direction from the already flow

  

* Finding the augmenting path

* The path found must be a shortest path that has available capacity

  * Found by DFS (Ford-Fulkerson), time complexity is always O(V+E)
    * there's a two ways bottle-neck, Time complexity increases geometrically 

  * Found by BFS (**Edmonds-Karp Algorithm**)
    * Maximum Time complexity is O(V*E^2)

* Flow the smallest weight to all the edges that can go in the path.

  





---

* When passing through the edge only once, the capacity size is set to 1.

* but, when passing node at once, visit[array] is not sufficient all case.

  * If the the node has already visited, reverse flow is not considered.

  * So,  setting to edges, not nodes(visit array), can be considered reverse flow

  * Creating Every node's in / out and Flowing In to out.

    



**Code**

```c++
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#define MAX 100
#define INF 100000000
using namespace std;

int n = 6, result;
int c[MAX][MAX], f[MAX][MAX], d[MAX]; 
vector <int> a[MAX];

void maxFlow(int start, int end) {
	while (1) {
		fill(d, d + MAX, -1);
		queue<int> q;
		q.push(start);
		while (!q.empty()) {
			int x = q.front();
			q.pop();
			for (int i = 0; i < a[x].size(); i++) {
				int y = a[x][i];
				if (c[x][y] - f[x][y] > 0 && d[y] == -1) {
					q.push(y);
					d[y] = x; 
					if (y == end) break; 
				}
			}
		}
		if (d[end] == -1) break;
		int flow = INF;
		for (int i = end; i != start; i = d[i]) {
			flow = min(flow, c[d[i]][i] - f[d[i]][i]);
		}
		for (int i = end; i != start; i = d[i]) {
			f[d[i]][i] += flow;
			f[i][d[i]] -= flow;
		}
		result += flow;
	}
}

int main() {
	a[1].push_back(2);
	a[2].push_back(1);
	c[1][2] = 12;

	a[1].push_back(4);
	a[4].push_back(1);
	c[1][4] = 11;

	a[2].push_back(3);
	a[3].push_back(2);
	c[2][3] = 6;

	a[2].push_back(4);
	a[4].push_back(2);
	c[2][4] = 3;

	a[2].push_back(5);
	a[5].push_back(2);
	c[2][5] = 5;

	a[2].push_back(6);
	a[6].push_back(2);
	c[2][6] = 9;

	a[3].push_back(6);
	a[6].push_back(3);
	c[3][6] = 8;

	a[4].push_back(5);
	a[5].push_back(4);
	c[4][5] = 9;

	a[5].push_back(3);
	a[3].push_back(5);
	c[5][3] = 3;

	a[5].push_back(6);
	a[6].push_back(5);
	c[5][6] = 4;

	maxFlow(1, 6);
	printf("%d", result);
}

```

