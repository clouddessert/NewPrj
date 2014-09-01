#include "SingleIdentify.h"
#include <vector>
#include <string>
#include <iostream>
#include <math.h>

using namespace std;

#define DTN 8000

typedef struct __STR//��λ�����ͬ��λ���ݽṹ
{
	   // 	float fReachAzimuth;  //���﷽λ
	unsigned long lAutonum;			//�ۺ�����
	VCT_ESM_MSG VecEsm;
	VCT_COMM_MSG VecCom;
	VCT_TRACE_MSG VecTrack;	
}STR;
typedef vector<STR> STRVEC;	//�洢ͬ��λ�ĸ�������Դ��Ϣ
STRVEC vStr;

typedef struct __STTYPE //���ֱ��Ҫ�õ����ݽṹ
{
	unsigned long lAutonum;   //�ۺ�����
//	char *type;    //Ŀ������
	unsigned short sType;  //ƽ̨����
	double  con;   //���Ŷ�	
}STTYPE;
typedef vector<STTYPE*> TYPEVEC;

//IDENTIINFOR IdentStr;
VCT_IDENTIINFOR_MSG IdentifyVec;//����ʶ����

STRVEC* Cluster_UniNum(VCT_ESM_MSG* pEsmStatusVec, VCT_COMM_MSG* pComStatusVec, VCT_TRACE_MSG* pTrackStatusVec)
{
	float fTrackAz(0.0);			// �з�������λ��	
	/*float fTrackEz(0.0);*/		
	float fReachA(0.0);          // �з����﷽λ��
	/*float tmpElevation(0.0);*/
	float fA(0.0);              // �з���λ�ǲ�
	/*float detElevation(0.0);*/
	int TN = DTN;
	int dtn = 0;
	STR Str;//��ʱ�洢ĳһ�ۺ����ŵ�������Ϣ
 	STRVEC* pvStr = &vStr;
//	STRVEC* pvStr = new STRVEC;
	// ���������ĵ�����
	VCT_TRACE_MSG::iterator iteTrack;
	VCT_ESM_MSG::iterator iteEsm;
	VCT_COMM_MSG::iterator iteCom;
	VCT_ESM_MSG::iterator itEsm;
	VCT_COMM_MSG::iterator itCom;
	//������յĵ�����
	VCT_ESM_MSG::iterator iteE;
	VCT_COMM_MSG::iterator iteC;
	VCT_TRACE_MSG::iterator iteT;
	Accuracy Acc;
	Acc.dirAcc = 1.0;
	//�к�����Ϣ
	for (iteTrack = (*pTrackStatusVec).begin(); iteTrack != (*pTrackStatusVec).end(); iteTrack ++)
	{
		/*���Str*/
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


		fTrackAz = (float)iteTrack->fAzimuth;	// �����ṩ�ķ�λ��

		/*��δ��������Ϣ���д���*/
		//��������
		if (iteTrack->cJfFlag == 0)
		{
			iteTrack->lAutonum = TN;
			iteTrack->cJfFlag = '1';
			TN++;
			dtn = iteTrack->lAutonum;
			Str.lAutonum = dtn;//�������ŷ�����ʱ��Str
			Str.VecTrack.push_back(*iteTrack); //�������ĺ�����Ϣ������ʱ��vTrack
		}		
		// ESM����
		for (iteEsm = (*pEsmStatusVec).begin(); iteEsm != (*pEsmStatusVec).end(); iteEsm ++)
		{
			if (iteEsm->cJfFlag == 0)
			{
				fReachA = iteEsm->fReachAzimuth; // ESM�ṩ�ķ�λ��
				fA = fabs(fReachA - fTrackAz);
				
				// ��Ϊһ��
				if ((fA < Acc.dirAcc*2)/* && (detElevation < stEsmAcc.dirAcc*2)*/)
				{
					iteEsm->lAutonum = dtn;
					iteEsm->cJfFlag = '1';
					Str.VecEsm.push_back(*iteEsm);//��������ESM��Ϣ������ʱ��vEsm
				}
			}
		}
		// COM����
		for (iteCom = (*pComStatusVec).begin(); iteCom != (*pComStatusVec).end(); iteCom ++)
		{
			if (iteCom->cJfFlag == 0)
			{
				fReachA = iteCom->fReachAzimuth; // COM�ṩ�ķ�λ��
				fA = fabs(fReachA - fTrackAz);
				
				// ��Ϊһ��
				if ((fA < Acc.dirAcc*2)/* && (detElevation < stComAcc.dirAcc*2)*/)
				{
					iteCom->lAutonum = dtn;
					iteCom->cJfFlag = '1';
					Str.VecCom.push_back(*iteCom);//��������COM��Ϣ������ʱ��vCom
				} 
			}
		}
		(*pvStr).push_back(Str);
	}

	//û�к�����Ϣ����ESM��Ϣ��COM��Ϣ
	for (iteEsm = (*pEsmStatusVec).begin(); iteEsm != (*pEsmStatusVec).end(); iteEsm ++)
	{
		/*���Str*/
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

		/*��δ��������Ϣ���д���*/
		if (iteEsm->cJfFlag == 0)
		{
			iteEsm->lAutonum = TN;
			TN++;
			dtn = iteEsm->lAutonum;
			iteEsm->cJfFlag = '1';
			fReachA = iteEsm->fReachAzimuth;
			Str.lAutonum = dtn;//�������ŷ�����ʱ��Str
			Str.VecEsm.push_back(*iteEsm);
			// ESM����
			for (itEsm = iteEsm; itEsm != (*pEsmStatusVec).end(); itEsm ++)
			{
				if (itEsm->cJfFlag == 0)
				{
					fA = fabs(fReachA - itEsm->fReachAzimuth);
					
					// ��Ϊһ��
					if ((fA < Acc.dirAcc*2)/* && (detElevation < stComAcc.dirAcc*2)*/)
					{
						itEsm->lAutonum = dtn;
						itEsm->cJfFlag = '1';
						Str.lAutonum = dtn;//�������ŷ�����ʱ��Str
						Str.VecEsm.push_back(*itEsm);//��������ESM��Ϣ������ʱ��vEsm
					} 
				}
			}			
			// COM����
		//	Str.VecCom.clear();
			for (iteCom = (*pComStatusVec).begin(); iteCom != (*pComStatusVec).end(); iteCom ++)
			{
				if (iteCom->cJfFlag == 0)
				{
					fA = fabs(fReachA - iteCom->fReachAzimuth);					
					// ��Ϊһ��
					if ((fA < Acc.dirAcc*2)/* && (detElevation < stComAcc.dirAcc*2)*/)
					{
						iteCom->lAutonum = dtn;
						iteCom->cJfFlag = '1';
						/*Str.VecCom.clear();*/
						Str.VecCom.push_back(*iteCom);//��������COM��Ϣ������ʱ��vCom
					} 
				}
			}
			(*pvStr).push_back(Str);
		}		
	}
	
	//ֻ��COM��Ϣ
	for (iteCom = (*pComStatusVec).begin(); iteCom != (*pComStatusVec).end(); iteCom ++)
	{
		/*���Str*/
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

		/*��δ��������Ϣ���д���*/
		if (iteCom->cJfFlag == 0)
		{
			iteCom->lAutonum = TN;
			TN++;
			dtn = iteCom->lAutonum;
			iteCom->cJfFlag = '1';
			fReachA = iteCom->fReachAzimuth;
			Str.lAutonum = dtn;//�������ŷ�����ʱ��Str
			Str.VecCom.push_back(*iteCom);
			// COM����
			for (itCom = iteCom; itCom != (*pComStatusVec).end(); itCom ++)
			{
				if (itCom->cJfFlag == 0)
				{
					fA = fabs(fReachA - itCom->fReachAzimuth);
					/*detElevation = fabs(tmpElevation - fTrackEz);*/
					
					// ��Ϊһ��
					if ((fA < Acc.dirAcc*2)/* && (detElevation < stComAcc.dirAcc*2)*/)
					{
						itCom->lAutonum = dtn;
						itCom->cJfFlag = '1';
						Str.lAutonum = dtn;//�������ŷ�����ʱ��Str
						/*Str.VecCom.clear();*/
						Str.VecCom.push_back(*itCom);//��������COM��Ϣ������ʱ��vCom
					} 
				}
			}
			(*pvStr).push_back(Str);
		}		
	}
 	return(pvStr);

}


