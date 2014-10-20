//******************************************************************************************//
//        �རЭͬ������Ϣ��������Ϣ�ϲ����� 0831 wanghaiying                       //

//********  ���룺����������Ϣ ,�յ����ڽ�����Ϣ                          ****************//
//********        ��������ĵ���λ����Ϣ                                          **********//
//********  �����������Ϣ�ͷ�����Ϣ�ĺϲ������Ϣ                     **********// 
//******************************************************************************************//
#include "CooperativeMsg.h"
#include "StdAfx.h"
#include <iostream>
#include <math.h>
#include <vector>
#include <string>
using namespace std;

//#define PI 3.1415926535898

//�����ڽ�������������Ϣʱ���������ھ��뷽λ������ʱ���������ڽ���γ�߶���֪������ڽ��۲⵽��Ŀ���ڱ����ϵ����꼰����ڱ����ľ�γ�ߡ�
void Get_Coordinate_Conversion_Module(double Rd1,double Az1,double Ez1,double Rd2,double Az2,double Ez2,double La1,double Ba1,double Ha1,
									  double La2,double Ba2,double Ha2,/*double *x1,double *y1,double *z1,*/double& Xt,double& Yt,double& Zt,double& Rdt,double& Azt,double& Ezt,double& SumCorr);
void Mf_SPA(double s, double t,double& corr); //s,tΪ��ͬ���͵���Ϣ�����м��Է����������ص����ϵ����������VctCorr��
//void Get_NO_SelfTrack_Coordinate_Conversion_Module(double Rd2,double Az2,double Ez2,double La1,double Ba1,double Ha1,
//												   double La2,double Ba2,double Ha2,double& Xt,double& Yt,double& Zt);
void Object_Radar_Transform(double Lt,double Bt,double Ht,double L0,double B0,double H0,double& rd,double& az,double& ez);


