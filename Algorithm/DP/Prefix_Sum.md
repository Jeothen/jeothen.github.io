---
sort: 1
---

# Prefix Sum

* DP로 동작하며 특정 구간의 합을 계산할 때 용이하게 사용할 수 있음

* Array에 저장되는 값은 인덱스 0부터의 합이므로, 끝구간과 시작 구간에 저장된 값을 빼면 특정 구간에서의 부분합을 계산할 수 있음

* 2차원 행렬에서도 특정 구간의 사각행렬 내 합을 계산할 수 있음

  * (start_x,start_y)에서 (end_x,end_y) 구간의 합이 필요한 경우

  `dp[end_x,end_y] + dp[start_x,start_y] - (dp[starx,end_y] + dp[end_x,start_y]`

<br/>

**Code**

```c++
#include <iostream>
using namespace std;
const int N = 10001;
int psum[N];

void prefix_sum(){
	int n = 20;
	for (int i=0; i<n; i++){
		int val = 2; // scanf or cin
		psum[i+1] = psum[i] + val;  // psum[3] = summary from 0 to 2
	}
	for (int i=1; i<=n; i++){
		cout << psum[n] - psum[i-1] << endl; 
		// i == 1, 0 to n
		// i == 2, 1 to n
		// i == n, n-1 to n
	}
}
```



