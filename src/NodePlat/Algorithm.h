// Algorithm.h: interface for the CAlgorithm class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ALGORITHM_H__7C7484B4_7CF4_448E_9522_7B29A17E7FE2__INCLUDED_)
#define AFX_ALGORITHM_H__7C7484B4_7CF4_448E_9522_7B29A17E7FE2__INCLUDED_

#include "StdAfx.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CAlgorithm  
{
public:
	MAP_BASIC_EVENT  m_mapBasicEvent;
	VCT_Cooperative_FUSIDENTIINFOR m_ForeData;
	VCT_Cooperative_FUSIDENTIINFOR m_NowData;
	//平台链表
	MAP_PLAT_LINK m_Plat_link;
	//飞机类空间链表
	SPACE_TARGET m_PlaneSpaceLink;	
	//舰船类空间链表
	SPACE_TARGET m_ShipSpaceLink;
	//功能群链表
	FUN_GROUP_LINK m_FunLink;
	//相互作用群链表
	INTERGROUPLINK m_InterGLink;
public:
	CAlgorithm();
	virtual ~CAlgorithm();
	//基本事件层
	int CopyData(VCT_Cooperative_FUSIDENTIINFOR& DstData, VCT_Cooperative_FUSIDENTIINFOR& SourceData);
	int BufferData(VCT_Cooperative_FUSIDENTIINFOR& ForeBufferData, VCT_Cooperative_FUSIDENTIINFOR& NowBufferData, VCT_Cooperative_FUSIDENTIINFOR NowData);
	int CalculateSpeed(VCT_Cooperative_FUSIDENTIINFOR& TaishiFore);
	int CalculateAddSpeed(VCT_Cooperative_FUSIDENTIINFOR& TaishiFore, VCT_Cooperative_FUSIDENTIINFOR& TaishiNow);
	int ThreatDegree(VCT_Cooperative_FUSIDENTIINFOR& TaishiNow);
	double TrackThreatDegree(VCT_Cooperative_FUSIDENTIINFOR::iterator iteNow);
	double ESMThreatDegree(VCT_Cooperative_FUSIDENTIINFOR::iterator iteNow);
	VCT_Cooperative_FUSIDENTIINFOR::iterator FindSameData(unsigned long lAutonum, VCT_Cooperative_FUSIDENTIINFOR& ForeData);
	VCT_ESM_MSG::iterator ESMFindSameData(unsigned long lAutonum, VCT_ESM_MSG& vctFusEsm);
	VCT_COMM_MSG::iterator COMFindSameData(unsigned long lAutonum, VCT_COMM_MSG& vctFusCom);
	void KnowLege_Database_Track_EventReason(VCT_INT& vctTrackEvent, int& nModelID, int& nEventType);
	void KnowLege_Database_ESM_EventReason(VCT_INT& vctTrackEvent, int& nModelID, int& nEventType);
	void KnowLege_Database_COM_EventReason(VCT_INT& vctTrackEvent, int& nModelID, int& nEventType);
	void CharacterChangeJudge(VCT_Cooperative_FUSIDENTIINFOR& ForeData, VCT_Cooperative_FUSIDENTIINFOR& NowData);
	void Basic_Event_First_LinKJudge_Process_Modul(VCT_Cooperative_FUSIDENTIINFOR& NowData, int& nTriggleFlag) ;
	void Basic_Event_NonFirst_LinKJudge_Process_Modul(VCT_Cooperative_FUSIDENTIINFOR& NowData, int& nTriggleFlag);
	void Basic_Event(VCT_Cooperative_FUSIDENTIINFOR& NowFusData, int& nTriggleFlag);
	//平台层
	void Plat_KnowLedge_Basic_Situation_Reason_Modil(MAP_EVENT_BLACK& m_EventBlack,double& Azimuth,int nFlag, int& nBack, MAP_PLAT_LINK& m_List_temp);
	void Plat_NonFirst_KnowLedge_Basic_Situation_Reason_Modil(MAP_PLAT_LINK& m_Link_temp, int& nBackF);
	//空间层
	void Metri_Cluttle_Modul(int pp, double Rd0, VV_DOUBLE& AA, VCT_INT& LLCC, int& TGroupN, VCT_INT& EGN, VV_INT& EveryGroup);
	void dVPspeed_dAzmith_Modul(int& TGroupN, VCT_INT& EGN, VV_INT& EveryGroup, VCT_PLAT_BLACK& vctTgt, double& iAverSpeed, double& AverAzmith, VCT_DOUBLE& Kthreatgree);
	void SpaceGroup_Reason_PlatSituationEvent_datamodul(MAP_PLAT_BLACK& m_Plat_Black, SPACE_TARGET& vctPlaneLink, SPACE_TARGET& vctShipLink, int& BFlag);
	void Updata_SpaceGroups_Situation_LinKJudge_Process_Modul(int nSpaceFlag, SPACE_TARGET PlaneData, SPACE_TARGET ShipData, int nFlag);
	//功能群
	void ObjectType_Moretomin_Moudul(int N, VCT_INT& GiveType, int& SumType);
	void FunctionGroup_Reason_PlatSituationEvent_datamodul(SPACE_BLACK& PlaneBlack, SPACE_BLACK& ShipBlack, FUN_GROUP_LINK& FunLink, int& nFlag);
	void FunctionGroup_LinkProcess_PlatSituationEvent_datamodul(int nFuncFlag, FUN_GROUP_LINK& FunLink, int& nFlag);
	//相互作用群
	void Interaction_KnowlegeReason_Process_datamodul(FUN_GROUP_BLACK& m_FunBlack, INTERGROUPLINK& NodeLink);
	void InteractGroup_LinkProcess_SituationEvent_datamodul(int nInterFlag, INTERGROUPLINK& NodeLink);

};

#endif // !defined(AFX_ALGORITHM_H__7C7484B4_7CF4_448E_9522_7B29A17E7FE2__INCLUDED_)
