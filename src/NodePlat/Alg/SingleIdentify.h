#include "../Comm Struct.h"

// 雷达侦查设备精度结构体
typedef struct _Accuracy 
{
	float dirAcc;		// 测向精度
	
}Accuracy;

typedef struct __IDENTIINFOR         //本舰识别结构体 
{	
	// 身份标识	
	unsigned long lAutonum; 	         //综合批号
	// 	unsigned short nPlatNumber;         //平台编号
	// 	unsigned short nEquipmentNumber;    //设备编号
	// 	unsigned char cEquipmentType;       //设备类型
	//	unsigned long lTargetNumber;        //目标批号 	
	//测量信息
	// 	ZAI_FREQ stZaiPin;                  //载频信息结构
	// 	CHONG_FREQ stChongPin;              //重频信息结构
	// 	WIDTH_MSG stMaiKuan;                //脉宽信息结构
	// 	AntennaScan_MSG stTianXianScan;     //天线扫描信息结构
	// 	PulseFeature_MSG stMaiChongFeature; //脉冲特征信息结构
	// 	short nPulseExtent;                 //脉冲幅度
	// 	long lSignalReachTime;              //信号到达时间
	//	float fReachAzimuth;                //到达方位
	//  	float fElevationAngle;              //仰角
	// 	float fRange;                        //距离
	//     float fCourse;                       //绝对航向
	// 	double dTargetAZSpeed;               //目标方位角速度
	// 	double dTargetEAngleSpeed;           //目标仰角角速度
	// 	float fTX;                           //目标空间坐标X
	// 	float fTY;                           //目标空间坐标Y
	// 	float fTZ;                           //目标空间坐标Z
	// 	double dTSpeedX;                     //目标绝对速度X
	//     double dTSpeedY;                     //目标绝对速度Y
	//     double dTSpeedZ;                     //目标绝对速度Z
	//识别信息
	// 	unsigned char cSignalType;           //信号类型
	// 	char cModulationStyle;               //调制样式 
	// 	char cRadarPurpose;                 //雷达用途
	// 	char cRadarName;                    //雷达名称
	// 	char cThreatLevel;                  //威胁等级
	// 	float fERPower;                     //有效辐射功率
//	char *pPlatType;                 //平台类型
	unsigned short sPlatType;            //平台类型  F117  ('1'代表F117； '2' 代表F118； '3'代表F119； '4'代表F120； '5'代表F121)
 
	// 	char cPlatXinghao;                  //平台型号
	// 	char cPlatName;                     //平台名称
	// 	char cDWAttribute;                  //敌我属性
	double dConfidence;                   //可信度
	//	unsigned char cCountry;             //国家（地区）  
	
}IDENTIINFOR;

typedef vector<IDENTIINFOR> VCT_IDENTIINFOR_MSG;//存储本舰识别信息

//本舰识别接口函数
VCT_IDENTIINFOR_MSG* SingleIdentify(VCT_ESM_MSG* pEsmStatusVec, VCT_COMM_MSG* pComStatusVec, VCT_TRACE_MSG* pTrackStatusVec);