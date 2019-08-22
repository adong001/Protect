#include"3chess.h"


void game()           //��װ��Ϸ�е���������
{
	char board[ROW][COL];
	init_board(board);
	printf("���");
	while (1)
	{
		system("cls");
		int choice = menu();
		switch (choice)
		{
		case 1: menu_play_com(board); continue;//���뵥����Ϸ�˵�,���������������������һ��ʱ����continue����ѭ���˺���
		case 2: play_play(board); continue;  //����˫����Ϸ
		case 3:exit(1);
		default:printf("����������������룺\n");
		}
	}
}

int menu()           //���˵�
{
	printf("\n\n\n");
	printf("\t\t\t\t\t\t**********************\n");
	printf("\t\t\t\t\t\t@��������Ϸ��������Ȥ@\n");
	printf("\t\t\t\t\t\t**********************\n\n\n\n\n");
	printf("\t\t\t\t\t\t    1.������Ϸ\n\n");
	printf("\t\t\t\t\t\t    2.˫����Ϸ\n\n");
	printf("\t\t\t\t\t\t    3.�˳���Ϸ\n\n");
	int choice = 0;
	printf("\t\t\t\t\t\t���������ѡ��");
	scanf("%d", &choice);
	return choice;
}

void init_board(char board[ROW][COL])   //��ʼ������
{
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			board[i][j] = ' ';
		}
	}
}

void menu_play_com(char board[ROW][COL])  //������Ϸ�˵�
{
	int choice = 0;
	while (1)
	{
		system("cls");
		printf("\n\n\n");
		printf("\t\t\t\t\t\t**********************\n");
		printf("\t\t\t\t\t\t@��������Ϸ��������Ȥ@\n");
		printf("\t\t\t\t\t\t**********************\n\n\n\n\n");
		printf("\t\t\t\t\t\t    1.��ģʽ\n\n");
		printf("\t\t\t\t\t\t    2.����ģʽ\n\n");
		printf("\t\t\t\t\t\t    3.������һ��\n\n");
		printf("\t\t\t\t\t\t    4.�˳���Ϸ\n\n");
		printf("\t\t\t\t\t\t����������ѡ��");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1: menu_play_com_Easy(board); continue;
		case 2: menu_play_com_Hard(board); continue;
		case 3: return;          //�˺�������������ѭ����һ���˵�
		case 4: exit(1);
		default:printf("����������������룺\n"); continue;
		}
	}
}

//void menu_play_com[]{menu_play_com_Easy, menu_play_com_Hard, menu_play_com_Hell}
void menu_play_com_Easy(char board[ROW][COL])       //��ģʽ�˵�
{
	int choice = 0;
	while (1)
	{
		system("cls");
		printf("\n\n\n");
		printf("\t\t\t\t\t\t**********************\n");
		printf("\t\t\t\t\t\t@��������Ϸ��������Ȥ@\n");
		printf("\t\t\t\t\t\t**********************\n\n\n\n\n");
		printf("\t\t\t\t\t\t    1.�������\n\n");
		printf("\t\t\t\t\t\t    2.��������\n\n");
		printf("\t\t\t\t\t\t    3.������һ��\n\n");
		printf("\t\t\t\t\t\t    4.�˳���Ϸ\n\n");
		printf("\t\t\t\t\t\t��������ѡ��");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1: play_com_Easy(board); break;
		case 2: com_play_Easy(board); break;
		case 3: return;
		case 4: exit(1);
		default:printf("����������������룺\n"); continue;
		}
	}
}
void play_com_Easy(char board[ROW][COL])            //��ģʽ���������
{
	int X = 0;
	int Y = 0;
	while (1)
	{
		system("cls");
	loop:print(board);
		printf("\n\n����ѡ����Ҫ�ߵĸ��ӣ�");
		scanf("%d%d", &X, &Y);
		--X;
		--Y;
		system("cls");

		if (player_mov(board, X, Y, 1) == 0)         //�ж������Ƿ�Ϸ�
		{
			goto loop;
		}
		print(board);
		if (check_win_pc1(board) != 0)                //�ж��ķ��Ƿ�ʤ��
		{
			init_board(board);
			return;
		}
		printf("����˼����......\n");
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

void com_play_Easy(char board[ROW][COL])     //��ģʽ����������
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
			init_board(board);        //ƽ�ֻ��ʤ���ʼ�����飬Ϊ�´���Ϸ��׼��
			return;
		}
		printf("\n\n����ѡ����Ҫ�ߵĸ��ӣ�");
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
			init_board(board);       //ƽ�ֻ��ʤ���ʼ�����飬Ϊ�´���Ϸ��׼��
			return;
		}
		printf("����˼����......\n");
		Sleep(500);
	}
}

