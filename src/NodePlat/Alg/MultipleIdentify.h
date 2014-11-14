//#include "CooperativeMsg.h"
#include <vector>
using namespace std;

typedef struct __MIDENTIINFOR         //����ʶ�����ṹ�� 
{	
	unsigned long lAutonum; 	         //�ۺ�����
	//char *sPlatType;            //ƽ̨����  F117  ('1'����F117�� '2' ����F118�� '3'����F119�� '4'����F120�� '5'����F121)
	char sPlatType[32];              //ƽ̨�ͺ�
	double dConfidence;              //ƽ̨�ͺſ��Ŷ�
	char cDWAttribute[32];           //�������� (IFF��Ϣ)
	double dDWConfidence;            //���ҿ��Ŷ�
}MIDENTIINFOR;


typedef vector<MIDENTIINFOR> VCT_MIDENTIINFOR_MSG;
typedef vector<double> VCT_CON;


//����ʶ��ӿں���
void MultipleIdentify(VCT_COOPER_MSG& vctCooperMsg, VCT_MIDENTIINFOR_MSG& vctMidentiinforMsg);
