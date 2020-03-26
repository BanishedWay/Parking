#include<stdio.h>
#include "myFunction.h"

void InitParking(Parking p)
{
	p->length = 0;
	for (int i = 0; i < MAXN; i++)
	{
		p->flag[i] = 0;
		p->car[i] = (Cnode)malloc(sizeof(Car));
	}
}

void InitQueue(linkqueue Q)
{
	Q->front = (queueptr)malloc(sizeof(qnode));
	if (!Q->front)
		exit(0);
	Q->rear = Q->front;
	Q->front->next = NULL;
}

void arrive(Parking p, linkqueue Q)
{
	Cnode c = (Cnode)malloc(sizeof(Car));
	printf("�����복����Ϣ��\n");
	printf("�����복�ƺţ�");
	scanf("%s", c->num);
	printf("�����뵽��ʱ�䣺");
	scanf("%s", c->arrive_time);
	printf("\n");
	if (p->length < MAXN)
	{
		for (int i = 0; i < MAXN; i++)
		{
			if (p->flag[i] == 0)
			{
				p->car[i] = c;
				p->length++;
				return;
			}
		}
	}
	else
	{
		queueptr q = (queueptr)malloc(sizeof(qnode));
		if (!p)
		{
			exit(0);
		}
		q->data = c;
		q->next = NULL;
		Q->rear->next = q;
		Q->rear = q;		
	}
}
