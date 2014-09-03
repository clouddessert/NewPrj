#include "SingleIdentify.h"

#include <vector>
#include <string>
#include <iostream>
#include <math.h>

using namespace std;

#define DTN 8000
#define NTN 7000
#define PI 3.1415926535898

typedef struct __STTYPE //举手表决要用的数据结构
{
	unsigned long lAutonum;   //综合批号
	//	char *type;    //目标类型
	//unsigned short sType;     
	char sType[32]; //平台类型
	double con;               //可信度	
}STTYPE;
typedef vector<STTYPE> TYPEVEC;

static int TN = DTN;        //有航迹批号
static int NN = NTN;        //无航迹批号
static Accuracy Acc;

/***********************************************************/
/**  将目标或观测站的经纬度和高程坐标变换为地心坐标模块   **/
/*******    输入：目标或观测站的地理位置Lt,Bt,Ht       *****/
/*******    输出：Xt,Yt,Zt                         *********/
/***********************************************************/
void Target_Position_Transform(double Lt, double Bt, double Ht, double *Xt, double *Yt, double *Zt)
{ 
	double Nt;
	double e2,a;
	
	a=6378137.0;        //地球长半轴
	
	e2=0.0066943799014;
	
    Nt=a/sqrt(1.0-e2*sin(Bt)*sin(Bt));        //地球曲率半径
	
    *Xt=(Nt+Ht)*cos(Bt)*cos(Lt);
    *Yt=(Nt+Ht)*cos(Bt)*sin(Lt);
    *Zt=(Nt*(1-e2)+Ht)*sin(Bt);
 }

