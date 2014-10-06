//地图左上经纬度
#define LEFTLT 117.0720
#define LEFTBT 26.4891
//地图右下经纬度
#define RIGHTLT 123.0125
#define RIGHTBT 21.7320

//图半径
#define NRDIS 5
//PI/4.0
#define PI_4 3.1415926/4.0

//自定义消息
//更新数据列表消息
#define WM_UPDATELSTMSG WM_USER+101

//定义服务器端口
#define SERVERPORT 8001
//定义客户端端口
#define CLIENTPORT 7001

//定义P2P服务端口
#define P2P_SERVER_PORT 9001
//定义P2P客户端端口
#define P2P_CLIENT_PORT 6001

#include <math.h>

typedef struct _ProtcolHeader
{
	unsigned short		nMsgType;			//数据包类型
	unsigned short		nMsgLength;			//数据包长度	
}ProtcolHeader;
