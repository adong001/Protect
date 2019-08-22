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
void game();                                       //��װ���ļ���������������������
int menu();                                        //���˵�
void menu_play_com();                              //����ģʽ�˵�
void init_board(char board[ROW][COL]);             //��ʼ����ά����
void print(char board[ROW][COL]);                  //��ӡ����                                                  
void menu_play_com_Easy(char board[ROW][COL]);     //��ģʽ�˵�        
void menu_play_com_Hard(char board[ROW][COL]);     //����ģʽ�˵�
void menu_play_com_Hell(char board[ROW][COL]);     //����ģʽ�˵�        
void com_play_Easy(char board[ROW][COL]);          //��ģʽ����������
void play_com_Easy(char board[ROW][COL]);          //��ģʽ���������
void com_play_Hard(char board[ROW][COL]);          //����ģʽ����������
void play_com_Hard(char board[ROW][COL]);          //����ģʽ���������
void play_play(char board[ROW][COL]);              //���1�����2��
int player_mov(char board[ROW][COL], int row, int col, int sign);//�����λ
void computer_mov_Easy(char board[ROW][COL]);      //��ģʽ������λ
void computer_mov_Hard(char board[ROW][COL]);      //����ģʽ������λ
int check_win_pp(char board[ROW][COL]);            //������1�����2ʤ��
int check_win_pc(char board[ROW][COL]);            //�����Ժ����ʤ��
int Is_full(char board[ROW][COL]);                 //�ж������Ƿ�����

#endif //_3CHESS_H