//��ͼ���Ͼ�γ��
#define LEFTLT 117.0720
#define LEFTBT 26.4891
//��ͼ���¾�γ��
#define RIGHTLT 123.0125
#define RIGHTBT 21.7320

//ͼ�뾶
#define NRDIS 5
//PI/4.0
#define PI_4 3.1415926/4.0

//�Զ�����Ϣ
//���������б���Ϣ
#define WM_UPDATELSTMSG WM_USER+101

//����������˿�
#define SERVERPORT 8001
//����ͻ��˶˿�
#define CLIENTPORT 7001

//����P2P����˿�
#define P2P_SERVER_PORT 9001
//����P2P�ͻ��˶˿�
#define P2P_CLIENT_PORT 6001

#include <math.h>

typedef struct _ProtcolHeader
{
	unsigned short		nMsgType;			//���ݰ�����
	unsigned short		nMsgLength;			//���ݰ�����	
}ProtcolHeader;
