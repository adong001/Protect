#ifndef _MAP_H_
#define _MAP_H_

#define MAXLINE 24  //����ģʽ���̴�С
#define MAXROW 30

#define MINLINE 9   //��ģʽ���̴�С
#define MINROW 9

#define DEFLINE 16  //�е�ģʽ���̴�С
#define DEFROW  16
#define DEFMINE 40  //�����̶����䣬�ı����̴�С����Ϸ�ѶȲŻ�ı�

#define ARROW_UP    0xE048  //�������Ҽ���ֵ
#define ARROW_DOWN  0xE050
#define ARROW_LEFT  0xE04B
#define ARROW_RIGHT 0xE04D

#define DEFSIGN(a) ((a) / 2)

enum{
	MINE = -1, //-1��ʾ����
	BLANK      //0 ��ʾ������
};

enum{
	COVEREDNUM,
	DISPLAYNUM,
	MARKEDMINE
};

extern char g_map[MAXLINE + 2][MAXROW + 2]; //�������飬-1�������ף�0��������
extern char g_markMap[MAXLINE + 2][MAXROW + 2];//������ʾ���飬ɨ����Χ8������û��Ϊ�� ����
//��������ʾ��Χ8�������м����׵����֣�δɨ��Ϊ����������Ϊ���衯�����Ϊ����������Ǵ���Ϊ������
extern int g_win;   //��¼����Ƿ�ʤ����0����ʤ��

typedef struct{
	int x;
	int y;
}SIGN;


void makeMap(int x, int y, int m, SIGN point);
int countMine(int i, int j);
int setMap(int x, int y, int pointx, int pointy);
int setMapNum(int x, int y, SIGN point);

void printMap(int x, int y, int flag, SIGN point, int m);
void printWin(int x, int y, int m);
void printOver(int x, int y, int m);
#endif //_MAP_H_