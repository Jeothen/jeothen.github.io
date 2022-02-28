---
sort: 4
---

# Strongly Connected component

* 하나의 정점에서 동일한 SCC 내에 있는 정점으로 이동할 수 있다 
  * 직/간접적인 경로 존재



### 타잔 알고리즘

* Robert Tarjan이 개발한 알고리즘으로, DFS와 Stack을 이용
* 방문을 안했으면 정방향 간선, 이미 방문을 했으면 역방향 간선으로 구분
* dfsn[]으로 정점번호 저장 / visited 체크



* 모든 노드를 DFS로 탐색하면서 Stack에 담음
  * 노드/자식의 노드에서 조상 노드로 돌아갈 수 없을 때 SCC 생성
  * SCC가 생성되면 Stack에서 제거
  * Stack이 비게 되면 SCC 생성이 완료됨
* DFS
  * 자신의 node / 자식의 node 중 가장 작은 번호의 node 추출
  * 자기자신이 가장 작은 node인 경우, 되돌아갈 node가 없으니 SCC 추출
* 모든 정점과 간선에 한번씩 접근하기 때문에 시간복잡도는 O(V+E)







**Code**

```c++
#include <iostream>
#include <vector>
#include <stack>
using namespace std;
#define NODE 4


int cnt, dfsn[NODE];
bool extract[NODE];
vector <int> adj[NODE];
vector<vector<int>> SCC;
stack<int> s;

int min(const int& a, const int& b)
{
    return a > b ? b : a;
}

int dfs(int cur)
{
    dfsn[cur] =  ++cnt; // count to node
    s.push(cur);
    int res = dfsn[cur];

    for (auto next : adj[cur])
    {
        if (!dfsn[next]) res = min(res, dfs(next));
        else if (!extract[next]) res = min(res, dfsn[next]);
    }

    if (res == dfsn[cur]) 
    {
        vector<int> tmpscc;
        while(1)
        {
            int val = s.top(); s.pop();
            tmpscc.push_back(val);
            extract[val] = true;
            if (val == cur) break;
        }
        sort(tmpscc.begin(), tmpscc.end());
        SCC.push_back(tmpscc);
    }
    return res;
}

void CreateSCC()
{
    // Create CSS by using DFS
    for (int i=0; i<NODE; i++)
    {
        if (!dfsn[i])
        {
            dfs(i);
        }
    }
}

int main()
{
    cnt = 0;
    adj[1].push_back(2);
    adj[3].push_back(2);
    adj[0].push_back(1);
    adj[2].push_back(0);
    CreateSCC();

    for (auto& tmpscc : SCC)
    {
        for (auto val : tmpscc)
        {
            cout << val << " ";
        }
        cout << endl;
    }
}

```

