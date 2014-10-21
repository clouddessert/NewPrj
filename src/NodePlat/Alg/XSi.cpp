
/*****************邻舰请求 0811 wanghaiying*****************/
//1. 读取协同信息，判断有无目标航迹（先根据聚类标志，判断是否聚类过，对已经聚过类的判断综合批号，大于8000的为有航迹信息，小于8000的为无航迹信息）
//     (1)有目标航迹：a. 坐标转换。将请求舰的目标航迹中的坐标转到本舰(本平台)雷达坐标系下
//                    b. 从<TRACE,ESM,COM>聚类表中，匹配查找与邻舰关联度最大的信息，返回给请求舰
//                    c. 若从上表中找不到匹配信息，则从<ESM,COM>聚类表,<ESM>单独表,<COM>单独表中匹配查找特征关联度最大的信息，返回给请求舰
//     (2)无目标航迹：a. 匹配查找ESM或通信特征关联度最大的信息，先从 <TRACE,ESM,COM>聚类表中查找。
//                    b. 若从上表中找不到匹配信息，则代表本舰中也无该目标的航迹信息----交叉定位获取(航迹信息发给请求舰)???
/*****************************************/

//请求信息中只有航迹的信息，从本舰的聚类结果中找出，指向同一目标的航迹信息。
//对请求信息VCT_Request_Cooperative_Msg中的Request_Cooperative_Msg结构体中的TRACKSTATUS_MARK航迹信息赋值,作为函数的输入参数

#include "XSi.h"
#include "stdafx.h" 
#include <iostream>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <vector>
using namespace std;  
#define PI 3.1415926535898

/********************************************************************************/
/********************************************************************************/
//分函数:
//根据请求信息中的综合批号来决定调用哪一种函数
//(总批大于8000，即请求信息是聚类后有航迹的信息，调用函数1)
//(总批号在7000到8000之间，即请求信息是聚类后无航迹的信息，调用函数2)
//(总批号小于7000，即为目标批号，请求信息为未聚类的航迹信息，调用函数3)
void ReqUnin_COOP_Find_Information_To_MainShip(SHIP_POSITION& stSelfPosi,UNI_All_NUM& stUniAll, VCT_Request_Cooperative_Msg::iterator& iteRequestMsg,/*VCT_Request_Cooperative_Msg& vctRequestCooperative,*/ VCT_BACK_Cooperative_Msg& vctBackCooperative);
void ReqNoTraceUnin_COOP_Find_Information_To_MainShip(SHIP_POSITION& stSelfPosi,UNI_All_NUM& stUniAll, VCT_Request_Cooperative_Msg::iterator& iteRequestMsg,/*VCT_Request_Cooperative_Msg& vctRequestCooperative, */VCT_BACK_Cooperative_Msg& vctBackCooperative);
void ReqSingleTrace_COOP_Find_Information_To_MainShip(SHIP_POSITION& stSelfPosi,UNI_All_NUM& stUniAll, VCT_Request_Cooperative_Msg::iterator & iteRequestMsg,/*VCT_Request_Cooperative_Msg& vctRequestCooperative,*/ VCT_BACK_Cooperative_Msg& vctBackCooperative);
// 本舰邻舰都有自身航迹信息时（即都存在距离方位俯仰角时），本舰邻舰经纬高都已知，输出邻舰观测到的目标在本舰上的坐标及相对于本舰的经纬高。
void Get_Coordinate_Conversion_Module(double Rd1,double Az1,double Ez1,double Rd2,double Az2,double Ez2,double La1,double Ba1,double Ha1,
									  double La2,double Ba2,double Ha2,/*double *x1,double *y1,double *z1,*/double& Xt,double& Yt,double& Zt,double& Rdt,double& Azt,double& Ezt,double& SumCorr);
void Mf_SPA(double s, double t,double& corr); //s,t为相同类型的信息，进行集对分析，将返回的相关系数存入容器VctCorr中
void Get_NO_SelfTrack_Coordinate_Conversion_Module(double Rd2,double Az2,double Ez2,double La1,double Ba1,double Ha1,
												   double La2,double Ba2,double Ha2,double& Xt,double& Yt,double& Zt);
void Object_Radar_Transform(double Lt,double Bt,double Ht,double L0,double B0,double H0,double& rd,double& az,double& ez);
/********************************************************************************/
/********************************************************************************/


