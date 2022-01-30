---
sort: 3
---

# LCS



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
| e    | 0    | 1     | 1     | 2     | **3** |
| f    | 0    | 1     | **2** | 2     | 3     |

* 경로추적
  * 마지막 노드에서 bottom-up 방식으로 찾음
  * 마지막 노드에서 왼쪽과 윗쪽을 보면서 같은 수가 있으면 index 이동
  * 같은 수가 없으면 stack에 index를 저장하고 대각선으로 이동 

**점화식**

```c++
	for (int i = 1; i < len1; i++) {
		for (int j = 1; j < len2; j++) {
			if (s1[i] == s2[j]) lcs[i][j] = lcs[i - 1][j - 1] + 1;
			else lcs[i][j] = max(lcs[i-1][j], lcs[i][j-1]);
		}
	}
```



**Code**

```c++
#include <iostream>
#include <algorithm>
#include <string>
#include <stack>
#define MAX_NODE 501
using namespace std;

int lcs[MAX_NODE][MAX_NODE];

int main()
{
	
	string s1, s2;
	cin >> s1 >> s2;

	s1 = '0' + s1;
	s2 = '0' + s2;

	int len1 = s1.size();
	int len2 = s2.size();
	for (int i = 0; i < len1; i++) lcs[i][0] = 0;
	for (int i = 0; i < len2; i++) lcs[0][i] = 0;

	for (int i = 1; i < len1; i++) {
		for (int j = 1; j < len2; j++) {
			if (s1[i] == s2[j]) lcs[i][j] = lcs[i - 1][j - 1] + 1;
			else lcs[i][j] = max(lcs[i-1][j], lcs[i][j-1]);
		}
	}

	cout << "LCS LENGTH IS " << lcs[len1 - 1][len2 - 1] << endl;

	int i = len1 - 1;
	int j = len2 - 1;
	stack<int> st; // FROM LAST NODE

	while (lcs[i][j] != 0)
	{
		if (lcs[i][j] == lcs[i][j - 1]) j--;
		else if (lcs[i][j] == lcs[i - 1][j]) i--;
		else if (lcs[i][j] - 1 == lcs[i - 1][j - 1])
		{
			st.push(i);
			i--; j--;
		}
	}
	while (!st.empty())
	{
		cout << s1[st.top()];
		st.pop();
	}
}
```



### Longest Common Substring

* Longeset Common Subsequence와 비슷한 내용이지만, 연속되지 않은 부분문자를 포함한다.
* Longest Common Subsequence에서는 연속하지 않은 부분 수열을 포함하기 때문에 ``max(lcs[i-1][j], lcs[i][j-1])``을 적용했지만, Substring에서는 0으로 대체한다
* Trace할 때도, 최대값이 나온 자리에서 대각선으로 이동하며 stack에 쌓으면 된다.

**점화식**

```c++
	for (int i = 1; i < len1; i++) {
		for (int j = 1; j < len2; j++) {
			if (s1[i] == s2[j]) lcs[i][j] = lcs[i - 1][j - 1] + 1;
			else lcs[i][j] = 0;
		}
	}
```



**Code**

```c++
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <stack>
#define MAX_NODE 501
using namespace std;

int lcs[MAX_NODE][MAX_NODE];

int main()
{
	
	string s1, s2;
	cin >> s1 >> s2;

	s1 = '0' + s1;
	s2 = '0' + s2;

	int len1 = s1.size();
	int len2 = s2.size();
	for (int i = 0; i < len1; i++) lcs[i][0] = 0;
	for (int i = 0; i < len2; i++) lcs[0][i] = 0;

	int max_length = 0;

	for (int i = 1; i < len1; i++) {
		for (int j = 1; j < len2; j++) {
			if (s1[i] == s2[j]) lcs[i][j] = lcs[i - 1][j - 1] + 1;
			else lcs[i][j] = 0;
			max_length = max(max_length, lcs[i][j]);
		}
	}
	cout << "LCS LENGTH IS " << max_length << endl;

	vector<pair<int, int>> vc;
	for (int i=1; i<len1;i++){
		for (int j=1; j< len2; j++){
			if (lcs[i][j] == max_length) vc.push_back({i,j});
		}
	}
	for (auto it : vc){
		for (int i=it.first-max_length; i < it.first ; i++){
			cout << s1[i];
		}
		cout << endl;
	}
}
```



