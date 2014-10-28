#ifndef __COMM_STRUCT
#define __COMM_STRUCT

#pragma warning(disable : 4786)
#include <vector>
using namespace std;
typedef vector<int> VCT_INT;

typedef struct __SHIP_POSITION           //���ľ�γ��
{
	double dLonti;
	double dLati; 
	double dHeight;

}SHIP_POSITION;

/* �״������Ϣ */
typedef struct __ESMSTATUS_MARK   
{

	// ������Ϣ
	char head;				         // ����ͷ
	// ��ݱ�ʶ	
	unsigned long lAutonum;			 //�ۺ�����
	char cPlatNumber[32];              //ƽ̨���
	char cEquipmentNumber[32];         //�豸���
	char cEquipmentType[32];           //�豸����
	unsigned long lTargetNumber;       //Ŀ������ 
	
	double dZaiPin;                     //��Ƶ��Ϣ�ṹ
	double dChongPin;                   //��Ƶ��Ϣ�ṹ
	double dMaiKuan;                    //������Ϣ�ṹ
	double dTianXianScan;               //����ɨ����Ϣ�ṹ������ɨ�����ڣ�
	double dMaiChongFeature;            //����������Ϣ�ṹ������Ƶ�ʣ�
	double dPulseExtent;                //�������
	long lSignalReachTime;              //�źŵ���ʱ��
	double dReachAzimuth;               //���﷽λ
	double dElevationAngle;             //����
	
	//ʶ����Ϣ
	char cRadarPurpose[32];             //�״���;
	char cRadarName[32];                //�״�����
	double dThreatLevel;                //��в�ȼ�0--7
	double dERPower;                    //��Ч���书��
	// unsigned short sPlatType;             //ƽ̨����   (F117�� F118�� 'F119�� F120��F121)
	char sPlatType[32];  
	char cPlatName[32];                 //ƽ̨����  �ɻ� ���� ��ը�� ս����
	
	char cDWAttribute[32];              //��������
	double dConfidence;                 //���Ŷ�
	char cCountry[32];                  //���ң�������
	
	unsigned long lJfFlag;               //������
	unsigned long lFlag;                 //�ۼӱ��
	//1016����
	unsigned long lFusFlag;                //�ںϲ��ұ��

	//10.20������ESM�����¼���ģ���
	int nESMEvt;                         //ESM�����¼�
	int nModel;                          //ģ���

}ESMSTATUS_MARK;
 

/* ͨ�������Ϣ */
typedef struct __COMSTATUS_MARK           //ͨ�������Ϣ 
{	

// ������Ϣ
	char head;				             //����ͷ
// ��ݱ�ʶ
	unsigned long lAutonum;			     //�ۺ�����
	char cPlatNumber[32];                //ƽ̨���
    char cEquipmentNumber[32];           //�豸���
    char cEquipmentType[32];             //�豸����
    unsigned long lTargetNumber;         //Ŀ������ 
// ������Ϣ
    double dComZaiPin;                   //��Ƶ��Ϣ�ṹ
	double dReachAzimuth;                //���﷽λ
	double dElevationAngle;              //����
	unsigned long lSignalReachTime;      //�źŵ���ʱ��
   	double dPulseExtent;                 //������� 
// 0909����:
    double dComFre;                       // ����Ƶ��(MHz)
	double dComBand;                      // �źŴ���(MHz)
	double dComJPN;                       // ��������
//ʶ����Ϣ 
    char cSignalType[32];                 //�ź�����
	char cModulationStyle[32];            //������ʽ     
    char sPlatType[32];                   //ƽ̨����  F117  (F117�� F118�� F119�� F120�� F121)
	char cPlatName[32];			          //ƽ̨����    
	char cDWAttribute[32];				  //��������
	double dConfidence;  			      //���Ŷ�
    char cCountry[32];			          //���ң�������
	unsigned long lJfFlag;                //������
	unsigned long lFlag;                  //�ۼӱ��
//1016����
	unsigned long lFusFlag;                //�ںϲ��ұ��

	//10.20������COM�����¼���ģ���
	int nCOMEvt;                          //COM�����¼�
	int nModel;                           //COMģ���

}COMSTATUS_MARK;

