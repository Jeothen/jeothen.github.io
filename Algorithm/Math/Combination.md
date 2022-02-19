---
sort: 1
---

# Combination

* n개에서 k개를 뽑는 경우를 조합 ($$n<= k$$)
  * n개의 데이터에는 중복된 수가 존재하면 안 됨

* 모든 경우의 수를 구하는 식은 아래와 같다.

  $$ {n \choose k} = {P(n,k) \over k!} = {n! \over k! \times (n-k)!}$$ 



* 단순히 경우의 수가 아니라, 가능한 모든 경우의 수를 찾는 경우, 재귀를 통하여 전체 탐색이 필요
* (1,2,4)에서 2가지를 선택하는 경우는 (1,2), (1,4), (2,4) 3가지가 존재. 동일한 수가 q개 있으면  $$q!$$ 로 나눠줌

  * $${_4C_2 \over 2!} =  3 $$

* 재귀를 이용하는 방법, powerset을 이용하는 방법, 순열을 이용하는 방법이 있지만 순열을 이용하는 방법은 너무 느려서 사용을 안 하는 게 좋음

**Code**

```c++
_data[] = [1,2, ... , n]
t[] = [0,0,... ,0] // print

void combination(int n, int q, int k, int start)
{
    if (k == q)
    {
        count2++; // print loop
        return;
    }
    for (int i = start; i < n; i++) //  0
    {
        t[k] = _data[i];
        combination2(n, q, k + 1, i + 1); 
    }
}

void Implement(){
    combination(n, 4, 0, 0);  
}

```

* 아래는 여러가지 경우를 구현하고 속도 비교

```c++
#include <iostream>
#include <algorithm>
#include <vector>
#include <string.h>
#include <time.h>
using namespace std;

int data1[100];
int t1[100], t2[100], t3[100];
int n;
int count1, count2, count3, count4;

void combination1(int n, int k, int q)
{
    if (k == 0)
    { // Picked all n
        count1++;
/*        for (int i = 0; i < q; i++)
            printf("%d ", t1[i]);
        printf("\n");*/
    }
    else if (n < k)
        return; // n >= k
    else
    {
        t1[k - 1] = data1[n - 1];      // have to pick one out of n so parameter is n-1
        combination1(n - 1, k - 1, q); // if data[n-1] is picked, so next is k-1
        combination1(n - 1, k, q);     // if data[n-1] is not picked, so next is k
    }
}

void combination2(int n, int q, int k, int start)
{
    if (k == q)
    { // k is filled to q
        count2++;
/*        for (int i = 0; i < q; i++)
            printf("%d ", t2[i]);
        cout << endl;*/
        return;
    }
    for (int i = start; i < n; i++) //  0
    {
        t2[k] = data1[i];
        combination2(n, q, k + 1, i + 1); // insert t2[next_index]  by data[index] : index start from next_index
    }
}

// powerset
bool visited[10];
void combination3(int n, int q, int k, int start)
{
    if (k == q)
    { // visited count is q
        count3++;
/*        for (int i = 0; i < n; i++)
        {
            if (visited[i])
                cout << data1[i] << " ";
        }
        cout << endl;*/
        return;
    }
    for (int i = start; i < n; i++)
    {
        if (visited[i])
            continue;
        else
        {
            visited[i] = true; // visited check
            t3[k] = data1[i];
            combination3(n, q, k + 1, i + 1);
            visited[i] = false; // uncheck
        }
    }
}

// permutation
void combination4(int n, int k)
{
    vector<bool> chk(n);
    for (int i = 0; i < k; i++)
    {
        chk[i] = true;
    }
    sort(chk.begin(), chk.end());
    do
    {
        count4++;
/*        for (int i = 0; i < n; i++)
        {
            if (chk[i])
                cout << data1[i] << " ";
        }
        cout << endl;*/
    } while (next_permutation(chk.begin(), chk.end()));
}

int main()
{
    n = 100;
    count1 = 0, count2 = 0, count3 = 0, count4 = 0;
    for (int i = 0; i < n; i++)
    {
        data1[i] = i + 1;
    }
    clock_t start;
    start = clock();
    combination1(n, 4, 4);
    cout << "Comb1 = " << clock() - start << "\n"; // 33175
    start = clock();
    combination2(n, 4, 0, 0);
    cout << "Comb2 = " << clock() - start << "\n"; // 16497
    start = clock();
    memset(visited, 0, sizeof(visited));
    combination3(n, 4, 0, 0);
    cout << "Comb3 = " << clock() - start << "\n";  // 19655
    start = clock();
    combination4(n, 4);
    cout << "Comb4 = " << clock() - start << "\n";  // 4944031
    start = clock();
    printf("%d %d %d %d\n", count1, count2, count3, count4);
}
```



### 중복 조합 (Recursive Combination)

* 조합과 동일하나 중복을 허용하기 때문에 같은 숫자를 여러번 뽑는 것이 가능
* $$_nH_k = _{n+k-1}C_{k-1}$$
* (1,4)에서 3개를 뽑는 경우를 생각하면,  (1,1,1), (1,1,4), (1,4,4),(4,4,4)
  * $$_2H_3 = _4C_3 = 4$$  

**Code**

```c++
_data[] = [1,2, ... , n]
t[] = [0,0,... ,0] // print

void repeat_combination(int n, int q, int k, int start)
{
    if (k == q)
    {
        count++; // print loop
      	return;
    }
    for (int i = start; i < n; i++)
    {
        t[k] = _data[i];
        repeat_combination(n, q, k + 1, i); 
    }
}

void Implement(){
    repeat_combination(n, 4, 0, 0);  
}
```

* 아래는 여러가지 경우를 구현하고 속도 비교

```c++
#include <iostream>
#include <algorithm>
#include <vector>
#include <time.h>
using namespace std;

int data1[101];
int t1[101], t2[101];
int n;
int count1, count2;

void repeat_combination1(int n, int k, int q)
{
    if (k == 0)
    { // Picked all n
        count1++;
        /*        for (int i = 0; i < q; i++)
                    printf("%d ", t1[i]);
                printf("\n");*/
    }
    else if (n == 0)
        return;
    else
    {
        t1[k - 1] = data1[n - 1];
        // have to pick one out of n so parameter is n-1
        repeat_combination1(n, k - 1, q); // if data[n-1] is picked and data[n] can be repeated, so next is k-1
        repeat_combination1(n - 1, k, q); // if data[n-1] is not picked, so next is k
    }
}

void repeat_combination2(int n, int q, int k, int start)
{
    if (k == q)
    { // k is filled to q
        count2++;
        /*        for (int i = 0; i < q; i++)
                    printf("%d ", t2[i]);
                cout << endl;*/
        return;
    }
    for (int i = start; i < n; i++)
    {
        t2[k] = data1[i];
        repeat_combination2(n, q, k + 1, i); // insert t2[next_index]  by data[index] : index start from next_index
    }
}

int main()
{
    n = 100;
    count1 = 0, count2 = 0;
    for (int i = 0; i < 100; i++)
    {
        data1[i] = i + 1;
    }
    // 100H5
    clock_t start = clock();
    repeat_combination1(n, 5, 5);
    cout << "Comb1 = " << clock() - start << "\n"; // 662784
    start = clock();
    repeat_combination2(n, 5, 0, 0);
    cout << "Comb2 = " << clock() - start << "\n"; // 321057
    printf("%d %d\n", count1, count2);
}
```
