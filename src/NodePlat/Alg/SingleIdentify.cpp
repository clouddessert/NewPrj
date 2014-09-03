#include "SingleIdentify.h"

#include <vector>
#include <string>
#include <iostream>
#include <math.h>

using namespace std;

#define DTN 8000
#define NTN 7000
#define PI 3.1415926535898

typedef struct __STTYPE //���ֱ��Ҫ�õ����ݽṹ
{
	unsigned long lAutonum;   //�ۺ�����
	//	char *type;    //Ŀ������
	//unsigned short sType;     
	char sType[32]; //ƽ̨����
	double con;               //���Ŷ�	
}STTYPE;
typedef vector<STTYPE> TYPEVEC;

static int TN = DTN;        //�к�������
static int NN = NTN;        //�޺�������
static Accuracy Acc;

/***********************************************************/
/**  ��Ŀ���۲�վ�ľ�γ�Ⱥ͸߳�����任Ϊ��������ģ��   **/
/*******    ���룺Ŀ���۲�վ�ĵ���λ��Lt,Bt,Ht       *****/
/*******    �����Xt,Yt,Zt                         *********/
/***********************************************************/
void Target_Position_Transform(double Lt, double Bt, double Ht, double *Xt, double *Yt, double *Zt)
{ 
	double Nt;
	double e2,a;
	
	a=6378137.0;        //���򳤰���
	
	e2=0.0066943799014;
	
    Nt=a/sqrt(1.0-e2*sin(Bt)*sin(Bt));        //�������ʰ뾶
	
    *Xt=(Nt+Ht)*cos(Bt)*cos(Lt);
    *Yt=(Nt+Ht)*cos(Bt)*sin(Lt);
    *Zt=(Nt*(1-e2)+Ht)*sin(Bt);
 }

