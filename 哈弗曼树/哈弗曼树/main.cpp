#include"haffum.h"

int main()
{
	int i, n;
	printf("������Ҷ�ӽ��ĸ�����\n");
	while (1)
	{
		scanf("%d", &n);
		if (n>1)
			break;
		else
			printf("�����������������nֵ��");
	}

	int* arr;
	arr = (int*)malloc(n*sizeof(ELEMTYPE));
	printf("������%d��Ҷ�ӽ���Ȩֵ��\n", n);
	for (i = 0; i<n; ++i)
	{
		scanf("%d", &arr[i]);
	}

	char ch[100], string[100];
	printf("������������%d��Ҷ�ӽ�������������ַ���\n", n);
	fflush(stdin);      // ǿ����������е����ݣ�Ҳ������������Ȩֵ����ʱ�Ļس���
	gets(string);

	HuffmanNode* hufmTree = NULL;
	hufmTree = createHuffmanTree(arr, n);

	printf("�˹��������Ĺ������ʽΪ��\n");
	PrintHuffmanTree(hufmTree);
	printf("\n��Ҷ�ӽ��Ĺ���������Ϊ��\n");
	HuffmanCode(hufmTree, 0);

	printf("Ҫ���������������:\n");
	gets(ch);
	printf("������Ϊ��\n");
	HuffmanDecode(ch, hufmTree, string);
	printf("\n");

	free(arr);
	free(hufmTree);

	return 0;
}
