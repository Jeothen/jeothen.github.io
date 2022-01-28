---
sort: 4
---

# Edit Distance



* 두개의 문자열을 비교하여 동일한 문자를 만드는데 필요한 삭제/삽입/변경 횟수의 최솟값을 통해 유사도 측정

* direction

  * 문자가 일치할 때 대각선으로 동일한 값 (복사)

  * 값 변경 

    * 수정 / 삭제 / 추가 중 최솟값 + 1 적용

    * 수정 : 우하향 대각선으로 + 1

    * 삭제 : 아래 방향으로 + 1

    * 추가 : 오른쪽 방향으로 + 1

* 첫번째 문자부터 비교해야되기 때문에, 두 문자 앞에 '0' 추가하여 2차원 행렬 생성

* 2차원 행렬의 마지막 지점(2개의 문자열의 마지막 문자끼리 비교)의 값이 편집에 필요한 최소 변경 횟수

* lcs에서는 첫번째 행/열의 값을 0으로 했으나, edit distance에서는 index를 default로 잡는다

  * 0을 기준으로 length만큼 편집이 필요하다는 의미



| 0    | 0    | a    | c    | d    | e     |
| ---- | ---- | ---- | ---- | ---- | ----- |
| 0    | 0    | 1    | 2    | 3    | 4     |
| b    | 1    | 1    | 2    | 3    | 4     |
| c    | 2    | 2    | 1    | 2    | 3     |
| d    | 3    | 3    | 2    | 1    | **2** |



**점화식**

```c++
if (s1[i] == s2[j]) dp[i][j] = dp[i-1][j-1];
else dp[i][j] = min(dp[i-1][j],dp[i][j-1],dp[i-1][j-1]) + 1;
```



### Code

```c++
int editDist(int m, int n)
{
    str1 = '0' + str1; str2 = "0" + str2;
    for (int i=0; i<str1.length();i++) dp[0][i] = i;
    for (int i=0; i<str2.length();i++) dp[i][0] = i;

    for (int i=1;i<str2.length();i++){
        for (int j=1; j<str1.length();j++){
            if (str2[i] == str1[j]) dp[i][j] = dp[i-1][j-1];
            else {
                dp[i][j] = 1+min(dp[i-1][j-1],dp[i][j-1],dp[i-1][j]);
            }
        }
    }
    return dp[str2.length() - 1][str1.length() - 1];
}
```





