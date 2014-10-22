//******************************************************************************************//
//        多舰协同返回信息和请求信息合并部分 0831 wanghaiying                       //

//********  输入：主舰请求信息 ,收到的邻舰的信息                          ****************//
//********        主舰自身的地理位置信息                                          **********//
//********  输出：请求信息和返回信息的合并后的信息                     **********// 
//******************************************************************************************//
#include "CooperativeMsg.h"
#include "StdAfx.h"
#include <iostream>
#include <math.h>
#include <vector>
#include <string>
using namespace std;

//#define PI 3.1415926535898

//本舰邻舰都有自身航迹信息时（即都存在距离方位俯仰角时），本舰邻舰经纬高都已知，输出邻舰观测到的目标在本舰上的坐标及相对于本舰的经纬高。
void Get_Coordinate_Conversion_Module(double Rd1,double Az1,double Ez1,double Rd2,double Az2,double Ez2,double La1,double Ba1,double Ha1,
									  double La2,double Ba2,double Ha2,/*double *x1,double *y1,double *z1,*/double& Xt,double& Yt,double& Zt,double& Rdt,double& Azt,double& Ezt,double& SumCorr);
void Mf_SPA(double s, double t,double& corr); //s,t为相同类型的信息，进行集对分析，将返回的相关系数存入容器VctCorr中
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
	SHIP_POSITION stSelfPosi;  //需要获取本舰的经纬高 
