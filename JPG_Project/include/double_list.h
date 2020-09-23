#ifndef _DOUBLE_LIST_H
#define _DOUBLE_LIST_H


//头文件

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//全局变量与结构体
typedef	struct pic_path_node{
	char pic_path[32];
	
	struct pic_path_node *prev;
	struct pic_path_node *next;
}Pic_Node ,*pNode; 


pNode d_list;
pNode  p;


//宏定义



//函数声明

pNode Create_List();
pNode Create_Node(char pic_path[]);
bool Insert_Node(pNode list, pNode newnode);
void Delete_List(pNode list);



#endif


