---
sort: 2
---

# DFS

**Depth First Search**

* 하나의 정점을 최대한 깊이 탐색하고, 더 이상 탐색할 수 없을 때 다음 경로를 탐색하는 기법
* LIFO방식으로 동작하기 때문에 Stack를 이용함
* Stack에 이전 경로에 대한 값을 넣어서 구하는 방식과 재귀로 문제를 해결하는 방법이 있음
  * Stack을 이용하는 경우, BFS와 비슷한 방법으로 Stack이 빌 때까지 while문으로 모든 노드를 탐색
  * 재귀로 접근하는 경우, Parameter에 이전 값에 대한 정보를 추가 (전역으로 설정할 경우, 재귀 전후로 변경점에 대한 내용 추가 필요)


<br/>

**인접 행렬**

```c++
for (int i=0; i<V ;i++)}{
	if (graph[now][i] && !visit[i]){
	
	}
}
```

* 인접 행렬로 계산시 모든 노드를 탐색하기 때문에 시간 복잡도는 O($$V^2$$)이 됨
  * Stack(or recursive)에 모든 노드를 넣기 때문에 O(V), 각 노드에서 모든 노드를 탐색할 때 O(V)

**인접리스트**

```c++
for (int i=0; i< graph[now].size();i++)}{
	int next = graph[now][i]
  if (!visit[next]){
	}
}
```

* 인접 리스트로 계산시 시간 복잡도는 O(V+E)
  * Stack(or recursive)에 모든 노드를 넣기 때문에 O(V), 각 노드에서 연결된 edge를 찾기 때문에 O(E)

**Code**

```c++
void DFS(int start, bool visited[]){
  visited[start] = true;
  for (int i=0;i<graph[start].size();i++){
    int next = graph[start][i];
    if (!visited[next]){
      DFS(next,visited);
    }
  }
}
```


