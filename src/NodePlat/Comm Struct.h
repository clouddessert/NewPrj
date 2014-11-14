#ifndef __COMM_STRUCT
#define __COMM_STRUCT

#pragma warning(disable : 4786)
#include <vector>
#include <map>
using namespace std;
typedef vector<int> VCT_INT;
typedef vector<VCT_INT> VV_INT;
typedef vector<double> VCT_DOUBLE;
typedef vector<VCT_DOUBLE> VV_DOUBLE;

typedef struct __SHIP_POSITION           //舰的经纬高
{
	double dLonti;
	double dLati; 
	double dHeight;

}SHIP_POSITION;

typedef struct _POSITION
{
	double dx;
	double dy;
	double dz;
}TARGET_POSITION;

typedef vector<TARGET_POSITION> VCT_POSITION;		//舰船的x，y，z三个方向

/* 雷达侦查信息 */
typedef struct __ESMSTATUS_MARK   
{

	// 报文信息
	char head;				         // 报文头
	// 身份标识	
	unsigned long lAutonum;			 //综合批号
	char cPlatNumber[32];              //平台编号
	char cEquipmentNumber[32];         //设备编号
	char cEquipmentType[32];           //设备类型
	unsigned long lTargetNumber;       //目标批号 
	
	double dZaiPin;                     //载频信息结构
	double dChongPin;                   //重频信息结构
	double dMaiKuan;                    //脉宽信息结构
	double dTianXianScan;               //天线扫描信息结构（天线扫描周期）
	double dMaiChongFeature;            //脉冲特征信息结构（脉冲频率）
	double dPulseExtent;                //脉冲幅度
	long lSignalReachTime;              //信号到达时间
	double dReachAzimuth;               //到达方位
	double dElevationAngle;             //仰角
	
	//识别信息
	char cRadarPurpose[32];             //雷达用途
	char cRadarName[32];                //雷达名称
	double dThreatLevel;                //威胁等级0--7
	double dERPower;                    //有效辐射功率
	// unsigned short sPlatType;             //平台类型   (F117； F118； 'F119； F120；F121)
	char sPlatType[32];                 //平台型号   (F117； F118； 'F119； F120；F121)
	char cPlatName[32];                 //平台名称  飞机 导弹 轰炸机 战斗机
	double dConfidence;                 //平台型号可信度
    char cDWAttribute[32];              //敌我属性 (IFF信息)
	double dDWConfidence;               //敌我可信度
	char cCountry[32];                  //国家（地区）
	
	unsigned long lJfFlag;               //聚类标记
	unsigned long lFlag;                 //累加标记
	//1016补充
	unsigned long lFusFlag;                //融合查找标记

	//10.20新增，ESM基本事件，模板号
	int nESMEvt;                         //ESM基本事件
	int nModel;                          //模板号

}ESMSTATUS_MARK;
 

/* 通信侦查信息 */
typedef struct __COMSTATUS_MARK           //通信侦查信息 
{	

// 报文信息
	char head;				             //报文头
// 身份标识
	unsigned long lAutonum;			     //综合批号
	char cPlatNumber[32];                //平台编号
    char cEquipmentNumber[32];           //设备编号
    char cEquipmentType[32];             //设备类型
    unsigned long lTargetNumber;         //目标批号 
// 测量信息
    double dComZaiPin;                   //载频信息结构
	double dReachAzimuth;                //到达方位
	double dElevationAngle;              //仰角
	unsigned long lSignalReachTime;      //信号到达时间
   	double dPulseExtent;                 //脉冲幅度 
// 0909补充:
    double dComFre;                       // 中心频率(MHz)
	double dComBand;                      // 信号带宽(MHz)
	double dComJPN;                       // 跳步次数
//识别信息 
    char cSignalType[32];                 //信号类型
	char cModulationStyle[32];            //调制样式     
    char sPlatType[32];                   //平台型号   (F117； F118； 'F119； F120；F121)
	char cPlatName[32];			          //平台名称    
    double dConfidence;                  //平台型号可信度
    char cDWAttribute[32];               //敌我属性 (IFF信息)
	double dDWConfidence;                //敌我可信度
    char cCountry[32];			          //国家（地区）
	unsigned long lJfFlag;                //聚类标记
	unsigned long lFlag;                  //累加标记
//1016补充
	unsigned long lFusFlag;                //融合查找标记

	//10.20新增，COM基本事件，模板号
	int nCOMEvt;                          //COM基本事件
	int nModel;                           //COM模板号

}COMSTATUS_MARK;

