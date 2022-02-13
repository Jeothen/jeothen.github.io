---
sort: 5
---

# Boyer Moore

* Boyer Moore 알고리즘은 두가지 접근법을 조합하여 최적의 방법으로 문자를 비교

* Rabin-Karp와 KMP는 왼쪽에서 오른쪽으로 비교했지만, Boyer Moore는 오른쪽에서 왼쪽으로 비교

  * 문자열을 skip할 때는 왼쪽에서 오른쪽으로 진행

* 두가지 접근법은 Bad Character / Good Suffix

* **Bad Characeter**

  * 패턴의 문자와 일치하지 않는 텍스트의 문자를 Bad Character라고 함
    * Bad Character 테이블은 문자의 가장 오른쪽 index를 저장

  * Bad Character Table은 문자열 내에 속한 문자의 가장 오른쪽 인덱스를 저장
    * 존재하지 않는 문자는 -1로 저장하는 것이 일반적

  **Bad Character Code**

  ```c++
  
  vector<int> createBC(string pat)
  {
      int M = pat.length();
      vector<int>bc(NUM_OF_CHARS);
      for (int i = 0; i < NUM_OF_CHARS; ++i) bc[i] = -1;
      for (int i = 0; i < M - 1; ++i) bc[(int)pat[i]] = i;
      return bc;
  }
  
  void BM(string pat, string txt)
  {
      int N = txt.length(), M = pat.length();
      vector<int>bc = createBC(pat);
  
      int s = 0;
      int j = 0;
      
      while (s <= (N - M))
      {
          j = M - 1; // from last character
          while (j >= 0 && pat[j] == txt[s + j]) j--;
  
          if (j < 0)
          {
              printf("Pattern start index %d\n", s);
              s += (s + M < N) ? M - bc[txt[s + M]] : 1;
          }
          else
          {
              s += max(1, j - bc[txt[s + j]]);
          }
      }
  }
  ```

  * return으로 받은 bc를 이용하여 문자열 간 비교를 수행

  * 하나의 예시로 text : `AABACAADAABAACBAC`  와 pattern : `AABAC` 을 비교
  * BC (AABAC)
    * A = 3
    * B = 2
    * C = 4

  * Text를 와 Pattern을 비교할 때 BC를 이용

  * 첫번째로 모든 문자가 매칭
    * 다음 문자가 있는 경우, 다음 문자의 M-BC 만큼 이동
    * 매칭되고 다음 문자인 bc[txt[s + M]] = "A"이므로, M-3 = 2만큼 이동

  | A    | A    | B    | A    | C    | A    | A    | D    | A    | A    | B    | A    | A    | C    | B    | A    | C    |
  | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
  | A    | A    | B    | A    | C    |      |      |      |      |      |      |      |      |      |      |      |      |

  * 6번째 index인 A와 C를 비교
    * 다른 문자가 존재하기 때문에, `max(1, j-bc[txt[s+j]])` 만큼 이동
    * 매칭이 안 된 마지막 문자인 `bc[txt[s+j]]` = A가 존재하므로 4-3만큼 이동 (+1)

  | A    | A    | B    | A    | C    | A    | A     | D    | A    | A    | B    | A    | A    | C    | B    | A    | C    |
  | ---- | ---- | ---- | ---- | ---- | ---- | ----- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
  |      |      | A    | A    | B    | A    | **C** |      |      |      |      |      |      |      |      |      |      |

  * 7번째 index인 D와 C를 비교
    * 다른 문자가 존재하기 때문에, `max(1, j-bc[txt[s+j]])` 만큼 이동
    * 매칭이 안 된 마지막 문자인 `bc[txt[s+j]]` = D가 존재하지 않으므로 4-(-1)만큼 이동 (+5)

  | A    | A    | B    | A    | C    | A    | A    | D     | A    | A    | B    | A    | A    | C    | B    | A    | C    |
  | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ----- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
  |      |      |      | A    | A    | B    | A    | **C** |      |      |      |      |      |      |      |      |      |

  * 12번째 index인 A와 C를 비교
    * 다른 문자가 존재하기 때문에, `max(1, j-bc[txt[s+j]])` 만큼 이동
    * 매칭이 안 된 마지막 문자인   `bc[txt[s+j]]` = A가 존재하므로 4-3만큼 이동 (+1) 

  | A    | A    | B    | A    | C    | A    | A    | D    | A    | A    | B    | A    | A     | C    | B    | A    | C    |
  | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ----- | ---- | ---- | ---- | ---- |
  |      |      |      |      |      |      |      |      | A    | A    | B    | A    | **C** |      |      |      |      |

  * 13번째 index부터 왼쪽으로 11번째 까지 비교
    * 2번 매칭이 되었기 때문에 j = (M-1)-2 = 2
    * 매칭이 안 된 마지막 문자인 A가 BC에 존재하므로 ` max(1, j - bc[txt[s + j]])`에 의해 max(1,-1) = 1 만큼 이동

  | A    | A    | B    | A    | C    | A    | A    | D    | A    | A    | B    | A     | A    | C    | B    | A    | C    |
  | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ----- | ---- | ---- | ---- | ---- | ---- |
  |      |      |      |      |      |      |      |      |      | A    | A    | **B** | A    | C    |      |      |      |

  * 14번째 index 비교
    * 매칭이 안 된 마지막 문자 B가 bc에 존재하기 때문에 4-2 = 2만큼 이동

  | A    | A    | B    | A    | C    | A    | A    | D    | A    | A    | B    | A    | A    | C    | B     | A    | C    |
  | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ----- | ---- | ---- |
  |      |      |      |      |      |      |      |      |      |      | A    | A    | B    | A    | **C** |      |      |

  * 오른쪽에서 3개의 문자열이 매칭되었기 때문에 j = 1
  * `max(1, j - bc[txt[s + j]])` = max(1,-3) = 1만큼 이동

  | A    | A    | B    | A    | C    | A    | A    | D    | A    | A    | B    | A    | A    | C    | B    | A    | C    |
  | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
  |      |      |      |      |      |      |      |      |      |      |      |      | A    | A    | B    | A    | C    |

  * 최적의 경우, text에서 matching을 하는 문자가 pattern에 항상 없는 경우이고 이 때 시간 복잡도는 O(N/M)이다
    * 항상 M만큼 skip
  * 그러나 최악의 경우 "AAAAAA"에서 "AA" 같은 동일한 문자를 비교하는 경우, 항상 모든 문자열을 비교해야 되기 때문에 시간 복잡도는 O(NM)

