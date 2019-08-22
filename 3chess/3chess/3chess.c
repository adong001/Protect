#include"3chess.h"


void game()           //封装游戏中的其他函数
{
	char board[ROW][COL];
	init_board(board);
	printf("●○");
	while (1)
	{
		system("cls");
		int choice = menu();
		switch (choice)
		{
		case 1: menu_play_com(board); continue;//进入单人游戏菜单,当这个函数结束，返回上一层时，用continue继续循环此函数
		case 2: play_play(board); continue;  //进入双人游戏
		case 3:exit(1);
		default:printf("输入错误，请重新输入：\n");
		}
	}
}

int menu()           //主菜单
{
	printf("\n\n\n");
	printf("\t\t\t\t\t\t**********************\n");
	printf("\t\t\t\t\t\t@三子棋游戏好玩又有趣@\n");
	printf("\t\t\t\t\t\t**********************\n\n\n\n\n");
	printf("\t\t\t\t\t\t    1.单人游戏\n\n");
	printf("\t\t\t\t\t\t    2.双人游戏\n\n");
	printf("\t\t\t\t\t\t    3.退出游戏\n\n");
	int choice = 0;
	printf("\t\t\t\t\t\t请输入你的选择：");
	scanf("%d", &choice);
	return choice;
}

void init_board(char board[ROW][COL])   //初始化函数
{
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			board[i][j] = ' ';
		}
	}
}

void menu_play_com(char board[ROW][COL])  //单人游戏菜单
{
	int choice = 0;
	while (1)
	{
		system("cls");
		printf("\n\n\n");
		printf("\t\t\t\t\t\t**********************\n");
		printf("\t\t\t\t\t\t@三子棋游戏好玩又有趣@\n");
		printf("\t\t\t\t\t\t**********************\n\n\n\n\n");
		printf("\t\t\t\t\t\t    1.简单模式\n\n");
		printf("\t\t\t\t\t\t    2.困难模式\n\n");
		printf("\t\t\t\t\t\t    3.返回上一层\n\n");
		printf("\t\t\t\t\t\t    4.退出游戏\n\n");
		printf("\t\t\t\t\t\t请输入您的选择：");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1: menu_play_com_Easy(board); continue;
		case 2: menu_play_com_Hard(board); continue;
		case 3: return;          //此函数结束，继续循环上一个菜单
		case 4: exit(1);
		default:printf("输入错误，请重新输入：\n"); continue;
		}
	}
}

//void menu_play_com[]{menu_play_com_Easy, menu_play_com_Hard, menu_play_com_Hell}
void menu_play_com_Easy(char board[ROW][COL])       //简单模式菜单
{
	int choice = 0;
	while (1)
	{
		system("cls");
		printf("\n\n\n");
		printf("\t\t\t\t\t\t**********************\n");
		printf("\t\t\t\t\t\t@三子棋游戏好玩又有趣@\n");
		printf("\t\t\t\t\t\t**********************\n\n\n\n\n");
		printf("\t\t\t\t\t\t    1.玩家先手\n\n");
		printf("\t\t\t\t\t\t    2.电脑先手\n\n");
		printf("\t\t\t\t\t\t    3.返回上一层\n\n");
		printf("\t\t\t\t\t\t    4.退出游戏\n\n");
		printf("\t\t\t\t\t\t输入您的选择：");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1: play_com_Easy(board); break;
		case 2: com_play_Easy(board); break;
		case 3: return;
		case 4: exit(1);
		default:printf("输入错误，请重新输入：\n"); continue;
		}
	}
}
void play_com_Easy(char board[ROW][COL])            //简单模式，玩家先手
{
	int X = 0;
	int Y = 0;
	while (1)
	{
		system("cls");
	loop:print(board);
		printf("\n\n请您选择您要走的格子：");
		scanf("%d%d", &X, &Y);
		--X;
		--Y;
		system("cls");

		if (player_mov(board, X, Y, 1) == 0)         //判断输入是否合法
		{
			goto loop;
		}
		print(board);
		if (check_win_pc1(board) != 0)                //判断哪方是否胜利
		{
			init_board(board);
			return;
		}
		printf("电脑思考中......\n");
		Sleep(500);
		system("cls");
		computer_mov_Easy(board);
		print(board);
		if (check_win_pc1(board) != 0)
		{
			init_board(board);
			return;
		}
	}
}

