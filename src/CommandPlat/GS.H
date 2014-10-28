#ifndef GS_HEADER
#define GS_HEADER

//输出
#ifndef _EXPORT
#define _EXPORT_GS __declspec(dllimport)
#else
#define _EXPORT_GS __declspec(dllexport)
#endif

//参考点经纬高
struct	OriginGEO
{
	double	dRefLat_;//经度(单位：度)
	double	dRefLon_;//纬度(单位：度)
	double	dRefAlt_;//高度(单位：m)
};

//地理坐标系（经纬高）
struct	PositionGEO
{
	double	dLongitude;	//经度(单位：度)
	double	dLatitude;	//纬度(单位：度)
	double	dAltitude;	//高度(单位：m)
};

//极坐标系
struct	PositionPolar
{
	double	dRDistance;		//斜距
	double	dHLowAngle;		//高低角(单位：度)
	double	dAzimuth;		//方位角(单位：度)
};

//直角坐标系
struct PositionCross
{
	double dx;		//x坐标(单位：m)
	double dy;		//y坐标(单位：m)
	double dz;		//z坐标(单位：m)
};

extern "C"
{
	PositionPolar GEO2Polar(PositionGEO source, OriginGEO originPoint);
	PositionGEO Polar2GEO(PositionPolar source, OriginGEO originPoint);
	PositionCross Polar2Cross(PositionPolar source);
	PositionPolar Cross2Polar(PositionCross source);
};

#endif
