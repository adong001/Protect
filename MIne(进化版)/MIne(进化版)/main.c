#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
#include "print.h"
#include "map.h"
#include <conio.h>
#include <Windows.h>

//全局变量
char g_map[MAXLINE + 2][MAXROW + 2];//棋盘数组，-1代表有雷，0代表不是雷
char g_markMap[MAXLINE + 2][MAXROW + 2];//棋盘显示数组，扫开周围8个格子没雷为‘ ’，
//有雷则显示周围8个格子有几个雷的数字，未扫开为‘■’，雷为‘¤’，标记为‘△’，标记错误为‘×’
int g_win; //记录这局是否胜利，0代表胜利

int getKeyBoard() //返回输入键的ASCII码值
{
	int a = _getch();
	//_getch()函数是一个不回显函数，当按下某个字符时，函数自动读取，无需按回车,所在头文件是<conio.h>。
	int result = ((char)a < 0) ? (a << 8 | _getch()) : a;
	//
	return result;
}
void(*printSence[PAGE_NUM])() = { print_start, print_set, print_exit };
void(*printSet[SET_NUM])() = { print_easy, print_mid, print_hard, print_free };
void(*printFreeSet[FREESET_NUM])(int x, int y, int m, int lim) = { print_setnumW, print_setnumH, print_setnumM };

void setFree(int *x, int *y, int *m)
{
	int flag = 0;
	int maxmine = 0;
	print_setnumW(*x, *y, *m, 0);
	while (1)
	{
		maxmine = *x * *y * 9 / 10;
		switch (getKeyBoard())
		{
		case ARROW_UP:
			flag--;
			if (flag < 0)
			{
				flag = FREESET_NUM - 1;
			}
			break;
		case ARROW_DOWN:
			flag++;
			if (flag > FREESET_NUM - 1)
			{
				flag = 0;
			}
			break;
		case ARROW_RIGHT:
			if (flag == 2)
			{
				(*m)++;
				(*m) > maxmine ? (*m)-- : (*m);
				break;
			}
			flag ? (*y)++ : (*x)++;
			(*y) > MAXROW ? (*y)-- : (*y);
			(*x) > MAXLINE ? (*x)-- : (*x);
			break;
		case ARROW_LEFT:
			if (flag == 2)
			{
				(*m)--;
				(*m) < 10 ? (*m)++ : (*m);
				break;
			}
			flag ? (*y)-- : (*x)--;
			(*y) < MINROW ? (*y)++ : (*y);
			(*x) < MINLINE ? (*x)++ : (*x);
			break;
		case '\r':
			return;
		default:;
		}
		printFreeSet[flag](*x, *y, *m, maxmine);
	}
}

int setPage(int *x, int *y, int *m)
{
	int flag = 0;
	print_easy();
	while (1)
	{
		switch (getKeyBoard())
		{
		case ARROW_UP:
			flag--;
			if (flag < 0)
			{
				flag = SET_NUM - 1;
			}
			break;
		case ARROW_DOWN:
			flag++;
			if (flag > SET_NUM - 1)
			{
				flag = 0;
			}
			break;
		case '\r':
			switch (flag)
			{
			case EASY:
				*x = 9;
				*y = 9;
				*m = 10;
				break;
			case MID:
				*x = 16;
				*y = 16;
				*m = 40;
				break;
			case HARD:
				*x = 16;
				*y = 24;
				*m = 99;
				break;
			case FREE:
				setFree(x, y, m);
			}
			return flag;
		default:;
		}
		printSet[flag]();
	}
}

int welcomePage()
{
	int flag = 0;
	print_start();//打印游戏主菜单
	while (1)
	{
		switch (getKeyBoard())//输入上下键选择
		{
		case ARROW_UP:
			flag--;//标签，记录选择的位置
			if (flag < 0)
			{
				flag = PAGE_NUM - 1;//第一行位置调到最后一行
			}
			break;
		case ARROW_DOWN:
			flag++;
			if (flag > PAGE_NUM - 1)//最后一行调至第一行
			{
				flag = 0;
			}
			break;
		case '\r':
			return flag;//第一行直接输入回车，直接进入游戏。
		default:;
		}
		printSence[flag]();//利用标签调用函数数组进入不同的选项
	}
}

void gameStart(int x, int y, int m)//游戏开始函数
{
	SIGN point;
	int flag = 1;
	int first = 0;
	int arrow = 0;
	int leastMine = m;

	memset(g_map, 0, sizeof(g_map));//初始化棋盘和
	memset(g_markMap, 0, sizeof(g_markMap));

	point.x = DEFSIGN(x) + 1; //棋盘中心
	point.y = DEFSIGN(y) + 1;

	g_win = x * y - m;  //棋盘中没有雷的个数

	printMap(x, y, flag, point, leastMine);

	while (1)
	{
		arrow = getKeyBoard();
		switch (arrow)
		{
		case ARROW_UP:
			point.x > 1 ? point.x-- : (point.x = x);
			flag = 1;
			break;
		case ARROW_DOWN:
			point.x < x ? point.x++ : (point.x = 1);
			flag = 1;
			break;
		case ARROW_LEFT:
			point.y > 1 ? point.y-- : (point.y = y);
			flag = 1;
			break;
		case ARROW_RIGHT:
			point.y < y ? point.y++ : (point.y = 1);
			flag = 1;
			break;
		case 'v':
			flag = 0;
			break;
		case 'l':
			printWin(x, y, leastMine);
			Sleep(100);
			break;
		case 'm':
			if (g_markMap[point.x][point.y] == DISPLAYNUM)
			{
				break;
			}

			if (g_markMap[point.x][point.y] != MARKEDMINE)
			{
				g_markMap[point.x][point.y] = MARKEDMINE;
				leastMine--;
			}
			else
			{
				g_markMap[point.x][point.y] = COVEREDNUM;
				leastMine++;
			}
			break;
		case ' ':
		case '\r':
			if (!first)
			{
				makeMap(x, y, m, point);
				first = 1;
				leastMine = m;
			}

			if (g_markMap[point.x][point.y] == MARKEDMINE)
			{
				break;
			}

			if (g_markMap[point.x][point.y] == DISPLAYNUM && g_map[point.x][point.y])
			{
				if (setMapNum(x, y, point))
				{
					printOver(x, y, leastMine);
					getchar();
					return;
				}
				break;
			}

			if (setMap(x, y, point.x, point.y))
			{
				printOver(x, y, leastMine);
				getchar();
				return;
			}
			break;
		default:;
		}

		if (g_win == 0)
		{
			printWin(x, y, leastMine);
			getchar();
			return;
		}

		printMap(x, y, flag, point, leastMine);
		flag = !flag;
	}
}

int main()
{
	int x = DEFLINE, y = DEFROW, m = DEFMINE;
	while (1)
	{
		switch (welcomePage())
		{
		case START:
			gameStart(x, y, m);
			break;
		case SET:
			setPage(&x, &y, &m);
			break;
		case EXIT:
			return 0;
		}
	}
	return 0;
}