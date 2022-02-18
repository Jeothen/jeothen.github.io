---
sort: 3
---

# PowerSet

* 배열을 이용하여 나타낼 수 있는 모든 부분집합을 표현
* 배열의 크기가 n인 경우, 부분집합의 갯수는 $$2^n$$ 개이다.
* bool type으로 true / false를 부여하여 사용 여부를 설정

**Code**

```c++
int _data[100], t[100];

void powerset(int n, int k)
{
    if (n == k)
    {
        count++;
        for (int i = 0; i < n; i++)
        {
            if (t[i] == 1) printf("%d ", _data[i]);
        }
        printf("\n");
    }
    else
    {
        t[k] = 1;
        powerset(n, k + 1);
        t[k] = 0;
        powerset(n, k + 1);
    }
}

void implement(){
    for (int i = 0; i < n; i++)
    {
        _data[i] = i + 1;
        t[i] = 0;
    }
    powerset(n, 0);
}
```