void GET_CooperateMsg_Modul(/*SHIP_POSITION& stSelfPosi,*/VCT_Request_Cooperative_Msg& vctRequestCooperative, VCT_BACK_Cooperative_Msg& vctBackCooperative, VCT_COOPER_MSG& vctCooperMsg)
{
	double Xt = 0.0;        
	double Yt = 0.0;
	double Zt = 0.0;
	double Rdt = 0.0;
	double Azt = 0.0;
	double Ezt = 0.0;
	double dSumCorr_xyz = 0.0;
	SHIP_POSITION stSelfPosi;  //��Ҫ��ȡ�����ľ�γ�� 
// 	//���辭γ��:
// 	stSelfPosi.dHeight = 0.0;
// 	stSelfPosi.dLonti = 119.1;
// 	stSelfPosi.dLati = 22.5;	
	Cooperative_Msg stCooperMsg;   //��������Ϣ���ۺ����Ž��кϲ�
	//	VCT_COOPER_MSG vctCooperMsg;   //�������ͷ��صĺϲ���Ϣ
	VCT_COOPER_MSG::iterator iteCooperMsg; 
	
	// ͳ����������Ҫʶ��ĸ�����Ϣ���Լ��ڽ����͹����ĸ�����Ϣ��ESM��COM, ������Ϣ����
	VCT_BACK_Cooperative_Msg::iterator iteBackMsg;
	BACK_Cooperative_Msg stBackMsg;
	VCT_Request_Cooperative_Msg::iterator iteRequestMsg;
	VCT_TRACE_MSG::iterator iteTrack;
	VCT_ESM_MSG::iterator iteEsm;                
	VCT_COMM_MSG::iterator iteComm;
	
	//��պϲ���Ϣ����
	for (iteCooperMsg = vctCooperMsg.begin(); iteCooperMsg != vctCooperMsg.end(); iteCooperMsg++)
	{ 
		iteCooperMsg->lAutonum = NULL;
		iteCooperMsg->nComN = NULL;
		iteCooperMsg->nEsmN = NULL;
		iteCooperMsg->nComN = NULL;
		for (iteTrack = iteCooperMsg->vctTrace.begin(); iteTrack != iteCooperMsg->vctTrace.end(); iteTrack++)
		{
			memset(&(*iteTrack), 0, sizeof(TRACKSTATUS_MARK));
		}
		for (iteEsm = iteCooperMsg->vctEsm.begin(); iteEsm != iteCooperMsg->vctEsm.end();iteEsm++)
		{
			memset(&(*iteEsm), 0, sizeof(ESMSTATUS_MARK));
		}
		for(iteComm = iteCooperMsg->vctComm.begin(); iteComm != iteCooperMsg->vctComm.end();iteComm++)
		{
			memset(&(*iteComm), 0, sizeof(COMSTATUS_MARK));
		}
		iteCooperMsg->vctTrace.clear();
		iteCooperMsg->vctComm.clear();
		iteCooperMsg->vctEsm.clear();
	}
	vctCooperMsg.clear();
	
	//��������
	//    for (iteBackMsg = vctBackCooperative.begin(); iteBackMsg != vctBackCooperative.end(); iteBackMsg++)
	//    {
	// 	     cout << "������Ϣ��COMM������"<< iteBackMsg->vctComm.size() <<endl;
	// 		 cout << "������Ϣ��ESM������"<< iteBackMsg->vctEsm.size() <<endl;
	//    } 90
	
	//��������Ϣ,������Ϣ����ϲ������У� 
	for ( iteRequestMsg = vctRequestCooperative.begin(); iteRequestMsg != vctRequestCooperative.end(); iteRequestMsg++ )
	{   
        stSelfPosi = iteRequestMsg->stReqShipPosi;  // ���󽢼�Ϊ����
		if ( iteRequestMsg->lAutonum > 7999) //������Ϣ���У��ۺ����Ŵ��ڵ���8000����Ϊ�о�����ĺ�����Ϣ
		{
			stCooperMsg.lAutonum = iteRequestMsg->lAutonum;
			stCooperMsg.vctTrace.push_back(iteRequestMsg->stTrace);
			if (iteRequestMsg->vctEsm.size() != 0)
			{
				for(iteEsm = iteRequestMsg->vctEsm.begin(); iteEsm != iteRequestMsg->vctEsm.end(); iteEsm++)
				{
					stCooperMsg.vctEsm.push_back(*iteEsm);
				}
			}
			if (iteRequestMsg->vctComm.size() != 0)
			{
				for (iteComm = iteRequestMsg->vctComm.begin();iteComm != iteRequestMsg->vctComm.end();iteComm++)
				{
					stCooperMsg.vctComm.push_back(*iteComm);
				}
			}
		}
		if ( iteRequestMsg->lAutonum < 8000 && iteRequestMsg->lAutonum > 6999 )
		{
			stCooperMsg.lAutonum = iteRequestMsg->lAutonum;
			for(iteEsm = iteRequestMsg->vctEsm.begin(); iteEsm != iteRequestMsg->vctEsm.end(); iteEsm++)
			{
				stCooperMsg.vctEsm.push_back(*iteEsm);
			}
			
			for (iteComm = iteRequestMsg->vctComm.begin();iteComm != iteRequestMsg->vctComm.end();iteComm++)
			{
				stCooperMsg.vctComm.push_back(*iteComm);
			}
		}
		
		if (iteRequestMsg->lAutonum < 6000)
		{
			stCooperMsg.lAutonum =  iteRequestMsg->lAutonum;
			stCooperMsg.vctTrace.push_back(iteRequestMsg->stTrace);
		}
		//		vctCooperMsg.push_back(stCooperMsg);
		//��������Ϣ����ϲ���Ϣ��
		for ( iteBackMsg = vctBackCooperative.begin(); iteBackMsg != vctBackCooperative.end(); iteBackMsg++)
		{
			int Csizea = iteBackMsg->vctComm.size();
			if (iteBackMsg->lAutonum == iteRequestMsg->lAutonum)  //�ۺ�������ͬ
			{
				//��������Ϣ��ÿ����Ϣ����ϲ���Ϣ������
				if ( iteBackMsg->lAutonum >7999 ) //������Ϣ
					//  if ( iteBackMsg->BackTrackN !=0  ) //������Ϣ
				{	
					//ת��������Ϣ�������꣬��γ���滻
					Get_Coordinate_Conversion_Module(iteRequestMsg->stTrace.dRange,iteRequestMsg->stTrace.dAzimuth,iteRequestMsg->stTrace.dElevationAngle,
						iteBackMsg->stTrace.dRange,iteBackMsg->stTrace.dAzimuth,iteBackMsg->stTrace.dElevationAngle,  
						stSelfPosi.dLati,stSelfPosi.dLonti,stSelfPosi.dHeight,
						iteBackMsg->stBackShipPosi.dLati,iteBackMsg->stBackShipPosi.dLonti,iteBackMsg->stBackShipPosi.dHeight,
						Xt, Yt, Zt, Rdt, Azt, Ezt, dSumCorr_xyz);
					iteBackMsg->stTrace.dTX = Xt;
					iteBackMsg->stTrace.dTY = Yt;
					iteBackMsg->stTrace.dTZ = Zt;
					iteBackMsg->stTrace.dRange = Rdt;
					iteBackMsg->stTrace.dAzimuth = Azt;
					iteBackMsg->stTrace.dElevationAngle = Ezt;
					stCooperMsg.vctTrace.push_back(iteBackMsg->stTrace);
					//���� ������Ϣ������
					int Tsize = stCooperMsg.vctTrace.size();
					//�ǲ���
					stCooperMsg.nTraceN = stCooperMsg.vctTrace.size();
				}
				//���� ������Ϣ������
				int Esize = stCooperMsg.vctEsm.size();
				int Csize = stCooperMsg.vctComm.size();
				//�ǲ���
				stCooperMsg.nEsmN = stCooperMsg.vctEsm.size();
				stCooperMsg.nComN = stCooperMsg.vctComm.size();
				
				if ( iteBackMsg->vctEsm.size() != 0)
				{
					for (iteEsm = iteBackMsg->vctEsm.begin(); iteEsm != iteBackMsg->vctEsm.end(); iteEsm++)
					{
						stCooperMsg.vctEsm.push_back(*iteEsm);
					}
				}
				//���� ���ص�Comm����Ϣ����
				Csizea = iteBackMsg->vctComm.size();
				if ( iteBackMsg->vctComm.size() != 0)
				{
					for (iteComm = iteBackMsg->vctComm.begin(); iteComm != iteBackMsg->vctComm.end(); iteComm++)
					{
						stCooperMsg.vctComm.push_back(*iteComm);
					}
					
				}
				
			}//if �ۺ�������ͬ ����
		}// for iteBackMsg
		vctCooperMsg.push_back(stCooperMsg);
		
		
	} //for iteRequestMsg
	//��������  �ϲ���Ϣ����
	// for (iteCooperMsg = vctCooperMsg.begin(); iteCooperMsg != vctCooperMsg.end(); iteCooperMsg++)
	// {
	// 	cout<<"Track: "<< iteCooperMsg->vctTrace.size() << endl;
	// 	cout<<"ESM: "<< iteCooperMsg->vctEsm.size() << endl;
	// 	cout<<"COM: "<< iteCooperMsg->vctComm.size() <<endl;
	// }
	//��շ�������
// 	for ( iteBackMsg = vctBackCooperative.begin(); iteBackMsg != vctBackCooperative.end(); iteBackMsg++ )
// 	{
// 		iteBackMsg->BackCOMN = NULL;
// 		iteBackMsg->BackESMN= NULL;
// 		iteBackMsg->BackTrackN = NULL;
// 		// 		 iteBackMsg->dAzimuth = NULL;
// 		// 		 iteBackMsg->dElevationAngle = NULL;
// 		// 		 iteBackMsg->dRange = NULL;
// 		iteBackMsg->lAutonum = NULL;
// 		iteBackMsg->nStampTime =NULL;
// 		memset(&iteBackMsg->stBackShipPosi, 0, sizeof(SHIP_POSITION));
// 		memset(&iteBackMsg->stTrace, 0, sizeof( TRACKSTATUS_MARK));
// 		for (iteEsm = iteBackMsg->vctEsm.begin(); iteEsm != iteBackMsg->vctEsm.end(); iteEsm++)
// 		{
// 			memset(&(*iteEsm), 0, sizeof(ESMSTATUS_MARK));
// 		}
// 		for (iteComm = iteBackMsg->vctComm.begin(); iteComm != iteBackMsg->vctComm.end(); iteComm++)
// 		{
// 			memset(&(*iteComm), 0, sizeof(COMSTATUS_MARK));
// 		}
// 		iteBackMsg->vctComm.clear();
// 		iteBackMsg->vctEsm.clear();	 
// 	}
// 	vctBackCooperative.clear();
}





