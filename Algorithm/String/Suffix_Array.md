---
sort: 1
---

# Suffix Array

* 문자열에 존재하는 모든 접미사를 정렬

* 접미사를 구현하는 방법에는 Naive / Manber-Mayers 알고리즘 2가지가 있음
  * Naive 알고리즘의 시간 복잡도는 O($$N^2log(N)$$) 이므로 사용하는데 효과적이지 않음
    * 정말 단순하게 모든 접미사를 구하고 정렬하는 방식
  * Manber-Mayers 알고리즘의 시간 복잡도는 O($$N(logN)^2$$)이므로 Suffix Array를 구할 때는 Manber-Mayers를 적용

 <br/>

#### Manber-Myers Algorithm

* 정렬할 때 Rank를 사용하고, 기수정렬 컨셉을 적용
  * 반복문을 통해서 2의 거듭제곱 단위로 비교할 문자열을 지정하는데 O($$logN$$)
  * 비교할 문자열이 지정된 상태에서 배열 정렬할 때 O($$NlogN$$)

* 그룹이 같은 경우, 2의 거듭제곱에 있는 문자열을 비교하여 그룹이 같을 때 동일 그룹으로 지정
  * 2의 거듭재곱에 있는 문자열도 동일한 경우, 같은 그룹으로 엮은 후 다음 2의 거듭제곱에서 비교
* 그룹이 다른 경우, 새로운 그룹 번호로 지정
* 그룹 비교를 하면서 그룹에 변경할 내용을 반영해야되기 때문에, new group이라는 임시 값을 만들어서 비교
* new group의 default값이 0이므로, `ng[SA[0]] = 1;` 같은 양수 값을 넣어줌
  * 0으로 사용시 동일 rank(group)으로 인식

<br/>

**Code**

```c++
vector<int> getsfx(string &str)
{
    int n = str.size();
    vector<int> G(n), SA(n,0), ng(n);
    for (int i = 0; i < n; i++)
    {
        SA[i] = i; G[i] = str[i];// - 'a';
    }
    for (int diff = 1; diff < n; diff <<= 1)
    {
        auto cmp = [&] (int i, int j){
            return G[i] != G[j] ? G[i] < G[j] : G[i+diff] < G[j+diff];
        };
        sort(SA.begin(), SA.end(), cmp); // align suffix array
        ng[SA[0]] = 1; // bigger than 0 (default ng is 0)
        for (int i = 0; i < n - 1; i++) {
            ng[SA[i + 1]] = ng[SA[i]] + cmp(SA[i], SA[i + 1]); // if rank is differ, assign next rank
        }
        G = ng;
    }
    return SA;
}
```



##### 추가로 확인이 필요한 내용

* Radix Sort 대신 Counting Sort를 사용하는 경우, 시간 복잡도가 O($$N(logN)^2$$)애서 O($$NlogN$$) 으로 줄어듦







* 그리고 O(N)으로 구현하는 방법은 확인 필요
