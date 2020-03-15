#include"Graph.h"

int main()
{
	int i, n;
	cout << "输入你所输入的有向带权图的顶点个数: ";
	cin >> n;
	adjmatrix g;
	InitMatrix(g);
	CreateMatrix(g);
	cout << "你输入的有向带权图的邻接矩阵表示为: " << endl;
	PrintMatrix(g, n);
	int * d = new int[n];
	edgenode ** path = new edgenode *[n];
	cout << "请输入你要输入的源点: ";
	cin >> i;
	Dijkstra(g, d, path, i, n);
	PrintPath(d, path, i, n);
	return 0;
}
