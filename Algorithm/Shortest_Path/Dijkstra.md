---
sort: 1
---

# Dijkstra

* source node에서 target node까지 최단 거리를 계산하는 알고리즘
* 시간 복잡도는 O((V+E)logV) - pibonachi heap을 사용하여 priority queue가 작동
  * 각 노드의 경우, 시작점에서 방문하지 않은 노드 중 가장 짧은 거리를 계산하는데 O(VlogV)의 시간 복잡도가 필요하다
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

