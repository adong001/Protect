#ifndef _MAP_H_
#define _MAP_H_

#define MAXLINE 24  //困难模式棋盘大小
#define MAXROW 30

#define MINLINE 9   //简单模式棋盘大小
#define MINROW 9

#define DEFLINE 16  //中等模式棋盘大小
#define DEFROW  16
#define DEFMINE 40  //雷数固定不变，改变棋盘大小，游戏难度才会改变

#define ARROW_UP    0xE048  //上下左右键的值
#define ARROW_DOWN  0xE050
#define ARROW_LEFT  0xE04B
#define ARROW_RIGHT 0xE04D

#define DEFSIGN(a) ((a) / 2)

enum{
	MINE = -1, //-1表示是雷
	BLANK      //0 表示不是雷
};

enum{
	COVEREDNUM,
	DISPLAYNUM,
	MARKEDMINE
};

extern char g_map[MAXLINE + 2][MAXROW + 2]; //棋盘数组，-1代表有雷，0代表不是雷
extern char g_markMap[MAXLINE + 2][MAXROW + 2];//棋盘显示数组，扫开周围8个格子没雷为‘ ’，
//有雷则显示周围8个格子有几个雷的数字，未扫开为‘■’，雷为‘¤’，标记为‘△’，标记错误为‘×’
extern int g_win;   //记录这局是否胜利，0代表胜利

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