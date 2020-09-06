#include <string.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct LINK_NODE
{
	int data;
	struct LINK_NODE *next;
}LINK_NODE;

LINK_NODE *init_link_list()
{
	LINK_NODE *head = NULL;
	if(NULL == (head = (LINK_NODE *)malloc(sizeof(LINK_NODE))))
		return NULL;
	memset(head,0,sizeof(LINK_NODE));
	head->data = -1;
	head->next = NULL;
	
	LINK_NODE *p_current = head;		//	将指针指向头结点
	int data = 0;						
	while(1)
	{
		printf("请输入数据（输入0结束）:\n");
		scanf("%d",&data);
		//如果输入0，则退出循环
		if (0 == data)
		{
			printf("链表创建完成\n");
			break;
		}
		
		LINK_NODE *new_node = NULL;
		if(NULL == (new_node = (LINK_NODE *)malloc(sizeof(LINK_NODE))))
		{
			printf("无法申请更多空间\n");
			break;
		}
		memset(new_node,0,sizeof(LINK_NODE));
		new_node->data = data;
		new_node->next = NULL;
		
		
		p_current->next = new_node;
		p_current = new_node;
	}
	return head;
}

void traversal_link(LINK_NODE *head)
{
	if(NULL == head)
	{
		printf("该链表没有存储数据\n");
		return;
	}
	
	LINK_NODE *p_current = head->next;
	while(NULL != p_current)
	{
		printf("(本节点地址 %p ",p_current);
		printf("数据 %d\t",p_current->data);
		printf("下一个结点地址 %p )\n",p_current->next);
		p_current = p_current->next;
	}
	//printf("\n链表遍历完成\n");
}
void insert_node(LINK_NODE *head,int val,int data)
{
	if(NULL == head)
		return ;
	LINK_NODE *p_prev = head;
	LINK_NODE *p_current = p_prev->next;
	while(NULL != (p_current->next))
	{
		if(p_current->data == val)
			break;
		p_prev = p_current;
		p_current = p_prev->next;
	}
	
	//如果p_current为NULL，说明不存在值为val的节点
	if (NULL == p_current )
	{
		printf("不存在值为%d的节点!\n",val);
		return;
	}
	
	LINK_NODE *new_node = NULL;
	new_node = (LINK_NODE *)malloc(sizeof(LINK_NODE));
	if(NULL == new_node)
	{
		printf("无法申请更多空间!\n");
		return;
	}	
	memset(new_node,0,sizeof(LINK_NODE));
	//新节点的next指向p_current的下一个结点
	new_node->data = data;
	new_node->next = p_current->next;
	
	p_current->next = new_node;
	
}

void delete_node(LINK_NODE *head,int val)
{
	if(NULL == head)
		return ;
	LINK_NODE *p_prev = head;
	LINK_NODE *p_current = p_prev->next;
	while(NULL != (p_current->next))
	{
		if(p_current->data == val)
			break;
		p_prev = p_current;
		p_current = p_prev->next;
	}
	
	//如果p_current为NULL，说明不存在值为val的节点
	if (NULL == p_current )
	{
		printf("不存在值为%d的节点!\n",val);
		return;
	}
	
	p_prev->next = p_current->next;
	free(p_current);
	p_current = NULL;
}

void destroy_link(LINK_NODE *head)
{
	if(NULL == head)
		return ;
	LINK_NODE *p_current = head;
	while(NULL != p_current)
	{
		LINK_NODE *p_next = p_current->next;
		free(p_current);
		p_current = NULL;
		p_current = p_next;
	}
	printf("链表销毁完成\n");
}



int main()
{
	LINK_NODE *list = NULL;
	list = init_link_list();	//	链表的初始化
	if(NULL == list)
	{
		printf("链表创建失败\n");
	}
	printf("此链表结构为 ：\n");
	traversal_link(list);
	
	int val = 0;
	int data = 0;
	printf("在指定值后面插入数据\n");
	printf("请输入值:\n");
	scanf("%d",&val);
	printf("请输入数据:\n");
	scanf("%d",&data);
	insert_node(list,val,data);
	printf("现在此链表结构为 ：\n");
	traversal_link(list);
	
	printf("删除指定值\n");
	printf("请输入值:\n");
	scanf("%d",&val);
	delete_node(list,val);
	
	printf("现在此链表结构为 ：\n");
	traversal_link(list);
	
	printf("删除链表\n");
	destroy_link(list);
	printf("现在此链表结构为 ：\n");
	traversal_link(list);
	return 0;
}