#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int ELEMTYPE;

// 哈夫曼树结点结构体
typedef struct HuffmanTree
{
	ELEMTYPE weight;
	ELEMTYPE id;        // id用来主要用以区分权值相同的结点，这里代表了下标
	struct HuffmanTree* lchild;
	struct HuffmanTree* rchild;
}HuffmanNode;

// 构建哈夫曼树
HuffmanNode* createHuffmanTree(int* a, int n)
{
	int i, j;
	HuffmanNode **temp, *hufmTree=NULL;
	temp = (HuffmanNode**)malloc(n * sizeof(HuffmanNode));
	for (i = 0; i<n; ++i)     // 将数组a中的权值赋给结点中的weight
	{
		temp[i] = (HuffmanNode*)malloc(sizeof(HuffmanNode));
		temp[i]->weight = a[i];
		temp[i]->id = i;
		temp[i]->lchild = temp[i]->rchild = NULL;
	}

	for (i = 0; i<n - 1; ++i)       // 构建哈夫曼树需要n-1合并
	{
		int small1 = -1, small2;      // small1、small2分别作为最小和次小权值的下标
		for (j = 0; j<n; ++j)         // 先将最小的两个下标赋给small1、small2（注意：对应权值未必最小）
		{
			if (temp[j] != NULL && small1 == -1)
			{
				small1 = j;
				continue;
			}
			else if (temp[j] != NULL)
			{
				small2 = j;
				break;
			}
		}

		for (j = small2; j<n; ++j)    // 比较权值，挪动small1和small2使之分别成为最小和次小权值的下标
		{
			if (temp[j] != NULL)
			{
				if (temp[j]->weight < temp[small1]->weight)
				{
					small2 = small1;
					small1 = j;
				}
				else if (temp[j]->weight < temp[small2]->weight)
				{
					small2 = j;
				}
			}
		}
		hufmTree = (HuffmanNode*)malloc(sizeof(HuffmanNode));
		hufmTree->weight = temp[small1]->weight + temp[small2]->weight;
		hufmTree->lchild = temp[small1];
		hufmTree->rchild = temp[small2];

		temp[small1] = hufmTree;
		temp[small2] = NULL;
	}
	free(temp);
	return hufmTree;
}

// 以广义表的形式打印哈夫曼树
void PrintHuffmanTree(HuffmanNode* hufmTree)
{
	if (hufmTree)
	{
		printf("%d", hufmTree->weight);
		if (hufmTree->lchild != NULL || hufmTree->rchild != NULL)
		{
			printf("(");
			PrintHuffmanTree(hufmTree->lchild);
			printf(",");
			PrintHuffmanTree(hufmTree->rchild);
			printf(")");
		}
	}
}

// 递归进行哈夫曼编码
void HuffmanCode(HuffmanNode* hufmTree, int depth)      // depth是哈夫曼树的深度
{
	static int code[10];
	if (hufmTree)
	{
		if (hufmTree->lchild == NULL && hufmTree->rchild == NULL)
		{
			printf("id为%d权值为%d的叶子结点的哈夫曼编码为 ", hufmTree->id, hufmTree->weight);
			int i;
			for (i = 0; i<depth; ++i)
			{
				printf("%d", code[i]);
			}
			printf("\n");
		}
		else
		{
			code[depth] = 0;
			HuffmanCode(hufmTree->lchild, depth + 1);
			code[depth] = 1;
			HuffmanCode(hufmTree->rchild, depth + 1);
		}
	}
}

// 哈夫曼解码
void HuffmanDecode(char ch[], HuffmanNode* hufmTree, char string[])     // ch是要解码的01串，string是结点对应的字符
{
	int i;
	int num[100];
	HuffmanNode* tempTree = NULL;
	for (i = 0; i<strlen(ch); ++i)
	{
		if (ch[i] == '0')
			num[i] = 0;
		else
			num[i] = 1;
	}
	if (hufmTree)
	{
		i = 0;      // 计数已解码01串的长度
		while (i<strlen(ch))
		{
			tempTree = hufmTree;
			while (tempTree->lchild != NULL && tempTree->rchild != NULL)
			{
				if (num[i] == 0)
				{
					tempTree = tempTree->lchild;
				}
				else
				{
					tempTree = tempTree->rchild;
				}
				++i;
			}
			printf("%c", string[tempTree->id]);     // 输出解码后对应结点的字符
		}
	}
}