#include <malloc.h>
#include <stdio.h>

class treeNode
{
	friend class tree;
private:
	int value;
	treeNode* left, *right;
	treeNode(int val) : value(val), left(NULL), right(NULL) {}   //������
};

class tree
{
private:
	void recursiveInsert(treeNode*&, int);
	void recursiveRemove(treeNode*&, int);
	void preorderRecursivePrint(treeNode*);
	void postorderRecursivePrint(treeNode*);
	void inorderRecursivePrint(treeNode*);
public:
	treeNode* root;
	tree() : root(NULL) { }   //������
	void insert(int);
	void remove(int);
	void preorderPrint();
	void postorderPrint();
	void inorderPrint();
};


void tree::recursiveInsert(treeNode*& node, int val)
{
	if (node == NULL)
		node = new treeNode(val);   //Ž���ϰ� �ִ� ��尡 NULL�̸� ���� �����(����)

	else if (val > node->value)
		recursiveInsert(node->right, val);   //������ ���� ����� ������ ũ�� ������ Child�� Ž��

	else if (val < node->value)
		recursiveInsert(node->left, val);   //������ ���� ����� ������ ������ ���� Child�� Ž��
}

void tree::recursiveRemove(treeNode*& node, int val)
{
	treeNode* removal = new treeNode(0);

	if (node == NULL)
		return;      //ã�������� ��� �����ؼ� �Լ�����
	else if (val > node->value)
		recursiveRemove(node->right, val);   //������ ���� ����� ������ ũ�� ������ Child�� Ž��
	else if (val < node->value)
		recursiveRemove(node->left, val);   //������ ���� ����� ������ ������ ���� Child�� Ž��

	else //������ ��带 ã����(���� 3���� ���� ������ �ִ�)
	{
		if (node->left == NULL && node->right == NULL) //��� 1: ����� Child�� ������
		{
			delete node;
			node = NULL;
		}

		else if (node->left == NULL)   //��� 2-1: ����� Child�� ������ �ϳ��� ��
		{
			removal = node;
			node = node->right;
			delete removal;
		}
		else if (node->right == NULL)   //��� 2-2: ����� Child�� ���� �ϳ��� ��
		{
			removal = node;
			node = node->left;
			delete removal;
		}
		else                     //��� 3: ����� Child�� �ΰ��� ��
		{
			removal = node->right;
			while (removal->left != NULL)   //����� ������ Subtree���� �ּҰ��� ���� ��带 ã�´�.
				removal = removal->left;

			int minVal = removal->value;   //�ּҰ������ ���� ���
			recursiveRemove(root, minVal);   //�ּҰ���带 ����
			node->value = minVal;  //����� �ּҰ��� "���� ������ ���� ���� ���"�� ���� ���
		}
	}

}

void tree::preorderRecursivePrint(treeNode* node)
{
	if (node != NULL)
	{
		printf("%d\n", node->value);
		preorderRecursivePrint(node->left);
		preorderRecursivePrint(node->right);
	}
}

void tree::inorderRecursivePrint(treeNode* node)
{
	if (node != NULL)
	{
		inorderRecursivePrint(node->left); //Left Child�� ���������� �ִ��� �������� Ž���Ѵ�.
		printf("%d\n", node->value);     //����Ѵ�.   
		inorderRecursivePrint(node->right);//�� ���� Right Child�� Ž���Ѵ�.
	}
}

void tree::postorderRecursivePrint(treeNode* node)
{
	if (node != NULL)
	{
		postorderRecursivePrint(node->left); //Left Child�� ���������� �ִ��� �������� Ž���Ѵ�.
		postorderRecursivePrint(node->right);//�� ���� Right Child�� Ž���Ѵ�.
		printf("%d\n", node->value);       //����Ѵ�.   
	}
}

void tree::insert(int val)
{
	recursiveInsert(root, val);
}

void tree::remove(int val)
{
	recursiveRemove(root, val);
}

void tree::preorderPrint()
{
	printf("PREORDER\n");
	preorderRecursivePrint(root);
}

void tree::inorderPrint()
{
	printf("INORDER");
	inorderRecursivePrint(root);
}

void tree::postorderPrint()
{
	printf("POST ORDER\n");
	postorderRecursivePrint(root);
}

tree aa[101];

int main() {
	aa[0].insert(4);
	aa[0].insert(2);
	aa[0].insert(3);
	aa[0].insert(1);
	aa[1].insert(5);
	aa[1].insert(13);
	aa[1].insert(6);
	aa[1].insert(12);
	aa[1].insert(7);
	aa[0].preorderPrint();
	aa[1].preorderPrint();
}
