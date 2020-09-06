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
	
	LINK_NODE *p_current = head;		//	��ָ��ָ��ͷ���
	int data = 0;						
	while(1)
	{
		printf("���������ݣ�����0������:\n");
		scanf("%d",&data);
		//�������0�����˳�ѭ��
		if (0 == data)
		{
			printf("���������\n");
			break;
		}
		
		LINK_NODE *new_node = NULL;
		if(NULL == (new_node = (LINK_NODE *)malloc(sizeof(LINK_NODE))))
		{
			printf("�޷��������ռ�\n");
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
		printf("������û�д洢����\n");
		return;
	}
	
	LINK_NODE *p_current = head->next;
	while(NULL != p_current)
	{
		printf("(���ڵ��ַ %p ",p_current);
		printf("���� %d\t",p_current->data);
		printf("��һ������ַ %p )\n",p_current->next);
		p_current = p_current->next;
	}
	//printf("\n����������\n");
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
	
	//���p_currentΪNULL��˵��������ֵΪval�Ľڵ�
	if (NULL == p_current )
	{
		printf("������ֵΪ%d�Ľڵ�!\n",val);
		return;
	}
	
	LINK_NODE *new_node = NULL;
	new_node = (LINK_NODE *)malloc(sizeof(LINK_NODE));
	if(NULL == new_node)
	{
		printf("�޷��������ռ�!\n");
		return;
	}	
	memset(new_node,0,sizeof(LINK_NODE));
	//�½ڵ��nextָ��p_current����һ�����
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
	
	//���p_currentΪNULL��˵��������ֵΪval�Ľڵ�
	if (NULL == p_current )
	{
		printf("������ֵΪ%d�Ľڵ�!\n",val);
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
	printf("�����������\n");
}



int main()
{
	LINK_NODE *list = NULL;
	list = init_link_list();	//	����ĳ�ʼ��
	if(NULL == list)
	{
		printf("������ʧ��\n");
	}
	printf("������ṹΪ ��\n");
	traversal_link(list);
	
	int val = 0;
	int data = 0;
	printf("��ָ��ֵ�����������\n");
	printf("������ֵ:\n");
	scanf("%d",&val);
	printf("����������:\n");
	scanf("%d",&data);
	insert_node(list,val,data);
	printf("���ڴ�����ṹΪ ��\n");
	traversal_link(list);
	
	printf("ɾ��ָ��ֵ\n");
	printf("������ֵ:\n");
	scanf("%d",&val);
	delete_node(list,val);
	
	printf("���ڴ�����ṹΪ ��\n");
	traversal_link(list);
	
	printf("ɾ������\n");
	destroy_link(list);
	printf("���ڴ�����ṹΪ ��\n");
	traversal_link(list);
	return 0;
}