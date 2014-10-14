
#include "../Comm Struct.h"
using namespace std;


// �״�̽���豸���Ƚṹ��
typedef struct _Accuracy_TRACE 
{
    float dirRd;          //���ྫ��     Ŀ�꺽���ľ��ࣨ�ף�
    float dirAz;          //��λ����     Ŀ�꺽���ķ�λ�����ȣ�
    float dirEz;          //��������     Ŀ�꺽�������ǣ����ȣ�
	
}Accuracy_TRACE;

// �״�����豸���Ƚṹ��ESM
typedef struct _Accuracy_ESM 
{
	float dirDoAz;		// ���򾫶�      ESM�źŵĵ��﷽λ�����ȣ�
	float dirFre;       // ��Ƶ����      ESM�źŵ�Ƶ�ʣ�GHz��
	float dirPa;        // �������      ESM�źŵķ��� ��V��
    float dirPzw;       // �����      ESM�źŵ������ȣ�us��
	float dirPri;       // �ظ��������  ESM�źŵ��ظ������ms��;�ظ�Ƶ��PRF=PRI�ĵ���
	float dirScan;      // ����ɨ�辫��  ESM�źŵ�����״�����ɨ�����ڣ�s��	
	
}Accuracy_ESM;

// ͨ������豸���Ƚṹ��Com
typedef struct _Accuracy_COM
{
	float dirDoAz;      // ���򾫶�      COM�źŵĵ��﷽λ�����ȣ�
	float dirFre;       // ��Ƶ����      COM�źŵ�����Ƶ�ʣ�MHz��
	float dirPa;        // �������      COM�źŵķ���   ��V�� 
	float dirBand;      // ˲ʱ������  COM�źŵ��źŴ���MHz��
	
}Accuracy_COM;
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


typedef struct __Request_Cooperative_Msg     //��������Эͬ����Ϣ���ݽṹ
{
	long int nStampTime;                     //����������Ϣʱ�ĵ�ǰʱ�� �������ĵ�ǰʱ����÷�����Ϣ�ĵ�ǰʱ��������	
//  VCT_TRACE_MSG vctTrace;                  //����Эͬ�ĺ�����Ϣ
	unsigned long lAutonum;
	TRACKSTATUS_MARK stTrace;
	VCT_ESM_MSG vctEsm;                      //�Ƿ�Ҫ��?????????  ���ͳ�����Ϣֻ��ESM ������ЭͬESM��Ϣ
	VCT_COMM_MSG vctComm;                    //�Ƿ�Ҫ��?????????  ���ͳ�����Ϣֻ��COM , ����Эͬ��COM��Ϣ   
    SHIP_POSITION stReqShipPosi;             //��ű�����γ��
    int nCorrFlag;                           //������Ϣ�Ľṹ���Ƿ��ҵ��������Ϣ�ı�־


}Request_Cooperative_Msg;


