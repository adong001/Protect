#ifndef _PRINT_H_
#define _PRINT_H_

#define PAGE_NUM 3     
//printSence[PAGE_NUM]()���˵���������������С
#define SET_NUM 4      
//printSet[SET_NUM]()��Ϸ�Ѷ����ú�������������С
#define FREESET_NUM 3  
//printFreeSet[FREESET_NUM]()��Ϸ�Ѷ��Զ��庯������������С
enum
{
	START = 0, //��Ϸ���˵��Ŀ�ʼ�����ã��˳�
	SET,
	EXIT,
};

void print_start();  //��ʼ��Ϸ��ʾ(���й���ƶ�ֻ�����´�ӡ�˵�����)
void print_set();    //������ʾ
void print_exit();   //�˳���ʾ

enum{
	EASY, MID, HARD, FREE //��Ϸ�Ѷ�����
};                   
void print_easy(); //�ƶ���굽��ͬ���Ѷ�����ѡ���ϣ���ģʽ
void print_mid();  //ֻ�����´�ӡ�˵�����,�е�ģʽ
void print_hard(); //����ģʽ
void print_free(); //�Զ���ģʽ

void print_setnumW(int x, int y, int m, int rev);//�Զ����Ѷ����ò˵���ӡ���߶�����
void print_setnumH(int x, int y, int m, int rev);//�������
void print_setnumM(int x, int y, int m, int lim);//��������

void print_win(int score);
void print_over(int score);

#endif //_PRINT_H_