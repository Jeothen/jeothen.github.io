---
sort: 2
---

# Binary Search Tree





**Code**

```c++
#include <malloc.h>
#include <stdio.h>

typedef struct NodeStruct
{
	int value;
	struct NodeStruct* leftChild;
	struct NodeStruct* rightChild;
}Node;

Node* root = NULL;

Node* BST_insert(Node* root, int value)
{
	if (root == NULL)
	{
		root = (Node*)malloc(sizeof(Node));
		root->leftChild = root->rightChild = NULL;
		root->value = value;
		return root;
	}
	else
	{
		if (root->value > value)
			root->leftChild = BST_insert(root->leftChild, value);
		else
			root->rightChild = BST_insert(root->rightChild, value);
	}
	return root;
}
Node* findMinNode(Node* root)
{
	Node* tmp = root;
	while (tmp->leftChild != NULL)
		tmp = tmp->leftChild;
	return tmp;
}
Node* BST_delete(Node* root, int value)
{
	Node* tNode = NULL;
	if (root == NULL)
		return NULL;

	if (root->value > value)
		root->leftChild = BST_delete(root->leftChild, value);
	else if (root->value < value)
		root->rightChild = BST_delete(root->rightChild, value);
	else
	{
		// ¿⁄Ωƒ ≥ÎµÂ∞° µ— ¥Ÿ ¿÷¿ª ∞ÊøÏ
		if (root->rightChild != NULL && root->leftChild != NULL)
		{
			tNode = findMinNode(root->rightChild);
			root->value = tNode->value;
			root->rightChild = BST_delete(root->rightChild, tNode->value);
		}
		else
		{
			tNode = (root->leftChild == NULL) ? root->rightChild : root->leftChild;
			free(root);
			return tNode;
		}
	}

	return root;
}
Node* BST_search(Node* root, int value)
{
	if (root == NULL)
		return NULL;

	if (root->value == value)
		return root;
	else if (root->value > value)
		return BST_search(root->leftChild, value);
	else
		return BST_search(root->rightChild, value);
}


void BST_print(Node* root)
{
	if (root == NULL)
		return;
	printf("%d ", root->value);
	BST_print(root->leftChild);
	BST_print(root->rightChild);
}

int main() {
	root = BST_insert(root, 5);
	root = BST_insert(root, 3);
	root = BST_insert(root, 7);
	root = BST_insert(root, 1);
	root = BST_insert(root, 9);
	root = BST_insert(root, 6);
	root = BST_delete(root, 7);
	BST_print(root);
}





```





