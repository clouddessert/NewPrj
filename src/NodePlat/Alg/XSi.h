
#include "../Comm Struct.h"
using namespace std;


// 雷达探测设备精度结构体
typedef struct _Accuracy_TRACE 
{
    float dirRd;          //径距精度     目标航迹的径距（米）
    float dirAz;          //方位精度     目标航迹的方位（弧度）
    float dirEz;          //俯仰精度     目标航迹的仰角（弧度）
	
}Accuracy_TRACE;

// 雷达侦查设备精度结构体ESM
typedef struct _Accuracy_ESM 
{
	float dirDoAz;		// 测向精度      ESM信号的到达方位（弧度）
	float dirFre;       // 测频精度      ESM信号的频率（GHz）
	float dirPa;        // 测幅精度      ESM信号的幅度 （V）
    float dirPzw;       // 测宽精度      ESM信号的脉冲宽度（us）
	float dirPri;       // 重复间隔精度  ESM信号的重复间隔（ms）;重复频率PRF=PRI的倒数
	float dirScan;      // 天线扫描精度  ESM信号的侦察雷达天线扫描周期（s）	
	
}Accuracy_ESM;

// 通信侦察设备精度结构体Com
typedef struct _Accuracy_COM
{
	float dirDoAz;      // 测向精度      COM信号的到达方位（弧度）
	float dirFre;       // 测频精度      COM信号的中心频率（MHz）
	float dirPa;        // 测幅精度      COM信号的幅度   （V） 
	float dirBand;      // 瞬时带宽精度  COM信号的信号带宽（MHz）
	
}Accuracy_COM;
//////////////////////////////////////////////////////////////
//               数据和特征融合
//      结果：1、用于更新协同识别的目标中涉及的各类信息
//            2、融合后的批号，统一用本舰上的原协同目标对应的各批号，包括合批号
//            3、下发给态势分析模块
/////////////////////////////////////////////////////////////

//航迹融合
typedef struct __FUS_TRACK
{
	double dFusTrackRd;                //目标航迹的径距（米）
	double dFusTrackAz;                //目标航迹的方位（弧度）
	double dFusTrackEz;                //目标航迹的仰角（弧度）
	double dFusTrackVx;                //目标航迹的X轴上的速度（米/秒）
	double dFusTrackVy;                //目标航迹的Y轴上的速度（米/秒）
	double dFusTrackVz;                //目标航迹的Z轴上的速度（米/秒）
	char cFusTrackRecogType;           //目标航迹的识别类型(用综合识别类型代替)
    double dFusTrackConfidence;        //目标航迹的识别可信度(用综合识别可信度代替)

}FUS_TRACK;

//ESM融合
typedef struct __FUS_ESM
{
	double dFusESMDOAz;                 //ESM信号的到达方位（弧度）
	double dFusESMFre;                  //ESM信号的频率（GHz）
	double dFusESMPA;                   //ESM信号的幅度
	double dFusESMPzw;                  //ESM信号的脉冲宽度（us）
	double dFusESMPRI;                  //ESM信号的重复间隔（ms）;重复频率PRF=PRI的倒数
	double dFusESMSCan;                 //ESM信号的侦察雷达天线扫描周期（s）
	char cFusESMRecogType;              //ESM信号的识别类型(用综合识别类型代替)
    double dFusESMConfidence;           //ESM信号的识别可信度(用综合识别可信度代替)

}FUS_ESM;

//COM融合
typedef struct __FUS_COM
{ 
	double dFusCOMDOAz;                //COM信号的到达方位（弧度）
	double dFusCOMFre;                 //COM信号的中心频率（MHz）
	double dFusCOMPA;                  //COM信号的幅度
	double dFusCOMBand;                //COM信号的信号带宽（MHz）
	double dFusCOMJPN;                 //COM信号的跳步次数
	char cFusCOMRecogType;             //COM信号的识别类型
    double dFusCOMConfidence;          //COM信号的识别可信度

}FUS_COM;


