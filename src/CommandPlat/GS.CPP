#define PI 3.1415926
#define DEG2ARC PI/180
#define ARC2DEG 180/PI

#include <math.h>
#define _EXPORT
#include "GS.H"

PositionPolar GEO2Polar(PositionGEO source, OriginGEO originPoint)
{
	PositionPolar stTmp;

	const double a = 6378137.0;
	const double e2 = 0.0066943799014;
	double Nt=0;
	double Nr=0;
	double xt=0;
	double yt=0;
	double zt=0;
	double x0=0;
	double y0=0;
	double z0=0;
	double Rd=0;
	double Az=0;
	double Ez=0;
	double x=0;
	double y=0;
	double z=0;

	double SIN_BO = 0;
	double COS_BO = 0;
	double COS_Bt = 0;
	double SIN_Bt = 0;
	double COS_L0 = 0;
	double SIN_L0 = 0;

	SIN_BO = sin(originPoint.dRefLat_*DEG2ARC);
	COS_BO = cos(originPoint.dRefLat_*DEG2ARC);
	SIN_Bt = sin(source.dLatitude*DEG2ARC);
	COS_Bt = cos(source.dLatitude*DEG2ARC);
	COS_L0 = cos(originPoint.dRefLon_*DEG2ARC);
	SIN_L0 = sin(originPoint.dRefLon_*DEG2ARC);

	Nt=a/sqrt(1.0-e2*SIN_Bt*SIN_Bt);
	Nr=a/sqrt(1.0-e2*SIN_BO*SIN_BO);

	xt=(Nt+source.dAltitude)*COS_Bt*cos(source.dLongitude*DEG2ARC);
	yt=(Nt+source.dAltitude)*COS_Bt*sin(source.dLongitude*DEG2ARC);
	zt=(Nt*(1.0-e2)+source.dAltitude)*SIN_Bt;

	x0=(Nr+originPoint.dRefAlt_)*COS_BO*COS_L0;
	y0=(Nr+originPoint.dRefAlt_)*COS_BO*SIN_L0;
	z0=(Nr*(1.0-e2)+originPoint.dRefAlt_)*SIN_BO;

	x=-(xt-x0)*SIN_L0+(yt-y0)*COS_L0;
	y=-(xt-x0)*SIN_BO*COS_L0-(yt-y0)*SIN_BO*SIN_L0+(zt-z0)*COS_BO;
	z=(xt-x0)*COS_BO*COS_L0+(yt-y0)*COS_BO*SIN_L0+(zt-z0)*SIN_BO;

	Rd=sqrt(x*x+y*y+z*z);
	if(x>=0.0&&y>0.0)
	{
		Az=atan(x/y);
	}
	else if(x>0.0&&fabs(y)<1.0e-3)
	{
		Az=0.5*PI;
	}
	else if(y<0.0)
	{
		Az=PI+atan(x/y);
	}
	else if(x<0.0&&fabs(y)<1.0e-3)
	{
		Az=1.5*PI;
	}
	else if(x<0&&y>0.0)
	{
		Az=2.0*PI+atan(x/y);
	}
	Ez=atan(z/sqrt(x*x+y*y)); 

	stTmp.dRDistance = Rd;
	stTmp.dAzimuth = Az*ARC2DEG;
	stTmp.dHLowAngle = Ez*ARC2DEG;

	return (stTmp) ;
}

