---
sort: 3
---

# Stack

* LIFO (Last In First Out) 을 따르는 Container
  * Push : 리스트의 가장 우측에 값을 넣음
  * Pop :  리스트의 가장 오른쪽 값을 제거

**Code**

```c++
#include <iostream>
using namespace std;

struct snode{
    int value; 
  	snode* pre;
};

template <typename T>
class Stack{
private :
    snode *rear;
    int _size;
public :
    Stack() { 
        rear = NULL; 
        _size = 0;
    }
    ~Stack() {
        while (!isempty()) pop();
    }
    void push(T val)
    {
        snode* node = (snode*)malloc(sizeof(snode));
        node->value = val;
        node->pre = rear;
        rear = node;
        _size++;
    }
    T pop(){
        if (isempty()) return -1;
        snode* delnode = rear;
        T res = delnode->value;
        rear = delnode->pre;
        free(delnode);
        _size--;
        return res;
    }
    int size() {return _size;}
    int isempty() {return !_size;}
};
```

