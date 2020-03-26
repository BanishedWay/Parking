#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define MAXN 100

typedef struct node {
	char num[10];
	int arrive_hour, arrive_minute, leave_hour, leave_minute;
	struct node* next;
}Car, * Cnode;

typedef struct {
	Cnode car[MAXN];
	int flag[MAXN];
	int length;
}Parking;

typedef struct qnode {
	Cnode data;
	struct qnode* next;
}*queueptr;

typedef struct {
	queueptr front;
	queueptr rear;
}linkqueue;

typedef struct {
	int charge;
	int hour;
	int minute;
}reciept;

void InitParking(Parking* p);
void InitQueue(linkqueue* Q);
void Arrive(Parking* p, linkqueue* Q, int cont);
void Leave(Parking* p, linkqueue* Q);
void Print(Cnode c);
void List(Parking* p);


reciept re[MAXN];
int j = 0;

int main()
{
	Parking parking;
	linkqueue waiting;
	InitParking(&parking);
	InitQueue(&waiting);
	printf("请输入您的选择：\n\n");
	printf("1：进入车辆。\n2：离开车辆。\n3：打印停车场内车辆信息以及收费历史记录。\n0：退出\n\n");
	int count;
	while (scanf("%d", &count) == 1)
	{
		printf("\n");
		switch (count)
		{
		case 1:
			Arrive(&parking, &waiting, 0);
			break;
		case 2:
			Leave(&parking, &waiting);
			break;
		case 3:
			List(&parking);
			break;
		case 0:
			exit(0);
			break;
		default:
			printf("请重新输入：\n\n");
			printf("1：进入车辆。\n2：离开车辆。\n3：打印停车场内车辆信息以及收费历史记录。\n0：退出\n\n");
			break;
		}
		printf("\n请输入您的选择：\n\n");
		printf("1：进入车辆。\n2：离开车辆。\n3：打印停车场内车辆信息以及收费历史记录。\n0：退出\n\n");
	}
	return 0;
}

void InitParking(Parking* p)
{
	p->length = 0;
	for (int i = 0; i < MAXN; i++)
	{
		p->flag[i] = 0;
		p->car[i] = (Cnode)malloc(sizeof(Car));
	}
}

void InitQueue(linkqueue* Q)
{
	Q->front = (queueptr)malloc(sizeof(qnode));
	if (!Q->front)
		return;
	Q->rear = Q->front;
	Q->front->next = NULL;
}

void Arrive(Parking* p, linkqueue* Q, int cont)
{
	Cnode c = (Cnode)malloc(sizeof(Car));
	if (!c)
	{
		return;
	}
	time_t time_p;
	struct tm* temp;
	time(&time_p);
	temp = gmtime(&time_p);
	c->arrive_hour = temp->tm_hour + 8;
	c->arrive_minute = temp->tm_min;
	
	if (cont == 0)//从外部进入停车场和等待区域
	{
		printf("请输入车辆信息：\n");
		printf("请输入车牌号：\n");
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
			return;
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

void Leave(Parking* p, linkqueue* Q)
{
	if (p->length <= 0)
	{
		printf("停车场中没有车。\n");
		return;
	}
	int i;
	printf("请输入车停靠的位置：\n\n");
	scanf("%d", &i);
	time_t time_p;
	struct tm* temp;
	time(&time_p);
	temp = gmtime(&time_p);
	p->car[i - 1]->leave_hour = temp->tm_hour + 8;
	p->car[i - 1]->leave_minute = temp->tm_min;
	p->length--;
	p->flag[i - 1] = 0;
	Print(p->car[i - 1]);
	if (Q->front == Q->rear)
	{
		printf("等待队列中无车\n\n");
	}
	else
	{
		Arrive(p, Q, 1);
	}
	return;
}

void Print(Cnode c)
{
	printf("离开车的车牌号：%s\n\n", c->num);
	printf("离开车的进入时间：%d:%d\n\n", c->arrive_hour, c->arrive_minute);
	printf("离开车的离开时间：%d:%d\n\n", c->leave_hour, c->leave_minute);
	int charge = c->leave_hour - c->arrive_hour;
	printf("停车花费：%d 元\n", charge);
	re[j].charge = charge;
	re[j].hour = c->leave_hour;
	re[j++].minute = c->leave_minute;
	free(c);
}

void List(Parking* p)
{
	if (p->length > 0)
	{
		printf("停车信息表：\n\n");
		for (int i = 0; i < p->length; i++)
		{
			printf("第%d辆车： 车牌号： %s, 进入时间： %d:%d。\n\n", i + 1, p->car[i]->num, p->car[i]->arrive_hour, p->car[i]->arrive_minute);
		}
	}
	else
		printf("停车场内没有车。\n\n");
	printf("收费记录表：\n\n");
	for (int i = 0; i < j; i++)
	{
		printf("%d:%d：%d元\n", re[i].hour, re[i].minute, re[i].charge);
	}
	printf("\n");
}
