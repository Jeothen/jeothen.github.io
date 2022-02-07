---
sort: 3
---

# Rabin Karp

* Rabin Karp is an algorithm that finds 1:1 matching based on hashing
* So, there are a lot of collision.  To reduce collision, Usually the MOD is set to very large prime number.
* There may still be collisions, so the existance of the string is checked through simple comparision only when hash value is same.



* Rabin Karp algorithm usually using `Rabin fingerprint algorithm`

$$H[i] = t[i]  * $$m<sup>n-1</sup> + $$ t[i+1] * $$ m<sup>n-2</sup> + ....  + $$ t[i+n-2] * m^1 + t[i+n-1] * m^0 $$



* So, `Rabin fingerprint algorithm` transfered like belows

$$H[i+1] = t[i+1]* $$  m<sup>n-1</sup> + $$ t[i+2]* $$  m<sup>n-2</sup> + .... + $$ t[i+n-1] * m^1 + t[i+n] * m^0 $$

=  ($$t[i] *$$ m<sup>n</sup> + $$t[i+1] *$$ m<sup>n-1</sup> + $$t[i+2] *$$ m<sup>n-2</sup> + ... + $$t[i+n-1] * m^1 - t[i] * m^n $$ ) + $$t[i+n] * m^0$$ 

 = ($$t[i] * $$ m<sup>n-1</sup> + $$ t[i+1]*$$ m<sup>n-2</sup> + ... + $$ t[i+n-1]*m^0 - t[i]*$$m<sup>n-1</sup>) $$ * m + t[i+n]*m^0$$ 

 = $$m*(H[i] - t[i] *$$ m<sup>n-1</sup> $$) + t[i+m]*m^0 $$



* So, best case, time complexity is O(N+M).
* But worst case such as "AAAAAAAA", "AAA" : time complexity is O(NM)





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