/*
// / ******************************************************************* /
// / ***            Ŀ�����״�����ϵ��λ�ü���ģ��                   *** /
// / **                     ���԰�  2011-2-10                        *** /
// / ********      ���룺Ŀ��ƽ̨λ�ã�Lt,Bt,Ht��                ******* /
// / ********            �״�ƽ̨λ�ã�L0,B0,H0��                ******* /
// / ********      �����Ŀ�����״��ز�������ϵ�еľ��ࡢ��λ������ ** /
// / ******************************************************************* /
// void Object_Radar_Transform(double Lt,double Bt,double Ht,double L0,double B0,double H0,double& rd,double& az,double& ez)
// {
// 	double a,e2;
// 	double Nt,Nr;
// 	double xt,yt,zt,x0,y0,z0;
// 	double Rd,Az,Ez;
// 	double x,y,z;
// 	
// 	a=6378137;
// 	e2=0.0066943799014;
// 	
// 	Nt=a/sqrt(1-e2*sin(Bt)*sin(Bt));
// 	Nr=a/sqrt(1-e2*sin(B0)*sin(B0));
// 	
// 	xt=(Nt+Ht)*cos(Bt)*cos(Lt);
// 	yt=(Nt+Ht)*cos(Bt)*sin(Lt);
// 	zt=(Nt*(1-e2)+Ht)*sin(Bt);
// 	
// 	x0=(Nr+H0)*cos(B0)*cos(L0);
// 	y0=(Nr+H0)*cos(B0)*sin(L0);
// 	z0=(Nr*(1-e2)+H0)*sin(B0);
// 	
// 	x=-(xt-x0)*sin(L0)+(yt-y0)*cos(L0);
// 	y=-(xt-x0)*sin(B0)*cos(L0)-(yt-y0)*sin(B0)*sin(L0)+(zt-z0)*cos(B0);
// 	z=(xt-x0)*cos(B0)*cos(L0)+(yt-y0)*cos(B0)*sin(L0)+(zt-z0)*sin(B0);
// 	
// 	Rd=sqrt(x*x+y*y+z*z);  //��֪����XYZ�����������ϵ�µľ��룬��λ������
// 	if(x>=0&&y>0)
// 	{
// 		Az=atan(x/y);
// 	}
// 	else if(x>0&&fabs(y)<1.0e-3)
// 	{
// 		Az=0.5*PI;
// 	}
// 	else if(y<0)
// 	{
// 		Az=PI+atan(x/y);
// 	}
// 	else if(x<0&&fabs(y)<1.0e-3)
// 	{
// 		Az=1.5*PI;
// 	}
// 	else if(x<0&&y>0)
// 	{
// 		
// 		Az=2*PI+atan(x/y);
// 	}
// 	
// 	Ez=atan(z/sqrt(x*x+y*y)); 
// 	
// 	rd=Rd;
// 	az=Az;
// 	ez=Ez;       
// }
// / ******************************************************************************* /
// / *******      Ŀ���ڽ��۲�ľ��ࡢ��λ������ת������ͬһ����ϵ��ģ��     ******* /
// // *******     ���룺Ŀ����Ա���1�ľ��ࡢ��λ������(Rd1,Az1,Ez1)         ******* /
// // *******           Ŀ������ڽ�2�ľ��ࡢ��λ������(Rd2,Az2,Ez2)         ******* /
// / *******            �����������꣨La1,Ba1,Ha1��                         ******** /
// / *******            �ڽ��������꣨La2,Ba2,Ha2��                         ******** /
// // *******     �����//Ŀ���ڱ����Ĵ���״����ϵ�е�����x1,y1,z1           ******* /
// / ********           Ŀ����ڽ�ת�������Ĵ���״����ϵ�е�����Xt,Yt,Zt   ******* /
// / ********           Ŀ����ڽ�ת�������Ĵ���״����ϵ�еľ��ࡢ��λ������(Rdt,Azt,Ezt) ** /
// / ********           Ŀ����������۲�ļ����ۺ����ϵ��SumCorr           ******** /
// / ******************************************************************************* /
// void Get_Coordinate_Conversion_Module(double Rd1,double Az1,double Ez1,double Rd2,double Az2,double Ez2,double La1,double Ba1,double Ha1,
// 									  double La2,double Ba2,double Ha2,/ *double *x1,double *y1,double *z1,* /
// 									  double& Xt,double& Yt,double& Zt,double& Rdt,double& Azt,double& Ezt,double& SumCorr_xyz)
// {
// 	double xa,ya,za;
// 	double x2,y2,z2;
// 	double xg,yg,zg;      //�ڽ��ڱ����е�����
// 	double Rd,Az,Ez;
// 	double xt,yt,zt;
// 	
// 	double corr1,corr2,corr3/ *,corr4,corr5,corr6* /;   //�ż���ϵ��
//     double dertH;               //�Ÿ߶Ȳ���
// 	double G1;                  //�ڽ��뱾��֮��ĵ������
// 	double ae;
// 	
// 	//Ŀ���ڱ����Ĵ���״�����ϵ�е�ֱ������
// 	xa=Rd1*cos(Ez1)*sin(Az1);
// 	ya=Rd1*cos(Ez1)*cos(Az1);
// 	za=Rd1*sin(Ez1);
// 	
// // 	*x1=xa;    //����Ŀ���ڱ����е�����
// // 	*y1=ya;
// // 	*z1=za;
// 	
// 	//Ŀ�����ڽ��Ĵ���״�����ϵ�е�ֱ������
// 	x2=Rd2*cos(Ez2)*sin(Az2);
// 	y2=Rd2*cos(Ez2)*cos(Az2);
// 	z2=Rd2*sin(Ez2);
// 	
// 	//Ŀ������ڱ����ľ��ࡢ��λ�͸���
// 	Object_Radar_Transform(La2,Ba2,Ha2,La1,Ba1,Ha1,Rd,Az,Ez); //�ڽ�λ�ÿ�ֱ�Ӵ�ս���ã���Эͬ����ʱ�ڽ����ĸ���
// 	
// 	ae=4*6378130.0/3;                //�����Ч�뾶(m),��Ϊ����뾶������֮��
// 	G1=2*ae*asin(0.5*Rd/ae);
//     
// 	dertH=0.43*G1*G1/ae;           //�߶Ȳ���(����ڱ���)
// 	
// 	//�ڽ�λ���ڱ����е�����
// 	xg=Rd*cos(Ez)*sin(Az);
// 	yg=Rd*cos(Ez)*cos(Az);
// 	zg=Rd*sin(Ez)+dertH;              //�߶Ȳ���(����ڱ���)
// 	
// 	//����ϵƽ�ƣ�������Ϊ�����ꡢ�ڽ���Ϊ������
// 	//Ŀ���ڱ����е�����Ϊ��
// 	xt=x2+xg;
// 	yt=y2+yg;
// 	zt=z2+zg; 
// 	
// 	Xt=xt;       //����Ŀ���ڱ��ڽ���ת������������
// 	Yt=yt;
// 	Zt=zt;
// 	
// 	//�����Է���ģ��
// 	Mf_SPA(xa,xt,corr1);
// 	Mf_SPA(ya,yt,corr2);
// 	Mf_SPA(za,zt,corr3);
// 	
// 	SumCorr_xyz=0.5*corr1+0.3*corr2+0.2*corr3;		
// 
// 	//����ת��������꣬��Ŀ�����ڽ��еľ��෽λ����ת����Ŀ���ڱ����еľ��෽λ����
// 	Rdt=sqrt(xt*xt+yt*yt+zt*zt);  //��֪����XYZ�����������ϵ�µľ��룬��λ������
// 	if(xt>=0&&yt>0)
// 	{
// 		Azt=atan(xt/yt);
// 	}
// 	else if(xt>0&&fabs(yt)<1.0e-3)
// 	{
// 		Azt=0.5*PI;
// 	}
// 	else if(yt<0)
// 	{
// 		Azt=PI+atan(xt/yt);
// 	}
// 	else if(xt<0&&fabs(yt)<1.0e-3)
// 	{
// 		Azt=1.5*PI;
// 	}
// 	else if(xt<0&&yt>0)
// 	{
// 		
// 		Azt=2*PI+atan(xt/yt);
// 	}
// 	
// 	Ezt=atan(zt/sqrt(xt*xt+yt*yt)); 
// 
// // 	//�����Է���ģ��
// // 	Mf_SPA(Rd1,Rdt,&corr4);
// // 	Mf_SPA(Az1,Azt,&corr5);
// // 	Mf_SPA(Ez1,Ezt,&corr6);
// // 
// // 	
// // 	*AverCorr=SumCorr_xyz/4+corr4/4+corr5/4+corr6/4;	 //����ϵ�� �д��޸ģ��涨��׼��ʲô????��
// 		
// }
// / ************************************************************************ /
// / *                             ���Է�������                             * /
// / ************************************************************************ /
// void Mf_SPA(double s, double t,double& corr)
// {
// 	double spa;
// 	double tmp;
// 	
// 	double a,b,c;
// 	
// 	if(s>t)
// 	{
// 		tmp =s;
// 		s=t;
// 		t=tmp;
// 	}
// 	
// 	a=s/t;
// 	b=s/t/(t*t-1);
// 	c=(t*t-s*t-1)/(t*t-1);
// 	
// 	spa=a+fabs(b)-fabs(c);
// 	
// 	corr=spa;                 //�����������ϵ��
// }
*/









