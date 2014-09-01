#include "SingleIdentify.h"
#include <vector>
#include <string>
#include <iostream>
#include <math.h>

using namespace std;

#define DTN 8000

typedef struct __STR//方位聚类后，同方位数据结构
{
	   // 	float fReachAzimuth;  //到达方位
	unsigned long lAutonum;			//综合批号
	VCT_ESM_MSG VecEsm;
	VCT_COMM_MSG VecCom;
	VCT_TRACE_MSG VecTrack;	
}STR;
typedef vector<STR> STRVEC;	//存储同方位的各个辐射源信息
STRVEC vStr;

typedef struct __STTYPE //举手表决要用的数据结构
{
	unsigned long lAutonum;   //综合批号
//	char *type;    //目标类型
	unsigned short sType;  //平台类型
	double  con;   //可信度	
}STTYPE;
typedef vector<STTYPE*> TYPEVEC;

//IDENTIINFOR IdentStr;
VCT_IDENTIINFOR_MSG IdentifyVec;//最终识别结果

STRVEC* Cluster_UniNum(VCT_ESM_MSG* pEsmStatusVec, VCT_COMM_MSG* pComStatusVec, VCT_TRACE_MSG* pTrackStatusVec)
{
	float fTrackAz(0.0);			// 敌方航迹方位角	
	/*float fTrackEz(0.0);*/		
	float fReachA(0.0);          // 敌方到达方位角
	/*float tmpElevation(0.0);*/
	float fA(0.0);              // 敌方方位角差
	/*float detElevation(0.0);*/
	int TN = DTN;
	int dtn = 0;
	STR Str;//临时存储某一综合批号的所有信息
 	STRVEC* pvStr = &vStr;
//	STRVEC* pvStr = new STRVEC;
	// 用来遍历的迭代器
	VCT_TRACE_MSG::iterator iteTrack;
	VCT_ESM_MSG::iterator iteEsm;
	VCT_COMM_MSG::iterator iteCom;
	VCT_ESM_MSG::iterator itEsm;
	VCT_COMM_MSG::iterator itCom;
	//用来清空的迭代器
	VCT_ESM_MSG::iterator iteE;
	VCT_COMM_MSG::iterator iteC;
	VCT_TRACE_MSG::iterator iteT;
	Accuracy Acc;
	Acc.dirAcc = 1.0;
	//有航迹信息
	for (iteTrack = (*pTrackStatusVec).begin(); iteTrack != (*pTrackStatusVec).end(); iteTrack ++)
	{
		/*清空Str*/
		for (iteT = Str.VecTrack.begin();iteT != Str.VecTrack.end();iteT ++)
		{
			memset(&(*iteT), 0, sizeof(TRACKSTATUS_MARK));
		}
		for (iteE = Str.VecEsm.begin();iteE != Str.VecEsm.end();iteE ++)
		{
			memset(&(*iteE), 0, sizeof(ESMSTATUS_MARK));
		}
		for (iteC = Str.VecCom.begin();iteC != Str.VecCom.end();iteC ++)
		{
			memset(&(*iteC), 0, sizeof(COMSTATUS_MARK));
		}
		Str.VecTrack.clear();
		Str.VecEsm.clear();
		Str.VecCom.clear();


		fTrackAz = (float)iteTrack->fAzimuth;	// 航迹提供的方位角

		/*对未编批的信息进行处理*/
		//航迹部分
		if (iteTrack->cJfFlag == 0)
		{
			iteTrack->lAutonum = TN;
			iteTrack->cJfFlag = '1';
			TN++;
			dtn = iteTrack->lAutonum;
			Str.lAutonum = dtn;//将合批号放入临时的Str
			Str.VecTrack.push_back(*iteTrack); //将合批的航迹信息放入临时的vTrack
		}		
		// ESM部分
		for (iteEsm = (*pEsmStatusVec).begin(); iteEsm != (*pEsmStatusVec).end(); iteEsm ++)
		{
			if (iteEsm->cJfFlag == 0)
			{
				fReachA = iteEsm->fReachAzimuth; // ESM提供的方位角
				fA = fabs(fReachA - fTrackAz);
				
				// 聚为一类
				if ((fA < Acc.dirAcc*2)/* && (detElevation < stEsmAcc.dirAcc*2)*/)
				{
					iteEsm->lAutonum = dtn;
					iteEsm->cJfFlag = '1';
					Str.VecEsm.push_back(*iteEsm);//将合批的ESM信息放入临时的vEsm
				}
			}
		}
		// COM部分
		for (iteCom = (*pComStatusVec).begin(); iteCom != (*pComStatusVec).end(); iteCom ++)
		{
			if (iteCom->cJfFlag == 0)
			{
				fReachA = iteCom->fReachAzimuth; // COM提供的方位角
				fA = fabs(fReachA - fTrackAz);
				
				// 聚为一类
				if ((fA < Acc.dirAcc*2)/* && (detElevation < stComAcc.dirAcc*2)*/)
				{
					iteCom->lAutonum = dtn;
					iteCom->cJfFlag = '1';
					Str.VecCom.push_back(*iteCom);//将合批的COM信息放入临时的vCom
				} 
			}
		}
		(*pvStr).push_back(Str);
	}

	//没有航迹信息，有ESM信息和COM信息
	for (iteEsm = (*pEsmStatusVec).begin(); iteEsm != (*pEsmStatusVec).end(); iteEsm ++)
	{
		/*清空Str*/
		for (iteT = Str.VecTrack.begin();iteT != Str.VecTrack.end();iteT ++)
		{
			memset(&(*iteT), 0, sizeof(TRACKSTATUS_MARK));
		}
		for (iteE = Str.VecEsm.begin();iteE != Str.VecEsm.end();iteE ++)
		{
			memset(&(*iteE), 0, sizeof(ESMSTATUS_MARK));
		}
		for (iteC = Str.VecCom.begin();iteC != Str.VecCom.end();iteC ++)
		{
			memset(&(*iteC), 0, sizeof(COMSTATUS_MARK));
		}
		Str.VecTrack.clear();
		Str.VecEsm.clear();
		Str.VecCom.clear();

		/*对未编批的信息进行处理*/
		if (iteEsm->cJfFlag == 0)
		{
			iteEsm->lAutonum = TN;
			TN++;
			dtn = iteEsm->lAutonum;
			iteEsm->cJfFlag = '1';
			fReachA = iteEsm->fReachAzimuth;
			Str.lAutonum = dtn;//将合批号放入临时的Str
			Str.VecEsm.push_back(*iteEsm);
			// ESM部分
			for (itEsm = iteEsm; itEsm != (*pEsmStatusVec).end(); itEsm ++)
			{
				if (itEsm->cJfFlag == 0)
				{
					fA = fabs(fReachA - itEsm->fReachAzimuth);
					
					// 聚为一类
					if ((fA < Acc.dirAcc*2)/* && (detElevation < stComAcc.dirAcc*2)*/)
					{
						itEsm->lAutonum = dtn;
						itEsm->cJfFlag = '1';
						Str.lAutonum = dtn;//将合批号放入临时的Str
						Str.VecEsm.push_back(*itEsm);//将合批的ESM信息放入临时的vEsm
					} 
				}
			}			
			// COM部分
		//	Str.VecCom.clear();
			for (iteCom = (*pComStatusVec).begin(); iteCom != (*pComStatusVec).end(); iteCom ++)
			{
				if (iteCom->cJfFlag == 0)
				{
					fA = fabs(fReachA - iteCom->fReachAzimuth);					
					// 聚为一类
					if ((fA < Acc.dirAcc*2)/* && (detElevation < stComAcc.dirAcc*2)*/)
					{
						iteCom->lAutonum = dtn;
						iteCom->cJfFlag = '1';
						/*Str.VecCom.clear();*/
						Str.VecCom.push_back(*iteCom);//将合批的COM信息放入临时的vCom
					} 
				}
			}
			(*pvStr).push_back(Str);
		}		
	}
	
	//只有COM信息
	for (iteCom = (*pComStatusVec).begin(); iteCom != (*pComStatusVec).end(); iteCom ++)
	{
		/*清空Str*/
		for (iteT = Str.VecTrack.begin();iteT != Str.VecTrack.end();iteT++)
		{
			memset(&(*iteT), 0, sizeof(TRACKSTATUS_MARK));
		}
		for (iteE = Str.VecEsm.begin();iteE != Str.VecEsm.end();iteE++)
		{
			memset(&(*iteE), 0, sizeof(ESMSTATUS_MARK));
		}
		for (iteC = Str.VecCom.begin();iteC != Str.VecCom.end();iteC++)
		{
			memset(&(*iteC), 0, sizeof(COMSTATUS_MARK));
		}
		Str.VecTrack.clear();
		Str.VecEsm.clear();
		Str.VecCom.clear();

		/*对未编批的信息进行处理*/
		if (iteCom->cJfFlag == 0)
		{
			iteCom->lAutonum = TN;
			TN++;
			dtn = iteCom->lAutonum;
			iteCom->cJfFlag = '1';
			fReachA = iteCom->fReachAzimuth;
			Str.lAutonum = dtn;//将合批号放入临时的Str
			Str.VecCom.push_back(*iteCom);
			// COM部分
			for (itCom = iteCom; itCom != (*pComStatusVec).end(); itCom ++)
			{
				if (itCom->cJfFlag == 0)
				{
					fA = fabs(fReachA - itCom->fReachAzimuth);
					/*detElevation = fabs(tmpElevation - fTrackEz);*/
					
					// 聚为一类
					if ((fA < Acc.dirAcc*2)/* && (detElevation < stComAcc.dirAcc*2)*/)
					{
						itCom->lAutonum = dtn;
						itCom->cJfFlag = '1';
						Str.lAutonum = dtn;//将合批号放入临时的Str
						/*Str.VecCom.clear();*/
						Str.VecCom.push_back(*itCom);//将合批的COM信息放入临时的vCom
					} 
				}
			}
			(*pvStr).push_back(Str);
		}		
	}
 	return(pvStr);

}