///////////////////////////////////////////////////
///////////////////////////////////////////////////
//�������������飬�����������Ϣ�ṹ
typedef struct __SendRequest_Msg     //��Ҫ���͵�������Ϣ����������Эͬ����Ϣ���ݽṹ
{
	long int num;                            //��Ϣ��Ԫ���
    long int nStampTime;                     //����������Ϣʱ�ĵ�ǰʱ�� �������ĵ�ǰʱ����÷�����Ϣ�ĵ�ǰʱ��������
// 	char *ReceiveIp[20];                     //���շ�IP��ַ
// 	char *SendIp[20];                        //���ͷ�IP��ַ
	SHIP_POSITION stReqShipPosi;             //������γ��
	
	unsigned long lAutomn;                   //������
	TRACKSTATUS_MARK stTrace;

	int nRequestEsmN;                         //����Ŀ��������ESM��
	int nRequestComN;                         //����Ŀ��������COM��
//ESM
	unsigned long lEsmTargetNumber[10];        //Ŀ��ESM����
	double dEsmZaiPin[10];                     //��Ƶ��Ϣ�ṹ..
	double dEsmMaiKuan[10];                    //������Ϣ�ṹ..
	double dEsmTianXianScan[10];               //����ɨ����Ϣ�ṹ..
	//double dEsmConfidence[10];                 //���Ŷ�

//COM
	unsigned long lComTargetNumber[10];			//Ŀ��COMM����
    double dComZaiPin[10];                      //��Ƶ��Ϣ�ṹ
	double dComPulseExtent[10];                 //������� 
	//double dComConfidence[10];
//0909����:
	double dComFre[10];                       // ����Ƶ��(MHz)
	double dComBand[10];                      // �źŴ���(MHz)
	double dComJPN[10];                       // ��������

	int nCorrFlag;                           //������Ϣ�Ľṹ���Ƿ��ҵ��������Ϣ�ı�־
}SendRequest_Msg;
typedef vector<SendRequest_Msg> VCT_SendRequest_Msg;
//���ͷ�����Ϣ�Ľṹ,�ṹ����������
typedef struct __SendBack_Msg
{
	long int num;                            //��Ϣ��Ԫ���
    long int nStampTime;                     //����������Ϣʱ�ĵ�ǰʱ�� �������ĵ�ǰʱ����÷�����Ϣ�ĵ�ǰʱ��������
	char *SendIp[20];                        //���ͷ�IP��ַ
	char *ReceiveIp[20];                     //���շ�IP��ַ
	SHIP_POSITION stBackShipPosi;            //Ӧ�𽢵ľ�γ��

	unsigned long lAutonum;
    TRACKSTATUS_MARK stTrace;                //ͬһĿ��ĺ�����Ϣ,ֻ��һ��������Ϣ,����Ŀ���λ�ã�Ŀ�����ͣ�Ŀ���ͺţ����Ŷȣ�Ŀ������

	int BackTraceN;                             //Trace��Ϣ����
	int BackESMN;                               //ESM��Ϣ����
	int BackCOMN;                               //COM��Ϣ����
	//�貹��//���״��ͺ�[����]
    //��ͨ���ͺ�[����]
// 	double dRange;                           //Ŀ��������ڽ��ľ���
// 	double dAzimuth;                         //Ŀ��������ڽ��ķ�λ
// 	double dElevationAngle;                  //Ŀ��������ڽ�������

//ESM
	unsigned long lEsmTargetNumber[10];        //Ŀ������
	double dEsmZaiPin[10];                     //��Ƶ��Ϣ�ṹ..
	double dChongPin[10];                      //��Ƶ��Ϣ�ṹ
	double dEsmMaiKuan[10];                    //������Ϣ�ṹ..
	double dEsmTianXianScan[10];               //����ɨ����Ϣ�ṹ..
//1011 ��
    char sEsmPlatType[32][10];                    //F117,F118,F119
	double dEsmConfidence[10];                 //���Ŷ�
//COM
	//�貹��//ͨ���źŵ�ƽ[����]
	unsigned long lComTargetNumber[10];			//Ŀ��COMM����
    double dComZaiPin[10];                      //��Ƶ��Ϣ�ṹ
	double dComPulseExtent[10];                 //������� 
	double dComFre[10];                       // ����Ƶ��(MHz)
	double dComBand[10];                      // �źŴ���(MHz)
	double dComJPN[10];                       // ��������
//1011��
	char sComPlatType[32][10];                     //F117,F118,F119
	double dComConfidence[10];                  //���Ŷ�
	
	int nCorrFlag;                            //�Ƿ��ҵ�������Ϣ�ı�־
}SendBack_Msg;
typedef vector<SendBack_Msg> VCT_SendBack_Msg;

