#include <stdio.h>
#include <malloc.h>
#pragma warning(disable:4996)

typedef struct node {
	int num;
	node *left;
	node *right;
}node;

node *root;

// Ʈ���� �ʱ�ȭ
void initTree(int data) {
	node *n;
	n = (node *)malloc(sizeof(node));
	root = n;
	root->num = data;
	n->left = NULL;
	n->right = NULL;
}

// �ڽ� ��� ����

node *addchild(node *parent, int data) {
	if ((parent->left != NULL) && (parent->right != NULL)) return 0;
	node *n;
	n = (node *)malloc(sizeof(node));
	n->left = NULL;
	n->right = NULL;
	n->num = data;
	if (parent->left == NULL) parent->left = n;
	else if (parent->right == NULL) parent->right = n;
	return n;
}

void PreOrder(node *r) {
	printf("%d ", r->num);
	if (r->left) PreOrder(r->left);
	if (r->right) PreOrder(r->right);
}

void InOrder(node *r) {
	if (r->left) InOrder(r->left);
	printf("%d ", r->num);
	if (r->right) InOrder(r->right);
}

void PostOrder(node *r) {
	if (r->left) PostOrder(r->left);
	if (r->right) PostOrder(r->right);
	printf("%d ", r->num);
}

int main() {
	initTree(1);
	node *l = addchild(root, 2);
	node *r = addchild(root, 3);
	addchild(l, 4);
	addchild(l, 5);
	addchild(r, 6);
	addchild(r, 7);
	printf("PreOrder �Ѹ� ���� ������ \n");
	PreOrder(root);
	printf("\n");
	printf("Inorder ���� �Ѹ� ������ \n");
	InOrder(root);
	printf("\n");
	printf("PostOrder ���� ������ �Ѹ� \n");
	PostOrder(root);
	printf("\n");
}