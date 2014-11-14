#ifndef __COMM_STRUCT
#define __COMM_STRUCT

#pragma warning(disable : 4786)
#include <vector>
#include <map>
using namespace std;
typedef vector<int> VCT_INT;
typedef vector<VCT_INT> VV_INT;
typedef vector<double> VCT_DOUBLE;
typedef vector<VCT_DOUBLE> VV_DOUBLE;

typedef struct __SHIP_POSITION           //���ľ�γ��
{
	double dLonti;
	double dLati; 
	double dHeight;

}SHIP_POSITION;

typedef struct _POSITION
{
	double dx;
	double dy;
	double dz;
}TARGET_POSITION;

typedef vector<TARGET_POSITION> VCT_POSITION;		//������x��y��z��������

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
	char sPlatType[32];                 //ƽ̨�ͺ�   (F117�� F118�� 'F119�� F120��F121)
	char cPlatName[32];                 //ƽ̨����  �ɻ� ���� ��ը�� ս����
	double dConfidence;                 //ƽ̨�ͺſ��Ŷ�
    char cDWAttribute[32];              //�������� (IFF��Ϣ)
	double dDWConfidence;               //���ҿ��Ŷ�
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
    char sPlatType[32];                   //ƽ̨�ͺ�   (F117�� F118�� 'F119�� F120��F121)
	char cPlatName[32];			          //ƽ̨����    
    double dConfidence;                  //ƽ̨�ͺſ��Ŷ�
    char cDWAttribute[32];               //�������� (IFF��Ϣ)
	double dDWConfidence;                //���ҿ��Ŷ�
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
	double dThrDg;                        //�ۺ���в��
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
    char sPlatType[32];					 //ƽ̨�ͺ�   (F117�� F118�� 'F119�� F120��F121)	
	char cPlatName[32];                  //ƽ̨����  
    double dConfidence;                  //ƽ̨�ͺſ��Ŷ�
    char cDWAttribute[32];               //�������� (IFF��Ϣ)
	double dDWConfidence;                //���ҿ��Ŷ�
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
    long lStampTime;                     //����������Ϣʱ�ĵ�ǰʱ�� �������ĵ�ǰʱ����÷�����Ϣ�ĵ�ǰʱ��������	
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
	
	int nCOMCount;                            //������
	VCT_INT vctCOMMBHao;                      //COM��Ӧ��COMģ���
	VCT_INT vctCOMHao;                        //COM����
	
	VCT_INT vctCOMBasicSituation;               //COM�����¼�
	
    double dThreatDegree;                 //ƽ̨�ۺ���в��
	int nTrackType;                      //ƽ̨�ۺ�ʶ������
	
}EVENTLINKS;  //������������¼�����ڵ�����;
typedef map<int, EVENTLINKS> MAP_BASIC_EVENT;  //�����¼���//int��ʾ��������

//����̬�ƣ�1������ֱ���˶���2������ֱ�����С�3�����塢4��������5�����䡢6��Զ�뱾����7���ƽ�������
	//          8����λ�ù̶���9����Ŀ�ꡢ10��Ŀ����ʧ��11������

//�����¼��ڰ�ṹ
typedef struct BasicEVentBIndexes 
{
	int nSeriaN;                        //���
	long lTimeStamp;                  //ʱ��
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
    int nTrackType;               //�����ۺ�ʶ���Ŀ������
	
	//������쳣ESM���
	int nESMCount;                 //ESM��
	VCT_INT vctESMHao;                 //����ESM�������������ESM,//�����ESM�쳣������10��
	VCT_INT vctESMEvent;               //ESM�����¼�
	//������쳣COM���
	int nCOMCount;                 //COM��
	VCT_INT vctCOMHao;                 //����COM�������������COM
	
	VCT_INT vctCOMEvent;               //COM�����¼�
}EVENTBLACK;  //�źڰ�ڵ�����;


typedef map<int, EVENTBLACK> MAP_EVENT_BLACK;  //�ڰ壬int��ʾ��������


