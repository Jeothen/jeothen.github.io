---
sort: 1
---

# Palindrome

* 문자열을 앞으로 읽으나 뒤로 읽으나 동일한 문자열을 회문(Palindrome)이라고 함
  * `abcdcba` 같은 문자열을 보면 왼쪽에서 오른쪽으로 읽은 값과, 오른쪽에서 왼쪽으로 읽은 값이 동일

* 문자열이 Palindrome인지 확인하는데 시간복잡도는 $$O(N)$$ 이 발생

**Code**

```c++
bool is_palindrome(string txt){
    int length = txt.length();
    int left = 0, right = length-1;
    while ((right-left) > 1){
        if (txt[left] != txt[right]) return false;
        left++; right--;
    }
    return true;
}
```

### Manacher's Algorithm

* 문자열의 특정 문자를 기준으로 좌우가 동일한 가장 길이가 긴 Palindrome을 찾는 알고리즘
  * 특정 문자를 기준으로 Palindrome을 찾기 때문에 홀수개의 부분 문자열만 확인
* 홀수개의 부분 문자열만 찾는 이슈를 해결하기 위해 짝수개를 찾을 때는 문자 사이에 특수 문자를 대입하여 문자열 생성
  * 예를 들어 `zabbay` 라는 문자열이 있는 경우, `#` 을 추가했을 때
  * `#z#a#b#b#a#y#` 이라는 문자열을 생성하면 홀수개의 문자열이 됨
    * `#`을 기준으로 palindrome을 찾으면 짝수개의 부분 문자열의 palindrome을 확인할 수 있음
    * 문자를 기준으로 할 때는 홀수개의 palindrome을 확인
    * 가장 앞과 뒤에 특수 문자를 추가하지 않으면 마지막과 첫번째에 문자를 포함하는 palindrome을 위해 중간의 값 반영분을 추가해야 됨
      * ex) `abba` 라는 문자열인  경우, `a#b#b#a` 라는 문자열은 중간의 `#` 에서 palindrome을 계산시 3 (실제로는 4)
      * ex) `abcba` 라는 문자열인 경우, `a#b#c#b#a`라는 문자열은 중간의 `c`에서 palindrome을 계산시 4 (실제로는 5)

* 아래 Code에서 `init` 함수를 통해 문자열에 특수문자 추가

```c++
string init(string str){
    int n = str.size();
    str += str.substr(0); // first - last is not #
    for (int i = n - 1; i>=0; i--)
    {
        str[(i<<1)+1] = str[i];
        str[(i<<1)] = '#';
    }
    str += '#';
    return str;
}
```

* Manacher 함수

  *  m은 부분 문자열의 중앙 index이고, r은 부분 문자열의 가장 오른쪽 index, dp[i]는 i번째 palindrome의 반경

     *  r은 중심 m을 기준으로 하는 반경으로,  `r=m+dp[m]` 으로 대체 가능

  *  `i<=r` 을 만족하는 경우는 i가 반경 r에 포함되는 경우를 의미

     *  포함되지 않으면 `dp[i] = 0`
     *  회문에서 중심 `m` 을 기준으로 i의 대칭은 `m - (i-m) = 2*m-i` 이므로, 이전에 계산된 대칭점과 동일한 반경에서 비교를 시작할 수 있음
        *  `dp[2*m-i]` 
        *  반경은 `r-m` 이고, 회문을 만족하는 `dp[2*m-i]` 를 제외한 나머지 부분 `r-i` 에 대해서도 회문을 만족
        *  두가지 경우 회문을 만족하기 때문에, minimum 값에서 비교를 시작해야 됨. `dp[i] = min(r-i, dp[2*m-i])`
     *  `i + dp[i] > r` 은 이전에 발생했던 회문의 반경 `r` 보다 큰 경우, 중앙의 위치 및 r 값을 Update
     *  예를 들어 아래와 같은 문자가 있는 경우
        *  `#` 을 제외하고 문자만 적었을 때, m을 기준으로 반경은 7이고 `cbcdcbc` 가 회문을 만족
        *  `dp[2*m-i]` 는 `dcbcd` 라는 회문을 만족하기 때문에 a에서 시작해야 되고, $$r-i$$ = 1 이기 떄문에 반경+1 이후부터 비교 시작

     |        |      |      |      |       | r     | $$2*m-i$$ |       | $$m$$ |      | i    | r    | $$dp[2*m-i]$$ |      |      |      |
     | ------ | ---- | ---- | ---- | ----- | ----- | --------- | ----- | ----- | ---- | ---- | ---- | ------------- | ---- | ---- | ---- |
     |        |      | a    | d    | **d** | **c** | **b**     | **c** | **d** | c    | b    | c    | a             | a    |      |      |
     | Radius |      |      |      |       |       | 2         |       | 3     |      | ?    |      | 2             |      |      |      |

     * 대칭점의 회문이 중앙 회문에 포함되는 경우에는 $$ r-i$$ 는 k 이후부터 비교를 시작하고, `dp[2*m-i]` 는 b부터 비교를 시작
     * 매칭이 안 된 작은 값부터 비교를 시작해야 되기 때문에, b 이후부터 시작해야되는데 `dp[i] = min(r-i, dp[2*m-i])`.  b 이후부터 비교

     |        |      | r    |      |       | $$2*m-i$$ |       |      | $$m$$ |      |      | i    | $$dp[2*m-i]$$ |      | r    |      |
     | ------ | ---- | ---- | ---- | ----- | --------- | ----- | ---- | ----- | ---- | ---- | ---- | ------------- | ---- | ---- | ---- |
     |        |      | k    | a    | **b** | **c**     | **b** | c    | d     | c    | b    | c    | b             | a    | k    |      |
     | radius |      |      |      |       | 1         |       |      | 6     |      |      | ?    | 1             |      |      |      |

