// Algorithm.cpp: implementation of the CAlgorithm class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "nodeplat.h"
#include "Algorithm.h"
#include <algorithm>
using namespace std;


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern CNodePlatApp theApp;
CAlgorithm::CAlgorithm()
{
	m_ForeData.clear();
	m_NowData.clear();
	m_mapBasicEvent.clear();
}

CAlgorithm::~CAlgorithm()
{

}

//////////////////////////////基本事件层//////////////////////////////////////////////////////////////////

//**************************************************************************************************//
//                    目标数据拷贝                                                                  //
//    输入：目标地址，，要拷贝的数据                                                                //
//    输出：                                                                                        // 
//    返回值：0表示输入有误，1表示正确返回                                                          //
//**************************************************************************************************//
int CAlgorithm::CopyData(VCT_Cooperative_FUSIDENTIINFOR& DstData, VCT_Cooperative_FUSIDENTIINFOR& SourceData)
{
	char* str = NULL;
	VCT_Cooperative_FUSIDENTIINFOR::iterator iteDst;
	VCT_Cooperative_FUSIDENTIINFOR::iterator iteSor;
	VCT_ESM_MSG::iterator iteESMSor;
	VCT_COMM_MSG::iterator iteCOMSor;
	
	if (SourceData.empty())
	{
		return 0;
	}
	iteSor = SourceData.begin();
	iteDst = DstData.begin();
	while(iteDst != NULL)
	{
	//	iteDst->cPlatName = iteSor->cPlatName;
		memcpy(&iteDst->sPlatType, &iteSor->sPlatType, sizeof(iteSor->sPlatType));
		iteDst->dConfidence = iteSor->dConfidence;
		iteDst->lAutonum = iteSor->lAutonum;
		iteDst->lStampTime = iteSor->lStampTime;
		memcpy(&iteDst->stFusTrack, &iteSor->stFusTrack, sizeof(iteSor->stFusTrack));
		iteDst->vctFusEsm.clear();
		iteDst->vctFusCom.clear();
		for (iteESMSor = iteSor->vctFusEsm.begin(); iteESMSor != iteSor->vctFusEsm.end(); ++iteESMSor)
		{
			iteDst->vctFusEsm.push_back(*iteESMSor);
		}
		for (iteCOMSor = iteSor->vctFusCom.begin(); iteCOMSor != iteSor->vctFusCom.end(); ++iteCOMSor)
		{
			iteDst->vctFusCom.push_back(*iteCOMSor);
		}
	}
	return 1;	
}

//**************************************************************************************************//
//                    目标数据缓存模块                                                              //
//    输入：当前融合下发信息 ，两个缓存空间                                                         //
//    输出：两个缓存空间                                                                            // 
//    返回值：0表示输入有误，1表示正确返回                                                          //
//**************************************************************************************************//
int CAlgorithm::BufferData(VCT_Cooperative_FUSIDENTIINFOR& ForeBufferData, VCT_Cooperative_FUSIDENTIINFOR& NowBufferData, VCT_Cooperative_FUSIDENTIINFOR NowData)
{
	//接收的数据为空
	if (NowData.empty())
	{
		return 0;
	}
	VCT_Cooperative_FUSIDENTIINFOR::iterator iteNow;
	VCT_Cooperative_FUSIDENTIINFOR::iterator iteData;
	
	//将NowBufferData中的数据拷贝到ForeBufferData中
	ForeBufferData.clear();
	for (iteNow = NowBufferData.begin(); iteNow != NowBufferData.end(); ++iteNow)
	{
		ForeBufferData.push_back(*iteNow);
	}
	NowBufferData.clear();
	for (iteData = NowData.begin(); iteData != NowData.end(); ++iteData)
	{
		NowBufferData.push_back(*iteData);
	}
	
	return 1;
}

//**************************************************************************************************//
//                    目标速度计算模块                                                              //
//    输入：当前融合下发信息 此处vector中需要计算目标速度的数据                                     //
//    输出：当前目标融合信息后+计算的速度                                                           // 
//    返回值：0表示输入有误，1表示正确返回                                                          //
//**************************************************************************************************//
int CAlgorithm::CalculateSpeed(VCT_Cooperative_FUSIDENTIINFOR& TaishiFore)
{
	VCT_Cooperative_FUSIDENTIINFOR::iterator ite_taishi;
	int nInputSize = TaishiFore.size();
	ite_taishi = TaishiFore.begin();
	
// 	if (TaishiFore)
// 	{
// 		return 0;
// 	}
	
	while (ite_taishi != TaishiFore.end())
	{
		ite_taishi->stFusTrack.dVSpeed = sqrt(ite_taishi->stFusTrack.dTSpeedX*ite_taishi->stFusTrack.dTSpeedX +
			ite_taishi->stFusTrack.dTSpeedY*ite_taishi->stFusTrack.dTSpeedY + ite_taishi->stFusTrack.dTSpeedZ*ite_taishi->stFusTrack.dTSpeedZ);
		ite_taishi++;
	}
	
	return 1;
}


//**************************************************************************************************//
//                    目标加速度计算模块                                                              //
//    输入：当前融合下发信息 此处有两个vector，                                                     //
//            TaishiFore表示前一时刻数据，TaishiNow表示当前时刻的数据                               //
//    输出：将计算的加速度值填入到TaishiNow中                                                       //
//    返回值：0表示输入有误，1表示正确返回                                                          //
//**************************************************************************************************//
int CAlgorithm::CalculateAddSpeed(VCT_Cooperative_FUSIDENTIINFOR& TaishiFore, VCT_Cooperative_FUSIDENTIINFOR& TaishiNow)
{
	double dForeSpeed;
	double dNowSpeed;
	VCT_Cooperative_FUSIDENTIINFOR::iterator iteFore;
	VCT_Cooperative_FUSIDENTIINFOR::iterator iteNow;
	
// 	if (TaishiNow == NULL)
// 	{
// 		return 0;
// 	}
	
	for (iteNow = TaishiNow.begin(); iteNow != TaishiNow.end(); ++iteNow)
	{
		for (iteFore = TaishiFore.begin(); iteFore != TaishiFore.end(); ++iteFore)
		{
			if (iteNow->lAutonum == iteFore->lAutonum)
			{
				dForeSpeed = iteFore->stFusTrack.dVSpeed;
				dNowSpeed = iteNow->stFusTrack.dVSpeed;
				iteNow->stFusTrack.dAddSpeed = (dNowSpeed - dForeSpeed)/((iteNow->lStampTime - iteFore->lStampTime)/1000);
			}
		}
	}
	
	return 1;
}

//**************************************************************************************************//
//                    航迹威胁度计算模块采用三角模糊                                                //
//    输入：TaishiNow表示当前时刻的数据                                                             //
//    输出：将计算的威胁度值填入到TaishiNow中                                                       //
//    返回值：综合威胁度                                                                            //
//**************************************************************************************************//

// 1战斗机、2 轰炸机、3歼击机 、攻击机 （认为属1类）
// 4预警机、   （认为属2类）
// 5侦察机、6干扰机7 直升机(包括反潜机、无人机、不明)   （认为属3类）
// 8 舰艇             （属4类）
// 9战术导弹、（属5类）
// 10制导武器  （属6类）

double CAlgorithm::TrackThreatDegree(VCT_Cooperative_FUSIDENTIINFOR::iterator iteNow)
{
	double ThreRd,ThreHigh,ThreVSpeed,ThreAddSpeed,ThreAzmith,ThreType;//放目标航迹中单个特征威胁度
	double SumThredg;    //放临时威胁度和
	double temp;

	//径距威胁度模糊计算
	if(iteNow->stFusTrack.nTgtType != 4)    //属4类
	{
		if(iteNow->stFusTrack.dRange > 60000)     //径距60km
		{
	         ThreRd=0;
		}
	    else if(iteNow->stFusTrack.dRange > 5000 && iteNow->stFusTrack.dRange <= 60000)
		{
             ThreRd=(60 - iteNow->stFusTrack.dRange)/55000;
		}
		else
		{
		     ThreRd=1.0;
		}
		   
	}
	else    //飞机、导弹类
	{
		if(iteNow->stFusTrack.dRange > 200000)   //径距200km
		{
	         ThreRd=0;
		}
		else if(iteNow->stFusTrack.dRange > 10 && iteNow->stFusTrack.dRange <= 200000)
        {
			ThreRd=(200000 - iteNow->stFusTrack.dRange)/190000;
		}
		else
		{
			ThreRd = 1.0;
		}
		
	}
		
	//高度威胁度模糊计算
	if(iteNow->stFusTrack.nTgtType == 4)
	{
		  ThreHigh = 0;
	}
	else//否则，飞机类
	{
	     if(iteNow->stFusTrack.dHeight <= 100)//高度100m
		 {
	         ThreHigh = 1.0;
		 }
		 else if(iteNow->stFusTrack.dHeight > 100 && iteNow->stFusTrack.dHeight < 15000)
         {
			 ThreHigh = (15000 - iteNow->stFusTrack.dHeight)/15000;
		 }
		 else
		 {
		     ThreHigh = 0;
		 }	
	}

	//速度威胁度模糊计算
	if(iteNow->stFusTrack.nTgtType == 4)
	{
					 
	    if(iteNow->stFusTrack.dVSpeed > 60)//速度
		{
	           ThreVSpeed = 1;
		}
		else if(iteNow->stFusTrack.dVSpeed > 10 && iteNow->stFusTrack.dVSpeed <= 60)
		{
               ThreVSpeed = (iteNow->stFusTrack.dVSpeed - 10)/50;
		}
		else
		{
		       ThreVSpeed = 0;
		}
	}
	else if(iteNow->stFusTrack.nTgtType == 1 || iteNow->stFusTrack.nTgtType == 2 || iteNow->stFusTrack.nTgtType == 3)//飞机
	{
			  
	    if(iteNow->stFusTrack.dVSpeed > 1.8*340) //速度1.8Ma
		{
		       ThreVSpeed = 1.0;
		}
		else if(iteNow->stFusTrack.dVSpeed > 0.5*340 && iteNow->stFusTrack.dVSpeed <= 1.8*340)
		{
               ThreVSpeed = (iteNow->stFusTrack.dVSpeed - 170)/620;
		}
		else
		{
	           ThreVSpeed = 0.0;
		}
	}
	else  //导弹类
	{
		if(iteNow->stFusTrack.dVSpeed > 2.5*340)//速度2.5Ma
		{
		       ThreVSpeed = 1.0;
		}
		else if(iteNow->stFusTrack.dVSpeed > 1.5*340 && iteNow->stFusTrack.dVSpeed <= 2.5*340)
		{
               ThreVSpeed=(iteNow->stFusTrack.dVSpeed - 500)/170;
		}
		else
		{
		       ThreVSpeed = 0.0;
		}
	}

	//加速度威胁度模糊计算
	if(iteNow->stFusTrack.dAddSpeed <= 5)//加速度
	{
		      ThreAddSpeed = 0;
	}
	else if(iteNow->stFusTrack.dAddSpeed > 5 && iteNow->stFusTrack.dAddSpeed <= 20)
    {
		ThreAddSpeed = (iteNow->stFusTrack.dAddSpeed - 5)/15;
	}
	else
	{	
	    	ThreAddSpeed = 1.0;
	}
	 //目标航向威胁度模糊计算      Azimuth本舰航向和NewAzimuth目标航向
//	 temp = fabs(NewAzimuth - Azimuth); //弧度
	 temp = fabs(3 - iteNow->stFusTrack.dCourse); //弧度
	 if(temp <= 3*PI_4/180)               //加速度
	 {
		 ThreAzmith=1;
	 }
	 else if(temp > 3*PI_4/180 && temp <= 20*PI_4/180)
     {
		 ThreAzmith = (20*PI_4/180 - temp)*180/17/PI_4;
	 }
	 else
	 {
		 ThreAzmith = 0.0;
	 }

	 //目标类型威胁度模糊计算
	 if(iteNow->stFusTrack.nTgtType == 5)   //导弹
	 {
		 ThreType = 1.0;
	 }
	 else if(iteNow->stFusTrack.nTgtType == 6)   // 制导武器
	 {
		 ThreType = 0.2025;
	 }
     else if(iteNow->stFusTrack.nTgtType == 1)  //'战斗机、 轰炸机、歼击机 、攻击机'
	 {
		 ThreType = 0.4022;
	 }
     else if(iteNow->stFusTrack.nTgtType == 2)   //'预警机'
	 {
		 ThreType = 0.5774;
	 }
	 else if(iteNow->stFusTrack.nTgtType == 3)   //'侦察机、6干扰机7 直升机'
	 {
		 ThreType = 0.1001;
	 }
	 else
	 {
		 ThreType = 0.0001;
	 }

     SumThredg=ThreRd + ThreHigh + ThreVSpeed + ThreAddSpeed + ThreAzmith + ThreType;
     
	 return (SumThredg/6);  //归一化并加权,//带回: 该目标航迹的综合威胁度

}


//**************************************************************************************************//
//                    ESM威胁度计算模块采用三角模糊                                                //
//    输入：TaishiNow表示当前时刻的数据                                                             //
//    输出：将计算的威胁度值填入到TaishiNow中                                                       //
//    返回值：ESM威胁度                                                                            //
//**************************************************************************************************//
double CAlgorithm::ESMThreatDegree(VCT_Cooperative_FUSIDENTIINFOR::iterator iteNow)
{
	double ThreFre,ThrePA,ThrePw,ThrePRI,ThreScan;                     //放ESM中单个特征威胁度
	double SumThredg;    //放临时威胁度和
	double dAllThredg(1.0);   //ESM威胁度
	VCT_ESM_MSG::iterator iteESM;
	
	for(iteESM = iteNow->vctFusEsm.begin(); iteESM != iteNow->vctFusEsm.end(); ++iteESM)
	{
		//脉冲频率
		if(iteESM->dMaiChongFeature <= 0.5)
		{
			ThreFre = 0;
		}
		else if(iteESM->dMaiChongFeature > 0.5 && iteESM->dMaiChongFeature <= 2)
		{
			ThreFre=0.2;
		}
		else if(iteESM->dMaiChongFeature > 2 && iteESM->dMaiChongFeature <= 4)
		{
			ThreFre=0.4;
		}
		else if(iteESM->dMaiChongFeature > 4 && iteESM->dMaiChongFeature <= 8)
		{
			ThreFre=0.6;
		}
		else
		{
			ThreFre=1.0;
		}
		//脉冲幅度
		if(iteESM->dPulseExtent <= 0.2)
		{
			ThrePA = 0;
		}
		else if(iteESM->dPulseExtent > 0.2 && iteESM->dPulseExtent < 0.6)
		{
			ThrePA = 0.5;
		}
		else
		{
			ThrePA = 1.0;
		}
		//脉宽
		if(iteESM->dMaiKuan <= 1)               //
		{
			ThrePw = 1;
		}
		else if(iteESM->dMaiKuan > 1 && iteESM->dMaiKuan <= 20)
		{
			ThrePw = 0.8;
		}
		else if(iteESM->dMaiKuan > 20 && iteESM->dMaiKuan <= 100)
		{
			ThrePw = 0.4;
		}
		else if(iteESM->dMaiKuan > 100 && iteESM->dMaiKuan <= 300)
		{
			ThrePw = 0.2;
		}
		else
		{
			ThrePw = 0.0;
		}
		//重频
		if(iteESM->dChongPin <= 0.002)               //
		{
			ThrePRI = 1;
		}
		else if(iteESM->dChongPin > 0.02 && iteESM->dChongPin <= 0.500)
		{
			ThrePRI = 0.6;
		}
		else if(iteESM->dChongPin > 0.5 && iteESM->dChongPin <= 2)
		{
			ThrePRI = 0.4;
		}
		else
		{
			ThrePRI = 0.0;
		}		
		//天线扫描周期
		if(iteESM->dMaiChongFeature <= 0.5)               //
		{
			ThreScan = 1;
		}
		else if(iteESM->dMaiChongFeature > 0.5 && iteESM->dMaiChongFeature <= 1)
		{
			ThreScan = 0.7;
		}
		else if(iteESM->dMaiChongFeature > 1 && iteESM->dMaiChongFeature <= 2)
		{
			ThreScan = 0.4;
		}
		else
		{
			ThreScan = 0.0;
		}
		SumThredg = (ThreFre + ThrePA + ThrePw + ThrePRI + ThreScan)/5;
		dAllThredg = dAllThredg * (1 - SumThredg);

	}
	return dAllThredg;
}

//**************************************************************************************************//
//                    目标威胁度计算模块                                                            //
//    输入：TaishiNow表示当前时刻的数据                                                             //
//    输出：将计算的威胁度值填入到TaishiNow中                                                       //
//    返回值：0表示输入有误，1表示正确返回                                                          //
//**************************************************************************************************//
int CAlgorithm::ThreatDegree(VCT_Cooperative_FUSIDENTIINFOR& TaishiNow)
{
	double dTgtThrDg;  //目标威胁度
	VCT_Cooperative_FUSIDENTIINFOR::iterator iteNow;
	
// 	if (TaishiNow == NULL)
// 	{
// 		return 0;
// 	}
	
	for (iteNow = TaishiNow.begin(); iteNow != TaishiNow.end(); ++iteNow)
	{
		if (iteNow->lAutonum < 3000) //3000一下表示无目标未编批
		{
			iteNow->stFusTrack.dThrDg = TrackThreatDegree(iteNow);
		} 
		else if (iteNow->lAutonum >3000 && iteNow->lAutonum < 8000) 
		{
			//不应该出现此种情况
		} 
		else                               //有目标编批
		{
			dTgtThrDg = 1 - (1 - TrackThreatDegree(iteNow)) * ESMThreatDegree(iteNow);
			iteNow->stFusTrack.dThrDg = dTgtThrDg;
		}
	}
	
	return 1;
}


//**************************************************************************************************//
//                    在另外一个vector中找到与当前数据同航迹号的数据                                //    
//                    在另外一个vector中找到当前数据的前一时刻的数据                                //
//    输入：航迹号lAutonum，前一时刻的数据ForeData                                                  //
//    输出：                                                                                        //
//    返回值：指向前一时刻数据的迭代器,没有找到返回ForeData.end()                                   //
//**************************************************************************************************//

VCT_Cooperative_FUSIDENTIINFOR::iterator CAlgorithm::FindSameData(unsigned long lAutonum, VCT_Cooperative_FUSIDENTIINFOR& ForeData)
{
	VCT_Cooperative_FUSIDENTIINFOR::iterator iteFore;
	for (iteFore = ForeData.begin(); iteFore != ForeData.end(); ++iteFore)
	{
		if (lAutonum == iteFore->stFusTrack.lAutonum)
		{
			return iteFore;
		}
	}
	return iteFore;
}

//**************************************************************************************************//
//                    在另外一个vector中找到与当前数据同航迹号的数据                                //    
//                    在另外一个vector中找到当前数据的前一时刻的数据                                //
//    输入：ESM批号lAutonum，前一时刻的数据vctFusEsm                                                //
//    输出：                                                                                        //
//    返回值：指向前一时刻数据的迭代器,没有找到返回vctFusEsm.end()                                   //
//**************************************************************************************************//

