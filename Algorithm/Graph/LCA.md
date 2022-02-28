---
sort: 3
---

### LCA

* 





**Code**

```c++
#include <vector>
#include <iostream>
#define MAX 18 // 2^17 > 100000
#define N 100001
using namespace std;

int n, m, d;
int depth[N];
int parent[N][MAX];

vector<int> vc[N];

void dfs(int now, int cnt)
{
    depth[now] = cnt++;
  	for (int i = 1; i <= d; i++)
    {
        parent[now][i] = parent[parent[now][i - 1]][i - 1];
    }
    for (int i = 0; i < vc[now].size(); i++)
    {
        int next = vc[now][i];
        if (!depth[next])
        {
            parent[next][0] = now;
            dfs(next, cnt);
        }
    }
}

int main()
{
    scanf("%d", &n);
    for (d = 1; (1 << d) <= n; d++)
    for (int i = 1; i < n; i++)
    {
        int a, b;
        scanf("%d %d", &a, &b);
        vc[a].push_back(b);
        vc[b].push_back(a);
    }
    dfs(1, 1);
    scanf("%d", &m);
    for (int i = 0; i < m; i++)
    {
        int a, b;
        scanf("%d %d", &a, &b);
        if (depth[a] < depth[b])
            swap(a, b);
        for (int j = d; j >= 0; j--)
        {
            if (depth[b] <= depth[parent[a][j]])
            {
                a = parent[a][j];
            }
        }
        if (a == b)
        {
            printf("%d\n", a);
            continue;
        }
        for (int j = d; j >= 0; j--)
        {
            if (parent[a][j] != parent[b][j])
            {
                a = parent[a][j];
                b = parent[b][j];
            }
        }
        a = parent[a][0];
        printf("%d\n", a);
    }
}