//请求信息：有航迹的聚类信息，综合批号大于7999
void ReqUnin_COOP_Find_Information_To_MainShip(SHIP_POSITION& stSelfPosi,UNI_All_NUM& stUniAll, VCT_Request_Cooperative_Msg::iterator & iteRequestMsg,/*VCT_Request_Cooperative_Msg& vctRequestCooperative,*/ VCT_BACK_Cooperative_Msg& vctBackCooperative)
{
//测试 	int a = iteRequestMsg->lAutonum;
	double Xt = 0.0;        //定义变量时，不要定义在IF 与for循环中，定义到外部，作为全局变量
	double Yt = 0.0;
	double Zt = 0.0;
	double Rdt = 0.0;
	double Azt = 0.0;
	double Ezt = 0.0;
	double dSumCorr_xyz = 0.0;
	double dcorrRd = 0.0;
	double dcorrAz = 0.0;
	double dcorrEz = 0.0;
	double dcorrVx = 0.0;
	double dcorrVy = 0.0;
	double dcorrVz = 0.0;
	double dcorrChongPin = 0.0;
	double dcorrMaiKuan = 0.0;
	double dcorrTianXianScan =0.0;
	double dcorrComZaiPin =0.0;
    double dcorrdPulseExtent = 0.0;
	double dcorrBand = 0.0;
	double dcorrJPN = 0.0;
	//  double SumCorr = 0.0;
    double dAverCorr = 0.0; //各测量信息，集对分析后，取平均值后的相关系数
	//  TRACKSTATUS_MARK sttTrack;
	//	ESMSTATUS_MARK sttEsm;
	//	COMSTATUS_MARK sttCom;
    typedef vector<double> VCT_CORR;
	VCT_CORR VctCorr;      // 存放关联系数的容器
	VCT_CORR::iterator iteCorr;
	//  用来清空的迭代器
	//  在vctRequestCooperative容器中，三个容器（存放每类传感器信息）的迭代器
	//    VCT_TRACE_MSG::iterator iteTrace; //因为每个结构体中若有航迹，只存在一条航迹，直接用航迹信息的结构体
	VCT_ESM_MSG::iterator iteEsm;                
	VCT_COMM_MSG::iterator iteCom;
	//有航迹
	VCT_UNINUM_MSG::iterator iteUnin;
	//有航迹 两个容器（Esm,Com）的迭代器
	//	VCT_ESM_MSG::iterator iteUninEs;
	//	VCT_COMM_MSG::iterator iteUninCo;
	
	//无航迹
	VCT_UNINOTRACE_MSG::iterator iteNoTraceUnin;
	//无航迹 两个容器（ESM，com）的迭代器
	VCT_ESM_MSG::iterator iteNoTraceEs;
	VCT_ESM_MSG::iterator iteNoTraceEs1;
	VCT_COMM_MSG::iterator iteNoTraceCo;
	VCT_COMM_MSG::iterator iteNoTraceCo1;
	
	//未聚类 三个容器（存放每类传感器信息）的迭代器
	VCT_TRACE_MSG::iterator iteTra;
	VCT_ESM_MSG::iterator iteEs;
	VCT_COMM_MSG::iterator iteCo;
	
	VCT_BACK_Cooperative_Msg::iterator iteBackMsg;
	BACK_Cooperative_Msg stBackMsg;
	//	VCT_Request_Cooperative_Msg::iterator iteRequestMsg;
	//请求信息中 ESM，COM容器（存放每类传感器信息）的迭代器
	VCT_ESM_MSG::iterator re_iteEs;
	VCT_COMM_MSG::iterator re_iteCo;
	
	//清空 vctBackCooperative
	for (iteBackMsg = vctBackCooperative.begin(); iteBackMsg != vctBackCooperative.end(); iteBackMsg++)
	{	
		//清空 vctBackCooperative
		iteBackMsg->lAutonum = NULL;
		iteBackMsg->nStampTime = NULL;
 	//	iteBackMsg->dAzimuth = NULL;
 	//	iteBackMsg->dElevationAngle = NULL;
	//	iteBackMsg->dRange = NULL;
		iteBackMsg->BackTrackN = NULL;
		iteBackMsg->BackESMN = NULL;
		iteBackMsg->BackCOMN = NULL;
		memset(&iteBackMsg->stBackShipPosi,0 ,sizeof(iteBackMsg->stBackShipPosi));
		memset(&iteBackMsg->stTrace, 0, sizeof(TRACKSTATUS_MARK));
		for ( iteEsm = iteBackMsg->vctEsm.begin(); iteEsm != iteBackMsg->vctEsm.end(); iteEsm++)
		{
			memset(&(*iteEsm), 0, sizeof(ESMSTATUS_MARK));
		}
		for ( iteCom = iteBackMsg->vctComm.begin(); iteCom != iteBackMsg->vctComm.end();iteCom++)
		{
			memset(&(*iteCom), 0, sizeof(COMSTATUS_MARK));
		}
		//		iteBackMsg->vctTrace.clear();
		iteBackMsg->vctEsm.clear();
		iteBackMsg->vctComm.clear();
	}
	vctBackCooperative.clear();
	
    for ( iteUnin = stUniAll.vctUnin.begin(); iteUnin != stUniAll.vctUnin.end(); iteUnin++)
	{   
	    double dSumCorr = 0.0;
		Get_Coordinate_Conversion_Module(iteUnin->structTrace.dRange,iteUnin->structTrace.dAzimuth,iteUnin->structTrace.dElevationAngle,
		iteRequestMsg->stTrace.dRange,iteRequestMsg->stTrace.dAzimuth,iteRequestMsg->stTrace.dElevationAngle,
		stSelfPosi.dLati,stSelfPosi.dLonti,stSelfPosi.dHeight,
		iteRequestMsg->stReqShipPosi.dLati,iteRequestMsg->stReqShipPosi.dLonti,iteRequestMsg->stReqShipPosi.dHeight,
		Xt, Yt, Zt, Rdt, Azt, Ezt, dSumCorr_xyz);
	    //VctCorr.push_back(dSumCorr_xyz); 
		////对航迹结构体中的测量信息进行集对分析,还有 Vx,Vy,Vz(目标在邻舰的坐标系下各坐标方向上的绝对速度需要转换到本舰坐标系下才能用吗????????)
		//Mf_SPA(iteUnin->structTrace.dRange,Rdt,corrRd);
		//VctCorr.push_back(dcorrRd);
		//Mf_SPA(iteUnin->structTrace.dAzimuth,Azt,corrAz);
		//VctCorr.push_back(dcorrAz);
		//Mf_SPA(iteUnin->structTrace.dElevationAngle,Ezt,corrEz); 
		//VctCorr.push_back(dcorrEz);
		//各方向坐标下的绝对速度Vx,Vy,Vz未转换，直接做集对分析处理
	    Mf_SPA(iteUnin->structTrace.dTSpeedX,iteRequestMsg->stTrace.dTSpeedX,dcorrVx);
		VctCorr.push_back(dcorrVx);
		Mf_SPA(iteUnin->structTrace.dTSpeedY,iteRequestMsg->stTrace.dTSpeedY,dcorrVy);
		VctCorr.push_back(dcorrVy);
		Mf_SPA(iteUnin->structTrace.dTSpeedZ,iteRequestMsg->stTrace.dTSpeedZ,dcorrVz);
		VctCorr.push_back(dcorrVz);
	    //对相关系数容器处理，取容器中数据的平均值
	    for (iteCorr = VctCorr.begin(); iteCorr != VctCorr.end(); iteCorr++)
		{
		   dSumCorr = dSumCorr + *iteCorr;  
		}
		dAverCorr = dSumCorr/VctCorr.size();  //取相关系数的平均值
		//下次存放集对系数前先清空VctCorr容器
		VctCorr.clear();
		//与阈值比较（如何设定阈值，相关系数大于某阈值时，认为航迹是可以关联的????????????????????? 测试时修改）
		if (dAverCorr > 0.8) //0.8为阈值，测试时可调节
		{	//航迹信息可以关联，将信息放入vctBackCooperative返回信息容器中，
			//将同一合批号下（即相同方位下）的一条航迹信息，还有N条ESM与Com信息放入vctBackCooperative中
			//测试输出			
			//				cout<<"综合批号"<< iteUnin->lAutonum<<endl;
			//				cout<<"返回信息初始化的综合批号"<<iteBackMsg->lAutonum<<endl;
			//存请求信息的综合批号到返回信息中
			stBackMsg.lAutonum = iteRequestMsg->lAutonum;    //将请求信息的综合批号记录在返回信息中
			//				cout<<"修改后返回信息综合批号"<<stBackMsg.lAutonum<<endl;
			//存本舰经纬高到返回信息中
			memcpy(&stBackMsg.stBackShipPosi,&stSelfPosi,sizeof(stBackMsg.stBackShipPosi));  //memcpy(&A,&B,sizeof(A)); 把结构体B给结构体A
			//存航迹信息
			memcpy(&stBackMsg.stTrace,&iteUnin->structTrace,sizeof(stBackMsg.stTrace));	
		
			//存ESM信息
			if (iteUnin->vctEsm.size() !=0)
			{
				for (iteEs = iteUnin->vctEsm.begin(); iteEs != iteUnin->vctEsm.end(); iteEs++)
				{
					stBackMsg.vctEsm.push_back(*iteEs);
				}
			}
			//存COM 信息
			if (iteUnin->vctComm.size() != 0)
			{
				for (iteCo = iteUnin->vctComm.begin(); iteCo != iteUnin->vctComm.end(); iteCo++)
				{
					stBackMsg.vctComm.push_back(*iteCo);
				}
			}
			stBackMsg.BackTrackN = 1;  //航迹条数计数
			stBackMsg.BackESMN = stBackMsg.vctEsm.size();
			stBackMsg.BackCOMN = stBackMsg.vctComm.size();
			
			//将查找到的信息存入vctBackCooperative容器中
			vctBackCooperative.push_back(stBackMsg);
			//测试输出     				
			//for (iteBackMsg = vctBackCooperative.begin(); iteBackMsg != vctBackCooperative.end(); iteBackMsg++)
			//{
			//int PiHao = iteBackMsg->lAutonum;
			//int Ts = iteBackMsg->BackTrackN;
			//int Es = iteBackMsg->BackESMN;
			//int Cs = iteBackMsg->BackCOMN;
			//cout<<"返回信息综合批号"<<iteBackMsg->lAutonum<<endl;
			//cout<<"       &返回信息的航迹信息....& 目标绝对速度 Vx: "<< iteBackMsg->stTrace.dTSpeedX <<"   Vy: "<<iteBackMsg->stTrace.dTSpeedY << "   Vz:"<<iteBackMsg->stTrace.dTSpeedZ <<endl;
			//cout<<"       &返回信息的识别信息....&"<<"　　　"<< iteBackMsg->stTrace.sPlatType <<"    " <<iteBackMsg->stTrace.cDWAttribute <<"   " <<iteBackMsg->stTrace.dConfidence<<endl;
			//cout<<"       &返回的航迹信息："<< iteBackMsg->BackTrackN <<" 条"<< endl;
			//cout<<"       &返回的ESM信息："<< iteBackMsg->BackESMN <<" 条"<<endl;
			//cout<<"       &返回的COM信息： "<< iteBackMsg->BackCOMN <<" 条"<<endl;
			//}
			iteRequestMsg->nCorrFlag = 1; // 直到找到与请求信息相关联的信息,将标志信息该为1，若一直找不到则标志始终为0；
			break;//找到，跳出循环
					//至此，从聚类表里取出关联信息【同一综合批号下（即相同方位下）的TRACE,ESM和COM信息】，存入vctBackCooperative容器中 
		}//0.8为阈值，测试时可调节
		//else 
		//{   
		//continue;
		//}//未找到关联信息	
	}//for  iteUnin 遍历有航迹聚类表（根据航迹坐标转换和集对分析）
	
	
	//一：<2> 
		  if ( iteRequestMsg->nCorrFlag == 0 ) //请求信息还未找到关联信息时 ，则遍历无航迹聚类表
		  {
			  if (iteRequestMsg->vctEsm.size() !=0)   //if请求信息中有ESM信息
			  {
				  if (iteRequestMsg->vctComm.size() !=0) //if 请求中有Com信息 ，当ESM 比较后没有关联信息，再比较COM 信息
				  {
					  for ( re_iteEs = iteRequestMsg->vctEsm.begin(); re_iteEs != iteRequestMsg->vctEsm.end();re_iteEs++)
					  {
						  //在无航迹的聚类表中查找,无航迹中必有ESM和COM信息
						  for (iteNoTraceUnin = stUniAll.vctNoTraceUnin.begin(); iteNoTraceUnin != stUniAll.vctNoTraceUnin.end(); iteNoTraceUnin++)
						  {  //本舰自身无航迹信息时
							  //是否还需坐标转换........		 Get_NO_SelfTrack_Coordinate_Conversion_Module(iteRequestMsg->stTrace.dRange,iteRequestMsg->stTrace.dAzimuth,iteRequestMsg->stTrace.dElevationAngle,
							  // 								 stSelfPosi.dLati,stSelfPosi.dLonti,stSelfPosi.dHeight,
							  // 								 iteRequestMsg->stReqShipPosi.dLati,iteRequestMsg->stReqShipPosi.dLonti,iteRequestMsg->stReqShipPosi.dHeight,
							  // 								 Xt,Yt,Zt);
							  //一：<2>a.
							  for (iteNoTraceEs = iteNoTraceUnin->vctEsm.begin(); iteNoTraceEs != iteNoTraceUnin->vctEsm.end(); iteNoTraceEs++ )
							  {
								  double dSumCorr = 0.0;
								  Mf_SPA(iteNoTraceEs->dChongPin,re_iteEs->dChongPin,dcorrChongPin); //频率
								  VctCorr.push_back(dcorrChongPin);
								  Mf_SPA(iteNoTraceEs->dMaiKuan,re_iteEs->dMaiKuan,dcorrMaiKuan); //脉宽
								  VctCorr.push_back(dcorrMaiKuan);
								  Mf_SPA(iteNoTraceEs->dTianXianScan,re_iteEs->dTianXianScan,dcorrTianXianScan); //天线扫描周期
								  VctCorr.push_back(dcorrTianXianScan);
								  //对相关系数容器处理，取容器中数据的平均值
								  for (iteCorr = VctCorr.begin(); iteCorr != VctCorr.end(); iteCorr++)
								  {
									  dSumCorr = dSumCorr + *iteCorr;  
								  }
								  dAverCorr = dSumCorr/VctCorr.size();  //取相关系数的平均值
								  //下次存放集对系数前先清空VctCorr容器
								  VctCorr.clear();
								  //与阈值比较（设定阈值，相关系数大于某阈值时，认为ESM是可以关联的）
								  if (dAverCorr > 0.8)
								  {
									  //将找到的ESM与同一综合批号下的COM信息存入vctBackCooperative容器中
									  stBackMsg.lAutonum = iteRequestMsg->lAutonum;  //将请求信息的综合批号记录在返回信息中
									  //存ESM信息
									  for ( iteNoTraceEs1 = iteNoTraceUnin->vctEsm.begin();iteNoTraceEs1 !=iteNoTraceUnin->vctEsm.end(); iteNoTraceEs1++)
									  {
										  stBackMsg.vctEsm.push_back(*iteNoTraceEs1);
									  }
									  //存COM 信息
									  if (iteNoTraceUnin->vctComm.size() != 0)
									  {
										  for (iteNoTraceCo = iteNoTraceUnin->vctComm.begin();iteNoTraceCo !=iteNoTraceUnin->vctComm.end(); iteNoTraceCo++)
										  {
											  stBackMsg.vctComm.push_back(*iteNoTraceCo);
										  }
									  }
									  stBackMsg.BackTrackN = 0;  //航迹条数计数
									  stBackMsg.BackESMN = stBackMsg.vctEsm.size();
									  stBackMsg.BackCOMN = stBackMsg.vctComm.size();
									  //将查找到的信息存入vctBackCooperative容器中
									  vctBackCooperative.push_back(stBackMsg);
									  iteRequestMsg->nCorrFlag = 1; // 直到找到与请求信息相关联的信息,将标志信息该为1，若一直找不到则标志始终为0；
									  break;
								  } //if AverCorr > 0.8 结束
								  // else { nosearchFlag = 2;}
							  }// for iteNoTraceEs	
							  if (iteRequestMsg->nCorrFlag == 1) //标志位1，代表有找到相关信息，则结束iteNoTraceUnin 的循环。
							  {
								  break;
							  }
							  // 在ESM 中没找到 ，继续iteNoTraceUnin的循环，比较下一个结构体中的多条ESM信息
							  
						  }//for iteNoTraceUnin
						  
						  if (iteRequestMsg->nCorrFlag == 1) //标志位1，代表有找到相关信息，则结束re_iteEs 的循环。
						  {
							  break;
						  } //否则，用请求信息中vctEsm中的下一条ESM与聚类表中的ESM比较
						  
					  }//for re_iteEs 遍历请求信息中的每条ESM信息
					  
					  if (iteRequestMsg->nCorrFlag == 0)  //遍历所有的ESM 还未找到，则遍历COM信息
					  {
						  for ( re_iteCo = iteRequestMsg->vctComm.begin(); re_iteCo != iteRequestMsg->vctComm.end();re_iteCo++)
						  {
							  //在无航迹的聚类表中查找,无航迹中必有ESM和COM信息
							  for (iteNoTraceUnin = stUniAll.vctNoTraceUnin.begin(); iteNoTraceUnin != stUniAll.vctNoTraceUnin.end(); iteNoTraceUnin++)
							  {  //本舰自身无航迹信息时
								  for (iteNoTraceCo = iteNoTraceUnin->vctComm.begin(); iteNoTraceCo != iteNoTraceUnin->vctComm.end(); iteNoTraceCo++ )
								  {
									  double dSumCorr = 0.0;
									  Mf_SPA(iteCo->dComZaiPin,re_iteCo->dComZaiPin,dcorrComZaiPin); //载频
									  VctCorr.push_back(dcorrComZaiPin);
									  Mf_SPA(iteCo->dPulseExtent,re_iteCo->dPulseExtent,dcorrdPulseExtent); //脉冲幅度
									  VctCorr.push_back(dcorrdPulseExtent);
								//0909修改:增加COM的集对分析数据:  带宽和跳频次数	 
									  Mf_SPA(iteCo->dComBand,re_iteCo->dComBand,dcorrBand);//带宽
									  VctCorr.push_back(dcorrBand);
									  Mf_SPA(iteCo->dComJPN,re_iteCo->dComJPN,dcorrJPN);//跳频次数
									  VctCorr.push_back(dcorrJPN);
									  
									  //对相关系数容器处理，取容器中数据的平均值
									  for (iteCorr = VctCorr.begin(); iteCorr != VctCorr.end(); iteCorr++)
									  {
										  dSumCorr = dSumCorr + *iteCorr;  
									  }
									  dAverCorr = dSumCorr/VctCorr.size();  //取相关系数的平均值
									  //下次存放集对系数前先清空VctCorr容器
									  VctCorr.clear();
									  //与阈值比较（设定阈值，相关系数大于某阈值时，认为ESM是可以关联的）
									  if (dAverCorr > 0.8)
									  {
										  //将找到的ESM与同一综合批号下的COM信息存入vctBackCooperative容器中
										  stBackMsg.lAutonum = iteRequestMsg->lAutonum;  //将请求信息的综合批号记录在返回信息中
										  //存ESM信息
										  for ( iteNoTraceEs = iteNoTraceUnin->vctEsm.begin();iteNoTraceEs !=iteNoTraceUnin->vctEsm.end(); iteNoTraceEs++)
										  {
											  stBackMsg.vctEsm.push_back(*iteNoTraceEs);
										  }
										  //存COM 信息
										  if (iteNoTraceUnin->vctComm.size() != 0)
										  {
											  for (iteNoTraceCo1 = iteNoTraceUnin->vctComm.begin();iteNoTraceCo1 !=iteNoTraceUnin->vctComm.end(); iteNoTraceCo1++)
											  {
												  stBackMsg.vctComm.push_back(*iteNoTraceCo1);
											  }
										  }
										  stBackMsg.BackTrackN = 0;  //航迹条数计数
										  stBackMsg.BackESMN = stBackMsg.vctEsm.size();
										  stBackMsg.BackCOMN = stBackMsg.vctComm.size();
										  //将查找到的信息存入vctBackCooperative容器中
										  vctBackCooperative.push_back(stBackMsg);
										  iteRequestMsg->nCorrFlag = 1; // 直到找到与请求信息相关联的信息,将标志信息该为1，若一直找不到则标志始终为0；
										  break;
									  } //if AverCorr > 0.8 结束
								  }// for iteNoTraceEs	
								  if (iteRequestMsg->nCorrFlag == 1) //标志位1，代表有找到相关信息，则结束iteNoTraceUnin 的循环。
								  {
									  break;
								  }
								  // 在COM 中没找到 ，继续iteNoTraceUnin的循环，比较下一个结构体中的多条com信息
								  
							  }//for iteNoTraceUnin
							  
							  if (iteRequestMsg->nCorrFlag == 1) //标志位1，代表有找到相关信息，则结束re_iteCo 的循环。
							  {
								  break;
							  } //否则，用请求信息中vctCom中的下一条Com与聚类表中的com比较	 
							  
						  }//for re_iteCo 遍历请求信息中的每条COM信息
						  
					  }// if 遍历所有的ESM 还未找到,则遍历COM信息 结束
					  
					 } // if请求中有COM信息 结束
					 
					 else //else 请求信息中只有ESM，没有COM, 只能ESM比较
					 {
						 for ( re_iteEs = iteRequestMsg->vctEsm.begin(); re_iteEs != iteRequestMsg->vctEsm.end();re_iteEs++)
						 {
							 //在无航迹的聚类表中查找,无航迹中必有ESM和COM信息
							 for (iteNoTraceUnin = stUniAll.vctNoTraceUnin.begin(); iteNoTraceUnin != stUniAll.vctNoTraceUnin.end(); iteNoTraceUnin++)
							 {  //本舰自身无航迹信息时
								 for (iteNoTraceEs = iteNoTraceUnin->vctEsm.begin(); iteNoTraceEs != iteNoTraceUnin->vctEsm.end(); iteNoTraceEs++ )
								 {
									 double dSumCorr = 0.0;
									 Mf_SPA(iteNoTraceEs->dChongPin,re_iteEs->dChongPin,dcorrChongPin); //频率
									 VctCorr.push_back(dcorrChongPin);
									 Mf_SPA(iteNoTraceEs->dMaiKuan,re_iteEs->dMaiKuan,dcorrMaiKuan); //脉宽
									 VctCorr.push_back(dcorrMaiKuan);
									 Mf_SPA(iteNoTraceEs->dTianXianScan,re_iteEs->dTianXianScan,dcorrTianXianScan); //天线扫描周期
									 VctCorr.push_back(dcorrTianXianScan);
									 //对相关系数容器处理，取容器中数据的平均值
									 for (iteCorr = VctCorr.begin(); iteCorr != VctCorr.end(); iteCorr++)
									 {
										 dSumCorr = dSumCorr + *iteCorr;  
									 }
									 dAverCorr = dSumCorr/VctCorr.size();  //取相关系数的平均值
									 //下次存放集对系数前先清空VctCorr容器
									 VctCorr.clear();
									 //与阈值比较（设定阈值，相关系数大于某阈值时，认为ESM是可以关联的）
									 if (dAverCorr > 0.8)
									 {
										 //将找到的ESM与同一综合批号下的COM信息存入vctBackCooperative容器中
										 stBackMsg.lAutonum = iteRequestMsg->lAutonum;  //将请求信息的综合批号记录在返回信息中
										 //存ESM信息
										 for ( iteNoTraceEs1 = iteNoTraceUnin->vctEsm.begin();iteNoTraceEs1 !=iteNoTraceUnin->vctEsm.end(); iteNoTraceEs1++)
										 {
											 stBackMsg.vctEsm.push_back(*iteNoTraceEs1);
										 }
										 //存COM 信息
										 if (iteNoTraceUnin->vctComm.size() != 0)
										 {
											 for (iteNoTraceCo = iteNoTraceUnin->vctComm.begin();iteNoTraceCo !=iteNoTraceUnin->vctComm.end(); iteNoTraceCo++)
											 {
												 stBackMsg.vctComm.push_back(*iteNoTraceCo);
											 }
										 }
										 stBackMsg.BackTrackN = 0;  //航迹条数计数
										 stBackMsg.BackESMN = stBackMsg.vctEsm.size();
										 stBackMsg.BackCOMN = stBackMsg.vctComm.size();
										 //将查找到的信息存入vctBackCooperative容器中
										 vctBackCooperative.push_back(stBackMsg);
										 iteRequestMsg->nCorrFlag = 1; // 直到找到与请求信息相关联的信息,将标志信息该为1，若一直找不到则标志始终为0；
										 break;
									 } //if AverCorr > 0.8 结束
									 // else { nosearchFlag = 2;}
								 }// for iteNoTraceEs	
								 if (iteRequestMsg->nCorrFlag == 1) //标志位1，代表有找到相关信息，则结束iteNoTraceUnin 的循环。
								 {
									 break;
								 }
								 // 在ESM 中没找到 ，继续iteNoTraceUnin的循环，比较下一个结构体中的多条ESM信息
								 
							 }//for iteNoTraceUnin
						 }// for  re_iteEs
						 
					 } //else 请求信息中只有ESM，没有COM 结束
					 
				 }//if请求信息中有ESM信息
				 
				 //一：<2>b   	
				 else // else 请求信息中没有ESM , 必有COM ，根据COM 比较
				 {   
					 for ( re_iteCo = iteRequestMsg->vctComm.begin(); re_iteCo != iteRequestMsg->vctComm.end();re_iteCo++)
					 {
						 //在无航迹的聚类表中查找,无航迹中必有ESM和COM信息
						 for (iteNoTraceUnin = stUniAll.vctNoTraceUnin.begin(); iteNoTraceUnin != stUniAll.vctNoTraceUnin.end(); iteNoTraceUnin++)
						 {  //本舰自身无航迹信息时
							 for (iteNoTraceCo = iteNoTraceUnin->vctComm.begin(); iteNoTraceCo != iteNoTraceUnin->vctComm.end(); iteNoTraceCo++ )
							 {
								 double dSumCorr = 0.0;
								 Mf_SPA(iteCo->dComZaiPin,re_iteCo->dComZaiPin,dcorrComZaiPin); //载频
								 VctCorr.push_back(dcorrComZaiPin);
								 Mf_SPA(iteCo->dPulseExtent,re_iteCo->dPulseExtent,dcorrdPulseExtent); //脉冲幅度
								 VctCorr.push_back(dcorrdPulseExtent);
								 //0909修改:增加COM的集对分析数据:  带宽和跳频次数	 
								 Mf_SPA(iteCo->dComBand,re_iteCo->dComBand,dcorrBand);//带宽
								 VctCorr.push_back(dcorrBand);
								 Mf_SPA(iteCo->dComJPN,re_iteCo->dComJPN,dcorrJPN);//跳频次数
								 VctCorr.push_back(dcorrJPN);
								 
								 //对相关系数容器处理，取容器中数据的平均值
								 for (iteCorr = VctCorr.begin(); iteCorr != VctCorr.end(); iteCorr++)
								 {
									 dSumCorr = dSumCorr + *iteCorr;  
								 }
								 dAverCorr = dSumCorr/VctCorr.size();  //取相关系数的平均值
								 //下次存放集对系数前先清空VctCorr容器
								 VctCorr.clear();
								 //与阈值比较（设定阈值，相关系数大于某阈值时，认为ESM是可以关联的）
								 if (dAverCorr > 0.8)
								 {
									 //将找到的ESM与同一综合批号下的COM信息存入vctBackCooperative容器中
									 stBackMsg.lAutonum = iteRequestMsg->lAutonum;  //将请求信息的综合批号记录在返回信息中
									 //存ESM信息
									 for ( iteNoTraceEs = iteNoTraceUnin->vctEsm.begin();iteNoTraceEs !=iteNoTraceUnin->vctEsm.end(); iteNoTraceEs++)
									 {
										 stBackMsg .vctEsm.push_back(*iteNoTraceEs);
									 }
									 //存COM 信息
									 if (iteNoTraceUnin->vctComm.size() != 0)
									 {
										 for (iteNoTraceCo1 = iteNoTraceUnin->vctComm.begin();iteNoTraceCo1 !=iteNoTraceUnin->vctComm.end(); iteNoTraceCo1++)
										 {
											 stBackMsg.vctComm.push_back(*iteNoTraceCo1);
										 }
									 }
									 stBackMsg.BackTrackN = 0;  //航迹条数计数
									 stBackMsg.BackESMN = stBackMsg.vctEsm.size();
									 stBackMsg.BackCOMN = stBackMsg.vctComm.size();
									 //将查找到的信息存入vctBackCooperative容器中
									 vctBackCooperative.push_back(stBackMsg);
									 iteRequestMsg->nCorrFlag = 1; // 直到找到与请求信息相关联的信息,将标志信息该为1，若一直找不到则标志始终为0；
									 break;
								 } //if AverCorr > 0.8 结束
							 }// for iteNoTraceEs	
							 if (iteRequestMsg->nCorrFlag == 1) //标志位1，代表有找到相关信息，则结束iteNoTraceUnin 的循环。
							 {
								 break;
							 }
							 // 在COM 中没找到 ，继续iteNoTraceUnin的循环，比较下一个结构体中的多条com信息
							 
						 }//for iteNoTraceUnin
						 
						 if (iteRequestMsg->nCorrFlag == 1) //标志位1，代表有找到相关信息，则结束re_iteCo 的循环。
						 {
							 break;
						 } //否则，用请求信息中vctCom中的下一条Com与聚类表中的com比较	 
						 
					 }//for re_iteCo 遍历请求信息中的每条COM信息
					 
				 }// else 请求信息中无ESM信息，则根据COM信息查找（因为请求信息时已经聚类过的，并且综合批号大于8000的，必有航迹信息，必有ESM或者Com中的一类信息）
				 
		  }//if 有航迹聚类表中未找到，到无航迹聚类表中查找 (iteRequestMsg->nCorrFlag == 0 )
		  
		  //一：<3>
		  
		  if ( iteRequestMsg->nCorrFlag == 0)   //if 无航迹聚类表中未找到，到单个未聚类容器中查找
		  {   
			  //一：<3>a.  //查找stUniAll.vctSingleTrace 存放单一航迹的容器
			  for (iteTra = stUniAll.vctSingleTrace.begin(); iteTra != stUniAll.vctSingleTrace.end(); iteTra++)
			  {   double SumCorr = 0.0;
			  Get_Coordinate_Conversion_Module(iteTra->dRange,iteTra->dAzimuth,iteTra->dElevationAngle,
				  iteRequestMsg->stTrace.dRange,iteRequestMsg->stTrace.dAzimuth,iteRequestMsg->stTrace.dElevationAngle,
				  stSelfPosi.dLati,stSelfPosi.dLonti,stSelfPosi.dHeight,
				  iteRequestMsg->stReqShipPosi.dLati,iteRequestMsg->stReqShipPosi.dLonti,iteRequestMsg->stReqShipPosi.dHeight,
				  Xt, Yt, Zt, Rdt, Azt, Ezt, dSumCorr_xyz);
			  // 				  VctCorr.push_back(dSumCorr_xyz); 
			  // 				  //对航迹结构体中的测量信息进行集对分析,还有 Vx,Vy,Vz(目标在邻舰的坐标系下各坐标方向上的绝对速度需要转换到本舰坐标系下才能用吗????????)
			  // 				  Mf_SPA(iteTra->dRange,Rdt,dcorrRd);
			  // 				  VctCorr.push_back(dcorrRd);
			  // 				  Mf_SPA(iteTra->dAzimuth,Azt,dcorrAz);
			  // 				  VctCorr.push_back(dcorrAz);
			  // 				  Mf_SPA(iteTra->dElevationAngle,Ezt,dcorrEz); 
			  // 				  VctCorr.push_back(dcorrEz);
			  //各方向坐标下的绝对速度Vx,Vy,Vz未转换，直接做集对分析处理
			  Mf_SPA(iteTra->dTSpeedX,iteRequestMsg->stTrace.dTSpeedX,dcorrVx);
			  VctCorr.push_back(dcorrVx);
			  Mf_SPA(iteTra->dTSpeedY,iteRequestMsg->stTrace.dTSpeedY,dcorrVy);
			  VctCorr.push_back(dcorrVy);
			  Mf_SPA(iteTra->dTSpeedZ,iteRequestMsg->stTrace.dTSpeedZ,dcorrVz);
			  VctCorr.push_back(dcorrVz);
			  //对相关系数容器处理，取容器中数据的平均值
			  for (iteCorr = VctCorr.begin(); iteCorr != VctCorr.end(); iteCorr++)
			  {
				  SumCorr = SumCorr + *iteCorr;  
			  }
			  dAverCorr = SumCorr/VctCorr.size();  //取相关系数的平均值
			  //下次存放集对系数前先清空VctCorr容器
			  VctCorr.clear();
			  //与阈值比较（如何设定阈值，相关系数大于某阈值时，认为航迹是可以关联的?????????????????????）
			  if (dAverCorr > 0.8) //0.8为阈值，测试时可调节
			  {   //航迹信息可以关联，将信息放入vctBackCooperative返回信息容器中，
				  //将同一合批号下（即相同方位下）的一条航迹信息，还有N条ESM与Com信息放入vctBackCooperative中
				  //未编批则无综合批号
				  memcpy(&stBackMsg.stBackShipPosi,&stSelfPosi,sizeof(stBackMsg.stBackShipPosi));  //memcpy(&A,&B,sizeof(A)); 把结构体B给结构体A
				  //存航迹信息
				  memcpy(&stBackMsg.stTrace,&(*iteTra),sizeof(stBackMsg.stTrace));	
				  stBackMsg.BackTrackN = 1;
				  //将查找到的信息存入vctBackCooperative容器中
				  vctBackCooperative.push_back(stBackMsg);
				  
				  iteRequestMsg->nCorrFlag = 1;
				  break;//找到，跳出循环 
				  //至此，从未聚类的航迹表里取出关联信息，存入vctBackCooperative容器中 
			  }//0.8为阈值，测试时可调节
			  }//for 查找stUniAll.vctSingleTrace 存放单一航迹的容器 ,遍历stUniAll.vctSingleTrace
			  
			  //一：<3>b.   //查找stUniAll.vctSingleEsm 存放单一ESM的容器
			  if (iteRequestMsg->vctEsm.size() !=0)   //if请求信息中有ESM信息
			  {
				  //遍历每个请求信息中的vctEsm的每条信息
				  for ( re_iteEs = iteRequestMsg->vctEsm.begin(); re_iteEs != iteRequestMsg->vctEsm.end(); re_iteEs++)
				  {
					  //查找stUniAll.vctSingleEsm 存放单一航迹的容器
					  for ( iteEs =stUniAll.vctSingleEsm.begin(); iteEs != stUniAll.vctSingleEsm.end(); iteEs++ )
					  {   double dSumCorr = 0.0;
					  Mf_SPA(iteEs->dChongPin,re_iteEs->dChongPin,dcorrChongPin); //频率
					  VctCorr.push_back(dcorrChongPin);
					  Mf_SPA(iteEs->dMaiKuan,re_iteEs->dMaiKuan,dcorrMaiKuan); //脉宽
					  VctCorr.push_back(dcorrMaiKuan);
					  Mf_SPA(iteEs->dTianXianScan,re_iteEs->dTianXianScan,dcorrTianXianScan); //天线扫描周期
					  VctCorr.push_back(dcorrTianXianScan);
					  //对相关系数容器处理，取容器中数据的平均值
					  for (iteCorr = VctCorr.begin(); iteCorr != VctCorr.end(); iteCorr++)
					  {
						  dSumCorr = dSumCorr + *iteCorr;  
					  }
					  dAverCorr = dSumCorr/VctCorr.size();  //取相关系数的平均值
					  //下次存放集对系数前先清空VctCorr容器
					  VctCorr.clear();
					  //与阈值比较（设定阈值，相关系数大于某阈值时，认为ESM是可以关联的）
					  if (dAverCorr > 0.8) 
					  { //ESM信息可以关联，将信息放入vctBackCooperative返回信息容器中
						  //  memcpy(&sttEsm,&iteEs,sizeof(sttEsm));	
						  stBackMsg.lAutonum = iteEs->lTargetNumber;
						  stBackMsg.vctEsm.push_back(*iteEs);
						  stBackMsg.BackESMN = 1;
						  vctBackCooperative.push_back(stBackMsg);
						  iteRequestMsg->nCorrFlag = 1;
						  break; //找到，跳出循环
					  }//if
					  
					  }//for  查找stUniAll.vctSingleEsm 存放单一航迹的容器
					  if (iteRequestMsg->nCorrFlag == 1) //标志位1，代表有找到相关信息，则结束re_iteEs的循环。
					  {
						  break;
					  }
				  } //for  遍历每个请求信息中的vctEsm的每条信息 
				  
			  } //if请求信息中有ESM信息
			  
			  //一：<3>c.	//查找stUniAll.vctSingleCom 存放单一COM的容器	
			  if (iteRequestMsg->vctComm.size() !=0)   //if请求信息中有COM信息
			  {
				  //遍历每个请求信息中的vctCom的每条信息
				  for ( re_iteCo = iteRequestMsg->vctComm.begin(); re_iteCo != iteRequestMsg->vctComm.end(); re_iteEs++)
				  {
					  //查找stUniAll.vctSingleEsm 存放单一航迹的容器
					  for ( iteCo =stUniAll.vctSingleCom.begin(); iteCo != stUniAll.vctSingleCom.end(); iteCo++ )
					  {
						  double SumCorr = 0.0;
						  Mf_SPA(iteCo->dComZaiPin,re_iteCo->dComZaiPin,dcorrComZaiPin); //载频
						  VctCorr.push_back(dcorrComZaiPin);
						  Mf_SPA(iteCo->dPulseExtent,re_iteCo->dPulseExtent,dcorrdPulseExtent); //脉冲幅度
						  VctCorr.push_back(dcorrdPulseExtent);
						  //0909修改:增加COM的集对分析数据:  带宽和跳频次数	 
						  Mf_SPA(iteCo->dComBand,re_iteCo->dComBand,dcorrBand);//带宽
						  VctCorr.push_back(dcorrBand);
						  Mf_SPA(iteCo->dComJPN,re_iteCo->dComJPN,dcorrJPN);//跳频次数
						  VctCorr.push_back(dcorrJPN);
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
						  { //ESM信息可以关联，将信息放入vctBackCooperative返回信息容器中
							  // memcpy(&sttCom,&iteCo,sizeof(sttCom));	
							  stBackMsg.lAutonum = iteCo->lTargetNumber;
							  stBackMsg.vctComm.push_back(*iteCo);
							  stBackMsg.BackCOMN =1;
							  vctBackCooperative.push_back(stBackMsg);
							  iteRequestMsg->nCorrFlag = 1;
							  break; //找到，跳出循环
						  }//if
					  }// for iteCo	
					  if (iteRequestMsg->nCorrFlag == 1) //标志位1，代表有找到相关信息，则结束re_iteEs的循环。
					  {
						  break;
					  }
				  }//for re_iteCo 遍历每个请求信息中的vctCom的每条信息
			  }//if 请求信息中有ESM信息
		  }//if 结束 无航迹聚类表中未找到，到单个未聚类容器中查找
		  
		  
}//  void ReqUnin_COOP_Find_Information_To_MainShip()结束