//举手表决 输入同一综合批号的esm、com、track信息（只含目标类型及其综合可信度），得到对应最高综合可信度的目标类型存入识别结果vev中
void ShowOfHands(TYPEVEC* pESMType, TYPEVEC* pCOMMType, TYPEVEC* pTRACKType, VCT_IDENTIINFOR_MSG* pIdentifyVec)
{
	TYPEVEC Type; //临时变量
    TYPEVEC Vcst; //存储不同目标类型及其综合可信度
	
	vector<int>  typenum;     //目标类型识别数
	vector<double>  typecon;  //综合可信度
	
	/*将所有信息放入type中*/
	Type.insert(Type.end(), (*pESMType).begin(), (*pESMType).end());
	Type.insert(Type.end(), (*pCOMMType).begin(), (*pCOMMType).end());
	Type.insert(Type.end(), (*pTRACKType).begin(), (*pTRACKType).end());
	/*将Type中第一条信息放入vcst*/
	Vcst.insert(Vcst.begin(), Type.begin(), Type.begin()+1);
	/*识别数*/
	typenum.push_back(1);
	/*迭代器*/
	TYPEVEC::iterator it = Type.begin();
	/*综合可信度*/
	typecon.push_back(1 - (*it)->con);
	/*举手表决*/
	for (it ++;it != Type.end();it ++)
	{
		int nflag = 0;
		int len = Vcst.size();
        for (int i = 0;i < len;i ++)//遍历Vcst
		{
			if (Vcst[i]->sType == (*it)->sType)
//			if (strcmp(Vcst[i]->type,(*it)->type) == 0)//目标类型一致
			{
				typenum[i] = typenum[i] + 1;//识别数+1
				typecon[i] = typecon[i] * (1 - (*it)->con);//计算可信度
				//break;
			}
			else
			{
				nflag ++;
			}
		}		
		if (nflag == len)//出现新的目标类型
		{
			STTYPE *tmp = new STTYPE;
			tmp->sType = (*it)->sType;
			tmp->con = (*it)->con;
			Vcst.insert(Vcst.end(), tmp);//将新的目标类型信息存入Vcst
            typenum.push_back(1);//新的目标类型识别数为1
			typecon.push_back(1 - (*it)->con);//新的目标类型可信度
		}
		
	}
	int nLen = Vcst.size();
	for (int k = 0;k < nLen;k ++)//综合可信度
	{
		typecon[k] = 1 - typecon[k];
	}
	/*依据最大综合可信度求出初步识别目标类型依据最大综合可信度*/
	double c = typecon[0];//最大综合可信度c
	int max = 0;//初步识别目标类型Vcst[max]->type
	for (k = 1;k < nLen;k ++)
	{
		if (typecon[k] > c)
		{
			c = typecon[k];
			max = k;
		}
	}
// 	char p=NULL;
// 	strcpy(&p, Vcst[max]->type);
// 	printf("综合批号   目标类型     综合可信度\n");
// 	printf("%d\t   %s\t\t%f\n", Vcst[max]->lAutonum, &p, c);
// 	
	/*将识别结果存入Identify*/
 	IDENTIINFOR IdentStr;
	IdentStr.lAutonum = Vcst[max]->lAutonum;//综合批号
	IdentStr.sPlatType = (*Vcst[max]).sType;//目标类型
	IdentStr.dConfidence = c;//综合可信度

	(*pIdentifyVec).push_back(IdentStr);
}