//���ֱ�� ����ͬһ�ۺ����ŵ�esm��com��track��Ϣ��ֻ��Ŀ�����ͼ����ۺϿ��Ŷȣ����õ���Ӧ����ۺϿ��Ŷȵ�Ŀ�����ʹ���ʶ����vev��
void ShowOfHands(TYPEVEC* pESMType, TYPEVEC* pCOMMType, TYPEVEC* pTRACKType, VCT_IDENTIINFOR_MSG* pIdentifyVec)
{
	TYPEVEC Type; //��ʱ����
    TYPEVEC Vcst; //�洢��ͬĿ�����ͼ����ۺϿ��Ŷ�
	
	vector<int>  typenum;     //Ŀ������ʶ����
	vector<double>  typecon;  //�ۺϿ��Ŷ�
	
	/*��������Ϣ����type��*/
	Type.insert(Type.end(), (*pESMType).begin(), (*pESMType).end());
	Type.insert(Type.end(), (*pCOMMType).begin(), (*pCOMMType).end());
	Type.insert(Type.end(), (*pTRACKType).begin(), (*pTRACKType).end());
	/*��Type�е�һ����Ϣ����vcst*/
	Vcst.insert(Vcst.begin(), Type.begin(), Type.begin()+1);
	/*ʶ����*/
	typenum.push_back(1);
	/*������*/
	TYPEVEC::iterator it = Type.begin();
	/*�ۺϿ��Ŷ�*/
	typecon.push_back(1 - (*it)->con);
	/*���ֱ��*/
	for (it ++;it != Type.end();it ++)
	{
		int nflag = 0;
		int len = Vcst.size();
        for (int i = 0;i < len;i ++)//����Vcst
		{
			if (Vcst[i]->sType == (*it)->sType)
//			if (strcmp(Vcst[i]->type,(*it)->type) == 0)//Ŀ������һ��
			{
				typenum[i] = typenum[i] + 1;//ʶ����+1
				typecon[i] = typecon[i] * (1 - (*it)->con);//������Ŷ�
				//break;
			}
			else
			{
				nflag ++;
			}
		}		
		if (nflag == len)//�����µ�Ŀ������
		{
			STTYPE *tmp = new STTYPE;
			tmp->sType = (*it)->sType;
			tmp->con = (*it)->con;
			Vcst.insert(Vcst.end(), tmp);//���µ�Ŀ��������Ϣ����Vcst
            typenum.push_back(1);//�µ�Ŀ������ʶ����Ϊ1
			typecon.push_back(1 - (*it)->con);//�µ�Ŀ�����Ϳ��Ŷ�
		}
		
	}
	int nLen = Vcst.size();
	for (int k = 0;k < nLen;k ++)//�ۺϿ��Ŷ�
	{
		typecon[k] = 1 - typecon[k];
	}
	/*��������ۺϿ��Ŷ��������ʶ��Ŀ��������������ۺϿ��Ŷ�*/
	double c = typecon[0];//����ۺϿ��Ŷ�c
	int max = 0;//����ʶ��Ŀ������Vcst[max]->type
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
// 	printf("�ۺ�����   Ŀ������     �ۺϿ��Ŷ�\n");
// 	printf("%d\t   %s\t\t%f\n", Vcst[max]->lAutonum, &p, c);
// 	
	/*��ʶ��������Identify*/
 	IDENTIINFOR IdentStr;
	IdentStr.lAutonum = Vcst[max]->lAutonum;//�ۺ�����
	IdentStr.sPlatType = (*Vcst[max]).sType;//Ŀ������
	IdentStr.dConfidence = c;//�ۺϿ��Ŷ�

	(*pIdentifyVec).push_back(IdentStr);
}