void computer_mov_Easy(char board[ROW][COL])   //��ģʽ��������
{
	srand((unsigned)time(NULL));       //������������ӣ�������ÿ�ε����µĵط���һ��
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
void menu_play_com_Hard(char board[ROW][COL])    //����ģʽ�˵�
{
	int choice = 0;
	while (1)
	{
		system("cls");
		printf("\n\n\n");
		printf("\t\t\t\t\t\t**********************\n");
		printf("\t\t\t\t\t\t@��������Ϸ��������Ȥ@\n");
		printf("\t\t\t\t\t\t**********************\n\n\n\n\n");
		printf("\t\t\t\t\t\t    1.�������\n\n");
		printf("\t\t\t\t\t\t    2.��������\n\n");
		printf("\t\t\t\t\t\t    3.������һ��\n\n");
		printf("\t\t\t\t\t\t    4.�˳���Ϸ\n\n");
		printf("��������ѡ��");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1: play_com_Hard(board); break;
		case 2: com_play_Hard(board); break;
		case 3: return;
		case 4: exit(1);
		default:printf("����������������룺\n"); continue;
		}
	}
}

void com_play_Hard(char board[ROW][COL])          //����ģʽ����������
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
			init_board(board);        //ƽ�ֻ��ʤ���ʼ�����飬Ϊ�´���Ϸ��׼��
			return;
		}
		printf("\n\n����ѡ����Ҫ�ߵĸ��ӣ�");
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
			init_board(board);       //ƽ�ֻ��ʤ���ʼ�����飬Ϊ�´���Ϸ��׼��
			return;
		}
		printf("����˼����......\n");
		Sleep(500);
	}
}
void play_com_Hard(char board[ROW][COL])          //����ģʽ���������
{
	int X = 0;
	int Y = 0;
	while (1)
	{
		system("cls");
	loop:print(board);
		printf("\n\n����ѡ����Ҫ�ߵĸ��ӣ�");
		scanf("%d%d", &X, &Y);
		--X;
		--Y;
		system("cls");

		if (player_mov(board, X, Y, 1) == 0)         //�ж������Ƿ�Ϸ�
		{
			goto loop;
		}
		print(board);
		if (check_win_pc1(board) != 0)                //�ж��ķ��Ƿ�ʤ��
		{
			init_board(board);
			return;
		}
		printf("����˼����......\n");
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
void computer_mov_Hard(char board[ROW][COL])     //����ģʽ������λ
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

int player_mov(char board[ROW][COL], int row, int col, int sign)  //�����λ,��λ�ɹ�����1�����򷵻�0(signΪ��ʶλ��1Ϊ'X',0Ϊ'0')
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
			printf("��ʾ���˴�����!!!\n");
			return 0;
		}
	}
	else
	{
		printf("��ʾ����ѡ���������������!!!��\n");
		return 0;
	}
}