//////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///ԭ��   ���󣬵����������⣬�����ڱ仯�����ɶԵ���������д����   ���������޸İ棩////////////////////
/*	string s1("F111");
string sPt("F111");
//ͳ��(ͬһ�ۺ�������)������Ϣ��ƽ̨����
for (iteCooperMsg = vctCooperMsg.begin(); iteCooperMsg != vctCooperMsg.end(); iteCooperMsg++)
{    
if ( iteCooperMsg->vctTrace.size() != 0 )
{
for ( iteTrack = iteCooperMsg->vctTrace.begin(); iteTrack != iteCooperMsg->vctTrace.end(); iteTrack++)
{
if ( vctPlatType.size() == 0)
{
sPt.assign(iteTrack->sPlatType);
vctPlatType.push_back(sPt);

  } // if��������ƽ̨����
  else
  {
  for (itePlatType = vctPlatType.begin(); itePlatType != vctPlatType.end(); itePlatType++)
  {
  sPt.assign(iteTrack->sPlatType);
  s1.assign(*itePlatType);
  
	if ( sPt.compare(s1) != 0) //strcmp (*itePlatType, iteTrack->sPlatType) //   strcmp()�������ַ������д�Сд���еıȽ�
	//  strcmpi() �������ַ������д�Сд�����еıȽ�
	{
	vctPlatType.push_back(sPt);
	//	vctPlatType.push_back(iteTrack->sPlatType);
	}
	cout << "����"<< vctPlatType.size()<<endl;
	
	  }// for  itePlatType = vctPlatType.begin()
	  } //else ������ƽ̨����				
	  } // for iteTrack = iteCooperMsg->vctTrace.begin()
	  }// if iteCooperMsg->vctTrace.size() != 0
	  
		if ( iteCooperMsg->vctComm.size() !=0 )
		{
		for ( iteComm = iteCooperMsg->vctComm.begin(); iteComm != iteCooperMsg->vctComm.end(); iteComm++)
		{
		if ( vctPlatType.size() ==0 )
		{
		sPt.assign(iteComm->sPlatType);
		vctPlatType.push_back(sPt);
		//					vctPlatType.push_back(iteComm->sPlatType);
		}
		else
		{
		for (itePlatType = vctPlatType.begin(); itePlatType != vctPlatType.end(); itePlatType++)
		{
		s1.assign(*itePlatType);
		sPt.assign(iteComm->sPlatType);
		if ( sPt.compare(s1)!= 0)//strcmp(*itePlatType,iteComm->sPlatType)
		{
		vctPlatType.push_back(sPt);
		//							vctPlatType.push_back(iteComm->sPlatType);
		}
		
		  }
		  }
		  }
		  }
		  
			if (iteCooperMsg->vctEsm.size() !=0 )
			{
			for (iteEsm = iteCooperMsg->vctEsm.begin(); iteEsm != iteCooperMsg->vctEsm.end();iteEsm++)
			{
			if ( vctPlatType.size() == 0)
			{
			//	string sPt(iteEsm->sPlatType,4);
			sPt.assign(iteEsm->sPlatType);
			vctPlatType.push_back(sPt);
			
			  //					vctPlatType.push_back(iteEsm->sPlatType);
			  }
			  else
			  {
			  for (itePlatType = vctPlatType.begin(); itePlatType != vctPlatType.end(); itePlatType++)
			  {
			  s1.assign(*itePlatType);
			  sPt.assign(iteEsm->sPlatType);
			  if (sPt.compare(s1)!= 0) //strcmp(*itePlatType,iteEsm->sPlatType)
			  {
			  vctPlatType.push_back(sPt);
			  //							vctPlatType.push_back(iteEsm->sPlatType);
			  }
			  
				}
				}
				}
				
				  }
*/