//��ƽ̨̬������ṹ
typedef  struct Link_Table_Situation 
{
	int nSerialnum;                    //���
	int nPlatHao;                      //ƽ̨����
    int nPlatMBHao;                    //ģ���    

	int nESMHao;                       //ƽ̨�������õ�ESM����
	
	int nCOMHao;                       //ƽ̨�������õ�COM����

	int nPlatOBjType;                 //ƽ̨�ۺ�ʶ���Ŀ������	
	
	int nESMBasicSituation;           //ƽ̨�������õ�ESM�����¼�
    int nCOMBasicSituation;           //ƽ̨�������õ�COM�����¼�
    int nPlatCumulativeN;             //�ۻ�ֵ

	//֪ʶ����������
	int nPlatOBJEvent;                 //ƽ̨����̬��
	double dThreatDegree;              //ƽ̨�ۺ���в��

	//��Ӧ�ĺ�������(�ռ������)
	double dRd;                  //����
	double dAz;
	double dEz;
	double dHigh;               //�߶�
	double dSpeed;              //�ٶ�
	double dAddSpeed;           //���ٶ�
	double dAzimuth;            //����

}PLATEVENT;
typedef map<int, PLATEVENT> MAP_PLAT_LINK;

//ƽ̨̬�ƺڰ�ģ�ͽṹ
typedef struct PlatBlack_Table_Situation
{
	int nSerialnum;                       //���
    long lTimeStamp;                    //ʱ��

	int nPlatHao;                         //ƽ̨����
	int nPlatBasicSituation;             //ƽ̨����̬��

	int nESMHao;                          //��̬�������õ�ESM����
	int nESMBasicSituation;               //��̬�������õ�ESM�����¼�

	int nCOMHao;                          //��̬�������õ�COM����

	int nCOMBasicSituation;               //��̬�������õ�COM�����¼�
	
    int nTrackOBjType;                  //�����ۺ�ʶ���Ŀ������

	//��Ӧ�ĺ�������(�ռ������)
	double dRd;                  //����
	double dAz;
	double dEz;
	double dHigh;               //�߶�
	double dSpeed;              //�ٶ�
	double dAddSpeed;           //���ٶ�
	double dAzimuth;            //����

	double dThreatDegree;              //ƽ̨�ۺ���в��
}PLATBLACK;
typedef vector<PLATBLACK> VCT_PLAT_BLACK;
typedef map<int, PLATBLACK> MAP_PLAT_BLACK;

//�ռ�ȺĿ������ṹ
typedef struct SpaceGroup_PlanLink_Tabel             //�ռ�Ⱥ�ṹ
{
    int nPlanTypeN;                   //�ռ�Ⱥ��
	
    VCT_INT vctPlanGroupN;              //ÿ��Ⱥ��Ŀ������
    VV_INT vvPlanGroupHao;        //ÿ��Ⱥ��Ŀ�������
	
	int nPlanSpacMBHao;               //�ռ�Ⱥ����ɻ���ģ���
	
    VCT_DOUBLE vctPlanThreatDegree;     //ÿ��Ⱥ�ۺ���в��
	
	VV_INT vvPlanGroupOBjType;  //ÿ���ռ�Ⱥ�к���Ŀ������
	
    int nPlanCumulativeN;            //ģ���ۻ�ֵ
	//������
    VV_INT vvPlanEvent;            //ÿ���ռ�ȺĿ��̬��
	
 }SPACE_TARGET;

//�ռ�Ⱥ�ڰ�ṹ
typedef struct SpaceGroupBlack_Tabel               //�ռ�Ⱥ�ڰ�ṹ
{
	long lTimeStamp;                  //��ǰʱ��
	
	int nPlanTypeN;                   //������ռ�Ⱥ��
    VCT_INT vctPlanGroupN;              //������ÿ��Ⱥ��Ŀ������
    VV_INT vvPlanGroupHao;        //������ÿ��Ⱥ��Ŀ�������
	
    VCT_DOUBLE vctPlanThreatDegree;     //������ÿ��Ⱥ�ۺ���в��
	
    VV_INT vvPlanGroupOBjType;  //������ÿ���ռ�Ⱥ�к���Ŀ������
	
	//ǰ��������
	VV_INT vvPlanEvent;            //ÿ�������ռ�ȺĿ��̬��
	
 }SPACE_BLACK;

