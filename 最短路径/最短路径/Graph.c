#include"Graph.h"

//初始化邻接矩阵表示的有向带权图
void InitMatrix(adjmatrix G)
{
	int  i, j;
	for (i = 0; i < MaxVerNum; i++)
	for (j = 0; j < MaxVerNum; j++)
		G[i][j] = MaxValue;
}

//建立邻接矩阵表示的有权带向图(即通过输入图的每条边建立图的邻接矩阵)
void CreateMatrix(adjmatrix G)
{
	int i, j, x;
	cout << "请输入顶点和相应的权值: " << endl;

	cin >> i >> j >> x;
	while (i != -1)
	{
		G[i][j] = x;
		cin >> i >> j >> x;
	}
}

//输出邻接矩阵表示的有向带权图(即输出图的每条边)
void PrintMatrix(adjmatrix G, int n)
{
	int i, j;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (G[i][j] == MaxValue)
				cout << setiosflags(ios::left) << setw(5) << "Inf";
			else
				cout << setiosflags(ios::left) << setw(5) << G[i][j];
		}
		cout << endl;
	}
}

void Path(edgenode * path[], int m, int j)
{
	edgenode * p, *q, *s;
	p = path[j];
	while (p != NULL)
	{
		path[j] = p->next;
		delete p;
		p = path[j];
	}

	p = path[m];
	while (p != NULL)
	{
		q = new edgenode;
		q->adjvex = p->adjvex;
		if (path[j] == NULL)
			path[j] = q;
		else
			s->next = q;
		s = q;
		p = p->next;
	}

	q = new edgenode;
	q->adjvex = j;
	q->next = NULL;
	s->next = q;
}

//求最短路径的Dijkstral算法
void Dijkstra(adjmatrix GA, int dist[], edgenode *path[], int i, int n)
{
	int j, k, w, m;
	bool * s = new bool[n];
	for (j = 0; j < n; j++)
	{
		if (j == i)
			s[j] = true;
		else
			s[j] = false;
		dist[j] = GA[i][j];
		if (dist[j] < MaxValue && j != i)
		{
			edgenode * p1 = new edgenode;
			edgenode * p2 = new edgenode;
			p1->adjvex = i;
			p2->adjvex = j;
			p2->next = NULL;
			p1->next = p2;
			path[j] = p1;
		}
		else
			path[j] = NULL;
	}
	for (k = 1; k <= n - 2; k++)
	{
		w = MaxValue;
		m = i;

		for (j = 0; j < n; j++)
		if (s[j] == false && dist[j] < w)
		{
			w = dist[j];
			m = j;
		}

		if (m != i)
			s[m] = true;
		else
			break;

		for (j = 0; j < n; j++)
		if (s[j] == false && dist[m] + GA[m][j] < dist[j])
		{
			dist[j] = dist[m] + GA[m][j];
			Path(path, m, j);
		}
	}
	delete[]s;
}

//输出从源点到每个顶点的最短路径及长度的函数
void PrintPath(int dist[], edgenode * path[], int i, int n)
{
	int j;
	for (j = 0; j < n; j++)
	{
		if (i != j)
		{
			cout << "顶点v" << i << "到顶点v" << j << "的最短路径的长度为 "
				<< dist[j] << ", 最短路径为: ";
			edgenode * p = path[j];
			while (p != NULL)
			{
				cout << setw(4) << p->adjvex;
				p = p->next;
			}
			cout << endl;
		}
	}
}