void play_play(char board[ROW][COL])              //˫����Ϸ
{
	int X1 = 0, X2 = 0;
	int Y1 = 0, Y2 = 0;
	while (1)
	{
		system("cls");
		print(board);
	loop1:printf("\n\n��player1ѡ����Ҫ�ߵĸ��ӣ�");
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
			init_board(board);    //ƽ�ֻ��ʤ���ʼ�����飬Ϊ�´���Ϸ��׼��
			return;
		}
	loop2:printf("\n\n��player2ѡ����Ҫ�ߵĸ��ӣ�");
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
			init_board(board);      //ƽ�ֻ��ʤ���ʼ�����飬Ϊ�´���Ϸ��׼��
			return;
		}
	}
}

int check_win_pc(char board[ROW][COL])   //�ж���Һ͵����ķ�ʤ
{

	for (int i = 0; i < ROW; i++)      //���ʤ��1
	{
		if (board[i][0] == 'X' && board[i][1] == 'X' && board[i][2] == 'X'
			|| board[0][i] == 'X' && board[1][i] == 'X' && board[2][i] == 'X'
			|| board[0][0] == 'X' && board[1][1] == 'X' && board[2][2] == 'X'
			|| board[0][2] == 'X' && board[1][1] == 'X' && board[2][0] == 'X'
			)
		{
			return 1;
		}                               //����ʤ��2  
		else if (board[i][0] == '0' && board[i][1] == '0' && board[i][2] == '0'
			|| board[0][i] == '0' && board[1][i] == '0' && board[2][i] == '0'
			|| board[0][0] == '0' && board[1][1] == '0' && board[2][2] == '0'
			|| board[0][2] == '0' && board[1][1] == '0' && board[2][0] == '0'
			)
		{
			return 2;
		}
		if (Is_full(board) == 1)  //ƽ�ַ�-1
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
		printf("��ϲ��һ�ʤ������\n\n");
		system("pause");
		return 1;
	}
	else if (choice == 2)
	{
		printf("��ϲ���Ի�ʤ������\n\n");
		system("pause");
		return 2;
	}
	else if (choice == -1)
	{
		printf("ƽ�֣�����\n\n");
		system("pause");
		return -1;
	}
	else
	{
		return 0;
	}
}

int check_win_pp(char board[ROW][COL])    //�ж���Һ͵����ķ�ʤ  (��Ȼ�˴���������漸��һ�£���������ʱ��ֱ��ʹ�ã����ø��ݷ���ֵ�жϽ��)
{
	if (Is_full(board) == 1)     //ƽ�ַ�1
	{
		init_board(board);          //ƽ�ֻ��ʤ���ʼ�����飬Ϊ�´���Ϸ��׼��
		printf("\n\n\t\t\tƽ�֣�����\n\n");
		system("pause");
		return -1;
	}
	for (int i = 0; i < ROW; i++)         //player1ʤ��1
	{
		if (board[i][0] == 'X' && board[i][1] == 'X' && board[i][2] == 'X'
			|| board[0][i] == 'X' && board[1][i] == 'X' && board[2][i] == 'X'
			|| board[0][0] == 'X' && board[1][1] == 'X' && board[2][2] == 'X'
			|| board[0][2] == 'X' && board[1][1] == 'X' && board[2][0] == 'X'
			)
		{
			init_board(board);
			printf("\n\n\t\t\t��ϲplayer1ʤ��������\n\n\n");
			system("pause");
			return 1;
		}                                //player2ʤ��2
		else if (board[i][0] == '0' && board[i][1] == '0' && board[i][2] == '0'
			|| board[0][i] == '0' && board[1][i] == '0' && board[2][i] == '0'
			|| board[0][0] == '0' && board[1][1] == '0' && board[2][2] == '0'
			|| board[0][2] == '0' && board[1][1] == '0' && board[2][0] == '0'
			)
		{
			init_board(board);
			printf("��ϲplayer2��ʤ������\n\n");
			system("pause");
			return 2;
		}
	}
	return 0;
}

int Is_full(char board[ROW][COL])          //�ж������Ƿ��������˷���1�����򷵻�0;
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
			if (i < (COL - 1))                //ֻ��ӡ�м����еķָ���
				printf("---|");
		}
		printf("\n");
	}
}