/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/

//请求信息：无航迹的聚类信息，综合批号大于7000到8000之间
void ReqNoTraceUnin_COOP_Find_Information_To_MainShip(SHIP_POSITION& stSelfPosi,UNI_All_NUM& stUniAll,VCT_Request_Cooperative_Msg::iterator& iteRequestMsg,/*VCT_Request_Cooperative_Msg& vctRequestCooperative,*/ VCT_BACK_Cooperative_Msg& vctBackCooperative)
{
	double Xt = 0.0;        //定义变量时，不要定义在IF 与for循环中，定义到外部，作为全局变量
	double Yt = 0.0;
	double Zt = 0.0;
	double Rdt = 0.0;
	double Azt = 0.0;
	double Ezt = 0.0;
	double dSumCorr_xyz = 0.0;
	double dcorrRd = 0.0;
	double dcorrAz = 0.0;
	double dcorrEz = 0.0;
	double dcorrVx = 0.0;
	double dcorrVy = 0.0;
	double dcorrVz = 0.0;
	double dcorrChongPin = 0.0;
	double dcorrMaiKuan = 0.0;
	double dcorrTianXianScan =0.0;
	double dcorrComZaiPin =0.0;
    double dcorrdPulseExtent = 0.0;
    double dcorrBand = 0.0;
	double dcorrJPN = 0.0;
	
	//  double SumCorr = 0.0;
    double dAverCorr = 0.0; //各测量信息，集对分析后，取平均值后的相关系数
	//  TRACKSTATUS_MARK sttTrack;
	ESMSTATUS_MARK sttEsm;
	COMSTATUS_MARK sttCom;
    typedef vector<double> VCT_CORR;
	VCT_CORR VctCorr;      // 存放关联系数的容器
	VCT_CORR::iterator iteCorr;
	//  用来清空的迭代器
	//  在vctRequestCooperative容器中，三个容器（存放每类传感器信息）的迭代器
	//	VCT_TRACE_MSG::iterator iteTrace; //因为每个结构体中若有航迹，只存在一条航迹，直接用航迹信息的结构体
	VCT_ESM_MSG::iterator iteEsm;                
	VCT_COMM_MSG::iterator iteCom;
	//有航迹
	VCT_UNINUM_MSG::iterator iteUnin;
	//有航迹 两个容器（Esm,Com）的迭代器
	VCT_ESM_MSG::iterator iteUninEs;
	VCT_ESM_MSG::iterator iteUninEs1;
	VCT_COMM_MSG::iterator iteUninCo;
	VCT_COMM_MSG::iterator iteUninCo1;
	
	//无航迹
	VCT_UNINOTRACE_MSG::iterator iteNoTraceUnin;
	//无航迹 两个容器（ESM，com）的迭代器
	VCT_ESM_MSG::iterator iteNoTraceEs;
	VCT_ESM_MSG::iterator iteNoTraceEs1;
	VCT_COMM_MSG::iterator iteNoTraceCo;
//	VCT_COMM_MSG::iterator iteNoTraceCo1;
	
	//未聚类 三个容器（存放每类传感器信息）的迭代器
	//	VCT_TRACE_MSG::iterator iteTra;
	VCT_ESM_MSG::iterator iteEs;
	VCT_COMM_MSG::iterator iteCo;
	
	VCT_BACK_Cooperative_Msg::iterator iteBackMsg;
	BACK_Cooperative_Msg stBackMsg;
	//	VCT_Request_Cooperative_Msg::iterator iteRequestMsg;
	//请求信息中 ESM，COM容器（存放每类传感器信息）的迭代器
	VCT_ESM_MSG::iterator re_iteEs;
	VCT_COMM_MSG::iterator re_iteCo;
	// 
	
	//清空 vctBackCooperative
	for (iteBackMsg = vctBackCooperative.begin(); iteBackMsg != vctBackCooperative.end(); iteBackMsg++)
	{	
		//清空 vctBackCooperative
		iteBackMsg->lAutonum = NULL;
		iteBackMsg->nStampTime = NULL;
// 		iteBackMsg->dAzimuth = NULL;
// 		iteBackMsg->dElevationAngle = NULL;
// 		iteBackMsg->dRange = NULL;
		iteBackMsg->BackTrackN = 0;
		iteBackMsg->BackESMN = 0;
		iteBackMsg->BackCOMN = 0;
		memset(&iteBackMsg->stBackShipPosi,0 ,sizeof(iteBackMsg->stBackShipPosi));
		memset(&(*iteBackMsg), 0, sizeof(TRACKSTATUS_MARK));
		for ( iteEsm = iteBackMsg->vctEsm.begin(); iteEsm != iteBackMsg->vctEsm.end(); iteEsm++)
		{
			memset(&(*iteEsm), 0, sizeof(ESMSTATUS_MARK));
		}
		for ( iteCom = iteBackMsg->vctComm.begin(); iteCom != iteBackMsg->vctComm.end();iteCom++)
		{
			memset(&(*iteCom), 0, sizeof(COMSTATUS_MARK));
		}
		/*		iteBackMsg->vctTrace.clear();*/
		iteBackMsg->vctEsm.clear();
		iteBackMsg->vctComm.clear();
	}
	vctBackCooperative.clear();
	
	for ( re_iteEs = iteRequestMsg->vctEsm.begin(); re_iteEs != iteRequestMsg->vctEsm.end(); re_iteEs++) 
	{     //在有航迹的聚类表中查找 
		for ( iteUnin = stUniAll.vctUnin.begin(); iteUnin != stUniAll.vctUnin.end(); iteUnin++)
		{ 
			//判断聚类信息中iteUnin中是否有ESM信息
			if (iteUnin->vctEsm.size() !=0 ) //聚类信息表中有ESM信息
			{
				for (iteUninEs = iteUnin->vctEsm.begin(); iteUninEs != iteUnin->vctEsm.end(); iteUninEs++)
				{
					double SumCorr = 0.0;
					Mf_SPA(iteUninEs->dChongPin,re_iteEs->dChongPin,dcorrChongPin); //频率
					VctCorr.push_back(dcorrChongPin);
					Mf_SPA(iteUninEs->dMaiKuan,re_iteEs->dMaiKuan,dcorrMaiKuan); //脉宽
					VctCorr.push_back(dcorrMaiKuan);
					Mf_SPA(iteUninEs->dTianXianScan,re_iteEs->dTianXianScan,dcorrTianXianScan); //天线扫描周期
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
						//将找到的ESM与同一综合批号下的COM信息存入vctBackCooperative容器中
						stBackMsg.lAutonum = iteRequestMsg->lAutonum;  //将请求信息的综合批号记录在返回信息中
						//存ESM信息
						for ( iteUninEs1 = iteUnin->vctEsm.begin();iteUninEs1 !=iteUnin->vctEsm.end(); iteUninEs1++)
						{
							stBackMsg.vctEsm.push_back(*iteUninEs1);
						}
						//存被请求协同舰的经纬高
						memcpy(&stBackMsg.stBackShipPosi,&stSelfPosi,sizeof(stBackMsg.stBackShipPosi));  //memcpy(&A,&B,sizeof(A)); 把结构体B给结构体A
						//存航迹信息
						memcpy(&stBackMsg.stTrace,&iteUnin->structTrace,sizeof(stBackMsg.stTrace));		
						
						//存COM 信息,com不一定存在
						if (iteUnin->vctComm.size() != 0 )
						{
							for (iteUninCo = iteUnin->vctComm.begin();iteUninCo !=iteUnin->vctComm.end(); iteUninCo++)
							{
								stBackMsg.vctComm.push_back(*iteUninCo);
							}
						}
						stBackMsg.BackTrackN = 1;
						stBackMsg.BackESMN = stBackMsg.vctEsm.size();
						stBackMsg.BackCOMN = stBackMsg.vctComm.size();
						
						vctBackCooperative.push_back(stBackMsg);
						iteRequestMsg->nCorrFlag = 1;
						break;
					} //if AverCorr > 0.8 结束							
				}  //for  iteUninEs	
			}//if  iteUnin->vctEsm.size() !=0 聚类信息表中有ESM信息
			if (iteRequestMsg->nCorrFlag == 1) //标志位1，代表有找到相关信息，则结束iteUnin的循环。
			{
				break;
			}
		} //for  iteUnin
		if (iteRequestMsg->nCorrFlag == 1) //标志位1，代表有找到相关信息，则结束re_iteEs 的循环。
		{
			break;
		} //否则，用请求信息中vctEsm中的下一条Esm与聚类表中的Esm比较
	}//for  re_iteEs
	
	if (iteRequestMsg->nCorrFlag == 0) //请求信息ESM 在有聚类表中的有ESM 信息的结构体中未找到相关信息，那么在聚类表中结构体中的COM 中比较查找
	{
		if (  iteRequestMsg->vctComm.size() !=0 )
		{
			for ( re_iteCo = iteRequestMsg->vctComm.begin(); re_iteCo != iteRequestMsg->vctComm.end(); re_iteCo++) 
			{     //在有航迹的聚类表中查找 
				for ( iteUnin = stUniAll.vctUnin.begin(); iteUnin != stUniAll.vctUnin.end(); iteUnin++)
				{ 
					//判断聚类信息中iteUnin中是否有Com信息
					if (iteUnin->vctComm.size() !=0 ) //聚类信息表中有COM信息
					{
						for (iteUninCo = iteUnin->vctComm.begin(); iteUninCo != iteUnin->vctComm.end(); iteUninCo++)
						{
							double SumCorr = 0.0;
							Mf_SPA(iteUninCo->dComZaiPin,re_iteCo->dComZaiPin,dcorrComZaiPin); //载频
							VctCorr.push_back(dcorrComZaiPin);
							Mf_SPA(iteUninCo->dPulseExtent,re_iteCo->dPulseExtent,dcorrdPulseExtent); //脉冲幅度
							VctCorr.push_back(dcorrdPulseExtent);
							//0909修改:增加COM的集对分析数据:  带宽和跳频次数	 
							Mf_SPA(iteUninCo->dComBand,re_iteCo->dComBand,dcorrBand);//带宽
							VctCorr.push_back(dcorrBand);
							Mf_SPA(iteUninCo->dComJPN,re_iteCo->dComJPN,dcorrJPN);//跳频次数
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
							{ //COM信息可以关联，将信息放入vctBackCooperative返回信息容器中
								stBackMsg.lAutonum = iteRequestMsg->lAutonum;  //将请求信息的综合批号记录在返回信息中
								//存COM
								for (iteUninCo1 = iteUnin->vctComm.begin();iteUninCo1 !=iteUnin->vctComm.end(); iteUninCo1++)
								{
									stBackMsg.vctComm.push_back(*iteUninCo1);
								}
								//存ESM
								if (iteUnin->vctEsm.size() != 0 )
								{
									for ( iteUninEs = iteUnin->vctEsm.begin();iteUninEs !=iteUnin->vctEsm.end(); iteUninEs++)
									{
										stBackMsg.vctEsm.push_back(*iteUninEs);
									}
								}
								//存被请求协同舰的经纬高
								memcpy(&stBackMsg.stBackShipPosi,&stSelfPosi,sizeof(stBackMsg.stBackShipPosi));  //memcpy(&A,&B,sizeof(A)); 把结构体B给结构体A
								//存航迹信息
								memcpy(&stBackMsg.stTrace,&iteUnin->structTrace,sizeof(stBackMsg.stTrace));	
								//	memcpy(&sttCom,&iteCo,sizeof(sttCom));	
								//									stBackMsg.lAutonum = iteCo->lTargetNumber;
								//									stBackMsg.vctComm.push_back(sttCom);
								
								stBackMsg.BackTrackN = 1;
								stBackMsg.BackESMN = stBackMsg.vctEsm.size();
								stBackMsg.BackCOMN = stBackMsg.vctComm.size();
								vctBackCooperative.push_back(stBackMsg);
								iteRequestMsg->nCorrFlag = 1;
								break; //找到，跳出循环
							}//if
						}//for iteUninCo
					}// if 聚类表中iteUnin所代表的结构体中有COM信息
					
					if (iteRequestMsg->nCorrFlag == 1) //标志位1，代表有找到相关信息，则结束iteUnin的循环。
					{
						break;
					}
				}// for iteUnin
				if (iteRequestMsg->nCorrFlag == 1) //标志位1，代表有找到相关信息，则结束re_iteCo 的循环。
				{
					break;
				} //否则，用请求信息中vctCom中的下一条Com与聚类表中的Com比较
			}//for re_iteCo
		 
		}//if 请求信息有COM信息

	}// if 在聚类表中的结构体中有COM信息
	
	
	
	//二：<2>
	if ( iteRequestMsg->nCorrFlag == 0 )
	{   //在无航迹的聚类表中查找	
		for ( re_iteEs = iteRequestMsg->vctEsm.begin(); re_iteEs != iteRequestMsg->vctEsm.end(); re_iteEs++) 
		{
			for (iteNoTraceUnin = stUniAll.vctNoTraceUnin.begin(); iteNoTraceUnin != stUniAll.vctNoTraceUnin.end(); iteNoTraceUnin++)
			{
				for (iteNoTraceEs = iteNoTraceUnin->vctEsm.begin(); iteNoTraceEs != iteNoTraceUnin->vctEsm.end(); iteNoTraceEs++)	 
				{     
					double SumCorr = 0.0;
				    Mf_SPA(iteNoTraceEs->dChongPin,re_iteEs->dChongPin,dcorrChongPin); //频率
					VctCorr.push_back(dcorrChongPin);
					Mf_SPA(iteNoTraceEs->dMaiKuan,re_iteEs->dMaiKuan,dcorrMaiKuan); //脉宽
					VctCorr.push_back(dcorrMaiKuan);
					Mf_SPA(iteNoTraceEs->dTianXianScan,re_iteEs->dTianXianScan,dcorrTianXianScan); //天线扫描周期
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
						//将找到的ESM与同一综合批号下的COM信息存入vctBackCooperative容器中
						stBackMsg.lAutonum = iteRequestMsg->lAutonum;  //将请求信息的综合批号记录在返回信息中
						
						//存ESM信息
						for ( iteNoTraceEs1 = iteNoTraceUnin->vctEsm.begin();iteNoTraceEs1 !=iteNoTraceUnin->vctEsm.end(); iteNoTraceEs1++)
						{
							stBackMsg.vctEsm.push_back(*iteNoTraceEs1);
						}
						
						//存COM 信息
						for (iteNoTraceCo = iteNoTraceUnin->vctComm.begin();iteNoTraceCo !=iteNoTraceUnin->vctComm.end(); iteNoTraceCo++)
						{
							stBackMsg.vctComm.push_back(*iteNoTraceCo);
						} 
						stBackMsg.BackTrackN = 0;
						stBackMsg.BackESMN = stBackMsg.vctEsm.size();
						stBackMsg.BackCOMN = stBackMsg.vctComm.size();
						vctBackCooperative.push_back(stBackMsg);
						iteRequestMsg->nCorrFlag = 1;
						break;
					} //if AverCorr > 0.8 结束
				}// for  iteNoTraceEs 
				if (iteRequestMsg->nCorrFlag == 1) //标志位1，代表有找到相关信息，则结束iteNoTraceUnin的循环。
				{
					break;
				}  
			}// for iteNoTraceUnin
			if (iteRequestMsg->nCorrFlag == 1) //标志位1，代表有找到相关信息，则结束re_iteEs 的循环。
			{
				break;
			} //否则，用请求信息中vctEsm中的下一条Esm与聚类表中的Esm比较
			
		} // for re_iteEs
		
	}// if iteRequestMsg->nCorrFlag == 0 
	
	if (iteRequestMsg->nCorrFlag == 0) //请求信息ESM 在无航迹的聚类表中ESM 信息的结构体中未找到相关信息，那么在无航迹的聚类表中结构体中的COM 中比较查找
	{ 
		if (  iteRequestMsg->vctComm.size() != 0 )
		{
			for ( re_iteCo = iteRequestMsg->vctComm.begin(); re_iteCo != iteRequestMsg->vctComm.end(); re_iteCo++) 
			{     //在无航迹的聚类表中查找 
				for ( iteUnin = stUniAll.vctUnin.begin(); iteUnin != stUniAll.vctUnin.end(); iteUnin++)
				{ 
					if ( iteUnin->vctComm.size() != 0)
					{
						for (iteUninCo = iteUnin->vctComm.begin(); iteUninCo != iteUnin->vctComm.end(); iteUninCo++)
						{
							double SumCorr = 0.0;
							Mf_SPA(iteUninCo->dComZaiPin,re_iteCo->dComZaiPin,dcorrComZaiPin); //载频
							VctCorr.push_back(dcorrComZaiPin);
							Mf_SPA(iteUninCo->dPulseExtent,re_iteCo->dPulseExtent,dcorrdPulseExtent); //脉冲幅度
							VctCorr.push_back(dcorrdPulseExtent);
							//0909修改:增加COM的集对分析数据:  带宽和跳频次数	 
							Mf_SPA(iteUninCo->dComBand,re_iteCo->dComBand,dcorrBand);//带宽
							VctCorr.push_back(dcorrBand);
							Mf_SPA(iteUninCo->dComJPN,re_iteCo->dComJPN,dcorrJPN);//跳频次数
							VctCorr.push_back(dcorrJPN);
							//对相关系数容器处理，取容器中数据的平均值
							for (iteCorr = VctCorr.begin(); iteCorr != VctCorr.end(); iteCorr++)
							{
								SumCorr = SumCorr + *iteCorr;  
							}
							dAverCorr = SumCorr/VctCorr.size();  //取相关系数的平均值
							//下次存放集对系数前先清空VctCorr容器
							VctCorr.clear();
							//与阈值比较（设定阈值，相关系数大于某阈值时，认为Com是可以关联的）
							if (dAverCorr > 0.8) 
							{ //Com信息可以关联，将信息放入vctBackCooperative返回信息容器中
								//										   memcpy(&sttCom,&iteCo,sizeof(sttCom));	
								//										   stBackMsg.lAutonum = iteCo->lTargetNumber;
								//										   stBackMsg.vctComm.push_back(sttCom);
								//将找到的ESM与同一综合批号下的COM信息存入vctBackCooperative容器中
								stBackMsg.lAutonum = iteRequestMsg->lAutonum;  //将请求信息的综合批号记录在返回信息中
								//存ESM信息
								for ( iteNoTraceEs = iteNoTraceUnin->vctEsm.begin();iteNoTraceEs !=iteNoTraceUnin->vctEsm.end(); iteNoTraceEs++)
								{
									stBackMsg.vctEsm.push_back(*iteNoTraceEs);
								}
								//存COM 信息
								for (iteNoTraceCo = iteNoTraceUnin->vctComm.begin();iteNoTraceCo !=iteNoTraceUnin->vctComm.end(); iteNoTraceCo++)
								{
									stBackMsg.vctComm.push_back(*iteNoTraceCo);
								} 
								stBackMsg.BackTrackN = 0;
								stBackMsg.BackESMN = stBackMsg.vctEsm.size();
								stBackMsg.BackCOMN = stBackMsg.vctComm.size();
								vctBackCooperative.push_back(stBackMsg);
								
								iteRequestMsg->nCorrFlag = 1;
								break; //找到，跳出循环
							}//if
						}//for iteUninCo

					}// 无航迹聚类信息中有Com信息

					if (iteRequestMsg->nCorrFlag == 1) //标志位1，代表有找到相关信息，则结束iteUnin的循环。
					{
						break;
					}
				}// for iteUnin
				if (iteRequestMsg->nCorrFlag == 1) //标志位1，代表有找到相关信息，则结束re_iteCo 的循环。
				{
					break;
				} //否则，用请求信息中vctCom中的下一条Com与聚类表中的Com比较
			}//for re_iteCo

		}// 请求信息中有COM信息

	}// if 在聚类表中结构体中的COM 中比较查找
	
	
	//二：<3>
	if (iteRequestMsg->nCorrFlag == 0)   //if 无航迹聚类表中未找到，到单个未聚类容器中查找
	{   //查找stUniAll.vctSingleTrace 存放单一ESM的容器
		//二：<3>a. 
	    for ( re_iteEs = iteRequestMsg->vctEsm.begin(); re_iteEs != iteRequestMsg->vctEsm.end(); re_iteEs++) 
		{
		    for (iteEs = stUniAll.vctSingleEsm.begin(); iteEs != stUniAll.vctSingleEsm.end(); iteEs++)
			{
				double SumCorr = 0.0;
				Mf_SPA(iteEs->dChongPin,re_iteEs->dChongPin,dcorrChongPin); //频率
				VctCorr.push_back(dcorrChongPin);
				Mf_SPA(iteEs->dMaiKuan,re_iteEs->dMaiKuan,dcorrMaiKuan); //脉宽
				VctCorr.push_back(dcorrMaiKuan);
				Mf_SPA(iteEs->dTianXianScan,re_iteEs->dTianXianScan,dcorrTianXianScan); //天线扫描周期
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
				{ //ESM信息可以关联，将信息放入vctBackCooperative返回信息容器中
					memcpy(&sttEsm,&(*iteEs),sizeof(sttEsm));	
					stBackMsg.lAutonum = iteEs->lTargetNumber;
					stBackMsg.vctEsm.push_back(sttEsm);
					stBackMsg.BackESMN = 1;
					vctBackCooperative.push_back(stBackMsg);
					iteRequestMsg->nCorrFlag = 1;
					break; //找到，跳出循环
				}//if     
			}//for iteEs  
			if (iteRequestMsg->nCorrFlag == 1) //标志位1，代表有找到相关信息，则结束re_iteCo 的循环。
			{
				break;
			}
		}// for re_iteEs
		
		//请求信息中有Comm信息
		if ( iteRequestMsg->vctComm.size() != 0  )
		{
			for ( re_iteCo = iteRequestMsg->vctComm.begin(); re_iteCo != iteRequestMsg->vctComm.end(); re_iteCo++) 
			{
				for (iteCo = stUniAll.vctSingleCom.begin(); iteCo != stUniAll.vctSingleCom.end(); iteCo++)
				{
					double SumCorr = 0.0;
					Mf_SPA(iteCo->dComZaiPin,re_iteCo->dComZaiPin,dcorrComZaiPin); //载频
					VctCorr.push_back(dcorrComZaiPin);
					Mf_SPA(iteCo->dPulseExtent,re_iteCo->dPulseExtent,dcorrdPulseExtent); //脉冲幅度
					VctCorr.push_back(dcorrdPulseExtent);
					//0909修改:增加COM的集对分析数据:  带宽和跳频次数	 
					Mf_SPA(iteCo->dComBand,re_iteCo->dComBand,dcorrBand);//带宽
					VctCorr.push_back(dcorrBand);
					Mf_SPA(iteCo->dComJPN,re_iteCo->dComJPN,dcorrJPN);//跳频次数
					VctCorr.push_back(dcorrJPN);
					//对相关系数容器处理，取容器中数据的平均值
					for (iteCorr = VctCorr.begin(); iteCorr != VctCorr.end(); iteCorr++)
					{
						SumCorr = SumCorr + *iteCorr;  
					}
					dAverCorr = SumCorr/VctCorr.size();  //取相关系数的平均值
					//下次存放集对系数前先清空VctCorr容器
					VctCorr.clear();
					//与阈值比较（设定阈值，相关系数大于某阈值时，认为Com是可以关联的）
					if (dAverCorr > 0.8) 
					{ //Com信息可以关联，将信息放入vctBackCooperative返回信息容器中
						memcpy(&sttCom,&(*iteCo),sizeof(sttCom));	
						stBackMsg.lAutonum = iteCo->lTargetNumber;
						stBackMsg.vctComm.push_back(sttCom);
						
						stBackMsg.BackCOMN = 1;
						
						vctBackCooperative.push_back(stBackMsg);
						iteRequestMsg->nCorrFlag = 1;
						break; //找到，跳出循环
					}//if     
				}//for iteEs  
				if (iteRequestMsg->nCorrFlag == 1) //标志位1，代表有找到相关信息，则结束re_iteCo 的循环。
				{
					break;
				}
			}// for re_iteCo
		}
								   
	}// if iteRequestMsg->nCorrFlag == 0
	
}//void ReqNoTraceUnin_COOP_Find_Information_To_MainShip()结束