typedef struct __Request_Cooperative_Msg     //主舰请求协同的信息数据结构
{
	long int nStampTime;                     //发送请求信息时的当前时间 ，上述的当前时间可用返回信息的当前时间来代替	
//  VCT_TRACE_MSG vctTrace;                  //请求协同的航迹信息
	unsigned long lAutonum;
	TRACKSTATUS_MARK stTrace;
	VCT_ESM_MSG vctEsm;                      //是否要加?????????  当送出的信息只有ESM ，请求协同ESM信息
	VCT_COMM_MSG vctComm;                    //是否要加?????????  当送出的信息只有COM , 请求协同的COM信息   
    SHIP_POSITION stReqShipPosi;             //存放本舰经纬高
    int nCorrFlag;                           //请求信息的结构体是否找到相关联信息的标志


}Request_Cooperative_Msg;


///////////////////////////////////////////////////
///////////////////////////////////////////////////
//把容器换成数组，发送请求的信息结构
typedef struct __SendRequest_Msg     //需要发送的请求信息，主舰请求协同的信息数据结构
{
	long int num;                            //信息单元序号
    long int nStampTime;                     //发送请求信息时的当前时间 ，上述的当前时间可用返回信息的当前时间来代替
// 	char *ReceiveIp[20];                     //接收方IP地址
// 	char *SendIp[20];                        //发送方IP地址
	SHIP_POSITION stReqShipPosi;             //本舰经纬高
	
	unsigned long lAutomn;                   //合批号
	TRACKSTATUS_MARK stTrace;

	int nRequestEsmN;                         //本舰目标所含的ESM数
	int nRequestComN;                         //本舰目标所含的COM数
//ESM
	unsigned long lEsmTargetNumber[10];        //目标ESM批号
	double dEsmZaiPin[10];                     //载频信息结构..
	double dEsmMaiKuan[10];                    //脉宽信息结构..
	double dEsmTianXianScan[10];               //天线扫描信息结构..
	//double dEsmConfidence[10];                 //可信度

//COM
	unsigned long lComTargetNumber[10];			//目标COMM批号
    double dComZaiPin[10];                      //载频信息结构
	double dComPulseExtent[10];                 //脉冲幅度 
	//double dComConfidence[10];
//0909补充:
	double dComFre[10];                       // 中心频率(MHz)
	double dComBand[10];                      // 信号带宽(MHz)
	double dComJPN[10];                       // 跳步次数

	int nCorrFlag;                           //请求信息的结构体是否找到相关联信息的标志
}SendRequest_Msg;
typedef vector<SendRequest_Msg> VCT_SendRequest_Msg;
//发送返回信息的结构,结构体中有数组
typedef struct __SendBack_Msg
{
	long int num;                            //信息单元序号
    long int nStampTime;                     //发送请求信息时的当前时间 ，上述的当前时间可用返回信息的当前时间来代替
	char *SendIp[20];                        //发送方IP地址
	char *ReceiveIp[20];                     //接收方IP地址
	SHIP_POSITION stBackShipPosi;            //应答舰的经纬高

	unsigned long lAutonum;
    TRACKSTATUS_MARK stTrace;                //同一目标的航迹信息,只有一条航迹信息,包含目标的位置，目标类型，目标型号，可信度，目标批号

	int BackTraceN;                             //Trace信息总数
	int BackESMN;                               //ESM信息总数
	int BackCOMN;                               //COM信息总数
	//需补充//各雷达型号[数组]
    //各通信型号[数组]
// 	double dRange;                           //目标相对于邻舰的距离
// 	double dAzimuth;                         //目标相对于邻舰的方位
// 	double dElevationAngle;                  //目标相对于邻舰的仰角

//ESM
	unsigned long lEsmTargetNumber[10];        //目标批号
	double dEsmZaiPin[10];                     //载频信息结构..
	double dChongPin[10];                      //重频信息结构
	double dEsmMaiKuan[10];                    //脉宽信息结构..
	double dEsmTianXianScan[10];               //天线扫描信息结构..
//1011 改
    char sEsmPlatType[32][10];                    //F117,F118,F119
	double dEsmConfidence[10];                 //可信度
//COM
	//需补充//通信信号电平[数组]
	unsigned long lComTargetNumber[10];			//目标COMM批号
    double dComZaiPin[10];                      //载频信息结构
	double dComPulseExtent[10];                 //脉冲幅度 
	double dComFre[10];                       // 中心频率(MHz)
	double dComBand[10];                      // 信号带宽(MHz)
	double dComJPN[10];                       // 跳步次数
//1011改
	char sComPlatType[32][10];                     //F117,F118,F119
	double dComConfidence[10];                  //可信度
	
	int nCorrFlag;                            //是否找到关联信息的标志
}SendBack_Msg;
typedef vector<SendBack_Msg> VCT_SendBack_Msg;

