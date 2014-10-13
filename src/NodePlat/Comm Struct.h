#ifndef __COMM_STRUCT
#define __COMM_STRUCT

#pragma warning(disable : 4786)
#include <vector>
using namespace std;

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
// ������Ϣ
// 	 ZAI_FREQ stZaiPin;                  //��Ƶ��Ϣ�ṹ
// 	 CHONG_FREQ stChongPin;              //��Ƶ��Ϣ�ṹ
// 	 WIDTH_MSG stMaiKuan;                //������Ϣ�ṹ
// 	 AntennaScan_MSG stTianXianScan;     //����ɨ����Ϣ�ṹ
// 	 PulseFeature_MSG stMaiChongFeature; //����������Ϣ�ṹ
	 double dZaiPin;                     //��Ƶ��Ϣ�ṹ
	 double dChongPin;                   //��Ƶ��Ϣ�ṹ
	 double dMaiKuan;                    //������Ϣ�ṹ
	 double dTianXianScan;               //����ɨ����Ϣ�ṹ
	 double dMaiChongFeature;            //����������Ϣ�ṹ
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

	 char cDWAttribute[32];                  //��������
	 double dConfidence;                 //���Ŷ�
     char cCountry[32];                  //���ң�������

	 char cJfFlag;
	 unsigned long lFlag;                 //�ۼӱ��

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
//	ZAI_FREQ stComZaiPin;                //��Ƶ��Ϣ�ṹ
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
	char cDWAttribute[32];					  //��������
	double dConfidence;  			      //���Ŷ�
    char cCountry[32];			          //���ң�������
	char cJfFlag;
	unsigned long lFlag;                  //�ۼӱ��

}COMSTATUS_MARK;


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
    unsigned long lTargetNumber;         //Ŀ������	 
//������Ϣ
	double dRange;                        //����
	double dAzimuth;                      //��λ
	double dElevationAngle;               //����
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
//ʶ����Ϣ
//	unsigned short sPlatType;            //ƽ̨����  F117  (F117�� F118�� F119��F120�� F121)
    char sPlatType[32];  
	char cPlatName[32];                  //ƽ̨����  
    double dConfidence;                  //���Ŷ�
    char cDWAttribute;                   //�������� (IFF��Ϣ)
	char cJfFlag;                        //�Ƿ���������ںϱ�־��0��δ�ںϣ�1�����ں�
	unsigned long lFlag;                 //�ۼӱ��

}TRACKSTATUS_MARK;

typedef vector<SHIP_POSITION> VCT_SHIP_POSITION; //�洢������GPS��Ϣ
typedef vector<ESMSTATUS_MARK> VCT_ESM_MSG;	//�洢�״������Ϣ
typedef vector<COMSTATUS_MARK> VCT_COMM_MSG; //�洢ͨ�������Ϣ
typedef vector<TRACKSTATUS_MARK> VCT_TRACE_MSG; //�洢�״�̽����Ϣ

//������Ϣ��ͷ
typedef struct _X_ALL_RECV_MSG
{
	VCT_ESM_MSG stEsm;
	VCT_COMM_MSG stComm;
	VCT_TRACE_MSG stTrace;
}ALL_MSG_INPUT;

#endif