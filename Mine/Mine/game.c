#include"game.h"

void test()
{
	while (1)
	{
		srand((unsigned)time(NULL));
		int choice = Menu();  //得到菜单的返回值
		if (choice == 1)      //为1进入游戏
		{
			Game();
		}
		else if (choice == 0) //退出游戏
		{
			printf("GoodBye!!!\n");
			break;
		}
		else                //输入有误，继续循环
		{
			printf("输入有误！！！");
		}
	}
}

int Menu()               //游戏菜单打印函数
{
	int choice = 0;
	printf("\n\n\n\n");
	printf("\t\t\t\t\t\t\t扫雷");
	printf("\n\n");
	printf("\t\t\t\t\t*************************************\n");
	printf("\t\t\t\t\t****                          *******\n");
	printf("\t\t\t\t\t****         1.进入游戏       *******\n");
	printf("\t\t\t\t\t****         0.退出游戏       *******\n");
	printf("\t\t\t\t\t****                          *******\n");
	printf("\t\t\t\t\t*************************************\n\n\n");
	printf("\t\t\t\t\t请输入您的选择：");
	scanf("%d", &choice);
	return choice;
}

void Game()             //封装游戏其他函数
{  
    int flag = 0;                    //标记是否为第一次进入，
	int n = 0;                       //选择扫雷或标雷
	int m = 0;                       //记录是否为第一次进入，防止第一次踩雷
	char show_map[MAX_ROW][MAX_COL];// 表示每个位置是否被翻
	char mine_map[MAX_ROW][MAX_COL];// 表示每个位置是否有雷
	Init(show_map, mine_map);       //初始化两个二维数组
	system("cls");
	while (1)
	{
		int n = 0;
		int row = 0;                //玩家要输入的行数
		int col = 0;                //玩家要输入的列数
		//Print_map(mine_map);
		printf("\n");
	    Print_map(show_map);        //打印棋盘	
		printf("\t\t\t\t\t---------1.扫雷---------\n");
		printf("\t\t\t\t\t---------2.标雷---------\n");
		printf("\t\t\t\t\t请输入您的选择：");
		scanf("%d", &n);
		switch (n)
		{
		case 1:play_mine(show_map, mine_map, row, col,&flag); break;
		case 2:mark_mine(show_map, mine_map, row, col,&flag); break;
		default:system("cls"); printf("\t\t\t\t\t提示：输入有误！！！\n"); continue;
		}
	}
}

void Init(char show_map[MAX_ROW][MAX_COL], char mine_map[MAX_ROW][MAX_COL])//初始化两个二维数组
{

	for (int row = 0; row < MAX_ROW; ++row)
	{
		for (int col = 0; col < MAX_COL; ++col)
		{
			show_map[row][col] = '*';  //show_map[][]为'*'表示未翻开，'1'表示周围有一个地雷;
			                           //现在全部初始化为'*';
		}
	}
	for (int row = 0; row < MAX_ROW; ++row)
	{
		for (int col = 0; col < MAX_COL; ++col)
		{
			mine_map[row][col] = '0';//mine_map[][]为'0'表示不是地雷，'1'表示是地雷;
		}                            //现在先全部初始化为'0';
	}

}

