---
sort: 4
---

# Rabin Karp

* 라빈 카프 알고리즘은 해싱을 기반으로 1:1 매칭을 찾는 알고리즘이다.
* 해싱을 기반으로 찾기 때문에 충돌이 많다. 충돌을 줄이기 위해 보통 MOD를 매우 큰 수로 설정한다.
* 그래도 여전히 충돌이 있을 수 있기 때문에, 해시 값이 동일한 경우 문자열을 비교하는 작업을 추가로 수행한다.

<br/>

* 라빈카프 알고리즘은 보통 라빈카프 fingerprinting 알고리즘을 사용한다.

$$H[i] = t[i]  * $$m<sup>n-1</sup> + $$ t[i+1] * $$ m<sup>n-2</sup> + ....  + $$ t[i+n-2] * m^1 + t[i+n-1] * m^0 $$

<br/>

* 라빈카프 fingerprinting 알고리즘은 아래와 같이 변형됨

$$H[i+1] = t[i+1]* $$  m<sup>n-1</sup> + $$ t[i+2]* $$  m<sup>n-2</sup> + .... + $$ t[i+n-1] * m^1 + t[i+n] * m^0 $$

=  ($$t[i] *$$ m<sup>n</sup> + $$t[i+1] *$$ m<sup>n-1</sup> + $$t[i+2] *$$ m<sup>n-2</sup> + ... + $$t[i+n-1] * m^1 - t[i] * m^n $$ ) + $$t[i+n] * m^0$$ 

 = ($$t[i] * $$ m<sup>n-1</sup> + $$ t[i+1]*$$ m<sup>n-2</sup> + ... + $$ t[i+n-1]*m^0 - t[i]*$$m<sup>n-1</sup>) $$ * m + t[i+n]*m^0$$ 

 = $$m*(H[i] - t[i] *$$ m<sup>n-1</sup> $$) + t[i+m]*m^0 $$

<br/>

* 따라서, best case 인 경우, 시간복잡도는 O(N+M) 이다.
* 그러나, worst case인 경우 시간 복잡도는 O(NM)이다. 
  * "AAAAAAAAA", "AAA" 와 같은 경우..

**Code**

```c++
#include <cstdio>
#include <vector>
#define MOD 1000000009


std::vector<int> rabin_karp(char* text, char* pattern){
    int res = 0;
    int lent, lenp;
    long long texthash = 0, patternhash = 0, power = 1;
    for (lent = 0; text[lent] != '\0'; lent++);
    for (lenp = 0; pattern[lenp] != '\0'; lenp++);
    
    // rabin - karp algorithm
    std::vector<int>vc;
    
    // calculate hash value
    for (int i = 0; i < lenp; i++)  
    {
        texthash = (texthash * 257 + text[i]) % MOD; //  up to pattern length, first text hash value
        patternhash = (patternhash * 257 + pattern[i]) % MOD;
        if (i != 0) power = (power * 257) % MOD; // power is length of pattern's Degree, m^(lenp-1)
    }

    for (int i = 0; i <= lent - lenp; i++) // already calculate first text hash
    {
        if (texthash == patternhash) {
            // text compare
            bool isdiff = false;
            for (int j=0; j<lenp;j++){
                if (pattern[j] != text[i+j]) {
                    isdiff = true; break;
                }
            }
            if (!isdiff) vc.push_back(i); // start index
        }
        // H[i+1] = m * (H[i] - t[i] * m^(n-1)) + t[i+lenp]
        texthash = (257 * (texthash - text[i] * power) + text[i + lenp]) % MOD;  
        if (texthash < 0) texthash += MOD;
    }
    return vc;
}

```



