#include"game.h"

void test()
{
	while (1)
	{
		srand((unsigned)time(NULL));
		int choice = Menu();  //�õ��˵��ķ���ֵ
		if (choice == 1)      //Ϊ1������Ϸ
		{
			Game();
		}
		else if (choice == 0) //�˳���Ϸ
		{
			printf("GoodBye!!!\n");
			break;
		}
		else                //�������󣬼���ѭ��
		{
			printf("�������󣡣���");
		}
	}
}

int Menu()               //��Ϸ�˵���ӡ����
{
	int choice = 0;
	printf("\n\n\n\n");
	printf("\t\t\t\t\t\t\tɨ��");
	printf("\n\n");
	printf("\t\t\t\t\t*************************************\n");
	printf("\t\t\t\t\t****                          *******\n");
	printf("\t\t\t\t\t****         1.������Ϸ       *******\n");
	printf("\t\t\t\t\t****         0.�˳���Ϸ       *******\n");
	printf("\t\t\t\t\t****                          *******\n");
	printf("\t\t\t\t\t*************************************\n\n\n");
	printf("\t\t\t\t\t����������ѡ��");
	scanf("%d", &choice);
	return choice;
}

void Game()             //��װ��Ϸ��������
{  
    int flag = 0;                    //����Ƿ�Ϊ��һ�ν��룬
	int n = 0;                       //ѡ��ɨ�׻����
	int m = 0;                       //��¼�Ƿ�Ϊ��һ�ν��룬��ֹ��һ�β���
	char show_map[MAX_ROW][MAX_COL];// ��ʾÿ��λ���Ƿ񱻷�
	char mine_map[MAX_ROW][MAX_COL];// ��ʾÿ��λ���Ƿ�����
	Init(show_map, mine_map);       //��ʼ��������ά����
	system("cls");
	while (1)
	{
		int n = 0;
		int row = 0;                //���Ҫ���������
		int col = 0;                //���Ҫ���������
		//Print_map(mine_map);
		printf("\n");
	    Print_map(show_map);        //��ӡ����	
		printf("\t\t\t\t\t---------1.ɨ��---------\n");
		printf("\t\t\t\t\t---------2.����---------\n");
		printf("\t\t\t\t\t����������ѡ��");
		scanf("%d", &n);
		switch (n)
		{
		case 1:play_mine(show_map, mine_map, row, col,&flag); break;
		case 2:mark_mine(show_map, mine_map, row, col,&flag); break;
		default:system("cls"); printf("\t\t\t\t\t��ʾ���������󣡣���\n"); continue;
		}
	}
}

void Init(char show_map[MAX_ROW][MAX_COL], char mine_map[MAX_ROW][MAX_COL])//��ʼ��������ά����
{

	for (int row = 0; row < MAX_ROW; ++row)
	{
		for (int col = 0; col < MAX_COL; ++col)
		{
			show_map[row][col] = '*';  //show_map[][]Ϊ'*'��ʾδ������'1'��ʾ��Χ��һ������;
			                           //����ȫ����ʼ��Ϊ'*';
		}
	}
	for (int row = 0; row < MAX_ROW; ++row)
	{
		for (int col = 0; col < MAX_COL; ++col)
		{
			mine_map[row][col] = '0';//mine_map[][]Ϊ'0'��ʾ���ǵ��ף�'1'��ʾ�ǵ���;
		}                            //������ȫ����ʼ��Ϊ'0';
	}

}

void Print_map(char map[MAX_ROW][MAX_COL])        //��ӡ���̺���
{
	int i, j;
	printf("\t\t\t\t    ");//Ϊ�����̵�����
	for (i = 1; i <= ROW; i++)
	{
		printf(" %d  ", i);
	}
	printf("\n\t\t\t\t    ------------------------------------\n");
	for (i = 1; i <=ROW; i++)
	{
		printf("\t\t\t\t%2d |", i);
		for (j = 1; j <=COL; j++)
		{
			printf("  %c ", map[i][j]);
			if (j == COL)
			{
				printf("|\n");
			}
		}
		printf("\n");
	}
	printf("\t\t\t\t    -----------------------------------\n");
}

void Return_minecount(char show_map[MAX_ROW][MAX_COL], char mine_map[MAX_ROW][MAX_COL], int row, int col)
{     //�ж����������Χ8�����ӹ��м�����
   show_map[row][col]  = 
	     (mine_map[row - 1][col - 1] + mine_map[row - 1][col] 
		 + mine_map[row - 1][col + 1] + mine_map[row][col - 1]//�������ֵת��Ϊ�ַ����͸�ֵ��show_map
         + mine_map[row][col + 1] + mine_map[row + 1][col - 1]//�����⻹��һȦ�������������Խ��
		 + mine_map[row + 1][col] + mine_map[row + 1][col + 1]- 8 * '0') + '0';   
}      
//mine_mapΪ�ַ���,��8�μ�ȥ'0'�õ�������Χ8�����ӵ��׵ĸ���������,�ټ���'0'ת��Ϊ�ַ��͸���

