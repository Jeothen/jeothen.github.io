---
sort: 2
---

# Permutaion

* 서로 다른 n개의 원소에서 r개를 채택하여 순서대로 정렬한 것
* (1,2,4,5)의 원소에서 2개를 순서대로 나열하는 방법은 (1,2), (1,4), (1,5), (2,1), (2,4), (2,5), (4,1), (4,2), (4,5), (5,1), (5,2), (5,4) 12개임
* 즉, $$_nP_r = {n! \over (n-r)!}$$ 을 만족하는 것을 알 수 있음
* 단순히 경우의 수가 아니라, 가능한 모든 경우의 수를 찾는 경우, 재귀를 통하여 전체 탐색이 필요

**Code**

```c++
int _data[];
int n, count1;

void swap(int *a, int *b) {
    int tmp = *a; *a = *b; *b = tmp;
}

void permutation1(int n, int q, int k)
{
    if (k == q)
    {
        count1++; // print loop
    }
    else
    {
        for (int i = k; i < n; i++)
        {
            swap(&_data[i], &_data[k]); // order swap
            permutation1(n, q, k + 1); // recursion // pick i, so next is k+1
            swap(&_data[i], &_data[k]); // recover
        }
    }
}

void implement(){
    for (int i = 0; i < n; i++) _data[i] = i+1;
    permutation1(n, 5, 0);
}
```

* 직접 구현 / powerset / 알고리즘을 사용했으나, 직접 구현한 경우가 가장 속도가 빨랐음
  * powerset으로 구현하면 매우 비효율적

```c++
#include <iostream>
#include <algorithm>
#include <vector>
#include <time.h>
using namespace std;

int _data[100];
int t1[100], t2[100];
int n;
int count1, count2, count3;

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void permutation1(int n, int q, int k)
{ // q is just number of print count
    if (k == q)
    {
        count1++;
        /*        for (int i = 0; i < q; i++)
                {
                    printf("%d ", t1[i]);
                }
                printf("\n");*/
    }
    else
    {
        for (int i = k; i < n; i++)
        {
            swap(&t1[i], &t1[k]);      // order swap
            permutation1(n, q, k + 1); // recursion // pick i, so next is k+1
            swap(&t1[i], &t1[k]);      // recover
        }
    }
}

// powerset
bool visited[10];
void permutation2(int n, int q, int k)
{

    if (k == q)
    {
        count2++;
        /*        for (int i = 0; i < q; i++)
                {
                    printf("%d ", t2[i]);
                }
                printf("\n");*/
    }
    for (int i = 0; i < n; i++)
    {
        if (visited[i])
            continue;
        else
        {
            visited[i] = true;
            t2[k] = _data[i];
            permutation2(n, q, k + 1);
            visited[i] = false;
        }
    }
}

void permutation3(int n, int k)
{
    vector<int> vc(n);
    for (int i = 0; i < n; i++)
        vc[i] = _data[i];
    sort(vc.begin(), vc.end());
    do
    {
        count3++;
        /*        for (int i = 0; i < k; i++)
                {
                    cout << vc[i] << " ";
                }
                cout << endl;*/
        reverse(vc.begin() + k, vc.end()); // stl library doesn't support nPr, so this line needed
    } while (next_permutation(vc.begin(), vc.end()));
}

int main()
{
    n = 12;
    count1 = 0, count2 = 0, count3 = 0;
    for (int i = 0; i < n; i++)
    {
        _data[i] = i + 1;
        t1[i] = _data[i];
        t2[i] = 0;
    }
    clock_t start = clock();
    permutation1(n, 3, 0);
    cout << "Perm1 = " << clock() - start << endl; start = clock(); // 25
    permutation2(n, 3, 0);
    cout << "Perm2 = " << clock() - start << endl; start = clock(); // 31082093
    permutation3(n, 3);
    cout << "Perm3 = " << clock() - start << endl; // 917
    printf("%d %d %d\n", count1, count2, count3);
}
```





### 중복 순열 (Recursive with repetition)

*  서로 다른 n개의 원소에서 중복을 포함하여 r개를 채택하여 순서대로 정렬한 것
* $$_n \Pi _r  = n^r$$ 임을 직관적으로 확인할 수 있다.
  * 첫번째 자리에 n개가 올 수 있고, 두번째 자리... 마지막 자리도 마찬가지로 n개가 올 수 있음


**Code**

```c++
int _data[], t[];
int n, r;
int count1;

void repeat_permutation(int n, int q, int k)
{
    if (k == q)
    { 
        count1++; // print loop
        return;
    }
    for (int i = 0; i < n; i++)
    {
        t[k] = _data[i];
        repeat_permutation(n, q, k + 1); // enable duplication
    }
}

void implement(){
    for (int i = 0; i < n; i++)
    {
        _data[i] = i + 1;
        t[i] = 0;
    }
    repeat_permutation(n, r, 0);
}
```

