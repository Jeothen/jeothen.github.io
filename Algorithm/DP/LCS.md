---
sort: 3
---

# LCS (Longest Common Subsequence)



* 최장 공통 부분 수열 (Longest Common Subsequence) or 최장 공통 문자열 (Longest Common Substring)
* 최장 공통 부분 수열은 부분 수열이 연속된 index를 가지지 않아도 됨
* 최장 공통 문자열은 부분 문자열이기 떄문에 연속된 index를 가짐



### Longest Common Subsequence

* 부분 수열은 연속된 값이 아님
* 2개의 문자열을 축으로 2차원 배열 생성
* 연속된 값이 아니기 때문에 문자열이 다르더라도 최대값이 유지됨
* 문자열이 다른 경우 ```max(sub_s1, sub_s2) = max(lcs[i-1][j], lcs[i][j-1])```
  * 최댓값으로 적용하기 위해 두개의 부분 문자 중 큰 값을 취함
* 문자열이 같은 경우 ```lcs[i][j] = lcs[i-1][j-1] + 1``` 
  * 두 개의 문자 중 공통된 부분의 값에서 1을 더함
* 공통 문자열에 접근하기 위해 index 0 는 0으로 set

* 다른 경우 이전 값 중 큰 값으로 적용하기 때문에 행렬의 끝에 있는 값이 결과값임

ex)

|      |      | b     | f     | d     | e     |
| ---- | ---- | ----- | ----- | ----- | ----- |
|      | 0    | 0     | 0     | 0     | 0     |
| b    | 0    | **1** | 1     | 1     | 1     |
| b    | 0    | 1     | 1     | 1     | 1     |
| d    | 0    | 1     | 1     | **2** | 2     |
| e    | 0    | 1     | 1     | 1     | **3** |
| f    | 0    | 1     | **2** | 2     | 3     |



### Code

```c++
#include <iostream>
#include <string>
using namespace std;
#define str_max 5001
string a, b;
int table[str_max][str_max];

int main() {
	cin >> a;
	cin >> b;
	a = '0' + a;
	b = '0' + b;
	int len1, len2;
	len1 = a.length();
	len2 = b.length();
	for (int i = 0; i < len1; i++) table[0][i] = 0;
	int lcslen = 0;
	for (int i = 1; i < len2; i++) {
		table[i][0] = 0;
		int max_len = 0;
		for (int j = 1; j < len1; j++) {
			if (b[i] == a[j]) {
				max_len = table[i - 1][j - 1] + 1;
				table[i][j] = max_len;
			}
			else {
				if (table[i][j - 1] > table[i - 1][j])
					table[i][j] = table[i][j - 1];
				else
					table[i][j] = table[i - 1][j];
			}
		}
		lcslen = lcslen < max_len ? max_len : lcslen;
	}

	string LCS = "";
	int tmp = 1;
	for (int i = 1; i < len1; i++) {
		for (int j = tmp; j < len2; j++) {
			if (table[i][j] == tmp &&  table[i - 1][j] == tmp-1  && table[i][j - 1] == tmp-1 && table[i - 1][j - 1] == tmp-1) { // newly updated
				LCS += a[i];
				tmp++;
				break;
			}
		}
	}
	cout << LCS << endl;
}
```



### Longest Common Substring

* sadsa
* dasdasd

### Code

```c++
```



