---
sort: 2
---

# Bellman Ford

* 단일 소스의 최단거리를 찾는 알고리즘 중 하나
* 시간 복잡도 측면에서 dijkstra보다 오래 걸리지만, 음의 가중치도 계산할 수 있음



* 경로를 찾는 과정에서 dist는 최대 n-1번 (max node 수) 업데이트 됨

  * 노드 방문 순서에 따라 업데이트 순서가 변경되기 때문에, 첫번째 노드를 제외하고 n-1번 루프를 거치면 업데이트가 완료

* cycle이 발생하는 경우 n번째 루프에서도 최단거리가 업데이트가 됨

* 시간 복잡도는 O(VE),    V : node 갯수 / E : edge 갯수

  

* 아래의 예시는 노드가 3개인 경우, 2번의 루프가 필요(max loop cnt : node cnt - 1)

![bellman_ford](./img/bellman_ford.JPG)





### Code

```c++
#include <iostream>
#include <vector>
using namespace std;
#define INF 1'000'000'000
#define NODE 10000

struct Edge {
    int src;
    int dest;
    int weight;
};

vector <Edge> edges;
int dist[NODE];
int nodecount, edgecount;

void init(int src)
{
    for (int i = 1; i <= nodecount; i++) dist[i] = INF;
    dist[src] = 0;
}

void bellman_ford(int src) {
    bool cycle = false;
    // opeation
    for (int i=1; i <= nodecount; i++) {
        for (int j=1; j <= edgecount; j++) {
            if (dist[edges[j].src] != INF && dist[edges[j].dest] > dist[edges[j].src] + edges[j].weight) {
                dist[edges[j].dest] = dist[edges[j].src] + edges[j].weight;
                if (i == nodecount) cycle = true; // if update n count
            }
        }
    }
    if (cycle) return;
    for (int i=2; i <= nodecount ; i++) printf("%d ",dist[i] != INF ? dist[i] : -1);
}
```



