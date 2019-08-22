#include"3chess.h"
int getKeyBoard()
{
	
	int a = _getch() ;
	int result = ((char)a < 0) ? (a << 8 | _getch()) : a;
	return a;
	getchar();
}

int main()
{
	while (1)
	{
	printf("%d\n",getKeyBoard());
	}

	//game();
	system("pause");
	return 0;
}