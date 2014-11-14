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

//////////////////////////////�����¼���//////////////////////////////////////////////////////////////////

//**************************************************************************************************//
//                    Ŀ�����ݿ���                                                                  //
//    ���룺Ŀ���ַ����Ҫ����������                                                                //
//    �����                                                                                        // 
//    ����ֵ��0��ʾ��������1��ʾ��ȷ����                                                          //
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
//                    Ŀ�����ݻ���ģ��                                                              //
//    ���룺��ǰ�ں��·���Ϣ ����������ռ�                                                         //
//    �������������ռ�                                                                            // 
//    ����ֵ��0��ʾ��������1��ʾ��ȷ����                                                          //
//**************************************************************************************************//
int CAlgorithm::BufferData(VCT_Cooperative_FUSIDENTIINFOR& ForeBufferData, VCT_Cooperative_FUSIDENTIINFOR& NowBufferData, VCT_Cooperative_FUSIDENTIINFOR NowData)
{
	//���յ�����Ϊ��
	if (NowData.empty())
	{
		return 0;
	}
	VCT_Cooperative_FUSIDENTIINFOR::iterator iteNow;
	VCT_Cooperative_FUSIDENTIINFOR::iterator iteData;
	
	//��NowBufferData�е����ݿ�����ForeBufferData��
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
//                    Ŀ���ٶȼ���ģ��                                                              //
//    ���룺��ǰ�ں��·���Ϣ �˴�vector����Ҫ����Ŀ���ٶȵ�����                                     //
//    �������ǰĿ���ں���Ϣ��+������ٶ�                                                           // 
//    ����ֵ��0��ʾ��������1��ʾ��ȷ����                                                          //
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
//                    Ŀ����ٶȼ���ģ��                                                              //
//    ���룺��ǰ�ں��·���Ϣ �˴�������vector��                                                     //
//            TaishiFore��ʾǰһʱ�����ݣ�TaishiNow��ʾ��ǰʱ�̵�����                               //
//    �����������ļ��ٶ�ֵ���뵽TaishiNow��                                                       //
//    ����ֵ��0��ʾ��������1��ʾ��ȷ����                                                          //
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
//                    ������в�ȼ���ģ���������ģ��                                                //
//    ���룺TaishiNow��ʾ��ǰʱ�̵�����                                                             //
//    ��������������в��ֵ���뵽TaishiNow��                                                       //
//    ����ֵ���ۺ���в��                                                                            //
//**************************************************************************************************//

// 1ս������2 ��ը����3�߻��� �������� ����Ϊ��1�ࣩ
// 4Ԥ������   ����Ϊ��2�ࣩ
// 5������6���Ż�7 ֱ����(������Ǳ�������˻�������)   ����Ϊ��3�ࣩ
// 8 ��ͧ             ����4�ࣩ
// 9ս������������5�ࣩ
// 10�Ƶ�����  ����6�ࣩ

double CAlgorithm::TrackThreatDegree(VCT_Cooperative_FUSIDENTIINFOR::iterator iteNow)
{
	double ThreRd,ThreHigh,ThreVSpeed,ThreAddSpeed,ThreAzmith,ThreType;//��Ŀ�꺽���е���������в��
	double SumThredg;    //����ʱ��в�Ⱥ�
	double temp;

	//������в��ģ������
	if(iteNow->stFusTrack.nTgtType != 4)    //��4��
	{
		if(iteNow->stFusTrack.dRange > 60000)     //����60km
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
	else    //�ɻ���������
	{
		if(iteNow->stFusTrack.dRange > 200000)   //����200km
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
		
	//�߶���в��ģ������
	if(iteNow->stFusTrack.nTgtType == 4)
	{
		  ThreHigh = 0;
	}
	else//���򣬷ɻ���
	{
	     if(iteNow->stFusTrack.dHeight <= 100)//�߶�100m
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

	//�ٶ���в��ģ������
	if(iteNow->stFusTrack.nTgtType == 4)
	{
					 
	    if(iteNow->stFusTrack.dVSpeed > 60)//�ٶ�
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
	else if(iteNow->stFusTrack.nTgtType == 1 || iteNow->stFusTrack.nTgtType == 2 || iteNow->stFusTrack.nTgtType == 3)//�ɻ�
	{
			  
	    if(iteNow->stFusTrack.dVSpeed > 1.8*340) //�ٶ�1.8Ma
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
	else  //������
	{
		if(iteNow->stFusTrack.dVSpeed > 2.5*340)//�ٶ�2.5Ma
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

	//���ٶ���в��ģ������
	if(iteNow->stFusTrack.dAddSpeed <= 5)//���ٶ�
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
	 //Ŀ�꺽����в��ģ������      Azimuth���������NewAzimuthĿ�꺽��
//	 temp = fabs(NewAzimuth - Azimuth); //����
	 temp = fabs(3 - iteNow->stFusTrack.dCourse); //����
	 if(temp <= 3*PI_4/180)               //���ٶ�
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

	 //Ŀ��������в��ģ������
	 if(iteNow->stFusTrack.nTgtType == 5)   //����
	 {
		 ThreType = 1.0;
	 }
	 else if(iteNow->stFusTrack.nTgtType == 6)   // �Ƶ�����
	 {
		 ThreType = 0.2025;
	 }
     else if(iteNow->stFusTrack.nTgtType == 1)  //'ս������ ��ը�����߻��� ��������'
	 {
		 ThreType = 0.4022;
	 }
     else if(iteNow->stFusTrack.nTgtType == 2)   //'Ԥ����'
	 {
		 ThreType = 0.5774;
	 }
	 else if(iteNow->stFusTrack.nTgtType == 3)   //'������6���Ż�7 ֱ����'
	 {
		 ThreType = 0.1001;
	 }
	 else
	 {
		 ThreType = 0.0001;
	 }

     SumThredg=ThreRd + ThreHigh + ThreVSpeed + ThreAddSpeed + ThreAzmith + ThreType;
     
	 return (SumThredg/6);  //��һ������Ȩ,//����: ��Ŀ�꺽�����ۺ���в��

}


//**************************************************************************************************//
//                    ESM��в�ȼ���ģ���������ģ��                                                //
//    ���룺TaishiNow��ʾ��ǰʱ�̵�����                                                             //
//    ��������������в��ֵ���뵽TaishiNow��                                                       //
//    ����ֵ��ESM��в��                                                                            //
//**************************************************************************************************//
double CAlgorithm::ESMThreatDegree(VCT_Cooperative_FUSIDENTIINFOR::iterator iteNow)
{
	double ThreFre,ThrePA,ThrePw,ThrePRI,ThreScan;                     //��ESM�е���������в��
	double SumThredg;    //����ʱ��в�Ⱥ�
	double dAllThredg(1.0);   //ESM��в��
	VCT_ESM_MSG::iterator iteESM;
	
	for(iteESM = iteNow->vctFusEsm.begin(); iteESM != iteNow->vctFusEsm.end(); ++iteESM)
	{
		//����Ƶ��
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
		//�������
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
		//����
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
		//��Ƶ
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
		//����ɨ������
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
//                    Ŀ����в�ȼ���ģ��                                                            //
//    ���룺TaishiNow��ʾ��ǰʱ�̵�����                                                             //
//    ��������������в��ֵ���뵽TaishiNow��                                                       //
//    ����ֵ��0��ʾ��������1��ʾ��ȷ����                                                          //
//**************************************************************************************************//
int CAlgorithm::ThreatDegree(VCT_Cooperative_FUSIDENTIINFOR& TaishiNow)
{
	double dTgtThrDg;  //Ŀ����в��
	VCT_Cooperative_FUSIDENTIINFOR::iterator iteNow;
	
// 	if (TaishiNow == NULL)
// 	{
// 		return 0;
// 	}
	
	for (iteNow = TaishiNow.begin(); iteNow != TaishiNow.end(); ++iteNow)
	{
		if (iteNow->lAutonum < 3000) //3000һ�±�ʾ��Ŀ��δ����
		{
			iteNow->stFusTrack.dThrDg = TrackThreatDegree(iteNow);
		} 
		else if (iteNow->lAutonum >3000 && iteNow->lAutonum < 8000) 
		{
			//��Ӧ�ó��ִ������
		} 
		else                               //��Ŀ�����
		{
			dTgtThrDg = 1 - (1 - TrackThreatDegree(iteNow)) * ESMThreatDegree(iteNow);
			iteNow->stFusTrack.dThrDg = dTgtThrDg;
		}
	}
	
	return 1;
}


//**************************************************************************************************//
//                    ������һ��vector���ҵ��뵱ǰ����ͬ�����ŵ�����                                //    
//                    ������һ��vector���ҵ���ǰ���ݵ�ǰһʱ�̵�����                                //
//    ���룺������lAutonum��ǰһʱ�̵�����ForeData                                                  //
//    �����                                                                                        //
//    ����ֵ��ָ��ǰһʱ�����ݵĵ�����,û���ҵ�����ForeData.end()                                   //
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
//                    ������һ��vector���ҵ��뵱ǰ����ͬ�����ŵ�����                                //    
//                    ������һ��vector���ҵ���ǰ���ݵ�ǰһʱ�̵�����                                //
//    ���룺ESM����lAutonum��ǰһʱ�̵�����vctFusEsm                                                //
//    �����                                                                                        //
//    ����ֵ��ָ��ǰһʱ�����ݵĵ�����,û���ҵ�����vctFusEsm.end()                                   //
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
//                    ������һ��vector���ҵ��뵱ǰ����ͬ�����ŵ�����                                //    
//                    ������һ��vector���ҵ���ǰ���ݵ�ǰһʱ�̵�����                                //
//    ���룺COM����lAutonum��ǰһʱ�̵�����vctFusCom                                                //
//    �����                                                                                        //
//    ����ֵ��ָ��ǰһʱ�����ݵĵ�����,û���ҵ�����vctFusCom.end()                                   //
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
//                                           ��������
//                                   ֪ʶ��Ļ����¼������Ƹ�ʽ
/////////////////////////////////////////��������////////////////////////////////////////////////////////
//     ����      �߶�          �ٶ�         ���ٶ�        ����          //    �����˶�̬�ƣ�����
//                                                                      //
//                                                                      //
//����̬�ƣ�1������ֱ���˶���2������ֱ�����С�3�����塢4��������5�����䡢6��Զ�뱾����7���ƽ�������
//          8��λ�ù̶���9����Ŀ��(�����֪ʶ����)��10��Ŀ����ʧ(�����֪ʶ����),11������(�����֪ʶ����)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CAlgorithm::KnowLege_Database_Track_EventReason(VCT_INT& vctTrackEvent, int& nModelID, int& nEventType)
{   
	int i(0);
	int nPosition(-1);              //ģ������ڵ��±�
	int nMax;                   //ͳ�����ֵ
//	int nEvtID;                 //�����ݿ��ȡ���¼��ţ�Ҫ���ģ�����������
	int nSum;
	VV_INT::iterator ite_vDb;
	VCT_INT::iterator itedbevt;
	VCT_INT::iterator iteevt;
	VCT_INT::iterator iteSun;
	VCT_INT vctDbTrackEvt;      //������ݿ��к����¼��ĸ�������ֵ
	VCT_INT vctEvtID;           //��Ż����¼����ͣ������ݿ�ʱ�Ѵ��Ŀǰ��10��
	VCT_INT vctModelID;         //���ģ���
	VCT_INT vctSun;             //�����ۼ�ֵ
	vctDbTrackEvt.clear();
	vctEvtID.clear();
	vctModelID.clear();
	vctSun.clear();
	for (ite_vDb = theApp.m_DataBase.m_DataBaseData.vctDbTrackKng.begin(); ite_vDb != theApp.m_DataBase.m_DataBaseData.vctDbTrackKng.end(); ++ite_vDb)    //ѭ����ȡ���ݿ��е�ÿһ��֪ʶ
	{		
		//���㵱ǰ�����¼��ʹ����ݿ���ȡ�����¼���ƥ��ֵ
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
	//ȡ����ƥ��ֵ��������һ����Ϊ�����¼�
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
	if (nPosition > -1)  //˵���ҵ�
	{
		//ȡ��nPosition��Ӧ��֪ʶ���еĻ����¼������úڰ�����¼��ṹ����,��Ϊ"�ڰ���Ϣ"(ע���ڰ��ϵ���Ϣ���ڽ�����ʾ�����)
		nModelID = vctModelID.at(nPosition);
		nEventType = vctEvtID.at(nPosition);
	}
	else     //û���ҵ�
	{
		nModelID = -1;
		nEventType = 11;
	}
}

void CAlgorithm::KnowLege_Database_ESM_EventReason(VCT_INT& vctTrackEvent, int& nModelID, int& nEventType)
{
	int i(0);
	int nPosition(-1);              //ģ������ڵ��±�
	int nMax;                   //ͳ�����ֵ
//	int nEvtID;                 //�����ݿ��ȡ���¼��ţ�Ҫ���ģ�����������
	int nSum;
	VV_INT::iterator ite_vDb;
	VCT_INT::iterator itedbevt;
	VCT_INT::iterator iteevt;
	VCT_INT::iterator iteSun;
	VCT_INT vctDbTrackEvt;      //������ݿ��к����¼��ĸ�������ֵ
	VCT_INT vctEvtID;           //��Ż����¼����ͣ������ݿ�ʱ�Ѵ��Ŀǰ��?��
	VCT_INT vctModelID;         //���ģ���
	VCT_INT vctSun;             //�����ۼ�ֵ
	vctDbTrackEvt.clear();
	vctEvtID.clear();
	vctModelID.clear();
	vctSun.clear();
	//���㵱ǰESM�¼��ʹ����ݿ���ȡ�����¼���ƥ��ֵ
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
	//ȡ����ƥ��ֵ��������һ����ΪESM�¼�
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
	if (nPosition > -1)  //˵���ҵ�
	{
		//ȡ��nPosition��Ӧ��֪ʶ���еĻ����¼������úڰ�����¼��ṹ����,��Ϊ"�ڰ���Ϣ"(ע���ڰ��ϵ���Ϣ���ڽ�����ʾ�����)
		nModelID = vctModelID.at(nPosition);
		nEventType = vctEvtID.at(nPosition);
	}
	else     //����˵��������Ч,Ĭ�ϻ����¼�"����",û��ģ���
	{
		nModelID = -1;
		nEventType = 7;
	}
}


void CAlgorithm::KnowLege_Database_COM_EventReason(VCT_INT& vctTrackEvent, int& nModelID, int& nEventType)
{
	int i(0);
	int nPosition(-1);              //ģ������ڵ��±�
	int nMax;                   //ͳ�����ֵ
//	int nEvtID;                 //�����ݿ��ȡ���¼��ţ�Ҫ���ģ�����������
	int nSum;
	VV_INT::iterator ite_vDb;
	VCT_INT::iterator itedbevt;
	VCT_INT::iterator iteevt;
	VCT_INT::iterator iteSun;
	VCT_INT vctDbTrackEvt;      //������ݿ��к����¼��ĸ�������ֵ
	VCT_INT vctEvtID;           //��Ż����¼����ͣ������ݿ�ʱ�Ѵ��Ŀǰ��?��
	VCT_INT vctModelID;         //���ģ���
	VCT_INT vctSun;             //�����ۼ�ֵ
	vctDbTrackEvt.clear();
	vctEvtID.clear();
	vctModelID.clear();
	vctSun.clear();
	for (ite_vDb = theApp.m_DataBase.m_DataBaseData.vctDbCOMKng.begin(); ite_vDb != theApp.m_DataBase.m_DataBaseData.vctDbCOMKng.end(); ++ite_vDb)
	{
		//���㵱ǰCOM�¼��ʹ����ݿ���ȡ�����¼���ƥ��ֵ
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
	//ȡ����ƥ��ֵ��������һ����ΪCOM�¼�
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
	if (nPosition > -1)  //˵���ҵ�
	{
		//ȡ��nPosition��Ӧ��֪ʶ���еĻ����¼������úڰ�����¼��ṹ����,��Ϊ"�ڰ���Ϣ"(ע���ڰ��ϵ���Ϣ���ڽ�����ʾ�����)
		nModelID = vctModelID.at(nPosition);
		nEventType = vctEvtID.at(nPosition);
	}
	else     //����˵��������Ч,Ĭ�ϻ����¼�"����",û��ģ���
	{
		nModelID = -1;
		nEventType = 7;
	}	
}

//******************************************************************************************//
//                          �����仯����ģ��(������������)                                  //
//********                    2014-08-03 Liuyian                            ****************//
//********  ���룺                                                          ****************//
//********        ����Ŀ����Ϣ(���ٶȡ����ٶȡ���в��)      ****************//
//********        �ϴ�Ŀ����Ϣ(���ٶȡ����ٶȡ���в��)            **********//
//********  �����״̬�仯�����̼�ģ��ļ�����                                         *****//
//******************************************************************************************//
void CAlgorithm::CharacterChangeJudge(VCT_Cooperative_FUSIDENTIINFOR& ForeData, VCT_Cooperative_FUSIDENTIINFOR& NowData) 
{
	int nModelID(0);
	int nEventType(0);
	VCT_DOUBLE stNowChange;        //ǰ�����εĲ�ֵ��˳����TRACK_THRESHOLD�����е�˳��
	VCT_INT vctTrackEvent;         //˳�����¼���˳����TRACK_THRESHOLD�����е�˳��
	VCT_INT::iterator iteint;
	VCT_DOUBLE::iterator itedou;
	VCT_ESM_MSG::iterator iteESMFore;
	VCT_ESM_MSG::iterator iteESMNow;
	VCT_COMM_MSG::iterator iteCOMFore;
	VCT_COMM_MSG::iterator iteCOMNow;
	VCT_Cooperative_FUSIDENTIINFOR::iterator iteNOw;
	VCT_Cooperative_FUSIDENTIINFOR::iterator iteFore;
	//��ȡ���ݿ⣬������ֵ��Ϣ

	//ͳһ�����б������ޱ���������
	for (iteNOw = NowData.begin(); iteNOw != NowData.end(); ++iteNOw)
	{
		iteNOw->stFusTrack.dHeight = iteNOw->stFusTrack.dRange * sin(PI_4*iteNOw->stFusTrack.dElevationAngle/180);
		if (iteNOw->stFusTrack.lAutonum < 3000)    //ֻ�к�����Ϣ������ESM��COM��Ϣ����Ŀ��������Ϣ�仯
		{
			iteFore = FindSameData(iteNOw->stFusTrack.lAutonum, ForeData);
			if (iteFore != ForeData.end())              //�ҵ�ͬһ���ŵ�����
			{
				iteFore->stFusTrack.dHeight = iteFore->stFusTrack.dRange * sin(PI_4 * iteFore->stFusTrack.dElevationAngle/180);
				stNowChange.clear();
				//ǰ������ʱ�̵Ĳ�ֵ
				stNowChange.push_back(iteNOw->stFusTrack.dRange - iteFore->stFusTrack.dRange);
				stNowChange.push_back(iteNOw->stFusTrack.dHeight - iteFore->stFusTrack.dHeight);
				stNowChange.push_back(iteNOw->stFusTrack.dVSpeed - iteFore->stFusTrack.dVSpeed);
				stNowChange.push_back(iteNOw->stFusTrack.dAddSpeed - iteFore->stFusTrack.dAddSpeed);
				stNowChange.push_back(iteNOw->stFusTrack.dAzimuth - iteFore->stFusTrack.dAzimuth);
				vctTrackEvent.clear();
				//������ֵ�ж�Ŀ��״̬
				for (itedou = stNowChange.begin(), iteint = theApp.m_DataBase.m_DataBaseData.TrackThd.begin(); itedou != stNowChange.end(), iteint != theApp.m_DataBase.m_DataBaseData.TrackThd.end(); ++itedou, ++iteint)
				{
					//������TrackThd��ŵ��Ǵ����ݿ��ȡ����ֵ��Ϣ
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
				//���ú��������¼�����
				KnowLege_Database_Track_EventReason(vctTrackEvent, nModelID, nEventType);
				iteNOw->stFusTrack.nTrackEvent = nEventType;
				iteNOw->stFusTrack.nModel = nModelID;
				iteNOw->stFusTrack.nRdChEvt = vctTrackEvent.at(0);
				iteNOw->stFusTrack.nHtChEvt = vctTrackEvent.at(1);	
				iteNOw->stFusTrack.nVSChEvt = vctTrackEvent.at(2);
				iteNOw->stFusTrack.nAddVSChEvt = vctTrackEvent.at(3);
				iteNOw->stFusTrack.nCuChEvt = vctTrackEvent.at(4);
			} 
			else                                  //û���ҵ�ͬһ���ŵ�����
			{
			}
		}
		else if (iteNOw->stFusTrack.lAutonum >= 8000) //�к�����ESM,COM��ϢĿ�꺽�������仯
		{
			iteFore = FindSameData(iteNOw->stFusTrack.lAutonum, ForeData);
			stNowChange.clear();
			//ǰ������ʱ�̵Ĳ�ֵ
			stNowChange.push_back(iteNOw->stFusTrack.dRange - iteFore->stFusTrack.dRange);
			stNowChange.push_back(iteNOw->stFusTrack.dHeight - iteFore->stFusTrack.dHeight);
			stNowChange.push_back(iteNOw->stFusTrack.dVSpeed - iteFore->stFusTrack.dVSpeed);
			stNowChange.push_back(iteNOw->stFusTrack.dAddSpeed - iteFore->stFusTrack.dAddSpeed);
			stNowChange.push_back(iteNOw->stFusTrack.dAzimuth - iteFore->stFusTrack.dAzimuth);
			vctTrackEvent.clear();
			//������ֵ�ж�Ŀ��״̬,��֤stNowChange�����ݵ�˳���TrackThd�е�����˳��һ��
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
			//���ú��������¼�����
			KnowLege_Database_Track_EventReason(vctTrackEvent, nModelID, nEventType);
			iteNOw->stFusTrack.nTrackEvent = nEventType;
			iteNOw->stFusTrack.nModel = nModelID;
			iteNOw->stFusTrack.nRdChEvt = vctTrackEvent.at(0);
			iteNOw->stFusTrack.nHtChEvt = vctTrackEvent.at(1);
			iteNOw->stFusTrack.nVSChEvt = vctTrackEvent.at(2);
			iteNOw->stFusTrack.nAddVSChEvt = vctTrackEvent.at(3);
			iteNOw->stFusTrack.nCuChEvt = vctTrackEvent.at(4);
			// �ټ��������ڸ�iĿ���ϵ�ESM�����仯������
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
					//������ֵ�ж�Ŀ��״̬����֤stNowChange�����ݵ�˳���ESMThd�е�����˳��һ��,ESMThd��ʾ�����ݿ��ж�ȡ��ESM����ֵ��Ϣ
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
					 //����ESM�����¼�����ģ��
					KnowLege_Database_ESM_EventReason(vctTrackEvent, nModelID, nEventType);
					iteESMNow->nModel = nModelID;
					iteESMNow->nESMEvt = nEventType;
				}
			}
			// �ټ��������ڸ�iĿ���ϵ�ESM�����仯������
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
					//������ֵ�ж�Ŀ��״̬����֤stNowChange�����ݵ�˳���ESMThd�е�����˳��һ��,ESMThd��ʾ�����ݿ��ж�ȡ��ESM����ֵ��Ϣ
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
					//����ESM�����¼�����ģ��
					KnowLege_Database_COM_EventReason(vctTrackEvent, nModelID, nEventType);
					iteCOMNow->nModel = nModelID;
					iteCOMNow->nCOMEvt = nEventType;
				}
			}
		}
		else
		{
			//ֻ��ESM��COM��Ϣ����Ӧ�ó��ִ����
		}
	}
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
//***********            �����¼�������ڰ�ڵ㴴�����ģ��                                        *****//
//********                    (2014-18-17  Liuyian)                                           **********//
//********     ���룺�����ںϵ������ݣ���Ŀ���������������                                   **********//
//********     ��������ش����Ƿ������һ�������־��0�����²����У�1�����²�����             **********//
void CAlgorithm::Basic_Event_First_LinKJudge_Process_Modul(VCT_Cooperative_FUSIDENTIINFOR& NowData, int& nTriggleFlag)             //(�״ν���)
{
	int nNowCount(0);          //��ǰѭ������
	VCT_Cooperative_FUSIDENTIINFOR::iterator iteNowData;
	VCT_COMM_MSG::iterator iteCOM;
	VCT_ESM_MSG::iterator iteESM;
	EVENTLINKS TemData;
	EVENTBLACK BlackTemData;
	for (iteNowData = NowData.begin(); iteNowData != NowData.end(); ++iteNowData)
	{
		//������д���¼��б�
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

		//������д�뵽�ڰ���
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
			//����ѭ����δ��ģ��ţ��Ƿ������⣿
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
//***********            �����¼�������ڰ�ڵ㴴�����ģ��                                        *****//
//********                    (2014-18-17  Liuyian)                                           **********//
//********     ���룺�����ںϵ������ݣ���Ŀ���������������                                   **********//
//********     ��������ش����Ƿ������һ�������־��0�����²����У�1�����²�����             **********//
void CAlgorithm::Basic_Event_NonFirst_LinKJudge_Process_Modul(VCT_Cooperative_FUSIDENTIINFOR& NowData, int& nTriggleFlag)             //(���״�)
{
	int nCount(0);
	VCT_INT vctESMFlag;                             //����¿�����ESM
	VCT_INT vctESMCloseFlag;                        //����״�ػ�
	VCT_INT vctCOMOpenFlag;                         //���COM������Ϣ
	VCT_INT vctCOMCloseFlag;                        //���COM�ػ���Ϣ
	VCT_ESM_MSG::iterator iteESM;
	VCT_INT::iterator iteESMLink;
	VCT_COMM_MSG::iterator iteCOM;
	VCT_INT::iterator iteCOMLink;
	VCT_Cooperative_FUSIDENTIINFOR::iterator iteNowData;
	MAP_BASIC_EVENT::iterator iteBasicEvt;
	MAP_EVENT_BLACK::iterator iteBlack;
	for (iteNowData = NowData.begin(); iteNowData != NowData.end(); ++iteNowData)
	{
		iteBasicEvt = m_mapBasicEvent.find(iteNowData->stFusTrack.lAutonum);       //���������ҵ���Ŀ��ǰһʱ�̶�Ӧ��״̬
		if (iteBasicEvt != m_mapBasicEvent.end())  //�ҵ�
		{
			if (iteNowData->stFusTrack.nModel == iteBasicEvt->second.nTrackMBHao)
			{
				++iteBasicEvt->second.nTrackCumulativeN;                 //�ۼ�
				if (iteBasicEvt->second.nTrackCumulativeN >= 5)          //������ֵ
				{
					iteBlack = theApp.m_mapEventBlack.find(iteNowData->stFusTrack.lAutonum);
					iteBlack->second.nTrackHao = iteNowData->stFusTrack.lAutonum;     //������
					iteBlack->second.lTimeStamp = iteNowData->lStampTime;             //ʱ���
					iteBlack->second.dAddSpeed = iteNowData->stFusTrack.dAddSpeed;    //���ٶ�
					iteBlack->second.dRd = iteNowData->stFusTrack.dRange;             //����
					iteBlack->second.dAz = iteNowData->stFusTrack.dAzimuth;           //��λ
					iteBlack->second.dEz = iteNowData->stFusTrack.dElevationAngle;    //����
					iteBlack->second.dHigh = iteNowData->stFusTrack.dHeight;          //�߶�
					iteBlack->second.dSpeed = iteNowData->stFusTrack.dVSpeed;         //�ٶ�
					iteBlack->second.dAzimuth = iteNowData->stFusTrack.dCourse;       //����
					iteBlack->second.nTrackEvent = iteNowData->stFusTrack.nTrackEvent;//�����¼�
					iteBlack->second.vctEventValue.push_back(iteNowData->stFusTrack.nHtChEvt);   //�߶�����
					iteBlack->second.vctEventValue.push_back(iteNowData->stFusTrack.nVSChEvt);   //�ٶ�����
					iteBlack->second.vctEventValue.push_back(iteNowData->stFusTrack.nAddVSChEvt);//���ٶ�����
					iteBlack->second.vctEventValue.push_back(iteNowData->stFusTrack.nRdChEvt);   //��������
					iteBlack->second.vctEventValue.push_back(iteNowData->stFusTrack.nCuChEvt);   //��������
					iteBlack->second.dThreatDegree = iteNowData->stFusTrack.dThrDg;           //ƽ̨��в��
					iteBlack->second.nTrackType = iteNowData->stFusTrack.nTgtType;            //ƽ̨�¼�����
					//�ٴ��������ESM,��������ʧ���״Ҳ�������¿����״�
					vctESMFlag.clear();
					vctESMCloseFlag.clear();
					//vctESMFlagͳһ��0����ʾ��ʱ��ȫ��Ϊ�¿������״�
					for (int i = 0; i < iteNowData->vctFusEsm.size(); ++i)
					{
						vctESMFlag.push_back(0);
					}
					//vctESMCloseFlagͳһ��0����ʾ��һʱ�������е�ESMȫ���ػ��������ҵ���ʱ����1����ʾ����״̬һֱ����
					for (i = 0; i < iteBasicEvt->second.vctESMHao.size(); ++i)
					{
						vctESMCloseFlag.push_back(0);
					}
					for (iteESM = iteNowData->vctFusEsm.begin(); iteESM != iteNowData->vctFusEsm.end(); ++iteESM)             //��������ESM
					{
						nCount = 0;
						for (iteESMLink = iteBasicEvt->second.vctESMHao.begin(); iteESMLink != iteBasicEvt->second.vctESMHao.end(); ++iteESMLink)
						{
							if (*iteESMLink == iteESM->lAutonum)   //ESM��һ��
							{
								//�ҵ��������¿����״�
								vctESMFlag.at(nCount) = 1;
								vctESMCloseFlag.at(nCount) = 1;
								if (iteESM->nModel == iteBasicEvt->second.vctESMMBHao.at(nCount))
								{
									//ģ���һ������������
								} 
								else
								{
									//ģ��Ų�һ������ʾ״̬�����ı�
									//ע��ESM��Ҫ�ۼӣ���û�л����仯���̣��뺽����ͬ
									//�����¼��б������
									iteBasicEvt->second.vctESMMBHao.at(nCount) = iteESM->nModel;
									iteBasicEvt->second.vctESMBasicSituation.at(nCount) = iteESM->nESMEvt;
									//���ºڰ�����
									iteBlack->second.vctESMHao.at(nCount) = iteESM->lAutonum;
									iteBlack->second.vctESMEvent.at(nCount) = iteESM->nESMEvt;
								}
									
							}  //û�ҵ�����������������
							else          
							{
								
							}
							++nCount;
						}
					}
					i = 0;   //��ʾѭ������
					for (iteESM = iteNowData->vctFusEsm.begin(); iteESM != iteNowData->vctFusEsm.end(); ++iteESM)
					{
						//ESM���³��֣���ʾ�¿�����ESM�������±����ӵ�δ�����vector��
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
						//����ػ������
						if (vctESMCloseFlag.at(i) == 0)
						{
							iteBlack->second.vctESMEvent.at(i) = 1;                 //ESM�����¼����ػ�
						}
						++i;
					}
					//�ٴ���ESM��ʧ�����ػ��������е�ESM

					//�¼�������ȥ����ʧ��ESM


					//�ٴ���COM
					//�ٴ��������COM,��������ʧ���״Ҳ�������¿���ͨ���״�
					vctCOMOpenFlag.clear();
					vctCOMCloseFlag.clear();
					//vctCOMOpenFlagͳһ��0����ʾ��ʱ��ȫ��Ϊ�¿������״�
					for (i = 0; i < iteNowData->vctFusCom.size(); ++i)
					{
						vctCOMOpenFlag.push_back(0);
					}
					//vctESMCloseFlagͳһ��0����ʾ��һʱ�������е�COMȫ���ػ��������ҵ���ʱ����1����ʾ����״̬һֱ����
					for (i = 0; i < iteBasicEvt->second.vctCOMHao.size(); ++i)
					{
						vctCOMCloseFlag.push_back(0);
					}
					for (iteCOM = iteNowData->vctFusCom.begin(); iteCOM != iteNowData->vctFusCom.end(); ++iteCOM)             //��������ESM
					{
						nCount = 0;
						for (iteCOMLink = iteBasicEvt->second.vctCOMHao.begin(); iteCOMLink != iteBasicEvt->second.vctCOMHao.end(); ++iteCOMLink)
						{
							if (*iteCOMLink == iteCOM->lAutonum)   //COM��һ��
							{
								//�ҵ��������¿����״�
								vctCOMOpenFlag.at(nCount) = 1;
								vctCOMCloseFlag.at(nCount) = 1;
								if (iteCOM->nModel == iteBasicEvt->second.vctCOMMBHao.at(nCount))
								{
									//ģ���һ������������
								} 
								else
								{
									//ģ��Ų�һ������ʾ״̬�����ı�
									//ע��COM��Ҫ�ۼӣ���û�л����仯���̣��뺽����ͬ
									//�����¼��б������
									iteBasicEvt->second.vctCOMHao.at(nCount) = iteCOM->nModel;
									iteBasicEvt->second.vctCOMBasicSituation.at(nCount) = iteCOM->nCOMEvt;
									//���ºڰ�����
									iteBlack->second.vctCOMHao.at(nCount) = iteCOM->lAutonum;
									iteBlack->second.vctCOMEvent.at(nCount) = iteCOM->nCOMEvt;
								}
								
							}  //û�ҵ�����������������
							else          
							{
								
							}
							++nCount;
						}
					}
					i = 0;   //��ʾѭ������
					for (iteCOM = iteNowData->vctFusCom.begin(); iteCOM != iteNowData->vctFusCom.end(); ++iteCOM)
					{
						//COM���³��֣���ʾ�¿�����COM�������±����ӵ�δ�����vector��
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
						//����ػ������
						if (vctCOMCloseFlag.at(i) == 0)
						{
							iteBlack->second.vctCOMEvent.at(i) = 1;                 //COM�����¼����ػ�
						}
						++i;
					}
					//�ٴ���COM��ʧ�����ػ��������е�COM
					
					//�¼�������ȥ����ʧ��COM


				}
			}
			//������ͬ��ģ��Ų�һ����˵�������¼�
			else
			{
				//1 ���޸�����,ֻ���򵥴���

				//ͬʱ���滻���ϵ�ESM��COM
				//ESM

				//COM


				//2 �ٲ����ڰ�ṹ����
			}
		}
		else                             //δ�ҵ�����Ŀ��Ϊ�³��ֵ�Ŀ��
		{
			//1.��������ڵ�

			//2.���ºڰ�ڵ�����

			//3.���Ӻڰ�ڵ�
		}
	}
}

//�¼����ȫ���������
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


///////////////////////////////////////ƽ̨��//////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////
//***********              ƽ̨̬����ͼ֪ʶ�������ģ��           ****************//
//********                    (2014-07-31  Liuyian)                     **********//
//********     ���룺�ڰ��ϻ����¼���ṹ����                           **********//
//********           ��������:Azimuth                                   **********//
//******             ̬�Ʋ�֪ʶ���¼����  KnowlegeSituN                **********//
//******             �Ƿ��һ�ε��øú�����nFlagΪ1��ʾ�ǣ�����Ϊ0      **********//
//******             ƽ̨����̬�Ʋ�֪ʶ��                               **********//
//********    ������״Σ�����ƽ̨̬������ڵ�ͺڰ��ƽ̨̬�Ʋ�        **********//
//********��        ���״β��������µ��������� m_List_temp                  ******//
////////////////////////////////////////////////////////////////////////////////////
void CAlgorithm::Plat_KnowLedge_Basic_Situation_Reason_Modil(MAP_EVENT_BLACK& m_EventBlack,double& Azimuth,int nFlag, int& nBack, MAP_PLAT_LINK& m_List_temp) 
{
	int i;
	int nAzEvent;        //�����¼�
	int nMax;  
	int nFindFlag;       //�ҵ���־,0��ʾ�ҵ���1��ʾδ�ҵ�
	int nFindPos;        //�ҵ������ֵ���ڵ�λ��
	int nsum;
	int nESMHao;
	int nESMEvent;
	int nCOMHao;
	int nCOMEvent;
	int nCount(0);
	double dAzcr;       //����ǲ�ֵ
	VCT_INT vctSunCorr;  //����ƥ��ȣ�����ȡ����һ��
	VCT_INT vctTemp;
	MAP_EVENT_BLACK::iterator iteBlack;
	VV_INT::iterator iteDbKng;
	VCT_INT::iterator iteSigKng;
	VCT_INT::iterator iteTemp;
	PLATEVENT PlatListTemp;
	PLATBLACK PlatBlackTemp;
	//�����¼��ڰ��е����нڵ㣬�ֱ���д���
	for (iteBlack = m_EventBlack.begin(); iteBlack != m_EventBlack.end(); ++iteBlack)
	{
		//��ȡԭֵ���洢
		

		//���㺽���ж�Ŀ����˶�״̬��ƫ�뱾���ж�:1--���򱾽���3--������5--Զ��
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
		//֪ʶ��ƥ������
		vctSunCorr.clear();
		for (iteDbKng = theApp.m_DataBase.m_DataBaseData.vctDbPlatKng.begin(); iteDbKng != theApp.m_DataBase.m_DataBaseData.vctDbPlatKng.end(); ++iteDbKng)
		{
			//ƥ������
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
			
			//�ӶಿESM�����¼����ҳ�һ��
			nFindFlag = 0;
			for (iteSigKng = iteBlack->second.vctESMEvent.begin(), i = 0; iteSigKng != iteBlack->second.vctESMEvent.end(); ++i,++iteSigKng)
			{
				if (iteDbKng->at(6) == *iteSigKng)
				{
					nFindFlag = 1;
					nsum = nsum + 1;
					//����ƽ̨�������õ�ESM��ģ��źͻ����¼�
					nESMHao = iteBlack->second.vctESMHao.at(i);
					nESMEvent = iteBlack->second.vctESMEvent.at(i);
					
				}
			}
			if (nFindFlag == 0)
			{
				nsum = nsum - 1;
			}
			//�ӶಿCOM�����¼����ҳ�һ��
			nFindFlag = 0;
			for (iteSigKng = iteBlack->second.vctCOMEvent.begin(), i = 0; iteSigKng != iteBlack->second.vctCOMEvent.end(); ++i,++iteSigKng)
			{
				if (iteDbKng->at(7) == *iteSigKng)
				{
					nFindFlag = 1;
					nsum = nsum + 1;
					//����ƽ̨�������õ�COM��ģ��źͻ����¼�
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

		//����ƽ̨ƥ������ֵ
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
		if (nFindPos > -1)   //�ҵ�
		{
			//ȡ��MaxK��Ӧ��֪ʶ���еĻ����¼�
			//ֱ�Ӳ���ƽ̨̬�Ʒ��������ڵ�
			if (nFlag == 1)           //��һ��
			{
				//ƽ̨�����¼�
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
				PlatListTemp.nPlatOBJEvent = theApp.m_DataBase.m_DataBaseData.PlatEventID.at(nFindPos);//������
				PlatListTemp.nPlatOBjType = iteBlack->second.nTrackType;
				PlatListTemp.nSerialnum = nCount;
				m_Plat_link.insert(make_pair(PlatListTemp.nPlatHao, PlatListTemp));

				//ƽ̨�ڰ�
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
			else         //���״�
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
				PlatListTemp.nPlatOBJEvent =theApp.m_DataBase.m_DataBaseData.PlatEventID.at(nFindPos);//������
				PlatListTemp.nPlatOBjType = iteBlack->second.nTrackType;
				PlatListTemp.nSerialnum = nCount;
				m_List_temp.insert(make_pair(PlatListTemp.nPlatHao, PlatListTemp));
			}
		}
		++nCount;
	}
	//����ƽ̨�ͺڰ�ڵ������
	
	//�����Ƿ񴫵ݵ���һ��ı�־
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
//***********              ƽ̨̬����ͼ֪ʶ�������ģ��           ****************//
//********                    (2014-07-31  Liuyian)                     **********//
//********     ���룺��ģ������ı���ƽ̨̬�Ʋ�����ṹ����              *********//
//********    ���������ƽ̨̬������ڵ�ͺڰ��ƽ̨̬�Ʋ�              **********//
////////////////////////////////////////////////////////////////////////////////////
void CAlgorithm::Plat_NonFirst_KnowLedge_Basic_Situation_Reason_Modil(MAP_PLAT_LINK& m_Link_temp, int& nBackF)  //(���״�)
{
	VCT_INT::iterator itevct;
	VCT_INT vctNewPlatID;     //�洢�³��ֵ�ƽ̨�ı��
	VCT_INT vctAssioPlatID;   //����������ƽ̨��
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
		if (mapFind != m_Link_temp.end())    //�ҵ���������ͬ
		{
			vctAssioPlatID.push_back(mapFind->first);
			if (mapFind->second.nPlatMBHao == mapTemp->second.nPlatMBHao)            //ģ���Ҳ��ͬ
			{
				mapFind->second.nPlatCumulativeN++;
				if (mapFind->second.nPlatCumulativeN >= 5)
				{
					mapBlackFind = theApp.m_Plat_Black.find(mapFind->first);
					if (mapBlackFind != theApp.m_Plat_Black.end())  //�ںڰ��������ƽ̨,���ĺڰ�����
					{
						mapBlackFind->second.dAddSpeed = mapFind->second.dAddSpeed;
						mapBlackFind->second.dAz = mapFind->second.dAz;
						mapBlackFind->second.dAzimuth = mapFind->second.dAzimuth;
						mapBlackFind->second.dEz = mapFind->second.dEz;
						mapBlackFind->second.dHigh = mapFind->second.dHigh;
						mapBlackFind->second.dRd = mapFind->second.dRd;
						mapBlackFind->second.dSpeed = mapFind->second.dSpeed;
						mapBlackFind->second.dThreatDegree = mapFind->second.dThreatDegree;
						mapBlackFind->second.lTimeStamp = 1;//??????????????????����Ϊ��ǰʱ��
						mapBlackFind->second.nCOMBasicSituation = mapFind->second.nCOMBasicSituation;
						mapBlackFind->second.nCOMHao = mapFind->second.nCOMHao;
						mapBlackFind->second.nESMBasicSituation = mapFind->second.nESMBasicSituation;
						mapBlackFind->second.nESMHao = mapFind->second.nESMHao;
						mapBlackFind->second.nPlatBasicSituation = mapFind->second.nPlatOBJEvent;
						mapBlackFind->second.nPlatHao = mapFind->second.nPlatHao;
						mapBlackFind->second.nSerialnum = mapFind->second.nSerialnum;
						mapBlackFind->second.nTrackOBjType = mapFind->second.nPlatOBjType;
					}
					//ƽ̨�����н��д���
					mapFind->second.nPlatOBJEvent = mapTemp->second.nPlatOBJEvent;
					mapFind->second.dThreatDegree = mapTemp->second.dThreatDegree;
					mapFind->second.nPlatCumulativeN = 1;
					nBackF = 1;
				}
			} 
			else           //ģ��Ų�ͬ
			{
				nBackF = 1;
				//ƽ̨�������
				mapFind->second.nPlatMBHao = mapTemp->second.nPlatMBHao;
				mapFind->second.nPlatCumulativeN = 1;
				mapFind->second.nPlatOBJEvent = mapTemp->second.nPlatOBJEvent;
				mapFind->second.dThreatDegree = mapTemp->second.dThreatDegree;
				//�ڰ����
				mapBlackFind = theApp.m_Plat_Black.find(mapFind->first);
				if (mapBlackFind != theApp.m_Plat_Black.end())  //�ںڰ��������ƽ̨,���ĺڰ�����
				{
					mapBlackFind->second.dAddSpeed = mapFind->second.dAddSpeed;
					mapBlackFind->second.dAz = mapFind->second.dAz;
					mapBlackFind->second.dAzimuth = mapFind->second.dAzimuth;
					mapBlackFind->second.dEz = mapFind->second.dEz;
					mapBlackFind->second.dHigh = mapFind->second.dHigh;
					mapBlackFind->second.dRd = mapFind->second.dRd;
					mapBlackFind->second.dSpeed = mapFind->second.dSpeed;
					mapBlackFind->second.dThreatDegree = mapFind->second.dThreatDegree;
					mapBlackFind->second.lTimeStamp = 1;//??????????????????����Ϊ��ǰʱ��
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
		else      //û���ҵ���ͬ�����ţ���ʾ�³��ֵ�ƽ̨
		{
			vctNewPlatID.push_back(mapTemp->first);
		}
	}
	//��������ʧ��ƽ̨����
	for(mapTemp = m_Link_temp.begin(); mapTemp != m_Link_temp.end(); ++mapTemp)
 	{
// 		itevct = vctAssioPlatID.find(mapTemp->first);
// 		if (itevct == vctAssioPlatID.end())              //û�ҵ�����ʾĿ����ʧ
// 		{
// 			//����ʧ�����ݽ��д���
// 		}
	}
	//���������Ľڵ�
	for (itevct = vctNewPlatID.begin(); itevct != vctNewPlatID.end(); ++itevct)
	{
		mapTemp = m_Link_temp.find(*itevct);
		//ƽ̨�����¼�
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
		
		//ƽ̨�ڰ�
		PlatBlackTemp.dAddSpeed = mapTemp->second.dAddSpeed;
		PlatBlackTemp.dAz = mapTemp->second.dAz;
		PlatBlackTemp.dAzimuth = mapTemp->second.dAzimuth;
		PlatBlackTemp.dEz = mapTemp->second.dEz;
		PlatBlackTemp.dHigh = mapTemp->second.dHigh;
		PlatBlackTemp.dRd = mapTemp->second.dRd;
		PlatBlackTemp.dSpeed = mapTemp->second.dSpeed;
		PlatBlackTemp.dThreatDegree = mapTemp->second.dThreatDegree;
		PlatBlackTemp.lTimeStamp = 1;//??????????????????����Ϊ��ǰʱ��
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


/////////////////////////////////////////�ռ��////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////
/*****************************************************/
/**********         ϵͳ���෨(�Ѳ��Թ�)    **********/
/**********      2014-08-04  Liuyian   ***************/
/********* ����:�Գƾ���Rd0�ͽ���pp*/
/*Rd0��ʾ�����ݿ��л�ȡ��Ⱥ����ֵ*/
/*LLCC��ʾ�ɻ��򽢴�������              ******/
/*********  ���:����������������             ******/
/*TGroupN��ʾȺ������             ******/
/*EGN��ʾÿ��Ⱥ�е�Ŀ������              ******/
/*EveryGroup��ʾÿ��Ⱥ�е�Ŀ��ı��              ******/
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
	int qq[100];//�Ÿ������
	int SeekF0,SeekF1,SeekF2;
	VCT_INT vct_temp;
	/////////////////////////////
	
	/////////////////////////////
	
	//����ת��
	RN=pp;
	for(i=0;i<RN;i++)
		for(j=0;j<RN;j++)
			HH[i][j]=AA[i][j];
		
		//ϵͳȡ���෨(�����ص�:1:���Խ�����Ԫ�ؾ�Ϊ0,2:����Ԫ�ؾ�Ϊ��,3:��Ϊ�Գƾ���)
		//��һ���������ǶԳ���,ֻ����������,������Сֵ
		m=0;//ͳ������
		temp=RN;
		dFlag=0;
		min=0;
		while(RN>2)
		{
			Flag=0;
			for(i=0;i<RN-1;i++)//�ҳ���Сֵ
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
			
			for(i=0;i<RN;i++)    //����ϲ���
			{
				aa[i]=HH[mini][i];
				bb[i]=HH[minj][i];
			}
			for(i=0;i<RN;i++)  //�����ϲ���ֵ
			{
				if(aa[i]>bb[i])
					cc[i]=bb[i];
				else
					cc[i]=aa[i];		 
			}


		 //����ϲ���ԭʼ���
		 if(dFlag==0)
		 {
			LC[m][0]=LLCC[mini];
		     	LC[m][1]=LLCC[minj];

			 temp=temp+1;
			 LC[m][2]=temp;//�ϲ���
			 qq[m]=3;
		
			 //����LLCC�е����λ��
			 k=0;
			 for(i=0;i<RN;i++)//����
			 {
				 if(i!=mini && i!=minj)
				 {
				     	LLCC0[k]=LLCC[i];
				 
					 k++;
				 }			 
			 }
			 for(i=0;i<k;i++)//д��
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
				 for(i=0;i<m;i++)//��ѭ��
				 {
				      	SeekF1=0;//����i��
				      	for(k=0;k<qq[i];k++)//�����еĸ���
					  {

					     if(LLCC[mini]==LC[i][k])
						 {
						    SeekF1=1;//�ҵ�
						 }				 
					  }

					  SeekF2=0;//����j��
				     	 for(k=0;k<qq[i];k++)
					  {
					     	if(LLCC[minj]==LC[i][k])
						 {
						    SeekF2=1;//�ҵ�
						 }				 
					  }

					  if(SeekF1!=0 || SeekF2!=0)  //�ҵ�,��Ϊ����
					  {
						  if(SeekF1!=0 && SeekF2==0)
						  {
							  
					          		LC[i][qq[i]]=LLCC[minj];//����µĺ�

							   //����LLCC�е����λ��
			                   			g=0;
			                  			for(w=0;w<RN;w++)//����
							{
				                    			if(w!=minj)
								{
				                       				LLCC0[g]=LLCC[w];
					                   			g++;
								}			 
							   }
			                   			for(w=0;w<g;w++)//д��
							{
				                    			LLCC[w]=LLCC0[w];									
							}							   
							   LLCC[w]=temp;
							   qq[i]++;

							   temp++;

						  }

						  if(SeekF1==0 && SeekF2!=0)
						  {
							  
					          		LC[i][qq[i]]=LLCC[mini];//����µĺ�

							  //����LLCC�е����λ��
			                   			g=0;
			                   			for(w=0;w<RN;w++)//����
							 {
				                    			if(w!=mini)
								{
				                       				LLCC0[g]=LLCC[w];
				 
					                   			g++;
								}			 
							}
			                   			for(w=0;w<g;w++)//д��
							{
				                    			LLCC[w]=LLCC0[w];
							}
							   qq[i]++;
							   temp++;
							   LLCC[w]=temp;		    

						  }			
						  SeekF0=1;

						  i=i+m;   //��ǰ�˳�
					}

				 }//for i				 

				 if(SeekF0==0)  //��û�ҵ�,Ϊ����
				 {
					 LC[m][0]=LLCC[mini];
		             		LC[m][1]=LLCC[minj];

			        		 temp=temp+1;
			         		LC[m][2]=temp;//�ϲ���
					 qq[m]=3;

					//����LLCC�е����λ��
			        		g=0;
			        		for(w=0;w<RN;w++)//����
					{
				        		if(w!=mini && w!=minj)
						{
				              		LLCC0[g]=LLCC[w];
				 
					          		g++;
						}			 
					}
			        		for(w=0;w<g;w++)//д��
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
	 		
	 //������	
	 TGroupN=m;    //�ռ�Ⱥ��(����������Ŀ��ų�ΪȺ)
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


///////////////////////////////����///////////////////////////////////////////
//NewPlat ΪNvctTgt��ƽ̨��
//TGroupN�ռ�Ⱥ����Ŀ
//EGNÿ��Ⱥ��Ŀ����
//EveryGroupÿ��Ⱥ������Ŀ������
//vctTgt���зɻ�����Ϣ
///////////////////////////////���///////////////////////////////////////////
//iAverSpeed�����ٶȵ�����ƫ��
//AverAzmith���غ��������ƫ��
//Kthreatgree����ÿ��Ⱥ����в��
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
	
	//��ʼ��
	for(i = 0; i < vctTgt.size(); ++i)
	{
		MFlag.push_back(0);
		dFlag.push_back(0);
	}
	//	
	for(i=0; i < TGroupN; ++i)//Ⱥ��
	{
		TempAzmith.push_back(0);
		TempVSpeed.push_back(0);
		TSumVSpeed.push_back(0);
		TSumAzmith.push_back(0);
		Thretgr.push_back(1.0);
		for(j = 0; j < EGN[i]; ++j)//ÿȺ�е���
		{			
			for(k=0; k < vctTgt.size(); ++k)//ƽ̨��
			{
				if(MFlag[k] == 0)//û�����
				{
					if(EveryGroup[i][j] == vctTgt[k].nPlatHao)//�ҵ�
					{
						MFlag[k] = 1;
                        
						TempVSpeed[i] = TempVSpeed[i] + vctTgt[k].dSpeed/EGN[i];  //Ⱥ��ֵ
						TempAzmith[i] = TempAzmith[i] + vctTgt[k].dAzimuth/EGN[i];  //Ⱥ��ֵ	
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
				if(dFlag[k] == 0)//û�����
				{
					if(EveryGroup[i][j] == vctTgt[k].nPlatHao)//�ҵ�
					{
						dFlag[k] = 1;
                        
						ddSpeed[i] = ddSpeed[i]+(vctTgt[k].dSpeed - TempVSpeed[i])*(vctTgt[k].dSpeed - TempVSpeed[i]);    //Ⱥ����
						ddAzmith[i] = ddAzmith[i]+(vctTgt[k].dAzimuth - TempAzmith[i])*(vctTgt[k].dAzimuth - TempAzmith[i]);  //Ⱥ����			
					}
				}
				
			}//for k
			
		}//for j
		
		ddSpeed[i] = sqrt(ddSpeed[i]/EGN[i]);      //Ⱥ��׼��
		ddAzmith[i] = sqrt(ddAzmith[i]/EGN[i]);	 //Ⱥ��׼��
		Thretgr[i] = 1.0 - Thretgr[i];               //��Ⱥ���ۺ���в��
		
	}//for i
	
	SumVp = 0;
	SumAz = 0;
	for(i = 0; i < TGroupN; ++i)
	{
		SumVp = SumVp + ddSpeed[i]/TGroupN;
		SumAz = SumAz + ddAzmith[i]/TGroupN;	
		
		Kthreatgree.push_back(Thretgr[i]);        //���ظ�Ⱥ���ۺ���в��
		
	}//for i
	
	//��������ƫ��
	iAverSpeed = SumVp;    //�����ٶ�ƫ��
	AverAzmith = SumAz;   //���غ��������ƫ��	
}


/////////////////////////////////////////////////////////////////////////////////////////
//                               �ռ�Ⱥ֪ʶ����ģ�����                                //
//********                    (2014-10-18  Liuyian)                          **********//
//********     ���룺�ڰ���ƽ̨̬�Ʋ�ṹ����                           **********//
//********��         ���״β��������µ���������                              ******//
//********     ����������ռ�Ⱥ�ࡢ����Ŀ                                    **********//
//********           �����ռ�Ⱥ����ṹ����                                  **********//
/////////////////////////////////////////////////////////////////////////////////////////
void CAlgorithm::SpaceGroup_Reason_PlatSituationEvent_datamodul(MAP_PLAT_BLACK& m_Plat_Black, SPACE_TARGET& vctPlaneLink, SPACE_TARGET& vctShipLink, int& BFlag)
{
	int i, j;
	double dmin;
	double dMink;
	double dTemp;
	double dDistance;
	VCT_DOUBLE vct_dou_temp;
	vector<PLATBLACK> vctPlaneTemp;          //�洢�����ɻ�����������
	vector<PLATBLACK> vctShipTemp;
	vector<PLATBLACK>::iterator itePlat;
	MAP_PLAT_BLACK::iterator mapPlat;
	TARGET_POSITION PositonTemp;
	VCT_POSITION vctPoShip;			//�������н�����λ�ã�x��y��z
	VCT_POSITION vctPoPlane;		//�������еķɻ���λ�ã�x��y��z
	VV_DOUBLE vctMatrixPlane;		//�ɻ��ľ������
	VV_DOUBLE vctMatrixShip;		//�����ľ������
// 	VV_DOUBLE::iterator itevvtemp;
// 	VCT_DOUBLE::iterator itevcttemp;
	VCT_POSITION::iterator itePoFirst;
	VCT_POSITION::iterator itePoSec;
	VV_INT::iterator iteKng;
	VCT_INT vctModelID;			//ģ���
	VCT_INT vctModelNum;		//��ģ���Ӧ�Ŀռ�Ⱥ��
	VCT_INT vctPlatID;			//����
	int TGroupN;				//Ⱥ����
	VCT_INT EGN;				//ÿ��Ⱥ�ڵ�Ŀ��ĸ���
	VV_INT EveryGroup;			//ÿ��Ⱥ�ڵ�����
	DOUBLE iAverSpeed;			//ƽ�����ٶ�
	DOUBLE AverAzmith;			//ƽ���ĺ���
	VCT_DOUBLE vctiAverSpeed;			//ƽ�����ٶ�
	VCT_DOUBLE vctAverAzmith;			//ƽ���ĺ���
	VCT_DOUBLE vctKthreatgree;		//��в��
	VCT_INT vctPlatType;		//ƽ̨����
	VCT_INT vctPlatTaishi;		//ƽ̨̬��
	VCT_INT vctTemp;
	SPACE_TARGET TgtTmep;

	VV_INT::iterator iteEG;     //EveryGroup�ĵ�����

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

	//1:�Ȳ�������Ŀռ�Ⱥ�ṹ����
	//���ͷ���(ֻ����������,�ɻ������vctPlane,���������vctShip)
	//������任��ת�������״�ֱ������ϵ��
	//�������x,y,z��ֵ�ֱ����vctPoShip��vctPoPlane��
	for (mapPlat = m_Plat_Black.begin(); mapPlat != m_Plat_Black.end(); ++mapPlat)
	{
		if (mapPlat->second.nTrackOBjType == 1 || mapPlat->second.nTrackOBjType == 2 || mapPlat->second.nTrackOBjType == 3)	//�ɻ���
		{
			PositonTemp.dx = mapPlat->second.dRd*cos(mapPlat->second.dEz)*sin(mapPlat->second.dAz);//?????����Ҫ�û��ȣ���Ҫ�����𣿣�������
			PositonTemp.dy = mapPlat->second.dRd*cos(mapPlat->second.dEz)*cos(mapPlat->second.dAz);//ͬ��
			PositonTemp.dz = mapPlat->second.dRd*sin(mapPlat->second.dEz); //ͬ��
			vctPoPlane.push_back(PositonTemp);
			vctPlaneTemp.push_back(mapPlat->second);
		} 
		else if (mapPlat->second.nTrackOBjType == 4)	//������
		{
			PositonTemp.dx = mapPlat->second.dRd*cos(mapPlat->second.dEz)*sin(mapPlat->second.dAz);//?????����Ҫ�û��ȣ���Ҫ�����𣿣�������
			PositonTemp.dy = mapPlat->second.dRd*cos(mapPlat->second.dEz)*cos(mapPlat->second.dAz);//ͬ��
			PositonTemp.dz = mapPlat->second.dRd*sin(mapPlat->second.dEz); //ͬ��
			vctPoShip.push_back(PositonTemp);
			vctShipTemp.push_back(mapPlat->second);
		} 
		else
		{
			//������
		}
	}
	//1: �ȼ���ɻ���:  ����֮��Ŀռ����
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


	//���ÿռ��֪ʶ��Էɻ�����
	vctPlatID.clear();
	//�����Ŵ���vctPlatID��
	for(itePlat = vctPlaneTemp.begin(); itePlat != vctPlaneTemp.end(); ++itePlat)			
	{
		vctPlatID.push_back(itePlat->nPlatHao);
	}

	//vector���
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
		if ((*iteKng)[0] == 2)	//����Ϊ�ɻ�
		{
			vctModelID.push_back(theApp.m_DataBase.m_DataBaseData.SpaceGrpID[i]);
			//��Ҫ�������ݵı������
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
			vctModelNum.push_back(TGroupN);			//��ģ���Ӧ��Ŀ��Ⱥ��
		
			vvEGN.push_back(EGN);

			vctiAverSpeed.push_back(iAverSpeed);
			vctAverAzmith.push_back(AverAzmith);
			vvEveryGroup.push_back(EveryGroup);
			vvKthreatgree.push_back(vctKthreatgree);

		}
	}
	//�ҳ��ɻ������С��
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
	
	if (dMink > -1)			//�ҵ�
	{
		//�����ɻ��ռ�Ⱥ����ṹ
		vctPlaneLink.nPlanTypeN = vctModelNum[dMink];         //�ռ�Ⱥ�ĸ���
		for (i = 0; i < vctModelNum[dMink]; ++i)		//ÿһ���ռ�Ⱥ��
		{
			vctPlaneLink.vctPlanGroupN.push_back(vvEGN[dMink][i]);			//ÿ��Ⱥ��ƽ̨������
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
						 //ȡ����ƽ̨�����ͺ�̬��,д������ṹ
						vctPlatType.push_back(itePlat->nTrackOBjType);
						vctPlatTaishi.push_back(itePlat->nPlatBasicSituation);
					}
				}
			}
			vctPlaneLink.vvPlanGroupHao.push_back(vctTemp);
			vctPlaneLink.vvPlanGroupOBjType.push_back(vctPlatType);
			vctPlaneLink.vvPlanEvent.push_back(vctPlatTaishi);
			vctPlaneLink.vctPlanThreatDegree.push_back(vvKthreatgree[dMink][i]);		//ÿ��Ⱥ���ۺ���в��
		}
		vctPlaneLink.nPlanSpacMBHao = vctModelID[dMink];
	}

	//2: �ٴ������ࣺ��������֮��Ŀռ����
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
	

	//���ÿռ��֪ʶ��Խ�������
	vctPlatID.clear();
	//�����Ŵ���vctPlatID��
	for(itePlat = vctShipTemp.begin(); itePlat != vctShipTemp.end(); ++itePlat)			
	{
		vctPlatID.push_back(itePlat->nPlatHao);
	}
	//vector���
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
		if ((*iteKng)[0] == 1)	//����Ϊ����
		{
			vctModelID.push_back(theApp.m_DataBase.m_DataBaseData.SpaceGrpID[i]);
			//��Ҫ�������ݵı������
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
			//�����vector��֮ǰҪ���
			vctModelNum.push_back(TGroupN);			//��ģ���Ӧ��Ŀ��Ⱥ��
			vvEGN.push_back(EGN);
			vctiAverSpeed.push_back(iAverSpeed);
			vctAverAzmith.push_back(AverAzmith);
			vvEveryGroup.push_back(EveryGroup);
			vvKthreatgree.push_back(vctKthreatgree);
		}
	}
	//�ҳ��ɻ������С��
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
	
	if (dMink > -1)			//�ҵ�
	{
		//�����ɻ��ռ�Ⱥ����ṹ
		vctShipLink.nPlanTypeN = vctModelNum[dMink];         //�ռ�Ⱥ�ĸ���
		for (i = 0; i < vctModelNum[dMink]; ++i)		//ÿһ���ռ�Ⱥ��
		{
			vctShipLink.vctPlanGroupN.push_back(vvEGN[dMink][i]);			//ÿ��Ⱥ��ƽ̨������
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
						//ȡ����ƽ̨�����ͺ�̬��,д������ṹ
						vctPlatType.push_back(itePlat->nTrackOBjType);
						vctPlatTaishi.push_back(itePlat->nPlatBasicSituation);
					}
				}
			}
			vctShipLink.vvPlanGroupHao.push_back(vctTemp);
			vctShipLink.vvPlanGroupOBjType.push_back(vctPlatType);
			vctShipLink.vvPlanEvent.push_back(vctPlatTaishi);
			vctShipLink.vctPlanThreatDegree.push_back(vvKthreatgree[dMink][i]);		//ÿ��Ⱥ���ۺ���в��
		}
		vctShipLink.nPlanSpacMBHao = vctModelID[dMink];
	}
}


/////////////////////////////////////////////////////////////////////////////////////////
//***********            ���¿ռ�Ⱥ����ڵ㴦����ж����ģ��          ****************//
//********                    (2014-08-4  Liuyian)                           **********//
//********     ���룺SpaceFlag�Ƿ��ǵ�һ��                                         ****//
//********           �����ѻ���Ⱥ�ķɻ���Ϣ                                  **********//
//********           �ϴ��ѻ���Ⱥ�Ľ�����Ϣ                                  **********//
//********     ��������������ڰ�ṹ��Ϣ									 **********//
//********			 nFlag��ʾ�Ƿ�̼���һ��								 **********//
/////////////////////////////////////////////////////////////////////////////////////////
void CAlgorithm::Updata_SpaceGroups_Situation_LinKJudge_Process_Modul(int nSpaceFlag, SPACE_TARGET PlaneData, SPACE_TARGET ShipData, int nFlag)
{
	int i;
	int nPlaneFlag(0);			//�ɻ������и���
	int nShipFlag(0);			//���������и���
/*	VCT_INT::iterator itevctTemp;*/
	VV_INT::iterator itevv;
	VCT_INT vctTemp;
	if (nSpaceFlag == 0)				//�״�
	{
		//1  ֱ�ӽ������Ŀռ�Ⱥ�������ݣ�д��ռ�Ⱥ������
        //11 �ȷɻ���
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
		//12 �ٽ�����
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
		//2  ͬʱ�����ڰ�ģ�͵Ŀռ�Ⱥ�ṹ����	
		//21 �ɻ�
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
		//22 �ٽ�����
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
	else								//���״�
	{
		//1 ÿ�ε��ã�ÿ��ֻ����һ�λ��֣���ÿ��һ��ģ�����
		//��ȡ����ǰ�����Ŀռ���������
		//1.1 �ȷɻ���
		if (m_PlaneSpaceLink.nPlanSpacMBHao == PlaneData.nPlanSpacMBHao)			//�ҵ�,�ۼ�ģ��ڵ��ϵ���Ϣ
		{
			//���������Ͼɽڵ�����
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
			
			++m_PlaneSpaceLink.nPlanCumulativeN;		//�ۻ�����1

			//�ۻ�����5�Σ���ʼ���ºڰ�
			if (m_PlaneSpaceLink.nPlanCumulativeN >= 5)			
			{
				nPlaneFlag = 1;
				//ͬʱ���������ºڰ�ģ�͵Ŀռ�Ⱥ�ṹ����
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
				
				m_PlaneSpaceLink.nPlanCumulativeN = 1;		//���¿�ʼ�ۻ�	
			}
		} 
		else			//û�ҵ���Ϊ��ģ��,ֱ���滻ԭ�ڵ�����
		{
			//���·ɻ��ռ�Ⱥ����
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
			//ͬʱ�����ɻ��ڰ�ṹ���ݲ�����
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
			
			m_PlaneSpaceLink.nPlanCumulativeN = 1;		//���¿�ʼ�ۻ�	
		}
		//1.2 �����࣬ͬ�ɻ���
		if (m_ShipSpaceLink.nPlanSpacMBHao == ShipData.nPlanSpacMBHao)			//�ҵ�,�ۼ�ģ��ڵ��ϵ���Ϣ
		{
			//���������Ͼɽڵ�����
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
			
			++m_PlaneSpaceLink.nPlanCumulativeN;	//�ۻ�����1
		
			if (m_ShipSpaceLink.nPlanCumulativeN >= 5)
			{
				nShipFlag = 1;
				//ͬʱ���������ºڰ�ģ�͵Ŀռ�Ⱥ�ṹ����
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
				
				m_PlaneSpaceLink.nPlanCumulativeN = 1;	//���¿�ʼ����
			}
		} 
		else			//û�ҵ���Ϊ��ģ��,ֱ���滻ԭ�ڵ�����
		{
			//���½����ռ�Ⱥ����
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
			//ͬʱ���������ڰ�ṹ���ݲ�����
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
		//2 ��ͬģ����������������ݣ����ºڰ��ϵĿռ�Ⱥ�ڵ�����
		//2.1 �ҵ��ɻ��������������ݣ�����

		//2.2 �ҵ������������������ݣ�����
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



//////////////////////////////����Ⱥ//////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////////////////
//                               ���ֱ����  (�Ѳ��Թ���ֱ�ӵ���)                      //
//        ע��������ת��������                                                         //
//       ����: �����������N
//             ������GiveType[]
//       �������������SumType
/////////////////////////////////////////////////////////////////////////////////////////
void CAlgorithm::ObjectType_Moretomin_Moudul(int N, VCT_INT& GiveType, int& SumType)
{
	int i,j,k,n;
	int temp[20] = {0};
	int Value[20] = {0};     //��ͳ�Ƶĸ������
	int OBjType[20] = {0};
	
	int Max, Hao;
	
	//��ת��
	for(i = 0; i < N; i++)
	{
		temp[i] = GiveType[i];	
	}
	
	//����ͬ���ͳ��֧�ָ���
	k = 0;//���ڷŲ�ͬ����������0��ʼ
	for(i = 0; i < N; i++)
	{
		if(temp[i] != 0)//û�����
		{		
			n = 1;//ͳ�Ƹ������
			for(j = i+1; j < N; j++)
			{
				if(temp[i] == temp[j])
				{
					n++;
					temp[j] = 0;//��0				
				}		
			}//for j
			
			Value[k] = n;        //����ͳ�Ƹ���
			OBjType[k] = temp[i];//��Ÿ�����
			k++;
		}//�����Ѵ����	
	}//for i
	
	//�ٴ�k���ҳ������
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
	
	SumType = OBjType[Hao];//�������յ��������
}


/////////////////////////////////////////////////////////////////////////////////////////
//                               ����Ⱥ֪ʶ����ģ�����                                //
//********                    (2014-10-18  Liuyian)                           **********//
//             ���룺                                                         *********//
//                   ���κڰ��ϵĿռ�Ⱥ�ṹ����                               *********//
//                   ����Ⱥ������֪ʶ��                                        ********//
//********     �������������Ⱥ�ࡢ����Ŀ                                    **********//
//********           ��������Ⱥ����ṹ����FunLink                           **********//
/////////////////////////////////////////////////////////////////////////////////////////
void CAlgorithm::FunctionGroup_Reason_PlatSituationEvent_datamodul(SPACE_BLACK& PlaneBlack, SPACE_BLACK& ShipBlack, FUN_GROUP_LINK& FunLink, int& nFlag)
{
	int i, j;
	int nFindFlag;
	int nGroupNum;
	int nPlatNum;
	int nObjtype;		//���ֱ���Ľ��
	int nPlatEvent;		//���ֱ���Ľ��
	VCT_INT vctPlaneModelID;		//����ɻ�����Ⱥģ���
	VCT_INT vctPlaneEvent;			//����ɻ�����Ⱥ�¼�
	VCT_INT vctShipModelID;			//���潢������Ⱥģ���
	VCT_INT vctShipEvent;			//���潢������Ⱥ�¼�
	//�ȴ���ɻ�Ⱥ
	VCT_INT vctObjtype;
	VCT_INT vctPlantEvent;

	vctPlaneModelID.clear();
	vctPlaneEvent.clear();
	vctShipModelID.clear();
	vctShipEvent.clear();

	vctObjtype.clear();
	vctPlantEvent.clear();
	for (nGroupNum = 0; nGroupNum < PlaneBlack.nPlanTypeN; ++nGroupNum)		//�Էɻ�Ⱥ����ѭ��
	{
		vctObjtype.clear();
		vctPlantEvent.clear();
		for (nPlatNum = 0; nPlatNum < PlaneBlack.vctPlanGroupN[nGroupNum]; ++nPlatNum)			//ÿ��Ⱥ�е�ÿһ��Ŀ��
		{
			//ȡĿ�����ͺ�ƽ̨̬��
			vctObjtype.push_back(PlaneBlack.vvPlanGroupOBjType[nGroupNum][nPlatNum]);
			vctPlantEvent.push_back(PlaneBlack.vvPlanEvent[nGroupNum][nPlatNum]);
		}
		//���þ��ֱ����,��ø�ȺĿ������
		ObjectType_Moretomin_Moudul(nPlatNum, vctObjtype, nObjtype);
		//���þ��ֱ����,��ø�Ⱥ��̬��
		ObjectType_Moretomin_Moudul(nPlatNum, vctPlantEvent, nPlatEvent);

		//����֪ʶ��
		nFindFlag = 0;
		for (i = 0; i < theApp.m_DataBase.m_DataBaseData.FunModelID.size(); ++i)
		{
			if (nObjtype == theApp.m_DataBase.m_DataBaseData.vctDbFunKng[i][0] && nPlatEvent == theApp.m_DataBase.m_DataBaseData.vctDbFunKng[i][1])				//�ҵ�
			{
				vctPlaneModelID.push_back(theApp.m_DataBase.m_DataBaseData.FunModelID[i]);		//����ģ���
				vctPlaneEvent.push_back(theApp.m_DataBase.m_DataBaseData.FunModelID[i]);			//���湦��Ⱥ�¼�
				nFindFlag = 1;
				break;
			}
		}
		//û���ҵ�
		if (nFindFlag == 0)
		{
			vctPlaneEvent.push_back(10);			//����
			vctPlaneModelID.push_back(-1);
		}
	}
	//�ٴ�����Ⱥ

	for (nGroupNum = 0; nGroupNum < ShipBlack.nPlanTypeN; ++nGroupNum)		//�Խ���Ⱥ����ѭ��
	{
		vctObjtype.clear();
		vctPlantEvent.clear();
		for (nPlatNum = 0; nPlatNum < ShipBlack.vctPlanGroupN[nGroupNum]; ++nPlatNum)			//ÿ��Ⱥ�е�ÿһ��Ŀ��
		{
			//ȡĿ�����ͺ�ƽ̨̬��
			vctObjtype.push_back(ShipBlack.vvPlanGroupOBjType[nGroupNum][nPlatNum]);
			vctPlantEvent.push_back(ShipBlack.vvPlanEvent[nGroupNum][nPlatNum]);
		}
		//���þ��ֱ����,��ø�ȺĿ������
		ObjectType_Moretomin_Moudul(ShipBlack.vctPlanGroupN[nGroupNum], vctObjtype, nObjtype);
		//���þ��ֱ����,��ø�Ⱥ��̬��
		ObjectType_Moretomin_Moudul(ShipBlack.vctPlanGroupN[nGroupNum], vctPlantEvent, nPlatEvent);
		
		//����֪ʶ��
		nFindFlag = 0;
		for (i = 0; i < theApp.m_DataBase.m_DataBaseData.FunModelID.size(); ++i)
		{
			if (nObjtype == theApp.m_DataBase.m_DataBaseData.vctDbFunKng[i][0] && nPlatEvent == theApp.m_DataBase.m_DataBaseData.vctDbFunKng[i][1])				//�ҵ�
			{
				vctShipModelID.push_back(theApp.m_DataBase.m_DataBaseData.FunModelID[i]);		//����ģ���
				vctShipEvent.push_back(theApp.m_DataBase.m_DataBaseData.FunEventID[i]);			//���湦��Ⱥ�¼�
				nFindFlag = 1;
				break;
			}
		}
		//û���ҵ�
		if (nFindFlag == 0)
		{
			vctShipEvent.push_back(10);			//����
			vctShipModelID.push_back(-1);
		}
		
	}

	//////////////////////��������ṹ����/////////////////////////////////////
	
	FunLink.nFuncGroupN = PlaneBlack.nPlanTypeN + ShipBlack.nPlanTypeN;
	//�����ɻ�����ṹ
	for (i = 0; i < PlaneBlack.nPlanTypeN; ++i)
	{
		FunLink.vctFuncMBHao.push_back(vctPlaneModelID[i]);			//ģ���
		FunLink.vctFuncGpH.push_back(i);								//���
		FunLink.vctFuncGroupTrackN.push_back(PlaneBlack.vctPlanGroupN[i]);		//Ⱥ��Ŀ����
		FunLink.vvFuncGroupHao.push_back(PlaneBlack.vvPlanGroupHao[i]);			//����
		FunLink.vvFuncGroupOBjType.push_back(PlaneBlack.vvPlanGroupOBjType[i]);	//����
		FunLink.vctFuncThreatDegree.push_back(PlaneBlack.vctPlanThreatDegree[i]);	//��в��
		FunLink.vctFuncGroupEvent.push_back(vctPlaneEvent[i]);					//̬��
	}

	//������������ṹ
	for (i = PlaneBlack.nPlanTypeN; i < m_FunLink.nFuncGroupN; ++i)
	{
		j = i - PlaneBlack.nPlanTypeN;
		FunLink.vctFuncMBHao.push_back(vctPlaneModelID[i]);			//ģ���
		FunLink.vctFuncGpH.push_back(i);								//���
		FunLink.vctFuncGroupTrackN.push_back(ShipBlack.vctPlanGroupN[j]);		//Ⱥ��Ŀ����
		FunLink.vvFuncGroupHao.push_back(ShipBlack.vvPlanGroupHao[j]);			//����
		FunLink.vvFuncGroupOBjType.push_back(ShipBlack.vvPlanGroupOBjType[j]);	//����
		FunLink.vctFuncThreatDegree.push_back(ShipBlack.vctPlanThreatDegree[j]);	//��в��
		FunLink.vctFuncGroupEvent.push_back(vctPlaneEvent[i]);					//̬��
	}
	FunLink.nFuncGroupMBNum = m_FunLink.nFuncGroupN;

	nFlag = 1;
}



/////////////////////////////////////////////////////////////////////////////////////////
//                ����Ⱥ������ڰ�ڵ㴴�������ģ�����                               //
//********                    (2014-10-20  Liuyian)                          **********//
//             ���룺 nFuncFlag=0��ʾ�״Σ�����Ϊ���״�                       *********//
//                   ���β����Ĺ���Ⱥ����ṹ����                             *********//
//                   �ϴα���Ĺ���Ⱥ����ṹ����                              ********//
//                   �ϴα���Ĺ���Ⱥ�ڰ�ṹ����                              ********//
//********     ��������¹���Ⱥ��������                                      **********//
//********           �����Ƿ񴥷����ºڰ�,���ºڰ�ṹ����nFlag              **********//
/////////////////////////////////////////////////////////////////////////////////////////
void CAlgorithm::FunctionGroup_LinkProcess_PlatSituationEvent_datamodul(int nFuncFlag, FUN_GROUP_LINK& FunLink, int& nFlag)
{
	int i, j, k;
	VCT_INT vctLink;			//����Ⱥ������δ������Ľڵ�
	VCT_INT vctNowData;			//��ǰ�õ��Ĺ���Ⱥ��δ������Ľڵ�
	vctLink.assign(m_FunLink.nFuncGroupN, 0);
	vctNowData.assign(FunLink.nFuncGroupN, 0);
	if (nFuncFlag == 0)			//�״�
	{
		//������д������
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
		//������д��ڰ�
		theApp.m_FunBlack.lTimeStamp = 100000000;
		theApp.m_FunBlack.nFuncGroupN = FunLink.nFuncGroupN;
		theApp.m_FunBlack.vctFuncGpHao = FunLink.vctFuncGpH;
		theApp.m_FunBlack.vctFuncGroupEvent = FunLink.vctFuncGroupEvent;
		theApp.m_FunBlack.vctFuncGroupTrackN = FunLink.vctFuncGroupTrackN;
		theApp.m_FunBlack.vctFuncThreatDegree = FunLink.vctFuncThreatDegree;
		theApp.m_FunBlack.vvFuncGroupTrackHao = FunLink.vvFuncGroupHao;
		theApp.m_FunBlack.vvFuncGroupOBjType = FunLink.vvFuncGroupOBjType;

		nFlag = 1;			//������һ��
	}
	else						//���״�
	{
		//1.  ���¾�����
		for (i = 0; i < FunLink.nFuncGroupN; ++i)
		{
			for (j = 0; j < m_FunLink.nFuncGroupN; ++j)
			{
				if (FunLink.vctFuncMBHao[i] == m_FunLink.vctFuncMBHao[j])		//�ҵ�,���´�ģ���Ӧ�Ĺ���Ⱥ����Ϣ
				{
					vctNowData[i] = 1;
					vctLink[j] = 1;

					//1.1 ���¾ɽڵ�����,���滻�ù���Ⱥ����
					m_FunLink.vctFuncGroupTrackN[j] = FunLink.vctFuncGroupTrackN[i];
					m_FunLink.vvFuncGroupHao[j].clear();
					m_FunLink.vvFuncGroupHao[j] = FunLink.vvFuncGroupHao[i];
					m_FunLink.vvFuncGroupOBjType[j].clear();
					m_FunLink.vvFuncGroupOBjType[j] = FunLink.vvFuncGroupOBjType[i];
					m_FunLink.vctFuncThreatDegree[j] = FunLink.vctFuncThreatDegree[i];
					m_FunLink.vctFuncGroupEvent[j] = FunLink.vctFuncGroupEvent[i];
					m_FunLink.vctFuncCumulativeN[j] = m_FunLink.vctFuncCumulativeN[j] + 1;
					//1.2 �������ºڰ�ģ�͵Ĺ���Ⱥ�ṹ����
					if (m_FunLink.vctFuncCumulativeN[j] >= 5)
					{
						 
						for (k = 0; k < theApp.m_FunBlack.nFuncGroupN; ++k)
						{
							if (m_FunLink.vctFuncGpH[j] == theApp.m_FunBlack.vctFuncGpHao[k])		//�ҵ��ù���Ⱥ
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
		//2.  ���������ڵ�
		for (i = 0; i < FunLink.nFuncGroupN; ++i)
		{
			if (vctNowData[i] == 0)			//�����ڵ�
			{
				//1. ׷�ӵ�����֮��
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
				
				//2. ���ºڰ�
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
		//3.  ���ºڰ�����
			//3.1  �ȸ����Ѿ����ڵĽڵ�

			//3.2  �ٸ����³��ֵĽڵ�
	
	}
}




///////////////////////////////�໥����Ⱥ///////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////////////////
//                      �໥����Ⱥ֪ʶ����������������ģ�����                       //
//********                    (2014-08-5  Liuyian)                           **********//
//             ���룺                                                         *********//
//                   ���κڰ��ϵĹ���Ⱥ�ṹ����                               *********//
//                   �໥����Ⱥ������֪ʶ��                                    ********//
//********     ����������໥����Ⱥ����ṹ����                              **********//
//                   ������������ͺڰ�����ģ��                                        //
/////////////////////////////////////////////////////////////////////////////////////////
void CAlgorithm::Interaction_KnowlegeReason_Process_datamodul(FUN_GROUP_BLACK& m_FunBlack, INTERGROUPLINK& NodeLink)
{
	int i, j;
	int nImFunGNum;			//�໥����Ⱥ�п��ܵĹ���Ⱥ�ĸ���
	//�����ṹ
	//�໥����֪ʶ��:  1���䡢2��Ѳ�ߣ�3��������4�����أ�5����ը��6��ͻ����7�����š�8��Ԥ��,9:���      
    //1: ��ȡ��ǰ����Ⱥ
	for (i = 0; i < m_FunBlack.nFuncGroupN; ++i)
	{
// 		nImFunGNum = 0;
// 		++nImFunGNum;
// 		//1.1:����֪ʶ�⣬�����к��˹���Ⱥ��֪ʶ�ҳ�������������صĹ���Ⱥ��ŷŵ�һ��������
// 		for ()				 //��ȡ֪ʶ��
// 		{
// 			//1.1.1:  �Ȳ��Ҹ���֪ʶ���Ƿ��д˹���Ⱥ̬������
// 			for ()			//֪ʶ��ѭ��
// 			{
// 
// 				if ()				//�и���
// 				{
// 				}
// 			}
// 			//1.1.2:  ���ڸ����ҵ���֪ʶ���������ж�Ӧ������̬�ƶ���
// 			if ()
// 			{
// 				for ()		//֪ʶ��ѭ��
// 				{
// 				}
// 			}
// 		}
// 		//1.2: �ȴ����Ըù���Ϊ������,�ų�����FuncGroupEventValue[i][n]����ʱ��ŵ�,�������̬�ƣ�ÿ��̬��ֻ����1����
// 		for ()
// 		{
// 		}
	}

	//2: �໥����Ⱥ�������ϲ����汣���TempEventValue[i][m[i]]�еĹ���

	//3: �ٴ�������ϲ��������

	//4: �ٸ����໥����Ⱥ�еĸ�̬�ƣ����ϸ���Ⱥ����������,ͬʱ��������ṹ����
}




/////////////////////////////////////////////////////////////////////////////////////////
//                           �໥����Ⱥ������ڰ崦��ģ�����                          //
//********                    (2014-10-22  Liuyian)                          **********//
//             ���룺InterFlag�״α�־��0Ϊ�״�                               *********//
//                   ���β������໥����Ⱥ�ĸ�����ṹ����NodeLink             *********//
//                   �ϴα�����໥����Ⱥ�ṹ����                              ********//
//********     ��������»򴴽��໥����Ⱥ������ڰ�����                      **********//
/////////////////////////////////////////////////////////////////////////////////////////
void CAlgorithm::InteractGroup_LinkProcess_SituationEvent_datamodul(int nInterFlag, INTERGROUPLINK& NodeLink)
{
	int i, j, k, m, g;
	INTERGROUP LinkTemp;
	INTERBLACKNODE BlackTemp;
	VCT_INT vctOldFlag;		//���m_InterGBlackδ�����������Ⱥ����0��ʾ��
	VCT_INT vctNewFlag;		//���NodeLink��������δ������������Ⱥ,0��ʾδ������

	vctOldFlag.assign(theApp.m_InterGBlack.size(), 0);
	vctNewFlag.assign(NodeLink.size(), 0);
	if (nInterFlag == 0)				//�״�
	{
		//1.1 ֱ�Ӵ�ŵ�����ṹ��
		for (i = 0; i < NodeLink.size(); ++i)
		{
			LinkTemp.nInteGroupSeriNum = NodeLink[i].nInteGroupSeriNum;
			LinkTemp.nInteCumulativeN = 1;
			LinkTemp.nInteractGroupSGN = NodeLink[i].nInteractGroupSGN;
			//��=��ֵ��ʱ����ԭ��������������ȫ��������˴˴�����clear
			LinkTemp.vctInteGroupHao = NodeLink[i].vctInteGroupHao;
			LinkTemp.vctInteGroupTrackNum = NodeLink[i].vctInteGroupTrackNum;
			LinkTemp.vctInterEvent = NodeLink[i].vctInterEvent;
			LinkTemp.vvInterOBjType = NodeLink[i].vvInterOBjType;
			LinkTemp.vvIntertrackHao = NodeLink[i].vvIntertrackHao;
			m_InterGLink.push_back(LinkTemp);
		}

		//1.2 ͬʱ,Ҳֱ��д�뵽�ڰ��ϵ��໥����Ⱥ�ṹ������
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
		//2.1 �����໥����Ⱥ���´������ڲ������ǰ�ͬһ��Ⱥ����̬��ֻ��һ���໥����Ⱥ�У��ʲ���ʱֻҪ��һ����Ⱥƥ�䣬�͸���֮
		for (i = 0; i < NodeLink.size(); ++i)		//�໥����Ⱥ����
		{
			for (j = 0; j < NodeLink[i].nInteractGroupSGN; ++j)			//������Ⱥ
			{
				for (k = 0; k < m_InterGLink.size(); ++k)		//���ںڰ��е��໥����Ⱥ�ĸ���
				{
					for (m = 0; m < m_InterGLink[i].nInteractGroupSGN; ++m)	//�ڰ���ĳ���໥����Ⱥ�е�������Ⱥ
					{
						if (NodeLink[i].vctInterEvent[j] == theApp.m_InterGBlack[k].vctInterEvent[m])			//�ҵ�
						{
							vctNewFlag[i] = 1;
							vctOldFlag[k] = 1;
							//���¾ɽڵ�����,���õ�ǰ���滻�þ�����Ⱥ�в�������(������þɵ�)
							m_InterGLink[k].nInteractGroupSGN = NodeLink[i].nInteractGroupSGN;
							m_InterGLink[k].dSumThreatDegree = NodeLink[i].dSumThreatDegree;
							m_InterGLink[k].vctInteGroupTrackNum = NodeLink[i].vctInteGroupTrackNum;
							m_InterGLink[k].vctInteGroupHao = NodeLink[i].vctInteGroupHao;
							m_InterGLink[k].vctInterEvent = NodeLink[i].vctInterEvent;
							m_InterGLink[k].vvInterOBjType = NodeLink[i].vvInterOBjType;
							m_InterGLink[k].vvIntertrackHao = NodeLink[i].vvIntertrackHao;
							m_InterGLink[k].nInteCumulativeN = m_InterGLink[k].nInteCumulativeN + 1;
							if (m_InterGLink[k].nInteCumulativeN >= 5)		//���ºڰ�
							{
								//�������ºڰ�ģ�͵��໥����Ⱥ�ṹ����
								for (g = 0; g = theApp.m_InterGBlack.size(); ++g)			//�ںڰ����ҵ���ͬ��ŵ�����
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
							//�����������Ϊ���Ƴ�ѭ��
							m = m + theApp.m_InterGBlack[i].nInteractGroupSGN;
							k = k + m_InterGLink.size();
						}
					}
				}
			}
		}
		//2.2: ���������ڵ�,�������໥����Ⱥ
       	//�����໥����Ⱥ���´������ڲ������ǰ�ͬһ��Ⱥ����̬��ֻ��һ���໥����Ⱥ�У��ʲ���ʱֻҪ��һ����Ⱥƥ�䣬�͸���֮
		for (i = 0; i < NodeLink.size(); ++i)
		{
			if (vctNewFlag[i] == 0)				//�������ڵ�
			{
				//����ǰ�ڵ�׷�ӵ��������
				LinkTemp.nInteGroupSeriNum = NodeLink.size();
				LinkTemp.nInteCumulativeN = 1;
				LinkTemp.nInteractGroupSGN = NodeLink[i].nInteractGroupSGN;
				//��=��ֵ��ʱ����ԭ��������������ȫ��������˴˴�����clear
				LinkTemp.vctInteGroupHao = NodeLink[i].vctInteGroupHao;
				LinkTemp.vctInteGroupTrackNum = NodeLink[i].vctInteGroupTrackNum;
				LinkTemp.vctInterEvent = NodeLink[i].vctInterEvent;
				LinkTemp.vvInterOBjType = NodeLink[i].vvInterOBjType;
				LinkTemp.vvIntertrackHao = NodeLink[i].vvIntertrackHao;
				m_InterGLink.push_back(LinkTemp);

				//�����µĺڰ����ݲ�����
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


		//2.3: ���ºڰ��ϵĽڵ�����

			//2.3.1: �ȸ��´��ڵĽڵ�

			//2.3.2: �ٴ��������ĺڰ�ڵ�
	}
		
}