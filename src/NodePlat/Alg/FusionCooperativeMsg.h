#include <vector>
#include "XSi.h"
using namespace std;
//////// 0906 wanghaiying ///////////////////////////////////////////////////
//
//               数据和特征融合
/////////////////////////////////////////////////////////////

//假如主舰同时向N条邻舰请求信息，主舰收到N条邻舰的返回信息,需要将返回信息进行分类合并存放

//////// 2014 1016 wanghaiying ///////////////////////////////////////////////////
typedef struct __Cooperative_FUSIDENTIINFOR   //协同后，融合信息与识别结果结构体
{
    long int nStampTime;                     //发送请求信息时的当前时间 ，上述的当前时间可用返回信息的当前时间来代替	
	unsigned long lAutonum;

	unsigned short sPlatType;                //综合平台类型  F117  (F117； F118； F119； F120； F121)
	double dConfidence;                      //综合可信度

	TRACKSTATUS_MARK stFusTrack;            //存储融合后的雷达探测信息（航迹信息）
	VCT_ESM_MSG vctFusEsm;                  //存储融合后的雷达侦察信息
	VCT_COMM_MSG vctFusCom;                 //存储融合后的通信侦查信息   
}Cooperative_FUSIDENTIINFOR;

typedef vector<Cooperative_FUSIDENTIINFOR> VCT_Cooperative_FUSIDENTIINFOR;  //存储协同后融合信息和识别结果的结构体

///////////////////////////////////////////////////////////////////////////////////
///////////输入：本舰的请求信息，邻舰相应批号的返回信息(已经综合了不同邻舰返回的信息)
///////////输出：1--融合值，用此更新本舰协同目标的航迹信息，以及与之捆邦的相关ESM、COM各种信息
///////////      2--对于本舰的协同目标上缺少的相关信息，用融合的补（即协同取到互补作用）
///////////      3--融合结果一方面界面显示和更新、保存；另一方面：下发给态势分析模块 
////////////////////////////////////////////////////////////////////////////////////
void FusionCooperativeMsg(VCT_Request_Cooperative_Msg& vctReqMsg, VCT_BACK_Cooperative_Msg& vctBackMsg, VCT_Cooperative_FUSIDENTIINFOR& vctCoFusMsg);

