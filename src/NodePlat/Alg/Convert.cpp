


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


#include "stdafx.h"
#include "Convert.h"
#include "math.h"

#define LEFT_LONGIT 115.8 //左边经度
#define RIGHT_LONGIT 123.5//右边经度
#define UP_LATI 27.8   //上边纬度
#define DOWN_LATI 21.5//下边纬度



//构造函数CConvert中的参数ml,mt,xx,yy分别表示:地图的左上角x坐标,y坐标,地图的宽度,高度
CConvert::CConvert(int ml,int mt,int xx,int yy)
{
	mleft = ml;//初始化地图的左上角坐标
	mtop = mt;

	mapX = xx;//初始化电子海图的大小(像素)
	mapY = yy;
	
	cx = 0.0;
	cy = 0.0;
	
	bl = 333360.0/(double)mapX;//电子海图上x方向一个像素对应的实际距离(米)3度，333360.0m
	bb = 287800.8/(double)mapY;//电子海图上Y方向一个像素对应的实际距离(米)2.52度，287800.8m
	
}

CConvert::~CConvert()
{
	
}
CConvert::ConvertPtoC(int pX,int pY)
{
//	int    mapX;//保存电子海图的大小(像素)
//	int    mapY;
	
	
//	mapX=761;
//	mapY=643;
//	double bl;//电子海图上一个像素对应的实际距离(米)
//	bl=390.234234456345;
	//double cx,cy;//保存鼠标当前X Y坐标
	
	if(pX > (mleft + mapX/2) && pY > (mtop +mapY/2))//第四像限
	{
		cx=((double)pX-(double)(mleft + mapX/2))*bl;
		cy=((double)pY-(double)(mtop +mapY/2))*bb*(-1);
	}
	if(pX <(mleft + mapX/2) && pY < (mtop +mapY/2))//第二像限
	{
		cx=((double)pX-(double)(mleft + mapX/2))*bl;
		cy=((double)pY-(double)(mtop +mapY/2))*bb*(-1);
	}
	if(pX >= (mleft + mapX/2) && pY <= (mtop +mapY/2))//第一像限
	{
		cx=((double)pX-(double)(mleft + mapX/2))*bl;
		cy=((double)pY-(double)(mtop +mapY/2))*bb*(-1);
	}
	if(pX <=(mleft + mapX/2) && pY >= (mtop +mapY/2))//第三像限
	{
		cx=((double)pX-(double)(mleft + mapX/2))*bl;
		cy=((double)pY-(double)(mtop +mapY/2))*bb*(-1);
	}
}
CConvert::ConvertCtoP(double x,double y)
{
	//int pX;
	//int pY;

//	double bl;//电子海图上一个像素对应的实际距离(米)
	
//	mapX=761;
//	mapY=643;
//	bl=390.234234456345;
	if(x>=0 && y>=0)//第一像限
	{
		pX=(int)(mapX/2+fabs(x/bl))+mleft;
		pY=(int)(mapY/2-fabs(y/bb))+mtop;
	}
	if(x>0 && y<0)//第四像限
	{
		pX=(int)(mapX/2+fabs(x/bl))+mleft;
		pY=(int)(mapY/2+fabs(y/bb))+mtop;
	}
	if(x<=0 && y<=0)//第三像限
	{
		pX=(int)(mapX/2-fabs(x/bl))+mleft;
		pY=(int)(mapY/2+fabs(y/bb))+mtop;
	}
	if(x<0 && y>0)//第二像限
	{
		pX=(int)(mapX/2-fabs(x/bl))+mleft;
		pY=(int)(mapY/2-fabs(y/bb))+mtop;
	}

}
CConvert::ConvertPtoL(int pX,int pY)
{
	double lxmin;//电子海图的起始经度
	double lymin;//电子海图的起始纬度
	double lxmax;
	double lymax;
//	int    mapX;//保存电子海图的大小(像素)
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
	double lxmin;//电子海图的起始经度
	double lymin;//电子海图的起始纬度
	double lxmax;
	double lymax;
//	int    mapX;//保存电子海图的大小(像素)
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
	double pXtmp,pYtmp;//电子海图上一个像素对应的实际距离(米)
//	bl=390.234234456345;
	if(x>=0 && y>=0)//第一像限
	{
		pXtmp=(mapX/2+fabs(x/bl))+mleft;
		pYtmp=(mapY/2-fabs(y/bb))+mtop;
	}
	if(x>0 && y<0)//第四像限
	{
		pXtmp=(mapX/2+fabs(x/bl))+mleft;
		pYtmp=(mapY/2+fabs(y/bb))+mtop;
	}
	if(x<=0 && y<=0)//第三像限
	{
		pXtmp=(int)(mapX/2-fabs(x/bl))+mleft;
		pYtmp=(int)(mapY/2+fabs(y/bb))+mtop;
	}
	if(x<0 && y>0)//第二像限
	{
		pXtmp=(mapX/2-fabs(x/bl))+mleft;
		pYtmp=(mapY/2-fabs(y/bb))+mtop;
	}
	double lxmin;//电子海图的起始经度
	double lymin;//电子海图的起始纬度
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
	double lxmin;//电子海图的起始经度
	double lymin;//电子海图的起始纬度
	double lxmax;
	double lymax;
	double pXtmp,pYtmp;
	lxmin=LEFT_LONGIT;
	lymin=DOWN_LATI;
	lxmax=RIGHT_LONGIT;
	lymax=UP_LATI;

	pXtmp = mleft + (int)(((lx - lxmin)/(lxmax - lxmin))*mapX);
	pYtmp = mtop  + (int)(((lymax - ly)/(lxmax - lxmin))*mapY);

//	double bl;//电子海图上一个像素对应的实际距离(米)
//	bl=390.234234456345;
	
	if(pXtmp > (mleft + mapX/2) && pYtmp > (mtop +mapY/2))//第四像限
	{
		cx=((double)pXtmp-(double)(mleft + mapX/2))*bl;
		cy=((double)pYtmp-(double)(mtop +mapY/2))*bb*(-1);
	}
	if(pXtmp < (mleft + mapX/2) && pYtmp < (mtop +mapY/2))//第二像限
	{
		cx=((double)pXtmp-(double)(mleft + mapX/2))*bl;
		cy=((double)pYtmp-(double)(mtop +mapY/2))*bb*(-1);
	}
	if(pXtmp >= (mleft + mapX/2) && pYtmp <= (mtop +mapY/2))//第一像限
	{
		cx=((double)pXtmp-(double)(mleft + mapX/2))*bl;
		cy=((double)pYtmp-(double)(mtop +mapY/2))*bb*(-1);
	}
	if(pXtmp <= (mleft + mapX/2) && pYtmp >= (mtop +mapY/2))//第三像限
	{
		cx=((double)pXtmp-(double)(mleft + mapX/2))*bl;
		cy=((double)pYtmp-(double)(mtop +mapY/2))*bb*(-1);
	}
}