/*******************************************************************************/
/*******      将目标相对于WGS-84坐标系转成经纬度和高程模块               *******/
/*******                          (不需要调此模块)                       *******/
//*******     输入：目标坐标(WGS-84坐标)                                 *******/
//*******     输出：目标经度(Lt)、纬度(Bt)和高程(Ht)                     *******/
/*******************************************************************************/
void GET_Satellite_Trans(double xt,double yt,double zt,double *Lt,double *Bt,double *Ht)
{
	double a,b;                //地球长半轴(m),短半轴
    double e2;                 //扁心率
    double N0,H0,B0;
	double N1,H1,B1;
	
    a=6378130.0;                //地球长半轴(m)
	
	e2=0.0066943799014;
    b=a*(1.0-1.0/298.257223563);	
	
	//迭代运行计算在地纬度
	N0=a;
	H0=sqrt(xt*xt+yt*yt+zt*zt)-sqrt(a*b);
	B0=atan(zt/sqrt(xt*xt+yt*yt)/(1-e2*N0/(N0+H0)));
	
	N1=a/sqrt(1-e2*sin(B0)*sin(B0));
	H1=sqrt(xt*xt+yt*yt)/cos(B0)-N1;
	B1=atan(zt/sqrt(xt*xt+yt*yt)/(1-e2*N1/(N1+H1)));
	
	while(fabs(H1-H0)>0.001 || fabs(B1-B0)>0.00001)
	{
		N0=N1;
		H0=H1;
		B0=B1;
		
		N1=a/sqrt(1-e2*sin(B0)*sin(B0));
		H1=sqrt(xt*xt+yt*yt)/cos(B0)-N1;
		B1=atan(zt/sqrt(xt*xt+yt*yt)/(1-e2*N1/(N1+H1)));	
	}
	
	if(yt>0 && xt>0)
		*Lt=atan(yt/xt);    //大地经度
	else if(yt>0 && xt<0)
		*Lt=atan(yt/xt)+PI;
	else if(yt>0 && fabs(xt)<10e-6)
		*Lt=0.5*PI;
	else if(xt>0 && fabs(yt)<10e-6)
		*Lt=0;
	else if(yt<0 && fabs(xt)<10e-6)
		*Lt=-0.5*PI;
	else if(xt<0 && yt<0)
		*Lt=atan(yt/xt)-PI;
	else if(xt<0 && fabs(yt)<10e-6)
		*Lt=-PI;
	else if(xt>0 && yt<0)
		*Lt=atan(yt/xt);
	
	*Bt=B1;             //大地纬度
	*Ht=sqrt(xt*xt+yt*yt)/cos(B1)-N1;             //高程
}
/*航迹外推函数*/
void NextTrace(double Lt0, double Bt0, double Ht0, double Vx, double Vy, double Vz, double *Lt, double *Bt, double *Ht)
{
	double Xt0;
	double Yt0;
	double Zt0;
	Target_Position_Transform(Lt0, Bt0, Ht0, &Xt0, &Yt0, &Zt0);
	double Xt = Xt0 + Vx /** dlt*/;
	double Yt = Yt0 + Vy /** dlt*/;
	double Zt = Zt0 + Vz /** dlt*/;
	GET_Satellite_Trans(Xt, Yt, Zt, Lt, Bt, Ht);
}
/*******************************************************************/
/***            目标在雷达坐标系中位置计算模块(不需要调此模块)   ***/
/**                     刘以安  2011-2-10                        ***/
/********      输入：目标平台位置（Lt,Bt,Ht）                *******/
/********            雷达平台位置（L0,B0,H0）                *******/
/********      输出：目标在雷达大地测量坐标系中的径距、方位和仰角 **/
/*******************************************************************/
void Object_Radar_Transform(double Lt,double Bt,double Ht,double L0,double B0,double H0,double *rd,double *az,double *ez)
{
	double a,e2;
	double Nt,Nr;
	double xt,yt,zt,x0,y0,z0;
	double Rd,Az,Ez;
	double x,y,z;
	
	a=6378137;
	e2=0.0066943799014;
	
	Nt=a/sqrt(1-e2*sin(Bt)*sin(Bt));
	Nr=a/sqrt(1-e2*sin(B0)*sin(B0));
	
	xt=(Nt+Ht)*cos(Bt)*cos(Lt);
	yt=(Nt+Ht)*cos(Bt)*sin(Lt);
	zt=(Nt*(1-e2)+Ht)*sin(Bt);
	
	x0=(Nr+H0)*cos(B0)*cos(L0);
	y0=(Nr+H0)*cos(B0)*sin(L0);
	z0=(Nr*(1-e2)+H0)*sin(B0);
	
	x=-(xt-x0)*sin(L0)+(yt-y0)*cos(L0);
	y=-(xt-x0)*sin(B0)*cos(L0)-(yt-y0)*sin(B0)*sin(L0)+(zt-z0)*cos(B0);
	z=(xt-x0)*cos(B0)*cos(L0)+(yt-y0)*cos(B0)*sin(L0)+(zt-z0)*sin(B0);
	
	Rd=sqrt(x*x+y*y+z*z);
	if(x>=0&&y>0)
	{
		Az=atan(x/y);
	}
	else if(x>0&&fabs(y)<1.0e-3)
	{
		Az=0.5*PI;
	}
	else if(y<0)
	{
		Az=PI+atan(x/y);
	}
	else if(x<0&&fabs(y)<1.0e-3)
	{
		Az=1.5*PI;
	}
	else if(x<0&&y>0)
	{
		
		Az=2*PI+atan(x/y);
	}
	
	Ez=atan(z/sqrt(x*x+y*y)); 
	
	*rd=Rd;
	*az=Az;
	*ez=Ez;       
}
/**********************************************第一次信息处理******************************************/
void FirstClusterUni(ALL_MSG_INPUT& AllMessage, VCT_UNINUM_MSG& UniMsg, VCT_UNINOTRACE_MSG& UniNoTrace, VCT_TRACE_MSG& SingleTrace, VCT_ESM_MSG& SingleEsm, VCT_COMM_MSG& SingleComm)
{
	Acc.dirAcc = 1.0;           // 测向精度
	
	float fTraceAz(0.0);		// 敌方航迹方位角
	float fReachA(0.0);         // 敌方到达方位角
	float fA(0.0);              // 敌方方位角差
 	UNI_NUM StClu;              //临时存储有航迹同方位所有信息
	UNI_NOTRACE_NUM StCluNo;    //临时存储无航迹同方位所有信息
	
	/*用来遍历的迭代器*/	
	VCT_TRACE_MSG::iterator iteTrace;
	VCT_ESM_MSG::iterator iteEsm;
	VCT_ESM_MSG::iterator iteE;
	VCT_COMM_MSG::iterator iteComm;
	VCT_COMM_MSG::iterator iteC;
	
	/*有航迹信息*/
	for (iteTrace = AllMessage.stTrace.begin(); iteTrace != AllMessage.stTrace.end(); iteTrace++)
	{
		/*清空StClu*/
		StClu.lAutonum = NULL;
		for (iteE = StClu.vctEsm.begin(); iteE != StClu.vctEsm.end(); iteE++)
		{
			memset(&(*iteE), 0, sizeof(ESMSTATUS_MARK));
		}
		for (iteC = StClu.vctComm.begin(); iteC != StClu.vctComm.end(); iteC++)
		{
			memset(&(*iteC), 0, sizeof(COMSTATUS_MARK));
		}
		StClu.vctEsm.clear();
		StClu.vctComm.clear();
		
		
		/***方位聚类***/		
		fTraceAz = iteTrace->dAzimuth;	// 航迹提供的方位角
// 		StClu.lAutonum = TN;
// 		TN ++;
		
		iteTrace->cJfFlag = '1';
		iteTrace->lFlag = 3;//累加标志：消失一次lFlag--,3次不出现则为0
		StClu.structTrace = *iteTrace;
		
		/*对未聚类的ESM信息进行处理*/
		for (iteEsm = AllMessage.stEsm.begin(); iteEsm != AllMessage.stEsm.end(); iteEsm++)
		{
			if (iteEsm->cJfFlag == 0)
			{
				fReachA = iteEsm->dReachAzimuth; // ESM提供的方位角
				fA = fabs(fReachA - fTraceAz);				
				/*聚为一类*/
				if ((fA < Acc.dirAcc*2))
				{
					iteEsm->cJfFlag = '1';//聚类标志
					iteEsm->lFlag = 3;//累加标志：消失一次lFlag--,3次不出现则为0
					iteEsm->lAutonum = TN;//编批
					StClu.vctEsm.push_back(*iteEsm);//存储ESM信息
				}
			}
		}
		
		/*对未聚类的COMM信息进行处理*/
		for (iteComm = AllMessage.stComm.begin(); iteComm != AllMessage.stComm.end(); iteComm++)
		{
			if (iteComm->cJfFlag == 0)
			{
				fReachA = iteComm->dReachAzimuth; // COM提供的方位角
				fA = fabs(fReachA - fTraceAz);
				/*聚为一类*/
				if ((fA < Acc.dirAcc*2)/* && (detElevation < stComAcc.dirAcc*2)*/)
				{
					iteComm->cJfFlag = '1';//聚类标志
					iteComm->lFlag = 3;//累加标志：消失一次lFlag--,3次不出现则为0
					iteComm->lAutonum = TN;//编批
					StClu.vctComm.push_back(*iteComm);//存储COMM信息
				} 
			}
		}
		/*聚类结果StClu存储*/
		if (StClu.vctComm.empty()&&StClu.vctEsm.empty())//只有航迹信息
		{
			iteTrace->lAutonum = 0;
			SingleTrace.push_back(*iteTrace);//放入未聚类的单一航迹中存储
		} 
		else
		{
			StClu.lAutonum = TN;//编批
			iteTrace->lAutonum = TN;
			StClu.structTrace.lAutonum = TN;
// 			for (iteE = StClu.vctEsm.begin(); iteE != StClu.vctEsm.end(); iteE++)
// 			{
// 				iteE->lAutonum = TN;
// 			}
// 			for (iteC = StClu.vctComm.begin(); iteC != StClu.vctComm.end(); iteC++)
// 			{
// 				iteC->lAutonum = TN;
// 			}
			TN ++;
			UniMsg.push_back(StClu);//存入有航迹聚类信息
		}
		
	}

	/*无航迹信息*/
	for (iteEsm = AllMessage.stEsm.begin(); iteEsm != AllMessage.stEsm.end(); iteEsm++)//对未聚类的ESM信息进行处理
	{		
		if (iteEsm->cJfFlag == 0)
		{
			/*清空StCluNo*/
			StCluNo.lAutonum = NULL;
			for (iteE = StCluNo.vctEsm.begin(); iteE != StCluNo.vctEsm.end(); iteE++)
			{
				memset(&(*iteE), 0, sizeof(ESMSTATUS_MARK));
			}
			for (iteC = StCluNo.vctComm.begin(); iteC != StCluNo.vctComm.end(); iteC++)
			{
				memset(&(*iteC), 0, sizeof(COMSTATUS_MARK));
			}
			StCluNo.vctEsm.clear();
			StCluNo.vctComm.clear();

			fReachA = iteEsm->dReachAzimuth; // ESM提供的方位角
// 			StCluNo.lAutonum = NN;
// 			NN++;
			iteEsm->cJfFlag = '1';//聚类标志
			iteEsm->lFlag = 3;//累加标志：消失一次lFlag--,3次不出现则为0
			/*对未聚类的ESM信息进行处理*/
			iteE = iteEsm;
			for (iteE ++; iteE != AllMessage.stEsm.end(); iteE ++)
			{
				if (iteE->cJfFlag == 0)
				{
					fA = fabs(fReachA - iteE->dReachAzimuth);				
					/*聚为一类*/
					if ((fA < Acc.dirAcc*2))
					{
						iteE->cJfFlag = '1';//聚类标志
						iteE->lFlag = 3;//累加标志：消失一次lFlag--,3次不出现则为0
						iteE->lAutonum = NN;//编批
						StCluNo.vctEsm.push_back(*iteE);//存储ESM信息
					}
				}
			}
			
			/*对未聚类的COMM信息进行处理*/
			for (iteComm = AllMessage.stComm.begin(); iteComm != AllMessage.stComm.end(); iteComm++)
			{
				if (iteComm->cJfFlag == 0)
				{
					fA = fabs(fReachA - iteComm->dReachAzimuth);
					/*聚为一类*/
					if ((fA < Acc.dirAcc*2)/* && (detElevation < stComAcc.dirAcc*2)*/)
					{
						iteComm->cJfFlag = '1';//聚类标志
						iteComm->lFlag = 3;//累加标志：消失一次lFlag--,3次不出现则为0
						iteComm->lAutonum = NN;//编批
						StCluNo.vctComm.push_back(*iteComm);//存储COMM信息
					} 
				}
			}
			/*聚类结果StCluNo存储*/
			if (StCluNo.vctComm.empty()&&(StCluNo.vctEsm.size()<2))//只有ESM信息
			{
				iteEsm->lAutonum = 0;
				SingleEsm.push_back(*iteEsm);//放入未聚类的单一ESM中存储
			} 
			else
			{
				StCluNo.lAutonum = NN;//编批
				iteEsm->lAutonum = NN;
				StCluNo.vctEsm.push_back(*iteEsm);
// 				for (iteE = StCluNo.vctEsm.begin(); iteE != StCluNo.vctEsm.end(); iteE++)
// 				{
// 					iteE->lAutonum = NN;
// 				}
// 				for (iteC = StCluNo.vctComm.begin(); iteC != StCluNo.vctComm.end(); iteC++)
// 				{
// 					iteC->lAutonum = NN;
// 				}
				NN++;
				UniNoTrace.push_back(StCluNo);//存入无航迹聚类信息
			}	
		}
	}


	for (iteComm = AllMessage.stComm.begin(); iteComm != AllMessage.stComm.end(); iteComm++)//对未聚类的COMM信息进行处理
	{
		if (iteComm->cJfFlag == 0)
		{
			/*清空StCluNo*/
			StCluNo.lAutonum = NULL;
			for (iteE = StCluNo.vctEsm.begin(); iteE != StCluNo.vctEsm.end(); iteE++)
			{
				memset(&(*iteE), 0, sizeof(ESMSTATUS_MARK));
			}
			for (iteC = StCluNo.vctComm.begin(); iteC != StCluNo.vctComm.end(); iteC++)
			{
				memset(&(*iteC), 0, sizeof(COMSTATUS_MARK));
			}
			StCluNo.vctEsm.clear();
			StCluNo.vctComm.clear();
			
			fReachA = iteComm->dReachAzimuth; // ESM提供的方位角
// 			StCluNo.lAutonum = NN;
// 			NN++;
			iteComm->cJfFlag = '1';//聚类标志
			iteComm->lFlag = 3;//累加标志：消失一次lFlag--,3次不出现则为0
			/*对未聚类的COMM信息进行处理*/
			iteC = iteComm;
			for (iteC++; iteC != AllMessage.stComm.end(); iteC++)
			{
				if (iteC->cJfFlag == 0)
				{
					fA = fabs(fReachA - iteC->dReachAzimuth);
					/*聚为一类*/
					if ((fA < Acc.dirAcc*2)/* && (detElevation < stComAcc.dirAcc*2)*/)
					{
						iteC->cJfFlag = '1';//聚类标志
						iteC->lFlag = 3;//累加标志：消失一次lFlag--,3次不出现则为0
						iteC->lAutonum = NN;//编批
						StCluNo.vctComm.push_back(*iteC);//存储COMM信息
					} 
				}
			}
			/*聚类结果StCluNo存储*/
			if (StCluNo.vctComm.size()<2)//只有COMM信息
			{
				iteComm->lAutonum = 0;
				SingleComm.push_back(*iteComm);//放入未聚类的单一COMM中存储
			} 
			else
			{
				StCluNo.lAutonum = NN;
				iteComm->lAutonum = NN;
				StCluNo.vctComm.push_back(*iteComm);
// 				for (iteC = StCluNo.vctComm.begin(); iteC != StCluNo.vctComm.end(); iteC++)
// 				{
// 					iteC->lAutonum = NN;
// 				}
				NN++;
				UniNoTrace.push_back(StCluNo);//存入无航迹聚类信息
			}
		}
	}
}


