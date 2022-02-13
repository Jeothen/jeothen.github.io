---
sort: 2
---

# Queue





**Code**

```c++
#include <iostream>
using namespace std;

struct qnode
{
    int value;
    qnode *next;
};

template <typename T>
class Queue
{
private:
    qnode *front, *rear;
    int _size;

public:
    Queue()
    {
        front = rear = NULL;
        _size = 0;
    }
    ~Queue()
    {
        while (!isempty())
            pop();
    }
    void insert(T data)
    {
        qnode *node = (qnode *)malloc(sizeof(qnode));
        node->value = data;
        node->next = NULL;
        if (isempty())
            front = rear = node;
        else
        {
            rear->next = node;
            rear = rear->next;
        }
        _size++;
    };
    T pop()
    {
        if (isempty())
            return -1;
        qnode *delnode = front;
        T res = delnode->value;
        front = delnode->next;
        free(delnode);
        _size--;
        return res;
    }
    bool isempty() { return !_size; }
    int size() { return _size; }
};
```