// 1战斗机、2 轰炸机、3歼击机 、攻击机 （认为属1类）
// 4预警机、   （认为属2类）
// 5侦察机、6干扰机7 直升机(包括反潜机、无人机、不明)   （认为属3类）
// 8 舰艇             （属4类）
// 9战术导弹、（属5类）
// 10制导武器  （属6类）

/*雷达航迹和IFF信息*/
typedef struct __TRACKSTATUS_MARK        //雷达航迹和IFF信息  
{
// 报文信息
	char head;			                 // 报文头
// 身份信息
	unsigned long lAutonum;			     //综合批号
	char cPlatNumber[32];                //平台编号
    char cEquipmentNumber[32];           //设备编号
    char cEquipmentType[32];             //设备类型
	int nTgtType;                        //目标类型  10.21添加，按上面的6个大类区分
    unsigned long lTargetNumber;         //目标批号	 
//测量信息
	double dRange;                        //距离
	double dAzimuth;                      //方位
	double dElevationAngle;               //仰角
//1020 态势
	double dHeight;                       //高度
	double dVSpeed;                       //速度
    double dAddSpeed;                     //加速度
	double dThreatLevel;                  //威胁等级0--7
	double dThrDg;                        //综合威胁度
	int nTrackEvent;                      //航迹基本事件
	int nModel;                           //模板号
	int nRdChEvt;                         //径距变化事件
	int nHtChEvt;                         //高度变化事件
	int nVSChEvt;                         //速度变化事件
	int nAddVSChEvt;                      //加速度变化事件
	int nCuChEvt;                         //航向变化事件
    double dCourse;                       //绝对航向
	long lSignalReachTime;                //信号到达时间
	double dTargetAZSpeed;                //目标方位角速度
	double dTargetEAngleSpeed;            //目标仰角角速度
    double dTX;                           //目标空间坐标X
	double dTY;                           //目标空间坐标Y
	double dTZ;                           //目标空间坐标Z
	double dTSpeedX;                      //目标绝对速度X
    double dTSpeedY;                      //目标绝对速度Y
    double dTSpeedZ;                      //目标绝对速度Z
	double dLonti;                        //目标经度
	double dLati;                         //目标纬度
        double dObjHeight;		      //目标高度 
	//识别信息
    char sPlatType[32];					 //平台型号   (F117； F118； 'F119； F120；F121)	
	char cPlatName[32];                  //平台名称  
    double dConfidence;                  //平台型号可信度
    char cDWAttribute[32];               //敌我属性 (IFF信息)
	double dDWConfidence;                //敌我可信度
	unsigned long lJfFlag;               //是否进行数据融合标志，0：未融合，1：已融合
	unsigned long lFlag;                 //累加标记
//1016补充
	unsigned long lFusFlag;                //融合查找标记


}TRACKSTATUS_MARK;

typedef vector<SHIP_POSITION> VCT_SHIP_POSITION; //存储各舰的GPS信息
typedef vector<ESMSTATUS_MARK> VCT_ESM_MSG;	//存储雷达侦察信息
typedef vector<COMSTATUS_MARK> VCT_COMM_MSG; //存储通信侦查信息
typedef vector<TRACKSTATUS_MARK> VCT_TRACE_MSG; //存储雷达探测信息

//////// 2014 1016 wanghaiying ///////////////////////////////////////////////////
typedef struct __Cooperative_FUSIDENTIINFOR   //协同后，融合信息与识别结果结构体
{
    long lStampTime;                     //发送请求信息时的当前时间 ，上述的当前时间可用返回信息的当前时间来代替	
	unsigned long lAutonum;
    char sPlatType[32];             //综合平台类型  F117  (F117； F118； F119； F120； F121)
	double dConfidence;                      //综合可信度
	
	TRACKSTATUS_MARK stFusTrack;            //存储融合后的雷达探测信息（航迹信息）
	VCT_ESM_MSG vctFusEsm;                  //存储融合后的雷达侦察信息
	VCT_COMM_MSG vctFusCom;                 //存储融合后的通信侦查信息   
}Cooperative_FUSIDENTIINFOR;