// 	//假设经纬高:
// 	stSelfPosi.dHeight = 0.0;
// 	stSelfPosi.dLonti = 119.1;
// 	stSelfPosi.dLati = 22.5;	
	Cooperative_Msg stCooperMsg;   //按请求信息的综合批号进行合并
	//	VCT_COOPER_MSG vctCooperMsg;   //存放请求和返回的合并信息
	VCT_COOPER_MSG::iterator iteCooperMsg; 
	
	// 统计主舰的需要识别的各类信息数以及邻舰发送过来的各类信息的ESM，COM, 航迹信息条数
	VCT_BACK_Cooperative_Msg::iterator iteBackMsg;
	BACK_Cooperative_Msg stBackMsg;
	VCT_Request_Cooperative_Msg::iterator iteRequestMsg;
	VCT_TRACE_MSG::iterator iteTrack;
	VCT_ESM_MSG::iterator iteEsm;                
	VCT_COMM_MSG::iterator iteComm;
	
	//清空合并信息容器
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
	
	//测试数据
	//    for (iteBackMsg = vctBackCooperative.begin(); iteBackMsg != vctBackCooperative.end(); iteBackMsg++)
	//    {
	// 	     cout << "返回信息中COMM条数："<< iteBackMsg->vctComm.size() <<endl;
	// 		 cout << "返回信息中ESM条数："<< iteBackMsg->vctEsm.size() <<endl;
	//    } 90
	
	//将请求信息,返回信息放入合并容器中， 
	for ( iteRequestMsg = vctRequestCooperative.begin(); iteRequestMsg != vctRequestCooperative.end(); iteRequestMsg++ )
	{   
        stSelfPosi = iteRequestMsg->stReqShipPosi;  // 请求舰即为本舰
		if ( iteRequestMsg->lAutonum > 7999) //请求信息的中，综合批号大于等于8000，即为有聚类过的航迹信息
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
		//将返回信息放入合并信息中
		for ( iteBackMsg = vctBackCooperative.begin(); iteBackMsg != vctBackCooperative.end(); iteBackMsg++)
		{
			int Csizea = iteBackMsg->vctComm.size();
			if (iteBackMsg->lAutonum == iteRequestMsg->lAutonum)  //综合批号相同
			{
				//将返回信息的每类信息放入合并信息容器中
				if ( iteBackMsg->lAutonum >7999 ) //返回信息
					//  if ( iteBackMsg->BackTrackN !=0  ) //返回信息
				{	
					//转换航迹信息，将坐标，经纬度替换
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
					//测试 航迹信息的条数
					int Tsize = stCooperMsg.vctTrace.size();
					//非测试
					stCooperMsg.nTraceN = stCooperMsg.vctTrace.size();
				}
				//测试 航迹信息的条数
				int Esize = stCooperMsg.vctEsm.size();
				int Csize = stCooperMsg.vctComm.size();
				//非测试
				stCooperMsg.nEsmN = stCooperMsg.vctEsm.size();
				stCooperMsg.nComN = stCooperMsg.vctComm.size();
				
				if ( iteBackMsg->vctEsm.size() != 0)
				{
					for (iteEsm = iteBackMsg->vctEsm.begin(); iteEsm != iteBackMsg->vctEsm.end(); iteEsm++)
					{
						stCooperMsg.vctEsm.push_back(*iteEsm);
					}
				}
				//测试 返回的Comm的信息条数
				Csizea = iteBackMsg->vctComm.size();
				if ( iteBackMsg->vctComm.size() != 0)
				{
					for (iteComm = iteBackMsg->vctComm.begin(); iteComm != iteBackMsg->vctComm.end(); iteComm++)
					{
						stCooperMsg.vctComm.push_back(*iteComm);
					}
					
				}
				
			}//if 综合批号相同 结束
		}// for iteBackMsg
		vctCooperMsg.push_back(stCooperMsg);
		
		
	} //for iteRequestMsg
	//测试数据  合并信息条数
	// for (iteCooperMsg = vctCooperMsg.begin(); iteCooperMsg != vctCooperMsg.end(); iteCooperMsg++)
	// {
	// 	cout<<"Track: "<< iteCooperMsg->vctTrace.size() << endl;
	// 	cout<<"ESM: "<< iteCooperMsg->vctEsm.size() << endl;
	// 	cout<<"COM: "<< iteCooperMsg->vctComm.size() <<endl;
	// }
	//清空返回容器
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
// / ***            目标在雷达坐标系中位置计算模块                   *** /
// / **                     刘以安  2011-2-10                        *** /
// / ********      输入：目标平台位置（Lt,Bt,Ht）                ******* /
// / ********            雷达平台位置（L0,B0,H0）                ******* /
// / ********      输出：目标在雷达大地测量坐标系中的径距、方位和仰角 ** /
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
// 	Rd=sqrt(x*x+y*y+z*z);  //已知坐标XYZ，求出该坐标系下的距离，方位，仰角
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
// / *******      目标邻舰观测的径距、方位和仰角转到本舰同一坐标系中模块     ******* /
// // *******     输入：目标相对本舰1的径距、方位和仰角(Rd1,Az1,Ez1)         ******* /
// // *******           目标相对邻舰2的径距、方位和仰角(Rd2,Az2,Ez2)         ******* /
// / *******            本舰地理坐标（La1,Ba1,Ha1）                         ******** /
// / *******            邻舰地理坐标（La2,Ba2,Ha2）                         ******** /
// // *******     输出：//目标在本舰的大地雷达测量系中的坐标x1,y1,z1           ******* /
// / ********           目标从邻舰转到本舰的大地雷达测量系中的坐标Xt,Yt,Zt   ******* /
// / ********           目标从邻舰转到本舰的大地雷达测量系中的径距、方位和仰角(Rdt,Azt,Ezt) ** /
// / ********           目标相对两舰观测的集对综合相关系数SumCorr           ******** /
// / ******************************************************************************* /
// void Get_Coordinate_Conversion_Module(double Rd1,double Az1,double Ez1,double Rd2,double Az2,double Ez2,double La1,double Ba1,double Ha1,
// 									  double La2,double Ba2,double Ha2,/ *double *x1,double *y1,double *z1,* /
// 									  double& Xt,double& Yt,double& Zt,double& Rdt,double& Azt,double& Ezt,double& SumCorr_xyz)
// {
// 	double xa,ya,za;
// 	double x2,y2,z2;
// 	double xg,yg,zg;      //邻舰在本舰中的坐标
// 	double Rd,Az,Ez;
// 	double xt,yt,zt;
// 	
// 	double corr1,corr2,corr3/ *,corr4,corr5,corr6* /;   //放集对系数
//     double dertH;               //放高度补偿
// 	double G1;                  //邻舰与本舰之间的地面距离
// 	double ae;
// 	
// 	//目标在本舰的大地雷达坐标系中的直角坐标
// 	xa=Rd1*cos(Ez1)*sin(Az1);
// 	ya=Rd1*cos(Ez1)*cos(Az1);
// 	za=Rd1*sin(Ez1);
// 	
// // 	*x1=xa;    //带回目标在本舰中的坐标
// // 	*y1=ya;
// // 	*z1=za;
// 	
// 	//目标在邻舰的大地雷达坐标系中的直角坐标
// 	x2=Rd2*cos(Ez2)*sin(Az2);
// 	y2=Rd2*cos(Ez2)*cos(Az2);
// 	z2=Rd2*sin(Ez2);
// 	
// 	//目标相对于本舰的径距、方位和俯仰
// 	Object_Radar_Transform(La2,Ba2,Ha2,La1,Ba1,Ha1,Rd,Az,Ez); //邻舰位置可直接从战情获得，或协同请求时邻舰报文给出
// 	
// 	ae=4*6378130.0/3;                //地球等效半径(m),即为地球半径的三分之四
// 	G1=2*ae*asin(0.5*Rd/ae);
//     
// 	dertH=0.43*G1*G1/ae;           //高度补偿(相对于本舰)
// 	
// 	//邻舰位置在本舰中的坐标
// 	xg=Rd*cos(Ez)*sin(Az);
// 	yg=Rd*cos(Ez)*cos(Az);
// 	zg=Rd*sin(Ez)+dertH;              //高度补偿(相对于本舰)
// 	
// 	//坐标系平移：本舰视为旧坐标、邻舰视为新坐标
// 	//目标在本舰中的坐标为：
// 	xt=x2+xg;
// 	yt=y2+yg;
// 	zt=z2+zg; 
// 	
// 	Xt=xt;       //带回目标在本邻舰中转到本舰的坐标
// 	Yt=yt;
// 	Zt=zt;
// 	
// 	//调集对分析模块
// 	Mf_SPA(xa,xt,corr1);
// 	Mf_SPA(ya,yt,corr2);
// 	Mf_SPA(za,zt,corr3);
// 	
// 	SumCorr_xyz=0.5*corr1+0.3*corr2+0.2*corr3;		
// 
// 	//根据转换后的坐标，将目标在邻舰中的径距方位仰角转化成目标在本舰中的径距方位仰角
// 	Rdt=sqrt(xt*xt+yt*yt+zt*zt);  //已知坐标XYZ，求出该坐标系下的距离，方位，仰角
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
// // 	//调集对分析模块
// // 	Mf_SPA(Rd1,Rdt,&corr4);
// // 	Mf_SPA(Az1,Azt,&corr5);
// // 	Mf_SPA(Ez1,Ezt,&corr6);
// // 
// // 	
// // 	*AverCorr=SumCorr_xyz/4+corr4/4+corr5/4+corr6/4;	 //比例系数 有待修改（规定标准是什么????）
// 		
// }
// / ************************************************************************ /
// / *                             集对分析算子                             * /
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
// 	corr=spa;                 //带回两数相关系数
// }
*/









