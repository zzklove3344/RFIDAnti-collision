#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	unsigned char cStack;   //λջ
	int nTop;      //ջ��
}STACK;


typedef struct bitree
{
	unsigned char nIdentify;  //Ψһ��ǩ
	struct bitree *lchild;  //����
	struct bitree *rchild;  //�Һ���
}BITREE;

STACK s;


//��ջ
bool pushCStack(unsigned char cElem)
{
	if (s.nTop == 7)
	{
		printf_s("stack is full\n");
		return 0; //��ջʧ��
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


//��ջ
bool popCStack(void)
{
	if (s.nTop == -1)
	{
		printf_s("exception error,stack is empty\n");
		return 0;  //�쳣
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
