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

	//设置随机数种子
	srand(time(NULL));

	//初始化输入序列
	for (i = 0; i < N; i++)
		arr[i] = rand() % 10000;

	//printf("依次往树中添加元素: ");

	//开始计时
	ibeg = clock();
	for (i = 0; i < N; i++)
	{
		//printf("%d ", arr[i]);
		root = avltree_insert(root, arr[i]);
	}
	iend = clock();
	printf("\nAVL树中一共插入 %d 个数，耗时 %d ms \n", N, iend - ibeg);

	printf("树的高度为: %d\n", avltree_height(root));
	//printf("此AVL树的详细信息如下: \n");
	//print_avltree(root, root->key, 0);

	printf("现在按照输入序列的顺序，依次删除AVL树的节点...");
	ibeg = clock();
	for (i = 0; i < N; i++)
	{
		root = avltree_delete(root, arr[i]);
	}
	iend = clock();
	printf("\nAVL树中一共删除 %d 个数，耗时 %d ms \n", N, iend - ibeg);

	/*
	printf("\n删除后，树的详细信息如下: \n");
	if (root)
	{
		//print_avltree(root, root->key, 0);
		destroy_avltree(root);
	}
	else
	printf("树为空！！\n");
	*/
	return 0;
}

/*
* (递归实现)查找"AVL树x"中键值为key的节点
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
返回x的绝对值
*/
int iabs(int x)
{
	if (x >= 0)
		return x;
	else
		return -x;
}