* ` i + dp[i] ` 가 기존의 반경보다 값이 큰 경우, 중앙 위치와 반경을 업데이트
  * 비교의 중심이 되는 위치를 우측으로 지속적으로 이동

```c++
int dp[MAXN];
int manacher(string str)
{
    str = init(str);
    int n = str.length();
    int m = 0, r = 0, res = 0;
    for (int i = 1; i < n; i++)
    {
        if (i <= r)
            dp[i] = min(r - i, dp[2 * m - i]);
        while (i - dp[i] - 1 >= 0 && i + dp[i] + 1 < n && str[i - dp[i] - 1] == str[i + dp[i] + 1])
            dp[i]++;
        if (i + dp[i] > r)
            m = i, r = i + dp[i];
        res = max(res, dp[i]);
    }
    return res;
}
```

* 아래와 같이 변수 r을 `m+dp[m]` 로 대체 가능 (중심점 + 반경)
  * `m = i `와   `r = i + dp[i]` 를 동시에 대입하였으니, `r = m + dp[m]` 로 사용 가능
* 위의 function에서 `if (i <= r) dp[i] =  min(r-i, dp[2*m-i]`  / `else dp[i] = 0` 
  * `if (i<=r)` 이 아닌데 `min(r-i, dp[2*m-i]` 를 적용한 경우 처음 나오는 문자에서 0보다 작은 값이 나올 수 있음
    * 이전에 발생한 회문의 반경 r에 i가 포함되지 않는 경우, i가 r보다 큰 값이 발생
    * 코드 간결하게 작성하기 위해  `dp[i] = max(0, min(r-i, dp[2*m-i]))` 로 변경
  * `r = p+dp[p]` 로 적용했기 때문에, `dp[i] = max(0, min(m+dp[m]-i, dp[2*m-i]))` 로 적용

```c++
int dp[MAXN];
int manacher(string str)
{
    str = init(str);
    int n = str.length();
    int m = 0, res = 0;
    for (int i = 1; i < n; i++)
    {
        dp[i] = max(0, min(m + dp[m] - i, dp[2 * m - i]));
        while (i - dp[i] - 1 >= 0 && i + dp[i] + 1 < n && str[i - dp[i] - 1] == str[i + dp[i] + 1])
            dp[i]++;
        if (i + dp[i] > m + dp[m])
            m = i;
        res = max(res, dp[i]);
    }
    return res;
}
```



**Code**

```c++
const int MAXN = 200001;

string init(string str){
    int n = str.size();
    str += str.substr(0); // first - last is not #
    for (int i = n - 1; i>=0; i--)
    {
        str[(i<<1)+1] = str[i];
        str[(i<<1)] = '#';
    }
    str += '#';
    return str;
}

int dp[MAXN];
int manacher(string str)
{
    str = init(str);
    int n = str.length();
    int p = 0, res = 0;
    for (int i = 1; i < n; i++)
    {
        dp[i] = max(0, min(p + dp[p] - i, dp[2 * p - i]));
        while (i - dp[i] - 1 >= 0 && i + dp[i] + 1 < n && str[i - dp[i] - 1] == str[i + dp[i] + 1])
            dp[i]++;
        if (i + dp[i] > p + dp[p]) p = i;
        res = max(res, dp[i]);
    }
    return res;
}
```

