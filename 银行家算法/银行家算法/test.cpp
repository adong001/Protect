//#define _CRT_SECURE_NO_WARNINGS 1
//#include<iostream>
//#include<cstdio>
//using namespace std;
//#define MAX_SOURCE 6 //�ɴ�ӡ�������Դ��
//#define STATE 4 //����е�����
//
//void Dis_char1(int i, char ch)
//{
//	while (i--)
//	{
//		cout << ch;
//	}
//}
//
//int main()
//{
//	/*| ---------------------------------------------- |
//		|��\��Դ| Max | Allocation | Need | Available |
//		|   \�� | -------- | ---------- | ------ - | -------- - |
//		|��  \��| A B C | A B C | A B C | A B C |*/
//	int n = 4, m = 4, tmp;
//	int i, j;
//	char Name[] = "ABCDEFGH";
//	printf("|����������������������������������������������������������������������������������-|\n");
//	printf("%-8s%-19s%-19s%-19s%-20s", "|��\\��Դ", "|       Max        ", "|    Allocation    ", "|       Need       ", "|     Available    |\n");
//	printf("|   \\�� |������������������|������������������|������������������|������������������|\n");
//	printf("|��  \\��");
//	for (i = 0; i < STATE; i++)
//	{
//		cout << "|";
//		for (j = 0; j < m; j++)
//		{
//			printf(" %c ", Name[j]);
//		}
//		tmp = MAX_SOURCE - m;//�������ÿո��ֲ�
//		Dis_char1(tmp * 3, ' ');
//	}
//	cout << "|\n";
//	printf("|-------|������������������|������������������|������������������|������������������|\n");
//
//	for (i = 0; i < n; i++)
//	{
//		
//		printf("|  P%-2d  ",i);
//		for (int k = 0; k < STATE; k++)
//		{
//			cout << "|";
//			for (j = 0; j < m; j++)
//			{
//				printf(" %d ", j);
//			}
//			tmp = MAX_SOURCE - m;//�������ÿո��ֲ�
//			Dis_char1(tmp * 3, ' ');
//		}
//		cout << "|\n";
//	}
//	printf("|-------|������������������|������������������|������������������|������������������|\n");
//	system("pause");
//	return 0;
//}