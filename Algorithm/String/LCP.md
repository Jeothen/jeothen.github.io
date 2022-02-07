---
sort: 2
---

# LCP

* LCP (Longest Common Prefix)는 하나의 문자열이 주어졌을 때 접미사의 공통 접두사의 최대길이임
* LCP를 구하기 위해서는 사전에 Suffix Array를 만들어 놓아야 함

  * 최대 길이가 공통인 부분을 찾아야 하기 때문에 사전으로 정렬했을 때 찾을 수 있다.
* 바로 이전의 suffix array와 공통으로 포함하는 suffix의 길이를 찾으면 된다.
* ABAABA라는 문자열의 suffix array는 [[5,2,3,0,4,1]](https://jeothen.github.io/Algorithm/String/Suffix_Array.html)이다

  * A / AABA / ABA / ABAABA / BA / BAABA
* LCP는 RANK 순으로 작성함

  * RANK는 Suffix Array의 Index 값을 저장한 배열임 - suffix array와 역함수 관계
  * RANK값이 나타내는 index 바로 이전의 suffix array와 비교 (j)
  * rank 순으로 값을 정리하면 ABAABA / BAABA / AABA / ABA / BA / A와 같이 index가 0부터 1씩 증가한 곳에서 시작하는 것을 알 수 있음(i)

* 자세히 풀어 쓰면 아래와 같이 동작하는 것을 알 수 있다.

1. lcp = 3
   * **ABA**
   *  **ABA**ABA

2. lcp = 2
   * **BA**
   * **BA**ABA
3. lcp  = 1
   * **A**
   * **A**ABA
4. lcp = 1
   * **A**ABA
   * **A**BA

5. lcp = 0
   * ABAABA
   * BA

6. lcp = 0
   * x
   * A

* 처음에 문자열을 같을때까지 하나씩 비교하여 lcp로 작성 (1번)
* 다음 문자열에서 동일한 값이 나오지 않으면 lcp-1 진행 (2번 / 3번)
* 3번이 끝난 후 len = 0에서 다음에 오는 문자를 비교 (4번)
* 동일한 문자가 없어서 while문 못 도는 경우, lcp = 0 (5번 / 6번)

<br/>


| i    | Suffix Array | RANK=k | j (Sfx[k-1]) | lcp[k] = len |
| ---- | ------------ | ------ | ------------ | ------------ |
| 0    | 5 - A        | 3      | 3            | 0            |
| 1    | 2 - AABA     | 5      | 4            | 1 (A)        |
| 2    | 3 - ABA      | 1      | 5            | 1 (A)        |
| 3    | 0 - ABAABA   | 2      | 2            | 3 (ABA)      |
| 4    | 4 - BA       | 4      | 0            | 0 (X)        |
| 5    | 1 - BAABA    | 0      | x            | 2 (BA)       |

* 시간 복잡도 O(N)으로 해결할 수 있다.

<br/>

**Code**

```c++
vector<int> lcp(vector<int> sfx, string str){
    int n = str.size();
    vector<int>r(n), lcp(n); // rank
    for (int i=0;i<n;i++) r[sfx[i]] = i;

    int len =0;
    for (int i=0;i<n;i++){
        int k = r[i];
        if (k){ // not 0(first index of suffix array)
            int j = sfx[k-1];
            while(str[j+len] == str[i+len]) len++;
            lcp[k] = len;
            if (len) len--;
        }
    }
    return lcp;
}
```



