---
sort: 1
---

# BFS

**Breath First Search**

* 정점으로부터 가까운 노드를 방문하고 멀리 떨어진 노드를 방문하는 방법
* FIFO방식으로 동작하기 때문에 Queue를 이용함

* 노드를 방문할 때마다 Queue에 넣고, 이미 방문한 노드는 skip한다
* Queue가 빌 때까지 while문을 돌면서 방문할 수 있는 모든 노드를 탐색

**인접 행렬 / 리스트**

인접 행렬

```c++
for (int i=0; i<V ;i++)}{
	if (graph[now][i] && !visit[i]){
	
	}
}
```

* 인접 행렬로 계산시 모든 노드를 탐색하기 때문에 시간 복잡도는 O($$V^2$$)이 됨
  * queue에 모든 노드를 넣기 때문에 O(V), 각 노드에서 모든 노드를 탐색할 때 O(V)

인접리스트

```c++
for (int i=0; i< graph[now].size();i++)}{
	int next = graph[now][i]
  if (!visit[next]){
	}
}
```

* 인접 리스트로 계산시 시간 복잡도는 O(V+E)
  * queue에 모든 노드를 넣기 때문에 O(V), 각 노드에서 연결된 edge를 찾기 때문에 O(E)

**Code**

```c++
void BFS(int start){
  queue<int>q;
  vector<bool>visit(n,0);
  q.push(start);
  while(!q.empty()){
    int now = q.top(); q.pop();
    for (int i=0;i<graph[now].size();i++){
      int next = graph[now][i];
      if (!visit[next]){
        visit[next] = true;
        q.push(next);
      }
    }
  }
}
```



