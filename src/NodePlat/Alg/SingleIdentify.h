#include "../Comm Struct.h"

// �״�����豸���Ƚṹ��
typedef struct _Accuracy 
{
	float dirAcc;		// ���򾫶�
	
}Accuracy;

typedef struct __IDENTIINFOR         //����ʶ��ṹ�� 
{	
	// ��ݱ�ʶ	
	unsigned long lAutonum; 	         //�ۺ�����
	// 	unsigned short nPlatNumber;         //ƽ̨���
	// 	unsigned short nEquipmentNumber;    //�豸���
	// 	unsigned char cEquipmentType;       //�豸����
	//	unsigned long lTargetNumber;        //Ŀ������ 	
	//������Ϣ
	// 	ZAI_FREQ stZaiPin;                  //��Ƶ��Ϣ�ṹ
	// 	CHONG_FREQ stChongPin;              //��Ƶ��Ϣ�ṹ
	// 	WIDTH_MSG stMaiKuan;                //������Ϣ�ṹ
	// 	AntennaScan_MSG stTianXianScan;     //����ɨ����Ϣ�ṹ
	// 	PulseFeature_MSG stMaiChongFeature; //����������Ϣ�ṹ
	// 	short nPulseExtent;                 //�������
	// 	long lSignalReachTime;              //�źŵ���ʱ��
	//	float fReachAzimuth;                //���﷽λ
	//  	float fElevationAngle;              //����
	// 	float fRange;                        //����
	//     float fCourse;                       //���Ժ���
	// 	double dTargetAZSpeed;               //Ŀ�귽λ���ٶ�
	// 	double dTargetEAngleSpeed;           //Ŀ�����ǽ��ٶ�
	// 	float fTX;                           //Ŀ��ռ�����X
	// 	float fTY;                           //Ŀ��ռ�����Y
	// 	float fTZ;                           //Ŀ��ռ�����Z
	// 	double dTSpeedX;                     //Ŀ������ٶ�X
	//     double dTSpeedY;                     //Ŀ������ٶ�Y
	//     double dTSpeedZ;                     //Ŀ������ٶ�Z
	//ʶ����Ϣ
	// 	unsigned char cSignalType;           //�ź�����
	// 	char cModulationStyle;               //������ʽ 
	// 	char cRadarPurpose;                 //�״���;
	// 	char cRadarName;                    //�״�����
	// 	char cThreatLevel;                  //��в�ȼ�
	// 	float fERPower;                     //��Ч���书��
//	char *pPlatType;                 //ƽ̨����
	unsigned short sPlatType;            //ƽ̨����  F117  ('1'����F117�� '2' ����F118�� '3'����F119�� '4'����F120�� '5'����F121)
 
	// 	char cPlatXinghao;                  //ƽ̨�ͺ�
	// 	char cPlatName;                     //ƽ̨����
	// 	char cDWAttribute;                  //��������
	double dConfidence;                   //���Ŷ�
	//	unsigned char cCountry;             //���ң�������  
	
}IDENTIINFOR;

typedef vector<IDENTIINFOR> VCT_IDENTIINFOR_MSG;//�洢����ʶ����Ϣ

//����ʶ��ӿں���
VCT_IDENTIINFOR_MSG* SingleIdentify(VCT_ESM_MSG* pEsmStatusVec, VCT_COMM_MSG* pComStatusVec, VCT_TRACE_MSG* pTrackStatusVec);