```c++
#include <malloc.h>
#include <stdio.h>

class treeNode
{
	friend class tree;
private:
	int value;
	treeNode* left, *right;
	treeNode(int val) : value(val), left(NULL), right(NULL) {}   //ª˝º∫¿⁄
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
	tree() : root(NULL) { }   //ª˝º∫¿⁄
	void insert(int);
	void remove(int);
	void preorderPrint();
	void postorderPrint();
	void inorderPrint();
};


void tree::recursiveInsert(treeNode*& node, int val)
{
	if (node == NULL)
		node = new treeNode(val);   //≈Ωªˆ«œ∞Ì ¿÷¥¬ ≥ÎµÂ∞° NULL¿Ã∏È ªı∑Œ ∏∏µÁ¥Ÿ(ª¿‘)

	else if (val > node->value)
		recursiveInsert(node->right, val);   //ª¿‘«“ ∞™¿Ã ≥ÎµÂ¿« ∞™∫∏¥Ÿ ≈©∏È ø¿∏•¬  Child∏¶ ≈Ωªˆ

	else if (val < node->value)
		recursiveInsert(node->left, val);   //ª¿‘«“ ∞™¿Ã ≥ÎµÂ¿« ∞™∫∏¥Ÿ ¿€¿∏∏È øﬁ¬  Child∏¶ ≈Ωªˆ
}

void tree::recursiveRemove(treeNode*& node, int val)
{
	treeNode* removal = new treeNode(0);

	if (node == NULL)
		return;      //√£¡ˆ∏¯«ﬂ¿ª ∞ÊøÏ ∏Æ≈œ«ÿº≠ «‘ºˆ¡æ∑·
	else if (val > node->value)
		recursiveRemove(node->right, val);   //ªË¡¶«“ ∞™¿Ã ≥ÎµÂ¿« ∞™∫∏¥Ÿ ≈©∏È ø¿∏•¬  Child∏¶ ≈Ωªˆ
	else if (val < node->value)
		recursiveRemove(node->left, val);   //ªË¡¶«“ ∞™¿Ã ≥ÎµÂ¿« ∞™∫∏¥Ÿ ¿€¿∏∏È øﬁ¬  Child∏¶ ≈Ωªˆ

	else //ªË¡¶«“ ≥ÎµÂ∏¶ √£æ“¿Ω(¿Ã¡¶ 3∞°¡ˆ ∞ÊøÏ∑Œ ≥™¥≠ºˆ ¿÷¥Ÿ)
	{
		if (node->left == NULL && node->right == NULL) //∞ÊøÏ 1: ≥ÎµÂ¿« Child∞° æ¯¿ª∂ß
		{
			delete node;
			node = NULL;
		}

		else if (node->left == NULL)   //∞ÊøÏ 2-1: ≥ÎµÂ¿« Child∞° ø¿∏•¬  «œ≥™¿œ ∂ß
		{
			removal = node;
			node = node->right;
			delete removal;
		}
		else if (node->right == NULL)   //∞ÊøÏ 2-2: ≥ÎµÂ¿« Child∞° øﬁ¬  «œ≥™¿œ ∂ß
		{
			removal = node;
			node = node->left;
			delete removal;
		}
		else                     //∞ÊøÏ 3: ≥ÎµÂ¿« Child∞° µŒ∞≥¿œ ∂ß
		{
			removal = node->right;
			while (removal->left != NULL)   //≥ÎµÂ¿« ø¿∏•¬  Subtreeø°º≠ √÷º“∞™¿ª ∞°¡¯ ≥ÎµÂ∏¶ √£¥¬¥Ÿ.
				removal = removal->left;

			int minVal = removal->value;   //√÷º“∞™≥ÎµÂ¿« ∞™¿ª πÈæ˜
			recursiveRemove(root, minVal);   //√÷º“∞™≥ÎµÂ∏¶ ªË¡¶
			node->value = minVal;  //πÈæ˜«— √÷º“∞™¿ª "Ω«¡¶ ªË¡¶µ» ∞™¿ª ∞°¡¯ ≥ÎµÂ"¿« ∞™ø° µ§æÓæ∏
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
		inorderRecursivePrint(node->left); //Left Child∞° æ¯¿ª∂ß±Ó¡ˆ √÷¥Î«— øﬁ¬ ¿∏∑Œ ≈Ωªˆ«—¥Ÿ.
		printf("%d\n", node->value);     //√‚∑¬«—¥Ÿ.   
		inorderRecursivePrint(node->right);//±◊ ¥Ÿ¿Ω Right Child∏¶ ≈Ωªˆ«—¥Ÿ.
	}
}

void tree::postorderRecursivePrint(treeNode* node)
{
	if (node != NULL)
	{
		postorderRecursivePrint(node->left); //Left Child∞° æ¯¿ª∂ß±Ó¡ˆ √÷¥Î«— øﬁ¬ ¿∏∑Œ ≈Ωªˆ«—¥Ÿ.
		postorderRecursivePrint(node->right);//±◊ ¥Ÿ¿Ω Right Child∏¶ ≈Ωªˆ«—¥Ÿ.
		printf("%d\n", node->value);       //√‚∑¬«—¥Ÿ.   
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

```

