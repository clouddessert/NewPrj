#include <vector>
#include "XSi.h"
using namespace std;
//////// 0906 wanghaiying ///////////////////////////////////////////////////
//
//               ���ݺ������ں�
/////////////////////////////////////////////////////////////

//��������ͬʱ��N���ڽ�������Ϣ�������յ�N���ڽ��ķ�����Ϣ,��Ҫ��������Ϣ���з���ϲ����

//////// 2014 1016 wanghaiying ///////////////////////////////////////////////////
typedef struct __Cooperative_FUSIDENTIINFOR   //Эͬ���ں���Ϣ��ʶ�����ṹ��
{
    long int nStampTime;                     //����������Ϣʱ�ĵ�ǰʱ�� �������ĵ�ǰʱ����÷�����Ϣ�ĵ�ǰʱ��������	
	unsigned long lAutonum;

	unsigned short sPlatType;                //�ۺ�ƽ̨����  F117  (F117�� F118�� F119�� F120�� F121)
	double dConfidence;                      //�ۺϿ��Ŷ�

	TRACKSTATUS_MARK stFusTrack;            //�洢�ںϺ���״�̽����Ϣ��������Ϣ��
	VCT_ESM_MSG vctFusEsm;                  //�洢�ںϺ���״������Ϣ
	VCT_COMM_MSG vctFusCom;                 //�洢�ںϺ��ͨ�������Ϣ   
}Cooperative_FUSIDENTIINFOR;

typedef vector<Cooperative_FUSIDENTIINFOR> VCT_Cooperative_FUSIDENTIINFOR;  //�洢Эͬ���ں���Ϣ��ʶ�����Ľṹ��

///////////////////////////////////////////////////////////////////////////////////
///////////���룺������������Ϣ���ڽ���Ӧ���ŵķ�����Ϣ(�Ѿ��ۺ��˲�ͬ�ڽ����ص���Ϣ)
///////////�����1--�ں�ֵ���ô˸��±���ЭͬĿ��ĺ�����Ϣ���Լ���֮��������ESM��COM������Ϣ
///////////      2--���ڱ�����ЭͬĿ����ȱ�ٵ������Ϣ�����ںϵĲ�����Эͬȡ���������ã�
///////////      3--�ںϽ��һ���������ʾ�͸��¡����棻��һ���棺�·���̬�Ʒ���ģ�� 
////////////////////////////////////////////////////////////////////////////////////
void FusionCooperativeMsg(VCT_Request_Cooperative_Msg& vctReqMsg, VCT_BACK_Cooperative_Msg& vctBackMsg, VCT_Cooperative_FUSIDENTIINFOR& vctCoFusMsg);

