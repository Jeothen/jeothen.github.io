---
sort: 8
---

# Hash

* Key, Value로 데이터를 저장하며 빠른 속도로 Value를 검색/삽입/삭제 할 수 있는 구조
* 1:1 Mapping되어 있어 검색/삽입/삭제 시 시간복잡도는 평균 O(1)이라고 하지만, Key의 길이를 Index로 계산하는 과정이나 충돌이 났을 때 이동하는 과정을 고려해야 됨
* Key를 Hash Code에 적용하여 Index를 만들고 Hash Table 검색/저장/삭제 기능 수행
* 다른 Key라도 동일한 Index를 만들어지는 경우를 해결하기 위해, Open Addressing과 Chaining 기법이 많이 사용 됨

**Open Addressing**

* Hash Table에서 충돌이 났을 때, 비어있는 Index로 이동하는 기법
* 아래 예시는 충돌이 났을 때 +1을 했지만, 일반적으로 1,4,9와 같이 $$n^2$$ 이나 난수를 이용하여 충돌의 횟수를 줄임
* 테이블의 크기는 충돌을 고려하여 전체 Key의 수보다 크게 설정

![Open_Addressing](./Img/Open_Addressing.png)

**Code**

```c++

```



**Chaning**

* Hash 충돌이 났을 때, Index를 그대로 유지한 채 새로운 노드를 생성
* 연쇄적으로 연결을 하며, CRUD 할 때도 첫 Value에서 시작하면서 이동
* Linked로 연결되어 있기 때문에, 중간의 값을 삭제할 때는 이전의 value와 다음 value를 연결해야 됨
* 테이블의 크기는 전체 key의 숫자와 동일하게 맞추는 게 일반적임

![Chaining](./Img/Chaining.png)

**Code**

```c++
```



**Code**

```c++
#include <iostream>
#pragma warning(disable:4996)

#define max 200001

int n, namecount;

typedef struct node {
	node* next;
	int index;
	char* name;
}node;

node arr[max];

int idx = 0;


int hashcode(char* str) {
	int hash = 0;
	for (int i = 0; str[i] != '\0'; i++) {
		hash = (hash * 7 + 5 * str[i]) % max;
	}
	return hash;
}

node* h[max];

int get(char* name) {
	int hash = hashcode(name);
	node* curr = h[hash];
	while (curr) {
		int issame = 1;
		for (int i = 0; i < 21; i++) {
			if (name[i] != curr->name[i]) {
				issame = 0;
				break;
			}
		}
		if (issame) return curr->index;
		curr = curr->next;
	}
}

node* createnode(char* name, int index) {
	node* newnode = &arr[idx++];
	newnode->name = name;
	newnode->index = index;
	return newnode;
}

void put(char* name, int index) {
	int hash = hashcode(name);
	node* ne = createnode(name, index);
	if (!h[hash]) h[hash] = ne;
	else {
		ne->next = h[hash];
		h[hash] = ne;
	}
}

int iscontain(char* name) {
	int hash = hashcode(name);
	if (!h[hash]) {
		return 0;
	}
	else {
		node* curr = h[hash];
		while (curr) {
			int issame = 1;
			for (int i = 0; i < 21; i++) {
				if (name[i] != curr->name[i]) {
					issame = 0;
					break;
				}
			}
			if (issame) return 1;
			curr = curr->next;
		}
		return 0;
	}
}

int parent[max];
int size[max];

int find(int c) {
	if (parent[c] == c) return c;
	return parent[c] = find(parent[c]);
}

int unite(int a, int b) {
	int pa = find(a);
	int pb = find(b);

	if (pa != pb) {
		parent[pb] = pa;
		size[pa] += size[pb];

	}
	return size[pa];
}


int main() {
	int te, count;
	scanf("%d", &te);
	for (int tc = 1; tc <= te; tc++) {
		count = 0;
		scanf("%d", &n);
		for (int i = 0; i < max; i++) {
			parent[i] = i;
			size[i] = 1;
		}
		for (int i = 0; i < n; i++) {
			char* a = (char*)malloc(sizeof(char) * 21);
			char* b = (char*)malloc(sizeof(char) * 21);
			scanf("%s %s", a, b);
			if (iscontain(a) == 0)
				put(a, namecount++);
			if (iscontain(b) == 0)
				put(b, namecount++);
			count = unite(get(a), get(b));
			printf("%d\n", count);
		}
	}
}

```



