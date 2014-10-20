#include "FusionCooperativeMsg.h"
#include "stdafx.h" 
#include <iostream>
#include <math.h>
#include <vector>
#include <string>

using namespace std;
//ͬ��ʶ���ں�
//�Ժ������ں� ��һ��������Ϣ��Ӧ��ֻ��һ��������Ϣ��������Ϣ�����ֻ��һ��������Ϣ������������Ϣ�����ںϣ�����һ��������ϢЭͬ����

//��ESM���ںϣ�  ͳ��ESM��������
  
//��COM���ںϣ�ͳ��COM��������

//������Ϣ��һ���ṹ�壬������Ϣͬ��Ҳ�ǽṹ��
void Mf_SPA(double s, double t,double& corr); //s,tΪ��ͬ���͵���Ϣ�����м��Է����������ص����ϵ����������VctCorr��

void FusionCooperativeMsg(VCT_Request_Cooperative_Msg& vctReqMsg, VCT_BACK_Cooperative_Msg& vctBackMsg, /* �ۺ�ʶ����*/VCT_MIDENTIINFOR_MSG& vctMidentiinforMsg, VCT_Cooperative_FUSIDENTIINFOR& vctCoFusMsg);


void FusionCooperativeMsg(VCT_Request_Cooperative_Msg& vctReqMsg, VCT_BACK_Cooperative_Msg& vctBackMsg, /* �ۺ�ʶ����*/VCT_MIDENTIINFOR_MSG& vctMidentiinforMsg, VCT_Cooperative_FUSIDENTIINFOR& vctCoFusMsg)
{
	int nNumTrackRd = 0;  //Ŀ�꺽���ľ��ࣨ�ף�
	int nNumTrackAz = 0;  //Ŀ�꺽���ķ�λ�����ȣ�
	int nNumTrackEz = 0;  //Ŀ�꺽�������ǣ����ȣ�
	int nNumTrackVx = 0;  //Ŀ�꺽����X���ϵ��ٶȣ���/�룩
	int nNumTrackVy = 0;  //Ŀ�꺽����Y���ϵ��ٶȣ���/�룩
	int nNumTrackVz = 0;  //Ŀ�꺽����Z���ϵ��ٶȣ���/�룩

	int nNumESMDOAz = 1;  //ESM�źŵĵ��﷽λ�����ȣ�
	int nNumESMFre = 1;   //ESM�źŵ�Ƶ�ʣ�GHz��
	int nNumESMPA = 1;    //ESM�źŵķ���
	int nNumESMPzw = 1;   //ESM�źŵ������ȣ�us��
	int nNumESMPRI = 1;   //ESM�źŵ��ظ������ms��;�ظ�Ƶ��PRF=PRI�ĵ���
	int nNumESMSCan = 1;  //ESM�źŵ�����״�����ɨ�����ڣ�s��

	int nNumCOMDOAz = 1;  //COM�źŵĵ��﷽λ�����ȣ�   
	int nNumCOMFre = 1;   //COM�źŵ�����Ƶ�ʣ�MHz��
	int nNumCOMPA = 1; 	  //COM�źŵķ���
	int nNumCOMBand = 1;  //COM�źŵ��źŴ���MHz��
	int nNumCOMJPN = 1;   //COM�źŵ���������

	double dcorrEsmReachAzimuth = 0.0; //ESM�źŵĵ��﷽λ�����ȣ�
	double dcorrZaiPin= 0.0; //ESM�źŵ�Ƶ�ʣ�GHz��
    double dcorrEsmPulseExtent= 0.0; //ESM�źŵķ���
    double dcorrMaiKuan= 0.0; //ESM�źŵ������ȣ�us��
    double dcorrChongPin= 0.0; //ESM�źŵ��ظ������ms��;�ظ�Ƶ��PRF=PRI�ĵ���
    double dcorrTianXianScan= 0.0; //ESM�źŵ�����״�����ɨ�����ڣ�s��
	double dAverCorr = 0.0;
	double dcorrComReachAzimuth = 0.0;
	double dcorrComPulseExtent= 0.0;
	double dcorrFre = 0.0; 
	double dcorrBand = 0.0;
	double dcorrJPN = 0.0;

	VCT_BACK_Cooperative_Msg vctAllBackMsg;//��Ž�����ͬ�����ķ�����Ϣ�ϲ���һ���ķ�����Ϣ
	VCT_Request_Cooperative_Msg::iterator iteReqMsg;
	VCT_BACK_Cooperative_Msg::iterator iteBackMsg;
//	VCT_BACK_Cooperative_Msg::iterator iteBackMsg1;
	VCT_BACK_Cooperative_Msg::iterator iteBackMsg2;
//	VCT_BACK_Cooperative_Msg::iterator iteBackMsg3;
		VCT_BACK_Cooperative_Msg::iterator iteBackMsg4;
	VCT_Cooperative_FUSIDENTIINFOR::iterator iteCoFusionMsg;
	VCT_MIDENTIINFOR_MSG::reverse_iterator  r_iteMIdenti;
	VCT_ESM_MSG::iterator iteFusEsm;      //�洢�ںϺ���״������Ϣ
	VCT_COMM_MSG::iterator iteFusCom;
	VCT_ESM_MSG::iterator iteBaEsm;
//	VCT_ESM_MSG::iterator iteBaEsm1;
	VCT_COMM_MSG::iterator iteBaCom;
//	VCT_COMM_MSG::iterator iteBaCom1;
	VCT_ESM_MSG::iterator iteReEsm;      
	VCT_COMM_MSG::iterator iteReCom;

	typedef vector<double> VCT_CORR;
	VCT_CORR VctCorr;      // ��Ź���ϵ��������
	VCT_CORR::iterator iteCorr;

	Cooperative_FUSIDENTIINFOR stCoFusiInfor;
	BACK_Cooperative_Msg stBaMsg;
	ESMSTATUS_MARK stFusEsm;
	COMSTATUS_MARK stFusCom;
//��մ���ں���Ϣ������   
	for ( iteCoFusionMsg = vctCoFusMsg.begin(); iteCoFusionMsg != vctCoFusMsg.end(); iteCoFusionMsg++)
	{
		iteCoFusionMsg->lAutonum = NULL;
		iteCoFusionMsg->dConfidence = NULL;
		memset(iteCoFusionMsg->sPlatType,0,32); //����ַ�������
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

    //������Ϣ���ں�
	//Ŀ�꺽���ľ��ࣨ�ף�
	//Ŀ�꺽���ķ�λ�����ȣ�
	//Ŀ�꺽�������ǣ����ȣ�
	//Ŀ�꺽����X���ϵ��ٶȣ���/�룩
	//Ŀ�꺽����Y���ϵ��ٶȣ���/�룩
    //Ŀ�꺽����Z���ϵ��ٶȣ���/�룩
	for ( iteReqMsg = vctReqMsg.begin(); iteReqMsg != vctReqMsg.end(); iteReqMsg++)
	{
		int TFlag = 0;
		//����ں���Ϣ�ĺ�����Ϣ
		memset(&stCoFusiInfor.stFusTrack, 0, sizeof(TRACKSTATUS_MARK));
		//������Ϣ�к�����Ϊ������к�������Ϣ��δ����ĺ�����Ϣ
		if ( iteReqMsg->lAutonum > 7999 ||(iteReqMsg->lAutonum >4999 && iteReqMsg->lAutonum <6000) )
		{
		   //��������Ϣ�����ں���Ϣ��������
			stCoFusiInfor.stFusTrack.lAutonum = iteReqMsg->stTrace.lAutonum; //���ۺ����Ÿ��ں���Ϣ
			stCoFusiInfor.stFusTrack.dAzimuth = iteReqMsg->stTrace.dAzimuth;
			stCoFusiInfor.stFusTrack.dRange = iteReqMsg->stTrace.dRange;
			stCoFusiInfor.stFusTrack.dElevationAngle = iteReqMsg->stTrace.dElevationAngle;
			stCoFusiInfor.stFusTrack.dTSpeedX = iteReqMsg->stTrace.dTSpeedX;
			stCoFusiInfor.stFusTrack.dTSpeedY = iteReqMsg->stTrace.dTSpeedY;
			stCoFusiInfor.stFusTrack.dTSpeedZ = iteReqMsg->stTrace.dTSpeedZ;
			stCoFusiInfor.stFusTrack.dCourse = iteReqMsg->stTrace.dCourse;  // ���Ժ���
			stCoFusiInfor.stFusTrack.dTargetAZSpeed = iteReqMsg->stTrace.dTargetAZSpeed; // Ŀ�귽λ���ٶ�
			stCoFusiInfor.stFusTrack.dTargetEAngleSpeed = iteReqMsg->stTrace.dTargetEAngleSpeed;//Ŀ�����ǽ��ٶ�
			stCoFusiInfor.stFusTrack.lTargetNumber = iteReqMsg->stTrace.lTargetNumber;
			strcpy(stCoFusiInfor.stFusTrack.cEquipmentType , iteReqMsg->stTrace.cEquipmentType);
			strcpy(stCoFusiInfor.stFusTrack.cEquipmentNumber , iteReqMsg->stTrace.cEquipmentNumber);
			strcpy(stCoFusiInfor.stFusTrack.cDWAttribute , iteReqMsg->stTrace.cDWAttribute);
			strcpy(stCoFusiInfor.stFusTrack.cPlatNumber , iteReqMsg->stTrace.cPlatNumber);
			strcpy(stCoFusiInfor.stFusTrack.cPlatName , iteReqMsg->stTrace.cPlatName);
			for ( r_iteMIdenti = vctMidentiinforMsg.rbegin(); r_iteMIdenti != vctMidentiinforMsg.rend(); ++r_iteMIdenti )
			{
				// ������� 
				if ( r_iteMIdenti->lAutonum == stCoFusiInfor.stFusTrack.lAutonum )
				{
					strcpy( stCoFusiInfor.stFusTrack.sPlatType, r_iteMIdenti->sPlatType ); //�ۺ�ƽ̨����
					stCoFusiInfor.stFusTrack.dConfidence = r_iteMIdenti->dConfidence;  //�ۺϿ��ж�
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
		//������Ϣ�޺�����Ϊ������޺�������Ϣ
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
			if ( iteReqMsg->lAutonum == iteBackMsg->lAutonum ) //���ҳ���Ӧ��ͬһ���ŵķ�����Ϣ
			{ 
				//������Ϣ�к�����Ϣ ������к����ں�
				if (iteBackMsg->BackTrackN != 0)
				{
					stCoFusiInfor.stFusTrack.lFusFlag = 1; //�ںϲ��ұ��,�ܹ�����
					//�Ժ������ںϣ�����ر���ȡƽ��ֵ
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
			}//if ���ҳ���ͬ���ۺ����Ž�����Ϣ�ں�
		} //for ����������Ϣ
		//��Ҫ�ںϵ���Ϣ��ͳ��ȫ����ƽ��
		if ( nNumTrackAz != 0/*sizeof(stCoFusiInfor.stFusTrack) */)//������Ϣ�к�����Ϣ
		{
			//��ƽ��
			stCoFusiInfor.stFusTrack.dAzimuth /= nNumTrackAz;
			stCoFusiInfor.stFusTrack.dRange /= nNumTrackRd;
			stCoFusiInfor.stFusTrack.dElevationAngle /= nNumTrackEz;
			stCoFusiInfor.stFusTrack.dTSpeedX /= nNumTrackVx;
			stCoFusiInfor.stFusTrack.dTSpeedY /= nNumTrackVy;
			stCoFusiInfor.stFusTrack.dTSpeedZ /= nNumTrackVz;
		}
		//����������ֵ, ���ۺ����Ž����ж�
		for( iteBackMsg2 = vctBackMsg.begin(); iteBackMsg2 != vctBackMsg.end(); iteBackMsg2++ )
		{
			if ( iteReqMsg->lAutonum <8000 ) //������Ϣ���޺�����Ϣ
			{
				if (iteBackMsg2->BackTrackN != 0) // ������Ϣ���к���
				{
					stCoFusiInfor.stFusTrack.lAutonum +=2000;  //��������Ϣ���к���,���ۺ���������2000,��Ϊ9000
					TFlag = 1;  //���Ϊ1,����ı��ۺ�����
					break;
				}
			}
		}

//ESM��Ϣ���ں�

		 TFlag = 0;
		if( iteReqMsg->vctEsm.size() !=0 )
		{//����������Ϣ�е�ESM��ÿһ��
			for( iteReEsm = iteReqMsg->vctEsm.begin(); iteReEsm != iteReqMsg->vctEsm.end(); iteReEsm++)
			{
				 nNumESMDOAz = 1;//ESM�źŵĵ��﷽λ�����ȣ�
				 nNumESMFre = 1;//ESM�źŵ�Ƶ�ʣ�GHz��
				 nNumESMPA = 1;//ESM�źŵķ���
				 nNumESMPzw = 1;//ESM�źŵ������ȣ�us��
				 nNumESMPRI = 1;//ESM�źŵ��ظ������ms��;�ظ�Ƶ��PRF=PRI�ĵ���
				 nNumESMSCan = 1;//ESM�źŵ�����״�����ɨ�����ڣ�s��
				//��������Ϣ�еĸ����������ȸ����ں����ݽṹ
				stFusEsm.dReachAzimuth = iteReEsm->dReachAzimuth; 
				stFusEsm.dZaiPin = iteReEsm->dZaiPin;
				stFusEsm.dPulseExtent = iteReEsm->dPulseExtent;
				stFusEsm.dMaiKuan = iteReEsm->dMaiKuan;
				stFusEsm.dChongPin = iteReEsm->dChongPin;
				stFusEsm.dTianXianScan = iteReEsm->dTianXianScan;
				//����������Ϣ�е�ÿ���ṹ��
				for( iteBackMsg = vctBackMsg.begin(); iteBackMsg != vctBackMsg.end(); iteBackMsg++ )
				{   //�ж�������Ϣ�ͷ�����Ϣ�е��ۺ������Ƿ���ͬ,����ͬ�ٽ��д���
					if (iteReqMsg->lAutonum == iteBackMsg->lAutonum)
					{
						//(�ݲ����ڸ������(1),������)
						//(1)��������ϢΪ�޺���,������Ϣ���к���,��Ҫ���ںϺ���ۺ����Ÿ�Ϊ���ڵ���9000 ,���ܰ���������Ϣ��7000������
						//����������Ϣ�е�ÿ���ṹ���ESM������ÿ��ESM����Ϣ
						for( iteBaEsm = iteBackMsg->vctEsm.begin(); iteBaEsm != iteBackMsg->vctEsm.end(); iteBaEsm++)
						{
							//���Է���,�������
							//ESM�źŵĵ��﷽λ�����ȣ�
							//ESM�źŵ�Ƶ�ʣ�GHz��
							//ESM�źŵķ���
							//ESM�źŵ������ȣ�us��
							//ESM�źŵ��ظ������ms��;�ظ�Ƶ��PRF=PRI�ĵ���
							//ESM�źŵ�����״�����ɨ�����ڣ�s��
							double SumCorr = 0.0;
							Mf_SPA(iteBaEsm->dReachAzimuth,iteReEsm->dReachAzimuth,dcorrEsmReachAzimuth); //ESM�źŵĵ��﷽λ�����ȣ�
							VctCorr.push_back(dcorrEsmReachAzimuth);
							Mf_SPA(iteBaEsm->dZaiPin,iteReEsm->dZaiPin,dcorrZaiPin); //ESM�źŵ�Ƶ�ʣ�GHz��
							VctCorr.push_back(dcorrZaiPin);
							Mf_SPA(iteBaEsm->dPulseExtent,iteReEsm->dPulseExtent,dcorrEsmPulseExtent); //ESM�źŵķ���
							VctCorr.push_back(dcorrEsmPulseExtent);
							Mf_SPA(iteBaEsm->dMaiKuan,iteReEsm->dMaiKuan,dcorrMaiKuan); //ESM�źŵ������ȣ�us��
							VctCorr.push_back(dcorrMaiKuan);
							Mf_SPA(iteBaEsm->dChongPin,iteReEsm->dChongPin,dcorrChongPin); //ESM�źŵ��ظ������ms��;�ظ�Ƶ��PRF=PRI�ĵ���
							VctCorr.push_back(dcorrChongPin);
							Mf_SPA(iteBaEsm->dTianXianScan,iteReEsm->dTianXianScan,dcorrTianXianScan); //ESM�źŵ�����״�����ɨ�����ڣ�s��
							VctCorr.push_back(dcorrTianXianScan);
							//�����ϵ����������ȡ���������ݵ�ƽ��ֵ
							for (iteCorr = VctCorr.begin(); iteCorr != VctCorr.end(); iteCorr++)
							{
								SumCorr = SumCorr + *iteCorr;  
							}
							dAverCorr = SumCorr/VctCorr.size();  //ȡ���ϵ����ƽ��ֵ
							//�´δ�ż���ϵ��ǰ�����VctCorr����
							VctCorr.clear();
							//����ֵ�Ƚϣ��趨��ֵ�����ϵ������ĳ��ֵʱ����ΪESM�ǿ��Թ����ģ�
							if (dAverCorr > 0.8) 
							{
								iteBaEsm->lFusFlag = 1; //�ںϲ��ұ��,�ܹ�����
								stFusEsm.lFusFlag = 1;
								//��������Ϣ�����������ۼ�,����¼�ۼӸ���
								stFusEsm.dReachAzimuth += iteBaEsm->dReachAzimuth;
								nNumESMDOAz++;
								stFusEsm.dZaiPin += iteBaEsm->dZaiPin;
								nNumESMFre ++;//ESM�źŵ�Ƶ�ʣ�GHz��
								stFusEsm.dPulseExtent += iteBaEsm->dPulseExtent;
								nNumESMPA ++;//ESM�źŵķ���
								stFusEsm.dMaiKuan += iteBaEsm->dMaiKuan;
								nNumESMPzw ++;//ESM�źŵ������ȣ�us��
								stFusEsm.dChongPin += iteBaEsm->dChongPin;
								nNumESMPRI ++;//ESM�źŵ��ظ������ms��;�ظ�Ƶ��PRF=PRI�ĵ���
								stFusEsm.dTianXianScan += iteBaEsm->dTianXianScan;
								nNumESMSCan ++;
							}
						}//for( iteBaEsm = iteBackMsg->vctEsm.begin()	
					}// if �ж��ۺ������Ƿ���ͬ
				}//	for( iteBackMsg = vctBackMsg.begin()
				//ÿ��������Ϣ��Esm����֮��,������������ȡƽ��ֵ��,�����ں���Ϣ������
                stFusEsm.dReachAzimuth  =  stFusEsm.dReachAzimuth/nNumESMDOAz; 
				stFusEsm.dZaiPin = stFusEsm.dZaiPin/nNumESMFre;
				stFusEsm.dPulseExtent = stFusEsm.dPulseExtent/nNumESMPA;
				stFusEsm.dMaiKuan = stFusEsm.dMaiKuan/nNumESMPzw;
				stFusEsm.dChongPin = stFusEsm.dChongPin/nNumESMPRI;
				stFusEsm.dTianXianScan = stFusEsm.dTianXianScan/nNumESMSCan;
				//��������Ϣ������������ֵ���ں���Ϣ,��:����ʶ���ƽ̨���ͺ��ۺϿ��Ŷ�
				//�������,���������һ�����ݿ�ʼ����, �ۺ�ʶ�����еĵ�ǰ�ĸ�����ʶ�����ƽ̨���ͺ��ۺϿ��Ŷ�
				stFusEsm.lAutonum = iteReqMsg->lAutonum;  //�ۺ�����
                for ( r_iteMIdenti = vctMidentiinforMsg.rbegin(); r_iteMIdenti != vctMidentiinforMsg.rend(); ++r_iteMIdenti )
                {
					// ������� 
					if ( r_iteMIdenti->lAutonum == stFusEsm.lAutonum )
					{
						strcpy( stFusEsm.sPlatType, r_iteMIdenti->sPlatType ); //�ۺ�ƽ̨����
						stFusEsm.dConfidence = r_iteMIdenti->dConfidence;  //�ۺϿ��ж�
						break;
					}
                }
				for( iteBackMsg2 = vctBackMsg.begin(); iteBackMsg2 != vctBackMsg.end(); iteBackMsg2++ )
				{
					if ( iteReqMsg->lAutonum <8000 ) //������Ϣ���޺�����Ϣ
					{
						if (iteBackMsg2->BackTrackN != 0)
						{
							stFusEsm.lAutonum +=2000;  //��������Ϣ���к���,���ۺ���������2000,��Ϊ9000
							 TFlag = 1;  //���Ϊ1,����ı��ۺ�����
							break;
						}
					}
				}

				stFusEsm.lTargetNumber = iteReEsm->lTargetNumber; //Ŀ������
				stFusEsm.dElevationAngle = iteReEsm->dElevationAngle;//����
				stFusEsm.dMaiChongFeature = iteReEsm->dMaiChongFeature;//��������
				strcpy(stFusEsm.cEquipmentNumber , iteReEsm->cEquipmentNumber);  //�豸���
				strcpy(stFusEsm.cEquipmentType,iteReEsm->cEquipmentType); //�豸����
				strcpy(stFusEsm.cDWAttribute , iteReEsm->cDWAttribute);   //��������
				strcpy(stFusEsm.cCountry , iteReEsm->cCountry);           //����/����
                strcpy(stFusEsm.cPlatName , iteReEsm->cPlatName); //ƽ̨����
				strcpy(stFusEsm.cPlatNumber, iteReEsm->cPlatNumber);//ƽ̨���
				strcpy(stFusEsm.cRadarName, iteReEsm->cRadarName);//�״�����
				strcpy(stFusEsm.cRadarPurpose, iteReEsm->cRadarPurpose);//�״���;
                stCoFusiInfor.vctFusEsm.push_back(stFusEsm);
			}//for( iteReEsm = iteReqMsg->vctEsm.begin()
		}//if( iteReqMsg->vctEsm.size() !=0 )
		//������Ϣ�е�ÿ����Ϣ��������ɺ������������Ϣ����ESM��Ϣ,��������Ϣ�л�����Ϣ���ںϱ�ǲ�Ϊ1,˵��δ���ں�,�򲹳�ԭ������Ϣ
// 		for( iteBackMsg1 = vctBackMsg.begin(); iteBackMsg1 != vctBackMsg.end(); iteBackMsg1++ )
// 		{ //����������Ϣ�е�ÿ���ṹ���ESM������ÿ��ESM����Ϣ
// 			for( iteBaEsm1 = iteBackMsg->vctEsm.begin(); iteBaEsm1 != iteBackMsg->vctEsm.end(); iteBaEsm1++)
// 			{
//  				if ( iteBaEsm1->lFusFlag != 0 )
//  				{
// 					if( TFlag == 1 )  //�����ۺ��������2000
// 					{
// 						iteBaEsm1->lAutonum += 2000;
// 					}
// 					stCoFusiInfor.vctFusEsm.push_back(*iteBaEsm1);
// 				}//if iteBaEsm1->lFusFlag != 0
// 			}//for
// 		}//for

//COM��Ϣ���ں�

		    TFlag = 0;
			if( iteReqMsg->vctComm.size() !=0 )
			{//����������Ϣ�е�ESM��ÿһ��
				for( iteReCom = iteReqMsg->vctComm.begin(); iteReCom != iteReqMsg->vctComm.end(); iteReCom++)
				{
					int nNumCOMDOAz = 1; //COM�źŵĵ��﷽λ�����ȣ�   
					int nNumCOMFre = 1;  //COM�źŵ�����Ƶ�ʣ�MHz��
					int nNumCOMPA = 1; 	//COM�źŵķ���
					int nNumCOMBand = 1; //COM�źŵ��źŴ���MHz��
					int nNumCOMJPN = 1; //COM�źŵ���������
					//��������Ϣ�еĸ����������ȸ����ں����ݽṹ
					stFusCom.dReachAzimuth = iteReCom->dReachAzimuth; 
					stFusCom.dComFre = iteReCom->dComFre;
					stFusCom.dPulseExtent= iteReCom->dPulseExtent;
					stFusCom.dComBand = iteReCom->dComBand;
					stFusCom.dComJPN = iteReCom->dComJPN;
					//����������Ϣ�е�ÿ���ṹ��
					for( iteBackMsg = vctBackMsg.begin(); iteBackMsg != vctBackMsg.end(); iteBackMsg++ )
					{   //�ж�������Ϣ�ͷ�����Ϣ�е��ۺ������Ƿ���ͬ,����ͬ�ٽ��д���
						if (iteReqMsg->lAutonum == iteBackMsg->lAutonum)
						{
							//(�ݲ����ڸ������(1),������)
							//(1)��������ϢΪ�޺���,������Ϣ���к���,��Ҫ���ںϺ���ۺ����Ÿ�Ϊ���ڵ���9000 ,���ܰ���������Ϣ��7000������
							//����������Ϣ�е�ÿ���ṹ���ESM������ÿ��ESM����Ϣ
							for( iteBaCom = iteBackMsg->vctComm.begin(); iteBaCom != iteBackMsg->vctComm.end(); iteBaCom++)
							{
								//���Է���,�������
								//COM�źŵĵ��﷽λ�����ȣ�
								//COM�źŵ�����Ƶ�ʣ�MHz��
								//COM�źŵķ���
								//COM�źŵ��źŴ���MHz��
								//COM�źŵ���������
								double SumCorr = 0.0;
								Mf_SPA(iteBaCom->dReachAzimuth,iteReCom->dReachAzimuth,dcorrComReachAzimuth); //COM�źŵĵ��﷽λ�����ȣ�
								VctCorr.push_back(dcorrComReachAzimuth);
								Mf_SPA(iteBaCom->dComFre,iteReCom->dComFre,dcorrFre); //COM�źŵ�����Ƶ�ʣ�MHz��
								VctCorr.push_back(dcorrFre);
								Mf_SPA(iteBaCom->dPulseExtent,iteReCom->dPulseExtent,dcorrComPulseExtent); //COM�źŵķ���
								VctCorr.push_back(dcorrComPulseExtent);
								Mf_SPA(iteBaCom->dComBand,iteReCom->dComBand,dcorrBand); //COM�źŵ��źŴ���MHz��
								VctCorr.push_back(dcorrBand);
								Mf_SPA(iteBaCom->dComJPN,iteReCom->dComJPN,dcorrJPN); //COM�źŵ���������
								VctCorr.push_back(dcorrJPN);
								//�����ϵ����������ȡ���������ݵ�ƽ��ֵ
								for (iteCorr = VctCorr.begin(); iteCorr != VctCorr.end(); iteCorr++)
								{
									SumCorr = SumCorr + *iteCorr;  
								}
								dAverCorr = SumCorr/VctCorr.size();  //ȡ���ϵ����ƽ��ֵ
								//�´δ�ż���ϵ��ǰ�����VctCorr����
								VctCorr.clear();
								//����ֵ�Ƚϣ��趨��ֵ�����ϵ������ĳ��ֵʱ����ΪCOM�ǿ��Թ����ģ�
								if (dAverCorr > 0.8) 
								{
									iteBaEsm->lFusFlag = 1; //�ںϲ��ұ��,�ܹ�����
									//��������Ϣ�����������ۼ�,����¼�ۼӸ���
									stFusCom.dReachAzimuth += iteBaCom->dReachAzimuth;
									nNumCOMDOAz++;
									stFusCom.dComFre += iteBaCom->dComFre;
									nNumCOMFre ++;//cOM�źŵ�Ƶ�ʣ�GHz��
									stFusCom.dPulseExtent += iteBaCom->dPulseExtent;
									nNumCOMPA ++;//com�źŵķ���
									stFusCom.dComBand += iteBaCom->dComBand;
									nNumCOMBand ++;//COM�źŵ��źŴ���MHz��
									stFusCom.dComJPN += iteBaCom->dComJPN;
									nNumCOMJPN ++;//COM�źŵ���������
								}
							}//for( iteBaEsm = iteBackMsg->vctEsm.begin()	
						}// if �ж��ۺ������Ƿ���ͬ
					}//	for( iteBackMsg = vctBackMsg.begin()
					//ÿ��������Ϣ��Esm����֮��,������������ȡƽ��ֵ��,�����ں���Ϣ������
					stFusCom.dReachAzimuth  =  stFusEsm.dReachAzimuth/nNumCOMDOAz; 
					stFusCom.dComFre = stFusCom.dComFre/nNumCOMFre;
					stFusCom.dPulseExtent = stFusCom.dPulseExtent/nNumCOMPA;
					stFusCom.dComBand = stFusCom.dComBand/nNumCOMBand;
					stFusCom.dComJPN = stFusCom.dComJPN /nNumCOMJPN;
					//��������Ϣ������������ֵ���ں���Ϣ,��:����ʶ���ƽ̨���ͺ��ۺϿ��Ŷ�
					//�������,���������һ�����ݿ�ʼ����, �ۺ�ʶ�����еĵ�ǰ�ĸ�����ʶ�����ƽ̨���ͺ��ۺϿ��Ŷ�
					stFusCom.lAutonum = iteReqMsg->lAutonum;  //�ۺ�����
					for ( r_iteMIdenti = vctMidentiinforMsg.rbegin(); r_iteMIdenti != vctMidentiinforMsg.rend(); ++r_iteMIdenti )
					{
						// ������� 
						if ( r_iteMIdenti->lAutonum == stFusCom.lAutonum )
						{
							strcpy( stFusCom.sPlatType, r_iteMIdenti->sPlatType ); //�ۺ�ƽ̨����
							stFusCom.dConfidence = r_iteMIdenti->dConfidence;  //�ۺϿ��ж�
							break;
						}
					}
					for( iteBackMsg4 = vctBackMsg.begin(); iteBackMsg4 != vctBackMsg.end(); iteBackMsg4++ )
					{
						if ( iteReqMsg->lAutonum <8000 ) //������Ϣ���޺�����Ϣ
						{
							if (iteBackMsg4->BackTrackN != 0)
							{
								stFusCom.lAutonum +=2000;  //��������Ϣ���к���,���ۺ���������2000,��Ϊ9000
								TFlag = 1;  //���Ϊ1,����ı��ۺ�����
								break;
							}
						}
					}

					stFusCom.lTargetNumber = iteReCom->lTargetNumber; //Ŀ������
					strcpy(stFusCom.cModulationStyle ,iteReCom->cModulationStyle); //������ʽ
					strcpy(stFusCom.cSignalType , iteReCom->cSignalType);  //�ź�����
					strcpy(stFusCom.cEquipmentNumber , iteReCom->cEquipmentNumber);  //�豸���
					strcpy(stFusCom.cEquipmentType,iteReCom->cEquipmentType); //�豸����
					strcpy(stFusCom.cDWAttribute , iteReCom->cDWAttribute);   //��������
					strcpy(stFusCom.cCountry , iteReCom->cCountry);           //����/����
					strcpy(stFusCom.cPlatName , iteReCom->cPlatName); //ƽ̨����
					strcpy(stFusCom.cPlatNumber, iteReCom->cPlatNumber);//ƽ̨���
					stCoFusiInfor.vctFusCom.push_back(stFusCom);
			}//for( iteReEsm = iteReqMsg->vctEsm.begin()
		}//if( iteReqMsg->vctEsm.size() !=0 )
		//������Ϣ�е�ÿ����Ϣ��������ɺ������������Ϣ����ESM��Ϣ,��������Ϣ�л�����Ϣ���ںϱ�ǲ�Ϊ1,˵��δ���ں�,�򲹳�ԭ������Ϣ
// 		for( iteBackMsg3 = vctBackMsg.begin(); iteBackMsg3 != vctBackMsg.end(); iteBackMsg3++ )
// 		{ //����������Ϣ�е�ÿ���ṹ���ESM������ÿ��COM����Ϣ
// 			if(iteBackMsg->vctComm.size() != 0 )
//  			{
// 				for( iteBaCom1 = iteBackMsg->vctComm.begin(); iteBaCom1 != iteBackMsg->vctComm.end(); iteBaCom1++)
// 				{
//  					if ( iteBaCom1->lFusFlag != 0 ) 					
// 					{
// 						if( TFlag == 1 )  //�����ۺ��������2000
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
	}//for ÿһ��������Ϣ
}




// 	for ( iteReqMsg = vctReqMsg.begin(); iteReqMsg != vctReqMsg.end(); iteReqMsg++)
// 	{
// 		int TFlag = 0;
// 		if( iteReqMsg->vctEsm.size() !=0 )
// 		{//����������Ϣ�е�ESM��ÿһ��
// 			for( iteReEsm = iteReqMsg->vctEsm.begin(); iteReEsm != iteReqMsg->vctEsm.end(); iteReEsm++)
// 			{
// 				 nNumESMDOAz = 1;//ESM�źŵĵ��﷽λ�����ȣ�
// 				 nNumESMFre = 1;//ESM�źŵ�Ƶ�ʣ�GHz��
// 				 nNumESMPA = 1;//ESM�źŵķ���
// 				 nNumESMPzw = 1;//ESM�źŵ������ȣ�us��
// 				 nNumESMPRI = 1;//ESM�źŵ��ظ������ms��;�ظ�Ƶ��PRF=PRI�ĵ���
// 				 nNumESMSCan = 1;//ESM�źŵ�����״�����ɨ�����ڣ�s��
// 				//��������Ϣ�еĸ����������ȸ����ں����ݽṹ
// 				stFusEsm.dReachAzimuth = iteReEsm->dReachAzimuth; 
// 				stFusEsm.dZaiPin = iteReEsm->dZaiPin;
// 				stFusEsm.dPulseExtent = iteReEsm->dPulseExtent;
// 				stFusEsm.dMaiKuan = iteReEsm->dMaiKuan;
// 				stFusEsm.dChongPin = iteReEsm->dChongPin;
// 				stFusEsm.dTianXianScan = iteReEsm->dTianXianScan;
// 				//����������Ϣ�е�ÿ���ṹ��
// 				for( iteBackMsg = vctBackMsg.begin(); iteBackMsg != vctBackMsg.end(); iteBackMsg++ )
// 				{   //�ж�������Ϣ�ͷ�����Ϣ�е��ۺ������Ƿ���ͬ,����ͬ�ٽ��д���
// 					if (iteReqMsg->lAutonum == iteBackMsg->lAutonum)
// 					{
// 						//(�ݲ����ڸ������(1),������)
// 						//(1)��������ϢΪ�޺���,������Ϣ���к���,��Ҫ���ںϺ���ۺ����Ÿ�Ϊ���ڵ���9000 ,���ܰ���������Ϣ��7000������
// 						//����������Ϣ�е�ÿ���ṹ���ESM������ÿ��ESM����Ϣ
// 						for( iteBaEsm = iteBackMsg->vctEsm.begin(); iteBaEsm != iteBackMsg->vctEsm.end(); iteBaEsm++)
// 						{
// 							//���Է���,�������
// 							//ESM�źŵĵ��﷽λ�����ȣ�
// 							//ESM�źŵ�Ƶ�ʣ�GHz��
// 							//ESM�źŵķ���
// 							//ESM�źŵ������ȣ�us��
// 							//ESM�źŵ��ظ������ms��;�ظ�Ƶ��PRF=PRI�ĵ���
// 							//ESM�źŵ�����״�����ɨ�����ڣ�s��
// 							double SumCorr = 0.0;
// 							Mf_SPA(iteBaEsm->dReachAzimuth,iteReEsm->dReachAzimuth,dcorrEsmReachAzimuth); //ESM�źŵĵ��﷽λ�����ȣ�
// 							VctCorr.push_back(dcorrEsmReachAzimuth);
// 							Mf_SPA(iteBaEsm->dZaiPin,iteReEsm->dZaiPin,dcorrZaiPin); //ESM�źŵ�Ƶ�ʣ�GHz��
// 							VctCorr.push_back(dcorrZaiPin);
// 							Mf_SPA(iteBaEsm->dPulseExtent,iteReEsm->dPulseExtent,dcorrEsmPulseExtent); //ESM�źŵķ���
// 							VctCorr.push_back(dcorrEsmPulseExtent);
// 							Mf_SPA(iteBaEsm->dMaiKuan,iteReEsm->dMaiKuan,dcorrMaiKuan); //ESM�źŵ������ȣ�us��
// 							VctCorr.push_back(dcorrMaiKuan);
// 							Mf_SPA(iteBaEsm->dChongPin,iteReEsm->dChongPin,dcorrChongPin); //ESM�źŵ��ظ������ms��;�ظ�Ƶ��PRF=PRI�ĵ���
// 							VctCorr.push_back(dcorrChongPin);
// 							Mf_SPA(iteBaEsm->dTianXianScan,iteReEsm->dTianXianScan,dcorrTianXianScan); //ESM�źŵ�����״�����ɨ�����ڣ�s��
// 							VctCorr.push_back(dcorrTianXianScan);
// 							//�����ϵ����������ȡ���������ݵ�ƽ��ֵ
// 							for (iteCorr = VctCorr.begin(); iteCorr != VctCorr.end(); iteCorr++)
// 							{
// 								SumCorr = SumCorr + *iteCorr;  
// 							}
// 							dAverCorr = SumCorr/VctCorr.size();  //ȡ���ϵ����ƽ��ֵ
// 							//�´δ�ż���ϵ��ǰ�����VctCorr����
// 							VctCorr.clear();
// 							//����ֵ�Ƚϣ��趨��ֵ�����ϵ������ĳ��ֵʱ����ΪESM�ǿ��Թ����ģ�
// 							if (dAverCorr > 0.8) 
// 							{
// 								iteBaEsm->lFusFlag = 1; //�ںϲ��ұ��,�ܹ�����
// 								//��������Ϣ�����������ۼ�,����¼�ۼӸ���
// 								stFusEsm.dReachAzimuth += iteBaEsm->dReachAzimuth;
// 								nNumESMDOAz++;
// 								stFusEsm.dZaiPin += iteBaEsm->dZaiPin;
// 								nNumESMFre ++;//ESM�źŵ�Ƶ�ʣ�GHz��
// 								stFusEsm.dPulseExtent += iteBaEsm->dPulseExtent;
// 								nNumESMPA ++;//ESM�źŵķ���
// 								stFusEsm.dMaiKuan += iteBaEsm->dMaiKuan;
// 								nNumESMPzw ++;//ESM�źŵ������ȣ�us��
// 								stFusEsm.dChongPin += iteBaEsm->dChongPin;
// 								nNumESMPRI ++;//ESM�źŵ��ظ������ms��;�ظ�Ƶ��PRF=PRI�ĵ���
// 								stFusEsm.dTianXianScan += iteBaEsm->dTianXianScan;
// 								nNumESMSCan ++;
// 							}
// 						}//for( iteBaEsm = iteBackMsg->vctEsm.begin()	
// 					}// if �ж��ۺ������Ƿ���ͬ
// 				}//	for( iteBackMsg = vctBackMsg.begin()
// 				//ÿ��������Ϣ��Esm����֮��,������������ȡƽ��ֵ��,�����ں���Ϣ������
//                 stFusEsm.dReachAzimuth  =  stFusEsm.dReachAzimuth/nNumESMDOAz; 
// 				stFusEsm.dZaiPin = stFusEsm.dZaiPin/nNumESMFre;
// 				stFusEsm.dPulseExtent = stFusEsm.dPulseExtent/nNumESMPA;
// 				stFusEsm.dMaiKuan = stFusEsm.dMaiKuan/nNumESMPzw;
// 				stFusEsm.dChongPin = stFusEsm.dChongPin/nNumESMPRI;
// 				stFusEsm.dTianXianScan = stFusEsm.dTianXianScan/nNumESMSCan;
// 				//��������Ϣ������������ֵ���ں���Ϣ,��:����ʶ���ƽ̨���ͺ��ۺϿ��Ŷ�
// 				//�������,���������һ�����ݿ�ʼ����, �ۺ�ʶ�����еĵ�ǰ�ĸ�����ʶ�����ƽ̨���ͺ��ۺϿ��Ŷ�
// 				stFusEsm.lAutonum = iteReqMsg->lAutonum;  //�ۺ�����
//                 for ( r_iteMIdenti = vctMidentiinforMsg.rbegin(); r_iteMIdenti != vctMidentiinforMsg.rend(); ++r_iteMIdenti )
//                 {
// 					// ������� 
// 					if ( r_iteMIdenti->lAutonum == stFusEsm.lAutonum )
// 					{
// 						strcpy( stFusEsm.sPlatType, r_iteMIdenti->sPlatType ); //�ۺ�ƽ̨����
// 						stFusEsm.dConfidence = r_iteMIdenti->dConfidence;  //�ۺϿ��ж�
// 						break;
// 					}
//                 }
// 				for( iteBackMsg2 = vctBackMsg.begin(); iteBackMsg2 != vctBackMsg.end(); iteBackMsg2++ )
// 				{
// 					if ( iteReqMsg->lAutonum <8000 ) //������Ϣ���޺�����Ϣ
// 					{
// 						if (iteBackMsg2->BackTrackN != 0)
// 						{
// 							stFusEsm.lAutonum +=2000;  //��������Ϣ���к���,���ۺ���������2000,��Ϊ9000
// 							 TFlag = 1;  //���Ϊ1,����ı��ۺ�����
// 							break;
// 						}
// 					}
// 				}
// 
// 				stFusEsm.lTargetNumber = iteReEsm->lTargetNumber; //Ŀ������
// 				strcpy(stFusEsm.cEquipmentNumber , iteReEsm->cEquipmentNumber);  //�豸���
// 				strcpy(stFusEsm.cEquipmentType,iteReEsm->cEquipmentType); //�豸����
// 				strcpy(stFusEsm.cDWAttribute , iteReEsm->cDWAttribute);   //��������
// 				strcpy(stFusEsm.cCountry , iteReEsm->cCountry);           //����/����
//                 strcpy(stFusEsm.cPlatName , iteReEsm->cPlatName); //ƽ̨����
// 				strcpy(stFusEsm.cPlatNumber, iteReEsm->cPlatNumber);//ƽ̨���
// 				strcpy(stFusEsm.cRadarName, iteReEsm->cRadarName);//�״�����
// 				strcpy(stFusEsm.cRadarPurpose, iteReEsm->cRadarPurpose);//�״���;
//                 stCoFusiInfor.vctFusEsm.push_back(stFusEsm);
// 			}//for( iteReEsm = iteReqMsg->vctEsm.begin()
// 		}//if( iteReqMsg->vctEsm.size() !=0 )
// 		//������Ϣ�е�ÿ����Ϣ��������ɺ������������Ϣ����ESM��Ϣ,��������Ϣ�л�����Ϣ���ںϱ�ǲ�Ϊ1,˵��δ���ں�,�򲹳�ԭ������Ϣ
// 		for( iteBackMsg1 = vctBackMsg.begin(); iteBackMsg1 != vctBackMsg.end(); iteBackMsg1++ )
// 		{ //����������Ϣ�е�ÿ���ṹ���ESM������ÿ��ESM����Ϣ
// 			for( iteBaEsm1 = iteBackMsg->vctEsm.begin(); iteBaEsm1 != iteBackMsg->vctEsm.end(); iteBaEsm1++)
// 			{
// 				if ( iteBaEsm1->lFusFlag != 0 )
// 				{
// 					if( TFlag == 1 )  //�����ۺ��������2000
// 					{
// 						iteBaEsm1->lAutonum += 2000;
// 					}
// 					stCoFusiInfor.vctFusEsm.push_back(*iteBaEsm1);
// 				}//if iteBaEsm1->lFusFlag != 0
// 			}//for
// 		}//for
// 		//	vctCoFusMsg.push_back(stCoFusiInfor.vctFusEsm);
// 
// 	}//for ÿһ��������Ϣ


// 		for ( iteReqMsg = vctReqMsg.begin(); iteReqMsg != vctReqMsg.end(); iteReqMsg++)
// 		{
// 			int TFlag = 0;
// 			if( iteReqMsg->vctComm.size() !=0 )
// 			{//����������Ϣ�е�ESM��ÿһ��
// 				for( iteReCom = iteReqMsg->vctComm.begin(); iteReCom != iteReqMsg->vctComm.end(); iteReCom++)
// 				{
// 					int nNumCOMDOAz = 1; //COM�źŵĵ��﷽λ�����ȣ�   
// 					int nNumCOMFre = 1;  //COM�źŵ�����Ƶ�ʣ�MHz��
// 					int nNumCOMPA = 1; 	//COM�źŵķ���
// 					int nNumCOMBand = 1; //COM�źŵ��źŴ���MHz��
// 					int nNumCOMJPN = 1; //COM�źŵ���������
// 					//��������Ϣ�еĸ����������ȸ����ں����ݽṹ
// 					stFusCom.dReachAzimuth = iteReCom->dReachAzimuth; 
// 					stFusCom.dComFre = iteReCom->dComFre;
// 					stFusCom.dPulseExtent= iteReCom->dPulseExtent;
// 					stFusCom.dComBand = iteReCom->dComBand;
// 					stFusCom.dComJPN = iteReCom->dComJPN;
// 					//����������Ϣ�е�ÿ���ṹ��
// 					for( iteBackMsg = vctBackMsg.begin(); iteBackMsg != vctBackMsg.end(); iteBackMsg++ )
// 					{   //�ж�������Ϣ�ͷ�����Ϣ�е��ۺ������Ƿ���ͬ,����ͬ�ٽ��д���
// 						if (iteReqMsg->lAutonum == iteBackMsg->lAutonum)
// 						{
// 							//(�ݲ����ڸ������(1),������)
// 							//(1)��������ϢΪ�޺���,������Ϣ���к���,��Ҫ���ںϺ���ۺ����Ÿ�Ϊ���ڵ���9000 ,���ܰ���������Ϣ��7000������
// 							//����������Ϣ�е�ÿ���ṹ���ESM������ÿ��ESM����Ϣ
// 							for( iteBaCom = iteBackMsg->vctComm.begin(); iteBaCom != iteBackMsg->vctComm.end(); iteBaCom++)
// 							{
// 								//���Է���,�������
// 								//COM�źŵĵ��﷽λ�����ȣ�
// 								//COM�źŵ�����Ƶ�ʣ�MHz��
// 								//COM�źŵķ���
// 								//COM�źŵ��źŴ���MHz��
// 								//COM�źŵ���������
// 								double SumCorr = 0.0;
// 								Mf_SPA(iteBaCom->dReachAzimuth,iteReCom->dReachAzimuth,dcorrComReachAzimuth); //COM�źŵĵ��﷽λ�����ȣ�
// 								VctCorr.push_back(dcorrComReachAzimuth);
// 								Mf_SPA(iteBaCom->dComFre,iteReCom->dComFre,dcorrFre); //COM�źŵ�����Ƶ�ʣ�MHz��
// 								VctCorr.push_back(dcorrFre);
// 								Mf_SPA(iteBaCom->dPulseExtent,iteReCom->dPulseExtent,dcorrComPulseExtent); //COM�źŵķ���
// 								VctCorr.push_back(dcorrComPulseExtent);
// 								Mf_SPA(iteBaCom->dComBand,iteReCom->dComBand,dcorrBand); //COM�źŵ��źŴ���MHz��
// 								VctCorr.push_back(dcorrBand);
// 								Mf_SPA(iteBaCom->dComJPN,iteReCom->dComJPN,dcorrJPN); //COM�źŵ���������
// 								VctCorr.push_back(dcorrJPN);
// 								//�����ϵ����������ȡ���������ݵ�ƽ��ֵ
// 								for (iteCorr = VctCorr.begin(); iteCorr != VctCorr.end(); iteCorr++)
// 								{
// 									SumCorr = SumCorr + *iteCorr;  
// 								}
// 								dAverCorr = SumCorr/VctCorr.size();  //ȡ���ϵ����ƽ��ֵ
// 								//�´δ�ż���ϵ��ǰ�����VctCorr����
// 								VctCorr.clear();
// 								//����ֵ�Ƚϣ��趨��ֵ�����ϵ������ĳ��ֵʱ����ΪCOM�ǿ��Թ����ģ�
// 								if (dAverCorr > 0.8) 
// 								{
// 									iteBaEsm->lFusFlag = 1; //�ںϲ��ұ��,�ܹ�����
// 									//��������Ϣ�����������ۼ�,����¼�ۼӸ���
// 									stFusCom.dReachAzimuth += iteBaCom->dReachAzimuth;
// 									nNumCOMDOAz++;
// 									stFusCom.dComFre += iteBaCom->dComFre;
// 									nNumCOMFre ++;//cOM�źŵ�Ƶ�ʣ�GHz��
// 									stFusCom.dPulseExtent += iteBaCom->dPulseExtent;
// 									nNumCOMPA ++;//com�źŵķ���
// 									stFusCom.dComBand += iteBaCom->dComBand;
// 									nNumCOMBand ++;//COM�źŵ��źŴ���MHz��
// 									stFusCom.dComJPN += iteBaCom->dComJPN;
// 									nNumCOMJPN ++;//COM�źŵ���������
// 								}
// 							}//for( iteBaEsm = iteBackMsg->vctEsm.begin()	
// 						}// if �ж��ۺ������Ƿ���ͬ
// 					}//	for( iteBackMsg = vctBackMsg.begin()
// 					//ÿ��������Ϣ��Esm����֮��,������������ȡƽ��ֵ��,�����ں���Ϣ������
// 					stFusCom.dReachAzimuth  =  stFusEsm.dReachAzimuth/nNumCOMDOAz; 
// 					stFusCom.dComFre = stFusCom.dComFre/nNumCOMFre;
// 					stFusCom.dPulseExtent = stFusCom.dPulseExtent/nNumCOMPA;
// 					stFusCom.dComBand = stFusCom.dComBand/nNumCOMBand;
// 					stFusCom.dComJPN = stFusCom.dComJPN /nNumCOMJPN;
// 					//��������Ϣ������������ֵ���ں���Ϣ,��:����ʶ���ƽ̨���ͺ��ۺϿ��Ŷ�
// 					//�������,���������һ�����ݿ�ʼ����, �ۺ�ʶ�����еĵ�ǰ�ĸ�����ʶ�����ƽ̨���ͺ��ۺϿ��Ŷ�
// 					stFusCom.lAutonum = iteReqMsg->lAutonum;  //�ۺ�����
// 					for ( r_iteMIdenti = vctMidentiinforMsg.rbegin(); r_iteMIdenti != vctMidentiinforMsg.rend(); ++r_iteMIdenti )
// 					{
// 						// ������� 
// 						if ( r_iteMIdenti->lAutonum == stFusCom.lAutonum )
// 						{
// 							strcpy( stFusCom.sPlatType, r_iteMIdenti->sPlatType ); //�ۺ�ƽ̨����
// 							stFusCom.dConfidence = r_iteMIdenti->dConfidence;  //�ۺϿ��ж�
// 							break;
// 						}
// 					}
// 					for( iteBackMsg2 = vctBackMsg.begin(); iteBackMsg2 != vctBackMsg.end(); iteBackMsg2++ )
// 					{
// 						if ( iteReqMsg->lAutonum <8000 ) //������Ϣ���޺�����Ϣ
// 						{
// 							if (iteBackMsg2->BackTrackN != 0)
// 							{
// 								stFusCom.lAutonum +=2000;  //��������Ϣ���к���,���ۺ���������2000,��Ϊ9000
// 								TFlag = 1;  //���Ϊ1,����ı��ۺ�����
// 								break;
// 							}
// 						}
// 					}
// 
// 					stFusCom.lTargetNumber = iteReCom->lTargetNumber; //Ŀ������
// 					strcpy(stFusCom.cEquipmentNumber , iteReCom->cEquipmentNumber);  //�豸���
// 					strcpy(stFusCom.cEquipmentType,iteReCom->cEquipmentType); //�豸����
// 					strcpy(stFusCom.cDWAttribute , iteReCom->cDWAttribute);   //��������
// 					strcpy(stFusCom.cCountry , iteReCom->cCountry);           //����/����
// 					strcpy(stFusCom.cPlatName , iteReCom->cPlatName); //ƽ̨����
// 					strcpy(stFusCom.cPlatNumber, iteReCom->cPlatNumber);//ƽ̨���
// 					stCoFusiInfor.vctFusCom.push_back(stFusCom);
// 			}//for( iteReEsm = iteReqMsg->vctEsm.begin()
// 		}//if( iteReqMsg->vctEsm.size() !=0 )
// 		//������Ϣ�е�ÿ����Ϣ��������ɺ������������Ϣ����ESM��Ϣ,��������Ϣ�л�����Ϣ���ںϱ�ǲ�Ϊ1,˵��δ���ں�,�򲹳�ԭ������Ϣ
// 		for( iteBackMsg1 = vctBackMsg.begin(); iteBackMsg1 != vctBackMsg.end(); iteBackMsg1++ )
// 		{ //����������Ϣ�е�ÿ���ṹ���ESM������ÿ��ESM����Ϣ
// 			for( iteBaCom1 = iteBackMsg->vctComm.begin(); iteBaCom1 != iteBackMsg->vctComm.end(); iteBaCom1++)
// 			{
// 				if ( iteBaCom1->lFusFlag != 0 )
// 				{
// 					stCoFusiInfor.vctFusCom.push_back(*iteBaCom1);
// 					
// 					if( TFlag == 1 )  //�����ۺ��������2000
// 					{
// 						iteBaCom1->lAutonum += 2000;
// 					}
// 				}//if iteBaEsm1->lFusFlag != 0
// 			}//for
// 		}//for
// 		//	vctCoFusMsg.push_back(stCoFusiInfor.vctFusCom);
// 	}//for ÿһ��������Ϣ

/*} //��������*/

/************************************************************************/
/*                             ���Է�������                             */
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
// 	corr=spa;                 //�����������ϵ��
// }