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

	printf("请输入您的选择：\n");
	printf("1：进入车辆。\n2：离开车辆。\n3：打印停车场内车辆信息以及收费历史记录。\n");
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
		printf("请重新输入：\n");
		printf("1：进入车辆。\n2：离开车辆。\n3：打印停车场内车辆信息以及收费历史记录。\n");
		break;
	}
	return 0;
}