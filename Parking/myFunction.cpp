#include<stdio.h>
#include "myFunction.h"

void InitParking(Parking *p)
{
	p->length = 0;
	for (int i = 0; i < MAXN; i++)
	{
		p->flag[i] = 0;
		p->car[i] = (Cnode)malloc(sizeof(Car));
	}
}

void InitQueue(linkqueue *Q)
{
	Q->front = (queueptr)malloc(sizeof(qnode));
	if (!Q->front)
		exit(0);
	Q->rear = Q->front;
	Q->front->next = NULL;
}

void Arrive(Parking *p, linkqueue *Q, int cont)
{
	Cnode c = (Cnode)malloc(sizeof(Car));
	time_t time_p;
	struct tm* temp;
	time(&time_p);
	temp = gmtime(&time_p);
	c->arrive_time = temp->tm_hour;
	if (cont == 0)//从外部进入停车场和等待区域
	{
		printf("请输入车辆信息：\n");
		printf("请输入车牌号：");
		scanf("%s", c->num);
		if (p->length < MAXN)
		{
			for (int i = 0; i < MAXN; i++)
			{
				if (p->flag[i] == 0)
				{
					p->car[i] = c;
					p->length++;
					break;
				}
			}
		}
		else
		{
			queueptr q = (queueptr)malloc(sizeof(qnode));
			if (!q)
			{
				exit(0);
			}
			q->data = c;
			q->next = NULL;
			Q->rear->next = q;
			Q->rear = q;
		}
	}
	else//有车离开后等待队列不为空时，从等待队列进入停车场
	{
		queueptr q = (queueptr)malloc(sizeof(qnode));
		if (!q)
		{
			exit(0);
		}
		q = Q->front->next;
		Q->front->next = q->next;
		Cnode tc = q->data;
		if (Q->rear == q) {
			Q->rear = Q->front;
		}
		c = q->data;
		for (int i = 0; i < MAXN; i++)
		{
			if (p->flag[i] == 0)
			{
				p->car[i] = c;
				p->length++;
				break;
			}
		}
		free(q);
	}
	free(c);
	return;
}//cont为0时，从外部区域进入，cont=1时，从等待区域进入。

void Leave(Parking *p, linkqueue *Q)
{
	int i;
	printf("请输入车停靠的位置：\n");
	scanf("%d", &i);
	time_t time_p;
	struct tm* temp;
	time(&time_p);
	temp = gmtime(&time_p);
	p->car[i - 1]->leave_time = temp->tm_hour;
	p->length--;
	p->flag[i - 1] = 0;
	Print(p->car[i - 1]);
	if (Q->front == Q->rear)
	{
		printf("等待队列中无车\n");
	}
	else
	{
		Arrive(p, Q, 1);
	}
}

void Print(Cnode c)
{
	printf("离开车的车牌号：%s\n", c->num);
	printf("离开车的进入时间：%d\n", c->arrive_time);
	printf("离开车的离开时间：%d\n", c->leave_time);
	int charge = c->leave_time - c->arrive_time;
	printf("停车花费：%d 元\n", charge);
	free(c);
}

void List(Parking *p)
{
	if (p->length > 0)
	{
		printf("停车信息表：\n");
		for (int i = 0; i < p->length; i++)
		{
			printf("第%d辆车：车牌号：%s,进入时间：%d。\n", i + 1, p->car[i]->num, p->car[i]->arrive_time);
		}
	}
	else
		printf("停车场内没有车。\n");
	printf("收费记录表：\n");
}
