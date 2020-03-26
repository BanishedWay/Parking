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
	printf("请输入车辆信息：\n");
	printf("请输入车牌号：");
	scanf("%s", c->num);
	printf("请输入到达时间：");
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