* **Good Suffix**

  * Pattern과 text를 비교하는 중 불일치하는 지점이 발생했을 때, text와 일치했던 Pattern의 Suffix와 동일한 연속된 부분 문자열을 찾아서 이동시켜서 중간 내용을 skip
    * 2개 이상의 동일한 부분 문자열이 있는 경우 우측부터 검색 (오른쪽에서 왼쪽으로 문자열을 비교하기 때문)
    * 일치하는 Suffix를 제외하고 동일한 부분 문자열이 없는 경우, 일치하는 곳까지를 새로운 Suffix로 만들어서 매칭
  
  * **Good Suffix Table**은 마지막 문자부터 비교했을 때 일치하지 않는 지점에서 skip 할 수 있는 거리를 의미
  
    * i는 str2의 시작과 비교되는 str1의 index이고, j는 str1의 마지막과 비교되는 str2의 index
    * `nanana` 라는 문자열로 good suffix array를 만드는 경우
  
    ---
  
    * i = M - 1 = 5, j = 0에서시작
      * gs[i+j], 즉 문자 불일치가 발생한 위치에 start index(i) 대입
        * gs[i+j] = 5
      * i = 4, j = 1 로 변경
  
    | i        | 0    | 1    | 2    | 3    | 4    | 5     |      |      |      |      |      |
    | -------- | ---- | ---- | ---- | ---- | ---- | ----- | ---- | ---- | ---- | ---- | ---- |
    | j        |      |      |      |      |      | 0     | 1    | 2    | 3    | 4    | 5    |
    | str1     | n    | a    | n    | a    | n    | **a** |      |      |      |      |      |
    | str2     |      |      |      |      |      | **n** | a    | n    | a    | n    | a    |
    | pre_gs   | 6    | 6    | 6    | 6    | 6    | 6     |      |      |      |      |      |
    | after_gs | 6    | 6    | 6    | 6    | 6    | **5** |      |      |      |      |      |
  
    * i = 4, j = 1에서시작
      * j = 1에서의 문자가 매칭되었으므로 i =4 , j=0에서 비교했으나 매칭됨
      * suffix가 일치하므로 i 이전의 index에 i 값 대입
  
    | i        | 0     | 1     | 2     | 3     | 4     | 5     |      |      |      |      |      |
    | -------- | ----- | ----- | ----- | ----- | ----- | ----- | ---- | ---- | ---- | ---- | ---- |
    | j        |       |       |       |       | 0     | 1     | 2    | 3    | 4    | 5    |      |
    | str1     | n     | a     | n     | a     | **n** | **a** |      |      |      |      |      |
    | str2     |       |       |       |       | **n** | **a** | n    | a    | n    | a    |      |
    | pre_gs   | 6     | 6     | 6     | 6     | 6     | 5     |      |      |      |      |      |
    | after_gs | **4** | **4** | **4** | **4** | 6     | 5     |      |      |      |      |      |
  
    * i =3, j = 2에서 시작
      * i+j = 3 에서 불일치 하므로 gs[i+j] = 3 대입, i = 2, j = 3 
  
    | i        | 0    | 1    | 2    | 3    | 4    | 5     |      |      |      |      |      |
    | -------- | ---- | ---- | ---- | ---- | ---- | ----- | ---- | ---- | ---- | ---- | ---- |
    | j        |      |      |      | 0    | 1    | 2     | 3    | 4    | 5    |      |      |
    | str1     | n    | a    | n    | a    | n    | **a** |      |      |      |      |      |
    | str2     |      |      |      | n    | a    | **n** | a    | n    | a    |      |      |
    | pre_gs   | 4    | 4    | 4    | 4    | 6    | 5     |      |      |      |      |      |
    | after_gs | 4    | 4    | 4    | 4    | 6    | **3** |      |      |      |      |      |

    * i = 2, j = 3에서 시작
      * 모든 suffix가 일치하므로, i = 2 이전의 gs index를 2로 대입
  
    | i        | 0     | 1     | 2     | 3     | 4     | 5     |      |      |      |      |      |      |
    | -------- | ----- | ----- | ----- | ----- | ----- | ----- | ---- | ---- | ---- | ---- | ---- | ---- |
    | j        |       |       | 0     | 1     | 2     | 3     | 4    | 5    |      |      |      |      |
    | str1     | n     | a     | **n** | **a** | **n** | **a** |      |      |      |      |      |      |
    | str2     |       |       | **n** | **a** | **n** | **a** | n    | a    |      |      |      |      |
    | pre_gs   | 4     | 4     | 4     | 4     | 6     | 3     |      |      |      |      |      |      |
    | after_gs | **2** | **2** | 4     | 4     | 6     | 3     |      |      |      |      |      |      |
  
    * i = 1 , j = 4에서 시작
      * i+j = 5에서 문자가 불일치하므로, gs[i+j] = 1 대입
  
    | i        | 0    | 1    | 2    | 3    | 4    | 5     |      |      |      |      |      |
    | -------- | ---- | ---- | ---- | ---- | ---- | ----- | ---- | ---- | ---- | ---- | ---- |
    | j        |      | 0    | 1    | 2    | 3    | 4     | 5    |      |      |      |      |
    | str1     | n    | a    | n    | a    | n    | **a** |      |      |      |      |      |
    | str2     |      | n    | a    | n    | a    | **n** | a    |      |      |      |      |
    | pre_gs   | 2    | 2    | 4    | 4    | 6    | 3     |      |      |      |      |      |
    | after_gs | 2    | 2    | 4    | 4    | 6    | **1** |      |      |      |      |      |
  
    * i > 0 보다 클때만 동작하기 때문에, while문 종료
  
  **Good Suffix Code**
  
  ```c++
  
  vector<int> createGS(string pat)
  {
      int M = pat.length();
      vector<int> gs(M);
      for (int i = 0; i < M; ++i) gs[i] = M;
      int i = M - 1, j = 0;
      while (i > 0)
      {
          if (pat[i + j] == pat[j] && j >= 0) j--;
          else
          {
              if (j < 0)
                  for (; i + j >= 0; --j) gs[i + j] = i;
              else
                  gs[i + j] = i;
              j = M - i;
              i--;
          }
      }
      return gs;
  }
  
  void BM(string pat, string text)
  {
      int N = text.length(), M = pat.length();
  
      vector<int> gs = createGS(pat);
  
      int s = 0, j = 0;
      while (s <= (N - M))
      {
          j = M - 1;
          while (j >= 0 && pat[j] == text[s + j]) j--;
          if (j < 0)
          {
              printf("Pattern start index %d\n", s);
              s += gs[0];
          }
          else s += gs[j];
      }
  }
  ```
  
  * text와 pattern을 비교할 때, 이전에 만들었던 good suffix table을 이용
  
  * 모든 문자열이 일치하기 되면, gs[0]만큼 이동
  
  * 일치하지 않는 지점이 발생하면 gs[j] 만큼 이동
  
  * 하나의 예시로 text : `AABACAADAABAACBAC`  와 pattern : `AABAC` 을 비교
  
  * gs = [5,5,5,5,1]
  
  * 첫번째로 모든 문자가 매칭되기 때문에 gs[0]만큼 이동
  
  | A    | A    | B    | A    | C    | A    | A    | D    | A    | A    | B    | A    | A    | C    | B    | A    | C    |
  | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
  | A    | A    | B    | A    | C    |      |      |      |      |      |      |      |      |      |      |      |      |
  
  * pattern의 index=4에서 매칭 실패했으므롤 gs[4] = 1만큼 이동
  
  | A    | A    | B    | A    | C    | A    | A    | D    | A    | A     | B    | A    | A    | C    | B    | A    | C    |
  | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ----- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
  |      |      |      |      |      | A    | A    | B    | A    | **C** |      |      |      |      |      |      |      |
  
  * pattern의 index=4에서 매칭 실패했으므롤 gs[4] = 1만큼 이동
  
  | A    | A    | B    | A    | C    | A    | A    | D    | A    | A    | B    | A    | A    | C    | B    | A    | C    |
  | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
  |      |      |      |      |      |      | A    | A    | B    | A    | C    |      |      |      |      |      |      |
  
  * pattern의 index=4에서 매칭 실패했으므롤 gs[4] = 1만큼 이동
  
  | A    | A    | B    | A    | C    | A    | A    | D    | A    | A    | B    | A    | A    | C    | B    | A    | C    |
  | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
  |      |      |      |      |      |      |      | A    | A    | B    | A    | C    |      |      |      |      |      |
  
  * pattern의 index=4에서 매칭 실패했으므롤 gs[4] = 1만큼 이동
  
  | A    | A    | B    | A    | C    | A    | A    | D    | A    | A    | B    | A    | A    | C    | B    | A    | C    |
  | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
  |      |      |      |      |      |      |      |      | A    | A    | B    | A    | C    |      |      |      |      |
  
  * pattern의 index=2에서 매칭 실패했으므롤 gs[2] = 5만큼 이동
  
  | A    | A    | B    | A    | C    | A    | A    | D    | A    | A    | B    | A     | A    | C    | B    | A    | C    |
  | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ----- | ---- | ---- | ---- | ---- | ---- |
  |      |      |      |      |      |      |      |      |      | A    | A    | **B** | A    | C    |      |      |      |
  
  * 문자열 길이 초과로 while문 빠져 나옴