VCT_IDENTIINFOR_MSG* SingleIdentify(VCT_ESM_MSG* pEsmStatusVec, VCT_COMM_MSG* pComStatusVec, VCT_TRACE_MSG* pTrackStatusVec)
{
	STRVEC* pvStr = &vStr;
	pvStr = Cluster_UniNum(pEsmStatusVec, pComStatusVec, pTrackStatusVec);//调用方位聚类编批函数
	
	STTYPE StType;
	TYPEVEC EsmType;
	TYPEVEC ComType;
	TYPEVEC TrackType;
	STRVEC::iterator itt;

	for (itt = (*pvStr).begin(); itt!= (*pvStr).end(); itt++)//遍历聚类结果
	{
		int nLenEsm = itt->VecEsm.size();
		for (int j = 0;j < nLenEsm;j++)//清空EsmType
		{
			memset(&EsmType, 0, sizeof(TYPEVEC));
		}
		EsmType.clear();

		for (int i = 0;i < nLenEsm; i ++)//同一批号的esm信息如type结构存入EsmType
		{
			StType.lAutonum = itt->VecEsm[i].lAutonum;
			StType.con = itt->VecEsm[i].dConfidence;
			StType.sType = itt->VecEsm[i].sPlatType;
			EsmType.push_back(&StType);			
		}
		
		int nLenCom = itt->VecCom.size();
		for (j = 0;j < nLenCom;j++)//清空ComType
		{
			memset(&ComType, 0, sizeof(TYPEVEC));
		}
		ComType.clear();

		for (i = 0;i < nLenCom; i ++)//同一批号的com信息如type结构存入ComType
		{
			StType.lAutonum = itt->VecCom[i].lAutonum;
			StType.con = itt->VecCom[i].dConfidence;
			StType.sType = itt->VecCom[i].sPlatType;
			ComType.push_back(&StType);			
		}
		
		int nLenTrack = itt->VecTrack.size();
		for (j = 0;j < nLenTrack;j++)//清空TrackType
		{
			memset(&TrackType, 0, sizeof(TYPEVEC));
		}
		TrackType.clear();

		for (i = 0;i < nLenTrack; i ++)//同一批号的Track信息如type结构存入TrackType
		{
			StType.lAutonum = itt->VecTrack[i].lAutonum;
			StType.con = itt->VecTrack[i].dConfidence;
			StType.sType = itt->VecTrack[i].sPlatType;
			TrackType.push_back(&StType);			
		}
		ShowOfHands(&EsmType, &ComType, &TrackType, &IdentifyVec);//调用举手表决函数
	}

	return (&IdentifyVec);
}
