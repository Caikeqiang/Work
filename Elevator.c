#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<windows.h>
typedef struct elevator
{
	int staus;//三种状态：静止，上行，下行
	int type;//三种类型：双，单，全
	int floor;//此时停在的楼层数
	int beixuyao;//此楼层是否被调用
	int flag;//是否有人用电梯
}B;
B a[4];
int flag, dir, floor, gofloor;
int c[3], k[3], m[3];
int Lookfor(int x, int y, int z)//查找电梯函数
{
	int c;
	if (a[x].staus == 0)//此时a[x]电梯处于静止状态
	{
		if (y < z)
		{
			c = z - y;
		}
		else
		{
			c = y - z;
		}
	}
	if (a[x].staus == 1)//此时a[x]电梯处于上升状态
	{
		if (y > z && dir == 1)
		{
			c = y - z;
		}
		else
		{
			printf("此电梯不能响应用户的请求");
		}
	}
	if (a[x].staus == 2)//此时a[x]电梯处于下降状态
	{
		if (y < z && dir == 0)
		{
			c = z - y;
		}
		else
		{
			printf("此电梯不能响应用户的请求");
		}
	}
	return c;
}
void main()
{
	//接人操作
	printf("       ----       ----       ----       ---- \n");
	printf("      |    |     |    |     |    |     |    |\n");
	printf("        1           3         4          20  \n");
	printf("      |    |     |    |     |    |     |    |\n");
	printf("       ----       ----       ----       ---- \n");
	a[0].staus = 0;//静止
	a[1].staus = 0;//静止
	a[2].staus = 0;//静止
	a[3].staus = 0;//静止
	a[0].floor = 1;//表示此时电梯停在的楼层数为1楼
	a[1].floor = 3;//表示此时电梯停在的楼层数为3楼
	a[2].floor = 4;//表示此时电梯停在的楼层数为4楼
	a[3].floor = 20;//表示此时电梯停在的楼层数为20楼
	while (1)
	{
		a[0].type = 2;//一号电梯所有楼层都停靠
		a[1].type = 1;//二号电梯单号楼层都停靠
		a[2].type = 0;//三号电梯双号楼层都停靠
		a[3].type = 2;//四号电梯所有楼层都停靠
		int i;
		int flag1 = 0, j = 0;
		printf("----------------------------------------------\n");
		printf("若要用电梯请按按钮 1 ！\n");
		scanf("%d", &flag);//此时是否有人按电梯
		if (flag == 1)
		{
			printf("*****此时有用户按电梯！*****\n");
		}
		printf("用户所在楼层为: ");
		scanf("%d", &floor);//此时按电梯的人所在的楼层数
		printf("上楼请按 1 ，下楼请按 0: ");
		scanf("%d", &dir);//用户请求是上楼还是下楼标记
		printf("请选择要去的楼层: ");
		scanf("%d", &gofloor);//用户要去的楼层
		if (flag == 1)//用户按电梯
		{
			if (dir == 1)//用户要上楼
			{
				if (floor % 2 == 0)//用户所在为偶数楼层
				{
					if (gofloor % 2 == 1)//用户要去奇数楼层
					{
						for (i = 0; i < 4; i++)
						{
							if (a[i].type == 2)
							{
								a[i].beixuyao = 1;
							}
							else
							{
								a[i].beixuyao = 0;
							}
							while (a[i].beixuyao == 1)
							{
								k[flag1] = Lookfor(i, floor, a[i].floor);//此处调用计算楼层差值函数
								m[flag1] = i;
								flag1++;
								a[i].beixuyao = 0;
							}
						}
						if (k[0] < k[1])
						{
							printf("离用户最近并且符合条件的电梯为：1\n");
							a[0].floor = gofloor;
							a[0].staus = 0;
						}
						else
						{
							printf("离用户最近并且符合条件的电梯为：4\n");
							a[3].floor = gofloor;
							a[3].staus = 0;
						}
					}
					if (gofloor % 2 == 0)//用户要去偶数楼层
					{
						for (i = 0; i < 4; i++)
						{
							if (a[i].type == 2 || a[i].type == 0)
							{
								a[i].beixuyao = 1;
							}
							else
							{
								a[i].beixuyao = 0;
							}
							while (a[i].beixuyao == 1)
							{
								k[flag1] = Lookfor(i, floor, a[i].floor);
								m[flag1] = i;
								flag1++;
								a[i].beixuyao = 0;
							}
						}
						if (k[0] < k[1])
						{
							if (k[0] < k[2])
							{
								printf("离用户最近并且符合条件的电梯为：1\n");
								a[0].floor = gofloor;
								a[0].staus = 0;
							}
							else
							{
								printf("离用户最近并且符合条件的电梯为：4\n");
								a[3].floor = gofloor;
								a[3].staus = 0;
							}
						}
						else
						{
							if (k[1] < k[2])
							{
								printf("离用户最近并且符合条件的电梯为：3\n");
								a[2].floor = gofloor;
								a[2].staus = 0;
							}
							else
							{
								printf("离用户最近并且符合条件的电梯为：4\n");
								a[3].floor = gofloor;
								a[3].staus = 0;
							}
						}
					}
				}
				if (floor % 2 == 1)//用户所在为奇数楼层
				{
					if (gofloor % 2 == 0)//用户要去偶数楼层
					{
						for (i = 0; i < 4; i++)
						{
							if (a[i].type == 2)
							{
								a[i].beixuyao = 1;
							}
							else
							{
								a[i].beixuyao = 0;
							}
							while (a[i].beixuyao == 1)
							{
								k[flag1] = Lookfor(i, floor, a[i].floor);
								m[flag1] = i;
								flag1++;
								a[i].beixuyao = 0;
							}
						}
						if (k[0] < k[1])
						{
							printf("离用户最近并且符合条件的电梯为：1\n");
							a[0].floor = gofloor;
							a[0].staus = 0;
						}
						else
						{
							printf("离用户最近并且符合条件的电梯为：4\n");
							a[3].floor = gofloor;
							a[3].staus = 0;
						}
					}
					if (gofloor % 2 == 1)//用户要去奇数楼层
					{
						for (i = 0; i < 4; i++)
						{
							if (a[i].type == 2 || a[i].type == 1)
							{
								a[i].beixuyao = 1;
							}
							else
							{
								a[i].beixuyao = 0;
							}
							while (a[i].beixuyao == 1)
							{
								k[flag1] = Lookfor(i, floor, a[i].floor);
								m[flag1] = i;
								flag1++;
								a[i].beixuyao = 0;
							}
						}
						if (k[0] < k[1])
						{
							if (k[0] < k[2])
							{
								printf("离用户最近并且符合条件的电梯为：1\n");
								a[0].floor = gofloor;
								a[0].staus = 0;
							}
							else
							{
								printf("离用户最近并且符合条件的电梯为：4\n");
								a[3].floor = gofloor;
								a[3].staus = 0;
							}
						}
						else
						{
							if (k[1] < k[2])
							{
								printf("离用户最近并且符合条件的电梯为：2\n");
								a[1].floor = gofloor;
								a[1].staus = 0;
							}
							else
							{
								printf("离用户最近并且符合条件的电梯为：4\n");
								a[3].floor = gofloor;
								a[3].staus = 0;
							}
						}
					}
				}
			}
			if (dir == 0)//用户要下楼
			{
				if (floor % 2 == 0)//用户所在为偶数楼层
				{
					if (gofloor % 2 == 1)//用户要去奇数楼层
					{
						for (i = 0; i < 4; i++)
						{
							if (a[i].type == 2)
							{
								a[i].beixuyao = 1;
							}
							else
							{
								a[i].beixuyao = 0;
							}
							while (a[i].beixuyao == 1)
							{
								k[flag1] = Lookfor(i, floor, a[i].floor);
								m[flag1] = i;
								flag1++;
								a[i].beixuyao = 0;
							}
						}
						if (k[0] < k[1])
						{
							printf("离用户最近并且符合条件的电梯为：1\n");
							a[0].floor = gofloor;
							a[0].staus = 0;
						}
						else
						{
							printf("离用户最近并且符合条件的电梯为：4\n");
							a[3].floor = gofloor;
							a[3].staus = 0;
						}
					}
					if (gofloor % 2 == 0)//用户要去偶数楼层
					{
						for (i = 0; i < 4; i++)
						{
							if (a[i].type == 2 || a[i].type == 0)
							{
								a[i].beixuyao = 1;
							}
							else
							{
								a[i].beixuyao = 0;
							}
							while (a[i].beixuyao == 1)
							{
								k[flag1] = Lookfor(i, floor, a[i].floor);
								m[flag1] = i;
								flag1++;
								a[i].beixuyao = 0;
							}
						}
						if (k[0] < k[1])
						{
							if (k[0] < k[2])
							{
								printf("离用户最近并且符合条件的电梯为：1\n");
								a[0].floor = gofloor;
								a[0].staus = 0;
							}
							else
							{
								printf("离用户最近并且符合条件的电梯为：4\n");
								a[3].floor = gofloor;
								a[3].staus = 0;
							}
						}
						else
						{
							if (k[1] < k[2])
							{
								printf("离用户最近并且符合条件的电梯为：3\n");
								a[2].floor = gofloor;
								a[2].staus = 0;
							}
							else
							{
								printf("离用户最近并且符合条件的电梯为：4\n");
								a[3].floor = gofloor;
								a[3].staus = 0;
							}
						}
					}
				}
				if (floor % 2 == 1)//用户所在为奇数楼层
				{
					if (gofloor % 2 == 0)//用户要去偶数楼层
					{
						for (i = 0; i < 4; i++)
						{
							if (a[i].type == 2)
							{
								a[i].beixuyao = 1;
							}
							else
							{
								a[i].beixuyao = 0;
							}
							while (a[i].beixuyao == 1)
							{
								k[flag1] = Lookfor(i, floor, a[i].floor);
								m[flag1] = i;
								flag1++;
								a[i].beixuyao = 0;
							}
						}
						if (k[0] < k[1])
						{
							printf("离用户最近并且符合条件的电梯为：1\n");
							a[0].floor = gofloor;
							a[0].staus = 0;
						}
						else
						{
							printf("离用户最近并且符合条件的电梯为：4\n");
							a[3].floor = gofloor;
							a[3].staus = 0;
						}
					}
					if (gofloor % 2 == 1)//用户要去奇数楼层
					{
						for (i = 0; i < 4; i++)
						{
							if (a[i].type == 2 || a[i].type == 1)
							{
								a[i].beixuyao = 1;
							}
							else
							{
								a[i].beixuyao = 0;
							}
							while (a[i].beixuyao == 1)
							{
								k[flag1] = Lookfor(i, floor, a[i].floor);
								m[flag1] = i;
								flag1++;
								a[i].beixuyao = 0;
							}
						}
						if (k[0] < k[1])
						{
							if (k[0] < k[2])
							{
								printf("离用户最近并且符合条件的电梯为：1\n");
								a[0].floor = gofloor;
								a[0].staus = 0;
							}
							else
							{
								printf("离用户最近并且符合条件的电梯为：4\n");
								a[3].floor = gofloor;
								a[3].staus = 0;
							}
						}
						else
						{
							if (k[1] < k[2])
							{
								printf("离用户最近并且符合条件的电梯为：2\n");
								a[1].floor = gofloor;
								a[1].staus = 0;
							}
							else
							{
								printf("离用户最近并且符合条件的电梯为：4\n");
								a[3].floor = gofloor;
								a[3].staus = 0;
							}
						}
					}
				}
			}
		}
		else if (flag == 0)
		{
			printf("此时无人用电梯");
		}
		printf("       ----       ----       ----       ---- \n");
		printf("      |    |     |    |     |    |     |    |\n");
		printf("        %d         %d          %d         %d  \n", a[0].floor, a[1].floor, a[2].floor, a[3].floor);
		printf("      |    |     |    |     |    |     |    |\n");
		printf("       ----       ----       ----       ---- \n");
		printf("\n");
		printf("----------------------------------------------\n");
	}
}
