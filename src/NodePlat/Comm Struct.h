#ifndef __COMM_STRUCT
#define __COMM_STRUCT

#pragma warning(disable : 4786)
#include <vector>
using namespace std;

typedef struct __ZAI_FREQ         //��Ƶ��Ϣ
{

}ZAI_FREQ;

typedef struct __CHONG_FREQ       //��Ƶ��Ϣ
{

}CHONG_FREQ;
 
typedef struct __WIDTH_MSG        //������Ϣs
{

}WIDTH_MSG;

typedef struct __AntennaScan_MSG  //����ɨ����Ϣ
{

}AntennaScan_MSG;

typedef struct __PulseFeature_MSG //����������Ϣ�����ڣ����䣩
{

}PulseFeature_MSG;

#define SOPTNUMC 32         // ����ƽ̨����ַ��� char cPlatNumber[SOPTNUMC]
#define SOEQNUMC 32         // �����豸����ַ��� char cEquipmentNumber[SOEQNUMC]
#define SOEQTYPEC 32        // �����豸�����ַ��� char cEquipmentType[SOEQTYPEC]
#define SORADPURC 32	    // �����״���;�ַ��� char cRadarPurpose[SORADPURC]
#define SORADNAMEC 32	    // �����״������ַ��� char cRadarName[SORADNAMEC]

// #define SOCTYC 32		// ����ͨ�������ַ���
// #define SOCMYC 32		// ���������ʽ�ַ���
// #define SOTARGETC 32 	// ����ʶ����Ϣ ƽ̨�ͺ��ַ���

#define SOPTNUMEC 32        // ����ʶ����Ϣ ƽ̨�����ַ���
#define SOPTYC 32		    // ����ʶ����Ϣ ƽ̨�����ַ���
#define SOCOUNTRYC 32   	// ����ʶ����Ϣ �����ַ���

/* �״������Ϣ */
typedef struct __ESMSTATUS_MARK   
{

// ������Ϣ
	  char head;				         // ����ͷ

// ��ݱ�ʶ	
	  unsigned long lAutonum;			 //�ۺ�����

	  char cPlatNumber[SOPTNUMC];        //ƽ̨���
      char cEquipmentNumber[SOEQNUMC];   //�豸���
      char cEquipmentType[SOEQTYPEC];    //�豸����

      unsigned long lTargetNumber;       //Ŀ������ 

//������Ϣ
	 ZAI_FREQ stZaiPin;                  //��Ƶ��Ϣ�ṹ
	 CHONG_FREQ stChongPin;              //��Ƶ��Ϣ�ṹ
	 WIDTH_MSG stMaiKuan;                //������Ϣ�ṹ
	 AntennaScan_MSG stTianXianScan;     //����ɨ����Ϣ�ṹ
	 PulseFeature_MSG stMaiChongFeature; //����������Ϣ�ṹ
	 float fPulseExtent;                 //�������
	 long lSignalReachTime;              //�źŵ���ʱ��
	 float fReachAzimuth;                //���﷽λ
     float fElevationAngle;              //����

//ʶ����Ϣ
	 char cRadarPurpose[SORADPURC];      //�״���;
	 char cRadarName[SORADNAMEC];        //�״�����
	 float fThreatLevel;                 //��в�ȼ�0--7
	 float fERPower;                     //��Ч���书��
//	 char cPlatXinghao;                  //ƽ̨�ͺ�

	 unsigned short sPlatType;           //ƽ̨����   ('1'����F117�� '2' ����F118�� '3'����F119�� '4'����F120�� '5'����F121)
	 
	 char cPlatName[SOPTNUMEC];          //ƽ̨����  �ɻ� ���� ��ը�� ս����

	 char cDWAttribute;                  //��������
	 double dConfidence;                 //���Ŷ�
     char cCountry[SOCOUNTRYC];          //���ң�������

	 char cJfFlag;

}ESMSTATUS_MARK;
 

/* ͨ�������Ϣ */
typedef struct __COMSTATUS_MARK          //ͨ�������Ϣ 
{	

// ������Ϣ
	char head;				             //����ͷ

// ��ݱ�ʶ
	unsigned long lAutonum;			    //�ۺ�����

	char cPlatNumber[SOPTNUMC];          //ƽ̨���
    char cEquipmentNumber[SOEQNUMC];     //�豸���
    char cEquipmentType[SOEQTYPEC];      //�豸����

    unsigned long lTargetNumber;         //Ŀ������ 

//������Ϣ
	ZAI_FREQ stComZaiPin;                //��Ƶ��Ϣ�ṹ
	float fReachAzimuth;                 //���﷽λ
	float fElevationAngle;               //����
	unsigned long lSignalReachTime;      //�źŵ���ʱ��
   	float fPulseExtent;                  //������� 

//ʶ����Ϣ 
	unsigned char cSignalType;           //�ź�����
	char cModulationStyle;               //������ʽ     
	unsigned short sPlatType;            //ƽ̨����  F117  ('1'����F117�� '2' ����F118�� '3'����F119�� '4'����F120�� '5'����F121)
 
	char cPlatName[SOPTNUMEC];			 //ƽ̨����    
	char cDWAttribute;					 //��������
	double dConfidence;  			     //���Ŷ�
    char cCountry[SOCOUNTRYC];			 //���ң�������
	char cJfFlag;

}COMSTATUS_MARK;


/*�״ﺽ����IFF��Ϣ*/
typedef struct __TRACKSTATUS_MARK        //�״ﺽ����IFF��Ϣ  
{
// ������Ϣ
	char head;			                 // ����ͷ
// �����Ϣ
	unsigned long lAutonum;			     //�ۺ�����

	char cPlatNumber[SOPTNUMC];          //ƽ̨���
    char cEquipmentNumber[SOEQNUMC];     //�豸���
    char cEquipmentType[SOEQTYPEC];      //�豸����

    unsigned long lTargetNumber;         //Ŀ������
	 
//������Ϣ
	float fRange;                        //����
	float fAzimuth;                      //��λ
	float fElevationAngle;               //����
    float fCourse;                       //���Ժ���
	long lSignalReachTime;               //�źŵ���ʱ��
	double dTargetAZSpeed;               //Ŀ�귽λ���ٶ�
	double dTargetEAngleSpeed;           //Ŀ�����ǽ��ٶ�
	float fTX;                           //Ŀ��ռ�����X
	float fTY;                           //Ŀ��ռ�����Y
	float fTZ;                           //Ŀ��ռ�����Z
	double dTSpeedX;                     //Ŀ������ٶ�X
    double dTSpeedY;                     //Ŀ������ٶ�Y
    double dTSpeedZ;                     //Ŀ������ٶ�Z

    float fLonti;     //Ŀ�꾭��
	float fLati;      //Ŀ��γ��

//ʶ����Ϣ
	unsigned short sPlatType;            //ƽ̨����  F117  ('1'����F117�� '2' ����F118�� '3'����F119�� '4'����F120�� '5'����F121)
    char cPlatName[SOPTNUMEC];           //ƽ̨����  
    double dConfidence;                  //���Ŷ�
    char cDWAttribute;                   //�������� (IFF��Ϣ)
	char cJfFlag;                        //�Ƿ���������ںϱ�־��0��δ�ںϣ�1�����ں�

}TRACKSTATUS_MARK;

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