///////////////////////////////////////////////////////
////////////////////////////////////////////////////////
typedef struct __BACK_Cooperative_Msg        //邻舰送给主舰协同信息的数据结构
{ 
    long int nStampTime;                     //发送返回信息的当前时间 
//  VCT_TRACE_MSG vctTrace;                  //同一目标下只有一条航迹信息,计数使用
	unsigned long lAutonum;
    TRACKSTATUS_MARK stTrace;                //同一目标的航迹信息,只有一条航迹信息
	VCT_ESM_MSG vctEsm;                      //同一目标的ESM信息
	VCT_COMM_MSG vctComm;                    //同一目标的COMM信息
// 	double dRange;                           //目标相对于邻舰的距离
// 	double dAzimuth;                         //目标相对于邻舰的方位
// 	double dElevationAngle;                  //目标相对于邻舰的仰角
	SHIP_POSITION stBackShipPosi;            //应答舰的经纬高
    int nCorrFlag;                           //是否找到关联信息的标志
	int BackESMN;                    //ESM信息总数
	int BackCOMN;                    //COM信息总数
	int BackTrackN;                  //航迹数
}BACK_Cooperative_Msg;


typedef vector<FUS_TRACK> VCT_FUS_TRACK;      //存储融合后的雷达探测信息 (航迹信息)
typedef vector<FUS_ESM> VCT_FUS_ESM;	     //存储融合后的雷达侦察信息 (根据关联系数，存储不同种类的侦查信息结构体)
typedef vector<FUS_COM> VCT_FUS_COM;         //存储融合后的通信侦查信息 (根据关联系数，存储不同种类的通信信息结构体)

typedef struct __Cooperative_FUSIDENTIINFOR  //协同后，融合信息与识别结果结构体
{
	unsigned long lAutonum; 	             //综合批号
	unsigned short sPlatType;                //平台类型  F117  (F117； F118； F119； F120； F121)
	double dConfidence;                      //可信度	
	FUS_TRACK stFusTrack;                    //存储融合后的雷达探测信息（航迹信息）
//	VCT_FUS_TRACK vctFusTrack;
	VCT_FUS_ESM vctFusEsm;                   //存储融合后的雷达侦察信息
    VCT_FUS_COM vctFusCom;                   //存储融合后的通信侦查信息                  

}Cooperative_FUSIDENTIINFOR;
/*
typedef struct __STR//方位聚类后，同方位数据结构(航迹信息每个结构体只有一条)
{
// 	float fReachAzimuth;    //到达方位
	int lAutonum;			//综合批号
	VCT_ESM_MSG VecEsm;
	VCT_COMM_MSG VecCom;
//	VCT_TRACE_MSG VecTrack;	
	TRACKSTATUS_MARK st_oneTrack;
}STR;
typedef vector<STR> STRVEC;	//存储同方位的各个辐射源信息


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

typedef vector<UNI_NUM> VCT_UNINUM_MSG;  //存储有航迹信息结构体
typedef vector<UNI_NOTRACE_NUM> VCT_UNINOTRACE_MSG;   //存储无航迹信息的结构体
*/
typedef struct __UNI_All_NUM //聚类后有编批和无编批数据结构
{
	VCT_UNINUM_MSG vctUnin;
	VCT_UNINOTRACE_MSG vctNoTraceUnin;
	VCT_COMM_MSG vctSingleCom;
	VCT_ESM_MSG vctSingleEsm;
	VCT_TRACE_MSG vctSingleTrace;
}UNI_All_NUM;



typedef vector<Request_Cooperative_Msg> VCT_Request_Cooperative_Msg; //存储本舰请求协同的信息结构体

typedef vector<BACK_Cooperative_Msg> VCT_BACK_Cooperative_Msg;  //存储邻舰送给主舰的协同信息结构体