/**********************************************之后信息处理******************************************/
void ClusterUni(ALL_MSG_INPUT& AllMessage, VCT_UNINUM_MSG& UniMsg, VCT_UNINOTRACE_MSG& UniNoTrace, VCT_TRACE_MSG& SingleTrace, VCT_ESM_MSG& SingleEsm, VCT_COMM_MSG& SingleComm)
{
	Acc.dirAcc = 1.0;           // 测向精度
	float fA(0.0);              // 敌方方位角差
 	UNI_NUM StClu;               // 临时变量 存有航迹信息结构
 	UNI_NOTRACE_NUM StCluNo;     // 临时变量 存无航迹信息结构
	
	/*用来遍历的迭代器*/
	VCT_UNINUM_MSG::iterator iteUni;
	VCT_UNINOTRACE_MSG::iterator iteNoTrace;
	VCT_TRACE_MSG::iterator iteTrace;
	VCT_TRACE_MSG::iterator iteT;
	VCT_ESM_MSG::iterator iteEsm;
 	VCT_ESM_MSG::iterator iteE;
	VCT_COMM_MSG::iterator iteComm;
 	VCT_COMM_MSG::iterator iteC;
	
	/*有航迹聚类信息*/
	/*1.是否有航迹信息更新  2.更新其他信息*/
	for (iteUni = UniMsg.begin(); iteUni!= UniMsg.end(); iteUni++)
	{
		//有航迹信息更新，更新航迹信息
		for (iteTrace = AllMessage.stTrace.begin(); iteTrace != AllMessage.stTrace.end(); iteTrace++)
		{
			if (iteUni->structTrace.lTargetNumber ==iteTrace->lTargetNumber)//有批号一样的trace更新
			{
				iteTrace->cJfFlag = 1;
				iteTrace->lFlag = 3;//出现，标记为3
				iteTrace->lAutonum = iteUni->lAutonum;
				iteUni->structTrace = (*iteTrace);//更新				
			} 
		}
		//更新其他信息
		/*处理ESM信息*/
		for (iteE = iteUni->vctEsm.begin(); iteE != iteUni->vctEsm.end(); iteE++)//有批号一样的esm更新
		{
			for (iteEsm = AllMessage.stEsm.begin(); iteEsm != AllMessage.stEsm.end(); iteEsm++)
			{
				if (iteE->lTargetNumber == iteEsm->lTargetNumber)//批号一样
				{
					iteEsm->cJfFlag = 1;
					iteEsm->lFlag = 3;//出现，标记为3
					iteEsm->lAutonum = iteUni->lAutonum;
					*iteE = *iteEsm;//更新					
				}
			}
		}
		for (iteEsm = AllMessage.stEsm.begin(); iteEsm != AllMessage.stEsm.end(); iteEsm++)//有方位一样的esm添加
		{
			if (!iteEsm->cJfFlag)//未聚类
			{
				fA = fabs(iteUni->structTrace.dAzimuth - iteEsm->dReachAzimuth);
				if (fA < Acc.dirAcc*2)//聚为一类
				{
					iteEsm->cJfFlag = 1;
					iteEsm->lFlag = 3;//出现，标记为3
					iteEsm->lAutonum = iteUni->lAutonum;//编批
					iteUni->vctEsm.push_back(*iteEsm);//添加					
				}
			}
		}
		/*处理COMM信息*/
		for (iteC = iteUni->vctComm.begin(); iteC != iteUni->vctComm.end(); iteC++)//有批号一样的Comm更新
		{
			for (iteComm = AllMessage.stComm.begin(); iteComm != AllMessage.stComm.end(); iteComm++)
			{
				if (iteC->lTargetNumber == iteComm->lTargetNumber)//批号一样
				{
					iteComm->cJfFlag = 1;
					iteComm->lFlag = 3;//出现，标记为3
					iteComm->lAutonum = iteUni->lAutonum;
					*iteC = *iteComm;//更新
				}
			}
		}
		for (iteComm = AllMessage.stComm.begin(); iteComm != AllMessage.stComm.end(); iteComm++)//有方位一样的Comm添加
		{
			if (!iteComm->cJfFlag)//未聚类
			{
				fA = fabs(iteUni->structTrace.dAzimuth - iteComm->dReachAzimuth);
				if (fA < Acc.dirAcc*2)//聚为一类
				{
					iteComm->cJfFlag = 1;
					iteComm->lFlag = 3;//出现，标记为3
					iteComm->lAutonum = iteUni->lAutonum;//编批
					iteUni->vctComm.push_back(*iteComm);//添加
				}
			}
		}
	}

	/*无航迹聚类信息*/
	for (iteNoTrace = UniNoTrace.begin(); iteNoTrace != UniNoTrace.end(); iteNoTrace++)
	{
		//取得方位角
		if (!iteNoTrace->vctEsm.empty())
		{
			iteE = iteNoTrace->vctEsm.begin();
			fA = iteE->dReachAzimuth;//取方位
		}
		else
		{
			iteC = iteNoTrace->vctComm.begin();
			fA = iteC->dReachAzimuth;//取方位
		}
		/*处理ESM信息*/
		for (iteE = iteNoTrace->vctEsm.begin(); iteE != iteNoTrace->vctEsm.end(); iteE++)//有批号一样的esm更新
		{
			for (iteEsm = AllMessage.stEsm.begin(); iteEsm != AllMessage.stEsm.end(); iteEsm++)
			{
				if (iteE->lTargetNumber == iteEsm->lTargetNumber)//批号一样
				{
					iteEsm->cJfFlag = 1;
					iteEsm->lFlag = 3;//出现，标记为3
					iteEsm->lAutonum = iteNoTrace->lAutonum;
					*iteE = *iteEsm;//更新					
				}
			}
		}
		for (iteEsm = AllMessage.stEsm.begin(); iteEsm != AllMessage.stEsm.end(); iteEsm++)//有方位一样的esm添加
		{
			if (!iteEsm->cJfFlag)//未聚类
			{
				fA = fabs(fA - iteEsm->dReachAzimuth);
				if (fA < Acc.dirAcc*2)//聚为一类
				{
					iteEsm->cJfFlag = 1;
					iteEsm->lFlag = 3;//出现，标记为3
					iteEsm->lAutonum = iteNoTrace->lAutonum;//编批
					iteNoTrace->vctEsm.push_back(*iteEsm);//添加					
				}
			}
		}
		
		/*处理COMM信息*/
		for (iteC = iteUni->vctComm.begin(); iteC != iteUni->vctComm.end(); iteC++)//有批号一样的Comm更新
		{
			for (iteComm = AllMessage.stComm.begin(); iteComm != AllMessage.stComm.end(); iteComm++)
			{
				if (iteC->lTargetNumber == iteComm->lTargetNumber)//批号一样
				{
					iteComm->cJfFlag = 1;
					iteComm->lFlag = 3;//出现，标记为3
					iteComm->lAutonum = iteNoTrace->lAutonum;
					*iteC = *iteComm;//更新
				}
			}
		}
		for (iteComm = AllMessage.stComm.begin(); iteComm != AllMessage.stComm.end(); iteComm++)//有方位一样的Comm添加
		{
			if (!iteComm->cJfFlag)//未聚类
			{
				fA = fabs(fA - iteComm->dReachAzimuth);
				if (fA < Acc.dirAcc*2)//聚为一类
				{
					iteComm->cJfFlag = 1;
					iteComm->lFlag = 3;//出现，标记为3
					iteComm->lAutonum = iteNoTrace->lAutonum;//编批
					iteUni->vctComm.push_back(*iteComm);//添加
				}
			}
		}

		/*处理trace信息:有可聚类的航迹信息，则聚类，并将此批号的信息存入有航迹信息中*/
		for (iteTrace = AllMessage.stTrace.begin(); iteTrace != AllMessage.stTrace.end(); iteTrace++)//有方位一样的Comm添加
		{
			if (!iteTrace->cJfFlag)//未聚类
			{
				fA = fabs(fA - iteTrace->dAzimuth);
				if (fA < Acc.dirAcc*2)//聚为一类，存入有航迹信息
				{
					/*清空StClu*/
					for (iteE = StClu.vctEsm.begin(); iteE != StClu.vctEsm.end(); iteE++)
					{
						memset(&(*iteE), 0, sizeof(ESMSTATUS_MARK));
					}
					for (iteC = StClu.vctComm.begin(); iteC != StClu.vctComm.end(); iteC++)
					{
						memset(&(*iteC), 0, sizeof(COMSTATUS_MARK));
					}
					StClu.vctEsm.clear();
					StClu.vctComm.clear();

					iteTrace->cJfFlag = 1;
					iteTrace->lFlag = 3;//出现，标记为3
					StClu.structTrace = *iteTrace;//structTrace				
					for (iteE = iteNoTrace->vctEsm.begin(); iteE != iteNoTrace->vctEsm.end(); iteE++)//vctEsm
					{
						StClu.vctEsm.push_back(*iteE);
					}
					for (iteC = iteNoTrace->vctComm.begin(); iteC != iteNoTrace->vctComm.end(); iteC++)//vctComm
					{
						StClu.vctComm.push_back(*iteC);
					}
					StClu.lAutonum = TN;//编批
					StClu.structTrace.lAutonum = TN;
					for (iteE = StClu.vctEsm.begin(); iteE != StClu.vctEsm.end(); iteE++)
					{
						iteE->lAutonum = TN;
					}
					for (iteC = StClu.vctComm.begin(); iteC != StClu.vctComm.end(); iteC++)
					{
						iteC->lAutonum = TN;
					}
					TN++;
					UniMsg.push_back(StClu);
				}
			}
		}
		
	}

	/*未聚类信息*/
	//航迹信息
	for(iteT = SingleTrace.begin(); iteT != SingleTrace.end(); iteT++)
	{
		/*清空StClu*/
		StClu.lAutonum = NULL;
		for (iteE = StClu.vctEsm.begin(); iteE != StClu.vctEsm.end(); iteE++)
		{
			memset(&(*iteE), 0, sizeof(ESMSTATUS_MARK));
		}
		for (iteC = StClu.vctComm.begin(); iteC != StClu.vctComm.end(); iteC++)
		{
			memset(&(*iteC), 0, sizeof(COMSTATUS_MARK));
		}
		StClu.vctEsm.clear();
		StClu.vctComm.clear();

		fA = iteT->dAzimuth;		
		for(iteTrace = AllMessage.stTrace.begin(); iteTrace != AllMessage.stTrace.end(); iteTrace++)//未处理信息
		{
			if (!iteTrace->cJfFlag)//未聚类
			{
				if(iteT->lTargetNumber == iteTrace->lTargetNumber)
				{
					iteTrace->cJfFlag = 1;
					iteTrace->lFlag = 3;//出现，标记为3
					iteTrace->lAutonum = 0;
					*iteT = *iteTrace;//更新
				}
			}
		}
		for(iteEsm = AllMessage.stEsm.begin(); iteEsm != AllMessage.stEsm.end(); iteEsm++)//未处理信息
		{
			if (!iteEsm->cJfFlag)//未聚类
			{
				fA = fabs(fA - iteEsm->dReachAzimuth);
				if (fA < Acc.dirAcc*2)//聚为一类
				{
					iteEsm->cJfFlag = 1;
					iteEsm->lFlag = 3;//出现，标记为3
					StClu.vctEsm.push_back(*iteEsm);
				}
			}
		}
		for(iteComm = AllMessage.stComm.begin(); iteComm != AllMessage.stComm.end(); iteComm++)//未处理信息
		{
			if (!iteComm->cJfFlag)//未聚类
			{
				fA = fabs(fA - iteComm->dReachAzimuth);
				if (fA < Acc.dirAcc*2)//聚为一类
				{
					iteComm->cJfFlag = 1;
					iteComm->lFlag = 3;//出现，标记为3
					StClu.vctComm.push_back(*iteComm);
				}
			}
		}
		if (StClu.vctComm.empty()&&StClu.vctEsm.empty())//只有航迹信息
		{
			iteT->lAutonum = 0;
		} 
		else
		{
			StClu.structTrace = *iteT;
			StClu.lAutonum = TN;//编批
			StClu.structTrace.lAutonum = TN;
			for (iteE = StClu.vctEsm.begin(); iteE != StClu.vctEsm.end(); iteE++)
			{
				iteE->lAutonum = TN;
			}
			for (iteC = StClu.vctComm.begin(); iteC != StClu.vctComm.end(); iteC++)
			{
				iteC->lAutonum = TN;
			}
			TN ++;
			UniMsg.push_back(StClu);//存入有航迹聚类信息
		}
	}
	//ESM信息
	for (iteE = SingleEsm.begin(); iteE != SingleEsm.end(); iteE++)
	{
		/*清空StClu*/
		StClu.lAutonum = NULL;
		for (iteEsm = StClu.vctEsm.begin(); iteEsm != StClu.vctEsm.end(); iteEsm++)
		{
			memset(&(*iteEsm), 0, sizeof(ESMSTATUS_MARK));
		}
		for (iteComm = StClu.vctComm.begin(); iteComm != StClu.vctComm.end(); iteComm++)
		{
			memset(&(*iteComm), 0, sizeof(COMSTATUS_MARK));
		}
		StClu.vctEsm.clear();
		StClu.vctComm.clear();
		/*清空StCluNo*/
		StCluNo.lAutonum = NULL;
		for (iteEsm = StCluNo.vctEsm.begin(); iteEsm != StCluNo.vctEsm.end(); iteEsm++)
		{
			memset(&(*iteE), 0, sizeof(ESMSTATUS_MARK));
		}
		for (iteComm = StCluNo.vctComm.begin(); iteComm != StCluNo.vctComm.end(); iteComm++)
		{
			memset(&(*iteComm), 0, sizeof(COMSTATUS_MARK));
		}
		StCluNo.vctEsm.clear();
		StCluNo.vctComm.clear();

		fA = iteE->dReachAzimuth;
		for (iteEsm = AllMessage.stEsm.begin(); iteEsm != AllMessage.stEsm.end(); iteEsm++)//AllMessage.stEsm
		{
			if (!iteEsm->cJfFlag)//未聚类
			{
				if (iteE->lTargetNumber == iteEsm->lTargetNumber)//批号一样
				{
					iteEsm->cJfFlag = 1;
					iteEsm->lFlag = 3;//出现，标记为3
					iteEsm->lAutonum = 0;
					*iteE = *iteEsm;//更新
				}
			}			
		}
		for(iteTrace = AllMessage.stTrace.begin(); iteTrace != AllMessage.stTrace.end(); iteTrace++)//AllMessage.stTrace
		{
			if (!iteTrace->cJfFlag)//未聚类
			{
				fA = fabs(fA - iteTrace->dAzimuth);
				if (fA < Acc.dirAcc*2)//聚为一类
				{
					iteTrace->cJfFlag = 1;
					iteTrace->lFlag = 3;//出现，标记为3
					iteTrace->lAutonum = TN;
					StClu.structTrace = *iteTrace;
					StClu.lAutonum = TN;
				//	TN++;
				}
			}
		}
		if (StClu.lAutonum)
		{
			for(iteEsm = AllMessage.stEsm.begin(); iteEsm != AllMessage.stEsm.end(); iteEsm++)//未处理信息
			{
				if (!iteEsm->cJfFlag)//未聚类
				{
					fA = fabs(fA - iteEsm->dReachAzimuth);
					if (fA < Acc.dirAcc*2)//聚为一类
					{
						iteEsm->cJfFlag = 1;
						iteEsm->lFlag = 3;//出现，标记为3
					//	iteEsm->lAutonum = StClu.lAutonum;
						StClu.vctEsm.push_back(*iteEsm);
					}
				}
			}
			for(iteComm = AllMessage.stComm.begin(); iteComm != AllMessage.stComm.end(); iteComm++)//未处理信息
			{
				if (!iteComm->cJfFlag)//未聚类
				{
					fA = fabs(fA - iteComm->dReachAzimuth);
					if (fA < Acc.dirAcc*2)//聚为一类
					{
						iteComm->cJfFlag = 1;
						iteComm->lFlag = 3;//出现，标记为3
				//		iteComm->lAutonum = StClu.lAutonum;
						StClu.vctComm.push_back(*iteComm);
					}
				}
			}
//			iteE->lAutonum = StClu.lAutonum;
			StClu.vctEsm.push_back(*iteE);
			StClu.structTrace.lAutonum = TN;
			for (iteE = StClu.vctEsm.begin(); iteE != StClu.vctEsm.end(); iteE++)
			{
				iteE->lAutonum = TN;
			}
			for (iteC = StClu.vctComm.begin(); iteC != StClu.vctComm.end(); iteC++)
			{
				iteC->lAutonum = TN;
			}
  			TN++;
			UniMsg.push_back(StClu);
		} 
		else
		{
			for(iteEsm = AllMessage.stEsm.begin(); iteEsm != AllMessage.stEsm.end(); iteEsm++)//未处理信息
			{
				if (!iteEsm->cJfFlag)//未聚类
				{
					fA = fabs(fA - iteEsm->dReachAzimuth);
					if (fA < Acc.dirAcc*2)//聚为一类
					{
						iteEsm->cJfFlag = 1;
						iteEsm->lFlag = 3;//出现，标记为3
						StCluNo.vctEsm.push_back(*iteEsm);
					}
				}
			}
			for(iteComm = AllMessage.stComm.begin(); iteComm != AllMessage.stComm.end(); iteComm++)//未处理信息
			{
				if (!iteComm->cJfFlag)//未聚类
				{
					fA = fabs(fA - iteComm->dReachAzimuth);
					if (fA < Acc.dirAcc*2)//聚为一类
					{
						iteComm->cJfFlag = 1;
						iteComm->lFlag = 3;//出现，标记为3
						StCluNo.vctComm.push_back(*iteComm);
					}
				}
			}
			if (StClu.vctComm.empty()&&StClu.vctEsm.empty())
			{
			} 
			else
			{
				StCluNo.vctEsm.push_back(*iteE);
				StCluNo.lAutonum = NN;
				for (iteE = StCluNo.vctEsm.begin(); iteE != StCluNo.vctEsm.end(); iteE++)
				{
					iteE->lAutonum = NN;
				}
				for (iteC = StCluNo.vctComm.begin(); iteC != StCluNo.vctComm.end(); iteC++)
				{
					iteC->lAutonum = NN;
				}
				NN ++;
				UniNoTrace.push_back(StCluNo);//存入无航迹聚类信息
			}
		}
	}
	//COMM信息
	for (iteC = SingleComm.begin(); iteC != SingleComm.end(); iteC++)
	{
		/*清空StClu*/
		StClu.lAutonum = NULL;
		for (iteE = StClu.vctEsm.begin(); iteE != StClu.vctEsm.end(); iteE++)
		{
			memset(&(*iteE), 0, sizeof(ESMSTATUS_MARK));
		}
		for (iteComm = StClu.vctComm.begin(); iteComm != StClu.vctComm.end(); iteComm++)
		{
			memset(&(*iteComm), 0, sizeof(COMSTATUS_MARK));
		}
		StClu.vctEsm.clear();
		StClu.vctComm.clear();
		/*清空StCluNo*/
		StCluNo.lAutonum = NULL;
		for (iteE = StCluNo.vctEsm.begin(); iteE != StCluNo.vctEsm.end(); iteE++)
		{
			memset(&(*iteE), 0, sizeof(ESMSTATUS_MARK));
		}
		for (iteComm = StCluNo.vctComm.begin(); iteComm != StCluNo.vctComm.end(); iteComm++)
		{
			memset(&(*iteComm), 0, sizeof(COMSTATUS_MARK));
		}
		StCluNo.vctEsm.clear();
		StCluNo.vctComm.clear();

		fA = iteC->dReachAzimuth;//取得方位角

		for (iteComm = AllMessage.stComm.begin(); iteComm != AllMessage.stComm.end(); iteComm++)//AllMessage.stEsm
		{
			if (!iteComm->cJfFlag)//未聚类
			{
				if (iteC->lTargetNumber == iteComm->lTargetNumber)//批号一样
				{
					iteComm->cJfFlag = 1;
					iteComm->lFlag = 3;//出现，标记为3
					iteComm->lAutonum = 0;
					*iteC = *iteComm;//更新
				}
			}			
		}
		for(iteTrace = AllMessage.stTrace.begin(); iteTrace != AllMessage.stTrace.end(); iteTrace++)//AllMessage.stTrace
		{
			if (!iteTrace->cJfFlag)//未聚类
			{
				fA = fabs(fA - iteTrace->dAzimuth);
				if (fA < Acc.dirAcc*2)//聚为一类
				{
					iteTrace->cJfFlag = 1;
					iteTrace->lFlag = 3;//出现，标记为3
					iteTrace->lAutonum = TN;
					StClu.structTrace = *iteTrace;
					StClu.lAutonum = TN;
					//TN++;
				}
			}
		}
		if (StClu.lAutonum)
		{
			for(iteEsm = AllMessage.stEsm.begin(); iteEsm != AllMessage.stEsm.end(); iteEsm++)//未处理信息
			{
				if (!iteEsm->cJfFlag)//未聚类
				{
					fA = fabs(fA - iteEsm->dReachAzimuth);
					if (fA < Acc.dirAcc*2)//聚为一类
					{
						iteEsm->cJfFlag = 1;
						iteEsm->lFlag = 3;//出现，标记为3
						StClu.vctEsm.push_back(*iteEsm);
					}
				}
			}
			for(iteComm = AllMessage.stComm.begin(); iteComm != AllMessage.stComm.end(); iteComm++)//未处理信息
			{
				if (!iteComm->cJfFlag)//未聚类
				{
					fA = fabs(fA - iteComm->dReachAzimuth);
					if (fA < Acc.dirAcc*2)//聚为一类
					{
						iteComm->cJfFlag = 1;
						iteComm->lFlag = 3;//出现，标记为3
						StClu.vctComm.push_back(*iteComm);
					}
				}
			}
			StClu.vctComm.push_back(*iteC);
			for (iteE = StClu.vctEsm.begin(); iteE != StClu.vctEsm.end(); iteE++)
			{
				iteE->lAutonum = TN;
			}
			for (iteC = StClu.vctComm.begin(); iteC != StClu.vctComm.end(); iteC++)
			{
				iteC->lAutonum = TN;
			}
			TN ++;
			UniMsg.push_back(StClu);
		} 
		else
		{
			for(iteEsm = AllMessage.stEsm.begin(); iteEsm != AllMessage.stEsm.end(); iteEsm++)//未处理信息
			{
				if (!iteEsm->cJfFlag)//未聚类
				{
					fA = fabs(fA - iteEsm->dReachAzimuth);
					if (fA < Acc.dirAcc*2)//聚为一类
					{
						iteEsm->cJfFlag = 1;
						iteEsm->lFlag = 3;//出现，标记为3
						StCluNo.vctEsm.push_back(*iteEsm);
					}
				}
			}
			for(iteComm = AllMessage.stComm.begin(); iteComm != AllMessage.stComm.end(); iteComm++)//未处理信息
			{
				if (!iteComm->cJfFlag)//未聚类
				{
					fA = fabs(fA - iteComm->dReachAzimuth);
					if (fA < Acc.dirAcc*2)//聚为一类
					{
						iteComm->cJfFlag = 1;
						iteComm->lFlag = 3;//出现，标记为3
						StCluNo.vctComm.push_back(*iteComm);
					}
				}
			}
			if (StClu.vctComm.empty()&&StClu.vctEsm.empty())
			{
			} 
			else
			{
				StCluNo.lAutonum = NN;
				for (iteC = StCluNo.vctComm.begin(); iteC != StCluNo.vctComm.end(); iteC++)
				{
					iteC->lAutonum = NN;
				}
				NN ++;
				StClu.vctComm.push_back(*iteC);
				UniNoTrace.push_back(StCluNo);//存入无航迹聚类信息
			}
		}
	}

	/*剩余未处理信息直接存入未聚类信息*/
	for (iteTrace = AllMessage.stTrace.begin(); iteTrace != AllMessage.stTrace.end(); iteTrace++)
	{		
		if (!iteTrace->cJfFlag)//未聚类
		{
			iteTrace->lFlag = 3;//出现，标记为3
			iteTrace->lAutonum = 0;
			SingleTrace.push_back(*iteTrace);
		}
	}
	for (iteEsm = AllMessage.stEsm.begin(); iteEsm != AllMessage.stEsm.end(); iteEsm++)
	{		
		if (!iteEsm->cJfFlag)//未聚类
		{
			iteEsm->lFlag = 3;//出现，标记为3
			iteEsm->lAutonum = 0;
			SingleEsm.push_back(*iteEsm);
		}
	}
	for (iteComm = AllMessage.stComm.begin(); iteComm != AllMessage.stComm.end(); iteComm++)
	{		
		if (!iteComm->cJfFlag)//未聚类
		{
			iteComm->lFlag = 3;//出现，标记为3
			iteComm->lAutonum = 0;
			SingleComm.push_back(*iteComm);
		}
	}
}


