


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


#include "stdafx.h"
#include "Convert.h"
#include "math.h"

#define LEFT_LONGIT 115.8 //��߾���
#define RIGHT_LONGIT 123.5//�ұ߾���
#define UP_LATI 27.8   //�ϱ�γ��
#define DOWN_LATI 21.5//�±�γ��



//���캯��CConvert�еĲ���ml,mt,xx,yy�ֱ��ʾ:��ͼ�����Ͻ�x����,y����,��ͼ�Ŀ��,�߶�
CConvert::CConvert(int ml,int mt,int xx,int yy)
{
	mleft = ml;//��ʼ����ͼ�����Ͻ�����
	mtop = mt;

	mapX = xx;//��ʼ�����Ӻ�ͼ�Ĵ�С(����)
	mapY = yy;
	
	cx = 0.0;
	cy = 0.0;
	
	bl = 333360.0/(double)mapX;//���Ӻ�ͼ��x����һ�����ض�Ӧ��ʵ�ʾ���(��)3�ȣ�333360.0m
	bb = 287800.8/(double)mapY;//���Ӻ�ͼ��Y����һ�����ض�Ӧ��ʵ�ʾ���(��)2.52�ȣ�287800.8m
	
}

CConvert::~CConvert()
{
	
}
CConvert::ConvertPtoC(int pX,int pY)
{
//	int    mapX;//������Ӻ�ͼ�Ĵ�С(����)
//	int    mapY;
	
	
//	mapX=761;
//	mapY=643;
//	double bl;//���Ӻ�ͼ��һ�����ض�Ӧ��ʵ�ʾ���(��)
//	bl=390.234234456345;
	//double cx,cy;//������굱ǰX Y����
	
	if(pX > (mleft + mapX/2) && pY > (mtop +mapY/2))//��������
	{
		cx=((double)pX-(double)(mleft + mapX/2))*bl;
		cy=((double)pY-(double)(mtop +mapY/2))*bb*(-1);
	}
	if(pX <(mleft + mapX/2) && pY < (mtop +mapY/2))//�ڶ�����
	{
		cx=((double)pX-(double)(mleft + mapX/2))*bl;
		cy=((double)pY-(double)(mtop +mapY/2))*bb*(-1);
	}
	if(pX >= (mleft + mapX/2) && pY <= (mtop +mapY/2))//��һ����
	{
		cx=((double)pX-(double)(mleft + mapX/2))*bl;
		cy=((double)pY-(double)(mtop +mapY/2))*bb*(-1);
	}
	if(pX <=(mleft + mapX/2) && pY >= (mtop +mapY/2))//��������
	{
		cx=((double)pX-(double)(mleft + mapX/2))*bl;
		cy=((double)pY-(double)(mtop +mapY/2))*bb*(-1);
	}
}
CConvert::ConvertCtoP(double x,double y)
{
	//int pX;
	//int pY;

//	double bl;//���Ӻ�ͼ��һ�����ض�Ӧ��ʵ�ʾ���(��)
	
//	mapX=761;
//	mapY=643;
//	bl=390.234234456345;
	if(x>=0 && y>=0)//��һ����
	{
		pX=(int)(mapX/2+fabs(x/bl))+mleft;
		pY=(int)(mapY/2-fabs(y/bb))+mtop;
	}
	if(x>0 && y<0)//��������
	{
		pX=(int)(mapX/2+fabs(x/bl))+mleft;
		pY=(int)(mapY/2+fabs(y/bb))+mtop;
	}
	if(x<=0 && y<=0)//��������
	{
		pX=(int)(mapX/2-fabs(x/bl))+mleft;
		pY=(int)(mapY/2+fabs(y/bb))+mtop;
	}
	if(x<0 && y>0)//�ڶ�����
	{
		pX=(int)(mapX/2-fabs(x/bl))+mleft;
		pY=(int)(mapY/2-fabs(y/bb))+mtop;
	}

}
CConvert::ConvertPtoL(int pX,int pY)
{
	double lxmin;//���Ӻ�ͼ����ʼ����
	double lymin;//���Ӻ�ͼ����ʼγ��
	double lxmax;
	double lymax;
//	int    mapX;//������Ӻ�ͼ�Ĵ�С(����)
//	int    mapY;
//	mapX=761;
//	mapY=643;
	lxmin=LEFT_LONGIT;
	lymin=DOWN_LATI;
	lxmax=RIGHT_LONGIT;
    lymax=UP_LATI;
	lx=lxmin+(double)(pX-mleft)*(lxmax-lxmin)/(double)mapX;
	ly=lymax-(double)(pY-mtop)*(lymax-lymin)/(double)mapY;
}

