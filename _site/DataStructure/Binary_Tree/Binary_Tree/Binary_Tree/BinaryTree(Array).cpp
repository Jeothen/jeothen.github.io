#include <stdio.h>
#include <malloc.h>
#pragma warning(disable:4996)

typedef struct node {
	char word;
	node *left;
	node *right;
}node;

node *nodes;

void PreOrder(node *r) {
	printf("%c", r->word);
	if (r->left) PreOrder(r->left);
	if (r->right) PreOrder(r->right);
}

void InOrder(node *r) {
	if (r->left) InOrder(r->left);
	printf("%c", r->word);
	if (r->right) InOrder(r->right);
}

void PostOrder(node *r) {
	if (r->left) PostOrder(r->left);
	if (r->right) PostOrder(r->right);
	printf("%c", r->word);
}

int main() {
	freopen("input.txt", "r", stdin);
	int n;
	scanf("%d", &n);
	// ��ũ�� ����Ʈ�� �迭ó�� ��������� ���� �迭�� ��� ����
	// typedef ���� �� node �� arr��ŭ ���� �� 
	// ���ʰ� ������ �ڽĿ� �ε����� ����ϸ� ��
	nodes = (node *)malloc(sizeof(node)*n);
	char a, l, r;
	int cnt;
	for (int i = 0; i < n; i++) {
		scanf(" %c %c %c", &a, &l, &r);
		cnt = a - 'A';
		nodes[cnt].word = a;
		if (l == '.') nodes[cnt].left = NULL;
		else nodes[cnt].left = &nodes[l - 'A'];
		if (r == '.') nodes[cnt].right = NULL;
		else nodes[cnt].right = &nodes[r - 'A'];
	}
	PreOrder(&nodes[0]);
	printf("\n");
	InOrder(&nodes[0]);
	printf("\n");
	PostOrder(&nodes[0]);

}