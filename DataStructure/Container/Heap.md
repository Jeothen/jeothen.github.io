---
sort: 6
---

# Heap







**Code**

```c++
#define MAX_SIZE 100001

template <typename T>
class heap
{
private:
    T h[MAX_SIZE];
    int _size = 1;

public:
    void swap(T *a, T *b) {
        T tmp = *a; *a = *b; *b = tmp;
    }
  
    T push(T value)
    {
        if (_size >= MAX_SIZE)
        {
            return -1;
        }

        h[_size] = value;
        int current = _size;
        int parent = _size / 2;

        while (current > 1 && h[current] < h[parent]) { // change
            swap(&h[current], &h[parent]);
            current = parent;
            parent = parent / 2;
        }
        _size++;
        return 1;
    }

    T pop()
    {
        if (_size <= 1)
            return 0;

        T ret = h[1];
        _size--;

        h[1] = h[_size];
        int current = 1;
        int leftChild = current * 2;
        int rightChild = current * 2 + 1;
        int minNode = current;

        while (leftChild < _size)
        {
            if (h[minNode] > h[leftChild])
                minNode = leftChild; // change
            if (rightChild < _size && h[minNode] > h[rightChild])
                minNode = rightChild; // chagne
            if (minNode == current)
                break;
            else
            {
                swap(&h[current], &h[minNode]);
                current = minNode;
                leftChild = current * 2;
                rightChild = current * 2 + 1;
            }
        }
        return ret;
    }
    bool empty() { return !(_size - 1); }
    int size() { return _size - 1; }
};
```

