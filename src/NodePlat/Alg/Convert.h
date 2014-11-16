#if !defined(AFX_FSYLXDLG_H__6C3382B3_0C92_4A33_BF7B_AD46FD8CD86E__INCLUDED_)
#define AFX_FSYLXDLG_H__6C3382B3_0C92_4A33_BF7B_AD46FD8CD86E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "NodeDlg.h"
class CConvert
{
  public:
	  ConvertLtoC(double lx,double ly);
	  
	  double cx;//保存转化后的X Y坐标
	  double cy;
	  int pX;//保存转化后的像素坐标
	  int pY;
	  double lx;//保存转化后的经度纬度
	  double ly;
	  CConvert(int ml,int mt,int xx,int yy);
	  virtual ~CConvert();
	  ConvertCtoL(double x,double y);
	  ConvertPtoC(int pX,int pY);//将像素点转成参考坐标系下坐标
	  ConvertCtoP(double x,double y);//将参考坐标系下的坐标转成像素点坐标
	  ConvertPtoL(int pX,int pY);//将像素点坐标转成经纬度
	  ConvertLtoP(double lx,double ly);//将经纬度转成像素点坐标
protected:
	int     mapX;//保存电子海图的大小(像素)
	int     mapY;	 
	int		mleft;//地图的左上角坐标;
	int		mtop;
	double  bl;
	double  bb;
};



#endif // !defined(AFX_CTRLGRAM_H__B869F3DF_0716_4F45_B2E7_F81AD9D0BE68__INCLUDED_)
