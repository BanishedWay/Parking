#include<stdio.h>
#include"myFunction.h"

reciept re[MAXN];

#define MAXN 100

int main()
{
	Parking parking;
	linkqueue waiting;
	InitParking(&parking);
	InitQueue(&waiting);

	printf("����������ѡ��\n");
	printf("1�����복����\n2���뿪������\n3����ӡͣ�����ڳ�����Ϣ�Լ��շ���ʷ��¼��\n");
	int count;
	scanf("%d", &count);
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
	default:
		printf("���������룺\n");
		printf("1�����복����\n2���뿪������\n3����ӡͣ�����ڳ�����Ϣ�Լ��շ���ʷ��¼��\n");
		break;
	}
	return 0;
}