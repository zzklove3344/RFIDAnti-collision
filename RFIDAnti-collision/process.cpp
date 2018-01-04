#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	unsigned char cStack;   //位栈
	int nTop;      //栈顶
}STACK;


typedef struct bitree
{
	unsigned char nIdentify;  //唯一标签
	struct bitree *lchild;  //左孩子
	struct bitree *rchild;  //右孩子
}BITREE;

STACK s;


//入栈
bool pushCStack(unsigned char cElem)
{
	if (s.nTop == 7)
	{
		printf_s("stack is full\n");
		return 0; //入栈失败
	}
	else
	{
		if (cElem == 0)
		{
			++s.nTop;
			s.cStack <<= 1;
		}
		else if (cElem == 1)
		{
			++s.nTop;
			s.cStack <<= 1;
			s.cStack |= 0x01;
		}
	}
	return 1;
}


//出栈
bool popCStack(void)
{
	if (s.nTop == -1)
	{
		printf_s("exception error,stack is empty\n");
		return 0;  //异常
	}
	else
	{
		--s.nTop;
		s.cStack >>= 1;
		return 1;
	}
}

void GetBitString(BITREE *&pBt)
{
	if (s.nTop != 3)
	{
		pBt = (BITREE *)malloc(sizeof(BITREE));
		if (pBt != NULL)
		{
			pBt->nIdentify = 0;
			pBt->lchild = NULL;
			pBt->rchild = NULL;
		}
		else
		{
			printf_s("malloc error\n");
			return;
		}
		pBt->nIdentify |= s.cStack;
		pushCStack((unsigned char)0);
		GetBitString(pBt->lchild);
		popCStack();
		pushCStack((unsigned char)1);
		GetBitString(pBt->rchild);
		popCStack();
	}
}


void printBinaryTree(BITREE *&pBt)
{
	if (pBt != NULL)
	{
		printf_s("%x\n", pBt->nIdentify);
		printBinaryTree(pBt->lchild);
		printBinaryTree(pBt->rchild);
		free(pBt);
	}
}


int main(void)
{
	
	s.nTop = -1;
	s.cStack = 0x00;
	BITREE *root = NULL;
	GetBitString(root);
	printBinaryTree(root);

	getchar();
	return 0;
}
