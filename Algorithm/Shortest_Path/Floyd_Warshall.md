---
sort: 4
---

# Floyd Warshall

* 모든 노드에서 다른 모든 노드까지의 DP로 최단 거리 찾기
* 모든 노드에서 다른 노드까지의 거리와 해당 노드를 통과하는 거리를 확인해야되니 O($$N^3$$) 의 시간 복잡도를 가진다.



**Code**

```c++
#include <iostream>
#Include <vector>
#include <algorithm>
using namespace std;
#define nodecount 100
#define INF 1e9
int dist[nodecount][nodecount];

void floyd_warshall(){
    // init dist
    fill_n(dist,dist+nodecount*nodecount; INF);
    
    for (int i=0; i<nodecount; i++){
        for (int j=0; j<nodecount; j++){
            if (i==j) dist[i][j] = 0;
            else {
                int a, b, c; cin >> a >> b >> c;
				        dist[a][b] = min(dist[a][b],c);
                // If Bidirectional,  j = i; j<nodecount; j++ ;    dist[a][b] = dist[b][a] = c;
            }
        }
    }
    for (int i=0; i<nodecount; i++){ // through node
        for (int src=0; src<nodecount; src++){ // source
            for (int tgt=0; tgt < nodecount; tgt++){ // target
                dist[src][tgt] = min(dist[src][i] + dist[i][tgt], dist[src][tgt]);
            }
        }
    }
}
```