/**********************************************累计3次消失的，进行删除操作***********************************************/
void Delete(VCT_UNINUM_MSG& UniMsg, VCT_UNINOTRACE_MSG& UniNoTrace, VCT_TRACE_MSG& SingleTrace, VCT_ESM_MSG& SingleEsm, VCT_COMM_MSG& SingleComm)
{
	VCT_UNINUM_MSG::iterator itt;
	VCT_UNINOTRACE_MSG::iterator itnt;
	VCT_TRACE_MSG::iterator iteTrace;
	VCT_ESM_MSG::iterator iteEsm;
	VCT_COMM_MSG::iterator iteComm;
 	UNI_NOTRACE_NUM StCluNo;     // 临时变量 存无航迹信息结构
	
	/*有航迹聚类信息*/
	for (itt = UniMsg.begin(); itt != UniMsg.end(); itt++)
	{
		//删除esm和comm无用信息
		for (iteEsm = itt->vctEsm.begin(); iteEsm != itt->vctEsm.end(); iteEsm++)
		{
			if (iteEsm->lFlag == 0)
			{
				itt->vctEsm.erase(iteEsm);
				iteEsm--;
			}
		}
		for (iteComm = itt->vctComm.begin(); iteComm != itt->vctComm.end(); iteComm++)
		{
			if (iteComm->lFlag == 0)
			{
				itt->vctComm.erase(iteComm);
				iteComm--;
			}
		}
		//删除trace无用信息，同时移除此批号相关所有信息
		if (itt->structTrace.lFlag == 0)
		{
			//移至无航迹聚类信息
			if (itt->vctEsm.size() + itt->vctComm.size() >= 2)
			{
				for (iteEsm = itt->vctEsm.begin(); iteEsm != itt->vctEsm.end(); iteEsm++)
				{
					StCluNo.vctEsm.push_back(*iteEsm);
				}
				for (iteComm = itt->vctComm.begin(); iteComm != itt->vctComm.end(); iteComm++)
				{
					StCluNo.vctComm.push_back(*iteComm);
				}
				StCluNo.lAutonum = NN;
				NN++;
				UniNoTrace.push_back(StCluNo);
			}
			//移至未聚类信息
			else 
			{
				if (itt->vctEsm.empty())
				{
					SingleComm.push_back(*(itt->vctComm.begin()));
				}
				else
				{
					SingleEsm.push_back(*(itt->vctEsm.begin()));
				}				
			}			
			//删除有航迹聚类信息里此批号所有信息
			UniMsg.erase(itt);
			itt--;
		}
		else
		{
			if (itt->vctEsm.empty()&&itt->vctComm.empty())
			{
				//航迹移至未聚类信息
				SingleTrace.push_back(itt->structTrace);
				//删除有航迹聚类信息里此批号所有信息
				UniMsg.erase(itt);
				itt--;
			}
		}
	}
	
	/*无航迹聚类信息*/
	for (itnt = UniNoTrace.begin(); itnt != UniNoTrace.end(); itnt++)
	{
		//删除esm和comm无用信息
		for (iteEsm = itnt->vctEsm.begin(); iteEsm != itnt->vctEsm.end(); iteEsm++)
		{
			if (iteEsm->lFlag == 0)
			{
				itnt->vctEsm.erase(iteEsm);
				iteEsm--;
			}
		}
		for (iteComm = itnt->vctComm.begin(); iteComm != itnt->vctComm.end(); iteComm++)
		{
			if (iteComm->lFlag == 0)
			{
				itnt->vctComm.erase(iteComm);
				iteComm--;
			}
		}
		//移至移至未聚类信息
		if (itnt->vctEsm.size() + itnt->vctComm.size() < 2)
		{
			if (!itnt->vctComm.empty())
			{
				SingleComm.push_back(*(itnt->vctComm.begin()));
			}
			else if (!itnt->vctEsm.empty())
			{
				SingleEsm.push_back(*(itnt->vctEsm.begin()));
			}
			//删除无航迹聚类信息里此批号所有信息
			UniNoTrace.erase(itnt);
			itnt--;
		}			
	}

	/*未聚类信息*/
	for (iteTrace = SingleTrace.begin(); iteTrace != SingleTrace.end(); iteTrace++)
	{
		if (iteTrace->lFlag == 0)
		{
			SingleTrace.erase(iteTrace);
			iteTrace--;
		}
	}
	for (iteEsm = SingleEsm.begin(); iteEsm != SingleEsm.end(); iteEsm++)
	{
		if (iteEsm->lFlag == 0)
		{
			SingleEsm.erase(iteEsm);
			iteEsm--;
		}
	}
	for (iteComm = SingleComm.begin(); iteComm != SingleComm.end(); iteComm++)
	{
		if (iteComm->lFlag == 0)
		{
			SingleComm.erase(iteComm);
			iteComm--;
		}
	}
		
}

 
/***************************************************举手表决**************************************************************/
// 输入同一综合批号的esm、com、track信息（只含目标类型及其综合可信度），得到对应最高综合可信度的目标类型存入识别结果vev中
void ShowOfHands(TYPEVEC& Type, VCT_IDENTIINFOR_MSG& IdentifyVec)
{
    TYPEVEC Vcst; //存储不同目标类型及其综合可信度
	
	vector<int>  typenum;     //目标类型识别数
	vector<double>  typecon;  //综合可信度

	/*迭代器*/
	TYPEVEC::iterator it = Type.begin();
	/*将Type中第一条信息放入vcst*/
	Vcst.clear();
	Vcst.push_back(*it);
	/*综合可信度*/
	typecon.clear();
	typecon.push_back(1 - it->con);
	/*识别数*/
	typenum.clear();
	typenum.push_back(1);
	/*举手表决*/
	for (it++; it != Type.end(); it++)
	{
		int nflag = 0;
		int len = Vcst.size();
        for (int i = 0;i < len;i ++)//遍历Vcst
		{
			if (Vcst[i].sType == it->sType)
//			if (strcmp(Vcst[i]->type,(*it)->type) == 0)//目标类型一致
			{
				typenum[i] = typenum[i] + 1;//识别数+1
				typecon[i] = typecon[i] * (1 - it->con);//计算可信度
				//break;
			}
			else
			{
				nflag++;
			}
		}		
		if (nflag == len)//出现新的目标类型
		{
			STTYPE tmp;
			tmp.lAutonum = it->lAutonum;
			//tmp.sType = it->sType;
			strcpy(tmp.sType,it->sType);
			tmp.con = it->con;
			Vcst.push_back(tmp);//将新的目标类型信息存入Vcst
            typenum.push_back(1);//新的目标类型识别数为1
			typecon.push_back(1 - it->con);//新的目标类型可信度
		}
		
	}
	int nLen = Vcst.size();
	for (int k = 0; k < nLen; k++)//综合可信度
	{
		typecon[k] = 1 - typecon[k];
	}
	/*依据最大综合可信度求出初步识别目标类型依据最大综合可信度*/
  	int num = typenum[0];//最多统计数
  	double c = typecon[0];//最大综合可信度c
	int max = 0;//初步识别目标类型Vcst[max]->type
	for (k = 1; k < nLen; k++)
	{
		if (typenum[k] > num)
		{
			num = typenum[k];
			c = typecon[k];
			max = k;
		}
		else if (typenum[k] == num)
		{
			if (typecon[k] > c)
			{
				c = typecon[k];
				max = k;
			}
		}
	}

// 	
// 	printf("综合批号   目标类型     综合可信度\n");
// 	printf("%d\t   %d\t        %f\n", Vcst[max]->lAutonum, Vcst[max]->sType, c);

	/*将识别结果存入Identify*/
 	IDENTIINFOR IdentStr;
	IdentStr.lAutonum = Vcst[max].lAutonum;//综合批号
	strcpy(IdentStr.sPlatType,Vcst[max].sType);
	//IdentStr.sPlatType = Vcst[max].sType;//目标类型
	IdentStr.dConfidence = c;//综合可信度
	IdentifyVec.push_back(IdentStr);

	
	//清空
	Vcst.clear();
	typecon.clear();
	typenum.clear();
}