/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/

//请求信息：未聚类的航迹信息，无综合批号，有航迹信息的目标批号，5000到6000

void ReqSingleTrace_COOP_Find_Information_To_MainShip(SHIP_POSITION& stSelfPosi,UNI_All_NUM& stUniAll,VCT_Request_Cooperative_Msg::iterator& iteRequestMsg,/*VCT_Request_Cooperative_Msg& vctRequestCooperative,*/ VCT_BACK_Cooperative_Msg& vctBackCooperative)
{	
	double Xt = 0.0;        //定义变量时，不要定义在IF 与for循环中，定义到外部，作为全局变量
	double Yt = 0.0;
	double Zt = 0.0;
	double Rdt = 0.0;
	double Azt = 0.0;
	double Ezt = 0.0;
	double dSumCorr_xyz = 0.0;
	double dcorrRd = 0.0;
	double dcorrAz = 0.0;
	double dcorrEz = 0.0;
	double dcorrVx = 0.0;
	double dcorrVy = 0.0;
	double dcorrVz = 0.0;
	double dcorrChongPin = 0.0;
	double dcorrMaiKuan = 0.0;
	double dcorrTianXianScan =0.0;
	double dcorrComZaiPin =0.0;
	double dcorrdPulseExtent = 0.0;
	double dcorrBand = 0.0;
	double dcorrJPN = 0.0;
	
	//  double SumCorr = 0.0;
	double dAverCorr = 0.0; //各测量信息，集对分析后，取平均值后的相关系数
	//  TRACKSTATUS_MARK sttTrack;
	//	ESMSTATUS_MARK sttEsm;
	//	COMSTATUS_MARK sttCom;
	typedef vector<double> VCT_CORR;
	VCT_CORR VctCorr;      // 存放关联系数的容器
	VCT_CORR::iterator iteCorr;
	//  用来清空的迭代器
	//  在vctRequestCooperative容器中，三个容器（存放每类传感器信息）的迭代器
	//	VCT_TRACE_MSG::iterator iteTrace; //因为每个结构体中若有航迹，只存在一条航迹，直接用航迹信息的结构体
	VCT_ESM_MSG::iterator iteEsm;                
	VCT_COMM_MSG::iterator iteCom;
	//有航迹
	VCT_UNINUM_MSG::iterator iteUnin;
	//有航迹 两个容器（Esm,Com）的迭代器
	//	VCT_ESM_MSG::iterator iteUninEs;
	//	VCT_COMM_MSG::iterator iteUninCo;
	
	//无航迹
	//	VCT_UNINOTRACE_MSG::iterator iteNoTraceUnin;
	//无航迹 两个容器（ESM，com）的迭代器
	//	VCT_ESM_MSG::iterator iteNoTraceEs;
	//	VCT_COMM_MSG::iterator iteNoTraceCo;
	
	//未聚类 三个容器（存放每类传感器信息）的迭代器
	VCT_TRACE_MSG::iterator iteTra;
	VCT_ESM_MSG::iterator iteEs;
	VCT_COMM_MSG::iterator iteCo;
	
	VCT_BACK_Cooperative_Msg::iterator iteBackMsg;
	BACK_Cooperative_Msg stBackMsg;
	//	VCT_Request_Cooperative_Msg::iterator iteRequestMsg;
	//请求信息中 ESM，COM容器（存放每类传感器信息）的迭代器
	//	VCT_ESM_MSG::iterator re_iteEs;
	//	VCT_COMM_MSG::iterator re_iteCo;
	// 

	//清空 vctBackCooperative
	for (iteBackMsg = vctBackCooperative.begin(); iteBackMsg != vctBackCooperative.end(); iteBackMsg++)
	{	
		//清空 vctBackCooperative
		iteBackMsg->lAutonum = NULL;
		iteBackMsg->nStampTime = NULL;
		// 	iteBackMsg->dAzimuth = NULL;
		// 	iteBackMsg->dElevationAngle = NULL;
		// 	iteBackMsg->dRange = NULL;
		iteBackMsg->BackTrackN = 0;
		iteBackMsg->BackESMN = 0;
		iteBackMsg->BackCOMN = 0;
		memset(&iteBackMsg->stBackShipPosi,0 ,sizeof(iteBackMsg->stBackShipPosi));
		memset(&(*iteBackMsg), 0, sizeof(TRACKSTATUS_MARK));
		for ( iteEsm = iteBackMsg->vctEsm.begin(); iteEsm != iteBackMsg->vctEsm.end(); iteEsm++)
		{
			memset(&(*iteBackMsg), 0, sizeof(ESMSTATUS_MARK));
		}
		for ( iteCom = iteBackMsg->vctComm.begin(); iteCom != iteBackMsg->vctComm.end();iteCom++)
		{
			memset(&(*iteBackMsg), 0, sizeof(COMSTATUS_MARK));
		}
		/*		iteBackMsg->vctTrace.clear();*/
		iteBackMsg->vctEsm.clear();
		iteBackMsg->vctComm.clear();
	}
	vctBackCooperative.clear();
	//在有航迹的聚类表中查找 	
	for ( iteUnin = stUniAll.vctUnin.begin(); iteUnin != stUniAll.vctUnin.end(); iteUnin++)
	{     
		double SumCorr = 0.0;
		Get_Coordinate_Conversion_Module(iteUnin->structTrace.dRange,iteUnin->structTrace.dAzimuth,iteUnin->structTrace.dElevationAngle,
			iteRequestMsg->stTrace.dRange,iteRequestMsg->stTrace.dAzimuth,iteRequestMsg->stTrace.dElevationAngle,
			stSelfPosi.dLati,stSelfPosi.dLonti,stSelfPosi.dHeight,
			iteRequestMsg->stReqShipPosi.dLati,iteRequestMsg->stReqShipPosi.dLonti,iteRequestMsg->stReqShipPosi.dHeight,
			Xt, Yt, Zt, Rdt, Azt, Ezt,dSumCorr_xyz);
		// 			  VctCorr.push_back(dSumCorr_xyz); 
		// 			  //对航迹结构体中的测量信息进行集对分析,还有 Vx,Vy,Vz(目标在邻舰的坐标系下各坐标方向上的绝对速度需要转换到本舰坐标系下才能用吗????????)
		//            Mf_SPA(iteUnin->structTrace.dRange,Rdt,dcorrRd);
		// 			  VctCorr.push_back(dcorrRd);
		// 			  Mf_SPA(iteUnin->structTrace.dAzimuth,Azt,dcorrAz);
		// 			  VctCorr.push_back(dcorrAz);
		// 			  Mf_SPA(iteUnin->structTrace.dElevationAngle,Ezt,dcorrEz); 
		// 			  VctCorr.push_back(dcorrEz);
		//各方向坐标下的绝对速度Vx,Vy,Vz未转换，直接做集对分析处理
		Mf_SPA(iteUnin->structTrace.dTSpeedX,iteRequestMsg->stTrace.dTSpeedX,dcorrVx);
		VctCorr.push_back(dcorrVx);
		Mf_SPA(iteUnin->structTrace.dTSpeedY,iteRequestMsg->stTrace.dTSpeedY,dcorrVy);
		VctCorr.push_back(dcorrVy);
		Mf_SPA(iteUnin->structTrace.dTSpeedZ,iteRequestMsg->stTrace.dTSpeedZ,dcorrVz);
		VctCorr.push_back(dcorrVz);
		//对相关系数容器处理，取容器中数据的平均值
		for (iteCorr = VctCorr.begin(); iteCorr != VctCorr.end(); iteCorr++)
		{
			SumCorr = SumCorr + *iteCorr;  
		}
		dAverCorr = SumCorr/VctCorr.size();  //取相关系数的平均值
		//下次存放集对系数前先清空VctCorr容器
		VctCorr.clear();
		if (dAverCorr > 0.8)
		{   //航迹信息可以关联，将信息放入vctBackCooperative返回信息容器中，
			//将同一合批号下（即相同方位下）的一条航迹信息，还有N条ESM与Com信息放入vctBackCooperative中
			stBackMsg.lAutonum = iteRequestMsg->lAutonum; //将请求信息的综合批号赋值给返回信息。
			memcpy(&stBackMsg.stBackShipPosi,&stSelfPosi,sizeof(stBackMsg.stBackShipPosi));  //memcpy(&A,&B,sizeof(A)); 把结构体B给结构体A
			//存航迹信息
			memcpy(&stBackMsg.stTrace,&iteUnin->structTrace,sizeof(stBackMsg.stTrace));			
			//存ESM信息
			if (iteUnin->vctEsm.size() !=0)
			{
				for (iteEs = iteUnin->vctEsm.begin(); iteEs != iteUnin->vctEsm.end(); iteEs++)
				{
					stBackMsg.vctEsm.push_back(*iteEs);
				}
			}
			//存COM 信息
			if (iteUnin->vctComm.size() != 0)
			{
				for (iteCo = iteUnin->vctComm.begin(); iteCo != iteUnin->vctComm.end(); iteCo++)
				{
					stBackMsg.vctComm.push_back(*iteCo);
				}
			}
			stBackMsg.BackTrackN = 1;
			stBackMsg.BackCOMN = stBackMsg.vctComm.size();
			stBackMsg.BackESMN = stBackMsg.vctEsm.size();
			
			//将查找到的信息存入vctBackCooperative容器中
			vctBackCooperative.push_back(stBackMsg);
			iteRequestMsg->nCorrFlag = 1;
			break;
		}// if(AverCorr > 0.8)
		
	} //for iteUnin  查找有航迹的聚类表 结束

	if (iteRequestMsg->nCorrFlag == 0) //在有航迹的聚类表中未找到，则在SingleTrack中查找（即在未聚类的容器中查找）
	{  // 在未聚类的航迹中查找（SingleTrack）
		for ( iteTra = stUniAll.vctSingleTrace.begin(); iteTra != stUniAll.vctSingleTrace.end(); iteTra++)
		{ 
			double dSumCorr = 0.0;
			Get_Coordinate_Conversion_Module(iteTra->dRange,iteTra->dAzimuth,iteTra->dElevationAngle,
				iteRequestMsg->stTrace.dRange,iteRequestMsg->stTrace.dAzimuth,iteRequestMsg->stTrace.dElevationAngle,
				stSelfPosi.dLati,stSelfPosi.dLonti,stSelfPosi.dHeight,
				iteRequestMsg->stReqShipPosi.dLati,iteRequestMsg->stReqShipPosi.dLonti,iteRequestMsg->stReqShipPosi.dHeight,
				Xt, Yt, Zt, Rdt, Azt, Ezt, dSumCorr_xyz);
			// 				  VctCorr.push_back(dSumCorr_xyz); 
			// 				  //对航迹结构体中的测量信息进行集对分析,还有 Vx,Vy,Vz(目标在邻舰的坐标系下各坐标方向上的绝对速度需要转换到本舰坐标系下才能用吗????????)
			// 				  Mf_SPA(iteTra->dRange,Rdt,dcorrRd);
			// 				  VctCorr.push_back(dcorrRd);
			// 				  Mf_SPA(iteTra->dAzimuth,Azt,dcorrAz);
			// 				  VctCorr.push_back(dcorrAz);
			// 				  Mf_SPA(iteTra->dElevationAngle,Ezt,dcorrEz); 
			// 				  VctCorr.push_back(dcorrEz);
			//各方向坐标下的绝对速度Vx,Vy,Vz未转换，直接做集对分析处理
			Mf_SPA(iteTra->dTSpeedX,iteRequestMsg->stTrace.dTSpeedX,dcorrVx);
			VctCorr.push_back(dcorrVx);
			Mf_SPA(iteTra->dTSpeedY,iteRequestMsg->stTrace.dTSpeedY,dcorrVy);
			VctCorr.push_back(dcorrVy);
			Mf_SPA(iteTra->dTSpeedZ,iteRequestMsg->stTrace.dTSpeedZ,dcorrVz);
			VctCorr.push_back(dcorrVz);
			//对相关系数容器处理，取容器中数据的平均值
			for (iteCorr = VctCorr.begin(); iteCorr != VctCorr.end(); iteCorr++)
			{
				dSumCorr = dSumCorr + *iteCorr;  
			}
			dAverCorr = dSumCorr/VctCorr.size();  //取相关系数的平均值
			//下次存放集对系数前先清空VctCorr容器
			VctCorr.clear();
			//与阈值比较（如何设定阈值，相关系数大于某阈值时，认为航迹是可以关联的?????????????????????）
			if (dAverCorr > 0.8) //0.8为阈值，测试时可调节
			{   //航迹信息可以关联，将信息放入vctBackCooperative返回信息容器中，
				//将同一合批号下（即相同方位下）的一条航迹信息，还有N条ESM与Com信息放入vctBackCooperative中
				//未编批则无综合批号
				stBackMsg.lAutonum = iteRequestMsg->stTrace.lAutonum; //将无聚类的航迹请求信息中的目标批号给返回信息
				memcpy(&stBackMsg.stBackShipPosi,&stSelfPosi,sizeof(stBackMsg.stBackShipPosi));  //memcpy(&A,&B,sizeof(A)); 把结构体B给结构体A
				//存航迹信息
				memcpy(&stBackMsg.stTrace,&iteTra,sizeof(stBackMsg.stTrace));	
				stBackMsg.BackTrackN = 1;
				
				//将查找到的信息存入vctBackCooperative容器中
				vctBackCooperative.push_back(stBackMsg);
				iteRequestMsg->nCorrFlag = 1;
				break;//找到，跳出循环 
				//至此，从未聚类的航迹表里取出关联信息，存入vctBackCooperative容器中 
			}// if (AverCorr >0.8 )
			
		}// for  iteTra遍历为聚类的航迹中查找
		
	}// if ( iteRequestMsg->nCorrFlag == 0)
	
}//void ReqSingleTrace_COOP_Find_Information_To_MainShip()结束



