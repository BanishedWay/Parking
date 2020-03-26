#include<stdlib.h>
#include<time.h>

#define MAXN 100

typedef struct node{
	char num[10];
	int arrive_time, leave_time;
	struct node* next;
}Car,*Cnode;

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

typedef struct reciept {
	int charge;
	int time;
};

void InitParking(Parking *p);
void InitQueue(linkqueue *Q);
void Arrive(Parking *p, linkqueue *Q, int cont);
void Leave(Parking *p, linkqueue *Q);
void Print(Cnode c);
void List(Parking *p);
