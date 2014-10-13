#ifndef __COMM_STRUCT
#define __COMM_STRUCT

#pragma warning(disable : 4786)
#include <vector>
using namespace std;

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
// 测量信息
// 	 ZAI_FREQ stZaiPin;                  //载频信息结构
// 	 CHONG_FREQ stChongPin;              //重频信息结构
// 	 WIDTH_MSG stMaiKuan;                //脉宽信息结构
// 	 AntennaScan_MSG stTianXianScan;     //天线扫描信息结构
// 	 PulseFeature_MSG stMaiChongFeature; //脉冲特征信息结构
	 double dZaiPin;                     //载频信息结构
	 double dChongPin;                   //重频信息结构
	 double dMaiKuan;                    //脉宽信息结构
	 double dTianXianScan;               //天线扫描信息结构
	 double dMaiChongFeature;            //脉冲特征信息结构
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

	 char cDWAttribute[32];                  //敌我属性
	 double dConfidence;                 //可信度
     char cCountry[32];                  //国家（地区）

	 char cJfFlag;
	 unsigned long lFlag;                 //累加标记

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
//	ZAI_FREQ stComZaiPin;                //载频信息结构
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
	char cDWAttribute[32];					  //敌我属性
	double dConfidence;  			      //可信度
    char cCountry[32];			          //国家（地区）
	char cJfFlag;
	unsigned long lFlag;                  //累加标记

}COMSTATUS_MARK;


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
    unsigned long lTargetNumber;         //目标批号	 
//测量信息
	double dRange;                        //距离
	double dAzimuth;                      //方位
	double dElevationAngle;               //仰角
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
//识别信息
//	unsigned short sPlatType;            //平台类型  F117  (F117； F118； F119；F120； F121)
    char sPlatType[32];  
	char cPlatName[32];                  //平台名称  
    double dConfidence;                  //可信度
    char cDWAttribute;                   //敌我属性 (IFF信息)
	char cJfFlag;                        //是否进行数据融合标志，0：未融合，1：已融合
	unsigned long lFlag;                 //累加标记

}TRACKSTATUS_MARK;

typedef vector<SHIP_POSITION> VCT_SHIP_POSITION; //存储各舰的GPS信息
typedef vector<ESMSTATUS_MARK> VCT_ESM_MSG;	//存储雷达侦察信息
typedef vector<COMSTATUS_MARK> VCT_COMM_MSG; //存储通信侦查信息
typedef vector<TRACKSTATUS_MARK> VCT_TRACE_MSG; //存储雷达探测信息

//所有消息的头
typedef struct _X_ALL_RECV_MSG
{
	VCT_ESM_MSG stEsm;
	VCT_COMM_MSG stComm;
	VCT_TRACE_MSG stTrace;
}ALL_MSG_INPUT;

#endif