/*
*前置条件：x的左右子树均为AVL树。判断以x为根的树
*是否也为AVL树，若是，则返回true，否则返回false
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
*得到x的左子树的高度
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
*得到x的右子树的高度
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
*以x为根结点进行左旋操作
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
*以x为根结点进行右旋操作
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
*前置条件：x的左右子树均为AVL树，且左右子树的高度差最多为2
*作用：若x不为AVL树，则将其调整为AVL树，返回根结点
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
*AVL树中插入一个结点z
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
AVL树中删除一个结点z
*/
Node* idelete_node(AVLTree tree, Node * z)
{
	// 根为空 或者 没有要删除的节点，直接返回NULL。
	if (tree == NULL || z == NULL)
		return NULL;

	Node * y;
	if ((z->key) < (tree->key))        // 待删除的节点在"tree的左子树"中
	{
		y = idelete_node(tree->left, z);
		tree->left = y;
		tree->height = MAX(GetLeftHeight(tree), GetRightHeight(tree)) + 1;
		Balance(tree);
	}
	else if ((z->key) > (tree->key))// 待删除的节点在"tree的右子树"中
	{
		y = idelete_node(tree->right, z);
		tree->right = y;
		tree->height = MAX(GetLeftHeight(tree), GetRightHeight(tree)) + 1;
		Balance(tree);
	}
	else    // tree是对应要删除的节点。
	{
		// tree的左右孩子都非空
		if ((tree->left) && (tree->right))
		{
			if (HEIGHT(tree->left) > HEIGHT(tree->right))
			{
				// 如果tree的左子树比右子树高；
				// 则(01)找出tree的左子树中的最大节点
				//   (02)将该最大节点的值赋值给tree。
				//   (03)删除该最大节点。
				// 这类似于用"tree的左子树中最大节点"做"tree"的替身；
				// 采用这种方式的好处是：删除"tree的左子树中最大节点"之后，AVL树仍然是平衡的。
				Node * max = avltree_maximum(tree->left);
				tree->key = max->key;
				tree->left = idelete_node(tree->left, max);
			}
			else
			{
				// 如果tree的左子树不比右子树高(即它们相等，或右子树比左子树高1)
				// 则(01)找出tree的右子树中的最小节点
				//   (02)将该最小节点的值赋值给tree。
				//   (03)删除该最小节点。
				// 这类似于用"tree的右子树中最小节点"做"tree"的替身；
				// 采用这种方式的好处是：删除"tree的右子树中最小节点"之后，AVL树仍然是平衡的。
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
* 查找最小结点：返回tree为根结点的AVL树的最小结点。
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
* 查找最大结点：返回tree为根结点的AVL树的最大结点。
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
* 返回值调整后的根节点
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
* 返回调整后的根节点
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
* 返回调整后的根节点
*/
Node* left_right_rotation(AVLTree k3)
{
	k3->left = right_right_rotation(k3->left);

	return left_left_rotation(k3);
}

/*
* RL
* 返回调整后的根节点
*/
Node* right_left_rotation(AVLTree k1)
{
	k1->right = left_left_rotation(k1->right);

	return right_right_rotation(k1);
}

/*
* 创建AVL树结点。
* key 是键值。
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
* 将结点插入到AVL树中，并返回根节点
*
* 参数说明：
*     tree AVL树的根结点
*     key 插入的结点的键值
* 返回值：
*     根节点
*/
Node* avltree_insert(AVLTree tree, Type key)
{
	if (tree == NULL)
	{
		// 新建节点
		tree = avltree_create_node(key);
		if (tree == NULL)
		{
			printf("ERROR: create avltree node failed!\n");
			return NULL;
		}
	}
	// 应该将key插入到"tree的左子树"的情况
	else if (key < tree->key)
	{
		tree->left = avltree_insert(tree->left, key);

		// 插入节点后，若AVL树失去平衡，则进行相应的调节。
		if (HEIGHT(tree->left) - HEIGHT(tree->right) == 2)
		{
			if (key < tree->left->key)
				tree = left_left_rotation(tree);
			else
				tree = left_right_rotation(tree);
		}
	}
	// 应该将key插入到"tree的右子树"的情况
	else if (key > tree->key)
	{
		tree->right = avltree_insert(tree->right, key);

		// 插入节点后，若AVL树失去平衡，则进行相应的调节。
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

	//更新树的高度
	tree->height = MAX(HEIGHT(tree->left), HEIGHT(tree->right)) + 1;

	return tree;
}

/*
* 删除结点(z)，返回根节点
*
* 参数说明：
*     ptree AVL树的根结点
*     z 待删除的结点
* 返回值：
*     根节点
*/
Node* delete_node(AVLTree tree, Node *z)
{
	// 根为空 或者 没有要删除的节点，直接返回NULL。
	if (tree == NULL || z == NULL)
		return NULL;

	// 待删除的节点在"tree的左子树"中
	if (z->key < tree->key)
	{
		tree->left = delete_node(tree->left, z);

		// 删除节点后，若AVL树失去平衡，则进行相应的调节。
		if (HEIGHT(tree->right) - HEIGHT(tree->left) == 2)
		{
			Node *r = tree->right;
			if (HEIGHT(r->left) > HEIGHT(r->right))
				tree = right_left_rotation(tree);
			else
				tree = right_right_rotation(tree);
		}
	}

	// 待删除的节点在"tree的右子树"中
	else if (z->key > tree->key)
	{
		tree->right = delete_node(tree->right, z);

		// 删除节点后，若AVL树失去平衡，则进行相应的调节。
		if (HEIGHT(tree->left) - HEIGHT(tree->right) == 2)
		{
			Node *l = tree->left;
			if (HEIGHT(l->right) > HEIGHT(l->left))
				tree = left_right_rotation(tree);
			else
				tree = left_left_rotation(tree);
		}
	}

	// tree是对应要删除的节点。
	else
	{
		// tree的左右孩子都非空
		if ((tree->left) && (tree->right))
		{
			if (HEIGHT(tree->left) > HEIGHT(tree->right))
			{
				/* 如果tree的左子树比右子树高；
				* 则(01)找出tree的左子树中的最大节点
				*   (02)将该最大节点的值赋值给tree。
				*   (03)删除该最大节点。
				* 这类似于用"tree的左子树中最大节点"做"tree"的替身；
				* 这样，删除"tree的左子树中最大节点"之后，AVL树仍然是平衡的。
				*/
				Node * max = avltree_maximum(tree->left);
				tree->key = max->key;
				tree->left = delete_node(tree->left, max);
			}
			else
			{
				/* 如果tree的左子树不比右子树高(即它们相等，或右子树比左子树高1)
				* 则(01)找出tree的右子树中的最小节点
				*   (02)将该最小节点的值赋值给tree。
				*   (03)删除该最小节点。
				* 这类似于用"tree的右子树中最小节点"做"tree"的替身；
				* 这样，删除"tree的右子树中最小节点"之后，AVL树仍然是平衡的。
				*/
				Node *min = avltree_minimum(tree->right);
				tree->key = min->key;
				tree->right = delete_node(tree->right, min);
			}
		}

		//tree即为最后要删除的，最多有一个孩子的结点
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
* 删除结点(key是节点值)，返回根节点
*
* 参数说明：
*     tree AVL树的根结点
*     key 待删除的结点的键值
* 返回值：
*     根节点
*/
Node* avltree_delete(AVLTree tree, Type key)
{
	Node *z;

	if ((z = avltree_search(tree, key)) != NULL)
		tree = delete_node(tree, z);
	return tree;
}

/*
* 销毁AVL树
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
* 打印AVL树
* tree       -- AVL树的节点
* key        -- 节点的键值
* direction  --  0，表示该节点是根节点;
*               -1，表示该节点是它的父结点的左孩子;
*                1，表示该节点是它的父结点的右孩子。
*/
void print_avltree(AVLTree tree, Type key, int direction)
{
	if (tree != NULL)
	{
		// tree是根节点
		if (direction == 0)
			printf("%2d is root\n", tree->key);

		// tree是分支节点
		else
			printf("%2d is %2d's %6s child\n", tree->key, key, direction == 1 ? "right" : "left");

		print_avltree(tree->left, tree->key, -1);
		print_avltree(tree->right, tree->key, 1);
	}
}

/*
* 获取AVL树的高度
*/
int avltree_height(AVLTree tree)
{
	return HEIGHT(tree);
}