/*******************************************************************************/
/*******      目标邻舰观测的径距、方位和仰角转到本舰同一坐标系中模块     *******/
//*******     输入：                                                     *******/
//*******           目标相对邻舰2的径距、方位和仰角(Rd2,Az2,Ez2)         *******/
/*******            本舰地理坐标（La1,Ba1,Ha1）                         ********/
/*******            邻舰地理坐标（La2,Ba2,Ha2）                         ********/
//*******     输出：                                                     *******/
/********           目标从邻舰转到本舰的大地雷达测量系中的坐标Xt,Yt,Zt   *******/
/*******************************************************************************/

//本舰自身无航迹信息时
void Get_NO_SelfTrack_Coordinate_Conversion_Module(double Rd2,double Az2,double Ez2,double La1,double Ba1,double Ha1,
												   double La2,double Ba2,double Ha2,double& Xt,double& Yt,double& Zt)
{
	double x2,y2,z2;
	
	double xg,yg,zg;      //邻舰在本舰中的坐标
	double Rd,Az,Ez;
	double xxd,yyd,zzd;
	
	double dertH;               //放高度补偿
	double G1;                  //邻舰与本舰之间的地面距离
	double ae;
	
	//目标在邻舰的大地雷达坐标系中的直角坐标
	x2=Rd2*cos(Ez2)*sin(Az2);
	y2=Rd2*cos(Ez2)*cos(Az2);
	z2=Rd2*sin(Ez2);
	
	//邻舰相对于本舰的径距、方位和俯仰
	Object_Radar_Transform(La2,Ba2,Ha2,La1,Ba1,Ha1,Rd,Az,Ez); //邻舰位置可直接从战情获得，或协同请求时邻舰报文给出
	
	ae=4*6378130.0/3;                //地球等效半径(m),即为地球半径的三分之四
	G1=2*ae*asin(0.5*Rd/ae);
	
	dertH=0.43*G1*G1/ae;           //高度补偿(相对于本舰)
	
	//邻舰位置在本舰中的坐标
	xg=Rd*cos(Ez)*sin(Az);
	yg=Rd*cos(Ez)*cos(Az);
	zg=Rd*sin(Ez)+dertH;              //高度补偿(相对于本舰)
	
	//坐标系平移：本舰视为旧坐标、邻舰视为新坐标
	//目标在本舰中的坐标为：
	xxd=x2+xg;
	yyd=y2+yg;
	zzd=z2+zg; 
	
	Xt=xxd;       //带回目标在本邻舰中转到本舰的坐标
	Yt=yyd;
	Zt=zzd;	
}