typedef vector<Cooperative_FUSIDENTIINFOR> VCT_Cooperative_FUSIDENTIINFOR;  //存储协同后融合信息和识别结果的结构体

typedef struct Link_Table_Event
{
	int nSerialnum;                       //序号
    int nTrackMBHao;                      //航迹对应的模板号
	int nTrackHao;                        //航迹批号
	
	int nTrackCumulativeN;                //航迹累积值
	int nTrackBasicSituation;             //航迹推理的基本事件
	
	int nESMCount;                        //捆邦ESM数
	VCT_INT vctESMMBHao;                      //ESM对应的ESM模板号
	VCT_INT vctESMHao;                        //ESM批号
	
	VCT_INT vctESMCumulativeN;                //ESM累积值
	VCT_INT vctESMBasicSituation;             //ESM基本事件
	
	int nCOMCount;                            //捆邦数
	VCT_INT vctCOMMBHao;                      //COM对应的COM模板号
	VCT_INT vctCOMHao;                        //COM批号
	
	VCT_INT vctCOMBasicSituation;               //COM基本事件
	
    double dThreatDegree;                 //平台综合威胁度
	int nTrackType;                      //平台综合识别类型
	
}EVENTLINKS;  //放特征层基本事件链表节点数据;
typedef map<int, EVENTLINKS> MAP_BASIC_EVENT;  //基本事件，//int表示航迹批号

//基本态势：1：匀速直线运动、2：加速直线运行、3：俯冲、4、上升、5、拐弯、6：远离本舰、7：逼近本舰、
	//          8：：位置固定、9：新目标、10：目标消失、11：不明

//基本事件黑板结构
typedef struct BasicEVentBIndexes 
{
	int nSeriaN;                        //序号
	long lTimeStamp;                  //时戳
	int nTrackHao;                      //航迹批号	
	
	//对应的航迹参数(空间聚类要用)
	double dRd;                  //径距
	double dAz;
	double dEz;
	double dHigh;               //高度
	double dSpeed;              //速度
	double dAddSpeed;           //加速度
	double dAzimuth;            //航向
	
	
	int nTrackEvent;           //航迹基本事件：
	VCT_INT vctEventValue;        //航迹参数变化特征
	
    double dThreatDegree;          //平台综合威胁度
    int nTrackType;               //航迹综合识别的目标类型
	
	//捆邦的异常ESM情况
	int nESMCount;                 //ESM数
	VCT_INT vctESMHao;                 //正常ESM批号与非正常的ESM,//捆邦的ESM异常不超过10个
	VCT_INT vctESMEvent;               //ESM基本事件
	//捆邦的异常COM情况
	int nCOMCount;                 //COM数
	VCT_INT vctCOMHao;                 //正常COM批号与非正常的COM
	
	VCT_INT vctCOMEvent;               //COM基本事件
}EVENTBLACK;  //放黑板节点数据;


typedef map<int, EVENTBLACK> MAP_EVENT_BLACK;  //黑板，int表示航迹批号


//单平台态势链表结构
typedef  struct Link_Table_Situation 
{
	int nSerialnum;                    //序号
	int nPlatHao;                      //平台批号
    int nPlatMBHao;                    //模板号    

	int nESMHao;                       //平台上起作用的ESM批号
	
	int nCOMHao;                       //平台上起作用的COM批号

	int nPlatOBjType;                 //平台综合识别的目标类型	
	
	int nESMBasicSituation;           //平台上起作用的ESM基本事件
    int nCOMBasicSituation;           //平台上起作用的COM基本事件
    int nPlatCumulativeN;             //累积值

	//知识库中推理获得
	int nPlatOBJEvent;                 //平台基本态势
	double dThreatDegree;              //平台综合威胁度

	//对应的航迹参数(空间聚类用)
	double dRd;                  //径距
	double dAz;
	double dEz;
	double dHigh;               //高度
	double dSpeed;              //速度
	double dAddSpeed;           //加速度
	double dAzimuth;            //航向

}PLATEVENT;
typedef map<int, PLATEVENT> MAP_PLAT_LINK;