void com_play_Easy(char board[ROW][COL])     //简单模式，电脑先手
{

	int X = 0;
	int Y = 0;
	while (1)
	{
		system("cls");
		computer_mov_Easy(board);
	loop:print(board);
		if (check_win_pc1(board) != 0)
		{
			init_board(board);        //平局或获胜后初始化数组，为下次游戏做准备
			return;
		}
		printf("\n\n请您选择您要走的格子：");
		scanf("%d%d", &X, &Y);
		--X;
		--Y;
		if (player_mov(board, X, Y, 1) == 0)
		{
			goto loop;
		}
		system("cls");
		print(board);
		if (check_win_pc1(board) != 0)
		{
			init_board(board);       //平局或获胜后初始化数组，为下次游戏做准备
			return;
		}
		printf("电脑思考中......\n");
		Sleep(500);
	}
}

void computer_mov_Easy(char board[ROW][COL])   //简单模式，电脑走
{
	srand((unsigned)time(NULL));       //播下随机数种子，不至于每次电脑下的地方都一样
	while (1)
	{
		int x = rand() % 3;
		int y = rand() % 3;
		if (board[x][y] == ' ')
		{
			board[x][y] = '0';
			break;
		}
	}
}
void menu_play_com_Hard(char board[ROW][COL])    //困难模式菜单
{
	int choice = 0;
	while (1)
	{
		system("cls");
		printf("\n\n\n");
		printf("\t\t\t\t\t\t**********************\n");
		printf("\t\t\t\t\t\t@三子棋游戏好玩又有趣@\n");
		printf("\t\t\t\t\t\t**********************\n\n\n\n\n");
		printf("\t\t\t\t\t\t    1.玩家先手\n\n");
		printf("\t\t\t\t\t\t    2.电脑先手\n\n");
		printf("\t\t\t\t\t\t    3.返回上一层\n\n");
		printf("\t\t\t\t\t\t    4.退出游戏\n\n");
		printf("输入您的选择：");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1: play_com_Hard(board); break;
		case 2: com_play_Hard(board); break;
		case 3: return;
		case 4: exit(1);
		default:printf("输入错误，请重新输入：\n"); continue;
		}
	}
}

