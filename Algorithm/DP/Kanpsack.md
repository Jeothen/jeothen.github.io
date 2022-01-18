---
sort: 1
---

# Knapsack

* 배낭에 담을 수 있는 무게의 최대값이 정해져있고, 각 물건의 무게와 가치가 주어질 때 배낭에 담을 수 있는 최대 가치를 구하는 문제
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



### Knapsack Code

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







# Coin Change

* Kanpsack 알고리즘을 이용한 알고리즘
* 동전의 종류의 금액이 주어졌을 때, 특정 금액을 만들기 위한 동전의 최소 갯수를 구하는 문제

* 예로들어, target : 9원 / source : 2원,3원,5원인 경우

  Rules of coin change

```
1. first step
2원 + 7원
3원 + 6원
5원 + 4원

2. second step (recursive or 2차원 loop)
[7,6,4]원을 만드는 데 필요한 최소 갯수
```

* 1차원 배열로 표현
  * 4원인 경우 (4-2 / 4-3 / 4-5) 를 수행하여 유효한 값인 경우, 그 배열의 값을 더한다.
    * 즉, 6원인 경우 (6-2 / 6-3 / 6-5) 를 수행하여 유효한 최솟값 + 1을 가져옴 

| 1원  | 2원  | 3원  | 4원   | 5원  | 6원   | 7원  | 8원  | 9원  |
| ---- | ---- | ---- | ----- | ---- | :---- | ---- | ---- | ---- |
| -1   | 1    | 1    | 2=1+1 | 1    | 1+1=2 | 1+1  | 1+1  | 2+1  |



#### Coin Change Code

```c++
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int INF = 100'000'000;

int coin_change(vector<int> coins, int value)
{
    vector<int>dp(value+1,0);
    int coin_cnt = coins.size();

    for (int i=1; i<=value;i++){
        int minimum = INF;
        for (int j = 0; j < coin_cnt; j++) {            
            if (i >= coins[j]) {
                minimum = min(minimum, 1 + dp[i-coins[j]]);
            }
        }
        dp[i] = minimum;
    }
    cout << endl;
    return dp[value];
}

int main()
{
    vector<int> coins = {2, 3, 5};
    cout << coin_change(coins,9); // res = 9
}
```

