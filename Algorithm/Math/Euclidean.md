---
sort: 5
---

# Euclidean

* 유클리드 호제법(Euclidean Algorithm)은 두개의 자연수의 최대 공약수를 빠르게 계산하는 방법
* 두 수 A,B의 최대 공약수를 구하는 방법 ($$A >= B$$)
  * A % B = r
  * B % r = r1
  * r % r1 = r2
  * ...
  * $$r_k$$ % $$r_{k+1}$$ = 0 을 만족하는 지점까지 반복했을 때, $$r_{k+1}$$ 이 A,B의 최대 공약수

* 최소 공배수는 두 수를 곱하고 최대 공약수로 나누어주면 된다.

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

