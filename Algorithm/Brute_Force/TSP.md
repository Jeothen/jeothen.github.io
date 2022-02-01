---
sort: 3
---

# TSP

* 시작점에서 모든 경로에 대한 최소 비용을 찾는 NP(non-deterministic Polynomial)
  * 모든 경로는 1번씩만 방문하며 마지막에 시작점으로 돌아오는 구조
* TSP 문제는 기본적으로 방문 가능한 경로인 모든 순의 시간 복잡도는 O($$n!$$) 을 갖는다.
* bitmasking을 이용하면 시간 복잡도가 O($$2^n$$)으로 줄어든다
* 시간 복잡도를 더 줄이기 위해 DP와 bit-masking을 이용할 수 있다.



**parameter**

* cur : 현재 노드의 위치를 나타냄
* Visit : 방문한 도시의 합을 나타냄 
  * ex) visit = 5인 경우,  0000101로 1과 3을 방문

<br/>

**Code**

```c++
#include <iostream>
using namespace std;
#pragma warning(disable:4996)
#define INF 1e9;
#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))

char lists[17];
int n, cnt, dist[17][17], dp[17][1 << 16];

int TSP(int cur, int visit)
{
	if (visit == (1 << n) - 1) // all city visit
	{
		return dist[cur][0] ? dist[cur][0] : INF;
	}
	int& ret = dp[cur][visit]; // reference
	if (ret != -1) return ret; // already visit  cur -> visit 

	ret = INF;
	for (int next = 0; next < n; next++)
	{
		if (visit & (1 << next)) continue; // visit next city
		if (dist[cur][next] == 0) continue;	// not destinated
		ret = MIN(ret, dist[cur][next] + TSP(next, visit | (1 << next))); // current->next + tsp(start next)
	}
	return ret;	// minimum of current to visit
}

void Solve(){
	memset(dp, -1, sizeof(dp)); // 4*17*2^16
	printf("%d\n", TSP(0, 1));	// if INF, Not TSP;
}
```



