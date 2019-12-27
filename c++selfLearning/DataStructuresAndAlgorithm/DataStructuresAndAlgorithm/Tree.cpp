#include <iostream>
#include <vector>

typedef struct BiTNode {
	int data;
	BiTNode *lchild;
	BiTNode *rchild;
};

void PreOrderTraverse(BiTNode *T)
{
	if (T == NULL)
		return;
	std::cout << T->data << std::endl;
	PreOrderTraverse(T->lchild);
	PreOrderTraverse(T->rchild);
}

void InOrderTraverse(BiTNode *T)
{
	if (T == NULL)
		return;
	PreOrderTraverse(T->lchild);
	std::cout << T->data << std::endl;
	PreOrderTraverse(T->rchild);
}

void PostOrderTraverse(BiTNode *T)
{
	if (T == NULL)
		return;
	PreOrderTraverse(T->lchild);
	PreOrderTraverse(T->rchild);
	std::cout << T->data << std::endl;
}

void LayerOrderTraverse(BiTNode *T)
{
	if (T == NULL)
		return;
	PreOrderTraverse(T->lchild);
	PreOrderTraverse(T->rchild);
	std::cout << T->data << std::endl;
}

class AVLTreeNode {
public:
	int key;              
	int bf;         
	AVLTreeNode *left;  
	AVLTreeNode *right; 

	AVLTreeNode(int value) : key(value), bf(0), left(NULL), right(NULL) {}
};

void insertNode(AVLTreeNode* pHead, AVLTreeNode* pChild)
{
	if (pChild->key < pHead->key)
	{
		pHead->bf++;
		if (pHead->left == NULL)
		{
			pHead->left = pChild;
			return;
		}
		insertNode(pHead->left, pChild);
	}
	else
	{
		pHead->bf--;
		if (pHead->right == NULL)
		{
			pHead->right = pChild;
			return;
		}
		insertNode(pHead->right, pChild);
	}
}

AVLTreeNode *head = new AVLTreeNode(3);

int main()
{
	std::vector<int> res = { 2,1,4,5,6,7,10,9,8 };
	for (int i : res)
	{
		AVLTreeNode *child = new AVLTreeNode(i);
		insertNode(head, child);

	}
	
	return 0;

}