typedef vector<SPACE_TARGET> VCT_SPACE;

/////////////////////////////////���ܲ�/////////////////////////////////////////////////
////����Ⱥ����ṹ
typedef struct FuncGroup_Link_Tabel             //��������Ⱥ�ṹ
{
	int nFuncGroupMBNum;                     //����Ⱥģ����
	VCT_INT vctFuncMBHao;                  //����ģ���
	
	int nFuncGroupN;                 //����Ⱥ��
	VCT_INT vctFuncGpH;                //ÿ������Ⱥ��Ӧ�ı��
	VCT_INT vctFuncGroupTrackN;        //ÿ������Ⱥ�к�Ŀ������
	VV_INT vvFuncGroupHao;        //ÿ��Ⱥ��Ŀ�������
	
	VCT_DOUBLE vctFuncThreatDegree;     //ÿ��Ⱥ�ۺ���в��
	
	VV_INT vvFuncGroupOBjType;  //ÿ������Ⱥ�к���Ŀ������
	
	//֪ʶ����������
	VCT_INT vctFuncGroupEvent;         //ÿ������Ⱥ̬�ƣ�1���䡢2��Ѳ�ߣ�3��������4�����أ�5����ը��6��ͻ����7�����š�8��Ԥ��,9:��졢10������
    VCT_INT vctFuncCumulativeN;            //ģ���ۻ�ֵ
	
}FUN_GROUP_LINK;

///����Ⱥ�ڰ����ݽṹ
typedef struct FuncGroup_Black_Tabel             //����Ⱥ�ڰ�ṹ
{
	long lTimeStamp;                //��ǰʱ��
	
    int nFuncGroupN;                 //����Ⱥ��
    VCT_INT vctFuncGpHao;            //����Ⱥ���
	
    VCT_INT vctFuncGroupTrackN;        //ÿ������Ⱥ�к�Ŀ������
    VV_INT vvFuncGroupTrackHao;        //ÿ��Ⱥ��Ŀ�������
	
    VCT_DOUBLE vctFuncThreatDegree;     //ÿ��Ⱥ�ۺ���в��
	
	VV_INT vvFuncGroupOBjType;  //ÿ������Ⱥ�к���Ŀ������
	
	//֪ʶ����������
	VCT_INT vctFuncGroupEvent;         //ÿ������Ⱥ̬�ƣ�1���䡢2��Ѳ�ߣ�3��������4�����أ�5����ը��6��ͻ����7�����š�8��Ԥ��,9:��졢10������
	
}FUN_GROUP_BLACK;


//////////////////////////////////////////�໥���ò�////////////////////////////////////////////////



//�໥����Ⱥ̬������ƽṹ
typedef struct Interaction_Link_Tabel               //�໥����Ⱥ����ṹ
{
	int nInteGroupSeriNum;                   //�໥����Ⱥ��ţ��Զ�������,�����໥����Ⱥ������10��
	
	int nInteractGroupSGN;                   //�໥����Ⱥ�к�����Ⱥ��
    
    double dSumThreatDegree;                 //�໥����Ⱥ���ۺ���в��
	
    VCT_INT vctInteGroupTrackNum;              //ÿ����Ⱥ�е�Ŀ����
    VCT_INT vctInteGroupHao;                   //ÿ����Ⱥ��
    VCT_INT vctInterEvent;                     //ÿ����Ⱥ��̬������
	
    VV_INT vvIntertrackHao;					//ÿ����Ⱥ�к�Ŀ������
    VV_INT vvInterOBjType;					//ÿ����Ⱥ�к�Ŀ������       
	
    int nInteCumulativeN;                    //�໥����Ⱥģ���ۻ�ֵ
}INTERGROUP;
typedef vector<INTERGROUP> INTERGROUPLINK;

