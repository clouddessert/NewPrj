#include "FusionCooperativeMsg.h"
#include "stdafx.h" 
#include <iostream>
#include <math.h>
#include <vector>
#include <string>

using namespace std;
//同类识别融合
//对航迹的融合 ：一条请求信息对应的只有一条航迹信息，返回信息中最多只有一条航迹信息，两条航迹信息进行融合，或者一条返回信息协同互补

//对ESM的融合：  统计ESM的类型数
  
//对COM的融合：统计COM的类型数

//请求信息是一个结构体，返回信息同样也是结构体
void Mf_SPA(double s, double t,double& corr); //s,t为相同类型的信息，进行集对分析，将返回的相关系数存入容器VctCorr中

void FusionCooperativeMsg(VCT_Request_Cooperative_Msg& vctReqMsg, VCT_BACK_Cooperative_Msg& vctBackMsg, /* 综合识别结果*/VCT_MIDENTIINFOR_MSG& vctMidentiinforMsg, VCT_Cooperative_FUSIDENTIINFOR& vctCoFusMsg);


void FusionCooperativeMsg(VCT_Request_Cooperative_Msg& vctReqMsg, VCT_BACK_Cooperative_Msg& vctBackMsg, /* 综合识别结果*/VCT_MIDENTIINFOR_MSG& vctMidentiinforMsg, VCT_Cooperative_FUSIDENTIINFOR& vctCoFusMsg)
{
	int nNumTrackRd = 0;  //目标航迹的径距（米）
	int nNumTrackAz = 0;  //目标航迹的方位（弧度）
	int nNumTrackEz = 0;  //目标航迹的仰角（弧度）
	int nNumTrackVx = 0;  //目标航迹的X轴上的速度（米/秒）
	int nNumTrackVy = 0;  //目标航迹的Y轴上的速度（米/秒）
	int nNumTrackVz = 0;  //目标航迹的Z轴上的速度（米/秒）

	int nNumESMDOAz = 1;  //ESM信号的到达方位（弧度）
	int nNumESMFre = 1;   //ESM信号的频率（GHz）
	int nNumESMPA = 1;    //ESM信号的幅度
	int nNumESMPzw = 1;   //ESM信号的脉冲宽度（us）
	int nNumESMPRI = 1;   //ESM信号的重复间隔（ms）;重复频率PRF=PRI的倒数
	int nNumESMSCan = 1;  //ESM信号的侦察雷达天线扫描周期（s）

	int nNumCOMDOAz = 1;  //COM信号的到达方位（弧度）   
	int nNumCOMFre = 1;   //COM信号的中心频率（MHz）
	int nNumCOMPA = 1; 	  //COM信号的幅度
	int nNumCOMBand = 1;  //COM信号的信号带宽（MHz）
	int nNumCOMJPN = 1;   //COM信号的跳步次数

	double dcorrEsmReachAzimuth = 0.0; //ESM信号的到达方位（弧度）
	double dcorrZaiPin= 0.0; //ESM信号的频率（GHz）
    double dcorrEsmPulseExtent= 0.0; //ESM信号的幅度
    double dcorrMaiKuan= 0.0; //ESM信号的脉冲宽度（us）
    double dcorrChongPin= 0.0; //ESM信号的重复间隔（ms）;重复频率PRF=PRI的倒数
    double dcorrTianXianScan= 0.0; //ESM信号的侦察雷达天线扫描周期（s）
	double dAverCorr = 0.0;
	double dcorrComReachAzimuth = 0.0;
	double dcorrComPulseExtent= 0.0;
	double dcorrFre = 0.0; 
	double dcorrBand = 0.0;
	double dcorrJPN = 0.0;

	VCT_BACK_Cooperative_Msg vctAllBackMsg;//存放将多条同综批的返回信息合并成一条的返回信息
	VCT_Request_Cooperative_Msg::iterator iteReqMsg;
	VCT_BACK_Cooperative_Msg::iterator iteBackMsg;
//	VCT_BACK_Cooperative_Msg::iterator iteBackMsg1;
	VCT_BACK_Cooperative_Msg::iterator iteBackMsg2;
//	VCT_BACK_Cooperative_Msg::iterator iteBackMsg3;
		VCT_BACK_Cooperative_Msg::iterator iteBackMsg4;
	VCT_Cooperative_FUSIDENTIINFOR::iterator iteCoFusionMsg;
	VCT_MIDENTIINFOR_MSG::reverse_iterator  r_iteMIdenti;
	VCT_ESM_MSG::iterator iteFusEsm;      //存储融合后的雷达侦察信息
	VCT_COMM_MSG::iterator iteFusCom;
	VCT_ESM_MSG::iterator iteBaEsm;
//	VCT_ESM_MSG::iterator iteBaEsm1;
	VCT_COMM_MSG::iterator iteBaCom;
//	VCT_COMM_MSG::iterator iteBaCom1;
	VCT_ESM_MSG::iterator iteReEsm;      
	VCT_COMM_MSG::iterator iteReCom;

	typedef vector<double> VCT_CORR;
	VCT_CORR VctCorr;      // 存放关联系数的容器
	VCT_CORR::iterator iteCorr;

	Cooperative_FUSIDENTIINFOR stCoFusiInfor;
	BACK_Cooperative_Msg stBaMsg;
	ESMSTATUS_MARK stFusEsm;
	COMSTATUS_MARK stFusCom;
//清空存放融合信息的容器   
	for ( iteCoFusionMsg = vctCoFusMsg.begin(); iteCoFusionMsg != vctCoFusMsg.end(); iteCoFusionMsg++)
	{
		iteCoFusionMsg->lAutonum = NULL;
		iteCoFusionMsg->dConfidence = NULL;
		memset(iteCoFusionMsg->sPlatType,0,32); //清空字符串数组
		memset(&(iteCoFusionMsg->stFusTrack),0,sizeof(TRACKSTATUS_MARK));
		for ( iteFusEsm = iteCoFusionMsg->vctFusEsm.begin(); iteFusEsm != iteCoFusionMsg->vctFusEsm.end(); iteFusEsm++)
		{
			memset(&(*iteFusEsm),0, sizeof(ESMSTATUS_MARK));
		}
		for( iteFusCom = iteCoFusionMsg->vctFusCom.begin(); iteFusCom != iteCoFusionMsg->vctFusCom.end(); iteFusCom++)
		{
			memset(&(*iteFusCom),0,sizeof(COMSTATUS_MARK));
		}
	}

    //航迹信息的融合
	//目标航迹的径距（米）
	//目标航迹的方位（弧度）
	//目标航迹的仰角（弧度）
	//目标航迹的X轴上的速度（米/秒）
	//目标航迹的Y轴上的速度（米/秒）
    //目标航迹的Z轴上的速度（米/秒）
	for ( iteReqMsg = vctReqMsg.begin(); iteReqMsg != vctReqMsg.end(); iteReqMsg++)
	{
		int TFlag = 0;
		//清空融合信息的航迹信息
		memset(&stCoFusiInfor.stFusTrack, 0, sizeof(TRACKSTATUS_MARK));
		//请求信息有航迹，为聚类后有航迹的信息或未聚类的航迹信息
		if ( iteReqMsg->lAutonum > 7999 ||(iteReqMsg->lAutonum >4999 && iteReqMsg->lAutonum <6000) )
		{
		   //将请求信息赋给融合信息，并计数
			stCoFusiInfor.stFusTrack.lAutonum = iteReqMsg->stTrace.lAutonum; //将综合批号给融合信息
			stCoFusiInfor.stFusTrack.dAzimuth = iteReqMsg->stTrace.dAzimuth;
			stCoFusiInfor.stFusTrack.dRange = iteReqMsg->stTrace.dRange;
			stCoFusiInfor.stFusTrack.dElevationAngle = iteReqMsg->stTrace.dElevationAngle;
			stCoFusiInfor.stFusTrack.dTSpeedX = iteReqMsg->stTrace.dTSpeedX;
			stCoFusiInfor.stFusTrack.dTSpeedY = iteReqMsg->stTrace.dTSpeedY;
			stCoFusiInfor.stFusTrack.dTSpeedZ = iteReqMsg->stTrace.dTSpeedZ;
			stCoFusiInfor.stFusTrack.dCourse = iteReqMsg->stTrace.dCourse;  // 绝对航向
			stCoFusiInfor.stFusTrack.dTargetAZSpeed = iteReqMsg->stTrace.dTargetAZSpeed; // 目标方位角速度
			stCoFusiInfor.stFusTrack.dTargetEAngleSpeed = iteReqMsg->stTrace.dTargetEAngleSpeed;//目标仰角角速度
			stCoFusiInfor.stFusTrack.lTargetNumber = iteReqMsg->stTrace.lTargetNumber;
			strcpy(stCoFusiInfor.stFusTrack.cEquipmentType , iteReqMsg->stTrace.cEquipmentType);
			strcpy(stCoFusiInfor.stFusTrack.cEquipmentNumber , iteReqMsg->stTrace.cEquipmentNumber);
			strcpy(stCoFusiInfor.stFusTrack.cDWAttribute , iteReqMsg->stTrace.cDWAttribute);
			strcpy(stCoFusiInfor.stFusTrack.cPlatNumber , iteReqMsg->stTrace.cPlatNumber);
			strcpy(stCoFusiInfor.stFusTrack.cPlatName , iteReqMsg->stTrace.cPlatName);
			for ( r_iteMIdenti = vctMidentiinforMsg.rbegin(); r_iteMIdenti != vctMidentiinforMsg.rend(); ++r_iteMIdenti )
			{
				// 逆序查找 
				if ( r_iteMIdenti->lAutonum == stCoFusiInfor.stFusTrack.lAutonum )
				{
					strcpy( stCoFusiInfor.stFusTrack.sPlatType, r_iteMIdenti->sPlatType ); //综合平台类型
					stCoFusiInfor.stFusTrack.dConfidence = r_iteMIdenti->dConfidence;  //综合可行度
					break;
				}
			}

			nNumTrackAz = 1;
			nNumTrackRd = 1;
			nNumTrackEz = 1;
			nNumTrackVx = 1;
			nNumTrackVy = 1;
			nNumTrackVz = 1;
		}
		//请求信息无航迹，为聚类后无航迹的信息
		else if ( iteReqMsg->lAutonum >6999 && iteReqMsg->lAutonum < 8000 )
		{
			nNumTrackAz = 0;
			nNumTrackRd = 0;
			nNumTrackEz = 0;
			nNumTrackVx = 0;
			nNumTrackVy = 0;
			nNumTrackVz = 0;
		}

		for ( iteBackMsg = vctBackMsg.begin(); iteBackMsg != vctBackMsg.end(); iteBackMsg++ )
		{
			if ( iteReqMsg->lAutonum == iteBackMsg->lAutonum ) //查找出相应的同一批号的返回信息
			{ 
				//返回信息有航迹信息 ，需进行航迹融合
				if (iteBackMsg->BackTrackN != 0)
				{
					stCoFusiInfor.stFusTrack.lFusFlag = 1; //融合查找标记,能够关联
					//对航迹的融合，各相关变量取平均值
					stCoFusiInfor.stFusTrack.dAzimuth += iteBackMsg->stTrace.dAzimuth;
					stCoFusiInfor.stFusTrack.dRange += iteBackMsg->stTrace.dRange;
					stCoFusiInfor.stFusTrack.dElevationAngle += iteBackMsg->stTrace.dElevationAngle;
					stCoFusiInfor.stFusTrack.dTSpeedX += iteBackMsg->stTrace.dTSpeedX;
					stCoFusiInfor.stFusTrack.dTSpeedY += iteBackMsg->stTrace.dTSpeedY;
					stCoFusiInfor.stFusTrack.dTSpeedZ += iteBackMsg->stTrace.dTSpeedZ;
					nNumTrackAz ++;
					nNumTrackRd ++;
					nNumTrackEz ++;
					nNumTrackVx ++;
					nNumTrackVy ++;
		        	nNumTrackVz ++;
				}
			}//if 查找出相同的综合批号进行信息融合
		} //for 遍历返回信息
		//需要融合的信息已统计全，求平均
		if ( nNumTrackAz != 0/*sizeof(stCoFusiInfor.stFusTrack) */)//返回信息有航迹信息
		{
			//求平均
			stCoFusiInfor.stFusTrack.dAzimuth /= nNumTrackAz;
			stCoFusiInfor.stFusTrack.dRange /= nNumTrackRd;
			stCoFusiInfor.stFusTrack.dElevationAngle /= nNumTrackEz;
			stCoFusiInfor.stFusTrack.dTSpeedX /= nNumTrackVx;
			stCoFusiInfor.stFusTrack.dTSpeedY /= nNumTrackVy;
			stCoFusiInfor.stFusTrack.dTSpeedZ /= nNumTrackVz;
		}
		//其他参数赋值, 对综合批号进行判断
		for( iteBackMsg2 = vctBackMsg.begin(); iteBackMsg2 != vctBackMsg.end(); iteBackMsg2++ )
		{
			if ( iteReqMsg->lAutonum <8000 ) //请求信息中无航迹信息
			{
				if (iteBackMsg2->BackTrackN != 0) // 返回信息中有航迹
				{
					stCoFusiInfor.stFusTrack.lAutonum +=2000;  //当返回信息中有航迹,将综合批号增加2000,变为9000
					TFlag = 1;  //标记为1,代表改变综合批号
					break;
				}
			}
		}

//ESM信息的融合

		 TFlag = 0;
		if( iteReqMsg->vctEsm.size() !=0 )
		{//遍历请求信息中的ESM的每一条
			for( iteReEsm = iteReqMsg->vctEsm.begin(); iteReEsm != iteReqMsg->vctEsm.end(); iteReEsm++)
			{
				 nNumESMDOAz = 1;//ESM信号的到达方位（弧度）
				 nNumESMFre = 1;//ESM信号的频率（GHz）
				 nNumESMPA = 1;//ESM信号的幅度
				 nNumESMPzw = 1;//ESM信号的脉冲宽度（us）
				 nNumESMPRI = 1;//ESM信号的重复间隔（ms）;重复频率PRF=PRI的倒数
				 nNumESMSCan = 1;//ESM信号的侦察雷达天线扫描周期（s）
				//将请求信息中的各特征参数先赋给融合数据结构
				stFusEsm.dReachAzimuth = iteReEsm->dReachAzimuth; 
				stFusEsm.dZaiPin = iteReEsm->dZaiPin;
				stFusEsm.dPulseExtent = iteReEsm->dPulseExtent;
				stFusEsm.dMaiKuan = iteReEsm->dMaiKuan;
				stFusEsm.dChongPin = iteReEsm->dChongPin;
				stFusEsm.dTianXianScan = iteReEsm->dTianXianScan;
				//遍历返回信息中的每个结构体
				for( iteBackMsg = vctBackMsg.begin(); iteBackMsg != vctBackMsg.end(); iteBackMsg++ )
				{   //判断请求信息和返回信息中的综合批号是否相同,若相同再进行处理
					if (iteReqMsg->lAutonum == iteBackMsg->lAutonum)
					{
						//(暂不存在该种情况(1),可完善)
						//(1)若请求信息为无航迹,返回信息中有航迹,则要把融合后的综合批号改为大于等于9000 ,不能按照请求信息的7000来编批
						//遍历返回信息中的每个结构体的ESM容器的每条ESM的信息
						for( iteBaEsm = iteBackMsg->vctEsm.begin(); iteBaEsm != iteBackMsg->vctEsm.end(); iteBaEsm++)
						{
							//集对分析,求关联度
							//ESM信号的到达方位（弧度）
							//ESM信号的频率（GHz）
							//ESM信号的幅度
							//ESM信号的脉冲宽度（us）
							//ESM信号的重复间隔（ms）;重复频率PRF=PRI的倒数
							//ESM信号的侦察雷达天线扫描周期（s）
							double SumCorr = 0.0;
							Mf_SPA(iteBaEsm->dReachAzimuth,iteReEsm->dReachAzimuth,dcorrEsmReachAzimuth); //ESM信号的到达方位（弧度）
							VctCorr.push_back(dcorrEsmReachAzimuth);
							Mf_SPA(iteBaEsm->dZaiPin,iteReEsm->dZaiPin,dcorrZaiPin); //ESM信号的频率（GHz）
							VctCorr.push_back(dcorrZaiPin);
							Mf_SPA(iteBaEsm->dPulseExtent,iteReEsm->dPulseExtent,dcorrEsmPulseExtent); //ESM信号的幅度
							VctCorr.push_back(dcorrEsmPulseExtent);
							Mf_SPA(iteBaEsm->dMaiKuan,iteReEsm->dMaiKuan,dcorrMaiKuan); //ESM信号的脉冲宽度（us）
							VctCorr.push_back(dcorrMaiKuan);
							Mf_SPA(iteBaEsm->dChongPin,iteReEsm->dChongPin,dcorrChongPin); //ESM信号的重复间隔（ms）;重复频率PRF=PRI的倒数
							VctCorr.push_back(dcorrChongPin);
							Mf_SPA(iteBaEsm->dTianXianScan,iteReEsm->dTianXianScan,dcorrTianXianScan); //ESM信号的侦察雷达天线扫描周期（s）
							VctCorr.push_back(dcorrTianXianScan);
							//对相关系数容器处理，取容器中数据的平均值
							for (iteCorr = VctCorr.begin(); iteCorr != VctCorr.end(); iteCorr++)
							{
								SumCorr = SumCorr + *iteCorr;  
							}
							dAverCorr = SumCorr/VctCorr.size();  //取相关系数的平均值
							//下次存放集对系数前先清空VctCorr容器
							VctCorr.clear();
							//与阈值比较（设定阈值，相关系数大于某阈值时，认为ESM是可以关联的）
							if (dAverCorr > 0.8) 
							{
								iteBaEsm->lFusFlag = 1; //融合查找标记,能够关联
								stFusEsm.lFusFlag = 1;
								//将关联信息的特征参数累加,并记录累加个数
								stFusEsm.dReachAzimuth += iteBaEsm->dReachAzimuth;
								nNumESMDOAz++;
								stFusEsm.dZaiPin += iteBaEsm->dZaiPin;
								nNumESMFre ++;//ESM信号的频率（GHz）
								stFusEsm.dPulseExtent += iteBaEsm->dPulseExtent;
								nNumESMPA ++;//ESM信号的幅度
								stFusEsm.dMaiKuan += iteBaEsm->dMaiKuan;
								nNumESMPzw ++;//ESM信号的脉冲宽度（us）
								stFusEsm.dChongPin += iteBaEsm->dChongPin;
								nNumESMPRI ++;//ESM信号的重复间隔（ms）;重复频率PRF=PRI的倒数
								stFusEsm.dTianXianScan += iteBaEsm->dTianXianScan;
								nNumESMSCan ++;
							}
						}//for( iteBaEsm = iteBackMsg->vctEsm.begin()	
					}// if 判断综合批号是否相同
				}//	for( iteBackMsg = vctBackMsg.begin()
				//每条请求信息的Esm结束之后,将各特征参数取平均值后,放入融合信息容器中
                stFusEsm.dReachAzimuth  =  stFusEsm.dReachAzimuth/nNumESMDOAz; 
				stFusEsm.dZaiPin = stFusEsm.dZaiPin/nNumESMFre;
				stFusEsm.dPulseExtent = stFusEsm.dPulseExtent/nNumESMPA;
				stFusEsm.dMaiKuan = stFusEsm.dMaiKuan/nNumESMPzw;
				stFusEsm.dChongPin = stFusEsm.dChongPin/nNumESMPRI;
				stFusEsm.dTianXianScan = stFusEsm.dTianXianScan/nNumESMSCan;
				//将请求信息的其他参数赋值给融合信息,如:联合识别的平台类型和综合可信度
				//逆序查找,从容器最后一个数据开始遍历, 综合识别结果中的当前的该批号识别出的平台类型和综合可信度
				stFusEsm.lAutonum = iteReqMsg->lAutonum;  //综合批号
                for ( r_iteMIdenti = vctMidentiinforMsg.rbegin(); r_iteMIdenti != vctMidentiinforMsg.rend(); ++r_iteMIdenti )
                {
					// 逆序查找 
					if ( r_iteMIdenti->lAutonum == stFusEsm.lAutonum )
					{
						strcpy( stFusEsm.sPlatType, r_iteMIdenti->sPlatType ); //综合平台类型
						stFusEsm.dConfidence = r_iteMIdenti->dConfidence;  //综合可行度
						break;
					}
                }
				for( iteBackMsg2 = vctBackMsg.begin(); iteBackMsg2 != vctBackMsg.end(); iteBackMsg2++ )
				{
					if ( iteReqMsg->lAutonum <8000 ) //请求信息中无航迹信息
					{
						if (iteBackMsg2->BackTrackN != 0)
						{
							stFusEsm.lAutonum +=2000;  //当返回信息中有航迹,将综合批号增加2000,变为9000
							 TFlag = 1;  //标记为1,代表改变综合批号
							break;
						}
					}
				}

				stFusEsm.lTargetNumber = iteReEsm->lTargetNumber; //目标批号
				stFusEsm.dElevationAngle = iteReEsm->dElevationAngle;//仰角
				stFusEsm.dMaiChongFeature = iteReEsm->dMaiChongFeature;//脉冲特征
				strcpy(stFusEsm.cEquipmentNumber , iteReEsm->cEquipmentNumber);  //设备编号
				strcpy(stFusEsm.cEquipmentType,iteReEsm->cEquipmentType); //设备类型
				strcpy(stFusEsm.cDWAttribute , iteReEsm->cDWAttribute);   //敌我属性
				strcpy(stFusEsm.cCountry , iteReEsm->cCountry);           //国家/地区
                strcpy(stFusEsm.cPlatName , iteReEsm->cPlatName); //平台名称
				strcpy(stFusEsm.cPlatNumber, iteReEsm->cPlatNumber);//平台编号
				strcpy(stFusEsm.cRadarName, iteReEsm->cRadarName);//雷达名称
				strcpy(stFusEsm.cRadarPurpose, iteReEsm->cRadarPurpose);//雷达用途
                stCoFusiInfor.vctFusEsm.push_back(stFusEsm);
			}//for( iteReEsm = iteReqMsg->vctEsm.begin()
		}//if( iteReqMsg->vctEsm.size() !=0 )
		//请求信息中的每条信息都遍历完成后或者是请求信息中无ESM信息,若返回信息中还有信息的融合标记不为1,说明未被融合,则补充原来的信息
// 		for( iteBackMsg1 = vctBackMsg.begin(); iteBackMsg1 != vctBackMsg.end(); iteBackMsg1++ )
// 		{ //遍历返回信息中的每个结构体的ESM容器的每条ESM的信息
// 			for( iteBaEsm1 = iteBackMsg->vctEsm.begin(); iteBaEsm1 != iteBackMsg->vctEsm.end(); iteBaEsm1++)
// 			{
//  				if ( iteBaEsm1->lFusFlag != 0 )
//  				{
// 					if( TFlag == 1 )  //代表综合批号需加2000
// 					{
// 						iteBaEsm1->lAutonum += 2000;
// 					}
// 					stCoFusiInfor.vctFusEsm.push_back(*iteBaEsm1);
// 				}//if iteBaEsm1->lFusFlag != 0
// 			}//for
// 		}//for

//COM信息的融合

		    TFlag = 0;
			if( iteReqMsg->vctComm.size() !=0 )
			{//遍历请求信息中的ESM的每一条
				for( iteReCom = iteReqMsg->vctComm.begin(); iteReCom != iteReqMsg->vctComm.end(); iteReCom++)
				{
					int nNumCOMDOAz = 1; //COM信号的到达方位（弧度）   
					int nNumCOMFre = 1;  //COM信号的中心频率（MHz）
					int nNumCOMPA = 1; 	//COM信号的幅度
					int nNumCOMBand = 1; //COM信号的信号带宽（MHz）
					int nNumCOMJPN = 1; //COM信号的跳步次数
					//将请求信息中的各特征参数先赋给融合数据结构
					stFusCom.dReachAzimuth = iteReCom->dReachAzimuth; 
					stFusCom.dComFre = iteReCom->dComFre;
					stFusCom.dPulseExtent= iteReCom->dPulseExtent;
					stFusCom.dComBand = iteReCom->dComBand;
					stFusCom.dComJPN = iteReCom->dComJPN;
					//遍历返回信息中的每个结构体
					for( iteBackMsg = vctBackMsg.begin(); iteBackMsg != vctBackMsg.end(); iteBackMsg++ )
					{   //判断请求信息和返回信息中的综合批号是否相同,若相同再进行处理
						if (iteReqMsg->lAutonum == iteBackMsg->lAutonum)
						{
							//(暂不存在该种情况(1),可完善)
							//(1)若请求信息为无航迹,返回信息中有航迹,则要把融合后的综合批号改为大于等于9000 ,不能按照请求信息的7000来编批
							//遍历返回信息中的每个结构体的ESM容器的每条ESM的信息
							for( iteBaCom = iteBackMsg->vctComm.begin(); iteBaCom != iteBackMsg->vctComm.end(); iteBaCom++)
							{
								//集对分析,求关联度
								//COM信号的到达方位（弧度）
								//COM信号的中心频率（MHz）
								//COM信号的幅度
								//COM信号的信号带宽（MHz）
								//COM信号的跳步次数
								double SumCorr = 0.0;
								Mf_SPA(iteBaCom->dReachAzimuth,iteReCom->dReachAzimuth,dcorrComReachAzimuth); //COM信号的到达方位（弧度）
								VctCorr.push_back(dcorrComReachAzimuth);
								Mf_SPA(iteBaCom->dComFre,iteReCom->dComFre,dcorrFre); //COM信号的中心频率（MHz）
								VctCorr.push_back(dcorrFre);
								Mf_SPA(iteBaCom->dPulseExtent,iteReCom->dPulseExtent,dcorrComPulseExtent); //COM信号的幅度
								VctCorr.push_back(dcorrComPulseExtent);
								Mf_SPA(iteBaCom->dComBand,iteReCom->dComBand,dcorrBand); //COM信号的信号带宽（MHz）
								VctCorr.push_back(dcorrBand);
								Mf_SPA(iteBaCom->dComJPN,iteReCom->dComJPN,dcorrJPN); //COM信号的跳步次数
								VctCorr.push_back(dcorrJPN);
								//对相关系数容器处理，取容器中数据的平均值
								for (iteCorr = VctCorr.begin(); iteCorr != VctCorr.end(); iteCorr++)
								{
									SumCorr = SumCorr + *iteCorr;  
								}
								dAverCorr = SumCorr/VctCorr.size();  //取相关系数的平均值
								//下次存放集对系数前先清空VctCorr容器
								VctCorr.clear();
								//与阈值比较（设定阈值，相关系数大于某阈值时，认为COM是可以关联的）
								if (dAverCorr > 0.8) 
								{
									iteBaEsm->lFusFlag = 1; //融合查找标记,能够关联
									//将关联信息的特征参数累加,并记录累加个数
									stFusCom.dReachAzimuth += iteBaCom->dReachAzimuth;
									nNumCOMDOAz++;
									stFusCom.dComFre += iteBaCom->dComFre;
									nNumCOMFre ++;//cOM信号的频率（GHz）
									stFusCom.dPulseExtent += iteBaCom->dPulseExtent;
									nNumCOMPA ++;//com信号的幅度
									stFusCom.dComBand += iteBaCom->dComBand;
									nNumCOMBand ++;//COM信号的信号带宽（MHz）
									stFusCom.dComJPN += iteBaCom->dComJPN;
									nNumCOMJPN ++;//COM信号的跳步次数
								}
							}//for( iteBaEsm = iteBackMsg->vctEsm.begin()	
						}// if 判断综合批号是否相同
					}//	for( iteBackMsg = vctBackMsg.begin()
					//每条请求信息的Esm结束之后,将各特征参数取平均值后,放入融合信息容器中
					stFusCom.dReachAzimuth  =  stFusEsm.dReachAzimuth/nNumCOMDOAz; 
					stFusCom.dComFre = stFusCom.dComFre/nNumCOMFre;
					stFusCom.dPulseExtent = stFusCom.dPulseExtent/nNumCOMPA;
					stFusCom.dComBand = stFusCom.dComBand/nNumCOMBand;
					stFusCom.dComJPN = stFusCom.dComJPN /nNumCOMJPN;
					//将请求信息的其他参数赋值给融合信息,如:联合识别的平台类型和综合可信度
					//逆序查找,从容器最后一个数据开始遍历, 综合识别结果中的当前的该批号识别出的平台类型和综合可信度
					stFusCom.lAutonum = iteReqMsg->lAutonum;  //综合批号
					for ( r_iteMIdenti = vctMidentiinforMsg.rbegin(); r_iteMIdenti != vctMidentiinforMsg.rend(); ++r_iteMIdenti )
					{
						// 逆序查找 
						if ( r_iteMIdenti->lAutonum == stFusCom.lAutonum )
						{
							strcpy( stFusCom.sPlatType, r_iteMIdenti->sPlatType ); //综合平台类型
							stFusCom.dConfidence = r_iteMIdenti->dConfidence;  //综合可行度
							break;
						}
					}
					for( iteBackMsg4 = vctBackMsg.begin(); iteBackMsg4 != vctBackMsg.end(); iteBackMsg4++ )
					{
						if ( iteReqMsg->lAutonum <8000 ) //请求信息中无航迹信息
						{
							if (iteBackMsg4->BackTrackN != 0)
							{
								stFusCom.lAutonum +=2000;  //当返回信息中有航迹,将综合批号增加2000,变为9000
								TFlag = 1;  //标记为1,代表改变综合批号
								break;
							}
						}
					}

					stFusCom.lTargetNumber = iteReCom->lTargetNumber; //目标批号
					strcpy(stFusCom.cModulationStyle ,iteReCom->cModulationStyle); //调制样式
					strcpy(stFusCom.cSignalType , iteReCom->cSignalType);  //信号类型
					strcpy(stFusCom.cEquipmentNumber , iteReCom->cEquipmentNumber);  //设备编号
					strcpy(stFusCom.cEquipmentType,iteReCom->cEquipmentType); //设备类型
					strcpy(stFusCom.cDWAttribute , iteReCom->cDWAttribute);   //敌我属性
					strcpy(stFusCom.cCountry , iteReCom->cCountry);           //国家/地区
					strcpy(stFusCom.cPlatName , iteReCom->cPlatName); //平台名称
					strcpy(stFusCom.cPlatNumber, iteReCom->cPlatNumber);//平台编号
					stCoFusiInfor.vctFusCom.push_back(stFusCom);
			}//for( iteReEsm = iteReqMsg->vctEsm.begin()
		}//if( iteReqMsg->vctEsm.size() !=0 )
		//请求信息中的每条信息都遍历完成后或者是请求信息中无ESM信息,若返回信息中还有信息的融合标记不为1,说明未被融合,则补充原来的信息
// 		for( iteBackMsg3 = vctBackMsg.begin(); iteBackMsg3 != vctBackMsg.end(); iteBackMsg3++ )
// 		{ //遍历返回信息中的每个结构体的ESM容器的每条COM的信息
// 			if(iteBackMsg->vctComm.size() != 0 )
//  			{
// 				for( iteBaCom1 = iteBackMsg->vctComm.begin(); iteBaCom1 != iteBackMsg->vctComm.end(); iteBaCom1++)
// 				{
//  					if ( iteBaCom1->lFusFlag != 0 ) 					
// 					{
// 						if( TFlag == 1 )  //代表综合批号需加2000
// 						{
// 							iteBaCom1->lAutonum += 2000;
// 							stCoFusiInfor.vctFusCom.push_back(*iteBaCom1);
// 						}
// 						
// 					}//if iteBaEsm1->lFusFlag != 0
// 				}//for
// 			}
// 		}//for
			vctCoFusMsg.push_back(stCoFusiInfor);
	}//for 每一条请求信息
}