// 1ս������2 ��ը����3�߻��� �������� ����Ϊ��1�ࣩ
// 4Ԥ������   ����Ϊ��2�ࣩ
// 5������6���Ż�7 ֱ����(������Ǳ�������˻�������)   ����Ϊ��3�ࣩ
// 8 ��ͧ             ����4�ࣩ
// 9ս������������5�ࣩ
// 10�Ƶ�����  ����6�ࣩ

/*�״ﺽ����IFF��Ϣ*/
typedef struct __TRACKSTATUS_MARK        //�״ﺽ����IFF��Ϣ  
{
// ������Ϣ
	char head;			                 // ����ͷ
// �����Ϣ
	unsigned long lAutonum;			     //�ۺ�����
	char cPlatNumber[32];                //ƽ̨���
    char cEquipmentNumber[32];           //�豸���
    char cEquipmentType[32];             //�豸����
	int nTgtType;                        //Ŀ������  10.21��ӣ��������6����������
    unsigned long lTargetNumber;         //Ŀ������	 
//������Ϣ
	double dRange;                        //����
	double dAzimuth;                      //��λ
	double dElevationAngle;               //����
//1020 ̬��
	double dHeight;                       //�߶�
	double dVSpeed;                       //�ٶ�
    double dAddSpeed;                     //���ٶ�
	double dThreatLevel;                  //��в�ȼ�0--7
	int nTrackEvent;                      //���������¼�
	int nModel;                           //ģ���
	int nRdChEvt;                         //����仯�¼�
	int nHtChEvt;                         //�߶ȱ仯�¼�
	int nVSChEvt;                         //�ٶȱ仯�¼�
	int nAddVSChEvt;                      //���ٶȱ仯�¼�
	int nCuChEvt;                         //����仯�¼�
    double dCourse;                       //���Ժ���
	long lSignalReachTime;                //�źŵ���ʱ��
	double dTargetAZSpeed;                //Ŀ�귽λ���ٶ�
	double dTargetEAngleSpeed;            //Ŀ�����ǽ��ٶ�
    double dTX;                           //Ŀ��ռ�����X
	double dTY;                           //Ŀ��ռ�����Y
	double dTZ;                           //Ŀ��ռ�����Z
	double dTSpeedX;                      //Ŀ������ٶ�X
    double dTSpeedY;                      //Ŀ������ٶ�Y
    double dTSpeedZ;                      //Ŀ������ٶ�Z
	double dLonti;                        //Ŀ�꾭��
	double dLati;                         //Ŀ��γ��
        double dObjHeight;		      //Ŀ��߶� 
	//ʶ����Ϣ
    char sPlatType[32];						
	char cPlatName[32];                  //ƽ̨����  
    double dConfidence;                  //���Ŷ�
    char cDWAttribute[32];               //�������� (IFF��Ϣ)
	unsigned long lJfFlag;               //�Ƿ���������ںϱ�־��0��δ�ںϣ�1�����ں�
	unsigned long lFlag;                 //�ۼӱ��
//1016����
	unsigned long lFusFlag;                //�ںϲ��ұ��


}TRACKSTATUS_MARK;

typedef vector<SHIP_POSITION> VCT_SHIP_POSITION; //�洢������GPS��Ϣ
typedef vector<ESMSTATUS_MARK> VCT_ESM_MSG;	//�洢�״������Ϣ
typedef vector<COMSTATUS_MARK> VCT_COMM_MSG; //�洢ͨ�������Ϣ
typedef vector<TRACKSTATUS_MARK> VCT_TRACE_MSG; //�洢�״�̽����Ϣ

