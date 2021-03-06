---
sort: 3
---

# LIS (Longest Increasing Subsequence)

* 순차적으로 구성된 배열의 부분집합 중, 이전의 원소보다 큰 조건을 만족하는 최장 증가 부분수열
* 예로 [3,**1**,**2**,1,**6**,4,**8**]가 있는 경우, [1,2,6,8]이 가장 긴 부분 증가수열임
* 2차원 배열 DP를 이용하여 계산할 수 있으며 단순 이차원 배열로 계산할 경우 시간 복잡도는 O($$N^2$$) 이다.

|       | 0    | 1    | 2    | 3    | 4    | 5    | 6    | 7    |
| ----- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
| array | 0    | 3    | 1    | 2    | 1    | 6    | 4    | 8    |
| DP    | 0    | 1    | 1    | 2    | 1    | 3    | 3    | 4    |

```c++
const int n = 8;
int array[n] = {0,3,1,2,1,6,4,8};
int dp[n] = { 0,};
for (int i = 1; i <= n; i++)
{
  for (int j = 0; j < i; j++)
  {
    if (array[j] < array[i])
    {
      dp[i] = max(dp[i], dp[j] + 1);
    }
  }
}
cout << dp[n-1];
```



* LIS알고리즘을 구할 때 Binary Search를 적용하면 시간 복잡도를 O(NlogN)으로 개선할 수 있음



* 처음 값을 dp 배열의 인덱스0에 넣음
* 마지막 값보다 작은 값이 오면 이분 탐색으로 들어갈 자리를 찾음
  * 새로 추가되는 값보다 작은값들 중 가장 큰 값 뒤의 메모리에 업데이트 
* 이전 값보다 큰 값이 오면 dp 배열에 추가

| Times | 3    | 1    | 2    | 1    | 6    | 4    | 8    |
| ----- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
| 1(3)  | 3    |      |      |      |      |      |      |
| 2(1)  | 1    |      |      |      |      |      |      |
| 3(2)  | 1    | 2    |      |      |      |      |      |
| 4(1)  | 1    | 2    |      |      |      |      |      |
| 5(6)  | 1    | 2    | 6    |      |      |      |      |
| 6(4)  | 1    | 2    | 4    |      |      |      |      |
| 7(8)  | 1    | 2    | 4    | 8    |      |      |      |



**Code**



```c++
#include <iostream>
#include <vector>
using namespace std;

vector<int> arr;
vector<int> lis;

int binary_search(int left, int right, int value)
{
	while (left < right)
	{
		int mid = (left + right) >> 1;
		if (lis[mid] < value) left = mid + 1;
		else right = mid;
	}
	return left;
}

int make_lis(int n){ // size of array
	lis[0] = arr[0]; // initial
	int i = 1, res = 0;
	while (i < n)
	{
		if (lis[res] < arr[i]) lis[++res] = arr[i];
		else
		{
			int idx = binary_search(0, res, arr[i]); // from 0 to i
			lis[idx] = arr[i];
		}
		i += 1;
	}
	return res+1;
}
```



```c++
lis.push_back(0);
for (int i = 0; i < n; i++) {
  if (lis.back() < arr[i]) lis.push_back(arr[i]);
  else {
    auto it = lower_bound(lis.begin(), lis.end(), arr[i]);
    *it = arr[i];
  }
}
```

