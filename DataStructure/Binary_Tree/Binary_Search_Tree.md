---
sort: 1
---

# Binary Search Tree

* 아래와 같은 특징을 갖는 Binary Tree
  * 왼쪽 자식 노드의 값은 부모 노드보다 작음
  * 오른쪽 자식 노드의 값은 부모 노드보다 큼
  * 중복된 값을 허용하지 않음
  * Leaf Node를 제외한 모든 노드가 Binary Tree 형태로 구성됨 
* 기존의 Binary Tree에서 특정 값을 탐색하기 위해서는 최대 $$O(N)$$ 의 시간복잡도가 소요되기 때지만, BST에서는 평균 $$O(logN)$$ 으로 계산할 수 있음
  * Skewed 형태로 BST가 만들어지는 경우 탐색에 많은 시간이 소요되기 때문에 AVL이나 Red-Black처럼 Balanced Tree로 구현 필요
* 탐색을 root부터 해야되는데, 사용할 때마다 변수에 root를 추가하기 번거러움
  * public method를 호출할 때 private method에 root를 적용하여 실행

**Code**

```c++
template <typename T>
class BST
{
    struct treeNode{
        int value;
        treeNode *left, *right;
        treeNode(T val) : value(val), left(NULL), right(NULL) {}
    };
public:
    treeNode *root;
    BST() : root(NULL) {}
    bool insert(T);
    bool find(T);
    void remove(T);
    void preorder();
    void postorder();
    void inorder();
private:
    bool private_insert(treeNode *&, T);
    bool private_find(treeNode *&, T);
    bool private_remove(treeNode *&, T);
    void private_Preorder(treeNode *);
    void private_Inorder(treeNode *);
    void private_Postorder(treeNode *);
};

template <typename T>
bool BST<T>::private_insert(treeNode *&node, T val)
{
    if (node == NULL) {
        node = new treeNode(val);
        return true;
    }
    else if (val > node->value) return private_insert(node->right, val);
    else if (val < node->value) return private_insert(node->left, val);
    else {
        cout<<  val<<" : Already inserted\n";
        return false;
    }   
}

template <typename T>
bool BST<T>::private_find(treeNode *&node, T val)
{
    if (node == NULL) return false;
    else if (val > node->value) return private_find(node->right, val);
    else if (val < node->value) return private_find(node->left, val);
    else return true;
}

template <typename T>
bool BST<T>::private_remove(treeNode *&node, T val)
{
    if (node == NULL) return false; // not found in subtree
    else if (val > node->value) return private_remove(node->right, val); 
    else if (val < node->value) return private_remove(node->left, val); 
    else { // find value
        if (node->left == NULL && node->right == NULL) { // leaf
            delete node;
            node = NULL;
        }
        else if (node->left == NULL) { // only right subtree
            treeNode* removal = node;
            node = node->right;
            delete removal;
        }
        else if (node->right == NULL)  { // only left subtree
            treeNode* removal = node;
            node = node->left;
            delete removal;
        }
        else  {
            treeNode* removal = node->right;
            while (removal->left != NULL)  removal = removal->left;
            int minVal = removal->value;
            private_remove(root, minVal);  
            node->value = minVal;
        }
        return true;
    }
}

template <typename T>
void BST<T>::private_Preorder(treeNode *node)
{
    if (node != NULL)
    {
        cout << node->value << " ";
        private_Preorder(node->left);
        private_Preorder(node->right);
    }
}

template <typename T>
void BST<T>::private_Inorder(treeNode *node)
{
    if (node != NULL)
    {
        private_Inorder(node->left);
        cout << node->value << " ";
        private_Inorder(node->right);       
    }
}

template <typename T>
void BST<T>::private_Postorder(treeNode *node)
{
    if (node != NULL)
    {
        private_Postorder(node->left);
        private_Postorder(node->right);
        cout << node->value << " ";
    }
}
template <typename T>
bool BST<T>::insert(T val)
{
    return private_insert(root, val);
}

template <typename T>
bool BST<T>::find(T val)
{
    return private_find(root, val);
}

template <typename T>
void BST<T>::remove(T val) {
    if (!private_remove(root, val)){
        cout << "Not Found value : " << val << endl;
    }
}

template <typename T>
void BST<T>::preorder()
{
    printf("PREORDER\n");
    private_Preorder(root);
    cout <<"\n";
}
template <typename T>
void BST<T>::inorder()
{
    printf("INORDER\n");
    private_Inorder(root);
    cout << "\n";
}
template <typename T>
void BST<T>::postorder()
{
    printf("POST ORDER\n");
    private_Postorder(root);
    cout << "\n";
}
```

