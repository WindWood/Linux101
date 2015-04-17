#include <stdio.h>
#include<stdlib.h>
#include<malloc.h>


#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define STACK_INIT_SIZE 100 //�洢�ռ��ʼ������
#define STACKINCREMEMNT 10 //�洢�ռ��������



typedef struct{
	int x;
	int y;
}Point;
typedef Point SElemType;
typedef int Status;


typedef struct{
	SElemType *base;
	SElemType *top;
	int stacksize;
}SqStack;

void Exit(Point p);
bool Legal(Point p);
int Number(Point p);

Status InitStack(SqStack &s)
{
//����һ����ջ S
	s.base=(SElemType*)malloc(STACK_INIT_SIZE*sizeof(SElemType));
//�洢����ʧ��
	if (!s.base)
		return OVERFLOW;
	s.top=s.base;
	s.stacksize=STACK_INIT_SIZE;
	return OK;
}

Status Push(SqStack &s, SElemType e)
{
//����Ԫ��eΪ�µ�ջ��Ԫ��
	if (s.top-s.base>=s.stacksize)
	{
//ջ����׷�ӿռ�
		s.base=(SElemType*) realloc(s.base, (s.stacksize + STACK_INIT_SIZE) * sizeof(SElemType));
		if (!s.base)
			return OVERFLOW;
		s.top=s.base+s.stacksize;
		s.stacksize+=STACKINCREMEMNT;
	}
	*s.top++=e;
	return OK;
}

Status Pop(SqStack &s, SElemType &e)
{
	if (s.top==s.base)
		return ERROR;
	e=*--s.top;
	return OK;
}



#define N 8
//�����λ
int HTry1[]={-2,-1,1,2,2,1,-1,-2}; //x������λ
int HTry2[]={1,2,2,1,-1,-2,-2,-1}; //y������λ
//��ʶ
int board[N][N]={0}; //N * N ������
int step=1; //�Ѿ��ߵĲ���
SqStack s[65]; //��step������һ�������п���λ��
SqStack s1; //��ʱջ


int Number(Point p) //�ҳ���ǰλ����һ���ĸ��ֿ���λ�ã��������֮��
{
	Point p1;
	int j=0;
	for (int i=0;i<8;i++)
	{
		p1.x=p.x+HTry1[i];
		p1.y=p.y+HTry2[i];
		if (Legal(p1))
		{
			j++;
		}
	}
	return j;
}

void Next(Point p) //�ҳ�����λ�ò����䲽����¼
{
	Point p1,p2; //p2�洢��һ��Ҫ�ߵ�λ�� p1�洢��ǰλ��
	InitStack(s[step]);
	board[p.x][p.y]=step;
	Push(s1,p); //����ǰ����λ��ѹ����ʱջs1
	if (step<N*N)
	{
		Exit(p);
		Pop(s[step],p2); //p2�Ǵ�s[step]��pop������
		if ((s[step].base==s[step].top&&Number(p2)==0)&&step!=N*N-1) //s[step]Ϊ��ջ ��һ���������� ����û�е�64
		{ //���ʱ��������Ҫ���ݲ���
			Pop(s1,p1); //�ѵ�ǰλ�ô���ʱջs1��pop����
			board[p1.x][p1.y]=0; //�������
			--step; //������1
			while (s[step].base==s[step].top) //���s[step]ջΪ��ջ
			{
				Pop(s1,p1); //��s1�е�ջ�ŵ�p1��
				board[p1.x][p1.y]=0;
				step--; //һֱ���ݵ�����Ϊֹ
			}
			Pop(s[step], p2); //��һ����һ�����߷�
			step++;
			Next(p2);
		}
		else if (Number(p2)==0&&s[step].base!=s[step].top)//��һ��û���ߵ�λ�� ջ��Ϊ��
		{
			Pop(s[step],p2); //��һ����һ�����߷�
			step++;
			Next(p2);
		}
		else if (Number(p2)!=0&&s[step].base==s[step].top)//��һ�����ߵ�λ�� ����ջs[step]Ϊ��
		{ //ֱ������һ��
			step++;
			Next(p2);
		}
		else
		{
			step++;
			Next(p2);
		}
	}
}
void Exit(Point p)//������һ��
{
	Point temp;
	Point p1;
	int j=0;
	Point ap[8]={0};
	for (int i=0;i<8;i++)
	{
		p1.x=p.x+HTry1[i];
		p1.y=p.y+HTry2[i];
		if (Legal(p1))
		{
			ap[j]=p1;
			j++;
		}
	}//����һ���Ŀ���λ�ô洢��ap[]��
	for (int count=0; count<Number(p)-1;count++)
	{
		for (int k=0;k<Number(p)-1;k++)
		{
			if (Number(ap[k])<Number(ap[k+1])) //�Ӵ�С����
			{
				temp=ap[k+1];
				ap[k+1]=ap[k];
				ap[k]=temp;
			}
		}
	}
	for (int t=0; t<Number(p);t++)
	{ 
		Push(s[step],ap[t]); //�Ӵ�Сѹ��s[step]ջ�У�pop��ʱ����Ǵ�С����
	}
} 

bool Legal(Point p)//�ж��Ƿ����
{ 
	if ((p.x>=0)&&(p.x<N)&&(p.y>=0)&&(p.y<N)&&(board[p.x][p.y]==0))
		return true;
	else
		return false;
}



int main()
{
	Point p;
	int i,j;
	printf("����x(0-%d),y(0-%d)\n",N-1,N-1);
	scanf("%d%d", &p.x, &p.y);
	while (! ((p.x>=0)&&(p.x<N-1)&&(p.y>=0)&&(p.y<N-1)))
	{
		printf("���벻�Ϸ�������������\n");
		printf("����x(0-%d),y(0-%d)\n",N-1,N-1);
		scanf("%d%d", &p.x, &p.y);
	}
	InitStack(s1);
	Next(p);
	for (i=0;i<N;i++)
	{
		for (j=0;j<N;j++)
		{
			printf("%5d", board[i][j]);
		}
		printf("\n");
	}
	return 0;
}