VCT_ESM_MSG::iterator CAlgorithm::ESMFindSameData(unsigned long lAutonum, VCT_ESM_MSG& vctFusEsm)
{
	VCT_ESM_MSG::iterator iteFore;
	for (iteFore = vctFusEsm.begin(); iteFore != vctFusEsm.end(); ++iteFore)
	{
		if (lAutonum == iteFore->lAutonum)
		{
			return iteFore;
		}
	}
	return iteFore;
}

//**************************************************************************************************//
//                    在另外一个vector中找到与当前数据同航迹号的数据                                //    
//                    在另外一个vector中找到当前数据的前一时刻的数据                                //
//    输入：COM批号lAutonum，前一时刻的数据vctFusCom                                                //
//    输出：                                                                                        //
//    返回值：指向前一时刻数据的迭代器,没有找到返回vctFusCom.end()                                   //
//**************************************************************************************************//

VCT_COMM_MSG::iterator CAlgorithm::COMFindSameData(unsigned long lAutonum, VCT_COMM_MSG& vctFusCom)
{
	VCT_COMM_MSG::iterator iteFore;
	for (iteFore = vctFusCom.begin(); iteFore != vctFusCom.end(); ++iteFore)
	{
		if (lAutonum == iteFore->lAutonum)
		{
			return iteFore;
		}
	}
	return iteFore;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                           航迹推理
//                                   知识库的基本事件层的设计格式
/////////////////////////////////////////航迹部分////////////////////////////////////////////////////////
//     径距      高度          速度         加速度        航向          //    基本运动态势（推理）
//                                                                      //
//                                                                      //
//基本态势：1：匀速直线运动、2：加速直线运行、3：俯冲、4、上升、5、拐弯、6：远离本舰、7：逼近本舰、
//          8：位置固定、9：新目标(此项不放知识库中)、10：目标消失(此项不放知识库中),11：不明(此项不放知识库中)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CAlgorithm::KnowLege_Database_Track_EventReason(VCT_INT& vctTrackEvent, int& nModelID, int& nEventType)
{   
	int i(0);
	int nPosition(-1);              //模板号所在的下标
	int nMax;                   //统计最大值
//	int nEvtID;                 //从数据库读取的事件号，要更改？？？？？？
	int nSum;
	VV_INT::iterator ite_vDb;
	VCT_INT::iterator itedbevt;
	VCT_INT::iterator iteevt;
	VCT_INT::iterator iteSun;
	VCT_INT vctDbTrackEvt;      //存放数据库中航迹事件的各个变量值
	VCT_INT vctEvtID;           //存放基本事件类型，读数据库时已存好目前有10类
	VCT_INT vctModelID;         //存放模板号
	VCT_INT vctSun;             //推理累加值
	vctDbTrackEvt.clear();
	vctEvtID.clear();
	vctModelID.clear();
	vctSun.clear();
	for (ite_vDb = theApp.m_DataBase.m_DataBaseData.vctDbTrackKng.begin(); ite_vDb != theApp.m_DataBase.m_DataBaseData.vctDbTrackKng.end(); ++ite_vDb)    //循环读取数据库中的每一条知识
	{		
		//计算当前航迹事件和从数据库中取出的事件的匹配值
		nSum = 0;
		for (itedbevt = ite_vDb->begin(), iteevt = vctTrackEvent.begin(); iteevt != vctTrackEvent.end(); ++iteevt, ++itedbevt)
		{
			if (*itedbevt == *iteevt)
			{
				nSum = nSum + 1;
			} 
			else
			{
				nSum = nSum - 1;
			}
			vctSun.push_back(nSum);
		}
	}
	//取所有匹配值里面最大的一个作为航迹事件
	nMax = vctSun.at(0);
	for (iteSun = vctSun.begin(); iteSun != vctSun.end(); ++iteSun)
	{
		if (nMax < *iteSun)
		{
			nMax = *iteSun;
			nPosition = i;
		}
		else
		{
			
		}
		++i;
	}
	if (nPosition > -1)  //说明找到
	{
		//取出nPosition对应的知识库中的基本事件，并用黑板基本事件结构带回,作为"黑板信息"(注：黑板上的信息用于界面显示和输出)
		nModelID = vctModelID.at(nPosition);
		nEventType = vctEvtID.at(nPosition);
	}
	else     //没有找到
	{
		nModelID = -1;
		nEventType = 11;
	}
}

void CAlgorithm::KnowLege_Database_ESM_EventReason(VCT_INT& vctTrackEvent, int& nModelID, int& nEventType)
{
	int i(0);
	int nPosition(-1);              //模板号所在的下标
	int nMax;                   //统计最大值
//	int nEvtID;                 //从数据库读取的事件号，要更改？？？？？？
	int nSum;
	VV_INT::iterator ite_vDb;
	VCT_INT::iterator itedbevt;
	VCT_INT::iterator iteevt;
	VCT_INT::iterator iteSun;
	VCT_INT vctDbTrackEvt;      //存放数据库中航迹事件的各个变量值
	VCT_INT vctEvtID;           //存放基本事件类型，读数据库时已存好目前有?类
	VCT_INT vctModelID;         //存放模板号
	VCT_INT vctSun;             //推理累加值
	vctDbTrackEvt.clear();
	vctEvtID.clear();
	vctModelID.clear();
	vctSun.clear();
	//计算当前ESM事件和从数据库中取出的事件的匹配值
	for (ite_vDb = theApp.m_DataBase.m_DataBaseData.vctDbESMKng.begin(); ite_vDb != theApp.m_DataBase.m_DataBaseData.vctDbESMKng.end(); ++ite_vDb)
	{
		nSum = 0;
		for (itedbevt = ite_vDb->begin(), iteevt = vctTrackEvent.begin(); iteevt != vctTrackEvent.end(); ++iteevt, ++itedbevt)
		{
			if (*itedbevt == *iteevt)
			{
				nSum = nSum + 1;
			} 
			else
			{
				nSum = nSum - 1;
			}
			vctSun.push_back(nSum);
		}
	}
	//取所有匹配值里面最大的一个作为ESM事件
	nMax = vctSun.at(0);
	for (iteSun = vctSun.begin(); iteSun != vctSun.end(); ++iteSun)
	{
		if (nMax < *iteSun)
		{
			nMax = *iteSun;
			nPosition = i;
		}
		else
		{
			
		}
		++i;
	}
	if (nPosition > -1)  //说明找到
	{
		//取出nPosition对应的知识库中的基本事件，并用黑板基本事件结构带回,作为"黑板信息"(注：黑板上的信息用于界面显示和输出)
		nModelID = vctModelID.at(nPosition);
		nEventType = vctEvtID.at(nPosition);
	}
	else     //否则，说明推理无效,默认基本事件"不明",没有模板号
	{
		nModelID = -1;
		nEventType = 7;
	}
}


void CAlgorithm::KnowLege_Database_COM_EventReason(VCT_INT& vctTrackEvent, int& nModelID, int& nEventType)
{
	int i(0);
	int nPosition(-1);              //模板号所在的下标
	int nMax;                   //统计最大值
//	int nEvtID;                 //从数据库读取的事件号，要更改？？？？？？
	int nSum;
	VV_INT::iterator ite_vDb;
	VCT_INT::iterator itedbevt;
	VCT_INT::iterator iteevt;
	VCT_INT::iterator iteSun;
	VCT_INT vctDbTrackEvt;      //存放数据库中航迹事件的各个变量值
	VCT_INT vctEvtID;           //存放基本事件类型，读数据库时已存好目前有?类
	VCT_INT vctModelID;         //存放模板号
	VCT_INT vctSun;             //推理累加值
	vctDbTrackEvt.clear();
	vctEvtID.clear();
	vctModelID.clear();
	vctSun.clear();
	for (ite_vDb = theApp.m_DataBase.m_DataBaseData.vctDbCOMKng.begin(); ite_vDb != theApp.m_DataBase.m_DataBaseData.vctDbCOMKng.end(); ++ite_vDb)
	{
		//计算当前COM事件和从数据库中取出的事件的匹配值
		nSum = 0;
		for (itedbevt = ite_vDb->begin(), iteevt = vctTrackEvent.begin(); iteevt != vctTrackEvent.end(); ++iteevt, ++itedbevt)
		{
			if (*itedbevt == *iteevt)
			{
				nSum = nSum + 1;
			} 
			else
			{
				nSum = nSum - 1;
			}
			vctSun.push_back(nSum);
		}
	}
	//取所有匹配值里面最大的一个作为COM事件
	nMax = vctSun.at(0);
	for (iteSun = vctSun.begin(); iteSun != vctSun.end(); ++iteSun)
	{
		if (nMax < *iteSun)
		{
			nMax = *iteSun;
			nPosition = i;
		}
		else
		{
			
		}
		++i;
	}
	if (nPosition > -1)  //说明找到
	{
		//取出nPosition对应的知识库中的基本事件，并用黑板基本事件结构带回,作为"黑板信息"(注：黑板上的信息用于界面显示和输出)
		nModelID = vctModelID.at(nPosition);
		nEventType = vctEvtID.at(nPosition);
	}
	else     //否则，说明推理无效,默认基本事件"不明",没有模板号
	{
		nModelID = -1;
		nEventType = 7;
	}	
}

//******************************************************************************************//
//                          特征变化监听模块(含特征层推理)                                  //
//********                    2014-08-03 Liuyian                            ****************//
//********  输入：                                                          ****************//
//********        本次目标信息(含速度、加速度、威胁度)      ****************//
//********        上次目标信息(含速度、加速度、威胁度)            **********//
//********  输出：状态变化（属刺激模块的监听）                                         *****//
//******************************************************************************************//
void CAlgorithm::CharacterChangeJudge(VCT_Cooperative_FUSIDENTIINFOR& ForeData, VCT_Cooperative_FUSIDENTIINFOR& NowData) 
{
	int nModelID(0);
	int nEventType(0);
	VCT_DOUBLE stNowChange;        //前后两次的差值，顺序按照TRACK_THRESHOLD中排列的顺序
	VCT_INT vctTrackEvent;         //顺序存放事件，顺序按照TRACK_THRESHOLD中排列的顺序
	VCT_INT::iterator iteint;
	VCT_DOUBLE::iterator itedou;
	VCT_ESM_MSG::iterator iteESMFore;
	VCT_ESM_MSG::iterator iteESMNow;
	VCT_COMM_MSG::iterator iteCOMFore;
	VCT_COMM_MSG::iterator iteCOMNow;
	VCT_Cooperative_FUSIDENTIINFOR::iterator iteNOw;
	VCT_Cooperative_FUSIDENTIINFOR::iterator iteFore;
	//读取数据库，保存阈值信息

	//统一处理有编批和无编批的数据
	for (iteNOw = NowData.begin(); iteNOw != NowData.end(); ++iteNOw)
	{
		iteNOw->stFusTrack.dHeight = iteNOw->stFusTrack.dRange * sin(PI_4*iteNOw->stFusTrack.dElevationAngle/180);
		if (iteNOw->stFusTrack.lAutonum < 3000)    //只有航迹信息（不含ESM和COM信息）的目标特征信息变化
		{
			iteFore = FindSameData(iteNOw->stFusTrack.lAutonum, ForeData);
			if (iteFore != ForeData.end())              //找到同一批号的数据
			{
				iteFore->stFusTrack.dHeight = iteFore->stFusTrack.dRange * sin(PI_4 * iteFore->stFusTrack.dElevationAngle/180);
				stNowChange.clear();
				//前后两个时刻的差值
				stNowChange.push_back(iteNOw->stFusTrack.dRange - iteFore->stFusTrack.dRange);
				stNowChange.push_back(iteNOw->stFusTrack.dHeight - iteFore->stFusTrack.dHeight);
				stNowChange.push_back(iteNOw->stFusTrack.dVSpeed - iteFore->stFusTrack.dVSpeed);
				stNowChange.push_back(iteNOw->stFusTrack.dAddSpeed - iteFore->stFusTrack.dAddSpeed);
				stNowChange.push_back(iteNOw->stFusTrack.dAzimuth - iteFore->stFusTrack.dAzimuth);
				vctTrackEvent.clear();
				//根据阈值判断目标状态
				for (itedou = stNowChange.begin(), iteint = theApp.m_DataBase.m_DataBaseData.TrackThd.begin(); itedou != stNowChange.end(), iteint != theApp.m_DataBase.m_DataBaseData.TrackThd.end(); ++itedou, ++iteint)
				{
					//这里面TrackThd存放的是从数据库读取的阈值信息
					if (fabs(*itedou) <= *iteint)
					{
						vctTrackEvent.push_back(1);
					}
					else if (*itedou < (0 - *iteint))
					{
						vctTrackEvent.push_back(5);
					}
					else
					{
						vctTrackEvent.push_back(3);
					}
				}
				//调用航迹基本事件推理
				KnowLege_Database_Track_EventReason(vctTrackEvent, nModelID, nEventType);
				iteNOw->stFusTrack.nTrackEvent = nEventType;
				iteNOw->stFusTrack.nModel = nModelID;
				iteNOw->stFusTrack.nRdChEvt = vctTrackEvent.at(0);
				iteNOw->stFusTrack.nHtChEvt = vctTrackEvent.at(1);	
				iteNOw->stFusTrack.nVSChEvt = vctTrackEvent.at(2);
				iteNOw->stFusTrack.nAddVSChEvt = vctTrackEvent.at(3);
				iteNOw->stFusTrack.nCuChEvt = vctTrackEvent.at(4);
			} 
			else                                  //没有找到同一批号的数据
			{
			}
		}
		else if (iteNOw->stFusTrack.lAutonum >= 8000) //有航迹，ESM,COM信息目标航迹特征变化
		{
			iteFore = FindSameData(iteNOw->stFusTrack.lAutonum, ForeData);
			stNowChange.clear();
			//前后两个时刻的差值
			stNowChange.push_back(iteNOw->stFusTrack.dRange - iteFore->stFusTrack.dRange);
			stNowChange.push_back(iteNOw->stFusTrack.dHeight - iteFore->stFusTrack.dHeight);
			stNowChange.push_back(iteNOw->stFusTrack.dVSpeed - iteFore->stFusTrack.dVSpeed);
			stNowChange.push_back(iteNOw->stFusTrack.dAddSpeed - iteFore->stFusTrack.dAddSpeed);
			stNowChange.push_back(iteNOw->stFusTrack.dAzimuth - iteFore->stFusTrack.dAzimuth);
			vctTrackEvent.clear();
			//根据阈值判断目标状态,保证stNowChange中数据的顺序和TrackThd中的数据顺序一致
			for (itedou = stNowChange.begin(), iteint = theApp.m_DataBase.m_DataBaseData.TrackThd.begin(); itedou != stNowChange.end(), iteint != theApp.m_DataBase.m_DataBaseData.TrackThd.end(); ++itedou, ++iteint)
			{
				if (fabs(*itedou) <= *iteint)
				{
					vctTrackEvent.push_back(1);
				}
				else if (*itedou < (0 - *iteint))
				{
					vctTrackEvent.push_back(5);
				}
				else
				{
					vctTrackEvent.push_back(3);
				}
			}
			//调用航迹基本事件推理
			KnowLege_Database_Track_EventReason(vctTrackEvent, nModelID, nEventType);
			iteNOw->stFusTrack.nTrackEvent = nEventType;
			iteNOw->stFusTrack.nModel = nModelID;
			iteNOw->stFusTrack.nRdChEvt = vctTrackEvent.at(0);
			iteNOw->stFusTrack.nHtChEvt = vctTrackEvent.at(1);
			iteNOw->stFusTrack.nVSChEvt = vctTrackEvent.at(2);
			iteNOw->stFusTrack.nAddVSChEvt = vctTrackEvent.at(3);
			iteNOw->stFusTrack.nCuChEvt = vctTrackEvent.at(4);
			// 再计算捆邦在该i目标上的ESM特征变化与推理
			for (iteESMNow = iteNOw->vctFusEsm.begin(); iteESMNow != iteNOw->vctFusEsm.end(); ++iteESMNow)
			{
				iteESMFore = ESMFindSameData(iteESMNow->lAutonum, iteFore->vctFusEsm);
				if (iteESMFore != iteFore->vctFusEsm.end())
				{
					stNowChange.clear();
					stNowChange.push_back(iteESMNow->dMaiChongFeature - iteESMFore->dMaiChongFeature);
					stNowChange.push_back(iteESMNow->dPulseExtent - iteESMFore->dPulseExtent);
					stNowChange.push_back(iteESMNow->dMaiKuan - iteESMFore->dMaiKuan);
					stNowChange.push_back(iteESMNow->dChongPin - iteESMFore->dChongPin);
					stNowChange.push_back(iteESMNow->dTianXianScan - iteESMFore->dTianXianScan);
					vctTrackEvent.clear();
					//根据阈值判断目标状态，保证stNowChange中数据的顺序和ESMThd中的数据顺序一致,ESMThd表示从数据库中读取的ESM的阈值信息
					for (itedou = stNowChange.begin(), iteint = theApp.m_DataBase.m_DataBaseData.ESMThd.begin(); itedou != stNowChange.end(); ++itedou, ++iteint)
					{
						if (fabs(*itedou) <= *iteint)
						{
							vctTrackEvent.push_back(1);
						}
						else if (*itedou < (0 - *iteint))
						{
							vctTrackEvent.push_back(5);
						}
						else
						{
							vctTrackEvent.push_back(3);
						}
					}
					 //调用ESM基本事件推理模块
					KnowLege_Database_ESM_EventReason(vctTrackEvent, nModelID, nEventType);
					iteESMNow->nModel = nModelID;
					iteESMNow->nESMEvt = nEventType;
				}
			}
			// 再计算捆邦在该i目标上的ESM特征变化与推理
			for (iteCOMNow = iteNOw->vctFusCom.begin(); iteCOMNow != iteNOw->vctFusCom.end(); ++iteNOw)
			{
				iteCOMFore = COMFindSameData(iteCOMNow->lAutonum, iteFore->vctFusCom);
				if (iteCOMFore != iteFore->vctFusCom.end())
				{
					stNowChange.clear();
					stNowChange.push_back(iteCOMNow->dComFre - iteCOMFore->dComFre);
					stNowChange.push_back(iteCOMNow->dPulseExtent - iteCOMFore->dPulseExtent);
					stNowChange.push_back(iteCOMNow->dComJPN - iteCOMFore->dComJPN);
					vctTrackEvent.clear();
					//根据阈值判断目标状态，保证stNowChange中数据的顺序和ESMThd中的数据顺序一致,ESMThd表示从数据库中读取的ESM的阈值信息
					for (itedou = stNowChange.begin(), iteint = theApp.m_DataBase.m_DataBaseData.COMThd.begin(); itedou != stNowChange.end(); ++itedou, ++iteint)
					{
						if (fabs(*itedou) <= *iteint)
						{
							vctTrackEvent.push_back(1);
						}
						else if (*itedou < (0 - *iteint))
						{
							vctTrackEvent.push_back(5);
						}
						else
						{
							vctTrackEvent.push_back(3);
						}
					}
					//调用ESM基本事件推理模块
					KnowLege_Database_COM_EventReason(vctTrackEvent, nModelID, nEventType);
					iteCOMNow->nModel = nModelID;
					iteCOMNow->nCOMEvt = nEventType;
				}
			}
		}
		else
		{
			//只有ESM或COM信息，不应该出现此情况
		}
	}
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
//***********            基本事件链表与黑板节点创建设计模块                                        *****//
//********                    (2014-18-17  Liuyian)                                           **********//
//********     输入：本次融合的类数据（含目标的有批、无批）                                   **********//
//********     输出：带回触发是否进入下一层推理标志：0不向下层运行；1继续下层推理             **********//
void CAlgorithm::Basic_Event_First_LinKJudge_Process_Modul(VCT_Cooperative_FUSIDENTIINFOR& NowData, int& nTriggleFlag)             //(首次建立)
{
	int nNowCount(0);          //当前循环次数
	VCT_Cooperative_FUSIDENTIINFOR::iterator iteNowData;
	VCT_COMM_MSG::iterator iteCOM;
	VCT_ESM_MSG::iterator iteESM;
	EVENTLINKS TemData;
	EVENTBLACK BlackTemData;
	for (iteNowData = NowData.begin(); iteNowData != NowData.end(); ++iteNowData)
	{
		//将数据写入事件列表
		TemData.vctCOMBasicSituation.clear();
		TemData.vctCOMHao.clear();
		TemData.vctCOMMBHao.clear();
		TemData.vctESMBasicSituation.clear();
		TemData.vctESMCumulativeN.clear();
		TemData.vctESMHao.clear();
		TemData.vctESMMBHao.clear();
		TemData.dThreatDegree = iteNowData->stFusTrack.dThrDg;
		TemData.nCOMCount = iteNowData->vctFusCom.size();
		TemData.nESMCount = iteNowData->vctFusEsm.size();
		TemData.nSerialnum = nNowCount;
		TemData.nTrackBasicSituation = 0;        
		TemData.nTrackCumulativeN = 1;
		TemData.nTrackHao = iteNowData->stFusTrack.lAutonum;
		TemData.nTrackMBHao = iteNowData->stFusTrack.nModel;
		TemData.nTrackType = 0;
		for (iteCOM = iteNowData->vctFusCom.begin(); iteCOM != iteNowData->vctFusCom.end(); ++iteCOM)
		{
			TemData.vctCOMBasicSituation.push_back(iteCOM->nCOMEvt);
			TemData.vctCOMHao.push_back(iteCOM->lAutonum);
			TemData.vctCOMMBHao.push_back(iteCOM->nModel);
		}
		for (iteESM = iteNowData->vctFusEsm.begin(); iteESM != iteNowData->vctFusEsm.end(); ++iteESM)
		{
			TemData.vctESMBasicSituation.push_back(iteESM->nESMEvt);
			TemData.vctESMHao.push_back(iteESM->lAutonum);
			TemData.vctESMMBHao.push_back(iteESM->nModel);
		}
		m_mapBasicEvent.insert(make_pair(iteNowData->stFusTrack.lAutonum, TemData));

		//将数据写入到黑板中
		BlackTemData.vctCOMEvent.clear();
		BlackTemData.vctCOMHao.clear();
		BlackTemData.vctESMEvent.clear();
		BlackTemData.vctESMHao.clear();
		BlackTemData.vctEventValue.clear();
		BlackTemData.dAddSpeed = iteNowData->stFusTrack.dAddSpeed;
		BlackTemData.dAz = iteNowData->stFusTrack.dAzimuth;
		BlackTemData.dAzimuth = iteNowData->stFusTrack.dCourse;
		BlackTemData.dEz = iteNowData->stFusTrack.dElevationAngle;
		BlackTemData.dHigh = iteNowData->stFusTrack.dHeight;
		BlackTemData.dRd = iteNowData->stFusTrack.dRange;
		BlackTemData.dSpeed = iteNowData->stFusTrack.dVSpeed;
		BlackTemData.dThreatDegree = iteNowData->stFusTrack.dThrDg;
		BlackTemData.lTimeStamp = iteNowData->lStampTime;
		BlackTemData.nCOMCount = iteNowData->vctFusCom.size();
		BlackTemData.nESMCount = iteNowData->vctFusEsm.size();
		BlackTemData.nSeriaN = nNowCount;
		BlackTemData.nTrackEvent = iteNowData->stFusTrack.nTrackEvent;
		BlackTemData.nTrackHao = iteNowData->stFusTrack.lAutonum;
		BlackTemData.nTrackType = iteNowData->stFusTrack.nTgtType;
		for (iteCOM = iteNowData->vctFusCom.begin(); iteCOM != iteNowData->vctFusCom.end(); ++iteCOM)
		{
			BlackTemData.vctCOMEvent.push_back(iteCOM->nCOMEvt);
			BlackTemData.vctCOMHao.push_back(iteCOM->lAutonum);
			//上面循环中未见模板号，是否有问题？
		}
		for (iteESM = iteNowData->vctFusEsm.begin(); iteESM != iteNowData->vctFusEsm.end(); ++iteESM)
		{
			BlackTemData.vctESMEvent.push_back(iteESM->nESMEvt);
			BlackTemData.vctESMHao.push_back(iteESM->lAutonum);
		}
		
		BlackTemData.vctEventValue.push_back(iteNowData->stFusTrack.nHtChEvt);
		BlackTemData.vctEventValue.push_back(iteNowData->stFusTrack.nVSChEvt);
		BlackTemData.vctEventValue.push_back(iteNowData->stFusTrack.nAddVSChEvt);
		BlackTemData.vctEventValue.push_back(iteNowData->stFusTrack.nRdChEvt);
		BlackTemData.vctEventValue.push_back(iteNowData->stFusTrack.nCuChEvt);
		theApp.m_mapEventBlack.insert(make_pair(iteNowData->stFusTrack.lAutonum, BlackTemData));

		++nNowCount;
		
	}
	nTriggleFlag = 1;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//***********            基本事件链表与黑板节点创建设计模块                                        *****//
//********                    (2014-18-17  Liuyian)                                           **********//
//********     输入：本次融合的类数据（含目标的有批、无批）                                   **********//
//********     输出：带回触发是否进入下一层推理标志：0不向下层运行；1继续下层推理             **********//
void CAlgorithm::Basic_Event_NonFirst_LinKJudge_Process_Modul(VCT_Cooperative_FUSIDENTIINFOR& NowData, int& nTriggleFlag)             //(非首次)
{
	int nCount(0);
	VCT_INT vctESMFlag;                             //标记新开机的ESM
	VCT_INT vctESMCloseFlag;                        //标记雷达关机
	VCT_INT vctCOMOpenFlag;                         //标记COM开机信息
	VCT_INT vctCOMCloseFlag;                        //标记COM关机信息
	VCT_ESM_MSG::iterator iteESM;
	VCT_INT::iterator iteESMLink;
	VCT_COMM_MSG::iterator iteCOM;
	VCT_INT::iterator iteCOMLink;
	VCT_Cooperative_FUSIDENTIINFOR::iterator iteNowData;
	MAP_BASIC_EVENT::iterator iteBasicEvt;
	MAP_EVENT_BLACK::iterator iteBlack;
	for (iteNowData = NowData.begin(); iteNowData != NowData.end(); ++iteNowData)
	{
		iteBasicEvt = m_mapBasicEvent.find(iteNowData->stFusTrack.lAutonum);       //在链表中找到该目标前一时刻对应的状态
		if (iteBasicEvt != m_mapBasicEvent.end())  //找到
		{
			if (iteNowData->stFusTrack.nModel == iteBasicEvt->second.nTrackMBHao)
			{
				++iteBasicEvt->second.nTrackCumulativeN;                 //累加
				if (iteBasicEvt->second.nTrackCumulativeN >= 5)          //超过阈值
				{
					iteBlack = theApp.m_mapEventBlack.find(iteNowData->stFusTrack.lAutonum);
					iteBlack->second.nTrackHao = iteNowData->stFusTrack.lAutonum;     //航迹号
					iteBlack->second.lTimeStamp = iteNowData->lStampTime;             //时间戳
					iteBlack->second.dAddSpeed = iteNowData->stFusTrack.dAddSpeed;    //加速度
					iteBlack->second.dRd = iteNowData->stFusTrack.dRange;             //径距
					iteBlack->second.dAz = iteNowData->stFusTrack.dAzimuth;           //方位
					iteBlack->second.dEz = iteNowData->stFusTrack.dElevationAngle;    //仰角
					iteBlack->second.dHigh = iteNowData->stFusTrack.dHeight;          //高度
					iteBlack->second.dSpeed = iteNowData->stFusTrack.dVSpeed;         //速度
					iteBlack->second.dAzimuth = iteNowData->stFusTrack.dCourse;       //航向
					iteBlack->second.nTrackEvent = iteNowData->stFusTrack.nTrackEvent;//基本事件
					iteBlack->second.vctEventValue.push_back(iteNowData->stFusTrack.nHtChEvt);   //高度推理
					iteBlack->second.vctEventValue.push_back(iteNowData->stFusTrack.nVSChEvt);   //速度推理
					iteBlack->second.vctEventValue.push_back(iteNowData->stFusTrack.nAddVSChEvt);//加速度推理
					iteBlack->second.vctEventValue.push_back(iteNowData->stFusTrack.nRdChEvt);   //径距推理
					iteBlack->second.vctEventValue.push_back(iteNowData->stFusTrack.nCuChEvt);   //航向推理
					iteBlack->second.dThreatDegree = iteNowData->stFusTrack.dThrDg;           //平台威胁度
					iteBlack->second.nTrackType = iteNowData->stFusTrack.nTgtType;            //平台事件类型
					//再处理捆邦的ESM,可能有消失的雷达，也可能有新开的雷达
					vctESMFlag.clear();
					vctESMCloseFlag.clear();
					//vctESMFlag统一置0，表示当时刻全部为新开机的雷达
					for (int i = 0; i < iteNowData->vctFusEsm.size(); ++i)
					{
						vctESMFlag.push_back(0);
					}
					//vctESMCloseFlag统一置0，表示上一时刻链表中的ESM全部关机，当查找到的时候置1，表示开机状态一直保持
					for (i = 0; i < iteBasicEvt->second.vctESMHao.size(); ++i)
					{
						vctESMCloseFlag.push_back(0);
					}
					for (iteESM = iteNowData->vctFusEsm.begin(); iteESM != iteNowData->vctFusEsm.end(); ++iteESM)             //遍历所有ESM
					{
						nCount = 0;
						for (iteESMLink = iteBasicEvt->second.vctESMHao.begin(); iteESMLink != iteBasicEvt->second.vctESMHao.end(); ++iteESMLink)
						{
							if (*iteESMLink == iteESM->lAutonum)   //ESM号一样
							{
								//找到，不是新开机雷达
								vctESMFlag.at(nCount) = 1;
								vctESMCloseFlag.at(nCount) = 1;
								if (iteESM->nModel == iteBasicEvt->second.vctESMMBHao.at(nCount))
								{
									//模板号一样，不做处理
								} 
								else
								{
									//模板号不一样，表示状态发生改变
									//注：ESM不要累加，其没有缓慢变化过程，与航迹不同
									//更新事件列表的数据
									iteBasicEvt->second.vctESMMBHao.at(nCount) = iteESM->nModel;
									iteBasicEvt->second.vctESMBasicSituation.at(nCount) = iteESM->nESMEvt;
									//更新黑板数据
									iteBlack->second.vctESMHao.at(nCount) = iteESM->lAutonum;
									iteBlack->second.vctESMEvent.at(nCount) = iteESM->nESMEvt;
								}
									
							}  //没找到，不做处理，继续找
							else          
							{
								
							}
							++nCount;
						}
					}
					i = 0;   //表示循环次数
					for (iteESM = iteNowData->vctFusEsm.begin(); iteESM != iteNowData->vctFusEsm.end(); ++iteESM)
					{
						//ESM号新出现，表示新开机的ESM，将其下标号添加到未处理的vector中
						if (vctESMFlag.at(i) == 0)   
						{
							iteBasicEvt->second.vctESMHao.push_back(iteESM->lAutonum);
							iteBasicEvt->second.vctESMMBHao.push_back(iteESM->nModel);
							iteBasicEvt->second.vctESMBasicSituation.push_back(iteESM->nESMEvt);
							iteBasicEvt->second.nESMCount++;
						}
						++i;
					}
					i = 0;
					for (iteESMLink = iteBasicEvt->second.vctESMHao.begin(); iteESMLink != iteBasicEvt->second.vctESMHao.end(); ++iteESMLink)
					{
						//处理关机的情况
						if (vctESMCloseFlag.at(i) == 0)
						{
							iteBlack->second.vctESMEvent.at(i) = 1;                 //ESM基本事件：关机
						}
						++i;
					}
					//再处理ESM消失，即关机的链表中的ESM

					//事件链表中去除消失的ESM


					//再处理COM
					//再处理捆邦的COM,可能有消失的雷达，也可能有新开的通信雷达
					vctCOMOpenFlag.clear();
					vctCOMCloseFlag.clear();
					//vctCOMOpenFlag统一置0，表示当时刻全部为新开机的雷达
					for (i = 0; i < iteNowData->vctFusCom.size(); ++i)
					{
						vctCOMOpenFlag.push_back(0);
					}
					//vctESMCloseFlag统一置0，表示上一时刻链表中的COM全部关机，当查找到的时候置1，表示开机状态一直保持
					for (i = 0; i < iteBasicEvt->second.vctCOMHao.size(); ++i)
					{
						vctCOMCloseFlag.push_back(0);
					}
					for (iteCOM = iteNowData->vctFusCom.begin(); iteCOM != iteNowData->vctFusCom.end(); ++iteCOM)             //遍历所有ESM
					{
						nCount = 0;
						for (iteCOMLink = iteBasicEvt->second.vctCOMHao.begin(); iteCOMLink != iteBasicEvt->second.vctCOMHao.end(); ++iteCOMLink)
						{
							if (*iteCOMLink == iteCOM->lAutonum)   //COM号一样
							{
								//找到，不是新开机雷达
								vctCOMOpenFlag.at(nCount) = 1;
								vctCOMCloseFlag.at(nCount) = 1;
								if (iteCOM->nModel == iteBasicEvt->second.vctCOMMBHao.at(nCount))
								{
									//模板号一样，不做处理
								} 
								else
								{
									//模板号不一样，表示状态发生改变
									//注：COM不要累加，其没有缓慢变化过程，与航迹不同
									//更新事件列表的数据
									iteBasicEvt->second.vctCOMHao.at(nCount) = iteCOM->nModel;
									iteBasicEvt->second.vctCOMBasicSituation.at(nCount) = iteCOM->nCOMEvt;
									//更新黑板数据
									iteBlack->second.vctCOMHao.at(nCount) = iteCOM->lAutonum;
									iteBlack->second.vctCOMEvent.at(nCount) = iteCOM->nCOMEvt;
								}
								
							}  //没找到，不做处理，继续找
							else          
							{
								
							}
							++nCount;
						}
					}
					i = 0;   //表示循环次数
					for (iteCOM = iteNowData->vctFusCom.begin(); iteCOM != iteNowData->vctFusCom.end(); ++iteCOM)
					{
						//COM号新出现，表示新开机的COM，将其下标号添加到未处理的vector中
						if (vctESMFlag.at(i) == 0)   
						{
							iteBasicEvt->second.vctCOMHao.push_back(iteCOM->lAutonum);
							iteBasicEvt->second.vctCOMMBHao.push_back(iteCOM->nModel);
							iteBasicEvt->second.vctCOMBasicSituation.push_back(iteCOM->nCOMEvt);
							iteBasicEvt->second.nCOMCount++;
						}
						++i;
					}
					i = 0;
					for (iteCOMLink = iteBasicEvt->second.vctCOMHao.begin(); iteCOMLink != iteBasicEvt->second.vctCOMHao.end(); ++iteESMLink)
					{
						//处理关机的情况
						if (vctCOMCloseFlag.at(i) == 0)
						{
							iteBlack->second.vctCOMEvent.at(i) = 1;                 //COM基本事件：关机
						}
						++i;
					}
					//再处理COM消失，即关机的链表中的COM
					
					//事件链表中去除消失的COM


				}
			}
			//批号相同，模板号不一样，说明是新事件
			else
			{
				//1 先修改链表,只做简单处理

				//同时，替换其上的ESM和COM
				//ESM

				//COM


				//2 再产生黑板结构数据
			}
		}
		else                             //未找到，该目标为新出现的目标
		{
			//1.增加链表节点

			//2.更新黑板节点数据

			//3.增加黑板节点
		}
	}
}

//事件层的全部处理过程
void CAlgorithm::Basic_Event(VCT_Cooperative_FUSIDENTIINFOR& NowFusData, int& nTriggleFlag)
{
	BufferData(m_ForeData, m_NowData, NowFusData);	
	CalculateSpeed(m_NowData);
	CalculateAddSpeed(m_ForeData, m_NowData);
	ThreatDegree(m_NowData);
	CharacterChangeJudge(m_ForeData, m_NowData);
	if (m_mapBasicEvent.empty() && theApp.m_mapEventBlack.empty())
	{
		Basic_Event_First_LinKJudge_Process_Modul(m_NowData, nTriggleFlag);
	} 
	else
	{
		Basic_Event_NonFirst_LinKJudge_Process_Modul(m_NowData, nTriggleFlag);
	}
}


///////////////////////////////////////平台层//////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////
//***********              平台态势企图知识推理设计模块           ****************//
//********                    (2014-07-31  Liuyian)                     **********//
//********     输入：黑板上基本事件层结构数据                           **********//
//********           本舰航向:Azimuth                                   **********//
//******             态势层知识库记录个数  KnowlegeSituN                **********//
//******             是否第一次调用该函数，nFlag为1表示是，否则为0      **********//
//******             平台基本态势层知识库                               **********//
//********    输出：首次：创建平台态势链表节点和黑板的平台态势层        **********//
//********　        非首次产生待更新的链表数据 m_List_temp                  ******//
////////////////////////////////////////////////////////////////////////////////////
void CAlgorithm::Plat_KnowLedge_Basic_Situation_Reason_Modil(MAP_EVENT_BLACK& m_EventBlack,double& Azimuth,int nFlag, int& nBack, MAP_PLAT_LINK& m_List_temp) 
{
	int i;
	int nAzEvent;        //航向事件
	int nMax;  
	int nFindFlag;       //找到标志,0表示找到，1表示未找到
	int nFindPos;        //找到的最大值所在的位置
	int nsum;
	int nESMHao;
	int nESMEvent;
	int nCOMHao;
	int nCOMEvent;
	int nCount(0);
	double dAzcr;       //航向角差值
	VCT_INT vctSunCorr;  //所有匹配度，从中取最大的一个
	VCT_INT vctTemp;
	MAP_EVENT_BLACK::iterator iteBlack;
	VV_INT::iterator iteDbKng;
	VCT_INT::iterator iteSigKng;
	VCT_INT::iterator iteTemp;
	PLATEVENT PlatListTemp;
	PLATBLACK PlatBlackTemp;
	//遍历事件黑板中的所有节点，分别进行处理
	for (iteBlack = m_EventBlack.begin(); iteBlack != m_EventBlack.end(); ++iteBlack)
	{
		//读取原值，存储
		

		//计算航向，判断目标的运动状态，偏离本舰判断:1--朝向本舰、3--靠近、5--远离
		vctTemp.clear();
		vctTemp.assign(iteBlack->second.vctEventValue.begin(),iteBlack->second.vctEventValue.end() - 1);
		dAzcr = Azimuth - iteBlack->second.dAzimuth;
		if (fabs(dAzcr) <= 2*PI_4/180)
		{
			nAzEvent = 1;
		} 
		else if (fabs(dAzcr) > 2*PI_4/180 && fabs(dAzcr)<5*PI_4/180)
		{
			nAzEvent = 3;
		} 
		else
		{
			nAzEvent = 5;
		}
		vctTemp.push_back(nAzEvent);
		//知识库匹配推理
		vctSunCorr.clear();
		for (iteDbKng = theApp.m_DataBase.m_DataBaseData.vctDbPlatKng.begin(); iteDbKng != theApp.m_DataBase.m_DataBaseData.vctDbPlatKng.end(); ++iteDbKng)
		{
			//匹配推理
			nsum = 0;
			for (iteSigKng = iteDbKng->begin(), iteTemp = vctTemp.begin(); iteTemp != vctTemp.end(); ++iteTemp,++iteSigKng)
			{
				if (*iteSigKng == *iteTemp)
				{
					nsum = nsum + 1;
				} 
				else
				{
					nsum = nsum - 1;
				}
			}
			
			//从多部ESM基本事件中找出一种
			nFindFlag = 0;
			for (iteSigKng = iteBlack->second.vctESMEvent.begin(), i = 0; iteSigKng != iteBlack->second.vctESMEvent.end(); ++i,++iteSigKng)
			{
				if (iteDbKng->at(6) == *iteSigKng)
				{
					nFindFlag = 1;
					nsum = nsum + 1;
					//保存平台上有作用的ESM的模板号和基本事件
					nESMHao = iteBlack->second.vctESMHao.at(i);
					nESMEvent = iteBlack->second.vctESMEvent.at(i);
					
				}
			}
			if (nFindFlag == 0)
			{
				nsum = nsum - 1;
			}
			//从多部COM基本事件中找出一种
			nFindFlag = 0;
			for (iteSigKng = iteBlack->second.vctCOMEvent.begin(), i = 0; iteSigKng != iteBlack->second.vctCOMEvent.end(); ++i,++iteSigKng)
			{
				if (iteDbKng->at(7) == *iteSigKng)
				{
					nFindFlag = 1;
					nsum = nsum + 1;
					//保存平台上有作用的COM的模板号和基本事件
					nCOMHao = iteBlack->second.vctCOMHao.at(i);
					nCOMEvent = iteBlack->second.vctCOMEvent.at(i);
					
				}
			}
			if (nFindFlag == 0)
			{
				nsum = nsum - 1;
			}
			vctSunCorr.push_back(nsum);
		}

		//找与平台匹配的最大值
		nMax = vctSunCorr.front();
		nFindPos = -1;
		for (iteSigKng = vctSunCorr.begin(), i = 0; iteSigKng != vctSunCorr.end(); ++i, ++iteSigKng)
		{
			if (nMax < *iteSigKng)
			{
				nMax = *iteSigKng;
				nFindPos = i;
			}
		}
		if (nFindPos > -1)   //找到
		{
			//取出MaxK对应的知识库中的基本事件
			//直接产生平台态势分析链表层节点
			if (nFlag == 1)           //第一次
			{
				//平台链表事件
				PlatListTemp.dAddSpeed = iteBlack->second.dAddSpeed;
				PlatListTemp.dAz = iteBlack->second.dAz;
				PlatListTemp.dAzimuth = iteBlack->second.dAzimuth;
				PlatListTemp.dEz = iteBlack->second.dEz;
				PlatListTemp.dHigh = iteBlack->second.dHigh;
				PlatListTemp.dRd = iteBlack->second.dRd;
				PlatListTemp.dSpeed = iteBlack->second.dSpeed;
				PlatListTemp.dThreatDegree = iteBlack->second.dThreatDegree;
				PlatListTemp.nCOMBasicSituation = nCOMEvent;
				PlatListTemp.nCOMHao = nCOMHao;
				PlatListTemp.nESMBasicSituation = nESMEvent;
				PlatListTemp.nESMHao = nESMHao;
				PlatListTemp.nPlatCumulativeN = 1;
				PlatListTemp.nPlatHao = iteBlack->second.nTrackHao;
				PlatListTemp.nPlatMBHao = nFindPos;
				PlatListTemp.nPlatOBJEvent = theApp.m_DataBase.m_DataBaseData.PlatEventID.at(nFindPos);//有问题
				PlatListTemp.nPlatOBjType = iteBlack->second.nTrackType;
				PlatListTemp.nSerialnum = nCount;
				m_Plat_link.insert(make_pair(PlatListTemp.nPlatHao, PlatListTemp));

				//平台黑板
				PlatBlackTemp.dAddSpeed = iteBlack->second.dAddSpeed;
				PlatBlackTemp.dAz = iteBlack->second.dAz;
				PlatBlackTemp.dAzimuth = iteBlack->second.dAzimuth;
				PlatBlackTemp.dEz = iteBlack->second.dEz;
				PlatBlackTemp.dHigh = iteBlack->second.dHigh;
				PlatBlackTemp.dRd = iteBlack->second.dRd;
				PlatBlackTemp.dSpeed = iteBlack->second.dSpeed;
				PlatBlackTemp.dThreatDegree = iteBlack->second.dThreatDegree;
				PlatBlackTemp.lTimeStamp = iteBlack->second.lTimeStamp;
				PlatBlackTemp.nCOMBasicSituation = nCOMEvent;
				PlatBlackTemp.nCOMHao = nCOMHao;
				PlatBlackTemp.nESMBasicSituation = nESMEvent;
				PlatBlackTemp.nESMHao = nESMHao;
				PlatBlackTemp.nPlatBasicSituation = theApp.m_DataBase.m_DataBaseData.PlatEventID.at(nFindPos);
				PlatBlackTemp.nPlatHao = iteBlack->second.nTrackHao;
				PlatBlackTemp.nSerialnum = nCount;
				PlatBlackTemp.nTrackOBjType = iteBlack->second.nTrackType;
				theApp.m_Plat_Black.insert(make_pair(PlatBlackTemp.nPlatHao, PlatBlackTemp));
			}
			else         //非首次
			{
				PlatListTemp.dAddSpeed = iteBlack->second.dAddSpeed;
				PlatListTemp.dAz = iteBlack->second.dAz;
				PlatListTemp.dAzimuth = iteBlack->second.dAzimuth;
				PlatListTemp.dEz = iteBlack->second.dEz;
				PlatListTemp.dHigh = iteBlack->second.dHigh;
				PlatListTemp.dRd = iteBlack->second.dRd;
				PlatListTemp.dSpeed = iteBlack->second.dSpeed;
				PlatListTemp.dThreatDegree = iteBlack->second.dThreatDegree;
				PlatListTemp.nCOMBasicSituation = nCOMEvent;
				PlatListTemp.nCOMHao = nCOMHao;
				PlatListTemp.nESMBasicSituation = nESMEvent;
				PlatListTemp.nESMHao = nESMHao;
				PlatListTemp.nPlatCumulativeN = 1;
				PlatListTemp.nPlatHao = iteBlack->second.nTrackHao;
				PlatListTemp.nPlatMBHao = nFindPos;
				PlatListTemp.nPlatOBJEvent =theApp.m_DataBase.m_DataBaseData.PlatEventID.at(nFindPos);//有问题
				PlatListTemp.nPlatOBjType = iteBlack->second.nTrackType;
				PlatListTemp.nSerialnum = nCount;
				m_List_temp.insert(make_pair(PlatListTemp.nPlatHao, PlatListTemp));
			}
		}
		++nCount;
	}
	//保存平台和黑板节点的数量
	
	//带回是否传递到下一层的标志
	if (nCount != 0)
	{
		nBack = 1;
	} 
	else
	{
		nBack = 0;
	}
}


////////////////////////////////////////////////////////////////////////////////////
//***********              平台态势企图知识推理设计模块           ****************//
//********                    (2014-07-31  Liuyian)                     **********//
//********     输入：上模块产生的本次平台态势层链表结构数据              *********//
//********    输出：更新平台态势链表节点和黑板的平台态势层              **********//
////////////////////////////////////////////////////////////////////////////////////
void CAlgorithm::Plat_NonFirst_KnowLedge_Basic_Situation_Reason_Modil(MAP_PLAT_LINK& m_Link_temp, int& nBackF)  //(非首次)
{
	VCT_INT::iterator itevct;
	VCT_INT vctNewPlatID;     //存储新出现的平台的编号
	VCT_INT vctAssioPlatID;   //关联起来的平台号
	MAP_PLAT_LINK::iterator mapTemp;
	MAP_PLAT_LINK::iterator mapFind;
	MAP_PLAT_BLACK::iterator mapBlackFind;
	PLATEVENT PlatListTemp;
	PLATBLACK PlatBlackTemp;
	vctNewPlatID.clear();
	vctAssioPlatID.clear();
	nBackF = 0;
	for (mapTemp = m_Link_temp.begin(); mapTemp != m_Link_temp.end(); ++mapTemp)
	{
		mapFind = m_Plat_link.find(mapTemp->first);
		if (mapFind != m_Link_temp.end())    //找到，批号相同
		{
			vctAssioPlatID.push_back(mapFind->first);
			if (mapFind->second.nPlatMBHao == mapTemp->second.nPlatMBHao)            //模板号也相同
			{
				mapFind->second.nPlatCumulativeN++;
				if (mapFind->second.nPlatCumulativeN >= 5)
				{
					mapBlackFind = theApp.m_Plat_Black.find(mapFind->first);
					if (mapBlackFind != theApp.m_Plat_Black.end())  //在黑板中有这个平台,更改黑板数据
					{
						mapBlackFind->second.dAddSpeed = mapFind->second.dAddSpeed;
						mapBlackFind->second.dAz = mapFind->second.dAz;
						mapBlackFind->second.dAzimuth = mapFind->second.dAzimuth;
						mapBlackFind->second.dEz = mapFind->second.dEz;
						mapBlackFind->second.dHigh = mapFind->second.dHigh;
						mapBlackFind->second.dRd = mapFind->second.dRd;
						mapBlackFind->second.dSpeed = mapFind->second.dSpeed;
						mapBlackFind->second.dThreatDegree = mapFind->second.dThreatDegree;
						mapBlackFind->second.lTimeStamp = 1;//??????????????????设置为当前时间
						mapBlackFind->second.nCOMBasicSituation = mapFind->second.nCOMBasicSituation;
						mapBlackFind->second.nCOMHao = mapFind->second.nCOMHao;
						mapBlackFind->second.nESMBasicSituation = mapFind->second.nESMBasicSituation;
						mapBlackFind->second.nESMHao = mapFind->second.nESMHao;
						mapBlackFind->second.nPlatBasicSituation = mapFind->second.nPlatOBJEvent;
						mapBlackFind->second.nPlatHao = mapFind->second.nPlatHao;
						mapBlackFind->second.nSerialnum = mapFind->second.nSerialnum;
						mapBlackFind->second.nTrackOBjType = mapFind->second.nPlatOBjType;
					}
					//平台链表中进行处理
					mapFind->second.nPlatOBJEvent = mapTemp->second.nPlatOBJEvent;
					mapFind->second.dThreatDegree = mapTemp->second.dThreatDegree;
					mapFind->second.nPlatCumulativeN = 1;
					nBackF = 1;
				}
			} 
			else           //模板号不同
			{
				nBackF = 1;
				//平台链表更新
				mapFind->second.nPlatMBHao = mapTemp->second.nPlatMBHao;
				mapFind->second.nPlatCumulativeN = 1;
				mapFind->second.nPlatOBJEvent = mapTemp->second.nPlatOBJEvent;
				mapFind->second.dThreatDegree = mapTemp->second.dThreatDegree;
				//黑板更新
				mapBlackFind = theApp.m_Plat_Black.find(mapFind->first);
				if (mapBlackFind != theApp.m_Plat_Black.end())  //在黑板中有这个平台,更改黑板数据
				{
					mapBlackFind->second.dAddSpeed = mapFind->second.dAddSpeed;
					mapBlackFind->second.dAz = mapFind->second.dAz;
					mapBlackFind->second.dAzimuth = mapFind->second.dAzimuth;
					mapBlackFind->second.dEz = mapFind->second.dEz;
					mapBlackFind->second.dHigh = mapFind->second.dHigh;
					mapBlackFind->second.dRd = mapFind->second.dRd;
					mapBlackFind->second.dSpeed = mapFind->second.dSpeed;
					mapBlackFind->second.dThreatDegree = mapFind->second.dThreatDegree;
					mapBlackFind->second.lTimeStamp = 1;//??????????????????设置为当前时间
					mapBlackFind->second.nCOMBasicSituation = mapFind->second.nCOMBasicSituation;
					mapBlackFind->second.nCOMHao = mapFind->second.nCOMHao;
					mapBlackFind->second.nESMBasicSituation = mapFind->second.nESMBasicSituation;
					mapBlackFind->second.nESMHao = mapFind->second.nESMHao;
					mapBlackFind->second.nPlatBasicSituation = mapFind->second.nPlatOBJEvent;
					mapBlackFind->second.nPlatHao = mapFind->second.nPlatHao;
					mapBlackFind->second.nSerialnum = mapFind->second.nSerialnum;
					mapBlackFind->second.nTrackOBjType = mapFind->second.nPlatOBjType;
				}
			}
		}
		else      //没有找到相同的批号，表示新出现的平台
		{
			vctNewPlatID.push_back(mapTemp->first);
		}
	}
	//这里是消失的平台批号
	for(mapTemp = m_Link_temp.begin(); mapTemp != m_Link_temp.end(); ++mapTemp)
 	{
// 		itevct = vctAssioPlatID.find(mapTemp->first);
// 		if (itevct == vctAssioPlatID.end())              //没找到，表示目标消失
// 		{
// 			//对消失的数据进行处理
// 		}
	}
	//处理新增的节点
	for (itevct = vctNewPlatID.begin(); itevct != vctNewPlatID.end(); ++itevct)
	{
		mapTemp = m_Link_temp.find(*itevct);
		//平台链表事件
		PlatListTemp.dAddSpeed = mapTemp->second.dAddSpeed;
		PlatListTemp.dAz = mapTemp->second.dAz;
		PlatListTemp.dAzimuth = mapTemp->second.dAzimuth;
		PlatListTemp.dEz = mapTemp->second.dEz;
		PlatListTemp.dHigh = mapTemp->second.dHigh;
		PlatListTemp.dRd = mapTemp->second.dRd;
		PlatListTemp.dSpeed = mapTemp->second.dSpeed;
		PlatListTemp.dThreatDegree = mapTemp->second.dThreatDegree;
		PlatListTemp.nCOMBasicSituation = mapTemp->second.nCOMBasicSituation;
		PlatListTemp.nCOMHao = mapTemp->second.nCOMHao;
		PlatListTemp.nESMBasicSituation = mapTemp->second.nESMBasicSituation;
		PlatListTemp.nESMHao = mapTemp->second.nESMHao;
		PlatListTemp.nPlatCumulativeN = 1;
		PlatListTemp.nPlatHao = mapTemp->second.nPlatHao;
		PlatListTemp.nPlatMBHao = mapTemp->second.nPlatMBHao;
		PlatListTemp.nPlatOBJEvent = mapTemp->second.nPlatOBJEvent;
		PlatListTemp.nPlatOBjType = mapTemp->second.nPlatOBjType;
		PlatListTemp.nSerialnum = mapTemp->second.nSerialnum;
		m_Plat_link.insert(make_pair(PlatListTemp.nPlatHao, PlatListTemp));
		
		//平台黑板
		PlatBlackTemp.dAddSpeed = mapTemp->second.dAddSpeed;
		PlatBlackTemp.dAz = mapTemp->second.dAz;
		PlatBlackTemp.dAzimuth = mapTemp->second.dAzimuth;
		PlatBlackTemp.dEz = mapTemp->second.dEz;
		PlatBlackTemp.dHigh = mapTemp->second.dHigh;
		PlatBlackTemp.dRd = mapTemp->second.dRd;
		PlatBlackTemp.dSpeed = mapTemp->second.dSpeed;
		PlatBlackTemp.dThreatDegree = mapTemp->second.dThreatDegree;
		PlatBlackTemp.lTimeStamp = 1;//??????????????????设置为当前时间
		PlatBlackTemp.nCOMBasicSituation = mapTemp->second.nCOMBasicSituation;;
		PlatBlackTemp.nCOMHao = mapTemp->second.nCOMHao;
		PlatBlackTemp.nESMBasicSituation = mapTemp->second.nESMBasicSituation;
		PlatBlackTemp.nESMHao = mapTemp->second.nESMHao;
		PlatBlackTemp.nPlatBasicSituation = mapTemp->second.nPlatOBJEvent;
		PlatBlackTemp.nPlatHao = mapTemp->second.nPlatHao;
		PlatBlackTemp.nSerialnum = mapTemp->second.nSerialnum;
		PlatBlackTemp.nTrackOBjType = mapTemp->second.nPlatOBjType;
		theApp.m_Plat_Black.insert(make_pair(PlatBlackTemp.nPlatHao, PlatBlackTemp));

		nBackF = 1;
	}
}


/////////////////////////////////////////空间层////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////
/*****************************************************/
/**********         系统聚类法(已测试过)    **********/
/**********      2014-08-04  Liuyian   ***************/
/********* 输入:对称矩阵Rd0和阶数pp*/
/*Rd0表示从数据库中获取的群距离值*/
/*LLCC表示飞机或舰船的链表              ******/
/*********  输出:聚类的数及各类序号             ******/
/*TGroupN表示群的数量             ******/
/*EGN表示每个群中的目标数量              ******/
/*EveryGroup表示每个群中的目标的编号              ******/
/*****************************************************/
void CAlgorithm::Metri_Cluttle_Modul(int pp, double Rd0, VV_DOUBLE& AA, VCT_INT& LLCC, int& TGroupN, VCT_INT& EGN, VV_INT& EveryGroup)
{
	int i,j,k,m,n,g,w;
	
	double HH[100][100];
	double BB[100][100];
	///////////////////
	double min;
	double aa[100],bb[100],cc[100];
	int LC[100][50];
	int LLCC0[300];
	
	int mini,minj;
	int Flag,dFlag;
	int RN;
	int temp;
	int qq[100];//放各类个数
	int SeekF0,SeekF1,SeekF2;
	VCT_INT vct_temp;
	/////////////////////////////
	
	/////////////////////////////
	
	//接收转存
	RN=pp;
	for(i=0;i<RN;i++)
		for(j=0;j<RN;j++)
			HH[i][j]=AA[i][j];
		
		//系统取聚类法(矩阵特点:1:主对角线上元素均为0,2:其他元素均为正,3:且为对称矩阵)
		//第一步：由于是对称阵,只运算上三角,先找最小值
		m=0;//统计类数
		temp=RN;
		dFlag=0;
		min=0;
		while(RN>2)
		{
			Flag=0;
			for(i=0;i<RN-1;i++)//找出最小值
			{
				for(j=i+1;j<RN;j++)
				{
					if(Flag==0)
					{   
						min=HH[i][j];
						mini=i;
						minj=j;
						
						Flag=1;
					}
					else
					{
						if(min>HH[i][j])
						{
							min=HH[i][j];
							mini=i;
							minj=j;
						}
					}
					
				}//for j
			}//for i
			
			for(i=0;i<RN;i++)    //抽出合并行
			{
				aa[i]=HH[mini][i];
				bb[i]=HH[minj][i];
			}
			for(i=0;i<RN;i++)  //产生合并行值
			{
				if(aa[i]>bb[i])
					cc[i]=bb[i];
				else
					cc[i]=aa[i];		 
			}


		 //保存合并的原始序号
		 if(dFlag==0)
		 {
			LC[m][0]=LLCC[mini];
		     	LC[m][1]=LLCC[minj];

			 temp=temp+1;
			 LC[m][2]=temp;//合并号
			 qq[m]=3;
		
			 //调整LLCC中的序号位置
			 k=0;
			 for(i=0;i<RN;i++)//读出
			 {
				 if(i!=mini && i!=minj)
				 {
				     	LLCC0[k]=LLCC[i];
				 
					 k++;
				 }			 
			 }
			 for(i=0;i<k;i++)//写入
			 {
				 LLCC[i]=LLCC0[i];	
			 }
			 LLCC[i]=temp;

			 dFlag=1;
			 m++;
		 }
		 else
		 {
			 if(min<Rd0)
			 {
                 			SeekF0=0;
				 for(i=0;i<m;i++)//类循环
				 {
				      	SeekF1=0;//先找i号
				      	for(k=0;k<qq[i];k++)//此类中的个数
					  {

					     if(LLCC[mini]==LC[i][k])
						 {
						    SeekF1=1;//找到
						 }				 
					  }

					  SeekF2=0;//再找j号
				     	 for(k=0;k<qq[i];k++)
					  {
					     	if(LLCC[minj]==LC[i][k])
						 {
						    SeekF2=1;//找到
						 }				 
					  }

					  if(SeekF1!=0 || SeekF2!=0)  //找到,不为新类
					  {
						  if(SeekF1!=0 && SeekF2==0)
						  {
							  
					          		LC[i][qq[i]]=LLCC[minj];//添加新的号

							   //调整LLCC中的序号位置
			                   			g=0;
			                  			for(w=0;w<RN;w++)//读出
							{
				                    			if(w!=minj)
								{
				                       				LLCC0[g]=LLCC[w];
					                   			g++;
								}			 
							   }
			                   			for(w=0;w<g;w++)//写入
							{
				                    			LLCC[w]=LLCC0[w];									
							}							   
							   LLCC[w]=temp;
							   qq[i]++;

							   temp++;

						  }

						  if(SeekF1==0 && SeekF2!=0)
						  {
							  
					          		LC[i][qq[i]]=LLCC[mini];//添加新的号

							  //调整LLCC中的序号位置
			                   			g=0;
			                   			for(w=0;w<RN;w++)//读出
							 {
				                    			if(w!=mini)
								{
				                       				LLCC0[g]=LLCC[w];
				 
					                   			g++;
								}			 
							}
			                   			for(w=0;w<g;w++)//写入
							{
				                    			LLCC[w]=LLCC0[w];
							}
							   qq[i]++;
							   temp++;
							   LLCC[w]=temp;		    

						  }			
						  SeekF0=1;

						  i=i+m;   //提前退出
					}

				 }//for i				 

				 if(SeekF0==0)  //均没找到,为新类
				 {
					 LC[m][0]=LLCC[mini];
		             		LC[m][1]=LLCC[minj];

			        		 temp=temp+1;
			         		LC[m][2]=temp;//合并号
					 qq[m]=3;

					//调整LLCC中的序号位置
			        		g=0;
			        		for(w=0;w<RN;w++)//读出
					{
				        		if(w!=mini && w!=minj)
						{
				              		LLCC0[g]=LLCC[w];
				 
					          		g++;
						}			 
					}
			        		for(w=0;w<g;w++)//写入
					{
				        		LLCC[w]=LLCC0[w];
					}
					
					LLCC[w]=temp;

				    	m++;
				 }		   
			  }//Rd0  
		 }//if dFlag

		 n=0;
		 for(i=0;i<RN;i++)
		 {
		     	if(i!=mini && i!=minj)
			{
			      	k=0;
			     	 for(j=0;j<RN;j++)
				{
				      	if(j!=mini && j!=minj)
					{
					       	BB[n][k]=HH[i][j];	 
					 
					      	 k++;
					}
				}//for j

			      	n++;
			 }
		 
		 }//for i
		 
		 k=0;
		 for(i=0;i<RN;i++)
		 {
		    	if(i!=mini && i!=minj)
			 {
		         		BB[n][k]=cc[i];
		         		BB[k][n]=cc[i];
					  
		         		k++;
			}//
		 }//for i
		 BB[k][k]=0;

		 RN--;

		 for(i=0;i<RN;i++)
		 {
		      	for(j=0;j<RN;j++)
			{
		         		HH[i][j]=BB[i][j];
			}
		 }

	 }//while
	 		
	 //输出结果	
	 TGroupN=m;    //空间群数(两个及以上目标才称为群)
	for(i=0;i<m;i++)
	{
		k=0;
		vct_temp.clear();
		for(j=0;j<qq[i];j++)
		{
			if(LC[i][j]>pp)
				vct_temp.push_back(LC[i][j]);		
		    	k++;
		}//for j
		EveryGroup.push_back(vct_temp);
	    EGN.push_back(k-1);
	}//for i
	
}


///////////////////////////////输入///////////////////////////////////////////
//NewPlat 为NvctTgt的平台数
//TGroupN空间群的数目
//EGN每个群的目标数
//EveryGroup每个群所含的目标批号
//vctTgt所有飞机的信息
///////////////////////////////输出///////////////////////////////////////////
//iAverSpeed带回速度的总体偏差
//AverAzmith带回航向的总体偏差
//Kthreatgree带回每个群的威胁度
void CAlgorithm::dVPspeed_dAzmith_Modul(int& TGroupN, VCT_INT& EGN, VV_INT& EveryGroup, VCT_PLAT_BLACK& vctTgt, double& iAverSpeed, double& AverAzmith, VCT_DOUBLE& Kthreatgree)
{
	int i,j,k;
	
	VCT_INT MFlag;
	VCT_INT dFlag;
	
	VCT_DOUBLE TSumVSpeed;
	VCT_DOUBLE TSumAzmith;
	VCT_DOUBLE ddSpeed;
	VCT_DOUBLE ddAzmith;
	double SumVp;
	double SumAz;
	VCT_DOUBLE Thretgr;
	VCT_DOUBLE TempVSpeed;
	VCT_DOUBLE TempAzmith;
	
	//初始化
	for(i = 0; i < vctTgt.size(); ++i)
	{
		MFlag.push_back(0);
		dFlag.push_back(0);
	}
	//	
	for(i=0; i < TGroupN; ++i)//群数
	{
		TempAzmith.push_back(0);
		TempVSpeed.push_back(0);
		TSumVSpeed.push_back(0);
		TSumAzmith.push_back(0);
		Thretgr.push_back(1.0);
		for(j = 0; j < EGN[i]; ++j)//每群中的数
		{			
			for(k=0; k < vctTgt.size(); ++k)//平台数
			{
				if(MFlag[k] == 0)//没处理过
				{
					if(EveryGroup[i][j] == vctTgt[k].nPlatHao)//找到
					{
						MFlag[k] = 1;
                        
						TempVSpeed[i] = TempVSpeed[i] + vctTgt[k].dSpeed/EGN[i];  //群均值
						TempAzmith[i] = TempAzmith[i] + vctTgt[k].dAzimuth/EGN[i];  //群均值	
						Thretgr[i] = Thretgr[i]*(1.0 - vctTgt[k].dThreatDegree);
					}
				}
				
			}//for k
			
		}//for j
		
		ddSpeed.push_back(0);
		ddAzmith.push_back(0);
		for(j = 0; j < EGN[i]; ++j)
		{			
			for(k = 0; k < vctTgt.size(); ++k)
			{
				if(dFlag[k] == 0)//没处理过
				{
					if(EveryGroup[i][j] == vctTgt[k].nPlatHao)//找到
					{
						dFlag[k] = 1;
                        
						ddSpeed[i] = ddSpeed[i]+(vctTgt[k].dSpeed - TempVSpeed[i])*(vctTgt[k].dSpeed - TempVSpeed[i]);    //群方差
						ddAzmith[i] = ddAzmith[i]+(vctTgt[k].dAzimuth - TempAzmith[i])*(vctTgt[k].dAzimuth - TempAzmith[i]);  //群方差			
					}
				}
				
			}//for k
			
		}//for j
		
		ddSpeed[i] = sqrt(ddSpeed[i]/EGN[i]);      //群标准差
		ddAzmith[i] = sqrt(ddAzmith[i]/EGN[i]);	 //群标准差
		Thretgr[i] = 1.0 - Thretgr[i];               //该群的综合威胁度
		
	}//for i
	
	SumVp = 0;
	SumAz = 0;
	for(i = 0; i < TGroupN; ++i)
	{
		SumVp = SumVp + ddSpeed[i]/TGroupN;
		SumAz = SumAz + ddAzmith[i]/TGroupN;	
		
		Kthreatgree.push_back(Thretgr[i]);        //带回该群的综合威胁度
		
	}//for i
	
	//带回总体偏差
	iAverSpeed = SumVp;    //带回速度偏差
	AverAzmith = SumAz;   //带回航向的总体偏差	
}


/////////////////////////////////////////////////////////////////////////////////////////
//                               空间群知识推理模块设计                                //
//********                    (2014-10-18  Liuyian)                          **********//
//********     输入：黑板上平台态势层结构数据                           **********//
//********　         非首次产生待更新的链表数据                              ******//
//********     输出：产生空间群类、及数目                                    **********//
//********           产生空间群链表结构数据                                  **********//
/////////////////////////////////////////////////////////////////////////////////////////
void CAlgorithm::SpaceGroup_Reason_PlatSituationEvent_datamodul(MAP_PLAT_BLACK& m_Plat_Black, SPACE_TARGET& vctPlaneLink, SPACE_TARGET& vctShipLink, int& BFlag)
{
	int i, j;
	double dmin;
	double dMink;
	double dTemp;
	double dDistance;
	VCT_DOUBLE vct_dou_temp;
	vector<PLATBLACK> vctPlaneTemp;          //存储分类后飞机的所有数据
	vector<PLATBLACK> vctShipTemp;
	vector<PLATBLACK>::iterator itePlat;
	MAP_PLAT_BLACK::iterator mapPlat;
	TARGET_POSITION PositonTemp;
	VCT_POSITION vctPoShip;			//保存所有舰船的位置，x，y，z
	VCT_POSITION vctPoPlane;		//保存所有的飞机的位置，x，y，z
	VV_DOUBLE vctMatrixPlane;		//飞机的距离矩阵
	VV_DOUBLE vctMatrixShip;		//舰船的距离矩阵
// 	VV_DOUBLE::iterator itevvtemp;
// 	VCT_DOUBLE::iterator itevcttemp;
	VCT_POSITION::iterator itePoFirst;
	VCT_POSITION::iterator itePoSec;
	VV_INT::iterator iteKng;
	VCT_INT vctModelID;			//模板号
	VCT_INT vctModelNum;		//该模板对应的空间群数
	VCT_INT vctPlatID;			//批号
	int TGroupN;				//群数量
	VCT_INT EGN;				//每个群内的目标的个数
	VV_INT EveryGroup;			//每个群内的批号
	DOUBLE iAverSpeed;			//平均的速度
	DOUBLE AverAzmith;			//平均的航向
	VCT_DOUBLE vctiAverSpeed;			//平均的速度
	VCT_DOUBLE vctAverAzmith;			//平均的航向
	VCT_DOUBLE vctKthreatgree;		//威胁度
	VCT_INT vctPlatType;		//平台类型
	VCT_INT vctPlatTaishi;		//平台态势
	VCT_INT vctTemp;
	SPACE_TARGET TgtTmep;

	VV_INT::iterator iteEG;     //EveryGroup的迭代器

	VV_INT vvEGN;
	vector<VV_INT> vvEveryGroup;
	vector<VV_INT>::iterator itevvv;
	VV_DOUBLE vvKthreatgree;

	vctPlaneTemp.clear();
	vctShipTemp.clear();
	vctMatrixPlane.clear();
	vctMatrixShip.clear();
	vctPoPlane.clear();
	vctPoShip.clear();

	//1:先产生推理的空间群结构数据
	//类型分类(只考虑两大类,飞机类存入vctPlane,舰船类存入vctShip)
	//先坐标变换，转到本舰雷达直角坐标系中
	//将计算的x,y,z的值分别存入vctPoShip和vctPoPlane中
	for (mapPlat = m_Plat_Black.begin(); mapPlat != m_Plat_Black.end(); ++mapPlat)
	{
		if (mapPlat->second.nTrackOBjType == 1 || mapPlat->second.nTrackOBjType == 2 || mapPlat->second.nTrackOBjType == 3)	//飞机类
		{
			PositonTemp.dx = mapPlat->second.dRd*cos(mapPlat->second.dEz)*sin(mapPlat->second.dAz);//?????这里要用弧度，需要换算吗？？？？？
			PositonTemp.dy = mapPlat->second.dRd*cos(mapPlat->second.dEz)*cos(mapPlat->second.dAz);//同上
			PositonTemp.dz = mapPlat->second.dRd*sin(mapPlat->second.dEz); //同上
			vctPoPlane.push_back(PositonTemp);
			vctPlaneTemp.push_back(mapPlat->second);
		} 
		else if (mapPlat->second.nTrackOBjType == 4)	//舰船类
		{
			PositonTemp.dx = mapPlat->second.dRd*cos(mapPlat->second.dEz)*sin(mapPlat->second.dAz);//?????这里要用弧度，需要换算吗？？？？？
			PositonTemp.dy = mapPlat->second.dRd*cos(mapPlat->second.dEz)*cos(mapPlat->second.dAz);//同上
			PositonTemp.dz = mapPlat->second.dRd*sin(mapPlat->second.dEz); //同上
			vctPoShip.push_back(PositonTemp);
			vctShipTemp.push_back(mapPlat->second);
		} 
		else
		{
			//不处理
		}
	}
	//1: 先计算飞机类:  两两之间的空间距离
	for (itePoFirst = vctPoPlane.begin(); itePoFirst != vctPoPlane.end(); ++itePoFirst)
	{
		vct_dou_temp.clear();
		for (itePoSec = vctPoPlane.begin(); itePoSec != vctPoPlane.end(); ++itePoSec)
		{
			if (itePoSec == itePoFirst)
			{
				vct_dou_temp.push_back(0.0);
			} 
			else
			{
				dDistance = sqrt((itePoFirst->dx - itePoSec->dx)*(itePoFirst->dx - itePoSec->dx) + 
					(itePoFirst->dy - itePoSec->dy)*(itePoFirst->dy - itePoSec->dy) + 
					(itePoFirst->dz - itePoSec->dz)*(itePoFirst->dz - itePoSec->dz));
				vct_dou_temp.push_back(dDistance);
			}
		}
		vctMatrixPlane.push_back(vct_dou_temp);
	}


	//利用空间层知识库对飞机聚类
	vctPlatID.clear();
	//将批号存入vctPlatID中
	for(itePlat = vctPlaneTemp.begin(); itePlat != vctPlaneTemp.end(); ++itePlat)			
	{
		vctPlatID.push_back(itePlat->nPlatHao);
	}

	//vector清空
	vctModelID.clear();
	vctModelNum.clear();
	for(iteKng = vvEGN.begin(); iteKng != vvEGN.end(); ++iteKng)
	{
		iteKng->clear();
	}
	vvEGN.clear();
	for (itevvv = vvEveryGroup.begin(); itevvv != vvEveryGroup.end(); ++itevvv)
	{
		for (iteKng = itevvv->begin(); iteKng != itevvv->end(); ++iteKng)
		{
			iteKng->clear();
		}
		itevvv->clear();
	}
	vvEveryGroup.clear();

	for (iteKng = theApp.m_DataBase.m_DataBaseData.vctDbSpaceKng.begin(), i = 0; iteKng != theApp.m_DataBase.m_DataBaseData.vctDbSpaceKng.end(); ++iteKng, ++i)
	{
		if ((*iteKng)[0] == 2)	//类型为飞机
		{
			vctModelID.push_back(theApp.m_DataBase.m_DataBaseData.SpaceGrpID[i]);
			//将要接收数据的变量清空
			EGN.clear();
			for (iteEG = EveryGroup.begin(); iteEG != EveryGroup.end(); ++iteEG)
			{
				iteEG->clear();
			}
			EveryGroup.clear();
			vctiAverSpeed.clear();
			vctAverAzmith.clear();
			vctKthreatgree.clear();
			Metri_Cluttle_Modul(vctPoPlane.size(), (*iteKng)[1], vctMatrixPlane, vctPlatID, TGroupN, EGN, EveryGroup);
			dVPspeed_dAzmith_Modul(TGroupN, EGN, EveryGroup, vctPlaneTemp, iAverSpeed, AverAzmith, vctKthreatgree);
			vctModelNum.push_back(TGroupN);			//此模板对应的目标群数
		
			vvEGN.push_back(EGN);

			vctiAverSpeed.push_back(iAverSpeed);
			vctAverAzmith.push_back(AverAzmith);
			vvEveryGroup.push_back(EveryGroup);
			vvKthreatgree.push_back(vctKthreatgree);

		}
	}
	//找出飞机类差最小者
	dmin = vctiAverSpeed[0] + vctAverAzmith[0];
	dMink = -1;
	for (i = 1; i < vvEGN.size(); ++i)
	{
		dTemp = vctiAverSpeed[i] + vctAverAzmith[i];
		if (dmin > dTemp)
		{
			dmin = dTemp;
			dMink = i;
		}
	}
	
	if (dMink > -1)			//找到
	{
		//产生飞机空间群链表结构
		vctPlaneLink.nPlanTypeN = vctModelNum[dMink];         //空间群的个数
		for (i = 0; i < vctModelNum[dMink]; ++i)		//每一个空间群中
		{
			vctPlaneLink.vctPlanGroupN.push_back(vvEGN[dMink][i]);			//每个群中平台的数量
			vctTemp.clear();
			vctPlatType.clear();
			vctPlatTaishi.clear();
			for (j = 0; j < vvEGN[dMink][i]; ++j)
			{
				vctTemp.push_back(vvEveryGroup[dMink][i][j]);
				for (itePlat = vctPlaneTemp.begin(); itePlat != vctPlaneTemp.end(); ++itePlat)
				{
					if (itePlat->nPlatHao == vvEveryGroup[dMink][i][j])
					{
						 //取出此平台的类型和态势,写入链表结构
						vctPlatType.push_back(itePlat->nTrackOBjType);
						vctPlatTaishi.push_back(itePlat->nPlatBasicSituation);
					}
				}
			}
			vctPlaneLink.vvPlanGroupHao.push_back(vctTemp);
			vctPlaneLink.vvPlanGroupOBjType.push_back(vctPlatType);
			vctPlaneLink.vvPlanEvent.push_back(vctPlatTaishi);
			vctPlaneLink.vctPlanThreatDegree.push_back(vvKthreatgree[dMink][i]);		//每个群的综合威胁度
		}
		vctPlaneLink.nPlanSpacMBHao = vctModelID[dMink];
	}

	//2: 再处理舰船类：计算两两之间的空间距离
	for (itePoFirst = vctPoShip.begin(); itePoFirst != vctPoShip.end(); ++itePoFirst)
	{
		vct_dou_temp.clear();
		for (itePoSec = vctPoShip.begin(); itePoSec != vctPoShip.end(); ++itePoSec)
		{
			if (itePoSec == itePoFirst)
			{
				vct_dou_temp.push_back(0.0);
			} 
			else
			{
				dDistance = sqrt((itePoFirst->dx - itePoSec->dx)*(itePoFirst->dx - itePoSec->dx) + 
					(itePoFirst->dy - itePoSec->dy)*(itePoFirst->dy - itePoSec->dy) + 
					(itePoFirst->dz - itePoSec->dz)*(itePoFirst->dz - itePoSec->dz));
				vct_dou_temp.push_back(dDistance);
			}
		}
		vctMatrixShip.push_back(vct_dou_temp);
	}
	

	//利用空间层知识库对舰船聚类
	vctPlatID.clear();
	//将批号存入vctPlatID中
	for(itePlat = vctShipTemp.begin(); itePlat != vctShipTemp.end(); ++itePlat)			
	{
		vctPlatID.push_back(itePlat->nPlatHao);
	}
	//vector清空
	vctModelID.clear();
	vctModelNum.clear();
	for(iteKng = vvEGN.begin(); iteKng != vvEGN.end(); ++iteKng)
	{
		iteKng->clear();
	}
	vvEGN.clear();
	for (itevvv = vvEveryGroup.begin(); itevvv != vvEveryGroup.end(); ++itevvv)
	{
		for (iteKng = itevvv->begin(); iteKng != itevvv->end(); ++iteKng)
		{
			iteKng->clear();
		}
		itevvv->clear();
	}
	vvEveryGroup.clear();

	for (iteKng = theApp.m_DataBase.m_DataBaseData.vctDbSpaceKng.begin(), i = 0; iteKng != theApp.m_DataBase.m_DataBaseData.vctDbSpaceKng.end(); ++iteKng, ++i)
	{
		if ((*iteKng)[0] == 1)	//类型为舰船
		{
			vctModelID.push_back(theApp.m_DataBase.m_DataBaseData.SpaceGrpID[i]);
			//将要接收数据的变量清空
			EGN.clear();
			for (iteEG = EveryGroup.begin(); iteEG != EveryGroup.end(); ++iteEG)
			{
				iteEG->clear();
			}
			EveryGroup.clear();
			vctiAverSpeed.clear();
			vctAverAzmith.clear();
			vctKthreatgree.clear();
			Metri_Cluttle_Modul(vctPoPlane.size(), (*iteKng)[1], vctMatrixPlane, vctPlatID, TGroupN, EGN, EveryGroup);
			dVPspeed_dAzmith_Modul(TGroupN, EGN, EveryGroup, vctPlaneTemp, iAverSpeed, AverAzmith, vctKthreatgree);
			//下面的vector用之前要清空
			vctModelNum.push_back(TGroupN);			//此模板对应的目标群数
			vvEGN.push_back(EGN);
			vctiAverSpeed.push_back(iAverSpeed);
			vctAverAzmith.push_back(AverAzmith);
			vvEveryGroup.push_back(EveryGroup);
			vvKthreatgree.push_back(vctKthreatgree);
		}
	}
	//找出飞机类差最小者
	dmin = vctiAverSpeed[0] + vctAverAzmith[0];
	dMink = -1;
	for (i = 1; i < vvEGN.size(); ++i)
	{
		dTemp = vctiAverSpeed[i] + vctAverAzmith[i];
		if (dmin > dTemp)
		{
			dmin = dTemp;
			dMink = i;
		}
	}
	
	if (dMink > -1)			//找到
	{
		//产生飞机空间群链表结构
		vctShipLink.nPlanTypeN = vctModelNum[dMink];         //空间群的个数
		for (i = 0; i < vctModelNum[dMink]; ++i)		//每一个空间群中
		{
			vctShipLink.vctPlanGroupN.push_back(vvEGN[dMink][i]);			//每个群中平台的数量
			vctTemp.clear();
			vctPlatType.clear();
			vctPlatTaishi.clear();
			for (j = 0; j < vvEGN[dMink][i]; ++j)
			{
				vctTemp.push_back(vvEveryGroup[dMink][i][j]);
				for (itePlat = vctPlaneTemp.begin(); itePlat != vctPlaneTemp.end(); ++itePlat)
				{
					if (itePlat->nPlatHao == vvEveryGroup[dMink][i][j])
					{
						//取出此平台的类型和态势,写入链表结构
						vctPlatType.push_back(itePlat->nTrackOBjType);
						vctPlatTaishi.push_back(itePlat->nPlatBasicSituation);
					}
				}
			}
			vctShipLink.vvPlanGroupHao.push_back(vctTemp);
			vctShipLink.vvPlanGroupOBjType.push_back(vctPlatType);
			vctShipLink.vvPlanEvent.push_back(vctPlatTaishi);
			vctShipLink.vctPlanThreatDegree.push_back(vvKthreatgree[dMink][i]);		//每个群的综合威胁度
		}
		vctShipLink.nPlanSpacMBHao = vctModelID[dMink];
	}
}


/////////////////////////////////////////////////////////////////////////////////////////
//***********            更新空间群链表节点处理和判断设计模块          ****************//
//********                    (2014-08-4  Liuyian)                           **********//
//********     输入：SpaceFlag是否是第一次                                         ****//
//********           本次已划分群的飞机信息                                  **********//
//********           上次已划分群的舰船信息                                  **********//
//********     输出：更新链表、黑板结构信息									 **********//
//********			 nFlag表示是否刺激下一层								 **********//
/////////////////////////////////////////////////////////////////////////////////////////
void CAlgorithm::Updata_SpaceGroups_Situation_LinKJudge_Process_Modul(int nSpaceFlag, SPACE_TARGET PlaneData, SPACE_TARGET ShipData, int nFlag)
{
	int i;
	int nPlaneFlag(0);			//飞机数据有更新
	int nShipFlag(0);			//舰船数据有更新
/*	VCT_INT::iterator itevctTemp;*/
	VV_INT::iterator itevv;
	VCT_INT vctTemp;
	if (nSpaceFlag == 0)				//首次
	{
		//1  直接将产生的空间群链表数据，写入空间群链表中
        //11 先飞机类
		m_PlaneSpaceLink.nPlanCumulativeN = 1;
		m_PlaneSpaceLink.nPlanSpacMBHao = PlaneData.nPlanSpacMBHao;
		m_PlaneSpaceLink.nPlanTypeN = PlaneData.nPlanTypeN;
		m_PlaneSpaceLink.vctPlanGroupN.assign(PlaneData.vctPlanGroupN.begin(), PlaneData.vctPlanGroupN.end());
		for (itevv = PlaneData.vvPlanEvent.begin(); itevv != PlaneData.vvPlanEvent.end(); ++itevv)
		{
			vctTemp.clear();
			vctTemp.assign(itevv->begin(),itevv->end());
			m_PlaneSpaceLink.vvPlanEvent.push_back(vctTemp);
		}
		for (itevv = PlaneData.vvPlanGroupHao.begin(); itevv != PlaneData.vvPlanGroupHao.end(); ++itevv)
		{
			vctTemp.clear();
			vctTemp.assign(itevv->begin(),itevv->end());
			m_PlaneSpaceLink.vvPlanGroupHao.push_back(vctTemp);
		}
		for (itevv = PlaneData.vvPlanGroupOBjType.begin(); itevv != PlaneData.vvPlanGroupOBjType.end(); ++itevv)
		{
			vctTemp.clear();
			vctTemp.assign(itevv->begin(),itevv->end());
			m_PlaneSpaceLink.vvPlanGroupOBjType.push_back(vctTemp);
		}
		m_PlaneSpaceLink.vctPlanThreatDegree.assign(PlaneData.vctPlanThreatDegree.begin(), PlaneData.vctPlanThreatDegree.end());
		//12 再舰船类
		m_ShipSpaceLink.nPlanCumulativeN = 1;
		m_ShipSpaceLink.nPlanSpacMBHao = ShipData.nPlanSpacMBHao;
		m_ShipSpaceLink.nPlanTypeN = ShipData.nPlanTypeN;
		m_ShipSpaceLink.vctPlanGroupN.assign(ShipData.vctPlanGroupN.begin(), ShipData.vctPlanGroupN.end());
		for (itevv = ShipData.vvPlanEvent.begin(); itevv != ShipData.vvPlanEvent.end(); ++itevv)
		{
			vctTemp.clear();
			vctTemp.assign(itevv->begin(),itevv->end());
			m_ShipSpaceLink.vvPlanEvent.push_back(vctTemp);
		}
		for (itevv = ShipData.vvPlanGroupHao.begin(); itevv != ShipData.vvPlanGroupHao.end(); ++itevv)
		{
			vctTemp.clear();
			vctTemp.assign(itevv->begin(),itevv->end());
			m_ShipSpaceLink.vvPlanGroupHao.push_back(vctTemp);
		}
		for (itevv = ShipData.vvPlanGroupOBjType.begin(); itevv != ShipData.vvPlanGroupOBjType.end(); ++itevv)
		{
			vctTemp.clear();
			vctTemp.assign(itevv->begin(),itevv->end());
			m_ShipSpaceLink.vvPlanGroupOBjType.push_back(vctTemp);
		}
		m_ShipSpaceLink.vctPlanThreatDegree.assign(ShipData.vctPlanThreatDegree.begin(), ShipData.vctPlanThreatDegree.end());
		//2  同时创建黑板模型的空间群结构数据	
		//21 飞机
		theApp.m_PlaneSpaceBlack.lTimeStamp = 1000000;
		theApp.m_PlaneSpaceBlack.nPlanTypeN = PlaneData.nPlanTypeN;
		theApp.m_PlaneSpaceBlack.vctPlanGroupN.assign(PlaneData.vctPlanGroupN.begin(), PlaneData.vctPlanGroupN.end());
		theApp.m_PlaneSpaceBlack.vctPlanThreatDegree.assign(PlaneData.vctPlanThreatDegree.begin(), PlaneData.vctPlanThreatDegree.end());
		for (itevv = PlaneData.vvPlanEvent.begin(); itevv != PlaneData.vvPlanEvent.end(); ++itevv)
		{
			vctTemp.clear();
			vctTemp.assign(itevv->begin(),itevv->end());
			theApp.m_PlaneSpaceBlack.vvPlanEvent.push_back(vctTemp);
		}
		for (itevv = PlaneData.vvPlanGroupHao.begin(); itevv != PlaneData.vvPlanGroupHao.end(); ++itevv)
		{
			vctTemp.clear();
			vctTemp.assign(itevv->begin(),itevv->end());
			theApp.m_PlaneSpaceBlack.vvPlanGroupHao.push_back(vctTemp);
		}
		for (itevv = PlaneData.vvPlanGroupOBjType.begin(); itevv != PlaneData.vvPlanGroupOBjType.end(); ++itevv)
		{
			vctTemp.clear();
			vctTemp.assign(itevv->begin(),itevv->end());
			theApp.m_PlaneSpaceBlack.vvPlanGroupOBjType.push_back(vctTemp);
		}
		//22 再舰船类
		theApp.m_ShipSpaceBlack.lTimeStamp = 1000000;
		theApp.m_ShipSpaceBlack.nPlanTypeN = ShipData.nPlanTypeN;
		theApp.m_ShipSpaceBlack.vctPlanGroupN.assign(ShipData.vctPlanGroupN.begin(), ShipData.vctPlanGroupN.end());
		theApp.m_ShipSpaceBlack.vctPlanThreatDegree.assign(ShipData.vctPlanThreatDegree.begin(), ShipData.vctPlanThreatDegree.end());
		for (itevv = ShipData.vvPlanEvent.begin(); itevv != ShipData.vvPlanEvent.end(); ++itevv)
		{
			vctTemp.clear();
			vctTemp.assign(itevv->begin(),itevv->end());
			theApp.m_ShipSpaceBlack.vvPlanEvent.push_back(vctTemp);
		}
		for (itevv = ShipData.vvPlanGroupHao.begin(); itevv != ShipData.vvPlanGroupHao.end(); ++itevv)
		{
			vctTemp.clear();
			vctTemp.assign(itevv->begin(),itevv->end());
			theApp.m_ShipSpaceBlack.vvPlanGroupHao.push_back(vctTemp);
		}
		for (itevv = ShipData.vvPlanGroupOBjType.begin(); itevv != ShipData.vvPlanGroupOBjType.end(); ++itevv)
		{
			vctTemp.clear();
			vctTemp.assign(itevv->begin(),itevv->end());
			theApp.m_ShipSpaceBlack.vvPlanGroupOBjType.push_back(vctTemp);
		}
		nPlaneFlag = 1;
		nSpaceFlag = 1;
	} 
	else								//非首次
	{
		//1 每次调用，每类只产生一次划分，即每次一个模板号数
		//先取出当前产生的空间链表数据
		//1.1 先飞机类
		if (m_PlaneSpaceLink.nPlanSpacMBHao == PlaneData.nPlanSpacMBHao)			//找到,累加模板节点上的信息
		{
			//更新链表上旧节点内容
			m_PlaneSpaceLink.nPlanTypeN = PlaneData.nPlanTypeN;
			m_PlaneSpaceLink.vctPlanGroupN.clear();
			m_PlaneSpaceLink.vctPlanGroupN.assign(PlaneData.vctPlanGroupN.begin(), PlaneData.vctPlanGroupN.end());
			m_PlaneSpaceLink.vctPlanThreatDegree.clear();
			m_PlaneSpaceLink.vctPlanThreatDegree.assign(PlaneData.vctPlanThreatDegree.begin(), PlaneData.vctPlanThreatDegree.end());
			for (i = 0; i < PlaneData.nPlanTypeN; ++i)
			{
				m_PlaneSpaceLink.vvPlanGroupHao[i].clear();
				m_PlaneSpaceLink.vvPlanGroupHao[i].assign(PlaneData.vvPlanGroupHao[i].begin(), PlaneData.vvPlanGroupHao[i].end());
				m_PlaneSpaceLink.vvPlanGroupOBjType[i].clear();
				m_PlaneSpaceLink.vvPlanGroupOBjType[i].assign(PlaneData.vvPlanGroupOBjType[i].begin(), PlaneData.vvPlanGroupOBjType[i].end());
				m_PlaneSpaceLink.vvPlanEvent[i].clear();
				m_PlaneSpaceLink.vvPlanEvent[i].assign(PlaneData.vvPlanEvent[i].begin(), PlaneData.vvPlanEvent[i].end());
			}
			
			++m_PlaneSpaceLink.nPlanCumulativeN;		//累积数加1

			//累积超过5次，开始更新黑板
			if (m_PlaneSpaceLink.nPlanCumulativeN >= 5)			
			{
				nPlaneFlag = 1;
				//同时，产生更新黑板模型的空间群结构数据
				theApp.m_PlaneSpaceBlack.lTimeStamp = 1000000;
				theApp.m_PlaneSpaceBlack.nPlanTypeN = PlaneData.nPlanTypeN;
				theApp.m_PlaneSpaceBlack.nPlanTypeN = PlaneData.nPlanTypeN;
				theApp.m_PlaneSpaceBlack.vctPlanGroupN.clear();
				theApp.m_PlaneSpaceBlack.vctPlanGroupN.assign(PlaneData.vctPlanGroupN.begin(), PlaneData.vctPlanGroupN.end());
				theApp.m_PlaneSpaceBlack.vctPlanThreatDegree.clear();
				theApp.m_PlaneSpaceBlack.vctPlanThreatDegree.assign(PlaneData.vctPlanThreatDegree.begin(), PlaneData.vctPlanThreatDegree.end());
				for (i = 0; i < PlaneData.nPlanTypeN; ++i)
				{
					theApp.m_PlaneSpaceBlack.vvPlanGroupHao[i].clear();
					theApp.m_PlaneSpaceBlack.vvPlanGroupHao[i].assign(PlaneData.vvPlanGroupHao[i].begin(), PlaneData.vvPlanGroupHao[i].end());
					theApp.m_PlaneSpaceBlack.vvPlanGroupOBjType[i].clear();
					theApp.m_PlaneSpaceBlack.vvPlanGroupOBjType[i].assign(PlaneData.vvPlanGroupOBjType[i].begin(), PlaneData.vvPlanGroupOBjType[i].end());
					theApp.m_PlaneSpaceBlack.vvPlanEvent[i].clear();
					theApp.m_PlaneSpaceBlack.vvPlanEvent[i].assign(PlaneData.vvPlanEvent[i].begin(), PlaneData.vvPlanEvent[i].end());
				}
				
				m_PlaneSpaceLink.nPlanCumulativeN = 1;		//重新开始累积	
			}
		} 
		else			//没找到，为新模板,直接替换原节点内容
		{
			//更新飞机空间群链表
			m_PlaneSpaceLink.nPlanTypeN = PlaneData.nPlanTypeN;
			m_PlaneSpaceLink.nPlanSpacMBHao = PlaneData.nPlanSpacMBHao;
			m_PlaneSpaceLink.vctPlanGroupN.clear();
			m_PlaneSpaceLink.vctPlanGroupN.assign(PlaneData.vctPlanGroupN.begin(), PlaneData.vctPlanGroupN.end());
			m_PlaneSpaceLink.vctPlanThreatDegree.clear();
			m_PlaneSpaceLink.vctPlanThreatDegree.assign(PlaneData.vctPlanThreatDegree.begin(), PlaneData.vctPlanThreatDegree.end());
			for (i = 0; i < PlaneData.nPlanTypeN; ++i)
			{
				m_PlaneSpaceLink.vvPlanGroupHao[i].clear();
				m_PlaneSpaceLink.vvPlanGroupHao[i].assign(PlaneData.vvPlanGroupHao[i].begin(), PlaneData.vvPlanGroupHao[i].end());
				m_PlaneSpaceLink.vvPlanGroupOBjType[i].clear();
				m_PlaneSpaceLink.vvPlanGroupOBjType[i].assign(PlaneData.vvPlanGroupOBjType[i].begin(), PlaneData.vvPlanGroupOBjType[i].end());
				m_PlaneSpaceLink.vvPlanEvent[i].clear();
				m_PlaneSpaceLink.vvPlanEvent[i].assign(PlaneData.vvPlanEvent[i].begin(), PlaneData.vvPlanEvent[i].end());
			}
			nPlaneFlag = 1;
			//同时产生飞机黑板结构数据并更新
			theApp.m_PlaneSpaceBlack.lTimeStamp = 100000000;
			theApp.m_PlaneSpaceBlack.nPlanTypeN = PlaneData.nPlanTypeN;
			theApp.m_PlaneSpaceBlack.vctPlanGroupN.clear();
			theApp.m_PlaneSpaceBlack.vctPlanGroupN.assign(PlaneData.vctPlanGroupN.begin(), PlaneData.vctPlanGroupN.end());
			theApp.m_PlaneSpaceBlack.vctPlanThreatDegree.clear();
			theApp.m_PlaneSpaceBlack.vctPlanThreatDegree.assign(PlaneData.vctPlanThreatDegree.begin(), PlaneData.vctPlanThreatDegree.end());
			for (i = 0; i < PlaneData.nPlanTypeN; ++i)
			{
				theApp.m_PlaneSpaceBlack.vvPlanGroupHao[i].clear();
				theApp.m_PlaneSpaceBlack.vvPlanGroupHao[i].assign(PlaneData.vvPlanGroupHao[i].begin(), PlaneData.vvPlanGroupHao[i].end());
				theApp.m_PlaneSpaceBlack.vvPlanGroupOBjType[i].clear();
				theApp.m_PlaneSpaceBlack.vvPlanGroupOBjType[i].assign(PlaneData.vvPlanGroupOBjType[i].begin(), PlaneData.vvPlanGroupOBjType[i].end());
				theApp.m_PlaneSpaceBlack.vvPlanEvent[i].clear();
				theApp.m_PlaneSpaceBlack.vvPlanEvent[i].assign(PlaneData.vvPlanEvent[i].begin(), PlaneData.vvPlanEvent[i].end());
			}
			
			m_PlaneSpaceLink.nPlanCumulativeN = 1;		//重新开始累积	
		}
		//1.2 舰船类，同飞机类
		if (m_ShipSpaceLink.nPlanSpacMBHao == ShipData.nPlanSpacMBHao)			//找到,累加模板节点上的信息
		{
			//更新链表上旧节点内容
			m_ShipSpaceLink.nPlanTypeN = ShipData.nPlanTypeN;
			m_ShipSpaceLink.vctPlanGroupN.clear();
			m_ShipSpaceLink.vctPlanGroupN.assign(ShipData.vctPlanGroupN.begin(), ShipData.vctPlanGroupN.end());
			m_ShipSpaceLink.vctPlanThreatDegree.clear();
			m_ShipSpaceLink.vctPlanThreatDegree.assign(ShipData.vctPlanThreatDegree.begin(), ShipData.vctPlanThreatDegree.end());
			for (i = 0; i < PlaneData.nPlanTypeN; ++i)
			{
				m_ShipSpaceLink.vvPlanGroupHao[i].clear();
				m_ShipSpaceLink.vvPlanGroupHao[i].assign(ShipData.vvPlanGroupHao[i].begin(), ShipData.vvPlanGroupHao[i].end());
				m_ShipSpaceLink.vvPlanGroupOBjType[i].clear();
				m_ShipSpaceLink.vvPlanGroupOBjType[i].assign(ShipData.vvPlanGroupOBjType[i].begin(), ShipData.vvPlanGroupOBjType[i].end());
				m_ShipSpaceLink.vvPlanEvent[i].clear();
				m_ShipSpaceLink.vvPlanEvent[i].assign(ShipData.vvPlanEvent[i].begin(), ShipData.vvPlanEvent[i].end());
			}
			
			++m_PlaneSpaceLink.nPlanCumulativeN;	//累积数加1
		
			if (m_ShipSpaceLink.nPlanCumulativeN >= 5)
			{
				nShipFlag = 1;
				//同时，产生更新黑板模型的空间群结构数据
				theApp.m_ShipSpaceBlack.lTimeStamp = 100000000;
				theApp.m_ShipSpaceBlack.nPlanTypeN = ShipData.nPlanTypeN;
				theApp.m_ShipSpaceBlack.vctPlanGroupN.clear();
				theApp.m_ShipSpaceBlack.vctPlanGroupN.assign(ShipData.vctPlanGroupN.begin(), ShipData.vctPlanGroupN.end());
				theApp.m_ShipSpaceBlack.vctPlanThreatDegree.clear();
				theApp.m_ShipSpaceBlack.vctPlanThreatDegree.assign(ShipData.vctPlanThreatDegree.begin(), ShipData.vctPlanThreatDegree.end());
				for (i = 0; i < PlaneData.nPlanTypeN; ++i)
				{
					theApp.m_ShipSpaceBlack.vvPlanGroupHao[i].clear();
					theApp.m_ShipSpaceBlack.vvPlanGroupHao[i].assign(ShipData.vvPlanGroupHao[i].begin(), ShipData.vvPlanGroupHao[i].end());
					theApp.m_ShipSpaceBlack.vvPlanGroupOBjType[i].clear();
					theApp.m_ShipSpaceBlack.vvPlanGroupOBjType[i].assign(ShipData.vvPlanGroupOBjType[i].begin(), ShipData.vvPlanGroupOBjType[i].end());
					theApp.m_ShipSpaceBlack.vvPlanEvent[i].clear();
					theApp.m_ShipSpaceBlack.vvPlanEvent[i].assign(ShipData.vvPlanEvent[i].begin(), ShipData.vvPlanEvent[i].end());
				}
				
				m_PlaneSpaceLink.nPlanCumulativeN = 1;	//重新开始积累
			}
		} 
		else			//没找到，为新模板,直接替换原节点内容
		{
			//更新舰船空间群链表
			m_PlaneSpaceLink.nPlanSpacMBHao = ShipData.nPlanSpacMBHao;
			m_ShipSpaceLink.nPlanTypeN = ShipData.nPlanTypeN;
			m_ShipSpaceLink.vctPlanGroupN.clear();
			m_ShipSpaceLink.vctPlanGroupN.assign(ShipData.vctPlanGroupN.begin(), ShipData.vctPlanGroupN.end());
			m_ShipSpaceLink.vctPlanThreatDegree.clear();
			m_ShipSpaceLink.vctPlanThreatDegree.assign(ShipData.vctPlanThreatDegree.begin(), ShipData.vctPlanThreatDegree.end());
			for (i = 0; i < PlaneData.nPlanTypeN; ++i)
			{
				m_ShipSpaceLink.vvPlanGroupHao[i].clear();
				m_ShipSpaceLink.vvPlanGroupHao[i].assign(ShipData.vvPlanGroupHao[i].begin(), ShipData.vvPlanGroupHao[i].end());
				m_ShipSpaceLink.vvPlanGroupOBjType[i].clear();
				m_ShipSpaceLink.vvPlanGroupOBjType[i].assign(ShipData.vvPlanGroupOBjType[i].begin(), ShipData.vvPlanGroupOBjType[i].end());
				m_ShipSpaceLink.vvPlanEvent[i].clear();
				m_ShipSpaceLink.vvPlanEvent[i].assign(ShipData.vvPlanEvent[i].begin(), ShipData.vvPlanEvent[i].end());
			}
			//同时产生舰船黑板结构数据并更新
			nShipFlag = 1;
			theApp.m_ShipSpaceBlack.lTimeStamp = 100000000;
			theApp.m_ShipSpaceBlack.nPlanTypeN = ShipData.nPlanTypeN;
			theApp.m_ShipSpaceBlack.vctPlanGroupN.clear();
			theApp.m_ShipSpaceBlack.vctPlanGroupN.assign(ShipData.vctPlanGroupN.begin(), ShipData.vctPlanGroupN.end());
			theApp.m_ShipSpaceBlack.vctPlanThreatDegree.clear();
			theApp.m_ShipSpaceBlack.vctPlanThreatDegree.assign(ShipData.vctPlanThreatDegree.begin(), ShipData.vctPlanThreatDegree.end());
			for (i = 0; i < PlaneData.nPlanTypeN; ++i)
			{
				theApp.m_ShipSpaceBlack.vvPlanGroupHao[i].clear();
				theApp.m_ShipSpaceBlack.vvPlanGroupHao[i].assign(ShipData.vvPlanGroupHao[i].begin(), ShipData.vvPlanGroupHao[i].end());
				theApp.m_ShipSpaceBlack.vvPlanGroupOBjType[i].clear();
				theApp.m_ShipSpaceBlack.vvPlanGroupOBjType[i].assign(ShipData.vvPlanGroupOBjType[i].begin(), ShipData.vvPlanGroupOBjType[i].end());
				theApp.m_ShipSpaceBlack.vvPlanEvent[i].clear();
				theApp.m_ShipSpaceBlack.vvPlanEvent[i].assign(ShipData.vvPlanEvent[i].begin(), ShipData.vvPlanEvent[i].end());
			}
			
			m_PlaneSpaceLink.nPlanCumulativeN = 1;
		}
		//2 相同模板号中有新增的数据，更新黑板上的空间群节点数据
		//2.1 找到飞机类中新增的数据，更新

		//2.2 找到舰船类中新增的数据，更新
	}
	if (nPlaneFlag == 0 && nShipFlag == 0)
	{
		nFlag = 0;
	} 
	else
	{
		nFlag = 1;
	}
}



//////////////////////////////功能群//////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////////////////
//                               举手表决法  (已测试过，直接调用)                      //
//        注：将类型转化成整数                                                         //
//       输入: 混合类型总数N
//             类型组GiveType[]
//       输出：决策类型SumType
/////////////////////////////////////////////////////////////////////////////////////////
void CAlgorithm::ObjectType_Moretomin_Moudul(int N, VCT_INT& GiveType, int& SumType)
{
	int i,j,k,n;
	int temp[20] = {0};
	int Value[20] = {0};     //放统计的各类个数
	int OBjType[20] = {0};
	
	int Max, Hao;
	
	//先转放
	for(i = 0; i < N; i++)
	{
		temp[i] = GiveType[i];	
	}
	
	//将相同类的统计支持个数
	k = 0;//用于放不同类型数，从0开始
	for(i = 0; i < N; i++)
	{
		if(temp[i] != 0)//没处理过
		{		
			n = 1;//统计该类个数
			for(j = i+1; j < N; j++)
			{
				if(temp[i] == temp[j])
				{
					n++;
					temp[j] = 0;//置0				
				}		
			}//for j
			
			Value[k] = n;        //该类统计个数
			OBjType[k] = temp[i];//存放该类型
			k++;
		}//否则，已处理过	
	}//for i
	
	//再从k中找出最大者
	Max = Value[0];
	Hao = 0;
	for(i = 1; i < k; i++)
	{
		if(Max < Value[i])
		{
			Max = Value[i];
			Hao = i;		
		}	
	}//for i
	
	SumType = OBjType[Hao];//带回最终的类型输出
}


/////////////////////////////////////////////////////////////////////////////////////////
//                               功能群知识推理模块设计                                //
//********                    (2014-10-18  Liuyian)                           **********//
//             输入：                                                         *********//
//                   本次黑板上的空间群结构数据                               *********//
//                   功能群层推理知识库                                        ********//
//********     输出：产生功能群类、及数目                                    **********//
//********           产生功能群链表结构数据FunLink                           **********//
/////////////////////////////////////////////////////////////////////////////////////////
void CAlgorithm::FunctionGroup_Reason_PlatSituationEvent_datamodul(SPACE_BLACK& PlaneBlack, SPACE_BLACK& ShipBlack, FUN_GROUP_LINK& FunLink, int& nFlag)
{
	int i, j;
	int nFindFlag;
	int nGroupNum;
	int nPlatNum;
	int nObjtype;		//举手表决的结果
	int nPlatEvent;		//举手表决的结果
	VCT_INT vctPlaneModelID;		//保存飞机功能群模板号
	VCT_INT vctPlaneEvent;			//保存飞机功能群事件
	VCT_INT vctShipModelID;			//保存舰船功能群模板号
	VCT_INT vctShipEvent;			//保存舰船功能群事件
	//先处理飞机群
	VCT_INT vctObjtype;
	VCT_INT vctPlantEvent;

	vctPlaneModelID.clear();
	vctPlaneEvent.clear();
	vctShipModelID.clear();
	vctShipEvent.clear();

	vctObjtype.clear();
	vctPlantEvent.clear();
	for (nGroupNum = 0; nGroupNum < PlaneBlack.nPlanTypeN; ++nGroupNum)		//对飞机群进行循环
	{
		vctObjtype.clear();
		vctPlantEvent.clear();
		for (nPlatNum = 0; nPlatNum < PlaneBlack.vctPlanGroupN[nGroupNum]; ++nPlatNum)			//每个群中的每一个目标
		{
			//取目标类型和平台态势
			vctObjtype.push_back(PlaneBlack.vvPlanGroupOBjType[nGroupNum][nPlatNum]);
			vctPlantEvent.push_back(PlaneBlack.vvPlanEvent[nGroupNum][nPlatNum]);
		}
		//调用举手表决法,获得该群目标类型
		ObjectType_Moretomin_Moudul(nPlatNum, vctObjtype, nObjtype);
		//调用举手表决法,获得该群的态势
		ObjectType_Moretomin_Moudul(nPlatNum, vctPlantEvent, nPlatEvent);

		//查找知识库
		nFindFlag = 0;
		for (i = 0; i < theApp.m_DataBase.m_DataBaseData.FunModelID.size(); ++i)
		{
			if (nObjtype == theApp.m_DataBase.m_DataBaseData.vctDbFunKng[i][0] && nPlatEvent == theApp.m_DataBase.m_DataBaseData.vctDbFunKng[i][1])				//找到
			{
				vctPlaneModelID.push_back(theApp.m_DataBase.m_DataBaseData.FunModelID[i]);		//保存模板号
				vctPlaneEvent.push_back(theApp.m_DataBase.m_DataBaseData.FunModelID[i]);			//保存功能群事件
				nFindFlag = 1;
				break;
			}
		}
		//没有找到
		if (nFindFlag == 0)
		{
			vctPlaneEvent.push_back(10);			//不明
			vctPlaneModelID.push_back(-1);
		}
	}
	//再处理舰船群

	for (nGroupNum = 0; nGroupNum < ShipBlack.nPlanTypeN; ++nGroupNum)		//对舰船群进行循环
	{
		vctObjtype.clear();
		vctPlantEvent.clear();
		for (nPlatNum = 0; nPlatNum < ShipBlack.vctPlanGroupN[nGroupNum]; ++nPlatNum)			//每个群中的每一个目标
		{
			//取目标类型和平台态势
			vctObjtype.push_back(ShipBlack.vvPlanGroupOBjType[nGroupNum][nPlatNum]);
			vctPlantEvent.push_back(ShipBlack.vvPlanEvent[nGroupNum][nPlatNum]);
		}
		//调用举手表决法,获得该群目标类型
		ObjectType_Moretomin_Moudul(ShipBlack.vctPlanGroupN[nGroupNum], vctObjtype, nObjtype);
		//调用举手表决法,获得该群的态势
		ObjectType_Moretomin_Moudul(ShipBlack.vctPlanGroupN[nGroupNum], vctPlantEvent, nPlatEvent);
		
		//查找知识库
		nFindFlag = 0;
		for (i = 0; i < theApp.m_DataBase.m_DataBaseData.FunModelID.size(); ++i)
		{
			if (nObjtype == theApp.m_DataBase.m_DataBaseData.vctDbFunKng[i][0] && nPlatEvent == theApp.m_DataBase.m_DataBaseData.vctDbFunKng[i][1])				//找到
			{
				vctShipModelID.push_back(theApp.m_DataBase.m_DataBaseData.FunModelID[i]);		//保存模板号
				vctShipEvent.push_back(theApp.m_DataBase.m_DataBaseData.FunEventID[i]);			//保存功能群事件
				nFindFlag = 1;
				break;
			}
		}
		//没有找到
		if (nFindFlag == 0)
		{
			vctShipEvent.push_back(10);			//不明
			vctShipModelID.push_back(-1);
		}
		
	}

	//////////////////////产生链表结构数据/////////////////////////////////////
	
	FunLink.nFuncGroupN = PlaneBlack.nPlanTypeN + ShipBlack.nPlanTypeN;
	//产生飞机链表结构
	for (i = 0; i < PlaneBlack.nPlanTypeN; ++i)
	{
		FunLink.vctFuncMBHao.push_back(vctPlaneModelID[i]);			//模板号
		FunLink.vctFuncGpH.push_back(i);								//编号
		FunLink.vctFuncGroupTrackN.push_back(PlaneBlack.vctPlanGroupN[i]);		//群内目标数
		FunLink.vvFuncGroupHao.push_back(PlaneBlack.vvPlanGroupHao[i]);			//批号
		FunLink.vvFuncGroupOBjType.push_back(PlaneBlack.vvPlanGroupOBjType[i]);	//类型
		FunLink.vctFuncThreatDegree.push_back(PlaneBlack.vctPlanThreatDegree[i]);	//威胁度
		FunLink.vctFuncGroupEvent.push_back(vctPlaneEvent[i]);					//态势
	}

	//产生舰船链表结构
	for (i = PlaneBlack.nPlanTypeN; i < m_FunLink.nFuncGroupN; ++i)
	{
		j = i - PlaneBlack.nPlanTypeN;
		FunLink.vctFuncMBHao.push_back(vctPlaneModelID[i]);			//模板号
		FunLink.vctFuncGpH.push_back(i);								//编号
		FunLink.vctFuncGroupTrackN.push_back(ShipBlack.vctPlanGroupN[j]);		//群内目标数
		FunLink.vvFuncGroupHao.push_back(ShipBlack.vvPlanGroupHao[j]);			//批号
		FunLink.vvFuncGroupOBjType.push_back(ShipBlack.vvPlanGroupOBjType[j]);	//类型
		FunLink.vctFuncThreatDegree.push_back(ShipBlack.vctPlanThreatDegree[j]);	//威胁度
		FunLink.vctFuncGroupEvent.push_back(vctPlaneEvent[i]);					//态势
	}
	FunLink.nFuncGroupMBNum = m_FunLink.nFuncGroupN;

	nFlag = 1;
}



/////////////////////////////////////////////////////////////////////////////////////////
//                功能群链表与黑板节点创建与更新模块设计                               //
//********                    (2014-10-20  Liuyian)                          **********//
//             输入： nFuncFlag=0表示首次，否则为非首次                       *********//
//                   本次产生的功能群链表结构数据                             *********//
//                   上次保存的功能群链表结构数据                              ********//
//                   上次保存的功能群黑板结构数据                              ********//
//********     输出：更新功能群链表数据                                      **********//
//********           产生是否触发更新黑板,更新黑板结构数据nFlag              **********//
/////////////////////////////////////////////////////////////////////////////////////////
void CAlgorithm::FunctionGroup_LinkProcess_PlatSituationEvent_datamodul(int nFuncFlag, FUN_GROUP_LINK& FunLink, int& nFlag)
{
	int i, j, k;
	VCT_INT vctLink;			//功能群链表中未被处理的节点
	VCT_INT vctNowData;			//当前得到的功能群中未被处理的节点
	vctLink.assign(m_FunLink.nFuncGroupN, 0);
	vctNowData.assign(FunLink.nFuncGroupN, 0);
	if (nFuncFlag == 0)			//首次
	{
		//将数据写入链表
		m_FunLink.nFuncGroupMBNum = FunLink.nFuncGroupMBNum;
		m_FunLink.nFuncGroupN = FunLink.nFuncGroupN;
		m_FunLink.vctFuncGpH = FunLink.vctFuncGpH;
		m_FunLink.vctFuncGroupEvent = FunLink.vctFuncGroupEvent;
		m_FunLink.vctFuncGroupTrackN = FunLink.vctFuncGroupTrackN;
		m_FunLink.vctFuncMBHao = FunLink.vctFuncMBHao;
		m_FunLink.vctFuncThreatDegree = FunLink.vctFuncThreatDegree;
		m_FunLink.vvFuncGroupHao = FunLink.vvFuncGroupHao;
		m_FunLink.vvFuncGroupOBjType = FunLink.vvFuncGroupOBjType;
		m_FunLink.vctFuncCumulativeN.assign(FunLink.nFuncGroupN, 1);
		//将数据写入黑板
		theApp.m_FunBlack.lTimeStamp = 100000000;
		theApp.m_FunBlack.nFuncGroupN = FunLink.nFuncGroupN;
		theApp.m_FunBlack.vctFuncGpHao = FunLink.vctFuncGpH;
		theApp.m_FunBlack.vctFuncGroupEvent = FunLink.vctFuncGroupEvent;
		theApp.m_FunBlack.vctFuncGroupTrackN = FunLink.vctFuncGroupTrackN;
		theApp.m_FunBlack.vctFuncThreatDegree = FunLink.vctFuncThreatDegree;
		theApp.m_FunBlack.vvFuncGroupTrackHao = FunLink.vvFuncGroupHao;
		theApp.m_FunBlack.vvFuncGroupOBjType = FunLink.vvFuncGroupOBjType;

		nFlag = 1;			//触发下一层
	}
	else						//非首次
	{
		//1.  更新旧链表
		for (i = 0; i < FunLink.nFuncGroupN; ++i)
		{
			for (j = 0; j < m_FunLink.nFuncGroupN; ++j)
			{
				if (FunLink.vctFuncMBHao[i] == m_FunLink.vctFuncMBHao[j])		//找到,更新此模板对应的功能群的信息
				{
					vctNowData[i] = 1;
					vctLink[j] = 1;

					//1.1 更新旧节点内容,即替换该功能群内容
					m_FunLink.vctFuncGroupTrackN[j] = FunLink.vctFuncGroupTrackN[i];
					m_FunLink.vvFuncGroupHao[j].clear();
					m_FunLink.vvFuncGroupHao[j] = FunLink.vvFuncGroupHao[i];
					m_FunLink.vvFuncGroupOBjType[j].clear();
					m_FunLink.vvFuncGroupOBjType[j] = FunLink.vvFuncGroupOBjType[i];
					m_FunLink.vctFuncThreatDegree[j] = FunLink.vctFuncThreatDegree[i];
					m_FunLink.vctFuncGroupEvent[j] = FunLink.vctFuncGroupEvent[i];
					m_FunLink.vctFuncCumulativeN[j] = m_FunLink.vctFuncCumulativeN[j] + 1;
					//1.2 产生更新黑板模型的功能群结构数据
					if (m_FunLink.vctFuncCumulativeN[j] >= 5)
					{
						 
						for (k = 0; k < theApp.m_FunBlack.nFuncGroupN; ++k)
						{
							if (m_FunLink.vctFuncGpH[j] == theApp.m_FunBlack.vctFuncGpHao[k])		//找到该功能群
							{
								theApp.m_FunBlack.lTimeStamp = 100000000;
								theApp.m_FunBlack.vctFuncGpHao[k] = m_FunLink.vctFuncGpH[j];
								theApp.m_FunBlack.vctFuncGroupEvent[k] = m_FunLink.vctFuncGroupEvent[j];
								theApp.m_FunBlack.vctFuncGroupTrackN[k] = m_FunLink.vctFuncGroupTrackN[j];
								theApp.m_FunBlack.vctFuncThreatDegree[k] = m_FunLink.vctFuncThreatDegree[j];
								theApp.m_FunBlack.vvFuncGroupTrackHao[k].assign(m_FunLink.vvFuncGroupHao[j].begin(), m_FunLink.vvFuncGroupHao[j].end());
								theApp.m_FunBlack.vvFuncGroupOBjType[k].assign(m_FunLink.vvFuncGroupOBjType[j].begin(), m_FunLink.vvFuncGroupOBjType[j].end());
								m_FunLink.vctFuncCumulativeN[j] = 1;
								break;
							}
						}
					}
				}
			}
			nFlag = 1;
		}
		//2.  处理新增节点
		for (i = 0; i < FunLink.nFuncGroupN; ++i)
		{
			if (vctNowData[i] == 0)			//新增节点
			{
				//1. 追加到链表之后
				m_FunLink.vctFuncGpH.push_back(m_FunLink.vctFuncGpH[i]);
				m_FunLink.vctFuncGroupEvent.push_back(FunLink.vctFuncGroupEvent[i]);
				m_FunLink.vctFuncGroupTrackN.push_back(FunLink.vctFuncGroupTrackN[i]);
				m_FunLink.vctFuncMBHao.push_back(FunLink.vctFuncMBHao[i]);
				m_FunLink.vctFuncThreatDegree.push_back(FunLink.vctFuncThreatDegree[i]);
				m_FunLink.vvFuncGroupHao.push_back(FunLink.vvFuncGroupHao[i]);
				m_FunLink.vvFuncGroupOBjType.push_back(FunLink.vvFuncGroupOBjType[i]);
				m_FunLink.nFuncGroupN++;
				m_FunLink.nFuncGroupMBNum++;
				m_FunLink.vctFuncCumulativeN.push_back(1);
				
				//2. 更新黑板
				theApp.m_FunBlack.lTimeStamp = 100000000;
				theApp.m_FunBlack.vctFuncGpHao.push_back(FunLink.vctFuncGpH[i]);
				theApp.m_FunBlack.vctFuncGroupEvent.push_back(FunLink.vctFuncGroupEvent[i]);
				theApp.m_FunBlack.vctFuncGroupTrackN.push_back(FunLink.vctFuncGroupTrackN[i]);
				theApp.m_FunBlack.vctFuncThreatDegree.push_back(FunLink.vctFuncThreatDegree[i]);
				theApp.m_FunBlack.vvFuncGroupTrackHao.push_back(FunLink.vvFuncGroupHao[i]);
				theApp.m_FunBlack.vvFuncGroupOBjType.push_back(FunLink.vvFuncGroupOBjType[i]);
				theApp.m_FunBlack.nFuncGroupN++;
			}
				nFlag = 1;
		}
		//3.  更新黑板数据
			//3.1  先更新已经存在的节点

			//3.2  再更新新出现的节点
	
	}
}




///////////////////////////////相互作用群///////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////////////////
//                      相互作用群知识推理与链表创建处理模块设计                       //
//********                    (2014-08-5  Liuyian)                           **********//
//             输入：                                                         *********//
//                   本次黑板上的功能群结构数据                               *********//
//                   相互作用群层推理知识库                                    ********//
//********     输出：产生相互作用群链表结构数据                              **********//
//                   触发更新链表和黑板数据模块                                        //
/////////////////////////////////////////////////////////////////////////////////////////
void CAlgorithm::Interaction_KnowlegeReason_Process_datamodul(FUN_GROUP_BLACK& m_FunBlack, INTERGROUPLINK& NodeLink)
{
	int i, j;
	int nImFunGNum;			//相互作用群中可能的功能群的个数
	//创建结构
	//相互作用知识库:  1警戒、2：巡逻，3：攻击、4：拦截，5：轰炸、6：突防、7：干扰、8：预警,9:侦察      
    //1: 读取当前功能群
	for (i = 0; i < m_FunBlack.nFuncGroupN; ++i)
	{
// 		nImFunGNum = 0;
// 		++nImFunGNum;
// 		//1.1:查找知识库，将所有含此功能群的知识找出，并将其中相关的功能群编号放到一个数组中
// 		for ()				 //读取知识库
// 		{
// 			//1.1.1:  先查找该条知识中是否有此功能群态势设置
// 			for ()			//知识项循环
// 			{
// 
// 				if ()				//有该项
// 				{
// 				}
// 			}
// 			//1.1.2:  对于该条找到的知识，将其行中对应的所有态势读出
// 			if ()
// 			{
// 				for ()		//知识项循环
// 				{
// 				}
// 			}
// 		}
// 		//1.2: 先处理以该功能为基础的,排除数组FuncGroupEventValue[i][n]中临时存放的,有冗余的态势（每种态势只保留1个）
// 		for ()
// 		{
// 		}
	}

	//2: 相互作用群产生，合并上面保存的TempEventValue[i][m[i]]中的功能

	//3: 再处理上面合并中冗余的

	//4: 再根据相互作用群中的各态势，补上各子群的其他参数,同时产生链表结构数据
}




/////////////////////////////////////////////////////////////////////////////////////////
//                           相互作用群链表与黑板处理模块设计                          //
//********                    (2014-10-22  Liuyian)                          **********//
//             输入：InterFlag首次标志，0为首次                               *********//
//                   本次产生的相互作用群的个数与结构数据NodeLink             *********//
//                   上次保存的相互作用群结构数据                              ********//
//********     输出：更新或创建相互作用群链表与黑板数据                      **********//
/////////////////////////////////////////////////////////////////////////////////////////
void CAlgorithm::InteractGroup_LinkProcess_SituationEvent_datamodul(int nInterFlag, INTERGROUPLINK& NodeLink)
{
	int i, j, k, m, g;
	INTERGROUP LinkTemp;
	INTERBLACKNODE BlackTemp;
	VCT_INT vctOldFlag;		//标记m_InterGBlack未被处理的作用群（用0表示）
	VCT_INT vctNewFlag;		//标记NodeLink中新增（未被处理）的作用群,0表示未被处理

	vctOldFlag.assign(theApp.m_InterGBlack.size(), 0);
	vctNewFlag.assign(NodeLink.size(), 0);
	if (nInterFlag == 0)				//首次
	{
		//1.1 直接存放到链表结构中
		for (i = 0; i < NodeLink.size(); ++i)
		{
			LinkTemp.nInteGroupSeriNum = NodeLink[i].nInteGroupSeriNum;
			LinkTemp.nInteCumulativeN = 1;
			LinkTemp.nInteractGroupSGN = NodeLink[i].nInteractGroupSGN;
			//用=赋值的时候会把原来的容器的内容全部清除，顾此处不用clear
			LinkTemp.vctInteGroupHao = NodeLink[i].vctInteGroupHao;
			LinkTemp.vctInteGroupTrackNum = NodeLink[i].vctInteGroupTrackNum;
			LinkTemp.vctInterEvent = NodeLink[i].vctInterEvent;
			LinkTemp.vvInterOBjType = NodeLink[i].vvInterOBjType;
			LinkTemp.vvIntertrackHao = NodeLink[i].vvIntertrackHao;
			m_InterGLink.push_back(LinkTemp);
		}

		//1.2 同时,也直接写入到黑板上的相互作用群结构数据中
		for (i = 0; i < NodeLink.size(); ++i)
		{
			BlackTemp.lTimeStamp = 10000000;
			BlackTemp.dSumThreatDegree = NodeLink[i].dSumThreatDegree;
			BlackTemp.nInteGroupSeriNum = NodeLink[i].nInteGroupSeriNum;
			BlackTemp.nInteractGroupSGN = NodeLink[i].nInteractGroupSGN;
			BlackTemp.vctInteGroupHao = NodeLink[i].vctInteGroupHao;
			BlackTemp.vctInteGroupTrackNum = NodeLink[i].vctInteGroupTrackNum;
			BlackTemp.vctInterEvent = NodeLink[i].vctInterEvent;
			BlackTemp.vvInterOBjType = NodeLink[i].vvInterOBjType;
			BlackTemp.vvIntertrackHao = NodeLink[i].vvIntertrackHao;
			theApp.m_InterGBlack.push_back(BlackTemp);
		}
	}
	else
	{
		//2.1 对于相互作用群更新处理：由于产生中是按同一子群功能态势只在一个相互作用群中，故查找时只要有一个子群匹配，就更新之
		for (i = 0; i < NodeLink.size(); ++i)		//相互作用群个数
		{
			for (j = 0; j < NodeLink[i].nInteractGroupSGN; ++j)			//各个子群
			{
				for (k = 0; k < m_InterGLink.size(); ++k)		//现在黑板中的相互作用群的个数
				{
					for (m = 0; m < m_InterGLink[i].nInteractGroupSGN; ++m)	//黑板中某个相互作用群中的所有子群
					{
						if (NodeLink[i].vctInterEvent[j] == theApp.m_InterGBlack[k].vctInterEvent[m])			//找到
						{
							vctNewFlag[i] = 1;
							vctOldFlag[k] = 1;
							//更新旧节点内容,即用当前的替换该旧作用群中部分内容(编号仍用旧的)
							m_InterGLink[k].nInteractGroupSGN = NodeLink[i].nInteractGroupSGN;
							m_InterGLink[k].dSumThreatDegree = NodeLink[i].dSumThreatDegree;
							m_InterGLink[k].vctInteGroupTrackNum = NodeLink[i].vctInteGroupTrackNum;
							m_InterGLink[k].vctInteGroupHao = NodeLink[i].vctInteGroupHao;
							m_InterGLink[k].vctInterEvent = NodeLink[i].vctInterEvent;
							m_InterGLink[k].vvInterOBjType = NodeLink[i].vvInterOBjType;
							m_InterGLink[k].vvIntertrackHao = NodeLink[i].vvIntertrackHao;
							m_InterGLink[k].nInteCumulativeN = m_InterGLink[k].nInteCumulativeN + 1;
							if (m_InterGLink[k].nInteCumulativeN >= 5)		//更新黑板
							{
								//产生更新黑板模型的相互作用群结构数据
								for (g = 0; g = theApp.m_InterGBlack.size(); ++g)			//在黑板中找到相同编号的数据
								{
									if (m_InterGLink[k].nInteGroupSeriNum = theApp.m_InterGBlack[g].nInteGroupSeriNum)
									{
										theApp.m_InterGBlack[g].lTimeStamp = 10000000;
										theApp.m_InterGBlack[g].dSumThreatDegree = NodeLink[i].dSumThreatDegree;
										theApp.m_InterGBlack[g].nInteGroupSeriNum = NodeLink[i].nInteGroupSeriNum;
										theApp.m_InterGBlack[g].nInteractGroupSGN = NodeLink[i].nInteractGroupSGN;
										theApp.m_InterGBlack[g].vctInteGroupHao = NodeLink[i].vctInteGroupHao;
										theApp.m_InterGBlack[g].vctInteGroupTrackNum = NodeLink[i].vctInteGroupTrackNum;
										theApp.m_InterGBlack[g].vctInterEvent = NodeLink[i].vctInterEvent;
										theApp.m_InterGBlack[g].vvInterOBjType = NodeLink[i].vvInterOBjType;
										theApp.m_InterGBlack[g].vvIntertrackHao = NodeLink[i].vvIntertrackHao;
										g = g + theApp.m_InterGBlack.size();
									}
								}
							}
							//下面的设置是为了推出循环
							m = m + theApp.m_InterGBlack[i].nInteractGroupSGN;
							k = k + m_InterGLink.size();
						}
					}
				}
			}
		}
		//2.2: 处理新增节点,即新增相互作用群
       	//对于相互作用群更新处理：由于产生中是按同一子群功能态势只在一个相互作用群中，故查找时只要有一个子群匹配，就更新之
		for (i = 0; i < NodeLink.size(); ++i)
		{
			if (vctNewFlag[i] == 0)				//有新增节点
			{
				//将当前节点追加到链表后面
				LinkTemp.nInteGroupSeriNum = NodeLink.size();
				LinkTemp.nInteCumulativeN = 1;
				LinkTemp.nInteractGroupSGN = NodeLink[i].nInteractGroupSGN;
				//用=赋值的时候会把原来的容器的内容全部清除，顾此处不用clear
				LinkTemp.vctInteGroupHao = NodeLink[i].vctInteGroupHao;
				LinkTemp.vctInteGroupTrackNum = NodeLink[i].vctInteGroupTrackNum;
				LinkTemp.vctInterEvent = NodeLink[i].vctInterEvent;
				LinkTemp.vvInterOBjType = NodeLink[i].vvInterOBjType;
				LinkTemp.vvIntertrackHao = NodeLink[i].vvIntertrackHao;
				m_InterGLink.push_back(LinkTemp);

				//产生新的黑板数据并更新
				BlackTemp.lTimeStamp = 10000000;
				BlackTemp.dSumThreatDegree = NodeLink[i].dSumThreatDegree;
				BlackTemp.nInteGroupSeriNum = NodeLink[i].nInteGroupSeriNum;
				BlackTemp.nInteractGroupSGN = NodeLink[i].nInteractGroupSGN;
				BlackTemp.vctInteGroupHao = NodeLink[i].vctInteGroupHao;
				BlackTemp.vctInteGroupTrackNum = NodeLink[i].vctInteGroupTrackNum;
				BlackTemp.vctInterEvent = NodeLink[i].vctInterEvent;
				BlackTemp.vvInterOBjType = NodeLink[i].vvInterOBjType;
				BlackTemp.vvIntertrackHao = NodeLink[i].vvIntertrackHao;
				theApp.m_InterGBlack.push_back(BlackTemp);
			}
		}


		//2.3: 更新黑板上的节点数据

			//2.3.1: 先更新存在的节点

			//2.3.2: 再处理新增的黑板节点
	}
		
}