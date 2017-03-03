#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include "avltree.h"
#define HEIGHT(p)    ( (p==NULL) ? 0 : (((Node *)(p))->height) )
#define MAX(a, b)    ( (a) > (b) ? (a) : (b) )
#define N 10000

int main()
{
	int arr[N];
	int i;
	AVLTree root = NULL;
	int ibeg, iend;

	//�������������
	srand(time(NULL));

	//��ʼ����������
	for (i = 0; i < N; i++)
		arr[i] = rand() % 10000;

	//printf("�������������Ԫ��: ");

	//��ʼ��ʱ
	ibeg = clock();
	for (i = 0; i < N; i++)
	{
		//printf("%d ", arr[i]);
		root = avltree_insert(root, arr[i]);
	}
	iend = clock();
	printf("\nAVL����һ������ %d ��������ʱ %d ms \n", N, iend - ibeg);

	printf("���ĸ߶�Ϊ: %d\n", avltree_height(root));
	//printf("��AVL������ϸ��Ϣ����: \n");
	//print_avltree(root, root->key, 0);

	printf("���ڰ����������е�˳������ɾ��AVL���Ľڵ�...");
	ibeg = clock();
	for (i = 0; i < N; i++)
	{
		root = avltree_delete(root, arr[i]);
	}
	iend = clock();
	printf("\nAVL����һ��ɾ�� %d ��������ʱ %d ms \n", N, iend - ibeg);

	/*
	printf("\nɾ����������ϸ��Ϣ����: \n");
	if (root)
	{
		//print_avltree(root, root->key, 0);
		destroy_avltree(root);
	}
	else
	printf("��Ϊ�գ���\n");
	*/
	return 0;
}

/*
* (�ݹ�ʵ��)����"AVL��x"�м�ֵΪkey�Ľڵ�
*/
Node* avltree_search(AVLTree x, Type key)
{
	if (x == NULL || x->key == key)
		return x;

	if (key < x->key)
		return avltree_search(x->left, key);
	else
		return avltree_search(x->right, key);
}

/*
����x�ľ���ֵ
*/
int iabs(int x)
{
	if (x >= 0)
		return x;
	else
		return -x;
}

/*
*ǰ��������x������������ΪAVL�����ж���xΪ������
*�Ƿ�ҲΪAVL�������ǣ��򷵻�true�����򷵻�false
*/
bool IsAVL(Node *x)
{
	int lheight = x->left->height;
	int rheight = x->right->height;
	if (iabs(lheight - rheight) <= 1)
		return true;
	else
		return false;
}

/*
*�õ�x���������ĸ߶�
*/
int GetLeftHeight(Node * x)
{
	if (x == NULL)
		return 0;
	if (x->left == NULL)
		return 1;
	return x->left->height;
}

/*
*�õ�x���������ĸ߶�
*/
int GetRightHeight(Node * x)
{
	if (x == NULL)
		return 0;
	if (x->right == NULL)
		return 1;
	return x->right->height;
}

/*
*��xΪ����������������
*/
Node * iLeftRotate(Node * x)
{
	Node * xright = x->right;
	x->right = xright->left;
	x->height = MAX(GetLeftHeight(x), GetRightHeight(x)) + 1;
	xright->left = x;
	xright->height = MAX(GetLeftHeight(xright), GetRightHeight(xright)) + 1;
	return xright;
}

/*
*��xΪ����������������
*/
Node * iRightRotate(Node * x)
{
	Node * xleft = x->left;
	x->left = xleft->right;
	x->height = MAX(GetLeftHeight(x), GetRightHeight(x)) + 1;
	xleft->right = x;
	xleft->height = MAX(GetLeftHeight(xleft), GetRightHeight(xleft)) + 1;
	return xleft;
}

/*
*ǰ��������x������������ΪAVL���������������ĸ߶Ȳ����Ϊ2
*���ã���x��ΪAVL�����������ΪAVL�������ظ����
*/
Node * Balance(Node * x)
{
	if (IsAVL(x))
		return x;
	Node * y;
	if (GetLeftHeight(x) > GetRightHeight(x))
	{
		y = x->left;
		if (GetLeftHeight(y) < GetRightHeight(y))
			iLeftRotate(y);
		return iRightRotate(x);
	}
	else
	{
		y = x->right;
		if (GetLeftHeight(y) > GetRightHeight(y))
			iRightRotate(y);
		return iLeftRotate(x);
	}
}