void com_play_Hard(char board[ROW][COL])          //困难模式，电脑先手
{

	int X = 0;
	int Y = 0;
	while (1)
	{
		system("cls");
		computer_mov_Hard(board);
	loop:print(board);
		if (check_win_pc1(board) != 0)
		{
			init_board(board);        //平局或获胜后初始化数组，为下次游戏做准备
			return;
		}
		printf("\n\n请您选择您要走的格子：");
		scanf("%d%d", &X, &Y);
		--X;
		--Y;
		if (player_mov(board, X, Y, 1) == 0)
		{
			goto loop;
		}
		system("cls");
		print(board);
		if (check_win_pc1(board) != 0)
		{
			init_board(board);       //平局或获胜后初始化数组，为下次游戏做准备
			return;
		}
		printf("电脑思考中......\n");
		Sleep(500);
	}
}
void play_com_Hard(char board[ROW][COL])          //困难模式，玩家先手
{
	int X = 0;
	int Y = 0;
	while (1)
	{
		system("cls");
	loop:print(board);
		printf("\n\n请您选择您要走的格子：");
		scanf("%d%d", &X, &Y);
		--X;
		--Y;
		system("cls");

		if (player_mov(board, X, Y, 1) == 0)         //判断输入是否合法
		{
			goto loop;
		}
		print(board);
		if (check_win_pc1(board) != 0)                //判断哪方是否胜利
		{
			init_board(board);
			return;
		}
		printf("电脑思考中......\n");
		Sleep(500);
		system("cls");
		computer_mov_Hard(board);
		print(board);
		if (check_win_pc1(board) != 0)
		{
			init_board(board);
			return;
		}
	}
}
void computer_mov_Hard(char board[ROW][COL])     //困难模式电脑走位
{
	int x, y, i;
	while (1)
	{
		x = rand() % ROW;
		y = rand() % COL;
		for (i = 0; i < ROW; i++)
		{
			if (board[i][0] == board[i][1] && board[i][0] == '0' && board[i][2] == ' ')
			{
				board[i][2] = '0';
				return;
			}
			else if (board[i][1] == board[i][2] && board[i][1] == '0' && board[i][0] == ' ')
			{
				board[i][0] = '0';
				return;
			}
			else if (board[i][0] == board[i][2] && board[i][2] == '0' && board[i][1] == ' ')
			{
				board[i][1] = '0';
				return;
			}
			else if (board[0][i] == board[1][i] && board[0][i] == '0' && board[2][i] == ' ')
			{
				board[2][i] = '0';
				return;
			}
			else if (board[1][i] == board[2][i] && board[1][i] == '0' && board[0][i] == ' ')
			{
				board[0][i] = '0';
				return;
			}
			else if (board[0][i] == board[2][i] && board[2][i] == '0' && board[1][i] == ' ')
			{
				board[1][i] = '0';
				return;
			}
			else if (board[0][0] == board[1][1] && board[0][0] == '0' && board[2][2] == ' ')
			{
				board[2][2] = '0';
				return;
			}
			else if (board[1][1] == board[2][2] && board[1][1] == '0' && board[0][0] == ' ')
			{
				board[0][0] = '0';
				return;
			}
			else if (board[0][0] == board[2][2] && board[0][0] == '0' && board[1][1] == ' ')
			{
				board[1][1] = 'X';
				return;
			}
			else if (board[0][2] == board[1][1] && board[1][1] == '0' && board[2][0] == ' ')
			{
				board[2][0] = '0';
				return;
			}
			else if (board[1][1] == board[2][0] && board[1][1] == '0' && board[0][2] == ' ')
			{
				board[0][2] = '0';
				return;
			}
			else if (board[2][0] == board[0][2] && board[2][0] == '0' && board[1][1] == ' ')
			{
				board[1][1] = '0';
				return;
			}
		}
		for (i = 0; i < ROW; i++)
		{
			if (board[i][0] == board[i][1] && board[i][0] == 'X' && board[i][2] == ' ')
			{
				board[i][2] = '0';
				return;
			}
			else if (board[i][1] == board[i][2] && board[i][1] == 'X' && board[i][0] == ' ')
			{
				board[i][0] = '0';
				return;
			}
			else if (board[i][0] == board[i][2] && board[i][2] == 'X' && board[i][1] == ' ')
			{
				board[i][1] = '0';
				return;
			}
			else if (board[0][i] == board[1][i] && board[0][i] == 'X' && board[2][i] == ' ')
			{
				board[2][i] = '0';
				return;
			}
			else if (board[1][i] == board[2][i] && board[1][i] == 'X' && board[0][i] == ' ')
			{
				board[0][i] = '0';
				return;
			}
			else if (board[0][i] == board[2][i] && board[2][i] == 'X' && board[1][i] == ' ')
			{
				board[1][i] = '0';
				return;
			}
			else if (board[0][0] == board[1][1] && board[0][0] == 'X' && board[2][2] == ' ')
			{
				board[2][2] = '0';
				return;
			}
			else if (board[1][1] == board[2][2] && board[1][1] == 'X' && board[0][0] == ' ')
			{
				board[0][0] = '0';
				return;
			}
			else if (board[0][0] == board[2][2] && board[0][0] == 'X' && board[1][1] == ' ')
			{
				board[1][1] = '0';
				return;
			}
			else if (board[0][2] == board[1][1] && board[1][1] == 'X' && board[2][0] == ' ')
			{
				board[2][0] = '0';
				return;
			}
			else if (board[1][1] == board[2][0] && board[1][1] == 'X' && board[0][2] == ' ')
			{
				board[0][2] = '0';
				return;
			}
			else if (board[2][0] == board[0][2] && board[2][0] == 'X' && board[1][1] == ' ')
			{
				board[1][1] = '0';
				return;
			}
		}
		if (board[x][y] == ' ')
		{
			board[x][y] = '0';
			return;
		}
	}
}

int player_mov(char board[ROW][COL], int row, int col, int sign)  //玩家走位,走位成功返回1，否则返回0(sign为标识位，1为'X',0为'0')
{
	if ((0 <= row && col < ROW) && (0 <= row && col < COL))
	{
		if (board[row][col] == ' ')
		{
			if (sign == 1)
			{
				board[row][col] = 'X';
				return 1;
			}
			else
			{
				board[row][col] = '0';
				return 1;
			}
		}
		else
		{
			printf("提示：此处已下!!!\n");
			return 0;
		}
	}
	else
	{
		printf("提示：您选择的区域不在棋盘内!!!：\n");
		return 0;
	}
}