// 	for ( iteReqMsg = vctReqMsg.begin(); iteReqMsg != vctReqMsg.end(); iteReqMsg++)
// 	{
// 		int TFlag = 0;
// 		if( iteReqMsg->vctEsm.size() !=0 )
// 		{//遍历请求信息中的ESM的每一条
// 			for( iteReEsm = iteReqMsg->vctEsm.begin(); iteReEsm != iteReqMsg->vctEsm.end(); iteReEsm++)
// 			{
// 				 nNumESMDOAz = 1;//ESM信号的到达方位（弧度）
// 				 nNumESMFre = 1;//ESM信号的频率（GHz）
// 				 nNumESMPA = 1;//ESM信号的幅度
// 				 nNumESMPzw = 1;//ESM信号的脉冲宽度（us）
// 				 nNumESMPRI = 1;//ESM信号的重复间隔（ms）;重复频率PRF=PRI的倒数
// 				 nNumESMSCan = 1;//ESM信号的侦察雷达天线扫描周期（s）
// 				//将请求信息中的各特征参数先赋给融合数据结构
// 				stFusEsm.dReachAzimuth = iteReEsm->dReachAzimuth; 
// 				stFusEsm.dZaiPin = iteReEsm->dZaiPin;
// 				stFusEsm.dPulseExtent = iteReEsm->dPulseExtent;
// 				stFusEsm.dMaiKuan = iteReEsm->dMaiKuan;
// 				stFusEsm.dChongPin = iteReEsm->dChongPin;
// 				stFusEsm.dTianXianScan = iteReEsm->dTianXianScan;
// 				//遍历返回信息中的每个结构体
// 				for( iteBackMsg = vctBackMsg.begin(); iteBackMsg != vctBackMsg.end(); iteBackMsg++ )
// 				{   //判断请求信息和返回信息中的综合批号是否相同,若相同再进行处理
// 					if (iteReqMsg->lAutonum == iteBackMsg->lAutonum)
// 					{
// 						//(暂不存在该种情况(1),可完善)
// 						//(1)若请求信息为无航迹,返回信息中有航迹,则要把融合后的综合批号改为大于等于9000 ,不能按照请求信息的7000来编批
// 						//遍历返回信息中的每个结构体的ESM容器的每条ESM的信息
// 						for( iteBaEsm = iteBackMsg->vctEsm.begin(); iteBaEsm != iteBackMsg->vctEsm.end(); iteBaEsm++)
// 						{
// 							//集对分析,求关联度
// 							//ESM信号的到达方位（弧度）
// 							//ESM信号的频率（GHz）
// 							//ESM信号的幅度
// 							//ESM信号的脉冲宽度（us）
// 							//ESM信号的重复间隔（ms）;重复频率PRF=PRI的倒数
// 							//ESM信号的侦察雷达天线扫描周期（s）
// 							double SumCorr = 0.0;
// 							Mf_SPA(iteBaEsm->dReachAzimuth,iteReEsm->dReachAzimuth,dcorrEsmReachAzimuth); //ESM信号的到达方位（弧度）
// 							VctCorr.push_back(dcorrEsmReachAzimuth);
// 							Mf_SPA(iteBaEsm->dZaiPin,iteReEsm->dZaiPin,dcorrZaiPin); //ESM信号的频率（GHz）
// 							VctCorr.push_back(dcorrZaiPin);
// 							Mf_SPA(iteBaEsm->dPulseExtent,iteReEsm->dPulseExtent,dcorrEsmPulseExtent); //ESM信号的幅度
// 							VctCorr.push_back(dcorrEsmPulseExtent);
// 							Mf_SPA(iteBaEsm->dMaiKuan,iteReEsm->dMaiKuan,dcorrMaiKuan); //ESM信号的脉冲宽度（us）
// 							VctCorr.push_back(dcorrMaiKuan);
// 							Mf_SPA(iteBaEsm->dChongPin,iteReEsm->dChongPin,dcorrChongPin); //ESM信号的重复间隔（ms）;重复频率PRF=PRI的倒数
// 							VctCorr.push_back(dcorrChongPin);
// 							Mf_SPA(iteBaEsm->dTianXianScan,iteReEsm->dTianXianScan,dcorrTianXianScan); //ESM信号的侦察雷达天线扫描周期（s）
// 							VctCorr.push_back(dcorrTianXianScan);
// 							//对相关系数容器处理，取容器中数据的平均值
// 							for (iteCorr = VctCorr.begin(); iteCorr != VctCorr.end(); iteCorr++)
// 							{
// 								SumCorr = SumCorr + *iteCorr;  
// 							}
// 							dAverCorr = SumCorr/VctCorr.size();  //取相关系数的平均值
// 							//下次存放集对系数前先清空VctCorr容器
// 							VctCorr.clear();
// 							//与阈值比较（设定阈值，相关系数大于某阈值时，认为ESM是可以关联的）
// 							if (dAverCorr > 0.8) 
// 							{
// 								iteBaEsm->lFusFlag = 1; //融合查找标记,能够关联
// 								//将关联信息的特征参数累加,并记录累加个数
// 								stFusEsm.dReachAzimuth += iteBaEsm->dReachAzimuth;
// 								nNumESMDOAz++;
// 								stFusEsm.dZaiPin += iteBaEsm->dZaiPin;
// 								nNumESMFre ++;//ESM信号的频率（GHz）
// 								stFusEsm.dPulseExtent += iteBaEsm->dPulseExtent;
// 								nNumESMPA ++;//ESM信号的幅度
// 								stFusEsm.dMaiKuan += iteBaEsm->dMaiKuan;
// 								nNumESMPzw ++;//ESM信号的脉冲宽度（us）
// 								stFusEsm.dChongPin += iteBaEsm->dChongPin;
// 								nNumESMPRI ++;//ESM信号的重复间隔（ms）;重复频率PRF=PRI的倒数
// 								stFusEsm.dTianXianScan += iteBaEsm->dTianXianScan;
// 								nNumESMSCan ++;
// 							}
// 						}//for( iteBaEsm = iteBackMsg->vctEsm.begin()	
// 					}// if 判断综合批号是否相同
// 				}//	for( iteBackMsg = vctBackMsg.begin()
// 				//每条请求信息的Esm结束之后,将各特征参数取平均值后,放入融合信息容器中
//                 stFusEsm.dReachAzimuth  =  stFusEsm.dReachAzimuth/nNumESMDOAz; 
// 				stFusEsm.dZaiPin = stFusEsm.dZaiPin/nNumESMFre;
// 				stFusEsm.dPulseExtent = stFusEsm.dPulseExtent/nNumESMPA;
// 				stFusEsm.dMaiKuan = stFusEsm.dMaiKuan/nNumESMPzw;
// 				stFusEsm.dChongPin = stFusEsm.dChongPin/nNumESMPRI;
// 				stFusEsm.dTianXianScan = stFusEsm.dTianXianScan/nNumESMSCan;
// 				//将请求信息的其他参数赋值给融合信息,如:联合识别的平台类型和综合可信度
// 				//逆序查找,从容器最后一个数据开始遍历, 综合识别结果中的当前的该批号识别出的平台类型和综合可信度
// 				stFusEsm.lAutonum = iteReqMsg->lAutonum;  //综合批号
//                 for ( r_iteMIdenti = vctMidentiinforMsg.rbegin(); r_iteMIdenti != vctMidentiinforMsg.rend(); ++r_iteMIdenti )
//                 {
// 					// 逆序查找 
// 					if ( r_iteMIdenti->lAutonum == stFusEsm.lAutonum )
// 					{
// 						strcpy( stFusEsm.sPlatType, r_iteMIdenti->sPlatType ); //综合平台类型
// 						stFusEsm.dConfidence = r_iteMIdenti->dConfidence;  //综合可行度
// 						break;
// 					}
//                 }
// 				for( iteBackMsg2 = vctBackMsg.begin(); iteBackMsg2 != vctBackMsg.end(); iteBackMsg2++ )
// 				{
// 					if ( iteReqMsg->lAutonum <8000 ) //请求信息中无航迹信息
// 					{
// 						if (iteBackMsg2->BackTrackN != 0)
// 						{
// 							stFusEsm.lAutonum +=2000;  //当返回信息中有航迹,将综合批号增加2000,变为9000
// 							 TFlag = 1;  //标记为1,代表改变综合批号
// 							break;
// 						}
// 					}
// 				}
// 
// 				stFusEsm.lTargetNumber = iteReEsm->lTargetNumber; //目标批号
// 				strcpy(stFusEsm.cEquipmentNumber , iteReEsm->cEquipmentNumber);  //设备编号
// 				strcpy(stFusEsm.cEquipmentType,iteReEsm->cEquipmentType); //设备类型
// 				strcpy(stFusEsm.cDWAttribute , iteReEsm->cDWAttribute);   //敌我属性
// 				strcpy(stFusEsm.cCountry , iteReEsm->cCountry);           //国家/地区
//                 strcpy(stFusEsm.cPlatName , iteReEsm->cPlatName); //平台名称
// 				strcpy(stFusEsm.cPlatNumber, iteReEsm->cPlatNumber);//平台编号
// 				strcpy(stFusEsm.cRadarName, iteReEsm->cRadarName);//雷达名称
// 				strcpy(stFusEsm.cRadarPurpose, iteReEsm->cRadarPurpose);//雷达用途
//                 stCoFusiInfor.vctFusEsm.push_back(stFusEsm);
// 			}//for( iteReEsm = iteReqMsg->vctEsm.begin()
// 		}//if( iteReqMsg->vctEsm.size() !=0 )
// 		//请求信息中的每条信息都遍历完成后或者是请求信息中无ESM信息,若返回信息中还有信息的融合标记不为1,说明未被融合,则补充原来的信息
// 		for( iteBackMsg1 = vctBackMsg.begin(); iteBackMsg1 != vctBackMsg.end(); iteBackMsg1++ )
// 		{ //遍历返回信息中的每个结构体的ESM容器的每条ESM的信息
// 			for( iteBaEsm1 = iteBackMsg->vctEsm.begin(); iteBaEsm1 != iteBackMsg->vctEsm.end(); iteBaEsm1++)
// 			{
// 				if ( iteBaEsm1->lFusFlag != 0 )
// 				{
// 					if( TFlag == 1 )  //代表综合批号需加2000
// 					{
// 						iteBaEsm1->lAutonum += 2000;
// 					}
// 					stCoFusiInfor.vctFusEsm.push_back(*iteBaEsm1);
// 				}//if iteBaEsm1->lFusFlag != 0
// 			}//for
// 		}//for
// 		//	vctCoFusMsg.push_back(stCoFusiInfor.vctFusEsm);
// 
// 	}//for 每一条请求信息


