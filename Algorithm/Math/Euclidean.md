---
sort: 5
---

# Euclidean

* 유클리드 호제법(Euclidean Algorithm)은 두개의 자연수의 최대 공약수를 빠르게 계산하는 방법
* 





**Code**

```c++
int gcd(int a, int b)
{
    if (a % b == 0) return b;
    return gcd(b, a % b);
}

int lcm(int a, int b)
{
    return a * b / gcd(a, b);
}
```

