---
sort: 2
---

# Dijkstra

* source node에서 target node까지 최단 거리를 계산하는 알고리즘
* 시간 복잡도는 O((V+E)logV) - pibonachi heap을 사용하여 priority queue가 작동
  * 시작점에서 방문하지 않은 노드 중 가장 짧은 거리를 계산하는데 O(VlogV)의 시간 복잡도가 필요함 (node : V)
  * 인접 노드의 최단거리 업데이트 시 O(ElogV)의 시간 복잡도가 필요 ( edge : E)
* Dijkstra 알고리즘은 음의 가중치에는 적용할 수 없다. 



**Code**

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