//平台态势黑板模型结构
typedef struct PlatBlack_Table_Situation
{
	int nSerialnum;                       //序号
    long lTimeStamp;                    //时戳

	int nPlatHao;                         //平台批号
	int nPlatBasicSituation;             //平台基本态势

	int nESMHao;                          //此态势起作用的ESM批号
	int nESMBasicSituation;               //此态势起作用的ESM基本事件

	int nCOMHao;                          //此态势起作用的COM批号

	int nCOMBasicSituation;               //此态势起作用的COM基本事件
	
    int nTrackOBjType;                  //航迹综合识别的目标类型

	//对应的航迹参数(空间聚类用)
	double dRd;                  //径距
	double dAz;
	double dEz;
	double dHigh;               //高度
	double dSpeed;              //速度
	double dAddSpeed;           //加速度
	double dAzimuth;            //航向

	double dThreatDegree;              //平台综合威胁度
}PLATBLACK;
typedef vector<PLATBLACK> VCT_PLAT_BLACK;
typedef map<int, PLATBLACK> MAP_PLAT_BLACK;

//空间群目标链表结构
typedef struct SpaceGroup_PlanLink_Tabel             //空间群结构
{
    int nPlanTypeN;                   //空间群数
	
    VCT_INT vctPlanGroupN;              //每个群含目标数量
    VV_INT vvPlanGroupHao;        //每个群含目标的批号
	
	int nPlanSpacMBHao;               //空间群推理飞机类模板号
	
    VCT_DOUBLE vctPlanThreatDegree;     //每个群综合威胁度
	
	VV_INT vvPlanGroupOBjType;  //每个空间群中含的目标类型
	
    int nPlanCumulativeN;            //模板累积值
	//推理获得
    VV_INT vvPlanEvent;            //每个空间群目标态势
	
 }SPACE_TARGET;

//空间群黑板结构
typedef struct SpaceGroupBlack_Tabel               //空间群黑板结构
{
	long lTimeStamp;                  //当前时戳
	
	int nPlanTypeN;                   //舰船类空间群数
    VCT_INT vctPlanGroupN;              //舰船类每个群含目标数量
    VV_INT vvPlanGroupHao;        //舰船类每个群含目标的批号
	
    VCT_DOUBLE vctPlanThreatDegree;     //舰船类每个群综合威胁度
	
    VV_INT vvPlanGroupOBjType;  //舰船类每个空间群中含的目标类型
	
	//前面推理获得
	VV_INT vvPlanEvent;            //每个舰船空间群目标态势
	
 }SPACE_BLACK;

typedef vector<SPACE_TARGET> VCT_SPACE;

/////////////////////////////////功能层/////////////////////////////////////////////////
////功能群链表结构
typedef struct FuncGroup_Link_Tabel             //功能链表群结构
{
	int nFuncGroupMBNum;                     //功能群模板数
	VCT_INT vctFuncMBHao;                  //功能模板号
	
	int nFuncGroupN;                 //功能群数
	VCT_INT vctFuncGpH;                //每个功能群对应的编号
	VCT_INT vctFuncGroupTrackN;        //每个功能群中含目标数量
	VV_INT vvFuncGroupHao;        //每个群含目标的批号
	
	VCT_DOUBLE vctFuncThreatDegree;     //每个群综合威胁度
	
	VV_INT vvFuncGroupOBjType;  //每个功能群中含的目标类型
	
	//知识库中推理获得
	VCT_INT vctFuncGroupEvent;         //每个功能群态势：1警戒、2：巡逻，3：攻击、4：拦截，5：轰炸、6：突防、7：干扰、8：预警,9:侦察、10：不明
    VCT_INT vctFuncCumulativeN;            //模板累积值
	
}FUN_GROUP_LINK;

///功能群黑板数据结构
typedef struct FuncGroup_Black_Tabel             //功能群黑板结构
{
	long lTimeStamp;                //当前时戳
	
    int nFuncGroupN;                 //功能群数
    VCT_INT vctFuncGpHao;            //功能群序号
	
    VCT_INT vctFuncGroupTrackN;        //每个功能群中含目标数量
    VV_INT vvFuncGroupTrackHao;        //每个群含目标的批号
	
    VCT_DOUBLE vctFuncThreatDegree;     //每个群综合威胁度
	
	VV_INT vvFuncGroupOBjType;  //每个功能群中含的目标类型
	
	//知识库中推理获得
	VCT_INT vctFuncGroupEvent;         //每个功能群态势：1警戒、2：巡逻，3：攻击、4：拦截，5：轰炸、6：突防、7：干扰、8：预警,9:侦察、10：不明
	
}FUN_GROUP_BLACK;


