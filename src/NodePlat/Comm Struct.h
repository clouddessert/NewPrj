#ifndef __COMM_STRUCT
#define __COMM_STRUCT

#pragma warning(disable : 4786)
#include <vector>
using namespace std;
typedef vector<int> VCT_INT;

typedef struct __SHIP_POSITION           //舰的经纬高
{
	double dLonti;
	double dLati; 
	double dHeight;

}SHIP_POSITION;

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
	char sPlatType[32];  
	char cPlatName[32];                 //平台名称  飞机 导弹 轰炸机 战斗机
	
	char cDWAttribute[32];              //敌我属性
	double dConfidence;                 //可信度
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
    char sPlatType[32];                   //平台类型  F117  (F117； F118； F119； F120； F121)
	char cPlatName[32];			          //平台名称    
	char cDWAttribute[32];				  //敌我属性
	double dConfidence;  			      //可信度
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
    char sPlatType[32];						
	char cPlatName[32];                  //平台名称  
    double dConfidence;                  //可信度
    char cDWAttribute[32];               //敌我属性 (IFF信息)
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
    long int nStampTime;                     //发送请求信息时的当前时间 ，上述的当前时间可用返回信息的当前时间来代替	
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
	
	int nCOMN;                            //捆邦数
	VCT_INT vctCOMMBHao;                      //COM对应的COM模板号
	VCT_INT vctCOMHao;                        //COM批号
	
	VCT_INT nCOMBasicSituation;               //COM基本事件
	
    double dThreatDegree;                 //平台综合威胁度
	char cTrackType;                      //平台综合识别类型
	
}EVENTLINKS;  //放特征层基本事件链表节点数据;

//基本态势：1：匀速直线运动、2：加速直线运行、3：俯冲、4、上升、5、拐弯、6：远离本舰、7：逼近本舰、
	//          8：：位置固定、9：新目标、10：目标消失、11：不明

//基本事件黑板结构
typedef struct BasicEVentBIndexes 
{
	int nSeriaN;                        //序号
	double dTimeStamp;                  //时戳
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
    char cTrackType;               //航迹综合识别的目标类型
	
	//捆邦的异常ESM情况
	int nESMCount;                 //ESM数
	VCT_INT vctESMHao;                 //正常ESM批号与非正常的ESM,//捆邦的ESM异常不超过10个
	VCT_INT vctESMEvent;               //ESM基本事件
	//捆邦的异常COM情况
	int nCOMCount;                 //COM数
	VCT_INT vctCOMHao;                 //正常COM批号与非正常的COM
	
	VCT_INT vctCOMEvent;               //COM基本事件
}EVENTBLACK;  //放黑板节点数据;

//所有消息的头
typedef struct _X_ALL_RECV_MSG
{
	VCT_ESM_MSG stEsm;
	VCT_COMM_MSG stComm;
	VCT_TRACE_MSG stTrace;
}ALL_MSG_INPUT;

#endif