PositionGEO	Polar2GEO(PositionPolar source, OriginGEO originPoint)
{
	const double dKm = 4.0/3.0;
	const double dEarthRadius = 6371.1;

	PositionGEO	stTmp;	//输出

	//原始坐标转换
	double dTmpLonti = originPoint.dRefLon_*DEG2ARC;
	double dTmpLati = originPoint.dRefLat_*DEG2ARC;	//度转弧度
	double dTmpHeight = originPoint.dRefAlt_*0.001;	//高度转Km

	//目标坐标转换
	double dTmpDistance = source.dRDistance*0.001;	//距离转Km
	double dTmpBeta = source.dAzimuth*DEG2ARC;
	double dTgtEz = source.dHLowAngle*DEG2ARC;

	double dRm = dKm*dEarthRadius;
	double dTgtAz = dKm*atan(dTmpDistance*cos(dTgtEz)/(dRm+dTmpHeight+dTmpDistance*sin(dTgtEz)));

	//水平距离
	double dHroizeDistance = dEarthRadius*dTgtAz;
	//目标高度
	double dOutHeight = sqrt((dRm+dTmpHeight)*(dRm+dTmpHeight)+dTmpDistance*dTmpDistance+2*(dRm+dTmpHeight)*dTmpDistance*sin(dTgtEz))-dRm;
	dOutHeight = 1000.0*dOutHeight;	//Km转为m

	double dTmpAlpha = dHroizeDistance/dEarthRadius;
	//目标纬度
	double sin_phy = cos(dTmpAlpha)*sin(dTmpLati)+sin(dTmpAlpha)*cos(dTmpLati)*cos(dTmpBeta);
	double cos_phy = sqrt(1-sin_phy*sin_phy);
	double dOutLati = asin(sin_phy)*ARC2DEG;
	//目标经度
	double sin_numda=sin(dTmpBeta)*sin(dTmpAlpha)/cos_phy;
	if(sin_numda>1)
		sin_numda=1;
	else if (sin_numda <-1) 
		sin_numda=-1;
	else
	{
	}
	double dDetaLon = asin(sin_numda);
	double dOutLon = (dTmpLonti+dDetaLon)*ARC2DEG;
	
	stTmp.dLongitude = dOutLon;
	stTmp.dLatitude = dOutLati;
	stTmp.dAltitude = dOutHeight;

	return(stTmp);
}

PositionCross Polar2Cross(PositionPolar source)
{
	PositionCross stOutCross;

    stOutCross.dx = source.dRDistance * cos(source.dHLowAngle * DEG2ARC) * cos(source.dAzimuth * DEG2ARC);
    stOutCross.dy = source.dRDistance * cos(source.dHLowAngle * DEG2ARC) * sin(source.dAzimuth * DEG2ARC);
    stOutCross.dz = source.dRDistance * sin(source.dHLowAngle * DEG2ARC);

    return(stOutCross);
}

PositionPolar Cross2Polar(PositionCross source)
{
	PositionPolar stOutPolar;

	double dTmpDistance(0.0);
	double dTmpAz(0.0);
	double dTmpEz(0.0);

	double dTmpVtDistance(0.0);

	dTmpVtDistance = sqrt(source.dx * source.dx + source.dy * source.dy);	//水平距离
    dTmpDistance = sqrt(source.dx * source.dx + source.dy * source.dy + source.dz * source.dz);	//径距

	//径距无效
	if (dTmpDistance < 0.0001)
	{
		//什么都不做
		stOutPolar.dRDistance = 0.0;
		stOutPolar.dAzimuth = 0.0;
		stOutPolar.dHLowAngle = 0.0;
	} 
	else
	{
		if (dTmpVtDistance < 0.0001)
		{
			//水平无效
			stOutPolar.dRDistance = dTmpDistance;
			stOutPolar.dAzimuth = 0.0;
			stOutPolar.dHLowAngle = asin(source.dz/dTmpDistance)*ARC2DEG;
		} 
		else
		{
			//先算方位角
			if (source.dy < 0.0)
			{
				dTmpAz = 360.0 - ARC2DEG*acos(source.dx/dTmpVtDistance);
			} 
			else
			{
				dTmpAz = ARC2DEG*acos(source.dx/dTmpVtDistance);
			}
			
			if (dTmpAz<0.0)
			{
				dTmpAz = dTmpAz + 360.0;
			} 
			else if (dTmpAz > 360.0)
			{
				dTmpAz = dTmpAz - 360.0;
			}
			else
			{
				//正常
			}

			//计算仰角
			dTmpEz = asin(source.dz/dTmpDistance)*ARC2DEG;

			stOutPolar.dRDistance = dTmpDistance;
			stOutPolar.dAzimuth = dTmpAz;
			stOutPolar.dHLowAngle = dTmpEz;
		}
	}

	return(stOutPolar);
}