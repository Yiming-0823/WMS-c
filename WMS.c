#define _CRT_SECURE_NO_WARNINGS//消除scanf警告
#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#define true 1
#define false 0

//以下是声明
//***************
typedef int bool;
typedef struct Goods
{
	char name[100]; // 名称 
	int count; // 数量 

}Goods,*Good;

//进货，对应进货模块，表示当前进货一批数量为count的name商品
bool add_goods(char name[], int count);
//更新库存信息，对应增加库存子功能，对name商品新增count数量
bool add_count(char name[], int count);
//更新库存列表，对应新增商品子功能，新增name
bool add_to_list(char name[], int count);

//出货，对应出货模块，表示当前出货一批数量为count的name商品
bool delete_goods(char name[], int count);
//更新库存信息，对应减少库存子功能，对name商品减少count数量
bool delete_count(char name[], int count);
//更新库存列表，对应删除商品子功能，删除商品列表中name商品
bool delete_from_list(char name[]);

///显示当前库存列表，包括商品名及其库存量
void show_goods();
//查看仓库中的name商品
 Good find_goods(char name[]);
//文件读取
void open();
//文件保存
void save();

struct Goods food[100];
int S = 0;  //货物数-1

//入库函数

bool add_goods(char name[], int count)
{
	Good good;
	good = find_goods(name);

	if (good->count == 0) {//判断是否有该货物
		printf("\t新增物品： % s\n",name);
		add_to_list(name, count);
	}
	else {
		add_count(name, count);
	}
	printf("\t入库成功！\n");
	printf("\t名称： % s\n\t现有数量： % d\n", good->name, good->count);
	save();
	return true;
}

//更新库存信息，对应增加库存子功能，对name商品新增count数量
bool add_count(char name[], int count)
{
	Good good;
	good = find_goods(name);
	good->count += count;
	return true;
}
//更新库存列表，对应新增商品子功能，新增name
bool add_to_list(char name[], int count)
{
	S++;
	strcpy(food[S].name, name);
	food[S].count = count;
	return true;
}
//出库函数
bool delete_goods(char name[], int count)
{
	Good good;
	good = find_goods(name);

	if (count > good->count && good->count != 0) {
		printf("\t货物不足\n");
		return false;
	}
	else 
		if (good->count == 0) 
	{
		printf("\t没有此货物\n");
		return false;
		}
	else
	{
		delete_count(name, count);
		if (good->count==0)
		{
			printf("\t出库成功！\n");
			printf("\t%s已售罄\n", good->name);
			delete_from_list(name);
		}
		else{
			printf("\t出库成功！\n");
			printf("\t名称： % s\n\t剩余数量： % d\n", good->name, good->count);
		} 
	}
	save();
	return true;
}
//更新库存信息，对应减少库存子功能，对name商品减少count数量
bool delete_count(char name[], int count)
{

	Good good;
	good = find_goods(name);
	good->count -= count;
	return true;
}
//更新库存列表，对应删除商品子功能，删除商品列表中name商品
bool delete_from_list(char name[])
{
	int i;
	for (i = 0; i <= S; i++) {
		if (strcmp(name, food[i].name) == 0) {
			break;
		}
	}
	for (; i <= S; i++) {
		food[i] = food[i + 1];
	}
	S--;
	return true;
}

//显示当前库存列表，包括商品名及其库存量
void show_goods()
{
	int i;
	char c;
	printf("\t名称\t数量\n");
	for (i = 0; i <=S; i++)
	{
		printf("\t%s\t %d\n", food[i].name, food[i].count);
	}
	printf("\n\n");
}

//查找函数
 Good find_goods(char name[])
{
	int i;
	Good good;
	for (i = 0; i <= S; i++)
	{
		if (strcmp(name, food[i].name) == 0) {
			return &food[i];
		}
	}

	return  &food[S + 1];
}

//打开文件

void open()
{
	S = 0;
	char file[20] = "D:\Wms.txt";
	FILE* fp;
	if ((fp = fopen(file, "r")) != NULL) {
		while (!feof(fp)) {//结束表示
			if ((fscanf(fp, "%s\t%d\n", &food[S].name, &food[S].count)) == EOF)//文件结束标识
				break;
			//读文件信息
			S++;
		}
		S--;
	}
	else
	{
		printf("文件信息读取失败！\n");
	}
	fclose(fp);
}

//输出到文件

void save()
{
	char file[20] = "D:\Wms.txt";
	FILE* fp;
	int i;
	if ((fp = fopen(file, "w")) != NULL) {
		for (i = 0; i <= S; i++) {//结束表示
			(fprintf(fp, "%s\t%d\n", food[i].name, food[i].count));
			//写文件信息
		}
		printf("\t文件信息保存成功！\n");
	}
	else printf("\t文件信息保存失败！\n");
	fclose(fp);
}

int main()
{
	open();
	char name[20];
	int count = 0;
	///主菜单 
	while (1)
	{
		printf("\t * *******************\n");
		printf("\t * 1、货物出库       * \n");
		printf("\t * 2、货物入库       * \n");
		printf("\t * 3、显示仓库货物表 * \n");
		printf("\t * 4、查询指定货物   * \n");
		printf("\t * 0、退出           * \n");
		printf("\t * *******************\n");
		printf("\t请选择：");
		int a;
		scanf("%d", &a);
		switch (a)
		{
		case 1: 
			printf("\t请输入物品名称:");
			scanf("%s", name);
			printf("\t请输入物品数量:");
			scanf("%d", &count);
			delete_goods(name, count);
			break;
		case 2:
			printf("\t请输入物品名称:");
			scanf("%s", name);
			printf("\t请输入物品数量:");
			scanf("%d", &count);
			add_goods(name, count);
			break;
		case 3: 
			show_goods(); 
			break;
		case 4:
			printf("\t请输入需要查询货物的名称:");
			scanf("%s", &name);
			Good good=find_goods(name);
			if (good->count == 0) {
				printf("\t没有此货品\n");
				break;
			}
			printf("\t名称： % s\n\t数量： % d\n", good->name, good->count);
			break;
		case 0: 
		    printf("\t退出系统") ;
			exit(0);
		}
	}
	return 0;
}