/*
/////////////////////////////////////////////////////////////////////////////////////////////////////
////// �޸İ�    0831 ����ӱ ////////////////////////////////////////////////////////////////////////////////////////////
//���ϲ����������Ϣ��ƽ̨���Ͷ��ŵ�ͬһ����1��
//��������1������������a,b ������a��������ƽ̨������������b�����Ƚ�ƽ̨�����е�����a��ǰֵ��֮ǰֵ�Ƿ�����ͬ��
//����ͬ�ķ���ƽ̨����2�У�
//ƽ̨����2��������ƽ̨������

  //���ϲ�������ƽ̨���ͷŵ�����vctCooperPlatType
  
	for (iteCooperMsg = vctCooperMsg.begin(); iteCooperMsg != vctCooperMsg.end(); iteCooperMsg++)
	{   
	vctCooperPlatType.clear();
	vctPlatType.clear();
	int tpflag = 0;
	if ( iteCooperMsg->vctTrace.size() != 0 )
	{
				for ( iteTrack = iteCooperMsg->vctTrace.begin(); iteTrack != iteCooperMsg->vctTrace.end(); iteTrack++)
				{
				vctCooperPlatType.push_back(iteTrack->sPlatType);
				} 
				} 	
				if ( iteCooperMsg->vctComm.size() !=0 )
				{
				for ( iteComm = iteCooperMsg->vctComm.begin(); iteComm != iteCooperMsg->vctComm.end(); iteComm++)
				{
				vctCooperPlatType.push_back(iteComm->sPlatType);
				}
				}
				if (iteCooperMsg->vctEsm.size() !=0 )
				{
				for (iteEsm = iteCooperMsg->vctEsm.begin(); iteEsm != iteCooperMsg->vctEsm.end();iteEsm++)
				{
				vctCooperPlatType.push_back(iteEsm->sPlatType);			
				}		
				}
				for ( iteCPType1 = vctCooperPlatType.begin(); iteCPType1 != vctCooperPlatType.end(); iteCPType1++)
				{
				for( iteCPType2 = vctCooperPlatType.begin(); iteCPType2 != iteCPType1; iteCPType2++)
				{
				//�жϺϲ�������ǰһ���ͺ�һ����ƽ̨�����Ƿ���ͬ������ͬ������ѭ����ѭ��������������ͬ�����ƽ̨������
				if (strcmp(*iteCPType1, *iteCPType2) == 0)
				{   tpflag = 1; //��־�ҵ�����ͬ��
				break;
				}
				}
				//����ѭ��δ�ҵ���ͬ��
				if (tpflag == 0)
				{
				vctPlatType.push_back(*iteCPType1);
				}
				else
				{
				tpflag = 0;
				}
				}
				
				  //��ʱ����ͳ�ƺ�ͬһ�ۺ������µ�Ŀ��������
				  int OBjTypeNum; //Ŀ��������
				  OBjTypeNum = vctPlatType.size();//ΪĿ��������
				  
					//����ƽ̨����ƽ̨����
					cout <<"�ϲ�����Ϣƽ̨�������� "<<OBjTypeNum << endl;
					for (itePlatType = vctPlatType.begin(); itePlatType != vctPlatType.end(); itePlatType++)
					{
					cout<<"  "<< *itePlatType <<endl;
					}
					
					  }
					  }
*/