/*
*AVL���в���һ�����z
*/
Node * iInsert(Node * x, Node * z)
{
	if (x == NULL)
	{
		z->height = 0;
		return z;
	}
	Node * y;
	if ((z->key) <= (x->key))
	{
		y = iInsert(x->left, z);
		x->left = y;
		x->height = MAX(GetLeftHeight(x), GetRightHeight(x)) + 1;
	}
	else
	{
		y = iInsert(x->right, z);
		x->right = y;
		x->height = MAX(GetLeftHeight(x), GetRightHeight(x)) + 1;
	}
	x = Balance(x);
	return x;
}

/*
AVL����ɾ��һ�����z
*/
Node* idelete_node(AVLTree tree, Node * z)
{
	// ��Ϊ�� ���� û��Ҫɾ���Ľڵ㣬ֱ�ӷ���NULL��
	if (tree == NULL || z == NULL)
		return NULL;

	Node * y;
	if ((z->key) < (tree->key))        // ��ɾ���Ľڵ���"tree��������"��
	{
		y = idelete_node(tree->left, z);
		tree->left = y;
		tree->height = MAX(GetLeftHeight(tree), GetRightHeight(tree)) + 1;
		Balance(tree);
	}
	else if ((z->key) > (tree->key))// ��ɾ���Ľڵ���"tree��������"��
	{
		y = idelete_node(tree->right, z);
		tree->right = y;
		tree->height = MAX(GetLeftHeight(tree), GetRightHeight(tree)) + 1;
		Balance(tree);
	}
	else    // tree�Ƕ�ӦҪɾ���Ľڵ㡣
	{
		// tree�����Һ��Ӷ��ǿ�
		if ((tree->left) && (tree->right))
		{
			if (HEIGHT(tree->left) > HEIGHT(tree->right))
			{
				// ���tree�����������������ߣ�
				// ��(01)�ҳ�tree���������е����ڵ�
				//   (02)�������ڵ��ֵ��ֵ��tree��
				//   (03)ɾ�������ڵ㡣
				// ����������"tree�������������ڵ�"��"tree"������
				// �������ַ�ʽ�ĺô��ǣ�ɾ��"tree�������������ڵ�"֮��AVL����Ȼ��ƽ��ġ�
				Node * max = avltree_maximum(tree->left);
				tree->key = max->key;
				tree->left = idelete_node(tree->left, max);
			}
			else
			{
				// ���tree��������������������(��������ȣ�������������������1)
				// ��(01)�ҳ�tree���������е���С�ڵ�
				//   (02)������С�ڵ��ֵ��ֵ��tree��
				//   (03)ɾ������С�ڵ㡣
				// ����������"tree������������С�ڵ�"��"tree"������
				// �������ַ�ʽ�ĺô��ǣ�ɾ��"tree������������С�ڵ�"֮��AVL����Ȼ��ƽ��ġ�
				Node *min = avltree_minimum(tree->right);
				tree->key = min->key;
				tree->right = idelete_node(tree->right, min);
			}
		}
		else
		{
			Node *tmp = tree;
			tree = tree->left ? tree->left : tree->right;
			free(tmp);
		}
	}
	if (tree != NULL)
		tree->height = MAX(GetLeftHeight(tree), GetRightHeight(tree)) + 1;
	return tree;
}

/*
* ������С��㣺����treeΪ������AVL������С��㡣
*/
Node* avltree_minimum(AVLTree tree)
{
	if (tree == NULL)
		return NULL;

	while (tree->left != NULL)
		tree = tree->left;
	return tree;
}

/*
* ��������㣺����treeΪ������AVL��������㡣
*/
Node* avltree_maximum(AVLTree tree)
{
	if (tree == NULL)
		return NULL;

	while (tree->right != NULL)
		tree = tree->right;
	return tree;
}