/*******************************************************************/
/***            目标在雷达坐标系中位置计算模块                   ***/
/**                     刘以安  2011-2-10                        ***/
/********      输入：目标平台位置（Lt,Bt,Ht）                *******/
/********            雷达平台位置（L0,B0,H0）                *******/
/********      输出：目标在雷达大地测量坐标系中的径距、方位和仰角 **/
/*******************************************************************/
void Object_Radar_Transform(double Lt,double Bt,double Ht,double L0,double B0,double H0,double& rd,double& az,double& ez)
{
	double a,e2;
	double Nt,Nr;
	double xt,yt,zt,x0,y0,z0;
	double Rd,Az,Ez;
	double x,y,z;
	
	a=6378137;
	e2=0.0066943799014;
	
	Nt=a/sqrt(1-e2*sin(Bt)*sin(Bt));
	Nr=a/sqrt(1-e2*sin(B0)*sin(B0));
	
	xt=(Nt+Ht)*cos(Bt)*cos(Lt);
	yt=(Nt+Ht)*cos(Bt)*sin(Lt);
	zt=(Nt*(1-e2)+Ht)*sin(Bt);
	
	x0=(Nr+H0)*cos(B0)*cos(L0);
	y0=(Nr+H0)*cos(B0)*sin(L0);
	z0=(Nr*(1-e2)+H0)*sin(B0);
	
	x=-(xt-x0)*sin(L0)+(yt-y0)*cos(L0);
	y=-(xt-x0)*sin(B0)*cos(L0)-(yt-y0)*sin(B0)*sin(L0)+(zt-z0)*cos(B0);
	z=(xt-x0)*cos(B0)*cos(L0)+(yt-y0)*cos(B0)*sin(L0)+(zt-z0)*sin(B0);
	
	Rd=sqrt(x*x+y*y+z*z);  //已知坐标XYZ，求出该坐标系下的距离，方位，仰角
	if(x>=0&&y>0)
	{
		Az=atan(x/y);
	}
	else if(x>0&&fabs(y)<1.0e-3)
	{
		Az=0.5*PI;
	}
	else if(y<0)
	{
		Az=PI+atan(x/y);
	}
	else if(x<0&&fabs(y)<1.0e-3)
	{
		Az=1.5*PI;
	}
	else if(x<0&&y>0)
	{
		
		Az=2*PI+atan(x/y);
	}
	
	Ez=atan(z/sqrt(x*x+y*y)); 
	
	rd=Rd;
	az=Az;
	ez=Ez;       
}


