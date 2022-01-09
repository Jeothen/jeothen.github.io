---
sort: 1
---

# Dijkstra

* Algorithm that can calculate the shortest distance from source node to target node
* The time complexity is O((V+E)logV).  -  priority queue performed with pibonachi heap.
  * For each node, O(VlogV) is needed to find the node with the shortest distance calculated from the stating point among unvisited nodes
  * For each node, O(ElogV) is needed when updating the shortest distance of neighboring nodes.

* It cannot be used if there is a negative value.



### Code

```c++
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

#define node 20001  // max node

const int INF = 1e9;

int start;
vector<pair<int, int>> vc[node];  // node to node and value

int dist[node];
bool visited[node];

priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // calculate from minimum distance

void dijkstra()
{
	pq.push({0, start});
	while (!pq.empty())
	{
		int value = pq.top().first, now = pq.top().second;
		visited[now] = true;
		pq.pop();
		for (vector<int>::size_type i = 0; i < vc[now].size(); i++)
		{
			int d = vc[now][i].first, next = vc[now][i].second;
			if (!visited[next])  // not visited
			{
				if (dist[next] > d + value) 
				{
					dist[next] = d + value;  // updated least distance
					pq.push({dist[next], next});  
				}
			}
		}
	}
}

void init(){
	int nodecount;
	for (int i = 1; i <= nodecount; i++)
	{
		dist[i] = INF;
	}
	dist[start] = 0;
	dijkstra();
}
```

