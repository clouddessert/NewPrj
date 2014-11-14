//#include "CooperativeMsg.h"
#include <vector>
using namespace std;

typedef struct __MIDENTIINFOR         //本舰识别结果结构体 
{	
	unsigned long lAutonum; 	         //综合批号
	//char *sPlatType;            //平台类型  F117  ('1'代表F117； '2' 代表F118； '3'代表F119； '4'代表F120； '5'代表F121)
	char sPlatType[32];              //平台型号
	double dConfidence;              //平台型号可信度
	char cDWAttribute[32];           //敌我属性 (IFF信息)
	double dDWConfidence;            //敌我可信度
}MIDENTIINFOR;


typedef vector<MIDENTIINFOR> VCT_MIDENTIINFOR_MSG;
typedef vector<double> VCT_CON;


//联合识别接口函数
void MultipleIdentify(VCT_COOPER_MSG& vctCooperMsg, VCT_MIDENTIINFOR_MSG& vctMidentiinforMsg);