//�໥����Ⱥ�ڰ���ƽṹ
typedef struct Interaction_Black_Tabel                  //�ڰ��ϵ��໥����Ⱥ�ṹ
{
    long lTimeStamp;                           //ʱ��
	int nInteGroupSeriNum;                       //�໥����Ⱥ��ţ��Զ�������,�����໥����Ⱥ������20��  (��ʾ)   
	
	int nInteractGroupSGN;                      //�໥����Ⱥ�к�����Ⱥ��
    double dSumThreatDegree;                    //�໥����Ⱥ���ۺ���в��  
	
    VCT_INT vctInteGroupTrackNum;                //ÿ����Ⱥ�е�Ŀ����
    VCT_INT vctInteGroupHao;                     //ÿ����Ⱥ��
    VCT_INT vctInterEvent;                       //ÿ����Ⱥ��̬������
	
    VV_INT vvIntertrackHao;               //ÿ����Ⱥ�к�Ŀ������
    VV_INT vvInterOBjType;               //ÿ����Ⱥ�к�Ŀ������         
}INTERBLACKNODE;
typedef vector<INTERBLACKNODE> INTERGROUPBLACK;


///////////////////////////////////���ݿ����ݽṹ///////////////////////////////////////////////

typedef struct DataBase
{
	VCT_INT TrackThd;          //Track����ֵ,�洢˳��Ϊ�����࣬�߶ȣ��ٶȣ����ٶȣ���λ
	VCT_INT ESMThd;            //ESM����ֵ���洢˳��Ϊ ����Ƶ�ʣ�������ȣ������ȣ���Ƶ������ɨ������
	VCT_INT COMThd;            //COM����ֵ���洢˳��Ϊ ����Ƶ�ʣ�������ȣ���Ƶ����
	VCT_INT TrackModelID;	   //Track��ģ���
	VCT_INT ESMModelID;        //ESM��ģ���
	VCT_INT COMModelID;        //COM��ģ���
	VCT_INT PlatModelID;       //ƽ̨ģ���
	VCT_INT FunModelID;			//����Ⱥģ���
	VCT_INT InterModelID;		//ģ��ţ���ţ�
	VCT_INT TrackEventID;      //Track�����¼����
	VCT_INT ESMEventID;        //ESM�Ļ����¼����
	VCT_INT COMEventID;        //COM�Ļ����¼����
	VCT_INT PlatEventID;       //ƽ̨�¼����
	VCT_INT SpaceGrpID;        //�ռ�Ⱥ���
	VCT_INT FunEventID;			//����Ⱥ�¼����
	VV_INT vctDbTrackKng;      //������ݿ���track��֪ʶ���������ݣ��������ڳ����ʼ����ʱ�����
	VV_INT vctDbESMKng;        //������ݿ���ESM��֪ʶ���������ݣ��������ڳ����ʼ����ʱ�����
	VV_INT vctDbCOMKng;        //������ݿ���COM��֪ʶ���������ݣ��������ڳ����ʼ����ʱ�����
	VV_INT vctDbPlatKng;       //������ݿ���Plat��֪ʶ���������ݣ��������ڳ����ʼ����ʱ�����
	VV_INT vctDbSpaceKng;      //������ݿ���Space��֪ʶ���������ݣ��������ڳ����ʼ����ʱ�����
	VV_INT vctDbFunKng;			//������ݿ���Fun��֪ʶ����������
	VV_INT vctDbInterKng;      ////��ӹ���:1���䡢2��Ѳ�ߣ�3��������4�����أ�5����ը��6��ͻ����7�����š�8��Ԥ��,9:���
}DB_DATA;


//������Ϣ��ͷ
typedef struct _X_ALL_RECV_MSG
{
	VCT_ESM_MSG stEsm;
	VCT_COMM_MSG stComm;
	VCT_TRACE_MSG stTrace;
}ALL_MSG_INPUT;


#endif