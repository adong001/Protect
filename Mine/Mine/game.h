#define _CRT_SECURE_NO_WARNINGS
#define ROW 9            //���̵�����
#define COL 9            //���̵�����
#define MAX_ROW  ROW+2    //����������һȦ����ֹ����Խ��
#define MAX_COL  COL+2    //
#define MINE_COUNT  10       //���׵�����
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void test();
int Menu();//��Ϸ�˵���ӡ����
void Game();//��װ��Ϸ��������
void Init(char show_map[MAX_ROW][MAX_COL], char mine_map[MAX_ROW][MAX_COL]);//��ʼ��������ά����
void Print_map(char map[MAX_ROW][MAX_COL]);  //��ӡ���̺���
void Return_minecount(char show_map[MAX_ROW][MAX_COL], char mine_map[MAX_ROW][MAX_COL], int row, int col);//�ж����������Χ8�����ӹ��м�����
void Clear_map(char show_map[MAX_ROW][MAX_COL], char mine_map[MAX_ROW][MAX_COL], int row, int col);//����Χ8�����Ӷ�û���׵ı�Ϊ�ո�
void Set_mine(char mine_map[MAX_ROW][MAX_COL],int row,int col);//����������Ϊû�ף���һ��������Ϊ�ף������������һ����ֱ���ҵ�һ��û���׵�Ϊֹ
void play_mine(char show_map[MAX_ROW][MAX_COL], char mine_map[MAX_ROW][MAX_COL], int row, int col,int *flag);//���׺���
void mark_mine(char show_map[MAX_ROW][MAX_COL], char mine_map[MAX_ROW][MAX_COL], int row, int col,int *flag);//���׺���