/*******************************************************************************/
/*******      ��Ŀ�������WGS-84����ϵת�ɾ�γ�Ⱥ͸߳�ģ��               *******/
/*******                          (����Ҫ����ģ��)                       *******/
//*******     ���룺Ŀ������(WGS-84����)                                 *******/
//*******     �����Ŀ�꾭��(Lt)��γ��(Bt)�͸߳�(Ht)                     *******/
/*******************************************************************************/
void GET_Satellite_Trans(double xt,double yt,double zt,double *Lt,double *Bt,double *Ht)
{
	double a,b;                //���򳤰���(m),�̰���
    double e2;                 //������
    double N0,H0,B0;
	double N1,H1,B1;
	
    a=6378130.0;                //���򳤰���(m)
	
	e2=0.0066943799014;
    b=a*(1.0-1.0/298.257223563);	
	
	//�������м����ڵ�γ��
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
		*Lt=atan(yt/xt);    //��ؾ���
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
	
	*Bt=B1;             //���γ��
	*Ht=sqrt(xt*xt+yt*yt)/cos(B1)-N1;             //�߳�
}
/*�������ƺ���*/
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
/***            Ŀ�����״�����ϵ��λ�ü���ģ��(����Ҫ����ģ��)   ***/
/**                     ���԰�  2011-2-10                        ***/
/********      ���룺Ŀ��ƽ̨λ�ã�Lt,Bt,Ht��                *******/
/********            �״�ƽ̨λ�ã�L0,B0,H0��                *******/
/********      �����Ŀ�����״��ز�������ϵ�еľ��ࡢ��λ������ **/
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
/**********************************************��һ����Ϣ����******************************************/
void FirstClusterUni(ALL_MSG_INPUT& AllMessage, VCT_UNINUM_MSG& UniMsg, VCT_UNINOTRACE_MSG& UniNoTrace, VCT_TRACE_MSG& SingleTrace, VCT_ESM_MSG& SingleEsm, VCT_COMM_MSG& SingleComm)
{
	Acc.dirAcc = 1.0;           // ���򾫶�
	
	float fTraceAz(0.0);		// �з�������λ��
	float fReachA(0.0);         // �з����﷽λ��
	float fA(0.0);              // �з���λ�ǲ�
 	UNI_NUM StClu;              //��ʱ�洢�к���ͬ��λ������Ϣ
	UNI_NOTRACE_NUM StCluNo;    //��ʱ�洢�޺���ͬ��λ������Ϣ
	
	/*���������ĵ�����*/	
	VCT_TRACE_MSG::iterator iteTrace;
	VCT_ESM_MSG::iterator iteEsm;
	VCT_ESM_MSG::iterator iteE;
	VCT_COMM_MSG::iterator iteComm;
	VCT_COMM_MSG::iterator iteC;
	
	/*�к�����Ϣ*/
	for (iteTrace = AllMessage.stTrace.begin(); iteTrace != AllMessage.stTrace.end(); iteTrace++)
	{
		/*���StClu*/
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
		
		
		/***��λ����***/		
		fTraceAz = iteTrace->dAzimuth;	// �����ṩ�ķ�λ��
// 		StClu.lAutonum = TN;
// 		TN ++;
		
		iteTrace->cJfFlag = '1';
		iteTrace->lFlag = 3;//�ۼӱ�־����ʧһ��lFlag--,3�β�������Ϊ0
		StClu.structTrace = *iteTrace;
		
		/*��δ�����ESM��Ϣ���д���*/
		for (iteEsm = AllMessage.stEsm.begin(); iteEsm != AllMessage.stEsm.end(); iteEsm++)
		{
			if (iteEsm->cJfFlag == 0)
			{
				fReachA = iteEsm->dReachAzimuth; // ESM�ṩ�ķ�λ��
				fA = fabs(fReachA - fTraceAz);				
				/*��Ϊһ��*/
				if ((fA < Acc.dirAcc*2))
				{
					iteEsm->cJfFlag = '1';//�����־
					iteEsm->lFlag = 3;//�ۼӱ�־����ʧһ��lFlag--,3�β�������Ϊ0
					iteEsm->lAutonum = TN;//����
					StClu.vctEsm.push_back(*iteEsm);//�洢ESM��Ϣ
				}
			}
		}
		
		/*��δ�����COMM��Ϣ���д���*/
		for (iteComm = AllMessage.stComm.begin(); iteComm != AllMessage.stComm.end(); iteComm++)
		{
			if (iteComm->cJfFlag == 0)
			{
				fReachA = iteComm->dReachAzimuth; // COM�ṩ�ķ�λ��
				fA = fabs(fReachA - fTraceAz);
				/*��Ϊһ��*/
				if ((fA < Acc.dirAcc*2)/* && (detElevation < stComAcc.dirAcc*2)*/)
				{
					iteComm->cJfFlag = '1';//�����־
					iteComm->lFlag = 3;//�ۼӱ�־����ʧһ��lFlag--,3�β�������Ϊ0
					iteComm->lAutonum = TN;//����
					StClu.vctComm.push_back(*iteComm);//�洢COMM��Ϣ
				} 
			}
		}
		/*������StClu�洢*/
		if (StClu.vctComm.empty()&&StClu.vctEsm.empty())//ֻ�к�����Ϣ
		{
			iteTrace->lAutonum = 0;
			SingleTrace.push_back(*iteTrace);//����δ����ĵ�һ�����д洢
		} 
		else
		{
			StClu.lAutonum = TN;//����
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
			UniMsg.push_back(StClu);//�����к���������Ϣ
		}
		
	}

	/*�޺�����Ϣ*/
	for (iteEsm = AllMessage.stEsm.begin(); iteEsm != AllMessage.stEsm.end(); iteEsm++)//��δ�����ESM��Ϣ���д���
	{		
		if (iteEsm->cJfFlag == 0)
		{
			/*���StCluNo*/
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

			fReachA = iteEsm->dReachAzimuth; // ESM�ṩ�ķ�λ��
// 			StCluNo.lAutonum = NN;
// 			NN++;
			iteEsm->cJfFlag = '1';//�����־
			iteEsm->lFlag = 3;//�ۼӱ�־����ʧһ��lFlag--,3�β�������Ϊ0
			/*��δ�����ESM��Ϣ���д���*/
			iteE = iteEsm;
			for (iteE ++; iteE != AllMessage.stEsm.end(); iteE ++)
			{
				if (iteE->cJfFlag == 0)
				{
					fA = fabs(fReachA - iteE->dReachAzimuth);				
					/*��Ϊһ��*/
					if ((fA < Acc.dirAcc*2))
					{
						iteE->cJfFlag = '1';//�����־
						iteE->lFlag = 3;//�ۼӱ�־����ʧһ��lFlag--,3�β�������Ϊ0
						iteE->lAutonum = NN;//����
						StCluNo.vctEsm.push_back(*iteE);//�洢ESM��Ϣ
					}
				}
			}
			
			/*��δ�����COMM��Ϣ���д���*/
			for (iteComm = AllMessage.stComm.begin(); iteComm != AllMessage.stComm.end(); iteComm++)
			{
				if (iteComm->cJfFlag == 0)
				{
					fA = fabs(fReachA - iteComm->dReachAzimuth);
					/*��Ϊһ��*/
					if ((fA < Acc.dirAcc*2)/* && (detElevation < stComAcc.dirAcc*2)*/)
					{
						iteComm->cJfFlag = '1';//�����־
						iteComm->lFlag = 3;//�ۼӱ�־����ʧһ��lFlag--,3�β�������Ϊ0
						iteComm->lAutonum = NN;//����
						StCluNo.vctComm.push_back(*iteComm);//�洢COMM��Ϣ
					} 
				}
			}
			/*������StCluNo�洢*/
			if (StCluNo.vctComm.empty()&&(StCluNo.vctEsm.size()<2))//ֻ��ESM��Ϣ
			{
				iteEsm->lAutonum = 0;
				SingleEsm.push_back(*iteEsm);//����δ����ĵ�һESM�д洢
			} 
			else
			{
				StCluNo.lAutonum = NN;//����
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
				UniNoTrace.push_back(StCluNo);//�����޺���������Ϣ
			}	
		}
	}


	for (iteComm = AllMessage.stComm.begin(); iteComm != AllMessage.stComm.end(); iteComm++)//��δ�����COMM��Ϣ���д���
	{
		if (iteComm->cJfFlag == 0)
		{
			/*���StCluNo*/
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
			
			fReachA = iteComm->dReachAzimuth; // ESM�ṩ�ķ�λ��
// 			StCluNo.lAutonum = NN;
// 			NN++;
			iteComm->cJfFlag = '1';//�����־
			iteComm->lFlag = 3;//�ۼӱ�־����ʧһ��lFlag--,3�β�������Ϊ0
			/*��δ�����COMM��Ϣ���д���*/
			iteC = iteComm;
			for (iteC++; iteC != AllMessage.stComm.end(); iteC++)
			{
				if (iteC->cJfFlag == 0)
				{
					fA = fabs(fReachA - iteC->dReachAzimuth);
					/*��Ϊһ��*/
					if ((fA < Acc.dirAcc*2)/* && (detElevation < stComAcc.dirAcc*2)*/)
					{
						iteC->cJfFlag = '1';//�����־
						iteC->lFlag = 3;//�ۼӱ�־����ʧһ��lFlag--,3�β�������Ϊ0
						iteC->lAutonum = NN;//����
						StCluNo.vctComm.push_back(*iteC);//�洢COMM��Ϣ
					} 
				}
			}
			/*������StCluNo�洢*/
			if (StCluNo.vctComm.size()<2)//ֻ��COMM��Ϣ
			{
				iteComm->lAutonum = 0;
				SingleComm.push_back(*iteComm);//����δ����ĵ�һCOMM�д洢
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
				UniNoTrace.push_back(StCluNo);//�����޺���������Ϣ
			}
		}
	}
}


