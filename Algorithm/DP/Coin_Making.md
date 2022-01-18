---
sort: 2
---

# Coin Making Problem

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



### Code

```c++
#define MAX_NUM 1001
#define Coin_cnt 101
int dp[MAX_NUM];
int coins[Coin_cnt];

void coin_change(){
	  
}
```