void Print_map(char map[MAX_ROW][MAX_COL])        //打印棋盘函数
{
	int i, j;
	printf("\t\t\t\t    ");//为了棋盘的美观
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
{     //判断任意格子周围8个格子共有几颗雷
   show_map[row][col]  = 
	     (mine_map[row - 1][col - 1] + mine_map[row - 1][col] 
		 + mine_map[row - 1][col + 1] + mine_map[row][col - 1]//将计算的值转换为字符类型赋值给show_map
         + mine_map[row][col + 1] + mine_map[row + 1][col - 1]//棋盘外还有一圈，不会出现数组越界
		 + mine_map[row + 1][col] + mine_map[row + 1][col + 1]- 8 * '0') + '0';   
}      
//mine_map为字符型,加8次减去'0'得到的是周围8个格子的雷的个数整数据,再加上'0'转换为字符型个数

void  Clear_map(char show_map[MAX_ROW][MAX_COL], char mine_map[MAX_ROW][MAX_COL],int row,int col)
{	//将周围8个格子都没有雷的变为空格	
	Return_minecount(show_map, mine_map, row, col);
	//利用Return_minecount函数判断此坐标周围8个格子地雷数
	
	if (show_map[row][col] == '0')
	{
		show_map[row][col] = ' '; //将周围8个格子都没地雷的赋值为空格，便于观察
		///利用递归遍历周围8个格子
		if (row - 1 > 0 && col - 1 > 0 && show_map[row - 1][col - 1] == '*') //左上
		{
			Clear_map(show_map, mine_map, row - 1, col - 1);
		}
		if (row - 1 > 0 && show_map[row - 1][col] == '*')            //正上
		{
			Clear_map(show_map, mine_map, row - 1, col);
		}
		if (row - 1 > 0 && col <=COL && show_map[row - 1][col] == '*')//右上
		{
			Clear_map(show_map, mine_map, row - 1, col +1 );
		}
		if (col - 1 > 0 && show_map[row][col - 1] == '*')                //左
		{
			Clear_map(show_map, mine_map, row , col - 1);
		}
		if (col + 1 <= COL && show_map[row][col + 1] == '*')          //右
		{
			Clear_map(show_map, mine_map, row , col + 1 );
		}
		if (row + 1 <= ROW && col - 1 > 0 && show_map[row + 1][col - 1] == '*')//左下
		{
			Clear_map(show_map, mine_map, row + 1, col - 1);
		}
		if (row + 1 <= ROW && show_map[row + 1][col] == '*')     //正下
		{
			Clear_map(show_map, mine_map, row + 1, col);
		}
		if (row + 1 <= ROW && col + 1 <= COL && show_map[row + 1][col + 1] == '*')//右下
		{
			Clear_map(show_map, mine_map, row + 1, col + 1);
		}
	}
}


void Set_mine(char mine_map[MAX_ROW][MAX_COL], int row, int col)//将此坐标及周围8个格子设为没雷，防止第一次进入就结束游戏
{
	int mine_count = MINE_COUNT;       //定义一个临时变量记数雷的总数
	int rand_row = 0;                 //产生的随机横坐标(1--ROW)
	int rand_col = 0;                 //产生的随机纵坐标(1--COL)	
	while (mine_count > 0)
	{	
		rand_row = ((rand() % ROW) + 1);
		rand_col = ((rand() % COL) + 1);
        if (((rand_row <row-1)||(rand_row>row+1)||(rand_col<col-1)
			|| (rand_col>col + 1)) && mine_map[rand_row][rand_col] == '0')
		{
		   mine_map[rand_row][rand_col] = '1'; //此处没有生成地雷，赋值mine_map[row][col]为1，
		   --mine_count;             //并对地雷的总数 - 1，总数直到为零退出循环
	    }
	}
}

void play_mine(char show_map[MAX_ROW][MAX_COL], char mine_map[MAX_ROW][MAX_COL], int row, int col,int *flag)//排雷函数 
{
	
	while (1)
	{
	    //Print_map(mine_map);
		system("cls");
		printf("\n");
		Print_map(show_map);
		printf("\t\t\t\t\t---------扫雷中---------\n");
		printf("\n\n\t\t\t\t请输入您要选择的位置坐标(输入-1退出)：");
		scanf("%d%d", &row, &col);
		if (col == -1||row == -1)       //退出标雷
		{
			break;
		}
		if (row <= 0 || row > COL || col <= 0 || col > COL) //判断输入坐标的合法性
		{
			system("cls");
			printf("\t\t\t\t\t友情提示：输入坐标有误！\n");
			continue;
		}
		if (*flag == 0)
		{
			Set_mine(mine_map, row, col);    //随机生成雷，但不会第一次踩雷且会有大机率开一大片
			(*flag) ++;
		}
		if (show_map[row][col] != '*')   //判断这个坐标是否被翻开
		{
			system("cls");
			printf("\t\t\t\t\t友情提示：此坐标已被翻开!\n");
			continue;
		}

		if (mine_map[row][col] == '1')  //判断此坐标为'1'踩雷，游戏结束，退出循环
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
void mark_mine(char show_map[MAX_ROW][MAX_COL], char mine_map[MAX_ROW][MAX_COL], int row, int col,int *flag)//标雷函数
{
	static int count_mine = 0;//定义一个静态变量，每次调用完函数都不会释放
	while (1)
	{
		system("cls");
		//Print_map(mine_map);
		printf("\n");
		Print_map(show_map);
		printf("\t\t\t\t\t---------排雷中---------\n");
		printf("\t\t\t\t请输入标记雷的坐标：(输入-1退出)");
		scanf("%d%d", &row, &col);
		if (col == -1)       //退出标雷
		{
			break;
		}

		if (row <= 0 || row > COL || col <= 0 || col > COL) //判断输入坐标的合法性
		{
			system("cls");
			printf("\t\t\t\t\t友情提示：输入坐标有误！\n");
			continue;
		}
	
		if (mine_map[row][col] == '0'&& show_map[row][col] == '*')  //判断标的雷是否正确
		{   
			system("cls");
			show_map[row][col] = 'X';
			Print_map(show_map);
			printf("\t\t\t\t\t游戏结束，你雷标记错误了！！！\n");
			printf("\n");
			Init(show_map, mine_map);
			*flag = 0;
			system("pause");		
			break;
		}
		if (mine_map[row][col] == '1'&& show_map[row][col] == '*')
		{
			system("cls");
			show_map[row][col] = '?';         //标雷符号
			count_mine++;
		}	
		if (count_mine == MINE_COUNT)
		{
			Print_map(show_map);
			*flag = 0;
			Init(show_map, mine_map);
			printf("\t\t\t\t\t恭喜你排雷成功！！！\n");
			printf("\n");
			system("pause");
			system("cls");
			break;
		}
	}
}