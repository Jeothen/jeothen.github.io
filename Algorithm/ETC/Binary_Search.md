---
sort: 2
---

# Binary Search

* 정렬된 array에서 특정 값의 위치를 알아내는 방법
* low 값과 high값을 이용하여 mid 값을 계산하며, 값의 범위를 줄여나감
* 길이가 N인 행렬인 경우 log(N)번을 수행하면 원하는 위치를 찾을 수 있기 때문에 시간 복잡도는 O($$logN$$)

**Lower Bound**

* target value보다 크거나 같은 값이 나오는 처음 위치
* target value가 여러개 존재하면 target value의 첫번째 index

**Upper Bound**

* target value보다 큰 값이 나오는 처음 위치
* target value가 여러개 존재하면 target value보다 큰 값이 나오는 첫번째 index

**Code**

```c++
int lowerBound(vector<int>vc, int value)
{
    int low = 0, high = vc.size();
    while (low < high)
    {
        int mid = (low + high) >> 1;
        if (value <= vc[mid]) high = mid;
        else low = mid + 1;
    }
    return low;
}

int upperBound(vector<int>vc, int value)
{
    int low = 0, high = vc.size();
    while (low < high) 
    {
        int mid = (low + high) >> 1;
        if (value >= vc[mid]) low = mid+1;
        else high = mid;
    }
    return low;
}

void test(){
    vector<int> vc = {1, 2, 4, 7, 7, 7, 10, 22, 27};
    cout << lowerBound(vc, 6) << endl;  // 3
    cout << lowerBound(vc, 7) << endl;  // 3
    cout << lowerBound(vc, 8) << endl;  // 6
 
  	cout << upperBound(vc, 6) << endl;  // 3
    cout << upperBound(vc, 7) << endl;  // 6
    cout << upperBound(vc, 8) << endl;  // 6
}
```

