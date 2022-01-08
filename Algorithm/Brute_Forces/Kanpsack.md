---
sort: 1
---

# Knapsack

* Using DP
* 가방에 있는 물건 무게와 Value가 제공
* 2차원 배열을 생성 - y : 가방의 갯수 / x : 모든 배낭에 넣을 수 있는 최대 무게 (Max Weight)
* x축에서 현재 가방의 무게보다 클 때 넣을 수 있는 최대 양을 기입



In Case

|        | 1    | 2                                     | 3                                      |
| ------ | ---- | ------------------------------------- | -------------------------------------- |
| Weight | 3    | 2                                     | 6                                      |
| Value  | 30   | **<span style="color:red">15</span>** | **<span style="color:blue">20</span>** |

* BAG COUNT = 3, MAX_Weight = 10



DP

| i / j | 0    | 1    | 2    | 3                                      |      | 4    | 5                                     |      | 6    | 7    | 8    | 9                                      | 10   |
| ----- | ---- | ---- | ---- | -------------------------------------- | ---- | ---- | ------------------------------------- | ---- | ---- | ---- | ---- | -------------------------------------- | ---- |
| 1     | 0    | 0    | 0    | **<span style="color:red">15</span>**  |      | 30   | 30                                    |      | 30   | 30   | 30   | 30                                     | 30   |
| 2     | 0    | 0    | 15   | **<span style="color:blue">30</span>** |      | 30   | **<span style="color:red">45</span>** |      | 45   | 45   | 45   | 45                                     | 30   |
| 3     | 0    | 0    | 15   | 30                                     |      | 30   | 45                                    |      | 45   | 45   | 45   | **<span style="color:blue">50</span>** | 50   |



점화식 

```c++
if (w[i] <= j ) dp[i][j] = max(v[i] + dp[i-1][j-w[i]], dp[i-1][j])
if (w[i] > j) dp[i][j] = dp[i-1][j]
  
return dp[BAG_CNT][MAX_WEIGHT]
```



### Code

```c++
#include <iostream>
#define MAX_CNT 10
#define MAX_WEIGHT 1000

int dp[MAX_CNT+1][MAX_WEIGHT+1];

int kanpsack(int* C,int* W)
{	
	for (int i=1; i<=MAX_CNT; i++)
	{
		for (int j=1; j<=MAX_WEIGHT; j++)
		{
			if (j >= W[i]) dp[i][j] = std::max(dp[i-1][j], dp[i-1][j-W[i]] + C[i]);
			else dp[i][j] = dp[i-1][j];
		}
	}
	return dp[MAX_CNT][MAX_WEIGHT];
}

int main()
{
	int C[MAX_CNT], W[MAX_CNT]; // capacity, weight

	std::cout << kanpsack(C,W);
}
```
