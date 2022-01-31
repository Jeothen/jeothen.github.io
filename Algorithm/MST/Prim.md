---
sort: 1
---

# PRIM

* MST의 대표적인 알고리즘으로 Node 기반으로 동작함
* 최악의 시간 복잡도는 노드 갯수(V) 제곱인 O($$V^2$$)임
* E(edge count)는 항상 $$V^2$$ 보다 작으므로, 우선순위 큐를 사용했을 때 시간 복잡도를 줄일 수 있다.
  * 우선순위 큐에서 edge를 업데이트 하는데 O($$ElogV$$)이며, 방문하지 않은 노드를 우선순위 큐에 업데이트 하는데 O($$VlogV$$)이다
    * 시간 복잡도는 ($$(E+V)logV) 이다.($$E >> V인 경우, O($$ElogV$$))
* 크루스칼은 모든 edge를 우선순위 큐에 push하여 edge 기준으로 동작하지만, prim 알고리즘은 node를 방문할 때마다 해당 노드의 edge를 업데이트 함
* 간선의 수가 많은 Dense Matrix인 경우 크루스칼보다 Prim 알고리즘을 적용하기 적합함



**Code**

```c++
#include <iostream>
#include "string.h"
#include <queue>
using namespace std;

#define INF 1e9
typedef pair<int,pair<int,int>> pp;
const int nodecount = 1001;
int dist[nodecount], start, idx;
vector<pp> vc[nodecount];

int prim(){
	priority_queue<pp, vector<pp>, greater<pp>> pq;
	for (auto& p : vc[start]) pq.push(p);  // start node edge upload
	fill_n(dist,sizeof(dist),INF);
	int ret = 0;
	dist[start] = -1;

	while(!pq.empty()){
		int val = pq.top().first;
		pair<int,int> node = pq.top().second;
		if (dist[node.first] == -1) continue; // already visited
		dist[node.first] = -1; // start visited check
		pq.pop();
		for (auto& p: vc[node.second]) {
			if (dist[p.second.first] != -1) // not visited
				pq.push(p);
		}
		ret += val;
		// if n count break;
	}
	return ret;
}



int square_n(){
	int graph[nodecount][nodecount];
	fill_n(graph, sizeof(graph),INF); // default : not arrived
	// input graph a->b = c
	for (int i=1; i<=nodecount; i++){
        graph[i][i] = 0;
    }    
	int ret = 0;
	for (int i = 1; i <= nodecount; i++)
		dist[i] = graph[start][i]; // if not arrived, INF

	dist[start] = -1; // -1 is visited
	for (int i = 1; i < nodecount; i++) // mst need to find minimum distance from node to node 
	{
		int minimum = INF;
		for (int j = 1; j <= nodecount; j++)
		{
			if (dist[j] != -1) {
				if (minimum > dist[j]) {
					minimum = dist[j];
					idx = j;
				}
			}
		}
		ret += minimum;  // plus minimum distance
		dist[idx] = -1; // idx is visited (minimum distance index)
		for (int j = 1; j <= nodecount; j++) { // update if  idx to j is smaller than original distance to j
			if (dist[j] > graph[idx][j]) dist[j] = graph[idx][j];
		}
	}
	return ret;
}

```



