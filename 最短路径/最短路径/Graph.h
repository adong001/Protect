#include <iostream>
#include <iomanip>
using namespace std;
#define MaxVerNum 20
#define MaxValue 10000
typedef int adjmatrix[MaxVerNum][MaxVerNum];     //邻接矩阵的类型定义

typedef struct Node
{
	int adjvex;
	struct Node * next;
}edgenode;        //指针数组path[]基类型定义

//初始化邻接矩阵表示的有向带权图
void InitMatrix(adjmatrix G);

//建立邻接矩阵表示的有权带向图(即通过输入图的每条边建立图的邻接矩阵)
void CreateMatrix(adjmatrix G);

//输出邻接矩阵表示的有向带权图(即输出图的每条边)
void PrintMatrix(adjmatrix G, int n);

void Path(edgenode * path[], int m, int j);

//求最短路径的Dijkstral算法
void Dijkstra(adjmatrix GA, int dist[], edgenode *path[], int i, int n);

//输出从源点到每个顶点的最短路径及长度的函数
void PrintPath(int dist[], edgenode * path[], int i, int n);