///////////////////////////////////////////////////////
////////////////////////////////////////////////////////
typedef struct __BACK_Cooperative_Msg        //�ڽ��͸�����Эͬ��Ϣ�����ݽṹ
{ 
    long int nStampTime;                     //���ͷ�����Ϣ�ĵ�ǰʱ�� 
//  VCT_TRACE_MSG vctTrace;                  //ͬһĿ����ֻ��һ��������Ϣ,����ʹ��
	unsigned long lAutonum;
    TRACKSTATUS_MARK stTrace;                //ͬһĿ��ĺ�����Ϣ,ֻ��һ��������Ϣ
	VCT_ESM_MSG vctEsm;                      //ͬһĿ���ESM��Ϣ
	VCT_COMM_MSG vctComm;                    //ͬһĿ���COMM��Ϣ
// 	double dRange;                           //Ŀ��������ڽ��ľ���
// 	double dAzimuth;                         //Ŀ��������ڽ��ķ�λ
// 	double dElevationAngle;                  //Ŀ��������ڽ�������
	SHIP_POSITION stBackShipPosi;            //Ӧ�𽢵ľ�γ��
    int nCorrFlag;                           //�Ƿ��ҵ�������Ϣ�ı�־
	int BackESMN;                    //ESM��Ϣ����
	int BackCOMN;                    //COM��Ϣ����
	int BackTrackN;                  //������
}BACK_Cooperative_Msg;


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
/*
typedef struct __STR//��λ�����ͬ��λ���ݽṹ(������Ϣÿ���ṹ��ֻ��һ��)
{
// 	float fReachAzimuth;    //���﷽λ
	int lAutonum;			//�ۺ�����
	VCT_ESM_MSG VecEsm;
	VCT_COMM_MSG VecCom;
//	VCT_TRACE_MSG VecTrack;	
	TRACKSTATUS_MARK st_oneTrack;
}STR;
typedef vector<STR> STRVEC;	//�洢ͬ��λ�ĸ�������Դ��Ϣ


typedef struct __UNI_NUM //�к�������������ݽṹ
{
	unsigned long lAutonum;
	TRACKSTATUS_MARK structTrace;//ͬ��λ������Ϣ
	VCT_ESM_MSG vctEsm;          //ͬ��λESM��Ϣ
	VCT_COMM_MSG vctComm;        //ͬ��λCOMM��Ϣ
}UNI_NUM;

typedef struct __UNI_NOTRACE_NUM //�޺�������������ݽṹ
{
	unsigned long lAutonum;
	VCT_ESM_MSG vctEsm;          //ͬ��λESM��Ϣ
	VCT_COMM_MSG vctComm;        //ͬ��λCOMM��Ϣ
}UNI_NOTRACE_NUM;

typedef vector<UNI_NUM> VCT_UNINUM_MSG;  //�洢�к�����Ϣ�ṹ��
typedef vector<UNI_NOTRACE_NUM> VCT_UNINOTRACE_MSG;   //�洢�޺�����Ϣ�Ľṹ��
*/
typedef struct __UNI_All_NUM //������б������ޱ������ݽṹ
{
	VCT_UNINUM_MSG vctUnin;
	VCT_UNINOTRACE_MSG vctNoTraceUnin;
	VCT_COMM_MSG vctSingleCom;
	VCT_ESM_MSG vctSingleEsm;
	VCT_TRACE_MSG vctSingleTrace;
}UNI_All_NUM;



typedef vector<Request_Cooperative_Msg> VCT_Request_Cooperative_Msg; //�洢��������Эͬ����Ϣ�ṹ��

typedef vector<BACK_Cooperative_Msg> VCT_BACK_Cooperative_Msg;  //�洢�ڽ��͸�������Эͬ��Ϣ�ṹ��

typedef vector<Cooperative_FUSIDENTIINFOR> VCT_Cooperative_FUSIDENTIINFOR;  //�洢Эͬ���ں���Ϣ��ʶ�����Ľṹ��

//��������---Эͬʶ��ӿں���  ��������Эͬ����Ϣ�����ھ�������Ľ����������ڽ�Ӧ���͸�����Эͬ����Ϣ�ṹ����������洢Эͬ���ں���Ϣ��ʶ�����ṹ���������
//void GET_Cooperate_Recognition_Modul(VCT_Request_Cooperative_Msg& vctRequestCooperative, VCT_BACK_Cooperative_Msg& vctBackCooperative, VCT_Cooperative_FUSIDENTIINFOR& VctFusIdentify);