<br/>

### Good Suffix와 Bad Character를 조합

* Bad Character와 Good Suffix 중 문자열을 가장 많이 skip 할 수 있는 방법으로 적용함
* 완전히 매칭될 때는 Good Suffix

```c++
vector<int> createBC(string pat)
{
    int M = pat.length();
    vector<int> bc(NUM_OF_CHARS);
    for (int i = 0; i < NUM_OF_CHARS; ++i)
        bc[i] = -1;
    for (int i = 0; i < M - 1; ++i)
        bc[(int)pat[i]] = i;
    return bc;
}

vector<int> createGS(string pat)
{
    int M = pat.length();
    vector<int> gs(M);
    for (int i = 0; i < M; ++i)
        gs[i] = M;
    int i = M - 1;
    int j = 0;

    while (i > 0)
    {
        if (pat[i + j] == pat[j] && j >= 0) j--;
        else
        {
            if (j < 0) while (i + j) gs[i + (j--)] = i;
            else gs[i + j] = i;
            j = M - i;
            i--;
        }
    }
    return gs;
}
void BM(string pat, string txt)
{
    int N = txt.length(), M = pat.length();
    vector<int> bc = createBC(pat);
    vector<int> gs = createGS(pat);
    int s = 0, j = 0;

    while (s <= (N - M))
    {
        j = M - 1;
        while (pat[j] == txt[s + j] && j >= 0) j--;
        if (j < 0)
        {
            printf("Pattern start index %d\n", s);
            s += gs[0];
        }
        else
        {
            s += max(j - bc[txt[s + j]], gs[j]); // Bad Character || Good Suffix
        }
    }
}
```



