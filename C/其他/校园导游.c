#include<stdio.h>
#define INFINITY 3000
#define MAX_VERTEX_NUM 20
typedef int AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef struct{
	char vexs[MAX_VERTEX_NUM];    //��������
	AdjMatrix  arcs;                     //�ڽӾ���
	int vexnum,arcnum;                  // ͼ�ĵ�ǰ�������ͻ���
}MGraph;

typedef int Status;
void Floyd(MGraph G);

Status LocateVex(MGraph G,char v)
{
	int k;
	for(k=0;k<G.vexnum;k++)
	{
		if(G.vexs[k]==v)	
		{	
			return k;
			break;
		}
	}
	return -1;
}

Status CreateUDN(MGraph &G)
{
	int i,j,k,w;
	char v1,v2;
	printf("������ͼ�Ķ������ͻ�����");
	scanf("%d%d",&G.vexnum,&G.arcnum);
	getchar();
	for(i=0;i<G.vexnum;i++)
	{
		printf("�������%d�����㣺",i+1);
		scanf("%c",&G.vexs[i]);
		getchar();
	}
	for(i=0;i<G.vexnum;i++)
	{
		for(j=0;j<G.vexnum;j++)
		{
			G.arcs[i][j]=INFINITY;
		}
	}
	for(k=0;k<G.arcnum;k++)
	{
		printf("�������%d���������ӵ��������㼰Ȩֵ��",k+1);
		scanf("%c%c%d",&v1,&v2,&w);
		getchar();
		i=LocateVex(G,v1);
		j=LocateVex(G,v2);
		G.arcs[i][j]=w;
		G.arcs[j][i]=w;
	}
	return 0;
}
void PrintMatrix(MGraph G)
{
	int i,j;
	for(i=0;i<G.vexnum;i++)
	{
		for(j=0;j<G.vexnum;j++)
		{
			printf("%-5d",G.arcs[i][j]);
		}
		printf("\n");
	}
}



int main()
{
	MGraph G;
	CreateUDN(G);
	PrintMatrix(G);
	Floyd(G);
	return 0;
}


void Floyd(MGraph G)
{
	int C[20][20];
    int i,j,k;
     for(i=0;i<G.vexnum;i++)
	 {
         for(j=0;j<G.vexnum;j++)  
		 {
			 C[i][j]=G.arcs[i][j];
		}
	}
     for(i=0;i<G.vexnum;i++) 
	 {
		 C[i][i]=0;
	 }
     for(k=0;k<G.vexnum; k++)
	 {
        for(i=0;i<G.vexnum;i++)
		{
             for(j=0;j<G.vexnum;j++ ) 
			 {
				if(C[i][k]+C[k][j]<C[i][j]) 
				{
					C[i][j]=C[i][k]+C[k][j];
				}
			 }
		}
	 }

	 for(i=0;i<G.vexnum;i++)
	{
		for(j=0;j<G.vexnum;j++)
		{
			printf("%-5d",C[i][j]);
		}
		printf("\n");
	}
}