//////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///原版   错误，迭代器的问题，容器在变化，不可对迭代器进行写操作   （后面有修改版）////////////////////
/*	string s1("F111");
string sPt("F111");
//统计(同一综合批号下)所有信息的平台类型
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

  } // if容器中无平台类型
  else
  {
  for (itePlatType = vctPlatType.begin(); itePlatType != vctPlatType.end(); itePlatType++)
  {
  sPt.assign(iteTrack->sPlatType);
  s1.assign(*itePlatType);
  
	if ( sPt.compare(s1) != 0) //strcmp (*itePlatType, iteTrack->sPlatType) //   strcmp()对两个字符串进行大小写敏感的比较
	//  strcmpi() 对两个字符串进行大小写不敏感的比较
	{
	vctPlatType.push_back(sPt);
	//	vctPlatType.push_back(iteTrack->sPlatType);
	}
	cout << "长度"<< vctPlatType.size()<<endl;
	
	  }// for  itePlatType = vctPlatType.begin()
	  } //else 当存在平台类型				
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
////// 修改版    0831 王海颖 ////////////////////////////////////////////////////////////////////////////////////////////
//将合并后的所有信息的平台类型都放到同一容器1中
//定义容器1的两个迭代器a,b 迭代器a用来遍历平台容器，迭代器b用来比较平台容器中迭代器a当前值和之前值是否有相同的
//将不同的放入平台容器2中，
//平台容器2就是所求平台类型数

  //将合并后所有平台类型放到容器vctCooperPlatType
  
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
				//判断合并容器中前一个和后一个的平台类型是否相同，有相同，结束循环，循环结束若都不相同则放入平台容器中
				if (strcmp(*iteCPType1, *iteCPType2) == 0)
				{   tpflag = 1; //标志找到有相同的
				break;
				}
				}
				//结束循环未找到相同的
				if (tpflag == 0)
				{
				vctPlatType.push_back(*iteCPType1);
				}
				else
				{
				tpflag = 0;
				}
				}
				
				  //此时，已统计好同一综合批号下的目标类型数
				  int OBjTypeNum; //目标类型数
				  OBjTypeNum = vctPlatType.size();//为目标类型数
				  
					//测试平台数和平台类型
					cout <<"合并后信息平台类型数： "<<OBjTypeNum << endl;
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


//暑假  0827  why 
//具体参见SPAmetri 测试文档;
//计算相关系数矩阵
//矩阵con用来存储相关系数,m,n表示矩阵的行数和列数
//ESM_Data表示ESM信息
//COM_Data表示COM信息
//TRACK_Data表示TRACK信息
//Comb_Data合并后的数据
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
  VCT_CORR vctCorr;      // 存放关联系数的容器
  VCT_CORR::iterator ite_Corr;
  
	int i = 0;
	int j = 0;
	double dcorrAz = 0.0;
	double dMaxCorr = 0.0;
	double dcorrChongPin = 0.0;  //重频
    double dcorrMaiKuan = 0.0;   //脉宽
	double dcorrTianXianScan = 0.0;  //天线扫描周期
	double dcorrComZaiPin = 0.0;   // 载频
	double dcorrdPulseExtent =0.0; // 脉冲幅度
	double dAverCorr = 0.0;
	
	  
		//TRACK相关系数
		if (0 == ite_CooperMsg->vctTrace.size())
		{
		//不存在航迹，无航迹的相关系数
		} 
		else
		{
		//求相关系数
		//遍历航迹的vectror
		for (ite_TrackMsg = ite_CooperMsg->vctTrace.begin(); ite_TrackMsg != ite_CooperMsg->vctTrace.end(); ite_TrackMsg++)
		{
		for (ite_PlatType = vctPlatType.begin(); ite_PlatType != vctPlatType.end(); ite_PlatType++)
		{
		//航迹的平台类型和平台类型中的类型相同
		if (ite_TrackMsg->sPlatType == *ite_PlatType)
		{
		//直接取置信度作为相关系数
		con[i][j] = ite_TrackMsg->dConfidence;
		} 
		//航迹的平台类型和平台类型中的类型不相同
		else
		{
		//计算相关系数 ，取该航迹信息的方位和航迹的vector的所有信息中识别出平台类型中的该类型的航迹信息方位比较,若未找到则标记为0
		//清空存放相关系数的容器
		
		  vctCorr.clear();
		  //遍历航迹vector
		  
			for ( ite_TrackM = ite_CooperMsg->vctTrace.begin(); ite_TrackM != ite_CooperMsg->vctTrace.end();ite_TrackM++)
			{   //找出识别该平台类型的航迹信息
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
			//关联容器不为空
			else
			{
			//取关联容器的最大值
			//关联容器只有一个值
			if ( vctCorr.size() == 1 )
			{
			con[i][j] = vctCorr.front(); 
			}
			//关联容器长度大于1
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
			}  // if 容器长度大于1
			}//else  关联容器不为空
			
			  }//else  //航迹的平台类型和平台类型中的类型不相同
			  j++;
			  } // for 遍历平台类型的容器 ite_PlatType = vctPlatType.begin()
			  i++;
			  } // for 遍历航迹的容器 ite_TrackMsg = ite_CooperMsg->vctTrace.begin()
			  }
			  
				//ESM相关系数
				if ( 0 == ite_CooperMsg->vctEsm.size())
				{
				//不存在ESM，无Esm的相关系数
				}
				else
				{
				//求相关系数
				//遍历Esm的容器
				for ( ite_EsmMsg = ite_CooperMsg->vctEsm.begin(); ite_EsmMsg != ite_CooperMsg->vctEsm.end(); ite_CooperMsg++)
				{
				for (ite_PlatType = vctPlatType.begin(); ite_PlatType != vctPlatType.end(); ite_PlatType++)
				{
				//Esm的平台类型和平台类型中的类型相同
				if (ite_EsmMsg->sPlatType == *ite_PlatType)
				{
				//直接取置信度作为相关系数
				con[i][j] = ite_EsmMsg->dConfidence;
				} 
				//Esm的平台类型和平台类型中的类型不同
				else
				{
				//计算相关系数 ，取该Esm信息的特征参数和Esm的vector的所有信息中识别出平台类型中的该类型的Esm信息的特征参数比较,若未找到则标记为0
				//清空存放相关系数的容器
				vctCorr.clear();
				//遍历Esm的vector
				
				  for ( ite_EsmM = ite_CooperMsg->vctEsm.begin(); ite_EsmM != ite_CooperMsg->vctEsm.end();ite_EsmM++)
				  {   //找出识别该平台类型的Esm信息
				  if (*ite_PlatType == ite_EsmM->sPlatType)
				  {
				  Mf_SPA(ite_EsmM->dChongPin, ite_EsmMsg->dChongPin,dcorrChongPin); //频率
				  Mf_SPA(ite_EsmM->dMaiKuan,ite_EsmMsg->dMaiKuan,dcorrMaiKuan); //脉宽
				  Mf_SPA(ite_EsmM->dTianXianScan,ite_EsmMsg->dTianXianScan,dcorrTianXianScan); //天线扫描周期
				  dAverCorr = ( dcorrChongPin + dcorrMaiKuan +dcorrTianXianScan )/3;
				  vctCorr.push_back(dAverCorr);
				  }
				  }// for
				  if (vctCorr.empty())
				  {
				  con[i][j] = 0.0;
				  }
				  //关联容器不为空
				  else
				  {
				  //取关联容器的最大值
				  //关联容器只有一个值
				  if ( vctCorr.size() == 1 )
				  {
				  con[i][j] = vctCorr.front(); 
				  }
				  //关联容器长度大于1
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
				  }  // if 容器长度大于1
				  }//else  关联容器不为空
				  
					} //else //Esm的平台类型和平台类型中的类型不同
					j++;
					}// for 遍历平台类型的容器
					i++;
					}// for 遍历Esm的容器
					}//else 求Esm的相关系数
					
					  //COMM相关系数
					  if ( 0 == ite_CooperMsg->vctComm.size())
					  {
					  //不存在Com,无Comm的相关系数
					  }
					  else
					  {
					  //求相关系数
					  //遍历Comm的容器
					  for ( ite_CommMsg = ite_CooperMsg->vctComm.begin(); ite_CommMsg != ite_CooperMsg->vctComm.end(); ite_CommMsg++)
					  {
					  for (ite_PlatType = vctPlatType.begin(); ite_PlatType != vctPlatType.end(); ite_PlatType++)
					  {
					  //Comm的平台类型和平台类型中的类型相同
					  if (ite_CommMsg->sPlatType == *ite_PlatType)
					  {
					  //直接取置信度作为相关系数
					  con[i][j] = ite_CommMsg->dConfidence;
					  } 
					  //Esm的平台类型和平台类型中的类型不同
					  else
					  {
					  //计算相关系数 ，取该Comm信息的特征参数和Comm的vector的所有信息中识别出平台类型中的该类型的Comm信息的特征参数比较,若未找到则标记为0
					  //清空存放相关系数的容器
					  vctCorr.clear();
					  //遍历Esm的vector
					  
						for ( ite_CommM = ite_CooperMsg->vctComm.begin(); ite_CommM != ite_CooperMsg->vctComm.end();ite_CommM++)
						{   //找出识别该平台类型的Comm信息
						if (*ite_PlatType == ite_EsmM->sPlatType)
						{
						Mf_SPA(ite_CommM->dComZaiPin, ite_CommMsg->dComZaiPin,dcorrComZaiPin); //载频
						Mf_SPA(ite_CommM->dPulseExtent,ite_CommMsg->dPulseExtent,dcorrdPulseExtent); //脉冲幅度
						dAverCorr = ( dcorrComZaiPin + dcorrdPulseExtent )/2;
						vctCorr.push_back(dAverCorr);
						}
						}// for
						if (vctCorr.empty())
						{
						con[i][j] = 0.0;
						}
						//关联容器不为空
						else
						{
						//取关联容器的最大值
						//关联容器只有一个值
						if ( vctCorr.size() == 1 )
						{
						con[i][j] = vctCorr.front(); 
						}
						//关联容器长度大于1
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
						}  // if 容器长度大于1
						}//else  关联容器不为空
						
						  } //else //Esm的平台类型和平台类型中的类型不同
						  j++;
						  }// for 遍历平台类型的容器
						  i++;
						  }// for 遍历Esm的容器
						  
							}//else 求相关系数
							
							  }
*/





/************************************************************************/
/*                             集对分析算子                             */
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
		
		  corr=spa;                 //带回两数相关系数
		  }
*/






