void play_play(char board[ROW][COL])              //双人游戏
{
	int X1 = 0, X2 = 0;
	int Y1 = 0, Y2 = 0;
	while (1)
	{
		system("cls");
		print(board);
	loop1:printf("\n\n请player1选择您要走的格子：");
		scanf("%d%d", &X1, &Y1);
		--X1;
		--Y1;
		if (player_mov(board, X1, Y1, 1) == 0)
		{
			goto loop1;
		}
		system("cls");
		print(board);
		if (check_win_pp(board) != 0)
		{
			init_board(board);    //平局或获胜后初始化数组，为下次游戏做准备
			return;
		}
	loop2:printf("\n\n请player2选择您要走的格子：");
		scanf("%d%d", &X2, &Y2);
		--X2;
		--Y2;
		if (player_mov(board, X2, Y2, 0) == 0)
		{
			goto loop2;
		}
		system("cls");
		print(board);
		if (check_win_pp(board) != 0)
		{
			init_board(board);      //平局或获胜后初始化数组，为下次游戏做准备
			return;
		}
	}
}

int check_win_pc(char board[ROW][COL])   //判断玩家和电脑哪方胜
{

	for (int i = 0; i < ROW; i++)      //玩家胜返1
	{
		if (board[i][0] == 'X' && board[i][1] == 'X' && board[i][2] == 'X'
			|| board[0][i] == 'X' && board[1][i] == 'X' && board[2][i] == 'X'
			|| board[0][0] == 'X' && board[1][1] == 'X' && board[2][2] == 'X'
			|| board[0][2] == 'X' && board[1][1] == 'X' && board[2][0] == 'X'
			)
		{
			return 1;
		}                               //电脑胜返2  
		else if (board[i][0] == '0' && board[i][1] == '0' && board[i][2] == '0'
			|| board[0][i] == '0' && board[1][i] == '0' && board[2][i] == '0'
			|| board[0][0] == '0' && board[1][1] == '0' && board[2][2] == '0'
			|| board[0][2] == '0' && board[1][1] == '0' && board[2][0] == '0'
			)
		{
			return 2;
		}
		if (Is_full(board) == 1)  //平局返-1
		{
			return -1;
		}
	}
	return 0;
}

int check_win_pc1(char board[ROW][COL])
{
	int choice = check_win_pc(board);

	if (choice == 1)
	{
		printf("恭喜玩家获胜！！！\n\n");
		system("pause");
		return 1;
	}
	else if (choice == 2)
	{
		printf("恭喜电脑获胜！！！\n\n");
		system("pause");
		return 2;
	}
	else if (choice == -1)
	{
		printf("平局！！！\n\n");
		system("pause");
		return -1;
	}
	else
	{
		return 0;
	}
}

int check_win_pp(char board[ROW][COL])    //判断玩家和电脑哪方胜  (虽然此处代码和上面几乎一致，但被调用时可直接使用，不用根据返回值判断结果)
{
	if (Is_full(board) == 1)     //平局返1
	{
		init_board(board);          //平局或获胜后初始化数组，为下次游戏做准备
		printf("\n\n\t\t\t平局！！！\n\n");
		system("pause");
		return -1;
	}
	for (int i = 0; i < ROW; i++)         //player1胜返1
	{
		if (board[i][0] == 'X' && board[i][1] == 'X' && board[i][2] == 'X'
			|| board[0][i] == 'X' && board[1][i] == 'X' && board[2][i] == 'X'
			|| board[0][0] == 'X' && board[1][1] == 'X' && board[2][2] == 'X'
			|| board[0][2] == 'X' && board[1][1] == 'X' && board[2][0] == 'X'
			)
		{
			init_board(board);
			printf("\n\n\t\t\t恭喜player1胜利！！！\n\n\n");
			system("pause");
			return 1;
		}                                //player2胜返2
		else if (board[i][0] == '0' && board[i][1] == '0' && board[i][2] == '0'
			|| board[0][i] == '0' && board[1][i] == '0' && board[2][i] == '0'
			|| board[0][0] == '0' && board[1][1] == '0' && board[2][2] == '0'
			|| board[0][2] == '0' && board[1][1] == '0' && board[2][0] == '0'
			)
		{
			init_board(board);
			printf("恭喜player2获胜！！！\n\n");
			system("pause");
			return 2;
		}
	}
	return 0;
}

int Is_full(char board[ROW][COL])          //判断棋盘是否满，满了返回1，否则返回0;
{
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			if (board[i][j] == ' ')
			{
				return 0;
			}
		}
	}
	return 1;
}

void print(char board[ROW][COL])
{

	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			printf(" %c |", board[i][j]);
		}
		printf("\n");
		for (int j = 0; j < COL; j++)
		{
			if (i < (COL - 1))                //只打印中间两行的分割线
				printf("---|");
		}
		printf("\n");
	}
}