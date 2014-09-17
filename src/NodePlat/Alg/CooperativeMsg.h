#include "../Comm Struct.h"
/*#include "XSi.h"*/
using namespace std;
/*
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
typedef vector<Cooperative_FUSIDENTIINFOR> VCT_Cooperative_FUSIDENTIINFOR;  //存储协同后融合信息和识别结果的结构体
*/

typedef struct __Cooperative_Msg     //请求和返回信息汇总数据结构
{	
	unsigned long lAutonum;                  //请求信息的综合批号
    VCT_TRACE_MSG vctTrace;                  //存放请求和返回的航迹信息
	VCT_ESM_MSG vctEsm;                     
	VCT_COMM_MSG vctComm;   
}Cooperative_Msg;
typedef vector<Cooperative_Msg> VCT_COOPER_MSG;
//平台类型容器
typedef vector<char*> VCT_sPlatType;

//******************************************************************************************//
//           多舰协同查找返回信息部分     0831 why                                                   //

//********  输入：主舰请求信息                                              ****************//
//********        主舰自身的地理位置信息                                          **********//
//********  输出：返回信息                                                       **********// 
//******************************************************************************************//
//本舰请求邻舰协同,接收到邻舰发送的信息后,进行综合识别处理。
//void GET_CooperateMsg_Modul(SHIP_POSITION& stSelfPosi,VCT_Request_Cooperative_Msg& vctRequestCooperative, VCT_BACK_Cooperative_Msg& vctBackCooperative, VCT_COOPER_MSG& vctCooperMsg); 
void GET_CooperateMsg_Modul(/*SHIP_POSITION& stSelfPosi,*/VCT_Request_Cooperative_Msg& vctRequestCooperative, VCT_BACK_Cooperative_Msg& vctBackCooperative, VCT_COOPER_MSG& vctCooperMsg);

//void Mf_SPA(double s, double t,double& corr); //s,t为相同类型的信息，进行集对分析，将返回的相关系数存入容器VctCorr中