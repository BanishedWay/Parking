#include<stdlib.h>

#define MAXN 100

typedef struct node{
	char num[10];
	char arrive_time[10], leave_time[10];
	struct node* next;
}Car,*Cnode;

typedef struct {
	Cnode car[MAXN];
	int flag[MAXN];
	int length;
}*Parking;

typedef struct qnode {
	Cnode data;
	struct qnode* next;
}*queueptr;

typedef struct {
	queueptr front;
	queueptr rear;
}*linkqueue;

void InitParking(Parking p);
void InitQueue(linkqueue Q);
void arrive(Parking p, linkqueue Q);