//////// 2014 1016 wanghaiying ///////////////////////////////////////////////////
typedef struct __Cooperative_FUSIDENTIINFOR   //Эͬ���ں���Ϣ��ʶ�����ṹ��
{
    long int nStampTime;                     //����������Ϣʱ�ĵ�ǰʱ�� �������ĵ�ǰʱ����÷�����Ϣ�ĵ�ǰʱ��������	
	unsigned long lAutonum;
    char sPlatType[32];             //�ۺ�ƽ̨����  F117  (F117�� F118�� F119�� F120�� F121)
	double dConfidence;                      //�ۺϿ��Ŷ�
	
	TRACKSTATUS_MARK stFusTrack;            //�洢�ںϺ���״�̽����Ϣ��������Ϣ��
	VCT_ESM_MSG vctFusEsm;                  //�洢�ںϺ���״������Ϣ
	VCT_COMM_MSG vctFusCom;                 //�洢�ںϺ��ͨ�������Ϣ   
}Cooperative_FUSIDENTIINFOR;

typedef vector<Cooperative_FUSIDENTIINFOR> VCT_Cooperative_FUSIDENTIINFOR;  //�洢Эͬ���ں���Ϣ��ʶ�����Ľṹ��

typedef struct Link_Table_Event
{
	int nSerialnum;                       //���
    int nTrackMBHao;                      //������Ӧ��ģ���
	int nTrackHao;                        //��������
	
	int nTrackCumulativeN;                //�����ۻ�ֵ
	int nTrackBasicSituation;             //��������Ļ����¼�
	
	int nESMCount;                        //����ESM��
	VCT_INT vctESMMBHao;                      //ESM��Ӧ��ESMģ���
	VCT_INT vctESMHao;                        //ESM����
	
	VCT_INT vctESMCumulativeN;                //ESM�ۻ�ֵ
	VCT_INT vctESMBasicSituation;             //ESM�����¼�
	
	int nCOMN;                            //������
	VCT_INT vctCOMMBHao;                      //COM��Ӧ��COMģ���
	VCT_INT vctCOMHao;                        //COM����
	
	VCT_INT nCOMBasicSituation;               //COM�����¼�
	
    double dThreatDegree;                 //ƽ̨�ۺ���в��
	char cTrackType;                      //ƽ̨�ۺ�ʶ������
	
}EVENTLINKS;  //������������¼�����ڵ�����;

//����̬�ƣ�1������ֱ���˶���2������ֱ�����С�3�����塢4��������5�����䡢6��Զ�뱾����7���ƽ�������
	//          8����λ�ù̶���9����Ŀ�ꡢ10��Ŀ����ʧ��11������

//�����¼��ڰ�ṹ
typedef struct BasicEVentBIndexes 
{
	int nSeriaN;                        //���
	double dTimeStamp;                  //ʱ��
	int nTrackHao;                      //��������	
	
	//��Ӧ�ĺ�������(�ռ����Ҫ��)
	double dRd;                  //����
	double dAz;
	double dEz;
	double dHigh;               //�߶�
	double dSpeed;              //�ٶ�
	double dAddSpeed;           //���ٶ�
	double dAzimuth;            //����
	
	
	int nTrackEvent;           //���������¼���
	VCT_INT vctEventValue;        //���������仯����
	
    double dThreatDegree;          //ƽ̨�ۺ���в��
    char cTrackType;               //�����ۺ�ʶ���Ŀ������
	
	//������쳣ESM���
	int nESMCount;                 //ESM��
	VCT_INT vctESMHao;                 //����ESM�������������ESM,//�����ESM�쳣������10��
	VCT_INT vctESMEvent;               //ESM�����¼�
	//������쳣COM���
	int nCOMCount;                 //COM��
	VCT_INT vctCOMHao;                 //����COM�������������COM
	
	VCT_INT vctCOMEvent;               //COM�����¼�
}EVENTBLACK;  //�źڰ�ڵ�����;

//������Ϣ��ͷ
typedef struct _X_ALL_RECV_MSG
{
	VCT_ESM_MSG stEsm;
	VCT_COMM_MSG stComm;
	VCT_TRACE_MSG stTrace;
}ALL_MSG_INPUT;

#endif