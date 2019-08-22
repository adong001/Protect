#define _CRT_SECURE_NO_WARNINGS
#define ROW 9            //棋盘的行数
#define COL 9            //棋盘的列数
#define MAX_ROW  ROW+2    //给棋盘扩大一圈，防止数组越界
#define MAX_COL  COL+2    //
#define MINE_COUNT  10       //地雷的总数
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void test();
int Menu();//游戏菜单打印函数
void Game();//封装游戏其他函数
void Init(char show_map[MAX_ROW][MAX_COL], char mine_map[MAX_ROW][MAX_COL]);//初始化两个二维数组
void Print_map(char map[MAX_ROW][MAX_COL]);  //打印棋盘函数
void Return_minecount(char show_map[MAX_ROW][MAX_COL], char mine_map[MAX_ROW][MAX_COL], int row, int col);//判断任意格子周围8个格子共有几颗雷
void Clear_map(char show_map[MAX_ROW][MAX_COL], char mine_map[MAX_ROW][MAX_COL], int row, int col);//将周围8个格子都没有雷的变为空格
void Set_mine(char mine_map[MAX_ROW][MAX_COL],int row,int col);//将此坐标设为没雷，下一个格子设为雷，否则就设下下一个，直到找到一个没有雷的为止
void play_mine(char show_map[MAX_ROW][MAX_COL], char mine_map[MAX_ROW][MAX_COL], int row, int col,int *flag);//排雷函数
void mark_mine(char show_map[MAX_ROW][MAX_COL], char mine_map[MAX_ROW][MAX_COL], int row, int col,int *flag);//标雷函数