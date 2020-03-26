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
	if (cont == 0)//���ⲿ����ͣ�����͵ȴ�����
	{
		printf("�����복����Ϣ��\n");
		printf("�����복�ƺţ�");
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
	else//�г��뿪��ȴ����в�Ϊ��ʱ���ӵȴ����н���ͣ����
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
}//contΪ0ʱ�����ⲿ������룬cont=1ʱ���ӵȴ�������롣

void Leave(Parking *p, linkqueue *Q)
{
	int i;
	printf("�����복ͣ����λ�ã�\n");
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
		printf("�ȴ��������޳�\n");
	}
	else
	{
		Arrive(p, Q, 1);
	}
}

void Print(Cnode c)
{
	printf("�뿪���ĳ��ƺţ�%s\n", c->num);
	printf("�뿪���Ľ���ʱ�䣺%d\n", c->arrive_time);
	printf("�뿪�����뿪ʱ�䣺%d\n", c->leave_time);
	int charge = c->leave_time - c->arrive_time;
	printf("ͣ�����ѣ�%d Ԫ\n", charge);
	free(c);
}

void List(Parking *p)
{
	if (p->length > 0)
	{
		printf("ͣ����Ϣ��\n");
		for (int i = 0; i < p->length; i++)
		{
			printf("��%d���������ƺţ�%s,����ʱ�䣺%d��\n", i + 1, p->car[i]->num, p->car[i]->arrive_time);
		}
	}
	else
		printf("ͣ������û�г���\n");
	printf("�շѼ�¼��\n");
}