void SingleIdentify(ALL_MSG_INPUT& AllMessage, VCT_UNINUM_MSG& UniMsg, VCT_UNINOTRACE_MSG& UniNoTrace, VCT_IDENTIINFOR_MSG& IdentifyVec, VCT_TRACE_MSG& SingleTrace, VCT_ESM_MSG& SingleEsm, VCT_COMM_MSG& SingleComm)
{
	VCT_UNINUM_MSG::iterator itt;
	VCT_UNINOTRACE_MSG::iterator itnt;
	VCT_TRACE_MSG::iterator iteTrace;
	VCT_ESM_MSG::iterator iteEsm;
	VCT_COMM_MSG::iterator iteComm;

// 	double Lt;
// 	double Bt;
// 	double Ht;


	if (UniMsg.empty()&&UniNoTrace.empty())
	{
		FirstClusterUni(AllMessage, UniMsg, UniNoTrace, SingleTrace, SingleEsm, SingleComm);//第一次信息处理
	} 
	else
	{
		//结果存储累加标记减一，同时trace递推
		for (itt = UniMsg.begin(); itt != UniMsg.end(); itt++)
		{
			itt->structTrace.lFlag--;
// 			//trace递推
// 			Lt = itt->structTrace.dLonti;
// 			Bt = itt->structTrace.dLati;
// 			Ht = itt->structTrace.dHight;
// 			NextTrace(Lt, Bt, Ht, itt->structTrace.dTSpeedX, itt->structTrace.dTSpeedY, itt->structTrace.dTSpeedZ, &(itt->structTrace.dLonti), &(itt->structTrace.dLati), &(itt->structTrace.dHight));

			for (iteEsm = itt->vctEsm.begin(); iteEsm != itt->vctEsm.end(); iteEsm++)
			{
				iteEsm->lFlag--;
			}
			for (iteComm = itt->vctComm.begin(); iteComm != itt->vctComm.end(); iteComm++)
			{
				iteComm->lFlag--;
			}
		}
		for (itnt = UniNoTrace.begin(); itnt != UniNoTrace.end(); itnt++)
		{
			for (iteEsm = itnt->vctEsm.begin(); iteEsm != itnt->vctEsm.end(); iteEsm++)
			{
				iteEsm->lFlag--;
			}
			for (iteComm = itnt->vctComm.begin(); iteComm != itnt->vctComm.end(); iteComm++)
			{
				iteComm->lFlag--;
			}
		}
		for (iteTrace = SingleTrace.begin(); iteTrace != SingleTrace.end(); iteTrace++)
		{
			iteTrace->lFlag--;
// 			//trace递推
// 			Lt = iteTrace->dLonti;
// 			Bt = iteTrace->dLati;
// 			Ht = iteTrace->dHight;
// 			NextTrace(Lt, Bt, Ht, iteTrace->dTSpeedX, iteTrace->dTSpeedY, iteTrace->dTSpeedZ, &(iteTrace->dLonti), &(iteTrace->dLati), &(iteTrace->dHight));

		}
		for (iteEsm = SingleEsm.begin(); iteEsm != SingleEsm.end(); iteEsm++)
		{
			iteEsm->lFlag--;
		}
		for (iteComm = SingleComm.begin(); iteComm != SingleComm.end(); iteComm++)
		{
			iteComm->lFlag--;
		}

		//非第一次信息处理
		ClusterUni(AllMessage, UniMsg, UniNoTrace, SingleTrace, SingleEsm, SingleComm);
		//累计3次消失的，进行删除操作
		Delete(UniMsg, UniNoTrace, SingleTrace, SingleEsm, SingleComm);
	}
		
 	IdentifyVec.clear();//清空之前识别结果

	STTYPE StType;
	TYPEVEC Type;

	for (itt = UniMsg.begin(); itt != UniMsg.end(); itt++)//遍历聚类合批结果
	{
		int nLenEsm = itt->vctEsm.size();
		int nLenCom = itt->vctComm.size();
		Type.clear();

		for (int i = 0; i < nLenEsm; i++)//同一批号的esm信息如type结构存入Type
		{
			StType.lAutonum = itt->lAutonum;
			StType.con = itt->vctEsm[i].dConfidence;
			//StType.sType = itt->vctEsm[i].sPlatType;
			strcpy(StType.sType, itt->vctEsm[i].sPlatType);
			Type.push_back(StType);				
		}
		for (i = 0; i < nLenCom; i++)//同一批号的comm信息如type结构存入Type
		{
			StType.lAutonum = itt->lAutonum;
			StType.con = itt->vctComm[i].dConfidence;
			//StType.sType = itt->vctComm[i].sPlatType;
			strcpy(StType.sType,itt->vctComm[i].sPlatType);
			Type.push_back(StType);				
		}
		//同一批号的Trace信息如type结构存入Type
		StType.lAutonum = itt->lAutonum;
		StType.con = itt->structTrace.dConfidence;
		//StType.sType = itt->structTrace.sPlatType;
		strcpy(StType.sType,itt->structTrace.sPlatType);
		Type.push_back(StType);

		ShowOfHands(Type, IdentifyVec);//调用举手表决函数

// 		for (j = 0; j < nLenEsm; j++)//清空EsmType
// 		{
// 			memset(&EsmType, 0, sizeof(TYPEVEC));
// 		}
// 		EsmType.clear();
// 		for (j = 0; j < nLenCom; j++)//清空ComType
// 		{
// 			memset(&ComType, 0, sizeof(TYPEVEC));
// 		}
// 		ComType.clear();
	}

//	return (&IdentifyVec);
}
