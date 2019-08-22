#ifndef _3CHESS_H_
#define _3CHESS_H_
#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<time.h>

#define ROW 3
#define COL 3   
void game();                                       //封装本文件函数，被主函数所调用
int menu();                                        //主菜单
void menu_play_com();                              //单人模式菜单
void init_board(char board[ROW][COL]);             //初始化二维数组
void print(char board[ROW][COL]);                  //打印棋盘                                                  
void menu_play_com_Easy(char board[ROW][COL]);     //简单模式菜单        
void menu_play_com_Hard(char board[ROW][COL]);     //困难模式菜单
void menu_play_com_Hell(char board[ROW][COL]);     //地狱模式菜单        
void com_play_Easy(char board[ROW][COL]);          //简单模式，电脑先手
void play_com_Easy(char board[ROW][COL]);          //简单模式，玩家先手
void com_play_Hard(char board[ROW][COL]);          //困难模式，电脑先手
void play_com_Hard(char board[ROW][COL]);          //困难模式，玩家先手
void play_play(char board[ROW][COL]);              //玩家1和玩家2玩
int player_mov(char board[ROW][COL], int row, int col, int sign);//玩家走位
void computer_mov_Easy(char board[ROW][COL]);      //简单模式电脑走位
void computer_mov_Hard(char board[ROW][COL]);      //困难模式电脑走位
int check_win_pp(char board[ROW][COL]);            //检查玩家1和玩家2胜利
int check_win_pc(char board[ROW][COL]);            //检查电脑和玩家胜利
int Is_full(char board[ROW][COL]);                 //判断棋盘是否满了

#endif //_3CHESS_H