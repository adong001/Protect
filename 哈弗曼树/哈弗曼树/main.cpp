#include"haffum.h"

int main()
{
	int i, n;
	printf("请输入叶子结点的个数：\n");
	while (1)
	{
		scanf("%d", &n);
		if (n>1)
			break;
		else
			printf("输入错误，请重新输入n值！");
	}

	int* arr;
	arr = (int*)malloc(n*sizeof(ELEMTYPE));
	printf("请输入%d个叶子结点的权值：\n", n);
	for (i = 0; i<n; ++i)
	{
		scanf("%d", &arr[i]);
	}

	char ch[100], string[100];
	printf("请连续输入这%d个叶子结点各自所代表的字符：\n", n);
	fflush(stdin);      // 强行清除缓存中的数据，也就是上面输入权值结束时的回车符
	gets(string);

	HuffmanNode* hufmTree = NULL;
	hufmTree = createHuffmanTree(arr, n);

	printf("此哈夫曼树的广义表形式为：\n");
	PrintHuffmanTree(hufmTree);
	printf("\n各叶子结点的哈夫曼编码为：\n");
	HuffmanCode(hufmTree, 0);

	printf("要解码吗？请输入编码:\n");
	gets(ch);
	printf("解码结果为：\n");
	HuffmanDecode(ch, hufmTree, string);
	printf("\n");

	free(arr);
	free(hufmTree);

	return 0;
}
