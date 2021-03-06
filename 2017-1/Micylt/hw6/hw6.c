//说明：该文件中实现了作业2017-4-27中1和2.2的要求并且使用了上次作业中的两个测试用例外加自己写的两个测试用例进行测试
#include <stdio.h>
#include <stdlib.h>

typedef enum 
{

	false,

	true,

}bool;

typedef enum 
{

	OK,

	OVERFLOW,

	ERROR,

} Status;

typedef struct BiTNode 
{

	char data;

	struct BiTNode *lchild, *rchild;

}BiTNode, *BiTree;


int i = 0;

int length = 0;//深度

int testlength = 0;

int width[10] = { 0 };//宽度



Status CreateBiTree(BiTree *T, char *c) 
{

	char ch;

	ch = c[i];

	i++;

	if (ch == '#') 
	{

		*T = NULL;

	}

	else 
	{

		if (!(*T = (BiTNode *)malloc(sizeof(BiTNode)))) 
		{

			exit(OVERFLOW);

		}

		(*T)->data = ch;

		CreateBiTree(&(*T)->lchild, c);

		CreateBiTree(&(*T)->rchild, c);

	}

	return OK;

}



Status PostOrderTraverse(BiTree T) 
{

	if (T) 
	{

		PostOrderTraverse(T->lchild);

		PostOrderTraverse(T->rchild);

		printf("%c", T->data);

	}

	return OK;

}



Status MeasureLength(BiTree T) 
{

	if (!T) 
	{

		if (testlength > length) 
		{

			length = testlength;

		}

		return OK;

	}

	else 
	{

		testlength++;

		MeasureLength(T->lchild);

		MeasureLength(T->rchild);

		testlength--;

	}

	if (testlength > length) 
	{

		length = testlength;

	}

	return OK;

}



Status MeasureWidth(BiTree T, int len) 
{

	if (!T) {

		return ERROR;

	}

	else 
	{

		width[len] = width[len] + 1;

		len++;

	}

	MeasureWidth(T->lchild, len);

	MeasureWidth(T->rchild, len);

	return OK;

}



Status GetWidth() 
{

	int wi = 0;

	int i;

	for (i = 1; i <= length; i++) 
	{

		if (wi<width[i]) 
		{

			wi = width[i];

		}

		width[i] = 0;

	}

	printf("最大宽度为%d\n", wi);

	return OK;

}



Status MeasureLeaf(BiTree T, int *count1, int *count2) 
{

	if (T) 
	{

		if (T->lchild == NULL&&T->rchild == NULL) 
		{

			*(count1) = *(count1)+1;

		}

		else 
		{

			*(count2) = *(count2)+1;

		}

		MeasureLeaf(T->lchild, count1, count2);

		MeasureLeaf(T->rchild, count1, count2);

	}

	return OK;

}



int main() 
{

	int count1 = 0;

	int count2 = 0;

	char c[30];

	BiTree T = NULL;

	printf("请输入二叉树的先序序列（#表示空）:");
	gets(c);
	CreateBiTree(&T, c);

	MeasureLength(T);

	printf("创建完毕第一个二叉树\n二叉树的高度为%d\n", length);

	MeasureWidth(T, 1);

	GetWidth();

	printf("后序遍历第一个二叉树:\n");

	PostOrderTraverse(T);

	printf("\n遍历结束\n");

	MeasureLeaf(T, &count1, &count2);

	printf("该二叉树叶子节点数目为%d,非叶子节点数目为%d\n\n", count1, count2);

	return 0;

}