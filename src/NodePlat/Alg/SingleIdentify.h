#include "../Comm Struct.h"
#include <map>

// �״�����豸���Ƚṹ��
typedef struct _Accuracy 
{
	float dirAcc;		// ���򾫶�
	
}Accuracy;

// typedef struct __STCLUSTER //���������ݽṹ
// {
// 	TRACKSTATUS_MARK structTrace;//ͬ��λ������Ϣ
// 	VCT_ESM_MSG vctEsm;          //ͬ��λESM��Ϣ
// 	VCT_COMM_MSG vctComm;        //ͬ��λCOMM��Ϣ
// }STCLUSTER;

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

typedef struct __IDENTIINFOR         //����ʶ�����ṹ�� 
{	
	unsigned long lAutonum; 	         //�ۺ�����
//	unsigned short sPlatType;            //ƽ̨����  F117  ('1'����F117�� '2' ����F118�� '3'����F119�� '4'����F120�� '5'����F121)
    char sPlatType[32];                  //ƽ̨�ͺ�  F117  ('1'����F117�� '2' ����F118�� '3'����F119�� '4'����F120�� '5'����F121)
	double dConfidence;                  //ƽ̨�ͺſ��Ŷ�
	char cDWAttribute[32];               //�������� (IFF��Ϣ)
	double dDWConfidence;                //���ҿ��Ŷ�
}IDENTIINFOR;

//typedef map<unsigned long, STCLUSTER> MAP_CLUSTER;
typedef vector<UNI_NUM> VCT_UNINUM_MSG;
typedef vector<UNI_NOTRACE_NUM> VCT_UNINOTRACE_MSG;
typedef vector<IDENTIINFOR> VCT_IDENTIINFOR_MSG;



//����ʶ��ӿں���
void SingleIdentify(ALL_MSG_INPUT& AllMessage, VCT_UNINUM_MSG& UniMsg, VCT_UNINOTRACE_MSG& UniNoTrace, VCT_IDENTIINFOR_MSG& IdentifyVec, VCT_TRACE_MSG& SingleTrace, VCT_ESM_MSG& SingleEsm, VCT_COMM_MSG& SingleComm);

//void SingleIdentify(ALL_MSG_INPUT& AllMessage, VCT_UNINUM_MSG& UniMsg, VCT_UNINOTRACE_MSG& UniNoTrace, VCT_IDENTIINFOR_MSG& IdentifyVec);

//void SingleIdentify(ALL_MSG_INPUT& AllMessage, VCT_UNINUM_MSG& MapUni, VCT_IDENTIINFOR_MSG& IdentifyVec); 
//void SingleIdentify(ALL_MSG_INPUT& AllMessage, MAP_CLUSTER& MapUni, VCT_IDENTIINFOR_MSG& IdentifyVec);
//VCT_IDENTIINFOR_MSG* SingleIdentify(ALL_MSG_INPUT* pIn, MAP* pOut);
//VCT_IDENTIINFOR_MSG* SingleIdentify(VCT_ESM_MSG* pEsmStatusVec, VCT_COMM_MSG* pComStatusVec, VCT_TRACE_MSG* pTrackStatusVec);