typedef vector<Cooperative_FUSIDENTIINFOR> VCT_Cooperative_FUSIDENTIINFOR;  //存储协同后融合信息和识别结果的结构体

//本舰请求---协同识别接口函数  本舰请求协同的信息（对于聚类编批的结果），存放邻舰应答送给主舰协同的信息结构体的容器，存储协同后融合信息和识别结果结构体的容器。
//void GET_Cooperate_Recognition_Modul(VCT_Request_Cooperative_Msg& vctRequestCooperative, VCT_BACK_Cooperative_Msg& vctBackCooperative, VCT_Cooperative_FUSIDENTIINFOR& VctFusIdentify);

//邻舰请求协同--要求本舰接收到请求信息后，
               //1.查找合批信息<TRACE,ESM,COM>,找出同一目标的合批信息，发送给邻舰；
               //2.若合批信息<TRACE,ESM,COM>中不存在对应的信息，那么在未合批的信息（包括1.<ESM,COM>;  2.<ESM>; 3.<COM>）中查找对应的信息（同一类的方位角相同的）

//void COOP_Find_INFormation_TO_MainSHOP(SHIP_POSITION& stSelfPosi, UNI_All_NUM& stUniAll,VCT_Request_Cooperative_Msg& vctRequestCooperative, VCT_BACK_Cooperative_Msg& vctBackCooperative);

//主函数接口:
void CoopFind_Information_To_MainShip(UNI_All_NUM& stUniAll, SendRequest_Msg& stSendRequest, SendBack_Msg& stSendBackMsg);



// /*************************************************/
// /*************************************************/
// //根据请求信息中的综合批号来决定调用哪一种函数
// //(总批大于8000，即请求信息是聚类后有航迹的信息，调用函数1)
// //(总批号在7000到8000之间，即请求信息是聚类后无航迹的信息，调用函数2)
// //(总批号小于7000，即为目标批号，请求信息为未聚类的航迹信息，调用函数3)
// void ReqUnin_COOP_Find_Information_To_MainShip(SHIP_POSITION& stSelfPosi,UNI_All_NUM& stUniAll, VCT_Request_Cooperative_Msg::iterator& iteRequestMsg,/*VCT_Request_Cooperative_Msg& vctRequestCooperative,*/ VCT_BACK_Cooperative_Msg& vctBackCooperative);
// void ReqNoTraceUnin_COOP_Find_Information_To_MainShip(SHIP_POSITION& stSelfPosi,UNI_All_NUM& stUniAll, VCT_Request_Cooperative_Msg::iterator& iteRequestMsg,/*VCT_Request_Cooperative_Msg& vctRequestCooperative, */VCT_BACK_Cooperative_Msg& vctBackCooperative);
// void ReqSingleTrace_COOP_Find_Information_To_MainShip(SHIP_POSITION& stSelfPosi,UNI_All_NUM& stUniAll, VCT_Request_Cooperative_Msg::iterator & iteRequestMsg,/*VCT_Request_Cooperative_Msg& vctRequestCooperative,*/ VCT_BACK_Cooperative_Msg& vctBackCooperative);
// 
// // 本舰邻舰都有自身航迹信息时（即都存在距离方位俯仰角时），本舰邻舰经纬高都已知，输出邻舰观测到的目标在本舰上的坐标及相对于本舰的经纬高。
// void Get_Coordinate_Conversion_Module(double Rd1,double Az1,double Ez1,double Rd2,double Az2,double Ez2,double La1,double Ba1,double Ha1,
// 									  double La2,double Ba2,double Ha2,/*double *x1,double *y1,double *z1,*/double& Xt,double& Yt,double& Zt,double& Rdt,double& Azt,double& Ezt,double& SumCorr);
// 
// void Mf_SPA(double s, double t,double& corr); //s,t为相同类型的信息，进行集对分析，将返回的相关系数存入容器VctCorr中
// void Get_NO_SelfTrack_Coordinate_Conversion_Module(double Rd2,double Az2,double Ez2,double La1,double Ba1,double Ha1,
// 						  double La2,double Ba2,double Ha2,double& Xt,double& Yt,double& Zt);
// void Object_Radar_Transform(double Lt,double Bt,double Ht,double L0,double B0,double H0,double& rd,double& az,double& ez);