/**********************************************֮����Ϣ����******************************************/
void ClusterUni(ALL_MSG_INPUT& AllMessage, VCT_UNINUM_MSG& UniMsg, VCT_UNINOTRACE_MSG& UniNoTrace, VCT_TRACE_MSG& SingleTrace, VCT_ESM_MSG& SingleEsm, VCT_COMM_MSG& SingleComm)
{
	Acc.dirAcc = 1.0;           // ���򾫶�
	float fA(0.0);              // �з���λ�ǲ�
 	UNI_NUM StClu;               // ��ʱ���� ���к�����Ϣ�ṹ
 	UNI_NOTRACE_NUM StCluNo;     // ��ʱ���� ���޺�����Ϣ�ṹ
	
	/*���������ĵ�����*/
	VCT_UNINUM_MSG::iterator iteUni;
	VCT_UNINOTRACE_MSG::iterator iteNoTrace;
	VCT_TRACE_MSG::iterator iteTrace;
	VCT_TRACE_MSG::iterator iteT;
	VCT_ESM_MSG::iterator iteEsm;
 	VCT_ESM_MSG::iterator iteE;
	VCT_COMM_MSG::iterator iteComm;
 	VCT_COMM_MSG::iterator iteC;
	
	/*�к���������Ϣ*/
	/*1.�Ƿ��к�����Ϣ����  2.����������Ϣ*/
	for (iteUni = UniMsg.begin(); iteUni!= UniMsg.end(); iteUni++)
	{
		//�к�����Ϣ���£����º�����Ϣ
		for (iteTrace = AllMessage.stTrace.begin(); iteTrace != AllMessage.stTrace.end(); iteTrace++)
		{
			if (iteUni->structTrace.lTargetNumber ==iteTrace->lTargetNumber)//������һ����trace����
			{
				iteTrace->cJfFlag = 1;
				iteTrace->lFlag = 3;//���֣����Ϊ3
				iteTrace->lAutonum = iteUni->lAutonum;
				iteUni->structTrace = (*iteTrace);//����				
			} 
		}
		//����������Ϣ
		/*����ESM��Ϣ*/
		for (iteE = iteUni->vctEsm.begin(); iteE != iteUni->vctEsm.end(); iteE++)//������һ����esm����
		{
			for (iteEsm = AllMessage.stEsm.begin(); iteEsm != AllMessage.stEsm.end(); iteEsm++)
			{
				if (iteE->lTargetNumber == iteEsm->lTargetNumber)//����һ��
				{
					iteEsm->cJfFlag = 1;
					iteEsm->lFlag = 3;//���֣����Ϊ3
					iteEsm->lAutonum = iteUni->lAutonum;
					*iteE = *iteEsm;//����					
				}
			}
		}
		for (iteEsm = AllMessage.stEsm.begin(); iteEsm != AllMessage.stEsm.end(); iteEsm++)//�з�λһ����esm���
		{
			if (!iteEsm->cJfFlag)//δ����
			{
				fA = fabs(iteUni->structTrace.dAzimuth - iteEsm->dReachAzimuth);
				if (fA < Acc.dirAcc*2)//��Ϊһ��
				{
					iteEsm->cJfFlag = 1;
					iteEsm->lFlag = 3;//���֣����Ϊ3
					iteEsm->lAutonum = iteUni->lAutonum;//����
					iteUni->vctEsm.push_back(*iteEsm);//���					
				}
			}
		}
		/*����COMM��Ϣ*/
		for (iteC = iteUni->vctComm.begin(); iteC != iteUni->vctComm.end(); iteC++)//������һ����Comm����
		{
			for (iteComm = AllMessage.stComm.begin(); iteComm != AllMessage.stComm.end(); iteComm++)
			{
				if (iteC->lTargetNumber == iteComm->lTargetNumber)//����һ��
				{
					iteComm->cJfFlag = 1;
					iteComm->lFlag = 3;//���֣����Ϊ3
					iteComm->lAutonum = iteUni->lAutonum;
					*iteC = *iteComm;//����
				}
			}
		}
		for (iteComm = AllMessage.stComm.begin(); iteComm != AllMessage.stComm.end(); iteComm++)//�з�λһ����Comm���
		{
			if (!iteComm->cJfFlag)//δ����
			{
				fA = fabs(iteUni->structTrace.dAzimuth - iteComm->dReachAzimuth);
				if (fA < Acc.dirAcc*2)//��Ϊһ��
				{
					iteComm->cJfFlag = 1;
					iteComm->lFlag = 3;//���֣����Ϊ3
					iteComm->lAutonum = iteUni->lAutonum;//����
					iteUni->vctComm.push_back(*iteComm);//���
				}
			}
		}
	}

	/*�޺���������Ϣ*/
	for (iteNoTrace = UniNoTrace.begin(); iteNoTrace != UniNoTrace.end(); iteNoTrace++)
	{
		//ȡ�÷�λ��
		if (!iteNoTrace->vctEsm.empty())
		{
			iteE = iteNoTrace->vctEsm.begin();
			fA = iteE->dReachAzimuth;//ȡ��λ
		}
		else
		{
			iteC = iteNoTrace->vctComm.begin();
			fA = iteC->dReachAzimuth;//ȡ��λ
		}
		/*����ESM��Ϣ*/
		for (iteE = iteNoTrace->vctEsm.begin(); iteE != iteNoTrace->vctEsm.end(); iteE++)//������һ����esm����
		{
			for (iteEsm = AllMessage.stEsm.begin(); iteEsm != AllMessage.stEsm.end(); iteEsm++)
			{
				if (iteE->lTargetNumber == iteEsm->lTargetNumber)//����һ��
				{
					iteEsm->cJfFlag = 1;
					iteEsm->lFlag = 3;//���֣����Ϊ3
					iteEsm->lAutonum = iteNoTrace->lAutonum;
					*iteE = *iteEsm;//����					
				}
			}
		}
		for (iteEsm = AllMessage.stEsm.begin(); iteEsm != AllMessage.stEsm.end(); iteEsm++)//�з�λһ����esm���
		{
			if (!iteEsm->cJfFlag)//δ����
			{
				fA = fabs(fA - iteEsm->dReachAzimuth);
				if (fA < Acc.dirAcc*2)//��Ϊһ��
				{
					iteEsm->cJfFlag = 1;
					iteEsm->lFlag = 3;//���֣����Ϊ3
					iteEsm->lAutonum = iteNoTrace->lAutonum;//����
					iteNoTrace->vctEsm.push_back(*iteEsm);//���					
				}
			}
		}
		
		/*����COMM��Ϣ*/
		for (iteC = iteUni->vctComm.begin(); iteC != iteUni->vctComm.end(); iteC++)//������һ����Comm����
		{
			for (iteComm = AllMessage.stComm.begin(); iteComm != AllMessage.stComm.end(); iteComm++)
			{
				if (iteC->lTargetNumber == iteComm->lTargetNumber)//����һ��
				{
					iteComm->cJfFlag = 1;
					iteComm->lFlag = 3;//���֣����Ϊ3
					iteComm->lAutonum = iteNoTrace->lAutonum;
					*iteC = *iteComm;//����
				}
			}
		}
		for (iteComm = AllMessage.stComm.begin(); iteComm != AllMessage.stComm.end(); iteComm++)//�з�λһ����Comm���
		{
			if (!iteComm->cJfFlag)//δ����
			{
				fA = fabs(fA - iteComm->dReachAzimuth);
				if (fA < Acc.dirAcc*2)//��Ϊһ��
				{
					iteComm->cJfFlag = 1;
					iteComm->lFlag = 3;//���֣����Ϊ3
					iteComm->lAutonum = iteNoTrace->lAutonum;//����
					iteUni->vctComm.push_back(*iteComm);//���
				}
			}
		}

		/*����trace��Ϣ:�пɾ���ĺ�����Ϣ������࣬���������ŵ���Ϣ�����к�����Ϣ��*/
		for (iteTrace = AllMessage.stTrace.begin(); iteTrace != AllMessage.stTrace.end(); iteTrace++)//�з�λһ����Comm���
		{
			if (!iteTrace->cJfFlag)//δ����
			{
				fA = fabs(fA - iteTrace->dAzimuth);
				if (fA < Acc.dirAcc*2)//��Ϊһ�࣬�����к�����Ϣ
				{
					/*���StClu*/
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
					iteTrace->lFlag = 3;//���֣����Ϊ3
					StClu.structTrace = *iteTrace;//structTrace				
					for (iteE = iteNoTrace->vctEsm.begin(); iteE != iteNoTrace->vctEsm.end(); iteE++)//vctEsm
					{
						StClu.vctEsm.push_back(*iteE);
					}
					for (iteC = iteNoTrace->vctComm.begin(); iteC != iteNoTrace->vctComm.end(); iteC++)//vctComm
					{
						StClu.vctComm.push_back(*iteC);
					}
					StClu.lAutonum = TN;//����
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

	/*δ������Ϣ*/
	//������Ϣ
	for(iteT = SingleTrace.begin(); iteT != SingleTrace.end(); iteT++)
	{
		/*���StClu*/
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
		for(iteTrace = AllMessage.stTrace.begin(); iteTrace != AllMessage.stTrace.end(); iteTrace++)//δ������Ϣ
		{
			if (!iteTrace->cJfFlag)//δ����
			{
				if(iteT->lTargetNumber == iteTrace->lTargetNumber)
				{
					iteTrace->cJfFlag = 1;
					iteTrace->lFlag = 3;//���֣����Ϊ3
					iteTrace->lAutonum = 0;
					*iteT = *iteTrace;//����
				}
			}
		}
		for(iteEsm = AllMessage.stEsm.begin(); iteEsm != AllMessage.stEsm.end(); iteEsm++)//δ������Ϣ
		{
			if (!iteEsm->cJfFlag)//δ����
			{
				fA = fabs(fA - iteEsm->dReachAzimuth);
				if (fA < Acc.dirAcc*2)//��Ϊһ��
				{
					iteEsm->cJfFlag = 1;
					iteEsm->lFlag = 3;//���֣����Ϊ3
					StClu.vctEsm.push_back(*iteEsm);
				}
			}
		}
		for(iteComm = AllMessage.stComm.begin(); iteComm != AllMessage.stComm.end(); iteComm++)//δ������Ϣ
		{
			if (!iteComm->cJfFlag)//δ����
			{
				fA = fabs(fA - iteComm->dReachAzimuth);
				if (fA < Acc.dirAcc*2)//��Ϊһ��
				{
					iteComm->cJfFlag = 1;
					iteComm->lFlag = 3;//���֣����Ϊ3
					StClu.vctComm.push_back(*iteComm);
				}
			}
		}
		if (StClu.vctComm.empty()&&StClu.vctEsm.empty())//ֻ�к�����Ϣ
		{
			iteT->lAutonum = 0;
		} 
		else
		{
			StClu.structTrace = *iteT;
			StClu.lAutonum = TN;//����
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
			UniMsg.push_back(StClu);//�����к���������Ϣ
		}
	}
	//ESM��Ϣ
	for (iteE = SingleEsm.begin(); iteE != SingleEsm.end(); iteE++)
	{
		/*���StClu*/
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
		/*���StCluNo*/
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
			if (!iteEsm->cJfFlag)//δ����
			{
				if (iteE->lTargetNumber == iteEsm->lTargetNumber)//����һ��
				{
					iteEsm->cJfFlag = 1;
					iteEsm->lFlag = 3;//���֣����Ϊ3
					iteEsm->lAutonum = 0;
					*iteE = *iteEsm;//����
				}
			}			
		}
		for(iteTrace = AllMessage.stTrace.begin(); iteTrace != AllMessage.stTrace.end(); iteTrace++)//AllMessage.stTrace
		{
			if (!iteTrace->cJfFlag)//δ����
			{
				fA = fabs(fA - iteTrace->dAzimuth);
				if (fA < Acc.dirAcc*2)//��Ϊһ��
				{
					iteTrace->cJfFlag = 1;
					iteTrace->lFlag = 3;//���֣����Ϊ3
					iteTrace->lAutonum = TN;
					StClu.structTrace = *iteTrace;
					StClu.lAutonum = TN;
				//	TN++;
				}
			}
		}
		if (StClu.lAutonum)
		{
			for(iteEsm = AllMessage.stEsm.begin(); iteEsm != AllMessage.stEsm.end(); iteEsm++)//δ������Ϣ
			{
				if (!iteEsm->cJfFlag)//δ����
				{
					fA = fabs(fA - iteEsm->dReachAzimuth);
					if (fA < Acc.dirAcc*2)//��Ϊһ��
					{
						iteEsm->cJfFlag = 1;
						iteEsm->lFlag = 3;//���֣����Ϊ3
					//	iteEsm->lAutonum = StClu.lAutonum;
						StClu.vctEsm.push_back(*iteEsm);
					}
				}
			}
			for(iteComm = AllMessage.stComm.begin(); iteComm != AllMessage.stComm.end(); iteComm++)//δ������Ϣ
			{
				if (!iteComm->cJfFlag)//δ����
				{
					fA = fabs(fA - iteComm->dReachAzimuth);
					if (fA < Acc.dirAcc*2)//��Ϊһ��
					{
						iteComm->cJfFlag = 1;
						iteComm->lFlag = 3;//���֣����Ϊ3
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
			for(iteEsm = AllMessage.stEsm.begin(); iteEsm != AllMessage.stEsm.end(); iteEsm++)//δ������Ϣ
			{
				if (!iteEsm->cJfFlag)//δ����
				{
					fA = fabs(fA - iteEsm->dReachAzimuth);
					if (fA < Acc.dirAcc*2)//��Ϊһ��
					{
						iteEsm->cJfFlag = 1;
						iteEsm->lFlag = 3;//���֣����Ϊ3
						StCluNo.vctEsm.push_back(*iteEsm);
					}
				}
			}
			for(iteComm = AllMessage.stComm.begin(); iteComm != AllMessage.stComm.end(); iteComm++)//δ������Ϣ
			{
				if (!iteComm->cJfFlag)//δ����
				{
					fA = fabs(fA - iteComm->dReachAzimuth);
					if (fA < Acc.dirAcc*2)//��Ϊһ��
					{
						iteComm->cJfFlag = 1;
						iteComm->lFlag = 3;//���֣����Ϊ3
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
				UniNoTrace.push_back(StCluNo);//�����޺���������Ϣ
			}
		}
	}
	//COMM��Ϣ
	for (iteC = SingleComm.begin(); iteC != SingleComm.end(); iteC++)
	{
		/*���StClu*/
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
		/*���StCluNo*/
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

		fA = iteC->dReachAzimuth;//ȡ�÷�λ��

		for (iteComm = AllMessage.stComm.begin(); iteComm != AllMessage.stComm.end(); iteComm++)//AllMessage.stEsm
		{
			if (!iteComm->cJfFlag)//δ����
			{
				if (iteC->lTargetNumber == iteComm->lTargetNumber)//����һ��
				{
					iteComm->cJfFlag = 1;
					iteComm->lFlag = 3;//���֣����Ϊ3
					iteComm->lAutonum = 0;
					*iteC = *iteComm;//����
				}
			}			
		}
		for(iteTrace = AllMessage.stTrace.begin(); iteTrace != AllMessage.stTrace.end(); iteTrace++)//AllMessage.stTrace
		{
			if (!iteTrace->cJfFlag)//δ����
			{
				fA = fabs(fA - iteTrace->dAzimuth);
				if (fA < Acc.dirAcc*2)//��Ϊһ��
				{
					iteTrace->cJfFlag = 1;
					iteTrace->lFlag = 3;//���֣����Ϊ3
					iteTrace->lAutonum = TN;
					StClu.structTrace = *iteTrace;
					StClu.lAutonum = TN;
					//TN++;
				}
			}
		}
		if (StClu.lAutonum)
		{
			for(iteEsm = AllMessage.stEsm.begin(); iteEsm != AllMessage.stEsm.end(); iteEsm++)//δ������Ϣ
			{
				if (!iteEsm->cJfFlag)//δ����
				{
					fA = fabs(fA - iteEsm->dReachAzimuth);
					if (fA < Acc.dirAcc*2)//��Ϊһ��
					{
						iteEsm->cJfFlag = 1;
						iteEsm->lFlag = 3;//���֣����Ϊ3
						StClu.vctEsm.push_back(*iteEsm);
					}
				}
			}
			for(iteComm = AllMessage.stComm.begin(); iteComm != AllMessage.stComm.end(); iteComm++)//δ������Ϣ
			{
				if (!iteComm->cJfFlag)//δ����
				{
					fA = fabs(fA - iteComm->dReachAzimuth);
					if (fA < Acc.dirAcc*2)//��Ϊһ��
					{
						iteComm->cJfFlag = 1;
						iteComm->lFlag = 3;//���֣����Ϊ3
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
			for(iteEsm = AllMessage.stEsm.begin(); iteEsm != AllMessage.stEsm.end(); iteEsm++)//δ������Ϣ
			{
				if (!iteEsm->cJfFlag)//δ����
				{
					fA = fabs(fA - iteEsm->dReachAzimuth);
					if (fA < Acc.dirAcc*2)//��Ϊһ��
					{
						iteEsm->cJfFlag = 1;
						iteEsm->lFlag = 3;//���֣����Ϊ3
						StCluNo.vctEsm.push_back(*iteEsm);
					}
				}
			}
			for(iteComm = AllMessage.stComm.begin(); iteComm != AllMessage.stComm.end(); iteComm++)//δ������Ϣ
			{
				if (!iteComm->cJfFlag)//δ����
				{
					fA = fabs(fA - iteComm->dReachAzimuth);
					if (fA < Acc.dirAcc*2)//��Ϊһ��
					{
						iteComm->cJfFlag = 1;
						iteComm->lFlag = 3;//���֣����Ϊ3
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
				UniNoTrace.push_back(StCluNo);//�����޺���������Ϣ
			}
		}
	}

	/*ʣ��δ������Ϣֱ�Ӵ���δ������Ϣ*/
	for (iteTrace = AllMessage.stTrace.begin(); iteTrace != AllMessage.stTrace.end(); iteTrace++)
	{		
		if (!iteTrace->cJfFlag)//δ����
		{
			iteTrace->lFlag = 3;//���֣����Ϊ3
			iteTrace->lAutonum = 0;
			SingleTrace.push_back(*iteTrace);
		}
	}
	for (iteEsm = AllMessage.stEsm.begin(); iteEsm != AllMessage.stEsm.end(); iteEsm++)
	{		
		if (!iteEsm->cJfFlag)//δ����
		{
			iteEsm->lFlag = 3;//���֣����Ϊ3
			iteEsm->lAutonum = 0;
			SingleEsm.push_back(*iteEsm);
		}
	}
	for (iteComm = AllMessage.stComm.begin(); iteComm != AllMessage.stComm.end(); iteComm++)
	{		
		if (!iteComm->cJfFlag)//δ����
		{
			iteComm->lFlag = 3;//���֣����Ϊ3
			iteComm->lAutonum = 0;
			SingleComm.push_back(*iteComm);
		}
	}
}


/**********************************************�ۼ�3����ʧ�ģ�����ɾ������***********************************************/
void Delete(VCT_UNINUM_MSG& UniMsg, VCT_UNINOTRACE_MSG& UniNoTrace, VCT_TRACE_MSG& SingleTrace, VCT_ESM_MSG& SingleEsm, VCT_COMM_MSG& SingleComm)
{
	VCT_UNINUM_MSG::iterator itt;
	VCT_UNINOTRACE_MSG::iterator itnt;
	VCT_TRACE_MSG::iterator iteTrace;
	VCT_ESM_MSG::iterator iteEsm;
	VCT_COMM_MSG::iterator iteComm;
 	UNI_NOTRACE_NUM StCluNo;     // ��ʱ���� ���޺�����Ϣ�ṹ
	
	/*�к���������Ϣ*/
	for (itt = UniMsg.begin(); itt != UniMsg.end(); itt++)
	{
		//ɾ��esm��comm������Ϣ
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
		//ɾ��trace������Ϣ��ͬʱ�Ƴ����������������Ϣ
		if (itt->structTrace.lFlag == 0)
		{
			//�����޺���������Ϣ
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
			//����δ������Ϣ
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
			//ɾ���к���������Ϣ�������������Ϣ
			UniMsg.erase(itt);
			itt--;
		}
		else
		{
			if (itt->vctEsm.empty()&&itt->vctComm.empty())
			{
				//��������δ������Ϣ
				SingleTrace.push_back(itt->structTrace);
				//ɾ���к���������Ϣ�������������Ϣ
				UniMsg.erase(itt);
				itt--;
			}
		}
	}
	
	/*�޺���������Ϣ*/
	for (itnt = UniNoTrace.begin(); itnt != UniNoTrace.end(); itnt++)
	{
		//ɾ��esm��comm������Ϣ
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
		//��������δ������Ϣ
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
			//ɾ���޺���������Ϣ�������������Ϣ
			UniNoTrace.erase(itnt);
			itnt--;
		}			
	}

	/*δ������Ϣ*/
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

 
/***************************************************���ֱ��**************************************************************/
// ����ͬһ�ۺ����ŵ�esm��com��track��Ϣ��ֻ��Ŀ�����ͼ����ۺϿ��Ŷȣ����õ���Ӧ����ۺϿ��Ŷȵ�Ŀ�����ʹ���ʶ����vev��
void ShowOfHands(TYPEVEC& Type, VCT_IDENTIINFOR_MSG& IdentifyVec)
{
    TYPEVEC Vcst; //�洢��ͬĿ�����ͼ����ۺϿ��Ŷ�
	
	vector<int>  typenum;     //Ŀ������ʶ����
	vector<double>  typecon;  //�ۺϿ��Ŷ�

	/*������*/
	TYPEVEC::iterator it = Type.begin();
	/*��Type�е�һ����Ϣ����vcst*/
	Vcst.clear();
	Vcst.push_back(*it);
	/*�ۺϿ��Ŷ�*/
	typecon.clear();
	typecon.push_back(1 - it->con);
	/*ʶ����*/
	typenum.clear();
	typenum.push_back(1);
	/*���ֱ��*/
	for (it++; it != Type.end(); it++)
	{
		int nflag = 0;
		int len = Vcst.size();
        for (int i = 0;i < len;i ++)//����Vcst
		{
			if (Vcst[i].sType == it->sType)
//			if (strcmp(Vcst[i]->type,(*it)->type) == 0)//Ŀ������һ��
			{
				typenum[i] = typenum[i] + 1;//ʶ����+1
				typecon[i] = typecon[i] * (1 - it->con);//������Ŷ�
				//break;
			}
			else
			{
				nflag++;
			}
		}		
		if (nflag == len)//�����µ�Ŀ������
		{
			STTYPE tmp;
			tmp.lAutonum = it->lAutonum;
			//tmp.sType = it->sType;
			strcpy(tmp.sType,it->sType);
			tmp.con = it->con;
			Vcst.push_back(tmp);//���µ�Ŀ��������Ϣ����Vcst
            typenum.push_back(1);//�µ�Ŀ������ʶ����Ϊ1
			typecon.push_back(1 - it->con);//�µ�Ŀ�����Ϳ��Ŷ�
		}
		
	}
	int nLen = Vcst.size();
	for (int k = 0; k < nLen; k++)//�ۺϿ��Ŷ�
	{
		typecon[k] = 1 - typecon[k];
	}
	/*��������ۺϿ��Ŷ��������ʶ��Ŀ��������������ۺϿ��Ŷ�*/
  	int num = typenum[0];//���ͳ����
  	double c = typecon[0];//����ۺϿ��Ŷ�c
	int max = 0;//����ʶ��Ŀ������Vcst[max]->type
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
// 	printf("�ۺ�����   Ŀ������     �ۺϿ��Ŷ�\n");
// 	printf("%d\t   %d\t        %f\n", Vcst[max]->lAutonum, Vcst[max]->sType, c);

	/*��ʶ��������Identify*/
 	IDENTIINFOR IdentStr;
	IdentStr.lAutonum = Vcst[max].lAutonum;//�ۺ�����
	strcpy(IdentStr.sPlatType,Vcst[max].sType);
	//IdentStr.sPlatType = Vcst[max].sType;//Ŀ������
	IdentStr.dConfidence = c;//�ۺϿ��Ŷ�
	IdentifyVec.push_back(IdentStr);

	
	//���
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
		FirstClusterUni(AllMessage, UniMsg, UniNoTrace, SingleTrace, SingleEsm, SingleComm);//��һ����Ϣ����
	} 
	else
	{
		//����洢�ۼӱ�Ǽ�һ��ͬʱtrace����
		for (itt = UniMsg.begin(); itt != UniMsg.end(); itt++)
		{
			itt->structTrace.lFlag--;
// 			//trace����
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
// 			//trace����
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

		//�ǵ�һ����Ϣ����
		ClusterUni(AllMessage, UniMsg, UniNoTrace, SingleTrace, SingleEsm, SingleComm);
		//�ۼ�3����ʧ�ģ�����ɾ������
		Delete(UniMsg, UniNoTrace, SingleTrace, SingleEsm, SingleComm);
	}
		
 	IdentifyVec.clear();//���֮ǰʶ����

	STTYPE StType;
	TYPEVEC Type;

	for (itt = UniMsg.begin(); itt != UniMsg.end(); itt++)//��������������
	{
		int nLenEsm = itt->vctEsm.size();
		int nLenCom = itt->vctComm.size();
		Type.clear();

		for (int i = 0; i < nLenEsm; i++)//ͬһ���ŵ�esm��Ϣ��type�ṹ����Type
		{
			StType.lAutonum = itt->lAutonum;
			StType.con = itt->vctEsm[i].dConfidence;
			//StType.sType = itt->vctEsm[i].sPlatType;
			strcpy(StType.sType, itt->vctEsm[i].sPlatType);
			Type.push_back(StType);				
		}
		for (i = 0; i < nLenCom; i++)//ͬһ���ŵ�comm��Ϣ��type�ṹ����Type
		{
			StType.lAutonum = itt->lAutonum;
			StType.con = itt->vctComm[i].dConfidence;
			//StType.sType = itt->vctComm[i].sPlatType;
			strcpy(StType.sType,itt->vctComm[i].sPlatType);
			Type.push_back(StType);				
		}
		//ͬһ���ŵ�Trace��Ϣ��type�ṹ����Type
		StType.lAutonum = itt->lAutonum;
		StType.con = itt->structTrace.dConfidence;
		//StType.sType = itt->structTrace.sPlatType;
		strcpy(StType.sType,itt->structTrace.sPlatType);
		Type.push_back(StType);

		ShowOfHands(Type, IdentifyVec);//���þ��ֱ������

// 		for (j = 0; j < nLenEsm; j++)//���EsmType
// 		{
// 			memset(&EsmType, 0, sizeof(TYPEVEC));
// 		}
// 		EsmType.clear();
// 		for (j = 0; j < nLenCom; j++)//���ComType
// 		{
// 			memset(&ComType, 0, sizeof(TYPEVEC));
// 		}
// 		ComType.clear();
	}

//	return (&IdentifyVec);
}