/*
int a[100][100];
for (i = 0; i<100;i++)
{
for (j = 0;j<100; j++)
{
a[i][j] = n + a[i][j-1];
}
}
*/


//���  0827  why 
//����μ�SPAmetri �����ĵ�;
//�������ϵ������
//����con�����洢���ϵ��,m,n��ʾ���������������
//ESM_Data��ʾESM��Ϣ
//COM_Data��ʾCOM��Ϣ
//TRACK_Data��ʾTRACK��Ϣ
//Comb_Data�ϲ��������
/*
void Coefficient(float con[][], int m, int n, VCT_COOPER_MSG::const_iterator ite_CooperMsg, VCT_sPlatType vctPlatType)
{
VCT_sPlatType::iterator ite_PlatType;
VCT_TRACE_MSG::const_iterator ite_TrackMsg;
VCT_TRACE_MSG::const_iterator ite_TrackM;
VCT_ESM_MSG::const_iterator ite_EsmMsg;
VCT_ESM_MSG::const_iterator ite_EsmM;
VCT_COMM_MSG::const_iterator ite_CommMsg;
VCT_COMM_MSG::const_iterator ite_CommM;

  typedef vector<double> VCT_CORR;
  VCT_CORR vctCorr;      // ��Ź���ϵ��������
  VCT_CORR::iterator ite_Corr;
  
	int i = 0;
	int j = 0;
	double dcorrAz = 0.0;
	double dMaxCorr = 0.0;
	double dcorrChongPin = 0.0;  //��Ƶ
    double dcorrMaiKuan = 0.0;   //����
	double dcorrTianXianScan = 0.0;  //����ɨ������
	double dcorrComZaiPin = 0.0;   // ��Ƶ
	double dcorrdPulseExtent =0.0; // �������
	double dAverCorr = 0.0;
	
	  
		//TRACK���ϵ��
		if (0 == ite_CooperMsg->vctTrace.size())
		{
		//�����ں������޺��������ϵ��
		} 
		else
		{
		//�����ϵ��
		//����������vectror
		for (ite_TrackMsg = ite_CooperMsg->vctTrace.begin(); ite_TrackMsg != ite_CooperMsg->vctTrace.end(); ite_TrackMsg++)
		{
		for (ite_PlatType = vctPlatType.begin(); ite_PlatType != vctPlatType.end(); ite_PlatType++)
		{
		//������ƽ̨���ͺ�ƽ̨�����е�������ͬ
		if (ite_TrackMsg->sPlatType == *ite_PlatType)
		{
		//ֱ��ȡ���Ŷ���Ϊ���ϵ��
		con[i][j] = ite_TrackMsg->dConfidence;
		} 
		//������ƽ̨���ͺ�ƽ̨�����е����Ͳ���ͬ
		else
		{
		//�������ϵ�� ��ȡ�ú�����Ϣ�ķ�λ�ͺ�����vector��������Ϣ��ʶ���ƽ̨�����еĸ����͵ĺ�����Ϣ��λ�Ƚ�,��δ�ҵ�����Ϊ0
		//��մ�����ϵ��������
		
		  vctCorr.clear();
		  //��������vector
		  
			for ( ite_TrackM = ite_CooperMsg->vctTrace.begin(); ite_TrackM != ite_CooperMsg->vctTrace.end();ite_TrackM++)
			{   //�ҳ�ʶ���ƽ̨���͵ĺ�����Ϣ
			if (*ite_PlatType == ite_TrackM->sPlatType)
			{
			Mf_SPA(ite_TrackM->dAzimuth, ite_TrackMsg->dAzimuth, dcorrAz);
			vctCorr.push_back(dcorrAz);
			}
			}// for
			if (vctCorr.empty())
			{
			con[i][j] = 0.0;
			}
			//����������Ϊ��
			else
			{
			//ȡ�������������ֵ
			//��������ֻ��һ��ֵ
			if ( vctCorr.size() == 1 )
			{
			con[i][j] = vctCorr.front(); 
			}
			//�����������ȴ���1
			if ( vctCorr.size() > 1 )
			{
			dMaxCorr = vctCorr.front();
			for(ite_Corr = vctCorr.begin(); ite_Corr != vctCorr.end(); ite_Corr++)
			{
			if ( dMaxCorr < *ite_Corr)
			{
			dMaxCorr = *ite_Corr;
			}
			}//for
			con[i][j] = dMaxCorr;	
			}  // if �������ȴ���1
			}//else  ����������Ϊ��
			
			  }//else  //������ƽ̨���ͺ�ƽ̨�����е����Ͳ���ͬ
			  j++;
			  } // for ����ƽ̨���͵����� ite_PlatType = vctPlatType.begin()
			  i++;
			  } // for �������������� ite_TrackMsg = ite_CooperMsg->vctTrace.begin()
			  }
			  
				//ESM���ϵ��
				if ( 0 == ite_CooperMsg->vctEsm.size())
				{
				//������ESM����Esm�����ϵ��
				}
				else
				{
				//�����ϵ��
				//����Esm������
				for ( ite_EsmMsg = ite_CooperMsg->vctEsm.begin(); ite_EsmMsg != ite_CooperMsg->vctEsm.end(); ite_CooperMsg++)
				{
				for (ite_PlatType = vctPlatType.begin(); ite_PlatType != vctPlatType.end(); ite_PlatType++)
				{
				//Esm��ƽ̨���ͺ�ƽ̨�����е�������ͬ
				if (ite_EsmMsg->sPlatType == *ite_PlatType)
				{
				//ֱ��ȡ���Ŷ���Ϊ���ϵ��
				con[i][j] = ite_EsmMsg->dConfidence;
				} 
				//Esm��ƽ̨���ͺ�ƽ̨�����е����Ͳ�ͬ
				else
				{
				//�������ϵ�� ��ȡ��Esm��Ϣ������������Esm��vector��������Ϣ��ʶ���ƽ̨�����еĸ����͵�Esm��Ϣ�����������Ƚ�,��δ�ҵ�����Ϊ0
				//��մ�����ϵ��������
				vctCorr.clear();
				//����Esm��vector
				
				  for ( ite_EsmM = ite_CooperMsg->vctEsm.begin(); ite_EsmM != ite_CooperMsg->vctEsm.end();ite_EsmM++)
				  {   //�ҳ�ʶ���ƽ̨���͵�Esm��Ϣ
				  if (*ite_PlatType == ite_EsmM->sPlatType)
				  {
				  Mf_SPA(ite_EsmM->dChongPin, ite_EsmMsg->dChongPin,dcorrChongPin); //Ƶ��
				  Mf_SPA(ite_EsmM->dMaiKuan,ite_EsmMsg->dMaiKuan,dcorrMaiKuan); //����
				  Mf_SPA(ite_EsmM->dTianXianScan,ite_EsmMsg->dTianXianScan,dcorrTianXianScan); //����ɨ������
				  dAverCorr = ( dcorrChongPin + dcorrMaiKuan +dcorrTianXianScan )/3;
				  vctCorr.push_back(dAverCorr);
				  }
				  }// for
				  if (vctCorr.empty())
				  {
				  con[i][j] = 0.0;
				  }
				  //����������Ϊ��
				  else
				  {
				  //ȡ�������������ֵ
				  //��������ֻ��һ��ֵ
				  if ( vctCorr.size() == 1 )
				  {
				  con[i][j] = vctCorr.front(); 
				  }
				  //�����������ȴ���1
				  if ( vctCorr.size() > 1 )
				  {
				  dMaxCorr = vctCorr.front();
				  for(ite_Corr = vctCorr.begin(); ite_Corr != vctCorr.end(); ite_Corr++)
				  {
				  if ( dMaxCorr < *ite_Corr)
				  {
				  dMaxCorr = *ite_Corr;
				  }
				  }//for
				  con[i][j] = dMaxCorr;	
				  }  // if �������ȴ���1
				  }//else  ����������Ϊ��
				  
					} //else //Esm��ƽ̨���ͺ�ƽ̨�����е����Ͳ�ͬ
					j++;
					}// for ����ƽ̨���͵�����
					i++;
					}// for ����Esm������
					}//else ��Esm�����ϵ��
					
					  //COMM���ϵ��
					  if ( 0 == ite_CooperMsg->vctComm.size())
					  {
					  //������Com,��Comm�����ϵ��
					  }
					  else
					  {
					  //�����ϵ��
					  //����Comm������
					  for ( ite_CommMsg = ite_CooperMsg->vctComm.begin(); ite_CommMsg != ite_CooperMsg->vctComm.end(); ite_CommMsg++)
					  {
					  for (ite_PlatType = vctPlatType.begin(); ite_PlatType != vctPlatType.end(); ite_PlatType++)
					  {
					  //Comm��ƽ̨���ͺ�ƽ̨�����е�������ͬ
					  if (ite_CommMsg->sPlatType == *ite_PlatType)
					  {
					  //ֱ��ȡ���Ŷ���Ϊ���ϵ��
					  con[i][j] = ite_CommMsg->dConfidence;
					  } 
					  //Esm��ƽ̨���ͺ�ƽ̨�����е����Ͳ�ͬ
					  else
					  {
					  //�������ϵ�� ��ȡ��Comm��Ϣ������������Comm��vector��������Ϣ��ʶ���ƽ̨�����еĸ����͵�Comm��Ϣ�����������Ƚ�,��δ�ҵ�����Ϊ0
					  //��մ�����ϵ��������
					  vctCorr.clear();
					  //����Esm��vector
					  
						for ( ite_CommM = ite_CooperMsg->vctComm.begin(); ite_CommM != ite_CooperMsg->vctComm.end();ite_CommM++)
						{   //�ҳ�ʶ���ƽ̨���͵�Comm��Ϣ
						if (*ite_PlatType == ite_EsmM->sPlatType)
						{
						Mf_SPA(ite_CommM->dComZaiPin, ite_CommMsg->dComZaiPin,dcorrComZaiPin); //��Ƶ
						Mf_SPA(ite_CommM->dPulseExtent,ite_CommMsg->dPulseExtent,dcorrdPulseExtent); //�������
						dAverCorr = ( dcorrComZaiPin + dcorrdPulseExtent )/2;
						vctCorr.push_back(dAverCorr);
						}
						}// for
						if (vctCorr.empty())
						{
						con[i][j] = 0.0;
						}
						//����������Ϊ��
						else
						{
						//ȡ�������������ֵ
						//��������ֻ��һ��ֵ
						if ( vctCorr.size() == 1 )
						{
						con[i][j] = vctCorr.front(); 
						}
						//�����������ȴ���1
						if ( vctCorr.size() > 1 )
						{
						dMaxCorr = vctCorr.front();
						for(ite_Corr = vctCorr.begin(); ite_Corr != vctCorr.end(); ite_Corr++)
						{
						if ( dMaxCorr < *ite_Corr)
						{
						dMaxCorr = *ite_Corr;
						}
						}//for
						con[i][j] = dMaxCorr;	
						}  // if �������ȴ���1
						}//else  ����������Ϊ��
						
						  } //else //Esm��ƽ̨���ͺ�ƽ̨�����е����Ͳ�ͬ
						  j++;
						  }// for ����ƽ̨���͵�����
						  i++;
						  }// for ����Esm������
						  
							}//else �����ϵ��
							
							  }
*/





/************************************************************************/
/*                             ���Է�������                             */
/************************************************************************/
/*
void Mf_SPA(double s, double t,double& corr)
{
double spa;
double tmp;

  double a,b,c;
  
	if(s>t)
	{
	tmp =s;
	s=t;
	t=tmp;
	}
	
	  a=s/t;
	  b=s/t/(t*t-1);
	  c=(t*t-s*t-1)/(t*t-1);
	  
		spa=a+fabs(b)-fabs(c);
		
		  corr=spa;                 //�����������ϵ��
		  }
*/






