/*
* LL
* ����ֵ������ĸ��ڵ�
*/
Node* left_left_rotation(AVLTree k2)
{
	AVLTree k1;

	k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;

	k2->height = MAX(HEIGHT(k2->left), HEIGHT(k2->right)) + 1;
	k1->height = MAX(HEIGHT(k1->left), k2->height) + 1;

	return k1;
}

/*
* RR
* ���ص�����ĸ��ڵ�
*/
Node* right_right_rotation(AVLTree k1)
{
	AVLTree k2;

	k2 = k1->right;
	k1->right = k2->left;
	k2->left = k1;

	k1->height = MAX(HEIGHT(k1->left), HEIGHT(k1->right)) + 1;
	k2->height = MAX(HEIGHT(k2->right), k1->height) + 1;

	return k2;
}

/*
* LR
* ���ص�����ĸ��ڵ�
*/
Node* left_right_rotation(AVLTree k3)
{
	k3->left = right_right_rotation(k3->left);

	return left_left_rotation(k3);
}

/*
* RL
* ���ص�����ĸ��ڵ�
*/
Node* right_left_rotation(AVLTree k1)
{
	k1->right = left_left_rotation(k1->right);

	return right_right_rotation(k1);
}

/*
* ����AVL����㡣
* key �Ǽ�ֵ��
*/
Node* avltree_create_node(Type key)
{
	Node* p;
	if ((p = (Node *)malloc(sizeof(Node))) == NULL)
		return NULL;
	p->key = key;
	p->left = NULL;
	p->right = NULL;
	p->height = 1;
	return p;
}

/*
* �������뵽AVL���У������ظ��ڵ�
*
* ����˵����
*     tree AVL���ĸ����
*     key ����Ľ��ļ�ֵ
* ����ֵ��
*     ���ڵ�
*/
Node* avltree_insert(AVLTree tree, Type key)
{
	if (tree == NULL)
	{
		// �½��ڵ�
		tree = avltree_create_node(key);
		if (tree == NULL)
		{
			printf("ERROR: create avltree node failed!\n");
			return NULL;
		}
	}
	// Ӧ�ý�key���뵽"tree��������"�����
	else if (key < tree->key)
	{
		tree->left = avltree_insert(tree->left, key);

		// ����ڵ����AVL��ʧȥƽ�⣬�������Ӧ�ĵ��ڡ�
		if (HEIGHT(tree->left) - HEIGHT(tree->right) == 2)
		{
			if (key < tree->left->key)
				tree = left_left_rotation(tree);
			else
				tree = left_right_rotation(tree);
		}
	}
	// Ӧ�ý�key���뵽"tree��������"�����
	else if (key > tree->key)
	{
		tree->right = avltree_insert(tree->right, key);

		// ����ڵ����AVL��ʧȥƽ�⣬�������Ӧ�ĵ��ڡ�
		if (HEIGHT(tree->right) - HEIGHT(tree->left) == 2)
		{
			if (key > tree->right->key)
				tree = right_right_rotation(tree);
			else
				tree = right_left_rotation(tree);
		}
	}

	//key == tree->key
	else 
	{
		;
	}

	//�������ĸ߶�
	tree->height = MAX(HEIGHT(tree->left), HEIGHT(tree->right)) + 1;

	return tree;
}

