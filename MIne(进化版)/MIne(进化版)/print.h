#ifndef _PRINT_H_
#define _PRINT_H_

#define PAGE_NUM 3     
//printSence[PAGE_NUM]()主菜单函数数组的数组大小
#define SET_NUM 4      
//printSet[SET_NUM]()游戏难度设置函数数组的数组大小
#define FREESET_NUM 3  
//printFreeSet[FREESET_NUM]()游戏难度自定义函数数组的数组大小
enum
{
	START = 0, //游戏主菜单的开始，设置，退出
	SET,
	EXIT,
};

void print_start();  //开始游戏显示(所有光标移动只是重新打印菜单而已)
void print_set();    //设置显示
void print_exit();   //退出显示

enum{
	EASY, MID, HARD, FREE //游戏难度设置
};                   
void print_easy(); //移动光标到不同的难度设置选项上，简单模式
void print_mid();  //只是重新打印菜单而已,中等模式
void print_hard(); //困难模式
void print_free(); //自定义模式

void print_setnumW(int x, int y, int m, int rev);//自定义难度设置菜单打印，高度设置
void print_setnumH(int x, int y, int m, int rev);//宽度设置
void print_setnumM(int x, int y, int m, int lim);//雷数设置

void print_win(int score);
void print_over(int score);

#endif //_PRINT_H_