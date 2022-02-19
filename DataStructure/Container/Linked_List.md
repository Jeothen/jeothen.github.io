---
sort: 1
---

# Linked List

### 단순 링크드리스트 (Singly Linked List) 

* Asd

**Code**

```c++

```

### 원형 링크드리스트 (Circular Linked List)

* asdasd

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
#include <stdlib.h>
 
typedef struct _node{
    int i;                 //노드의 구성요소 첫번째. 값
    struct _node *nextadd; //노드의 구성요소 두번째. 다음 값을 가리키는 주소
}NODE;
 
NODE *firstnode=NULL;//첫번째 노드
NODE *lastnode=NULL;//마지막 노드
 
void add(int num){//맨 뒤에 추가함
    NODE *newnode = (NODE *)malloc(sizeof(NODE)); //먼저 생성하고 보자
    newnode->i = num;
    newnode->nextadd = NULL;
    if (firstnode == NULL)
    { //처음으로 이 함수가 실행되면
        firstnode = newnode;
        lastnode = newnode;
    }
    else
    {                                //처음이 아니면 뒤에 계속 추가. lastnode가 계속 바뀐다
        lastnode->nextadd = newnode; //원래 lastnode가 가리키는 곳이 새로 생성된 노드의 값을 가리키게 한 후,
        lastnode = newnode;          //방금 생성한 노드가 맨 끝자리에 추가했으므로 방금 생성한 노드가 lastnode가 된다.
    }
}
 
void erase(int num){
    NODE *temp = firstnode->nextadd;
    if (firstnode == NULL)
    {
        printf("값이 없는데 지울수 있을까요? => 지울수 없습니다.\n");
        return;
    }
    if (firstnode->i == num)
    { //첫번째 노드의 값==입력값

        firstnode = firstnode->nextadd;
        free(temp);
    }
    else
    {
        NODE *before = firstnode;
        while (1)
        {
            if (temp->i == num)
            {
                NODE *node_free = temp;
                before->nextadd = temp->nextadd;
                free(node_free);
                break;
            }
            else
            {
                if (temp->nextadd == NULL)
                {
                    printf("값이 없는데요? 이게 어터케 된 일이죠? 네?\n");
                    break;
                }
                before = before->nextadd;
                temp = temp->nextadd;
            }
        }
    }
    return;
}
 
void show(){
    int i;
    if (firstnode == NULL)
    {
        printf("값이 없어용\n");
        return;
    }
    else
    {
        NODE *temp = firstnode;
        for (i = 1; temp != NULL; ++i)
        {
            printf("%d번째 값 : %d\n", i, temp->i);
            temp = temp->nextadd;
        }
    }
}
 
int main(){
    int select, i, input, input_num;
    while (1)
    {
        printf("\n\n0 : 종료\n");
        printf("1 : 노드 생성\n");
        printf("2 : 노드 삭제\n");
        printf("3 : 노드 보기\n");
        printf("0~3 선택 : ");
        scanf("%d", &select);

        if (select == 0)
        {
            return 0;
        }
        else if (select == 1)
        {
            printf("몇개 생성? : ");
            scanf("%d", &input);
            for (i = 1; i <= input; ++i)
            {
                printf("%d번째 생성중입니다....\n값을 입력해주세요 : ", i);
                scanf("%d", &input_num);
                add(input_num);
            }
        }
        else if (select == 2)
        {
            printf("몇개 삭제? : ");
            scanf("%d", &input);
            for (i = 1; i <= input; ++i)
            {
                printf("%d번째 삭제중입니다....\n지울 값을 입력해주세요 : ", i);
                scanf("%d", &input_num);
                erase(input_num);
            }
        }
        else if (select == 3)
        {
            show();
        }
    }
}

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

