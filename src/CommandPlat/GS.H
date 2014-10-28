#ifndef GS_HEADER
#define GS_HEADER

//���
#ifndef _EXPORT
#define _EXPORT_GS __declspec(dllimport)
#else
#define _EXPORT_GS __declspec(dllexport)
#endif

//�ο��㾭γ��
struct	OriginGEO
{
	double	dRefLat_;//����(��λ����)
	double	dRefLon_;//γ��(��λ����)
	double	dRefAlt_;//�߶�(��λ��m)
};

//��������ϵ����γ�ߣ�
struct	PositionGEO
{
	double	dLongitude;	//����(��λ����)
	double	dLatitude;	//γ��(��λ����)
	double	dAltitude;	//�߶�(��λ��m)
};

//������ϵ
struct	PositionPolar
{
	double	dRDistance;		//б��
	double	dHLowAngle;		//�ߵͽ�(��λ����)
	double	dAzimuth;		//��λ��(��λ����)
};

//ֱ������ϵ
struct PositionCross
{
	double dx;		//x����(��λ��m)
	double dy;		//y����(��λ��m)
	double dz;		//z����(��λ��m)
};

extern "C"
{
	PositionPolar GEO2Polar(PositionGEO source, OriginGEO originPoint);
	PositionGEO Polar2GEO(PositionPolar source, OriginGEO originPoint);
	PositionCross Polar2Cross(PositionPolar source);
	PositionPolar Cross2Polar(PositionCross source);
};

#endif