//////////////////////////////////////////相互作用层////////////////////////////////////////////////



//相互作用群态链表设计结构
typedef struct Interaction_Link_Tabel               //相互作用群链表结构
{
	int nInteGroupSeriNum;                   //相互作用群序号（自动产生）,假设相互作用群不超过10个
	
	int nInteractGroupSGN;                   //相互作用群中含功能群数
    
    double dSumThreatDegree;                 //相互作用群的综合威胁度
	
    VCT_INT vctInteGroupTrackNum;              //每个子群中的目标数
    VCT_INT vctInteGroupHao;                   //每个子群号
    VCT_INT vctInterEvent;                     //每个子群的态势类型
	
    VV_INT vvIntertrackHao;					//每个子群中含目标批号
    VV_INT vvInterOBjType;					//每个子群中含目标类型       
	
    int nInteCumulativeN;                    //相互作用群模板累积值
}INTERGROUP;
typedef vector<INTERGROUP> INTERGROUPLINK;

//相互作用群黑板设计结构
typedef struct Interaction_Black_Tabel                  //黑板上的相互作用群结构
{
    long lTimeStamp;                           //时戳
	int nInteGroupSeriNum;                       //相互作用群序号（自动产生）,假设相互作用群不超过20个  (显示)   
	
	int nInteractGroupSGN;                      //相互作用群中含功能群数
    double dSumThreatDegree;                    //相互作用群的综合威胁度  
	
    VCT_INT vctInteGroupTrackNum;                //每个子群中的目标数
    VCT_INT vctInteGroupHao;                     //每个子群号
    VCT_INT vctInterEvent;                       //每个子群的态势类型
	
    VV_INT vvIntertrackHao;               //每个子群中含目标批号
    VV_INT vvInterOBjType;               //每个子群中含目标类型         
}INTERBLACKNODE;
typedef vector<INTERBLACKNODE> INTERGROUPBLACK;


///////////////////////////////////数据库数据结构///////////////////////////////////////////////

typedef struct DataBase
{
	VCT_INT TrackThd;          //Track的阈值,存储顺序为，径距，高度，速度，加速度，方位
	VCT_INT ESMThd;            //ESM的阈值，存储顺序为 脉冲频率，脉冲幅度，脉冲宽度，重频，天线扫描周期
	VCT_INT COMThd;            //COM的阈值，存储顺序为 脉冲频率，脉冲幅度，跳频次数
	VCT_INT TrackModelID;	   //Track的模板号
	VCT_INT ESMModelID;        //ESM的模板号
	VCT_INT COMModelID;        //COM的模板号
	VCT_INT PlatModelID;       //平台模板号
	VCT_INT FunModelID;			//功能群模板号
	VCT_INT InterModelID;		//模板号（序号）
	VCT_INT TrackEventID;      //Track基本事件编号
	VCT_INT ESMEventID;        //ESM的基本事件编号
	VCT_INT COMEventID;        //COM的基本事件编号
	VCT_INT PlatEventID;       //平台事件编号
	VCT_INT SpaceGrpID;        //空间群编号
	VCT_INT FunEventID;			//功能群事件编号
	VV_INT vctDbTrackKng;      //存放数据库中track的知识的所有内容，该内容在程序初始化的时候读入
	VV_INT vctDbESMKng;        //存放数据库中ESM的知识的所有内容，该内容在程序初始化的时候读入
	VV_INT vctDbCOMKng;        //存放数据库中COM的知识的所有内容，该内容在程序初始化的时候读入
	VV_INT vctDbPlatKng;       //存放数据库中Plat的知识的所有内容，该内容在程序初始化的时候读入
	VV_INT vctDbSpaceKng;      //存放数据库中Space的知识的所有内容，该内容在程序初始化的时候读入
	VV_INT vctDbFunKng;			//存放数据库中Fun的知识的所有内容
	VV_INT vctDbInterKng;      ////编队功能:1警戒、2：巡逻，3：攻击、4：拦截，5：轰炸、6：突防、7：干扰、8：预警,9:侦察
}DB_DATA;


//所有消息的头
typedef struct _X_ALL_RECV_MSG
{
	VCT_ESM_MSG stEsm;
	VCT_COMM_MSG stComm;
	VCT_TRACE_MSG stTrace;
}ALL_MSG_INPUT;


#endif