VCT_IDENTIINFOR_MSG* SingleIdentify(VCT_ESM_MSG* pEsmStatusVec, VCT_COMM_MSG* pComStatusVec, VCT_TRACE_MSG* pTrackStatusVec)
{
	STRVEC* pvStr = &vStr;
	pvStr = Cluster_UniNum(pEsmStatusVec, pComStatusVec, pTrackStatusVec);//���÷�λ�����������
	
	STTYPE StType;
	TYPEVEC EsmType;
	TYPEVEC ComType;
	TYPEVEC TrackType;
	STRVEC::iterator itt;

	for (itt = (*pvStr).begin(); itt!= (*pvStr).end(); itt++)//����������
	{
		int nLenEsm = itt->VecEsm.size();
		for (int j = 0;j < nLenEsm;j++)//���EsmType
		{
			memset(&EsmType, 0, sizeof(TYPEVEC));
		}
		EsmType.clear();

		for (int i = 0;i < nLenEsm; i ++)//ͬһ���ŵ�esm��Ϣ��type�ṹ����EsmType
		{
			StType.lAutonum = itt->VecEsm[i].lAutonum;
			StType.con = itt->VecEsm[i].dConfidence;
			StType.sType = itt->VecEsm[i].sPlatType;
			EsmType.push_back(&StType);			
		}
		
		int nLenCom = itt->VecCom.size();
		for (j = 0;j < nLenCom;j++)//���ComType
		{
			memset(&ComType, 0, sizeof(TYPEVEC));
		}
		ComType.clear();

		for (i = 0;i < nLenCom; i ++)//ͬһ���ŵ�com��Ϣ��type�ṹ����ComType
		{
			StType.lAutonum = itt->VecCom[i].lAutonum;
			StType.con = itt->VecCom[i].dConfidence;
			StType.sType = itt->VecCom[i].sPlatType;
			ComType.push_back(&StType);			
		}
		
		int nLenTrack = itt->VecTrack.size();
		for (j = 0;j < nLenTrack;j++)//���TrackType
		{
			memset(&TrackType, 0, sizeof(TYPEVEC));
		}
		TrackType.clear();

		for (i = 0;i < nLenTrack; i ++)//ͬһ���ŵ�Track��Ϣ��type�ṹ����TrackType
		{
			StType.lAutonum = itt->VecTrack[i].lAutonum;
			StType.con = itt->VecTrack[i].dConfidence;
			StType.sType = itt->VecTrack[i].sPlatType;
			TrackType.push_back(&StType);			
		}
		ShowOfHands(&EsmType, &ComType, &TrackType, &IdentifyVec);//���þ��ֱ������
	}

	return (&IdentifyVec);
}
