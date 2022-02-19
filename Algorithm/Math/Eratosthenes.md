---
sort: 4
---

# Eratosthenes

* 에라토스테네스의 체 (Sieve of Eratosthenes) : 임의의 수 N까지 소수(Prime Number)를 계산하는 방법
* loop의 범위를  $$\sqrt{N}$$ 까지만 계산하면 됨
  * 예를 들어 N = 30인 경우,  $$\sqrt{N} = 5$$ 인데 `4*5 / 4*6 / 4*7`  을 계산한 뒤에 `5*4 / 5*5 / 5*6 ` 까지 계산하게 됨
    * 이런 경우, `6 * 4/ 6 * 5 ` 도 계산되어야 할 것 같지만, 이전에 계산된 항목을 중복으로 하는 것을 알 수 있음
*  `isPrime = false` 처리가 미리 된 항목은 생략 가능
  * 두 수 A / B가 있고, B가 A의 배수라고 하면, B의 배수는 A의 배수를 만족
    * 예를 들어 A = 3, B = 12 인 경우, 12의 배수 24, 36 등은 3의 배수를 만족
* 두번째 반복문에서 `j = i*i` 부터 시작하는 이유는, 2부터 i-1까지의 배수는 이미 확인을 했기 떄문에 `i*i` 부터 확인
  * `j += i` 는 i의 배수를 나타냄

```c++
bool isPrime[N + 1];

void eratosthenes()
{
    int root = static_cast<int>(sqrt(N));
    for (int i = 2; i <= root; i++)
    {
        if (!isPrime[i]) continue;
        for (int j = i * i; j <= N; j += i)
        {
            isPrime[j] = false;
        }
    }
}
void implement(){
    
    memset(isPrime,true,sizeof(isPrime));
    eratosthenes();
}
```