void  Clear_map(char show_map[MAX_ROW][MAX_COL], char mine_map[MAX_ROW][MAX_COL],int row,int col)
{	//����Χ8�����Ӷ�û���׵ı�Ϊ�ո�	
	Return_minecount(show_map, mine_map, row, col);
	//����Return_minecount�����жϴ�������Χ8�����ӵ�����
	
	if (show_map[row][col] == '0')
	{
		show_map[row][col] = ' '; //����Χ8�����Ӷ�û���׵ĸ�ֵΪ�ո񣬱��ڹ۲�
		///���õݹ������Χ8������
		if (row - 1 > 0 && col - 1 > 0 && show_map[row - 1][col - 1] == '*') //����
		{
			Clear_map(show_map, mine_map, row - 1, col - 1);
		}
		if (row - 1 > 0 && show_map[row - 1][col] == '*')            //����
		{
			Clear_map(show_map, mine_map, row - 1, col);
		}
		if (row - 1 > 0 && col <=COL && show_map[row - 1][col] == '*')//����
		{
			Clear_map(show_map, mine_map, row - 1, col +1 );
		}
		if (col - 1 > 0 && show_map[row][col - 1] == '*')                //��
		{
			Clear_map(show_map, mine_map, row , col - 1);
		}
		if (col + 1 <= COL && show_map[row][col + 1] == '*')          //��
		{
			Clear_map(show_map, mine_map, row , col + 1 );
		}
		if (row + 1 <= ROW && col - 1 > 0 && show_map[row + 1][col - 1] == '*')//����
		{
			Clear_map(show_map, mine_map, row + 1, col - 1);
		}
		if (row + 1 <= ROW && show_map[row + 1][col] == '*')     //����
		{
			Clear_map(show_map, mine_map, row + 1, col);
		}
		if (row + 1 <= ROW && col + 1 <= COL && show_map[row + 1][col + 1] == '*')//����
		{
			Clear_map(show_map, mine_map, row + 1, col + 1);
		}
	}
}


void Set_mine(char mine_map[MAX_ROW][MAX_COL], int row, int col)//�������꼰��Χ8��������Ϊû�ף���ֹ��һ�ν���ͽ�����Ϸ
{
	int mine_count = MINE_COUNT;       //����һ����ʱ���������׵�����
	int rand_row = 0;                 //���������������(1--ROW)
	int rand_col = 0;                 //���������������(1--COL)	
	while (mine_count > 0)
	{	
		rand_row = ((rand() % ROW) + 1);
		rand_col = ((rand() % COL) + 1);
        if (((rand_row <row-1)||(rand_row>row+1)||(rand_col<col-1)
			|| (rand_col>col + 1)) && mine_map[rand_row][rand_col] == '0')
		{
		   mine_map[rand_row][rand_col] = '1'; //�˴�û�����ɵ��ף���ֵmine_map[row][col]Ϊ1��
		   --mine_count;             //���Ե��׵����� - 1������ֱ��Ϊ���˳�ѭ��
	    }
	}
}

void play_mine(char show_map[MAX_ROW][MAX_COL], char mine_map[MAX_ROW][MAX_COL], int row, int col,int *flag)//���׺��� 
{
	
	while (1)
	{
	    //Print_map(mine_map);
		system("cls");
		printf("\n");
		Print_map(show_map);
		printf("\t\t\t\t\t---------ɨ����---------\n");
		printf("\n\n\t\t\t\t��������Ҫѡ���λ������(����-1�˳�)��");
		scanf("%d%d", &row, &col);
		if (col == -1||row == -1)       //�˳�����
		{
			break;
		}
		if (row <= 0 || row > COL || col <= 0 || col > COL) //�ж���������ĺϷ���
		{
			system("cls");
			printf("\t\t\t\t\t������ʾ��������������\n");
			continue;
		}
		if (*flag == 0)
		{
			Set_mine(mine_map, row, col);    //��������ף��������һ�β����һ��д���ʿ�һ��Ƭ
			(*flag) ++;
		}
		if (show_map[row][col] != '*')   //�ж���������Ƿ񱻷���
		{
			system("cls");
			printf("\t\t\t\t\t������ʾ���������ѱ�����!\n");
			continue;
		}

		if (mine_map[row][col] == '1')  //�жϴ�����Ϊ'1'���ף���Ϸ�������˳�ѭ��
		{
			show_map[row][col] = 'X';
			Print_map(show_map);
			printf("\n\t\t\t\t\tGAME OVER !!!");
			printf("\n");
			Init(show_map, mine_map);
			*flag = 0;
			system("pause");	
			system("cls");
			return;
		}
		Clear_map(show_map, mine_map, row, col);
	}
    
}
void mark_mine(char show_map[MAX_ROW][MAX_COL], char mine_map[MAX_ROW][MAX_COL], int row, int col,int *flag)//���׺���
{
	static int count_mine = 0;//����һ����̬������ÿ�ε����꺯���������ͷ�
	while (1)
	{
		system("cls");
		//Print_map(mine_map);
		printf("\n");
		Print_map(show_map);
		printf("\t\t\t\t\t---------������---------\n");
		printf("\t\t\t\t���������׵����꣺(����-1�˳�)");
		scanf("%d%d", &row, &col);
		if (col == -1)       //�˳�����
		{
			break;
		}

		if (row <= 0 || row > COL || col <= 0 || col > COL) //�ж���������ĺϷ���
		{
			system("cls");
			printf("\t\t\t\t\t������ʾ��������������\n");
			continue;
		}
	
		if (mine_map[row][col] == '0'&& show_map[row][col] == '*')  //�жϱ�����Ƿ���ȷ
		{   
			system("cls");
			show_map[row][col] = 'X';
			Print_map(show_map);
			printf("\t\t\t\t\t��Ϸ���������ױ�Ǵ����ˣ�����\n");
			printf("\n");
			Init(show_map, mine_map);
			*flag = 0;
			system("pause");		
			break;
		}
		if (mine_map[row][col] == '1'&& show_map[row][col] == '*')
		{
			system("cls");
			show_map[row][col] = '?';         //���׷���
			count_mine++;
		}	
		if (count_mine == MINE_COUNT)
		{
			Print_map(show_map);
			*flag = 0;
			Init(show_map, mine_map);
			printf("\t\t\t\t\t��ϲ�����׳ɹ�������\n");
			printf("\n");
			system("pause");
			system("cls");
			break;
		}
	}
}