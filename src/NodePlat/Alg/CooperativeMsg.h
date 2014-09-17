#include "../Comm Struct.h"
/*#include "XSi.h"*/
using namespace std;
/*
//////////////////////////////////////////////////////////////
//               ���ݺ������ں�
//      �����1�����ڸ���Эͬʶ���Ŀ�����漰�ĸ�����Ϣ
//            2���ںϺ�����ţ�ͳһ�ñ����ϵ�ԭЭͬĿ���Ӧ�ĸ����ţ�����������
//            3���·���̬�Ʒ���ģ��
/////////////////////////////////////////////////////////////
//�����ں�
typedef struct __FUS_TRACK
{
	double dFusTrackRd;                //Ŀ�꺽���ľ��ࣨ�ף�
	double dFusTrackAz;                //Ŀ�꺽���ķ�λ�����ȣ�
	double dFusTrackEz;                //Ŀ�꺽�������ǣ����ȣ�
	double dFusTrackVx;                //Ŀ�꺽����X���ϵ��ٶȣ���/�룩
	double dFusTrackVy;                //Ŀ�꺽����Y���ϵ��ٶȣ���/�룩
	double dFusTrackVz;                //Ŀ�꺽����Z���ϵ��ٶȣ���/�룩
	char cFusTrackRecogType;           //Ŀ�꺽����ʶ������(���ۺ�ʶ�����ʹ���)
    double dFusTrackConfidence;        //Ŀ�꺽����ʶ����Ŷ�(���ۺ�ʶ����Ŷȴ���)
	
}FUS_TRACK;

//ESM�ں�
typedef struct __FUS_ESM
{
	double dFusESMDOAz;                 //ESM�źŵĵ��﷽λ�����ȣ�
	double dFusESMFre;                  //ESM�źŵ�Ƶ�ʣ�GHz��
	double dFusESMPA;                   //ESM�źŵķ���
	double dFusESMPzw;                  //ESM�źŵ������ȣ�us��
	double dFusESMPRI;                  //ESM�źŵ��ظ������ms��;�ظ�Ƶ��PRF=PRI�ĵ���
	double dFusESMSCan;                 //ESM�źŵ�����״�����ɨ�����ڣ�s��
	char cFusESMRecogType;              //ESM�źŵ�ʶ������(���ۺ�ʶ�����ʹ���)
    double dFusESMConfidence;           //ESM�źŵ�ʶ����Ŷ�(���ۺ�ʶ����Ŷȴ���)
	
}FUS_ESM;

//COM�ں�
typedef struct __FUS_COM
{ 
	double dFusCOMDOAz;                //COM�źŵĵ��﷽λ�����ȣ�
	double dFusCOMFre;                 //COM�źŵ�����Ƶ�ʣ�MHz��
	double dFusCOMPA;                  //COM�źŵķ���
	double dFusCOMBand;                //COM�źŵ��źŴ���MHz��
	double dFusCOMJPN;                 //COM�źŵ���������
	char cFusCOMRecogType;             //COM�źŵ�ʶ������
    double dFusCOMConfidence;          //COM�źŵ�ʶ����Ŷ�
	
}FUS_COM;

typedef vector<FUS_TRACK> VCT_FUS_TRACK;      //�洢�ںϺ���״�̽����Ϣ (������Ϣ)
typedef vector<FUS_ESM> VCT_FUS_ESM;	     //�洢�ںϺ���״������Ϣ (���ݹ���ϵ�����洢��ͬ����������Ϣ�ṹ��)
typedef vector<FUS_COM> VCT_FUS_COM;         //�洢�ںϺ��ͨ�������Ϣ (���ݹ���ϵ�����洢��ͬ�����ͨ����Ϣ�ṹ��)

typedef struct __Cooperative_FUSIDENTIINFOR  //Эͬ���ں���Ϣ��ʶ�����ṹ��
{
	unsigned long lAutonum; 	             //�ۺ�����
	unsigned short sPlatType;                //ƽ̨����  F117  (F117�� F118�� F119�� F120�� F121)
	double dConfidence;                      //���Ŷ�	
	FUS_TRACK stFusTrack;                    //�洢�ںϺ���״�̽����Ϣ��������Ϣ��
	//	VCT_FUS_TRACK vctFusTrack;
	VCT_FUS_ESM vctFusEsm;                   //�洢�ںϺ���״������Ϣ
    VCT_FUS_COM vctFusCom;                   //�洢�ںϺ��ͨ�������Ϣ                  	
}Cooperative_FUSIDENTIINFOR;
typedef vector<Cooperative_FUSIDENTIINFOR> VCT_Cooperative_FUSIDENTIINFOR;  //�洢Эͬ���ں���Ϣ��ʶ�����Ľṹ��
*/

typedef struct __Cooperative_Msg     //����ͷ�����Ϣ�������ݽṹ
{	
	unsigned long lAutonum;                  //������Ϣ���ۺ�����
    VCT_TRACE_MSG vctTrace;                  //�������ͷ��صĺ�����Ϣ
	VCT_ESM_MSG vctEsm;                     
	VCT_COMM_MSG vctComm;   
}Cooperative_Msg;
typedef vector<Cooperative_Msg> VCT_COOPER_MSG;
//ƽ̨��������
typedef vector<char*> VCT_sPlatType;

//******************************************************************************************//
//           �རЭͬ���ҷ�����Ϣ����     0831 why                                                   //

//********  ���룺����������Ϣ                                              ****************//
//********        ��������ĵ���λ����Ϣ                                          **********//
//********  �����������Ϣ                                                       **********// 
//******************************************************************************************//
//���������ڽ�Эͬ,���յ��ڽ����͵���Ϣ��,�����ۺ�ʶ����
//void GET_CooperateMsg_Modul(SHIP_POSITION& stSelfPosi,VCT_Request_Cooperative_Msg& vctRequestCooperative, VCT_BACK_Cooperative_Msg& vctBackCooperative, VCT_COOPER_MSG& vctCooperMsg); 
void GET_CooperateMsg_Modul(/*SHIP_POSITION& stSelfPosi,*/VCT_Request_Cooperative_Msg& vctRequestCooperative, VCT_BACK_Cooperative_Msg& vctBackCooperative, VCT_COOPER_MSG& vctCooperMsg);

//void Mf_SPA(double s, double t,double& corr); //s,tΪ��ͬ���͵���Ϣ�����м��Է����������ص����ϵ����������VctCorr��