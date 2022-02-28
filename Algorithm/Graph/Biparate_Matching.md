---
sort: 2
---

# Biparate Matching



* 정점의 갯수가 같은 2개의 그룹을 1:1로 매칭
* B 그룹에서 매칭되어 있지 않거나 다른 A 정점과 매칭시킬 수 있을 때, 재귀를 통해 최대로 연결
  * B그룹에 매칭이 안 된 노드를 선택
    * Visited -1 초기화
  * 노드와 연결된 A그룹 정점에서 연결이 안되어 있거나 (A[a] == -1),  (A[a]가 방문이 안되고 재귀에서 다른 node와 매칭 시켰을 때)  1:1 매칭





**Code**

```c++
#include <iostream>
#include <vector>
#include <string.h>
#define MAX_NODE 1001
int N,M;

std::vector<int> adj[MAX_NODE];
int A[MAX_NODE], B[MAX_NODE];
bool visited[MAX_NODE];

bool dfs(int b)
{
    visited[b] = true;
    for (int a : adj[b])
    {
        if (A[a] == -1 || (!visited[A[a]] && dfs(A[a])))
        {
            B[b] = a;
            A[a] = b;
            return true;
        } 
    }
    return false;
}

int biparate_matching(int n)
{
    memset(A, -1, sizeof(A));
    memset(B, -1, sizeof(B));
    int res = 0;
    for (int i=1; i <= n; i++)
    {
        if (B[i] == -1) // not visit
        {
            memset(visited, false,sizeof(visited));
            if (dfs(i)) res++; // success matching
        }
    }
    return res;
}

int main()
{
    biparate_matching(N);
}

```