/*******************************************************************************/
/*******      目标邻舰观测的径距、方位和仰角转到本舰同一坐标系中模块     *******/
//*******     输入：目标相对本舰1的径距、方位和仰角(Rd1,Az1,Ez1)         *******/
//*******           目标相对邻舰2的径距、方位和仰角(Rd2,Az2,Ez2)         *******/
/*******            本舰地理坐标（La1,Ba1,Ha1）                         ********/
/*******            邻舰地理坐标（La2,Ba2,Ha2）                         ********/
//*******     输出：//目标在本舰的大地雷达测量系中的坐标x1,y1,z1           *******/
/********           目标从邻舰转到本舰的大地雷达测量系中的坐标Xt,Yt,Zt   *******/
/********           目标从邻舰转到本舰的大地雷达测量系中的径距、方位和仰角(Rdt,Azt,Ezt) **/
/********           目标相对两舰观测的集对综合相关系数SumCorr           ********/
/*******************************************************************************/
void Get_Coordinate_Conversion_Module(double Rd1,double Az1,double Ez1,double Rd2,double Az2,double Ez2,double La1,double Ba1,double Ha1,
									  double La2,double Ba2,double Ha2,/*double *x1,double *y1,double *z1,*/
									  double& Xt,double& Yt,double& Zt,double& Rdt,double& Azt,double& Ezt,double& SumCorr_xyz)
{
	double xa,ya,za;
	double x2,y2,z2;
	double xg,yg,zg;      //邻舰在本舰中的坐标
	double Rd,Az,Ez;
	double xt,yt,zt;
	
	double corr1,corr2,corr3/*,corr4,corr5,corr6*/;   //放集对系数
    double dertH;               //放高度补偿
	double G1;                  //邻舰与本舰之间的地面距离
	double ae;
	
	//目标在本舰的大地雷达坐标系中的直角坐标
	xa=Rd1*cos(Ez1)*sin(Az1);
	ya=Rd1*cos(Ez1)*cos(Az1);
	za=Rd1*sin(Ez1);
	
	// 	*x1=xa;    //带回目标在本舰中的坐标
	// 	*y1=ya;
	// 	*z1=za;
	
	//目标在邻舰的大地雷达坐标系中的直角坐标
	x2=Rd2*cos(Ez2)*sin(Az2);
	y2=Rd2*cos(Ez2)*cos(Az2);
	z2=Rd2*sin(Ez2);
	
	//目标相对于本舰的径距、方位和俯仰
	Object_Radar_Transform(La2,Ba2,Ha2,La1,Ba1,Ha1,Rd,Az,Ez); //邻舰位置可直接从战情获得，或协同请求时邻舰报文给出
	
	ae=4*6378130.0/3;                //地球等效半径(m),即为地球半径的三分之四
	G1=2*ae*asin(0.5*Rd/ae);
    
	dertH=0.43*G1*G1/ae;           //高度补偿(相对于本舰)
	
	//邻舰位置在本舰中的坐标
	xg=Rd*cos(Ez)*sin(Az);
	yg=Rd*cos(Ez)*cos(Az);
	zg=Rd*sin(Ez)+dertH;              //高度补偿(相对于本舰)
	
	//坐标系平移：本舰视为旧坐标、邻舰视为新坐标
	//目标在本舰中的坐标为：
	xt=x2+xg;
	yt=y2+yg;
	zt=z2+zg; 
	
	Xt=xt;       //带回目标在本邻舰中转到本舰的坐标
	Yt=yt;
	Zt=zt;
	
	//调集对分析模块
	Mf_SPA(xa,xt,corr1);
	Mf_SPA(ya,yt,corr2);
	Mf_SPA(za,zt,corr3);
	
	SumCorr_xyz=0.5*corr1+0.3*corr2+0.2*corr3;		
	
	//根据转换后的坐标，将目标在邻舰中的径距方位仰角转化成目标在本舰中的径距方位仰角
	Rdt=sqrt(xt*xt+yt*yt+zt*zt);  //已知坐标XYZ，求出该坐标系下的距离，方位，仰角
	if(xt>=0&&yt>0)
	{
		Azt=atan(xt/yt);
	}
	else if(xt>0&&fabs(yt)<1.0e-3)
	{
		Azt=0.5*PI;
	}
	else if(yt<0)
	{
		Azt=PI+atan(xt/yt);
	}
	else if(xt<0&&fabs(yt)<1.0e-3)
	{
		Azt=1.5*PI;
	}
	else if(xt<0&&yt>0)
	{
		
		Azt=2*PI+atan(xt/yt);
	}
	
	Ezt=atan(zt/sqrt(xt*xt+yt*yt)); 
	
	// 	//调集对分析模块
	// 	Mf_SPA(Rd1,Rdt,&corr4);
	// 	Mf_SPA(Az1,Azt,&corr5);
	// 	Mf_SPA(Ez1,Ezt,&corr6);
	// 
	// 	
	// 	*AverCorr=SumCorr_xyz/4+corr4/4+corr5/4+corr6/4;	 //比例系数 有待修改（规定标准是什么????）
	
}
/************************************************************************/
/*                             集对分析算子                             */
/************************************************************************/
void Mf_SPA(double s, double t,double& corr)
{
	double spa;
	double tmp;
	
	double a,b,c;
	
	if(s>t)
	{
		tmp =s;
		s=t;
		t=tmp;
	}
	
	a=s/t;
	b=s/t/(t*t-1);
	c=(t*t-s*t-1)/(t*t-1);
	
	spa=a+fabs(b)-fabs(c);
	
	corr=spa;                 //带回两数相关系数
}
/* 输入:本舰上聚类后的信息结构体, 请求信息 (结构体), 返回信息(结构体)*/ 
void CoopFind_Information_To_MainShip(UNI_All_NUM& stUniAll, SendRequest_Msg& stSendRequest, SendBack_Msg& stSendBackMsg)
{
	//将请求信息的结构体先转化成小容器的结构体, 将该结构体放入容器中push back到vctRequestCooperative将舰的位置信息单独存放,
	int i ,j;
    //根据请求信息结构体的综合批号,选择需要调用的函数,再将子函数调用的结果转化为主函数SendBack_Msg数组的容器形式
	Request_Cooperative_Msg stReqCooperMsg;
	VCT_Request_Cooperative_Msg vctReqCoopMsg;
	VCT_BACK_Cooperative_Msg vctBackCooperative1;
	ESMSTATUS_MARK stEsm;
	COMSTATUS_MARK stCom;
    SHIP_POSITION stSelfPosi;
	VCT_ESM_MSG::iterator iteEsm;
	VCT_COMM_MSG::iterator iteCom;
	VCT_Request_Cooperative_Msg::iterator iteReqCoopMsg;
    VCT_Request_Cooperative_Msg::iterator iteRequestMsg1;
	VCT_BACK_Cooperative_Msg::iterator iteBackMsg;
	//将请求信息的数组结构体先转化为含容器的结构体
    stReqCooperMsg.lAutonum = stSendRequest.lAutomn;
    stReqCooperMsg.nCorrFlag = stSendRequest.nCorrFlag;
	stReqCooperMsg.nStampTime = stSendRequest.nStampTime;
    memcpy(&stSelfPosi, &stSendRequest.stReqShipPosi, sizeof(stSelfPosi)); 
	//	cout<<" 经纬高"<< stSelfPosi.dHeight <<endl;
	memcpy(&stReqCooperMsg.stReqShipPosi, &stSendRequest.stReqShipPosi, sizeof(stReqCooperMsg.stReqShipPosi)); //memcpy(&A,&B,sizeof(A)); 把结构体B给结构体A
	memcpy(&stReqCooperMsg.stTrace, &stSendRequest.stTrace,sizeof(stReqCooperMsg.stTrace));
    for ( i=0; i< stSendRequest.nRequestEsmN; i++)
    {
		stEsm.lTargetNumber = stSendRequest.lEsmTargetNumber[i];
		stEsm.dZaiPin = stSendRequest.dEsmZaiPin[i];
		stEsm.dMaiKuan = stSendRequest.dEsmMaiKuan[i];
		stEsm.dTianXianScan = stSendRequest.dEsmTianXianScan[i];
//		stEsm.dConfidence = stSendRequest.dEsmConfidence[i];
		stReqCooperMsg.vctEsm.push_back(stEsm);
    }
	for ( j=0; j< stSendRequest.nRequestComN; j++)
	{
		stCom.lTargetNumber = stSendRequest.lComTargetNumber[j];
		stCom.dComZaiPin = stSendRequest.dComZaiPin[j];
		stCom.dPulseExtent = stSendRequest.dComPulseExtent[j];
		stCom.dComFre = stSendRequest.dComFre[j];
		stCom.dComBand = stSendRequest.dComBand[j];
		stCom.dComJPN = stSendRequest.dComJPN[j];
	//	stCom.dConfidence = stSendRequest.dComConfidence[i];
		stReqCooperMsg.vctComm.push_back(stCom);
	}
	//清空vctReqCoopMsg
	//将转化后的结构体放入容器中(push back到vctReqCoopMsg)
	for ( iteReqCoopMsg = vctReqCoopMsg.begin(); iteReqCoopMsg != vctReqCoopMsg.end(); iteReqCoopMsg++)
	{ 
		iteReqCoopMsg->lAutonum = NULL;
		iteReqCoopMsg->nCorrFlag = NULL;
		iteReqCoopMsg->nStampTime = NULL;
		memset(&iteReqCoopMsg->stReqShipPosi, 0, sizeof(SHIP_POSITION));
		memset(&iteReqCoopMsg->stTrace, 0, sizeof(TRACKSTATUS_MARK));
		for ( iteEsm = iteReqCoopMsg->vctEsm.begin(); iteEsm != iteReqCoopMsg->vctEsm.end(); iteEsm++)
		{
			memset(&(*iteEsm), 0, sizeof(ESMSTATUS_MARK));
		}
		for ( iteCom = iteReqCoopMsg->vctComm.begin(); iteCom != iteReqCoopMsg->vctComm.end();iteCom++)
		{
			memset(&(*iteCom), 0, sizeof(COMSTATUS_MARK));
		}		
	}
	vctReqCoopMsg.clear();
	vctReqCoopMsg.push_back(stReqCooperMsg);
	
	for (iteRequestMsg1 = vctReqCoopMsg.begin(); iteRequestMsg1 != vctReqCoopMsg.end(); iteRequestMsg1++)
	{  	//遍历请求信息中每个结构体，
		if (iteRequestMsg1->lAutonum >7999)  //请求信息中，综合批号大于等于8000，即为聚类后有航迹信息的
		{
			ReqUnin_COOP_Find_Information_To_MainShip(stSelfPosi, stUniAll, iteRequestMsg1, vctBackCooperative1);
		}
		if (iteRequestMsg1->lAutonum < 8000 && iteRequestMsg1->lAutonum > 6999 )//请求信息，(无航迹信息)综合批号为 聚类后的综合批号在7000--8000之间
		{
			ReqNoTraceUnin_COOP_Find_Information_To_MainShip(stSelfPosi,stUniAll, iteRequestMsg1, vctBackCooperative1);
		}
		if (iteRequestMsg1->lAutonum < 6000)  //请求信息，//暂定有未聚类的航迹信息,目标批号在5000到6000之间  
		{
			ReqSingleTrace_COOP_Find_Information_To_MainShip(stSelfPosi,stUniAll, iteRequestMsg1, vctBackCooperative1);
		}
	}//for  iteRequestMsg1
    // 返回信息存放在vctBackCooperative1中 ,将返回信息的格式转化为含数组的结构体 stSendBackMsg
	
	if (vctBackCooperative1.size() == 0)
	{
		//返回容器中没有信息，表示未找到相关信息
	}
	else
	{
		//找到类似的返回信息、
		for ( iteBackMsg = vctBackCooperative1.begin(); iteBackMsg != vctBackCooperative1.end(); iteBackMsg++)
		{
			stSendBackMsg.lAutonum = iteBackMsg->lAutonum;
			stSendBackMsg.BackESMN = iteBackMsg->vctEsm.size();
			stSendBackMsg.BackCOMN = iteBackMsg->vctComm.size();
			//esm
			if ( stSendBackMsg.BackESMN != 0)
			{
				for (  i = 0 ; i < stSendBackMsg.BackESMN; i++)
				{
					stSendBackMsg.lEsmTargetNumber[i] = iteBackMsg->vctEsm.at(i).lTargetNumber;
					stSendBackMsg.dEsmZaiPin[i] =  iteBackMsg->vctEsm.at(i).dZaiPin;
					stSendBackMsg.dChongPin[i] = iteBackMsg->vctEsm.at(i).dChongPin;
					stSendBackMsg.dEsmMaiKuan[i] = iteBackMsg->vctEsm.at(i).dMaiKuan;
					stSendBackMsg.dEsmTianXianScan[i] = iteBackMsg->vctEsm.at(i).dTianXianScan;
					stSendBackMsg.dEsmConfidence[i] = iteBackMsg->vctEsm.at(i).dConfidence;
					for ( int k = 0; k<32; k++)
					{
						stSendBackMsg.sEsmPlatType[i][k] = iteBackMsg->vctEsm.at(i).sPlatType[k];

					}	
				}	
			}
            //com
			if ( stSendBackMsg.BackCOMN != 0)
			{
				for (  i = 0 ; i < stSendBackMsg.BackCOMN; i++)
				{
					stSendBackMsg.lComTargetNumber[i] = iteBackMsg->vctComm.at(i).lTargetNumber;
					stSendBackMsg.dComZaiPin[i] =  iteBackMsg->vctComm.at(i).dComZaiPin;
					stSendBackMsg.dComPulseExtent[i] = iteBackMsg->vctComm.at(i).dPulseExtent;
					stSendBackMsg.dComFre[i] = iteBackMsg->vctComm.at(i).dComFre;// 中心频率(MHz)
					stSendBackMsg.dComBand[i] = iteBackMsg->vctComm.at(i).dComBand;// 信号带宽(MHz)
					stSendBackMsg.dComJPN[i] = iteBackMsg->vctComm.at(i).dComJPN; // 跳步次数
					stSendBackMsg.dComConfidence[i] = iteBackMsg->vctComm.at(i).dConfidence;
					for ( int k = 0; k<32; k++)
					{
						stSendBackMsg.sComPlatType[i][k] = iteBackMsg->vctComm.at(i).sPlatType[k];	
					}
				}
			}
			//有航迹
			if (iteBackMsg->lAutonum >= 8000)
			{
				stSendBackMsg.BackTraceN = 1;

				//				cout<< "返回信息的航迹信息"<<iteBackMsg->lAutonum<<endl;
				memcpy( &stSendBackMsg.stTrace,&iteBackMsg->stTrace,sizeof(stSendBackMsg.stTrace));
				//			    cout<< "返回信息的航迹信息"<<stSendBackMsg.stTrace.sPlatType<<endl;
			}			
		}
	}
}