// 		for ( iteReqMsg = vctReqMsg.begin(); iteReqMsg != vctReqMsg.end(); iteReqMsg++)
// 		{
// 			int TFlag = 0;
// 			if( iteReqMsg->vctComm.size() !=0 )
// 			{//遍历请求信息中的ESM的每一条
// 				for( iteReCom = iteReqMsg->vctComm.begin(); iteReCom != iteReqMsg->vctComm.end(); iteReCom++)
// 				{
// 					int nNumCOMDOAz = 1; //COM信号的到达方位（弧度）   
// 					int nNumCOMFre = 1;  //COM信号的中心频率（MHz）
// 					int nNumCOMPA = 1; 	//COM信号的幅度
// 					int nNumCOMBand = 1; //COM信号的信号带宽（MHz）
// 					int nNumCOMJPN = 1; //COM信号的跳步次数
// 					//将请求信息中的各特征参数先赋给融合数据结构
// 					stFusCom.dReachAzimuth = iteReCom->dReachAzimuth; 
// 					stFusCom.dComFre = iteReCom->dComFre;
// 					stFusCom.dPulseExtent= iteReCom->dPulseExtent;
// 					stFusCom.dComBand = iteReCom->dComBand;
// 					stFusCom.dComJPN = iteReCom->dComJPN;
// 					//遍历返回信息中的每个结构体
// 					for( iteBackMsg = vctBackMsg.begin(); iteBackMsg != vctBackMsg.end(); iteBackMsg++ )
// 					{   //判断请求信息和返回信息中的综合批号是否相同,若相同再进行处理
// 						if (iteReqMsg->lAutonum == iteBackMsg->lAutonum)
// 						{
// 							//(暂不存在该种情况(1),可完善)
// 							//(1)若请求信息为无航迹,返回信息中有航迹,则要把融合后的综合批号改为大于等于9000 ,不能按照请求信息的7000来编批
// 							//遍历返回信息中的每个结构体的ESM容器的每条ESM的信息
// 							for( iteBaCom = iteBackMsg->vctComm.begin(); iteBaCom != iteBackMsg->vctComm.end(); iteBaCom++)
// 							{
// 								//集对分析,求关联度
// 								//COM信号的到达方位（弧度）
// 								//COM信号的中心频率（MHz）
// 								//COM信号的幅度
// 								//COM信号的信号带宽（MHz）
// 								//COM信号的跳步次数
// 								double SumCorr = 0.0;
// 								Mf_SPA(iteBaCom->dReachAzimuth,iteReCom->dReachAzimuth,dcorrComReachAzimuth); //COM信号的到达方位（弧度）
// 								VctCorr.push_back(dcorrComReachAzimuth);
// 								Mf_SPA(iteBaCom->dComFre,iteReCom->dComFre,dcorrFre); //COM信号的中心频率（MHz）
// 								VctCorr.push_back(dcorrFre);
// 								Mf_SPA(iteBaCom->dPulseExtent,iteReCom->dPulseExtent,dcorrComPulseExtent); //COM信号的幅度
// 								VctCorr.push_back(dcorrComPulseExtent);
// 								Mf_SPA(iteBaCom->dComBand,iteReCom->dComBand,dcorrBand); //COM信号的信号带宽（MHz）
// 								VctCorr.push_back(dcorrBand);
// 								Mf_SPA(iteBaCom->dComJPN,iteReCom->dComJPN,dcorrJPN); //COM信号的跳步次数
// 								VctCorr.push_back(dcorrJPN);
// 								//对相关系数容器处理，取容器中数据的平均值
// 								for (iteCorr = VctCorr.begin(); iteCorr != VctCorr.end(); iteCorr++)
// 								{
// 									SumCorr = SumCorr + *iteCorr;  
// 								}
// 								dAverCorr = SumCorr/VctCorr.size();  //取相关系数的平均值
// 								//下次存放集对系数前先清空VctCorr容器
// 								VctCorr.clear();
// 								//与阈值比较（设定阈值，相关系数大于某阈值时，认为COM是可以关联的）
// 								if (dAverCorr > 0.8) 
// 								{
// 									iteBaEsm->lFusFlag = 1; //融合查找标记,能够关联
// 									//将关联信息的特征参数累加,并记录累加个数
// 									stFusCom.dReachAzimuth += iteBaCom->dReachAzimuth;
// 									nNumCOMDOAz++;
// 									stFusCom.dComFre += iteBaCom->dComFre;
// 									nNumCOMFre ++;//cOM信号的频率（GHz）
// 									stFusCom.dPulseExtent += iteBaCom->dPulseExtent;
// 									nNumCOMPA ++;//com信号的幅度
// 									stFusCom.dComBand += iteBaCom->dComBand;
// 									nNumCOMBand ++;//COM信号的信号带宽（MHz）
// 									stFusCom.dComJPN += iteBaCom->dComJPN;
// 									nNumCOMJPN ++;//COM信号的跳步次数
// 								}
// 							}//for( iteBaEsm = iteBackMsg->vctEsm.begin()	
// 						}// if 判断综合批号是否相同
// 					}//	for( iteBackMsg = vctBackMsg.begin()
// 					//每条请求信息的Esm结束之后,将各特征参数取平均值后,放入融合信息容器中
// 					stFusCom.dReachAzimuth  =  stFusEsm.dReachAzimuth/nNumCOMDOAz; 
// 					stFusCom.dComFre = stFusCom.dComFre/nNumCOMFre;
// 					stFusCom.dPulseExtent = stFusCom.dPulseExtent/nNumCOMPA;
// 					stFusCom.dComBand = stFusCom.dComBand/nNumCOMBand;
// 					stFusCom.dComJPN = stFusCom.dComJPN /nNumCOMJPN;
// 					//将请求信息的其他参数赋值给融合信息,如:联合识别的平台类型和综合可信度
// 					//逆序查找,从容器最后一个数据开始遍历, 综合识别结果中的当前的该批号识别出的平台类型和综合可信度
// 					stFusCom.lAutonum = iteReqMsg->lAutonum;  //综合批号
// 					for ( r_iteMIdenti = vctMidentiinforMsg.rbegin(); r_iteMIdenti != vctMidentiinforMsg.rend(); ++r_iteMIdenti )
// 					{
// 						// 逆序查找 
// 						if ( r_iteMIdenti->lAutonum == stFusCom.lAutonum )
// 						{
// 							strcpy( stFusCom.sPlatType, r_iteMIdenti->sPlatType ); //综合平台类型
// 							stFusCom.dConfidence = r_iteMIdenti->dConfidence;  //综合可行度
// 							break;
// 						}
// 					}
// 					for( iteBackMsg2 = vctBackMsg.begin(); iteBackMsg2 != vctBackMsg.end(); iteBackMsg2++ )
// 					{
// 						if ( iteReqMsg->lAutonum <8000 ) //请求信息中无航迹信息
// 						{
// 							if (iteBackMsg2->BackTrackN != 0)
// 							{
// 								stFusCom.lAutonum +=2000;  //当返回信息中有航迹,将综合批号增加2000,变为9000
// 								TFlag = 1;  //标记为1,代表改变综合批号
// 								break;
// 							}
// 						}
// 					}
// 
// 					stFusCom.lTargetNumber = iteReCom->lTargetNumber; //目标批号
// 					strcpy(stFusCom.cEquipmentNumber , iteReCom->cEquipmentNumber);  //设备编号
// 					strcpy(stFusCom.cEquipmentType,iteReCom->cEquipmentType); //设备类型
// 					strcpy(stFusCom.cDWAttribute , iteReCom->cDWAttribute);   //敌我属性
// 					strcpy(stFusCom.cCountry , iteReCom->cCountry);           //国家/地区
// 					strcpy(stFusCom.cPlatName , iteReCom->cPlatName); //平台名称
// 					strcpy(stFusCom.cPlatNumber, iteReCom->cPlatNumber);//平台编号
// 					stCoFusiInfor.vctFusCom.push_back(stFusCom);
// 			}//for( iteReEsm = iteReqMsg->vctEsm.begin()
// 		}//if( iteReqMsg->vctEsm.size() !=0 )
// 		//请求信息中的每条信息都遍历完成后或者是请求信息中无ESM信息,若返回信息中还有信息的融合标记不为1,说明未被融合,则补充原来的信息
// 		for( iteBackMsg1 = vctBackMsg.begin(); iteBackMsg1 != vctBackMsg.end(); iteBackMsg1++ )
// 		{ //遍历返回信息中的每个结构体的ESM容器的每条ESM的信息
// 			for( iteBaCom1 = iteBackMsg->vctComm.begin(); iteBaCom1 != iteBackMsg->vctComm.end(); iteBaCom1++)
// 			{
// 				if ( iteBaCom1->lFusFlag != 0 )
// 				{
// 					stCoFusiInfor.vctFusCom.push_back(*iteBaCom1);
// 					
// 					if( TFlag == 1 )  //代表综合批号需加2000
// 					{
// 						iteBaCom1->lAutonum += 2000;
// 					}
// 				}//if iteBaEsm1->lFusFlag != 0
// 			}//for
// 		}//for
// 		//	vctCoFusMsg.push_back(stCoFusiInfor.vctFusCom);
// 	}//for 每一条请求信息

/*} //函数结束*/

/************************************************************************/
/*                             集对分析算子                             */
/************************************************************************/
// void Mf_SPA(double s, double t,double& corr)
// {
// 	double spa;
// 	double tmp;
// 	
// 	double a,b,c;
// 	
// 	if(s>t)
// 	{
// 		tmp =s;
// 		s=t;
// 		t=tmp;
// 	}
// 	
// 	a=s/t;
// 	b=s/t/(t*t-1);
// 	c=(t*t-s*t-1)/(t*t-1);
// 	
// 	spa=a+fabs(b)-fabs(c);
// 	
// 	corr=spa;                 //带回两数相关系数
// }