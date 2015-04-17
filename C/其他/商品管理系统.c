#include<stdio.h>
#include<stdlib.h>
#define len sizeof(struct node)
int n;

struct node
{
	int number;
	char name[50];
	int remain;
	struct node *next;
};

struct node *creat(void)
{
	struct node *head=NULL;
	struct node *p1,*p2;
	int n=0;
	printf("��������Ʒ��Ϣ\n");
	p1=p2=(struct node*)malloc(len);
	scanf("%d%s",&p1->number,p1->name);
	p1->remain=0;
	while(p1->number!=0)
	{
		n++;
		if(n==1)	
			head=p1;
		else
			p2->next=p1;
		p2=p1;
	    p1=(struct node*)malloc(len);
		scanf("%d%s",&p1->number,&p1->name);
		p1->remain=0;			
	}
	p2->next=NULL;
	return head;
}

void list(struct node *head)
{
	struct node *p;
	printf("��Ʒ:\n");
	p=head;
	if(head!=NULL)
	{
		do
		{
			printf("��Ʒ�ţ�%d ��Ʒ���ƣ�%s ��Ʒ��棺%d\n",p->number,p->name,p->remain);
			p=p->next;
		}while(p!=NULL);
	}
}

struct node *remove(struct node *l)
{
	struct node *p,*q;
	p=l;
	q=l->next;
	while(q!=NULL&&q->remain!=0)
	{	
		p=q;
		q=q->next;
	}
	if(q->remain==0)
	{
		p->next=q->next;
	}
	free(q);
	return l;
}

struct node *sell(struct node *head,int number,int remain)
{
	struct node *p1;
	if(head==NULL)	
	{
		printf("\nError!\n");
		return	NULL;
	}
	for(p1=head;p1!=NULL;p1=p1->next)
	{
		if(p1->number==number)	break;
	}
	if(p1!=NULL)
	{
		if(p1->remain<remain)
		{
			printf("��Ʒ����\n");
			return head;
		}
		else
		{
			p1->remain=p1->remain-remain;
			if(p1->remain==0)	head=remove(head);
			return head;
		}
	}
	else 
	{
		printf("Error!\n");
		return head;
	}
}

struct node *insert(struct node*head,struct node *p)
{
	struct node *p1;
	p1=head;
	if(p1->next!=NULL)
	{
		do
		{
			p1=p1->next;
		}while(p1->next!=NULL);
		p->next=p1->next;
		p1->next=p;
	}
	else
	{
		p->next=p1->next;
		p1->next=p;
	}
	return head;
}

struct node *stock(struct node *head,int number,int plus)
{
	struct node *p1,*p2;
	p2=(struct node*)malloc(len);
	p2->number=number;
	p2->remain=plus;
	p2->next=NULL;
	if(head==NULL)
	{
		printf("\nError!\n");
		return NULL;
	}
    p1=head;
	while(p1!=NULL)
	{
		if(p1->number==number) 
			break;
		p1=p1->next;
	}
	if(p1!=NULL)
	{
		p1->remain+=plus;	
        return head;
	}
	else
	{
		printf("��������Ʒ����:\n");
		scanf("%s",p2->name);
		head=insert(head,p2);
		return head;
	}

}

struct node *destroy(struct node *head)
{
	char word;
	struct node *p1,*p2;
	p1=p2=head;
	getchar();
	printf("Destroy?Yes or No?");
	scanf("%c",&word);
	if(word=='y')
	{
		if(p1)
		do{
			p2=p1;
			p1=p1->next;
			free(p2);
			}while(p1);
		printf("��������ա�\n");
		return NULL;
	}
	else printf("���ʧ��!\n");
	return head;
}

int main()
{
	struct node *head;
	int a;
	int m=n=0;
	int number,remain,plus;
	do{
		printf("1. ������Ʒ��Ϣ2. ����3. ����4. �о���Ʒ��Ϣ5. ���������Ʒ6. �˳�\n");
		scanf("%d",&a);
		if(a==1)
		{
			if(m!=0)
			{
				m=0;
				head=destroy(head);
				head=creat();
				n=0;
			}
			else	head=creat();
		}
		if (a==2)
		{
			printf("��������Ʒ�ź���������:\n");
			scanf("%d %d",&number,&remain);
			head=sell(head,number,remain);
			
		}
		if(a==3)
		{
			printf("��������Ʒ�źͽ�������:\n");
			scanf("%d%d",&number,&plus);
			head=stock(head,number,plus);
		}
		if(a==4)
		{
			list(head);
		}
		if(a==5)
		{
			head=destroy(head);
		}
	}while(a!=6);
	return 0;
}