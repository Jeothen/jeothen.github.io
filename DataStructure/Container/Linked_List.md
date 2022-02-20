---
sort: 1
---

# Linked List

### 단순 링크드리스트 (Singly Linked List) 

* head와 tail은 NULL 값으로 유지한 채 처음과 끝을 알려주는 Pointer로 사용
* 새로운 노드가 추가되거나 삭제될 때, pre/next Pointer가 가리키는 위치를 변경해서 연결
* Stack / Queue 등에서 사용되는 Linked List 

![Singly](./Img/Singly.png)

**Code**

```c++
struct node
{
    int data;
    node *next;
};

template <typename T>
class linked_list{
    node *head, *tail;
    int _size;
public :
    linked_list()
    {
        head = (node*)malloc(sizeof(node));
        tail = (node*)malloc(sizeof(node));
        head->next = tail;
        _size = 0;
    }
    ~linked_list()
    {
        clear();
        free(head);
        free(tail);
    }
    void addFront(T value){
        node* newnode = (node*)malloc(sizeof(node));
        newnode->data = value;
        newnode->next = head->next;
        head->next = newnode;
        _size++;
    }
    void addBack(T value){
        node *newnode = (node *)malloc(sizeof(node));
        newnode->data = value;
        newnode->next = tail;
        node* back = head; 
        while(back->next != tail) {
            back = back->next; // singly..
        }
        back->next = newnode;
        _size++;
    }
    int search_first_index(T value){
        int idx = 0;
        node* tmp = head;
        while (tmp->next != tail){
            tmp = tmp->next;
            idx++;
            if (tmp->data == value) return idx;
        }
        return -1;
    }    
    void remove_first_node(T value){
        node* tmp = head;
        while (tmp->next != tail){
            if (tmp->next->data == value){
                node* delnode = tmp->next;
                tmp->next = delnode->next;
                free(delnode);
                _size--;
                return;
            }
            tmp = tmp->next;
        }
        cout <<"There's no component " << value << endl;
        return;
    }
    void printall(){
        node* tmp = head->next;
        if (empty()) return;
        while(tmp != tail){
            cout << tmp->data << " ";
            tmp = tmp->next;
        }
        cout << endl;
    }
    bool empty(){return !_size;}
    int size() {return _size;}
    void clear(){
        node* tmp = head->next;
        while (!empty()){
            node* delnode = tmp;
            tmp = delnode->next;
            free(delnode);
            _size--;
        }
        head->next = tail;
    }
};
```

### 원형 링크드리스트 (Circular Linked List)

* 단순 링크드리스트에서 Head / Tail의 data에 값 추가
* 아래 예시는 Tail만 기입했지만, Head도 추가하여 리스트 최상단에 Data 추가할 수 있음

![Circular](./Img/Circular.png)

**Code**

```c++

```

### 이중 링크드리스트 (Doubly Linked List)

* asd

**Code**

```c++
```



**Code**

```c++
//--------------------------------------------------------------------------------------------

#include <stdio.h>
#include <malloc.h>

typedef struct node {
    struct node *pre;
    int data;
    struct node *next;
}node;
node *head;
node *t;

void createnodes(int n, char *start) {
    t = (node *)malloc(sizeof(node));
    t->data = 0;
    head = t;
    for (int i = 1; i <= n; i++)
    {
        t->next = (node *)malloc(sizeof(node));
        t->next->pre = t;
        t = t->next;
        t->data = start[i - 1];
    }
    t->next = NULL;
}

void insertnode(char x, node *t) {
    node *insert = (node *)malloc(sizeof(node));
    insert->pre = t;
    if (t->next == NULL)
        insert->next = NULL;
    else
    {
        insert->next = t->next;
        t->next->pre = insert;
    }
    t->next = insert;
    insert->data = x;
}

// t번째 node를 제거
node *deletenode(node *t){
    node *d;
    d = t;
    if (t->next != NULL)
    {
        t->pre->next = t->next;
        t->next->pre = t->pre;
    }
    else
        t->pre->next = NULL;
    t = t->pre;
    free(d);
    return t;
}

// 더미 노드를 이용한 이중 링크드 리스트
//--------------------------------------------------------------------------------------------
#include <iostream>
#include <cstdio>
 
using namespace std;
 
class NODE {
    friend class LIST;

private:
    int data;
    NODE *left;
    NODE *right;
};
 
class LIST {
private:
    int sz;
    NODE *head;
    NODE *tail;

public:
    LIST()
    {
        //cout << "\n\n생성자 호출\n\n" << endl;
        sz = 0;
        NODE *dummyHead = new NODE;
        NODE *dummyTail = new NODE;

        dummyHead->left = dummyHead->right = NULL;
        dummyTail->left = dummyTail->right = NULL;

        head = dummyHead;
        tail = dummyTail;
    }

    ~LIST()
    {
        init();
        delete head;
        delete tail;
    }

    void init()
    {
        NODE *pos = head;
        while (pos->right != NULL)
        {
            NODE *delNode = pos;
            pos = pos->right;

            delete delNode;
        }
        delete tail; // 마지막 tail이 삭제되지 않았다.

        // 더미노드 새로 생성(생성자와 동일)
        NODE *dummyHead = new NODE;
        NODE *dummyTail = new NODE;

        dummyHead->left = dummyHead->right = NULL;
        dummyTail->left = dummyTail->right = NULL;

        head = dummyHead;
        tail = dummyTail;
        sz = 0;
    }
    void insert(int val)
    {
        // 리스트가 형성되어 있지 않았을 때
        if (head->right == NULL)
        {
            NODE *newNode = new NODE;
            newNode->data = val;

            newNode->left = head;
            head->right = newNode;

            newNode->right = tail;
            tail->left = newNode;
        }

        else
        {
            NODE *newNode = new NODE;
            newNode->data = val;

            newNode->left = tail->left;
            tail->left->right = newNode;

            newNode->right = tail;
            tail->left = newNode;
        }
        sz++;
    }
    void del(int val)
    {
        NODE *pos = head;
        bool isFind = false;
        while (pos->right != NULL)
        {
            if (pos->data == val)
            {
                pos->left->right = pos->right;
                pos->right->left = pos->left;
                delete pos;
                isFind = true;
                break;
            }
            pos = pos->right;
        }

        if (isFind)
            sz--;
        else
            cout << "삭제할 데이터가 없습니다." << endl;
    }

    void all()
    {
        NODE *pos = head;
        while (pos != NULL)
        {
            // 더미노드는 출력하지 않는다.
            if (!(pos == head || pos == tail))
                cout << pos->data << " ";

            pos = pos->right;
        }
        cout << endl;
    }

    int size()
    {
        return sz;
    }
};
int main()
{
    LIST list;
    while (1)
    {
        int num;
        cout << "1 :: 초기화\n2 :: 추가\n3 :: 삭제\n4 :: 전체출력\n5 :: 총 개수\n6 :: 종료\n입력 :: ";
        cin >> num;

        if (num == 1)
            list.init();

        else if (num == 2)
        {
            int val;
            cout << "값 :: ";
            cin >> val;
            list.insert(val);
        }

        else if (num == 3)
        {
            int val;
            cout << "값 :: ";
            cin >> val;
            list.del(val);
        }

        else if (num == 4)
            list.all();

        else if (num == 5)
            cout << list.size() << endl;

        else if (num == 6)
            break;

        cout << endl;
    }

    return 0;
}

```

