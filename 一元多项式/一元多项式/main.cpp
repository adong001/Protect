#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#define MAX 20

typedef struct
{
	float coef;
	int exp;
}PolyArray[MAX];;


typedef struct pnode

{
	float coef;
	int exp;
	struct pnode *next;
}PolyNode;

void DispPoly(PolyNode *L)

{
	PolyNode *p = L->next;
	while (p != NULL)
	{
		printf("(");
		printf("%gX^%d", p->coef, p->exp);
		printf(") ");
		if (p->next != NULL)printf("+");
		p = p->next;
	}
	printf("\n");
}




void  CreateListR(PolyNode  * &L, PolyArray a, int  n)
{
	PolyNode *s, *r; int i;
	L = (PolyNode *)malloc(sizeof(PolyNode));
	L->next = NULL;
	r = L;
	for (i = 0; i<n; i++)
	{
		s = (PolyNode  *)malloc(sizeof(PolyNode));
		s->coef = a[i].coef;
		s->exp = a[i].exp;
		s->next = NULL;
		r->next = s;
		r = s;
	}
	r->next = NULL;
}


void Sort(PolyNode * &head)
{
	PolyNode  *p = head->next, *q, *r;
	if (p != NULL)
	{
		r = p->next;
		p->next = NULL;
		p = r;
		while (p != NULL)
		{
			r = p->next;
			q = head;
			while (q->next != NULL && q->next->exp >p->exp)
				q = q->next;
			p->next = q->next;
			q->next = p;
			p = r;
		}
	}
}


void Add(PolyNode  *ha,
	PolyNode * hb, PolyNode  *&hc)
{
	PolyNode*pa = ha->next, *pb = hb->next, *s, *tc;
	float c;
	hc = (PolyNode*)malloc(sizeof(PolyNode));
	tc = hc;
	while (pa != NULL && pb != NULL)
	{
		if (pa->exp > pb->exp)
		{
			s = (PolyNode*)malloc(sizeof(PolyNode));
			s->exp = pa->exp; s->coef = pa->coef;
			s->next = NULL;

			tc->next = s; tc = s;
			pa = pa->next;
		}
		else if (pa->exp <pb->exp)
		{
			s = (PolyNode *)malloc(sizeof(PolyNode));
			s->exp = pb->exp; s->coef = pb->coef;
			s->next = NULL;
			tc->next = s; tc = s;
			pb = pb->next;
		}
		else {
			c = pa->coef + pb->coef;
			if (c)
			{
				s = (PolyNode *)malloc(sizeof(PolyNode));
				s->exp = pa->exp; s->coef = c;
				s->next = NULL;
				tc->next = s; tc = s;
			}
			pa = pa->next;
			pb = pb->next;
		}
	}
	if (pb != NULL) pa = pb;
	while (pa != NULL)
	{
		s = (PolyNode*)malloc(sizeof(PolyNode));
		s->exp = pa->exp; s->coef = pa->coef;
		s->next = NULL;
		tc->next = s; tc = s;
		pa = pa->next;
	}
	tc->next = NULL;
}


int main()

{
	PolyNode *ha, *hb, *hc;
	PolyArray a = { { 1.2, 0 }, { 2.5, 1 }, { 3.2, 3 }, { -2.5, 5 } };
	PolyArray b = { { -1.2, 0 }, { 2.5, 1 }, { 3.2, 3 }, { 2.5, 5 }, { 5.4, 10 } };
	CreateListR(ha, a, 4);
	CreateListR(hb, b, 5);
	printf("原多项式A ："); DispPoly(ha);
	printf("原多项式 B ："); DispPoly(hb);



	Sort(ha);
	Sort(hb);
	printf("有序多项式A :"); DispPoly(ha);
	printf("有序多项式B :"); DispPoly(hb);

	Add(ha, hb, hc);
	printf("多项式相加："); DispPoly(hc);
	system("pause");
	return 0;
}