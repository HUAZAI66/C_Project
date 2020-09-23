#include "double_list.h"

/*
 *功   能：创建头结点
 *参   数：无
 *返回值：头结点首地址
 */

pNode Create_List()
{
	//申请一块堆内存
	pNode head = (pNode)malloc(sizeof(Pic_Node));
	if (head != NULL)  //成功
	{
		//初始化这块内存
		head->prev = head;
		head->next = head;
		return head;
	}
	else
	{

		printf("CreateHeadNode Failed!\n");
		return NULL;
	}
}

/*
 *
 *
 *
 *功   能：创建数据结点
 *参   数：无
 *返回值：数据结点首地址
 */

pNode Create_Node(char pic_path[])
{
	pNode NewNode = (pNode)malloc(sizeof(Pic_Node));
	if (NewNode != NULL)   //成功
	{
		sprintf(NewNode->pic_path,pic_path);//进行字符串拼接
		//初始化这块内存
		NewNode->next = NULL;    //初始化指针域
		NewNode->prev = NULL;
		
		return NewNode;
	}
	else
	{
		printf("CreateNewNode Failed!\n");
		return NULL;
	}

}


/*
 *功   能：插入节点之尾插法
 *参   数：
 	head 	--->头结点首地址
 *返回值：无
 */

bool Insert_Node(pNode list, pNode newnode)
{

	//2,尾插法
	pNode p = list;
	//把节点添加到链表中
	while(p->next != list)
	{
		//往后遍历
		p = p->next;
	}
	
	newnode->next = p->next;
	p->next = newnode;

	newnode->prev = p;
	list->prev = newnode;


	return true;
}


//删除链表
void Delete_List(pNode list)
{
	if(list->next == list)	//判断链表是否为空
	{
		free(list);
		return;
	}
	pNode p = list;
	pNode q = p;
	while(p != NULL)
	{
		q = p;
		p = p->next;
		free(q);
	}
	free(list);
}