CConvert::ConvertLtoP(double lx,double ly)
{
	double lxmin;//���Ӻ�ͼ����ʼ����
	double lymin;//���Ӻ�ͼ����ʼγ��
	double lxmax;
	double lymax;
//	int    mapX;//������Ӻ�ͼ�Ĵ�С(����)
//	int    mapY;
//	mapX=761;
//	mapY=643;
	lxmin=LEFT_LONGIT;
	lymin=DOWN_LATI;
	lxmax=RIGHT_LONGIT;
	lymax=UP_LATI;

	pX = mleft + (int)(((lx - lxmin)/(lxmax - lxmin))*mapX);
	pY = mtop  + (int)(((lymax - ly)/(lxmax - lxmin))*mapY);
}

CConvert::ConvertCtoL(double x,double y)
{	
	double pXtmp,pYtmp;//���Ӻ�ͼ��һ�����ض�Ӧ��ʵ�ʾ���(��)
//	bl=390.234234456345;
	if(x>=0 && y>=0)//��һ����
	{
		pXtmp=(mapX/2+fabs(x/bl))+mleft;
		pYtmp=(mapY/2-fabs(y/bb))+mtop;
	}
	if(x>0 && y<0)//��������
	{
		pXtmp=(mapX/2+fabs(x/bl))+mleft;
		pYtmp=(mapY/2+fabs(y/bb))+mtop;
	}
	if(x<=0 && y<=0)//��������
	{
		pXtmp=(int)(mapX/2-fabs(x/bl))+mleft;
		pYtmp=(int)(mapY/2+fabs(y/bb))+mtop;
	}
	if(x<0 && y>0)//�ڶ�����
	{
		pXtmp=(mapX/2-fabs(x/bl))+mleft;
		pYtmp=(mapY/2-fabs(y/bb))+mtop;
	}
	double lxmin;//���Ӻ�ͼ����ʼ����
	double lymin;//���Ӻ�ͼ����ʼγ��
	double lxmax;
	double lymax;
	lxmin=LEFT_LONGIT;
	lymin=DOWN_LATI;
	lxmax=RIGHT_LONGIT;
	lymax=UP_LATI;
	lx=lxmin+(double)(pXtmp-mleft)*(lxmax-lxmin)/(double)mapX;
	ly=lymax-(double)(pYtmp-mtop)*(lymax-lymin)/(double)mapY;

}

CConvert::ConvertLtoC(double lx, double ly)
{
	double lxmin;//���Ӻ�ͼ����ʼ����
	double lymin;//���Ӻ�ͼ����ʼγ��
	double lxmax;
	double lymax;
	double pXtmp,pYtmp;
	lxmin=LEFT_LONGIT;
	lymin=DOWN_LATI;
	lxmax=RIGHT_LONGIT;
	lymax=UP_LATI;

	pXtmp = mleft + (int)(((lx - lxmin)/(lxmax - lxmin))*mapX);
	pYtmp = mtop  + (int)(((lymax - ly)/(lxmax - lxmin))*mapY);

//	double bl;//���Ӻ�ͼ��һ�����ض�Ӧ��ʵ�ʾ���(��)
//	bl=390.234234456345;
	
	if(pXtmp > (mleft + mapX/2) && pYtmp > (mtop +mapY/2))//��������
	{
		cx=((double)pXtmp-(double)(mleft + mapX/2))*bl;
		cy=((double)pYtmp-(double)(mtop +mapY/2))*bb*(-1);
	}
	if(pXtmp < (mleft + mapX/2) && pYtmp < (mtop +mapY/2))//�ڶ�����
	{
		cx=((double)pXtmp-(double)(mleft + mapX/2))*bl;
		cy=((double)pYtmp-(double)(mtop +mapY/2))*bb*(-1);
	}
	if(pXtmp >= (mleft + mapX/2) && pYtmp <= (mtop +mapY/2))//��һ����
	{
		cx=((double)pXtmp-(double)(mleft + mapX/2))*bl;
		cy=((double)pYtmp-(double)(mtop +mapY/2))*bb*(-1);
	}
	if(pXtmp <= (mleft + mapX/2) && pYtmp >= (mtop +mapY/2))//��������
	{
		cx=((double)pXtmp-(double)(mleft + mapX/2))*bl;
		cy=((double)pYtmp-(double)(mtop +mapY/2))*bb*(-1);
	}
}