//�ڽ�����Эͬ--Ҫ�󱾽����յ�������Ϣ��
               //1.���Һ�����Ϣ<TRACE,ESM,COM>,�ҳ�ͬһĿ��ĺ�����Ϣ�����͸��ڽ���
               //2.��������Ϣ<TRACE,ESM,COM>�в����ڶ�Ӧ����Ϣ����ô��δ��������Ϣ������1.<ESM,COM>;  2.<ESM>; 3.<COM>���в��Ҷ�Ӧ����Ϣ��ͬһ��ķ�λ����ͬ�ģ�

//void COOP_Find_INFormation_TO_MainSHOP(SHIP_POSITION& stSelfPosi, UNI_All_NUM& stUniAll,VCT_Request_Cooperative_Msg& vctRequestCooperative, VCT_BACK_Cooperative_Msg& vctBackCooperative);

//�������ӿ�:
void CoopFind_Information_To_MainShip(UNI_All_NUM& stUniAll, SendRequest_Msg& stSendRequest, SendBack_Msg& stSendBackMsg);



// /*************************************************/
// /*************************************************/
// //����������Ϣ�е��ۺ�����������������һ�ֺ���
// //(��������8000����������Ϣ�Ǿ�����к�������Ϣ�����ú���1)
// //(��������7000��8000֮�䣬��������Ϣ�Ǿ�����޺�������Ϣ�����ú���2)
// //(������С��7000����ΪĿ�����ţ�������ϢΪδ����ĺ�����Ϣ�����ú���3)
// void ReqUnin_COOP_Find_Information_To_MainShip(SHIP_POSITION& stSelfPosi,UNI_All_NUM& stUniAll, VCT_Request_Cooperative_Msg::iterator& iteRequestMsg,/*VCT_Request_Cooperative_Msg& vctRequestCooperative,*/ VCT_BACK_Cooperative_Msg& vctBackCooperative);
// void ReqNoTraceUnin_COOP_Find_Information_To_MainShip(SHIP_POSITION& stSelfPosi,UNI_All_NUM& stUniAll, VCT_Request_Cooperative_Msg::iterator& iteRequestMsg,/*VCT_Request_Cooperative_Msg& vctRequestCooperative, */VCT_BACK_Cooperative_Msg& vctBackCooperative);
// void ReqSingleTrace_COOP_Find_Information_To_MainShip(SHIP_POSITION& stSelfPosi,UNI_All_NUM& stUniAll, VCT_Request_Cooperative_Msg::iterator & iteRequestMsg,/*VCT_Request_Cooperative_Msg& vctRequestCooperative,*/ VCT_BACK_Cooperative_Msg& vctBackCooperative);
// 
// // �����ڽ�������������Ϣʱ���������ھ��뷽λ������ʱ���������ڽ���γ�߶���֪������ڽ��۲⵽��Ŀ���ڱ����ϵ����꼰����ڱ����ľ�γ�ߡ�
// void Get_Coordinate_Conversion_Module(double Rd1,double Az1,double Ez1,double Rd2,double Az2,double Ez2,double La1,double Ba1,double Ha1,
// 									  double La2,double Ba2,double Ha2,/*double *x1,double *y1,double *z1,*/double& Xt,double& Yt,double& Zt,double& Rdt,double& Azt,double& Ezt,double& SumCorr);
// 
// void Mf_SPA(double s, double t,double& corr); //s,tΪ��ͬ���͵���Ϣ�����м��Է����������ص����ϵ����������VctCorr��
// void Get_NO_SelfTrack_Coordinate_Conversion_Module(double Rd2,double Az2,double Ez2,double La1,double Ba1,double Ha1,
// 						  double La2,double Ba2,double Ha2,double& Xt,double& Yt,double& Zt);
// void Object_Radar_Transform(double Lt,double Bt,double Ht,double L0,double B0,double H0,double& rd,double& az,double& ez);