---

<br/>

### Boyer Moore Hospool







```c++
#include <cstring>
#include <vector>

int ascii[256];

void create_Bad_Match_table(char pattern[]){
    int len_p;
    for (len_p = 0; pattern[len_p] != '\0'; len_p++);
    
    // value 0 is filled to length of pattenr    
    for (int i=0; i<256;i++){
        if (ascii[i] == 0) ascii[i] = len_p;
    }

    for (int i=0; i<len_p-1; i++){ // last character is skip
        ascii[pattern[i]] = len_p - i - 1;
    }

}

std::vector<int>Hospool(char* text, char* pattern){
    std::vector<int> res;
    int len_p, len_t;
    for (len_t = 0; text[len_t] != '\0'; len_t++);
    for (len_p = 0; pattern[len_p] != '\0'; len_p++);
    create_Bad_Match_table(pattern);

    int i =0, j =0, k =0;
    while(i <= len_t-len_p) {
        j = len_p-1; // pattern index from right
        k = i + len_p-1; // text index from right
        while(j >= 0 && pattern[j] == text[k]) {
            --j; --k;
        }
        if (j == -1) {
            printf("%d\n",i);
            res.push_back(i); // start index
        }
        i += ascii[text[i + len_p - 1]]; // text index from right
    }
    return res;
}

```

