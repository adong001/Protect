#include <iostream>
#include <iomanip>
using namespace std;
#define MaxVerNum 20
#define MaxValue 10000
typedef int adjmatrix[MaxVerNum][MaxVerNum];     //�ڽӾ�������Ͷ���

typedef struct Node
{
	int adjvex;
	struct Node * next;
}edgenode;        //ָ������path[]�����Ͷ���

//��ʼ���ڽӾ����ʾ�������Ȩͼ
void InitMatrix(adjmatrix G);

//�����ڽӾ����ʾ����Ȩ����ͼ(��ͨ������ͼ��ÿ���߽���ͼ���ڽӾ���)
void CreateMatrix(adjmatrix G);

//����ڽӾ����ʾ�������Ȩͼ(�����ͼ��ÿ����)
void PrintMatrix(adjmatrix G, int n);

void Path(edgenode * path[], int m, int j);

//�����·����Dijkstral�㷨
void Dijkstra(adjmatrix GA, int dist[], edgenode *path[], int i, int n);

//�����Դ�㵽ÿ����������·�������ȵĺ���
void PrintPath(int dist[], edgenode * path[], int i, int n);
