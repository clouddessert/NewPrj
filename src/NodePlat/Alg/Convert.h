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
	  
	  double cx;//����ת�����X Y����
	  double cy;
	  int pX;//����ת�������������
	  int pY;
	  double lx;//����ת����ľ���γ��
	  double ly;
	  CConvert(int ml,int mt,int xx,int yy);
	  virtual ~CConvert();
	  ConvertCtoL(double x,double y);
	  ConvertPtoC(int pX,int pY);//�����ص�ת�ɲο�����ϵ������
	  ConvertCtoP(double x,double y);//���ο�����ϵ�µ�����ת�����ص�����
	  ConvertPtoL(int pX,int pY);//�����ص�����ת�ɾ�γ��
	  ConvertLtoP(double lx,double ly);//����γ��ת�����ص�����
protected:
	int     mapX;//������Ӻ�ͼ�Ĵ�С(����)
	int     mapY;	 
	int		mleft;//��ͼ�����Ͻ�����;
	int		mtop;
	double  bl;
	double  bb;
};



#endif // !defined(AFX_CTRLGRAM_H__B869F3DF_0716_4F45_B2E7_F81AD9D0BE68__INCLUDED_)
