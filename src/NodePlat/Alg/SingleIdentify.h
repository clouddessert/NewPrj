#include "../Comm Struct.h"
#include <map>

// 雷达侦查设备精度结构体
typedef struct _Accuracy 
{
	float dirAcc;		// 测向精度
	
}Accuracy;

// typedef struct __STCLUSTER //聚类结果数据结构
// {
// 	TRACKSTATUS_MARK structTrace;//同方位航迹信息
// 	VCT_ESM_MSG vctEsm;          //同方位ESM信息
// 	VCT_COMM_MSG vctComm;        //同方位COMM信息
// }STCLUSTER;

typedef struct __UNI_NUM //有航迹编批结果数据结构
{
	unsigned long lAutonum;
	TRACKSTATUS_MARK structTrace;//同方位航迹信息
	VCT_ESM_MSG vctEsm;          //同方位ESM信息
	VCT_COMM_MSG vctComm;        //同方位COMM信息
}UNI_NUM;

typedef struct __UNI_NOTRACE_NUM //无航迹编批结果数据结构
{
	unsigned long lAutonum;
	VCT_ESM_MSG vctEsm;          //同方位ESM信息
	VCT_COMM_MSG vctComm;        //同方位COMM信息
}UNI_NOTRACE_NUM;

typedef struct __IDENTIINFOR         //本舰识别结果结构体 
{	
	unsigned long lAutonum; 	         //综合批号
//	unsigned short sPlatType;            //平台类型  F117  ('1'代表F117； '2' 代表F118； '3'代表F119； '4'代表F120； '5'代表F121)
    char sPlatType[32];                  //平台型号  F117  ('1'代表F117； '2' 代表F118； '3'代表F119； '4'代表F120； '5'代表F121)
	double dConfidence;                  //平台型号可信度
	char cDWAttribute[32];               //敌我属性 (IFF信息)
	double dDWConfidence;                //敌我可信度
}IDENTIINFOR;

//typedef map<unsigned long, STCLUSTER> MAP_CLUSTER;
typedef vector<UNI_NUM> VCT_UNINUM_MSG;
typedef vector<UNI_NOTRACE_NUM> VCT_UNINOTRACE_MSG;
typedef vector<IDENTIINFOR> VCT_IDENTIINFOR_MSG;



//本舰识别接口函数
void SingleIdentify(ALL_MSG_INPUT& AllMessage, VCT_UNINUM_MSG& UniMsg, VCT_UNINOTRACE_MSG& UniNoTrace, VCT_IDENTIINFOR_MSG& IdentifyVec, VCT_TRACE_MSG& SingleTrace, VCT_ESM_MSG& SingleEsm, VCT_COMM_MSG& SingleComm);

//void SingleIdentify(ALL_MSG_INPUT& AllMessage, VCT_UNINUM_MSG& UniMsg, VCT_UNINOTRACE_MSG& UniNoTrace, VCT_IDENTIINFOR_MSG& IdentifyVec);

//void SingleIdentify(ALL_MSG_INPUT& AllMessage, VCT_UNINUM_MSG& MapUni, VCT_IDENTIINFOR_MSG& IdentifyVec); 
//void SingleIdentify(ALL_MSG_INPUT& AllMessage, MAP_CLUSTER& MapUni, VCT_IDENTIINFOR_MSG& IdentifyVec);
//VCT_IDENTIINFOR_MSG* SingleIdentify(ALL_MSG_INPUT* pIn, MAP* pOut);
//VCT_IDENTIINFOR_MSG* SingleIdentify(VCT_ESM_MSG* pEsmStatusVec, VCT_COMM_MSG* pComStatusVec, VCT_TRACE_MSG* pTrackStatusVec);