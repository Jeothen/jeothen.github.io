---
sort: 1
---

# Shortest Paths

* 최단 경로 문제는 한 노드에서 다른 노드로 갈 때, 최소의 가중치를 갖는 경로를 찾는 알고리즘이다.

* 방향성 / 가중치 / cycle을 갖는 그래프의 최단경로 알고리즘 종류

  * 단일 source / 단일 target : [A*](https://jeothen.github.io/Algorithm/Shortest_Path/A_Star.html)
  * 단일 source / 다수 target : [dijkstra](https://jeothen.github.io/Algorithm/Shortest_Path/Dijkstra.html), [bellman-ford](https://jeothen.github.io/Algorithm/Shortest_Path/Bellman_Ford.html)
  * 모든 source / 다수 target : [Floyd-warshall](https://jeothen.github.io/Algorithm/Shortest_Path/Floyd_Warshall.html)

  * cycle이 아닌 경우 : [DAG](https://jeothen.github.io/Algorithm/Shortest_Path/DAG.html)



<br/>

**Algorithm List**

{% include list.liquid all=true %}