/*
* ɾ�����(z)�����ظ��ڵ�
*
* ����˵����
*     ptree AVL���ĸ����
*     z ��ɾ���Ľ��
* ����ֵ��
*     ���ڵ�
*/
Node* delete_node(AVLTree tree, Node *z)
{
	// ��Ϊ�� ���� û��Ҫɾ���Ľڵ㣬ֱ�ӷ���NULL��
	if (tree == NULL || z == NULL)
		return NULL;

	// ��ɾ���Ľڵ���"tree��������"��
	if (z->key < tree->key)
	{
		tree->left = delete_node(tree->left, z);

		// ɾ���ڵ����AVL��ʧȥƽ�⣬�������Ӧ�ĵ��ڡ�
		if (HEIGHT(tree->right) - HEIGHT(tree->left) == 2)
		{
			Node *r = tree->right;
			if (HEIGHT(r->left) > HEIGHT(r->right))
				tree = right_left_rotation(tree);
			else
				tree = right_right_rotation(tree);
		}
	}

	// ��ɾ���Ľڵ���"tree��������"��
	else if (z->key > tree->key)
	{
		tree->right = delete_node(tree->right, z);

		// ɾ���ڵ����AVL��ʧȥƽ�⣬�������Ӧ�ĵ��ڡ�
		if (HEIGHT(tree->left) - HEIGHT(tree->right) == 2)
		{
			Node *l = tree->left;
			if (HEIGHT(l->right) > HEIGHT(l->left))
				tree = left_right_rotation(tree);
			else
				tree = left_left_rotation(tree);
		}
	}

	// tree�Ƕ�ӦҪɾ���Ľڵ㡣
	else
	{
		// tree�����Һ��Ӷ��ǿ�
		if ((tree->left) && (tree->right))
		{
			if (HEIGHT(tree->left) > HEIGHT(tree->right))
			{
				/* ���tree�����������������ߣ�
				* ��(01)�ҳ�tree���������е����ڵ�
				*   (02)�������ڵ��ֵ��ֵ��tree��
				*   (03)ɾ�������ڵ㡣
				* ����������"tree�������������ڵ�"��"tree"������
				* ������ɾ��"tree�������������ڵ�"֮��AVL����Ȼ��ƽ��ġ�
				*/
				Node * max = avltree_maximum(tree->left);
				tree->key = max->key;
				tree->left = delete_node(tree->left, max);
			}
			else
			{
				/* ���tree��������������������(��������ȣ�������������������1)
				* ��(01)�ҳ�tree���������е���С�ڵ�
				*   (02)������С�ڵ��ֵ��ֵ��tree��
				*   (03)ɾ������С�ڵ㡣
				* ����������"tree������������С�ڵ�"��"tree"������
				* ������ɾ��"tree������������С�ڵ�"֮��AVL����Ȼ��ƽ��ġ�
				*/
				Node *min = avltree_minimum(tree->right);
				tree->key = min->key;
				tree->right = delete_node(tree->right, min);
			}
		}

		//tree��Ϊ���Ҫɾ���ģ������һ�����ӵĽ��
		else
		{
			Node * tmp = tree;
			tree = tree->left ? tree->left : tree->right;
			free(tmp);
		}
	}
	if (tree != NULL)
		tree->height = MAX(HEIGHT(tree->left), HEIGHT(tree->right)) + 1;
	return tree;
}

/*
* ɾ�����(key�ǽڵ�ֵ)�����ظ��ڵ�
*
* ����˵����
*     tree AVL���ĸ����
*     key ��ɾ���Ľ��ļ�ֵ
* ����ֵ��
*     ���ڵ�
*/
Node* avltree_delete(AVLTree tree, Type key)
{
	Node *z;

	if ((z = avltree_search(tree, key)) != NULL)
		tree = delete_node(tree, z);
	return tree;
}

/*
* ����AVL��
*/
void destroy_avltree(AVLTree tree)
{
	if (tree == NULL)
		return;

	if (tree->left != NULL)
		destroy_avltree(tree->left);
	if (tree->right != NULL)
		destroy_avltree(tree->right);

	free(tree);
}

/*
* ��ӡAVL��
* tree       -- AVL���Ľڵ�
* key        -- �ڵ�ļ�ֵ
* direction  --  0����ʾ�ýڵ��Ǹ��ڵ�;
*               -1����ʾ�ýڵ������ĸ���������;
*                1����ʾ�ýڵ������ĸ������Һ��ӡ�
*/
void print_avltree(AVLTree tree, Type key, int direction)
{
	if (tree != NULL)
	{
		// tree�Ǹ��ڵ�
		if (direction == 0)
			printf("%2d is root\n", tree->key);

		// tree�Ƿ�֧�ڵ�
		else
			printf("%2d is %2d's %6s child\n", tree->key, key, direction == 1 ? "right" : "left");

		print_avltree(tree->left, tree->key, -1);
		print_avltree(tree->right, tree->key, 1);
	}
}

/*
* ��ȡAVL���ĸ߶�
*/
int avltree_height(AVLTree tree)
{
	return HEIGHT(tree);
}



