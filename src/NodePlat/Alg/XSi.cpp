
/*****************�ڽ����� 0811 wanghaiying*****************/
//1. ��ȡЭͬ��Ϣ���ж�����Ŀ�꺽�����ȸ��ݾ����־���ж��Ƿ����������Ѿ��۹�����ж��ۺ����ţ�����8000��Ϊ�к�����Ϣ��С��8000��Ϊ�޺�����Ϣ��
//     (1)��Ŀ�꺽����a. ����ת���������󽢵�Ŀ�꺽���е�����ת������(��ƽ̨)�״�����ϵ��
//                    b. ��<TRACE,ESM,COM>������У�ƥ��������ڽ�������������Ϣ�����ظ�����
//                    c. �����ϱ����Ҳ���ƥ����Ϣ�����<ESM,COM>�����,<ESM>������,<COM>��������ƥ���������������������Ϣ�����ظ�����
//     (2)��Ŀ�꺽����a. ƥ�����ESM��ͨ������������������Ϣ���ȴ� <TRACE,ESM,COM>������в��ҡ�
//                    b. �����ϱ����Ҳ���ƥ����Ϣ�����������Ҳ�޸�Ŀ��ĺ�����Ϣ----���涨λ��ȡ(������Ϣ��������)???
/*****************************************/

//������Ϣ��ֻ�к�������Ϣ���ӱ����ľ��������ҳ���ָ��ͬһĿ��ĺ�����Ϣ��
//��������ϢVCT_Request_Cooperative_Msg�е�Request_Cooperative_Msg�ṹ���е�TRACKSTATUS_MARK������Ϣ��ֵ,��Ϊ�������������

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
//�ֺ���:
//����������Ϣ�е��ۺ�����������������һ�ֺ���
//(��������8000����������Ϣ�Ǿ�����к�������Ϣ�����ú���1)
//(��������7000��8000֮�䣬��������Ϣ�Ǿ�����޺�������Ϣ�����ú���2)
//(������С��7000����ΪĿ�����ţ�������ϢΪδ����ĺ�����Ϣ�����ú���3)
void ReqUnin_COOP_Find_Information_To_MainShip(SHIP_POSITION& stSelfPosi,UNI_All_NUM& stUniAll, VCT_Request_Cooperative_Msg::iterator& iteRequestMsg,/*VCT_Request_Cooperative_Msg& vctRequestCooperative,*/ VCT_BACK_Cooperative_Msg& vctBackCooperative);
void ReqNoTraceUnin_COOP_Find_Information_To_MainShip(SHIP_POSITION& stSelfPosi,UNI_All_NUM& stUniAll, VCT_Request_Cooperative_Msg::iterator& iteRequestMsg,/*VCT_Request_Cooperative_Msg& vctRequestCooperative, */VCT_BACK_Cooperative_Msg& vctBackCooperative);
void ReqSingleTrace_COOP_Find_Information_To_MainShip(SHIP_POSITION& stSelfPosi,UNI_All_NUM& stUniAll, VCT_Request_Cooperative_Msg::iterator & iteRequestMsg,/*VCT_Request_Cooperative_Msg& vctRequestCooperative,*/ VCT_BACK_Cooperative_Msg& vctBackCooperative);
// �����ڽ�������������Ϣʱ���������ھ��뷽λ������ʱ���������ڽ���γ�߶���֪������ڽ��۲⵽��Ŀ���ڱ����ϵ����꼰����ڱ����ľ�γ�ߡ�
void Get_Coordinate_Conversion_Module(double Rd1,double Az1,double Ez1,double Rd2,double Az2,double Ez2,double La1,double Ba1,double Ha1,
									  double La2,double Ba2,double Ha2,/*double *x1,double *y1,double *z1,*/double& Xt,double& Yt,double& Zt,double& Rdt,double& Azt,double& Ezt,double& SumCorr);
void Mf_SPA(double s, double t,double& corr); //s,tΪ��ͬ���͵���Ϣ�����м��Է����������ص����ϵ����������VctCorr��
void Get_NO_SelfTrack_Coordinate_Conversion_Module(double Rd2,double Az2,double Ez2,double La1,double Ba1,double Ha1,
												   double La2,double Ba2,double Ha2,double& Xt,double& Yt,double& Zt);
void Object_Radar_Transform(double Lt,double Bt,double Ht,double L0,double B0,double H0,double& rd,double& az,double& ez);
/********************************************************************************/
/********************************************************************************/


//������Ϣ���к����ľ�����Ϣ���ۺ����Ŵ���7999
void ReqUnin_COOP_Find_Information_To_MainShip(SHIP_POSITION& stSelfPosi,UNI_All_NUM& stUniAll, VCT_Request_Cooperative_Msg::iterator & iteRequestMsg,/*VCT_Request_Cooperative_Msg& vctRequestCooperative,*/ VCT_BACK_Cooperative_Msg& vctBackCooperative)
{
//���� 	int a = iteRequestMsg->lAutonum;
	double Xt = 0.0;        //�������ʱ����Ҫ������IF ��forѭ���У����嵽�ⲿ����Ϊȫ�ֱ���
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
    double dAverCorr = 0.0; //��������Ϣ�����Է�����ȡƽ��ֵ������ϵ��
	//  TRACKSTATUS_MARK sttTrack;
	//	ESMSTATUS_MARK sttEsm;
	//	COMSTATUS_MARK sttCom;
    typedef vector<double> VCT_CORR;
	VCT_CORR VctCorr;      // ��Ź���ϵ��������
	VCT_CORR::iterator iteCorr;
	//  ������յĵ�����
	//  ��vctRequestCooperative�����У��������������ÿ�ഫ������Ϣ���ĵ�����
	//    VCT_TRACE_MSG::iterator iteTrace; //��Ϊÿ���ṹ�������к�����ֻ����һ��������ֱ���ú�����Ϣ�Ľṹ��
	VCT_ESM_MSG::iterator iteEsm;                
	VCT_COMM_MSG::iterator iteCom;
	//�к���
	VCT_UNINUM_MSG::iterator iteUnin;
	//�к��� ����������Esm,Com���ĵ�����
	//	VCT_ESM_MSG::iterator iteUninEs;
	//	VCT_COMM_MSG::iterator iteUninCo;
	
	//�޺���
	VCT_UNINOTRACE_MSG::iterator iteNoTraceUnin;
	//�޺��� ����������ESM��com���ĵ�����
	VCT_ESM_MSG::iterator iteNoTraceEs;
	VCT_ESM_MSG::iterator iteNoTraceEs1;
	VCT_COMM_MSG::iterator iteNoTraceCo;
	VCT_COMM_MSG::iterator iteNoTraceCo1;
	
	//δ���� �������������ÿ�ഫ������Ϣ���ĵ�����
	VCT_TRACE_MSG::iterator iteTra;
	VCT_ESM_MSG::iterator iteEs;
	VCT_COMM_MSG::iterator iteCo;
	
	VCT_BACK_Cooperative_Msg::iterator iteBackMsg;
	BACK_Cooperative_Msg stBackMsg;
	//	VCT_Request_Cooperative_Msg::iterator iteRequestMsg;
	//������Ϣ�� ESM��COM���������ÿ�ഫ������Ϣ���ĵ�����
	VCT_ESM_MSG::iterator re_iteEs;
	VCT_COMM_MSG::iterator re_iteCo;
	
	//��� vctBackCooperative
	for (iteBackMsg = vctBackCooperative.begin(); iteBackMsg != vctBackCooperative.end(); iteBackMsg++)
	{	
		//��� vctBackCooperative
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
		////�Ժ����ṹ���еĲ�����Ϣ���м��Է���,���� Vx,Vy,Vz(Ŀ�����ڽ�������ϵ�¸����귽���ϵľ����ٶ���Ҫת������������ϵ�²�������????????)
		//Mf_SPA(iteUnin->structTrace.dRange,Rdt,corrRd);
		//VctCorr.push_back(dcorrRd);
		//Mf_SPA(iteUnin->structTrace.dAzimuth,Azt,corrAz);
		//VctCorr.push_back(dcorrAz);
		//Mf_SPA(iteUnin->structTrace.dElevationAngle,Ezt,corrEz); 
		//VctCorr.push_back(dcorrEz);
		//�����������µľ����ٶ�Vx,Vy,Vzδת����ֱ�������Է�������
	    Mf_SPA(iteUnin->structTrace.dTSpeedX,iteRequestMsg->stTrace.dTSpeedX,dcorrVx);
		VctCorr.push_back(dcorrVx);
		Mf_SPA(iteUnin->structTrace.dTSpeedY,iteRequestMsg->stTrace.dTSpeedY,dcorrVy);
		VctCorr.push_back(dcorrVy);
		Mf_SPA(iteUnin->structTrace.dTSpeedZ,iteRequestMsg->stTrace.dTSpeedZ,dcorrVz);
		VctCorr.push_back(dcorrVz);
	    //�����ϵ����������ȡ���������ݵ�ƽ��ֵ
	    for (iteCorr = VctCorr.begin(); iteCorr != VctCorr.end(); iteCorr++)
		{
		   dSumCorr = dSumCorr + *iteCorr;  
		}
		dAverCorr = dSumCorr/VctCorr.size();  //ȡ���ϵ����ƽ��ֵ
		//�´δ�ż���ϵ��ǰ�����VctCorr����
		VctCorr.clear();
		//����ֵ�Ƚϣ�����趨��ֵ�����ϵ������ĳ��ֵʱ����Ϊ�����ǿ��Թ�����????????????????????? ����ʱ�޸ģ�
		if (dAverCorr > 0.8) //0.8Ϊ��ֵ������ʱ�ɵ���
		{	//������Ϣ���Թ���������Ϣ����vctBackCooperative������Ϣ�����У�
			//��ͬһ�������£�����ͬ��λ�£���һ��������Ϣ������N��ESM��Com��Ϣ����vctBackCooperative��
			//�������			
			//				cout<<"�ۺ�����"<< iteUnin->lAutonum<<endl;
			//				cout<<"������Ϣ��ʼ�����ۺ�����"<<iteBackMsg->lAutonum<<endl;
			//��������Ϣ���ۺ����ŵ�������Ϣ��
			stBackMsg.lAutonum = iteRequestMsg->lAutonum;    //��������Ϣ���ۺ����ż�¼�ڷ�����Ϣ��
			//				cout<<"�޸ĺ󷵻���Ϣ�ۺ�����"<<stBackMsg.lAutonum<<endl;
			//�汾����γ�ߵ�������Ϣ��
			memcpy(&stBackMsg.stBackShipPosi,&stSelfPosi,sizeof(stBackMsg.stBackShipPosi));  //memcpy(&A,&B,sizeof(A)); �ѽṹ��B���ṹ��A
			//�溽����Ϣ
			memcpy(&stBackMsg.stTrace,&iteUnin->structTrace,sizeof(stBackMsg.stTrace));	
		
			//��ESM��Ϣ
			if (iteUnin->vctEsm.size() !=0)
			{
				for (iteEs = iteUnin->vctEsm.begin(); iteEs != iteUnin->vctEsm.end(); iteEs++)
				{
					stBackMsg.vctEsm.push_back(*iteEs);
				}
			}
			//��COM ��Ϣ
			if (iteUnin->vctComm.size() != 0)
			{
				for (iteCo = iteUnin->vctComm.begin(); iteCo != iteUnin->vctComm.end(); iteCo++)
				{
					stBackMsg.vctComm.push_back(*iteCo);
				}
			}
			stBackMsg.BackTrackN = 1;  //������������
			stBackMsg.BackESMN = stBackMsg.vctEsm.size();
			stBackMsg.BackCOMN = stBackMsg.vctComm.size();
			
			//�����ҵ�����Ϣ����vctBackCooperative������
			vctBackCooperative.push_back(stBackMsg);
			//�������     				
			//for (iteBackMsg = vctBackCooperative.begin(); iteBackMsg != vctBackCooperative.end(); iteBackMsg++)
			//{
			//int PiHao = iteBackMsg->lAutonum;
			//int Ts = iteBackMsg->BackTrackN;
			//int Es = iteBackMsg->BackESMN;
			//int Cs = iteBackMsg->BackCOMN;
			//cout<<"������Ϣ�ۺ�����"<<iteBackMsg->lAutonum<<endl;
			//cout<<"       &������Ϣ�ĺ�����Ϣ....& Ŀ������ٶ� Vx: "<< iteBackMsg->stTrace.dTSpeedX <<"   Vy: "<<iteBackMsg->stTrace.dTSpeedY << "   Vz:"<<iteBackMsg->stTrace.dTSpeedZ <<endl;
			//cout<<"       &������Ϣ��ʶ����Ϣ....&"<<"������"<< iteBackMsg->stTrace.sPlatType <<"    " <<iteBackMsg->stTrace.cDWAttribute <<"   " <<iteBackMsg->stTrace.dConfidence<<endl;
			//cout<<"       &���صĺ�����Ϣ��"<< iteBackMsg->BackTrackN <<" ��"<< endl;
			//cout<<"       &���ص�ESM��Ϣ��"<< iteBackMsg->BackESMN <<" ��"<<endl;
			//cout<<"       &���ص�COM��Ϣ�� "<< iteBackMsg->BackCOMN <<" ��"<<endl;
			//}
			iteRequestMsg->nCorrFlag = 1; // ֱ���ҵ���������Ϣ���������Ϣ,����־��Ϣ��Ϊ1����һֱ�Ҳ������־ʼ��Ϊ0��
			break;//�ҵ�������ѭ��
					//���ˣ��Ӿ������ȡ��������Ϣ��ͬһ�ۺ������£�����ͬ��λ�£���TRACE,ESM��COM��Ϣ��������vctBackCooperative������ 
		}//0.8Ϊ��ֵ������ʱ�ɵ���
		//else 
		//{   
		//continue;
		//}//δ�ҵ�������Ϣ	
	}//for  iteUnin �����к�����������ݺ�������ת���ͼ��Է�����
	
	
	//һ��<2> 
		  if ( iteRequestMsg->nCorrFlag == 0 ) //������Ϣ��δ�ҵ�������Ϣʱ ��������޺��������
		  {
			  if (iteRequestMsg->vctEsm.size() !=0)   //if������Ϣ����ESM��Ϣ
			  {
				  if (iteRequestMsg->vctComm.size() !=0) //if ��������Com��Ϣ ����ESM �ȽϺ�û�й�����Ϣ���ٱȽ�COM ��Ϣ
				  {
					  for ( re_iteEs = iteRequestMsg->vctEsm.begin(); re_iteEs != iteRequestMsg->vctEsm.end();re_iteEs++)
					  {
						  //���޺����ľ�����в���,�޺����б���ESM��COM��Ϣ
						  for (iteNoTraceUnin = stUniAll.vctNoTraceUnin.begin(); iteNoTraceUnin != stUniAll.vctNoTraceUnin.end(); iteNoTraceUnin++)
						  {  //���������޺�����Ϣʱ
							  //�Ƿ�������ת��........		 Get_NO_SelfTrack_Coordinate_Conversion_Module(iteRequestMsg->stTrace.dRange,iteRequestMsg->stTrace.dAzimuth,iteRequestMsg->stTrace.dElevationAngle,
							  // 								 stSelfPosi.dLati,stSelfPosi.dLonti,stSelfPosi.dHeight,
							  // 								 iteRequestMsg->stReqShipPosi.dLati,iteRequestMsg->stReqShipPosi.dLonti,iteRequestMsg->stReqShipPosi.dHeight,
							  // 								 Xt,Yt,Zt);
							  //һ��<2>a.
							  for (iteNoTraceEs = iteNoTraceUnin->vctEsm.begin(); iteNoTraceEs != iteNoTraceUnin->vctEsm.end(); iteNoTraceEs++ )
							  {
								  double dSumCorr = 0.0;
								  Mf_SPA(iteNoTraceEs->dChongPin,re_iteEs->dChongPin,dcorrChongPin); //Ƶ��
								  VctCorr.push_back(dcorrChongPin);
								  Mf_SPA(iteNoTraceEs->dMaiKuan,re_iteEs->dMaiKuan,dcorrMaiKuan); //����
								  VctCorr.push_back(dcorrMaiKuan);
								  Mf_SPA(iteNoTraceEs->dTianXianScan,re_iteEs->dTianXianScan,dcorrTianXianScan); //����ɨ������
								  VctCorr.push_back(dcorrTianXianScan);
								  //�����ϵ����������ȡ���������ݵ�ƽ��ֵ
								  for (iteCorr = VctCorr.begin(); iteCorr != VctCorr.end(); iteCorr++)
								  {
									  dSumCorr = dSumCorr + *iteCorr;  
								  }
								  dAverCorr = dSumCorr/VctCorr.size();  //ȡ���ϵ����ƽ��ֵ
								  //�´δ�ż���ϵ��ǰ�����VctCorr����
								  VctCorr.clear();
								  //����ֵ�Ƚϣ��趨��ֵ�����ϵ������ĳ��ֵʱ����ΪESM�ǿ��Թ����ģ�
								  if (dAverCorr > 0.8)
								  {
									  //���ҵ���ESM��ͬһ�ۺ������µ�COM��Ϣ����vctBackCooperative������
									  stBackMsg.lAutonum = iteRequestMsg->lAutonum;  //��������Ϣ���ۺ����ż�¼�ڷ�����Ϣ��
									  //��ESM��Ϣ
									  for ( iteNoTraceEs1 = iteNoTraceUnin->vctEsm.begin();iteNoTraceEs1 !=iteNoTraceUnin->vctEsm.end(); iteNoTraceEs1++)
									  {
										  stBackMsg.vctEsm.push_back(*iteNoTraceEs1);
									  }
									  //��COM ��Ϣ
									  if (iteNoTraceUnin->vctComm.size() != 0)
									  {
										  for (iteNoTraceCo = iteNoTraceUnin->vctComm.begin();iteNoTraceCo !=iteNoTraceUnin->vctComm.end(); iteNoTraceCo++)
										  {
											  stBackMsg.vctComm.push_back(*iteNoTraceCo);
										  }
									  }
									  stBackMsg.BackTrackN = 0;  //������������
									  stBackMsg.BackESMN = stBackMsg.vctEsm.size();
									  stBackMsg.BackCOMN = stBackMsg.vctComm.size();
									  //�����ҵ�����Ϣ����vctBackCooperative������
									  vctBackCooperative.push_back(stBackMsg);
									  iteRequestMsg->nCorrFlag = 1; // ֱ���ҵ���������Ϣ���������Ϣ,����־��Ϣ��Ϊ1����һֱ�Ҳ������־ʼ��Ϊ0��
									  break;
								  } //if AverCorr > 0.8 ����
								  // else { nosearchFlag = 2;}
							  }// for iteNoTraceEs	
							  if (iteRequestMsg->nCorrFlag == 1) //��־λ1���������ҵ������Ϣ�������iteNoTraceUnin ��ѭ����
							  {
								  break;
							  }
							  // ��ESM ��û�ҵ� ������iteNoTraceUnin��ѭ�����Ƚ���һ���ṹ���еĶ���ESM��Ϣ
							  
						  }//for iteNoTraceUnin
						  
						  if (iteRequestMsg->nCorrFlag == 1) //��־λ1���������ҵ������Ϣ�������re_iteEs ��ѭ����
						  {
							  break;
						  } //������������Ϣ��vctEsm�е���һ��ESM�������е�ESM�Ƚ�
						  
					  }//for re_iteEs ����������Ϣ�е�ÿ��ESM��Ϣ
					  
					  if (iteRequestMsg->nCorrFlag == 0)  //�������е�ESM ��δ�ҵ��������COM��Ϣ
					  {
						  for ( re_iteCo = iteRequestMsg->vctComm.begin(); re_iteCo != iteRequestMsg->vctComm.end();re_iteCo++)
						  {
							  //���޺����ľ�����в���,�޺����б���ESM��COM��Ϣ
							  for (iteNoTraceUnin = stUniAll.vctNoTraceUnin.begin(); iteNoTraceUnin != stUniAll.vctNoTraceUnin.end(); iteNoTraceUnin++)
							  {  //���������޺�����Ϣʱ
								  for (iteNoTraceCo = iteNoTraceUnin->vctComm.begin(); iteNoTraceCo != iteNoTraceUnin->vctComm.end(); iteNoTraceCo++ )
								  {
									  double dSumCorr = 0.0;
									  Mf_SPA(iteCo->dComZaiPin,re_iteCo->dComZaiPin,dcorrComZaiPin); //��Ƶ
									  VctCorr.push_back(dcorrComZaiPin);
									  Mf_SPA(iteCo->dPulseExtent,re_iteCo->dPulseExtent,dcorrdPulseExtent); //�������
									  VctCorr.push_back(dcorrdPulseExtent);
								//0909�޸�:����COM�ļ��Է�������:  �������Ƶ����	 
									  Mf_SPA(iteCo->dComBand,re_iteCo->dComBand,dcorrBand);//����
									  VctCorr.push_back(dcorrBand);
									  Mf_SPA(iteCo->dComJPN,re_iteCo->dComJPN,dcorrJPN);//��Ƶ����
									  VctCorr.push_back(dcorrJPN);
									  
									  //�����ϵ����������ȡ���������ݵ�ƽ��ֵ
									  for (iteCorr = VctCorr.begin(); iteCorr != VctCorr.end(); iteCorr++)
									  {
										  dSumCorr = dSumCorr + *iteCorr;  
									  }
									  dAverCorr = dSumCorr/VctCorr.size();  //ȡ���ϵ����ƽ��ֵ
									  //�´δ�ż���ϵ��ǰ�����VctCorr����
									  VctCorr.clear();
									  //����ֵ�Ƚϣ��趨��ֵ�����ϵ������ĳ��ֵʱ����ΪESM�ǿ��Թ����ģ�
									  if (dAverCorr > 0.8)
									  {
										  //���ҵ���ESM��ͬһ�ۺ������µ�COM��Ϣ����vctBackCooperative������
										  stBackMsg.lAutonum = iteRequestMsg->lAutonum;  //��������Ϣ���ۺ����ż�¼�ڷ�����Ϣ��
										  //��ESM��Ϣ
										  for ( iteNoTraceEs = iteNoTraceUnin->vctEsm.begin();iteNoTraceEs !=iteNoTraceUnin->vctEsm.end(); iteNoTraceEs++)
										  {
											  stBackMsg.vctEsm.push_back(*iteNoTraceEs);
										  }
										  //��COM ��Ϣ
										  if (iteNoTraceUnin->vctComm.size() != 0)
										  {
											  for (iteNoTraceCo1 = iteNoTraceUnin->vctComm.begin();iteNoTraceCo1 !=iteNoTraceUnin->vctComm.end(); iteNoTraceCo1++)
											  {
												  stBackMsg.vctComm.push_back(*iteNoTraceCo1);
											  }
										  }
										  stBackMsg.BackTrackN = 0;  //������������
										  stBackMsg.BackESMN = stBackMsg.vctEsm.size();
										  stBackMsg.BackCOMN = stBackMsg.vctComm.size();
										  //�����ҵ�����Ϣ����vctBackCooperative������
										  vctBackCooperative.push_back(stBackMsg);
										  iteRequestMsg->nCorrFlag = 1; // ֱ���ҵ���������Ϣ���������Ϣ,����־��Ϣ��Ϊ1����һֱ�Ҳ������־ʼ��Ϊ0��
										  break;
									  } //if AverCorr > 0.8 ����
								  }// for iteNoTraceEs	
								  if (iteRequestMsg->nCorrFlag == 1) //��־λ1���������ҵ������Ϣ�������iteNoTraceUnin ��ѭ����
								  {
									  break;
								  }
								  // ��COM ��û�ҵ� ������iteNoTraceUnin��ѭ�����Ƚ���һ���ṹ���еĶ���com��Ϣ
								  
							  }//for iteNoTraceUnin
							  
							  if (iteRequestMsg->nCorrFlag == 1) //��־λ1���������ҵ������Ϣ�������re_iteCo ��ѭ����
							  {
								  break;
							  } //������������Ϣ��vctCom�е���һ��Com�������е�com�Ƚ�	 
							  
						  }//for re_iteCo ����������Ϣ�е�ÿ��COM��Ϣ
						  
					  }// if �������е�ESM ��δ�ҵ�,�����COM��Ϣ ����
					  
					 } // if��������COM��Ϣ ����
					 
					 else //else ������Ϣ��ֻ��ESM��û��COM, ֻ��ESM�Ƚ�
					 {
						 for ( re_iteEs = iteRequestMsg->vctEsm.begin(); re_iteEs != iteRequestMsg->vctEsm.end();re_iteEs++)
						 {
							 //���޺����ľ�����в���,�޺����б���ESM��COM��Ϣ
							 for (iteNoTraceUnin = stUniAll.vctNoTraceUnin.begin(); iteNoTraceUnin != stUniAll.vctNoTraceUnin.end(); iteNoTraceUnin++)
							 {  //���������޺�����Ϣʱ
								 for (iteNoTraceEs = iteNoTraceUnin->vctEsm.begin(); iteNoTraceEs != iteNoTraceUnin->vctEsm.end(); iteNoTraceEs++ )
								 {
									 double dSumCorr = 0.0;
									 Mf_SPA(iteNoTraceEs->dChongPin,re_iteEs->dChongPin,dcorrChongPin); //Ƶ��
									 VctCorr.push_back(dcorrChongPin);
									 Mf_SPA(iteNoTraceEs->dMaiKuan,re_iteEs->dMaiKuan,dcorrMaiKuan); //����
									 VctCorr.push_back(dcorrMaiKuan);
									 Mf_SPA(iteNoTraceEs->dTianXianScan,re_iteEs->dTianXianScan,dcorrTianXianScan); //����ɨ������
									 VctCorr.push_back(dcorrTianXianScan);
									 //�����ϵ����������ȡ���������ݵ�ƽ��ֵ
									 for (iteCorr = VctCorr.begin(); iteCorr != VctCorr.end(); iteCorr++)
									 {
										 dSumCorr = dSumCorr + *iteCorr;  
									 }
									 dAverCorr = dSumCorr/VctCorr.size();  //ȡ���ϵ����ƽ��ֵ
									 //�´δ�ż���ϵ��ǰ�����VctCorr����
									 VctCorr.clear();
									 //����ֵ�Ƚϣ��趨��ֵ�����ϵ������ĳ��ֵʱ����ΪESM�ǿ��Թ����ģ�
									 if (dAverCorr > 0.8)
									 {
										 //���ҵ���ESM��ͬһ�ۺ������µ�COM��Ϣ����vctBackCooperative������
										 stBackMsg.lAutonum = iteRequestMsg->lAutonum;  //��������Ϣ���ۺ����ż�¼�ڷ�����Ϣ��
										 //��ESM��Ϣ
										 for ( iteNoTraceEs1 = iteNoTraceUnin->vctEsm.begin();iteNoTraceEs1 !=iteNoTraceUnin->vctEsm.end(); iteNoTraceEs1++)
										 {
											 stBackMsg.vctEsm.push_back(*iteNoTraceEs1);
										 }
										 //��COM ��Ϣ
										 if (iteNoTraceUnin->vctComm.size() != 0)
										 {
											 for (iteNoTraceCo = iteNoTraceUnin->vctComm.begin();iteNoTraceCo !=iteNoTraceUnin->vctComm.end(); iteNoTraceCo++)
											 {
												 stBackMsg.vctComm.push_back(*iteNoTraceCo);
											 }
										 }
										 stBackMsg.BackTrackN = 0;  //������������
										 stBackMsg.BackESMN = stBackMsg.vctEsm.size();
										 stBackMsg.BackCOMN = stBackMsg.vctComm.size();
										 //�����ҵ�����Ϣ����vctBackCooperative������
										 vctBackCooperative.push_back(stBackMsg);
										 iteRequestMsg->nCorrFlag = 1; // ֱ���ҵ���������Ϣ���������Ϣ,����־��Ϣ��Ϊ1����һֱ�Ҳ������־ʼ��Ϊ0��
										 break;
									 } //if AverCorr > 0.8 ����
									 // else { nosearchFlag = 2;}
								 }// for iteNoTraceEs	
								 if (iteRequestMsg->nCorrFlag == 1) //��־λ1���������ҵ������Ϣ�������iteNoTraceUnin ��ѭ����
								 {
									 break;
								 }
								 // ��ESM ��û�ҵ� ������iteNoTraceUnin��ѭ�����Ƚ���һ���ṹ���еĶ���ESM��Ϣ
								 
							 }//for iteNoTraceUnin
						 }// for  re_iteEs
						 
					 } //else ������Ϣ��ֻ��ESM��û��COM ����
					 
				 }//if������Ϣ����ESM��Ϣ
				 
				 //һ��<2>b   	
				 else // else ������Ϣ��û��ESM , ����COM ������COM �Ƚ�
				 {   
					 for ( re_iteCo = iteRequestMsg->vctComm.begin(); re_iteCo != iteRequestMsg->vctComm.end();re_iteCo++)
					 {
						 //���޺����ľ�����в���,�޺����б���ESM��COM��Ϣ
						 for (iteNoTraceUnin = stUniAll.vctNoTraceUnin.begin(); iteNoTraceUnin != stUniAll.vctNoTraceUnin.end(); iteNoTraceUnin++)
						 {  //���������޺�����Ϣʱ
							 for (iteNoTraceCo = iteNoTraceUnin->vctComm.begin(); iteNoTraceCo != iteNoTraceUnin->vctComm.end(); iteNoTraceCo++ )
							 {
								 double dSumCorr = 0.0;
								 Mf_SPA(iteCo->dComZaiPin,re_iteCo->dComZaiPin,dcorrComZaiPin); //��Ƶ
								 VctCorr.push_back(dcorrComZaiPin);
								 Mf_SPA(iteCo->dPulseExtent,re_iteCo->dPulseExtent,dcorrdPulseExtent); //�������
								 VctCorr.push_back(dcorrdPulseExtent);
								 //0909�޸�:����COM�ļ��Է�������:  �������Ƶ����	 
								 Mf_SPA(iteCo->dComBand,re_iteCo->dComBand,dcorrBand);//����
								 VctCorr.push_back(dcorrBand);
								 Mf_SPA(iteCo->dComJPN,re_iteCo->dComJPN,dcorrJPN);//��Ƶ����
								 VctCorr.push_back(dcorrJPN);
								 
								 //�����ϵ����������ȡ���������ݵ�ƽ��ֵ
								 for (iteCorr = VctCorr.begin(); iteCorr != VctCorr.end(); iteCorr++)
								 {
									 dSumCorr = dSumCorr + *iteCorr;  
								 }
								 dAverCorr = dSumCorr/VctCorr.size();  //ȡ���ϵ����ƽ��ֵ
								 //�´δ�ż���ϵ��ǰ�����VctCorr����
								 VctCorr.clear();
								 //����ֵ�Ƚϣ��趨��ֵ�����ϵ������ĳ��ֵʱ����ΪESM�ǿ��Թ����ģ�
								 if (dAverCorr > 0.8)
								 {
									 //���ҵ���ESM��ͬһ�ۺ������µ�COM��Ϣ����vctBackCooperative������
									 stBackMsg.lAutonum = iteRequestMsg->lAutonum;  //��������Ϣ���ۺ����ż�¼�ڷ�����Ϣ��
									 //��ESM��Ϣ
									 for ( iteNoTraceEs = iteNoTraceUnin->vctEsm.begin();iteNoTraceEs !=iteNoTraceUnin->vctEsm.end(); iteNoTraceEs++)
									 {
										 stBackMsg .vctEsm.push_back(*iteNoTraceEs);
									 }
									 //��COM ��Ϣ
									 if (iteNoTraceUnin->vctComm.size() != 0)
									 {
										 for (iteNoTraceCo1 = iteNoTraceUnin->vctComm.begin();iteNoTraceCo1 !=iteNoTraceUnin->vctComm.end(); iteNoTraceCo1++)
										 {
											 stBackMsg.vctComm.push_back(*iteNoTraceCo1);
										 }
									 }
									 stBackMsg.BackTrackN = 0;  //������������
									 stBackMsg.BackESMN = stBackMsg.vctEsm.size();
									 stBackMsg.BackCOMN = stBackMsg.vctComm.size();
									 //�����ҵ�����Ϣ����vctBackCooperative������
									 vctBackCooperative.push_back(stBackMsg);
									 iteRequestMsg->nCorrFlag = 1; // ֱ���ҵ���������Ϣ���������Ϣ,����־��Ϣ��Ϊ1����һֱ�Ҳ������־ʼ��Ϊ0��
									 break;
								 } //if AverCorr > 0.8 ����
							 }// for iteNoTraceEs	
							 if (iteRequestMsg->nCorrFlag == 1) //��־λ1���������ҵ������Ϣ�������iteNoTraceUnin ��ѭ����
							 {
								 break;
							 }
							 // ��COM ��û�ҵ� ������iteNoTraceUnin��ѭ�����Ƚ���һ���ṹ���еĶ���com��Ϣ
							 
						 }//for iteNoTraceUnin
						 
						 if (iteRequestMsg->nCorrFlag == 1) //��־λ1���������ҵ������Ϣ�������re_iteCo ��ѭ����
						 {
							 break;
						 } //������������Ϣ��vctCom�е���һ��Com�������е�com�Ƚ�	 
						 
					 }//for re_iteCo ����������Ϣ�е�ÿ��COM��Ϣ
					 
				 }// else ������Ϣ����ESM��Ϣ�������COM��Ϣ���ң���Ϊ������Ϣʱ�Ѿ�������ģ������ۺ����Ŵ���8000�ģ����к�����Ϣ������ESM����Com�е�һ����Ϣ��
				 
		  }//if �к����������δ�ҵ������޺���������в��� (iteRequestMsg->nCorrFlag == 0 )
		  
		  //һ��<3>
		  
		  if ( iteRequestMsg->nCorrFlag == 0)   //if �޺����������δ�ҵ���������δ���������в���
		  {   
			  //һ��<3>a.  //����stUniAll.vctSingleTrace ��ŵ�һ����������
			  for (iteTra = stUniAll.vctSingleTrace.begin(); iteTra != stUniAll.vctSingleTrace.end(); iteTra++)
			  {   double SumCorr = 0.0;
			  Get_Coordinate_Conversion_Module(iteTra->dRange,iteTra->dAzimuth,iteTra->dElevationAngle,
				  iteRequestMsg->stTrace.dRange,iteRequestMsg->stTrace.dAzimuth,iteRequestMsg->stTrace.dElevationAngle,
				  stSelfPosi.dLati,stSelfPosi.dLonti,stSelfPosi.dHeight,
				  iteRequestMsg->stReqShipPosi.dLati,iteRequestMsg->stReqShipPosi.dLonti,iteRequestMsg->stReqShipPosi.dHeight,
				  Xt, Yt, Zt, Rdt, Azt, Ezt, dSumCorr_xyz);
			  // 				  VctCorr.push_back(dSumCorr_xyz); 
			  // 				  //�Ժ����ṹ���еĲ�����Ϣ���м��Է���,���� Vx,Vy,Vz(Ŀ�����ڽ�������ϵ�¸����귽���ϵľ����ٶ���Ҫת������������ϵ�²�������????????)
			  // 				  Mf_SPA(iteTra->dRange,Rdt,dcorrRd);
			  // 				  VctCorr.push_back(dcorrRd);
			  // 				  Mf_SPA(iteTra->dAzimuth,Azt,dcorrAz);
			  // 				  VctCorr.push_back(dcorrAz);
			  // 				  Mf_SPA(iteTra->dElevationAngle,Ezt,dcorrEz); 
			  // 				  VctCorr.push_back(dcorrEz);
			  //�����������µľ����ٶ�Vx,Vy,Vzδת����ֱ�������Է�������
			  Mf_SPA(iteTra->dTSpeedX,iteRequestMsg->stTrace.dTSpeedX,dcorrVx);
			  VctCorr.push_back(dcorrVx);
			  Mf_SPA(iteTra->dTSpeedY,iteRequestMsg->stTrace.dTSpeedY,dcorrVy);
			  VctCorr.push_back(dcorrVy);
			  Mf_SPA(iteTra->dTSpeedZ,iteRequestMsg->stTrace.dTSpeedZ,dcorrVz);
			  VctCorr.push_back(dcorrVz);
			  //�����ϵ����������ȡ���������ݵ�ƽ��ֵ
			  for (iteCorr = VctCorr.begin(); iteCorr != VctCorr.end(); iteCorr++)
			  {
				  SumCorr = SumCorr + *iteCorr;  
			  }
			  dAverCorr = SumCorr/VctCorr.size();  //ȡ���ϵ����ƽ��ֵ
			  //�´δ�ż���ϵ��ǰ�����VctCorr����
			  VctCorr.clear();
			  //����ֵ�Ƚϣ�����趨��ֵ�����ϵ������ĳ��ֵʱ����Ϊ�����ǿ��Թ�����?????????????????????��
			  if (dAverCorr > 0.8) //0.8Ϊ��ֵ������ʱ�ɵ���
			  {   //������Ϣ���Թ���������Ϣ����vctBackCooperative������Ϣ�����У�
				  //��ͬһ�������£�����ͬ��λ�£���һ��������Ϣ������N��ESM��Com��Ϣ����vctBackCooperative��
				  //δ���������ۺ�����
				  memcpy(&stBackMsg.stBackShipPosi,&stSelfPosi,sizeof(stBackMsg.stBackShipPosi));  //memcpy(&A,&B,sizeof(A)); �ѽṹ��B���ṹ��A
				  //�溽����Ϣ
				  memcpy(&stBackMsg.stTrace,&(*iteTra),sizeof(stBackMsg.stTrace));	
				  stBackMsg.BackTrackN = 1;
				  //�����ҵ�����Ϣ����vctBackCooperative������
				  vctBackCooperative.push_back(stBackMsg);
				  
				  iteRequestMsg->nCorrFlag = 1;
				  break;//�ҵ�������ѭ�� 
				  //���ˣ���δ����ĺ�������ȡ��������Ϣ������vctBackCooperative������ 
			  }//0.8Ϊ��ֵ������ʱ�ɵ���
			  }//for ����stUniAll.vctSingleTrace ��ŵ�һ���������� ,����stUniAll.vctSingleTrace
			  
			  //һ��<3>b.   //����stUniAll.vctSingleEsm ��ŵ�һESM������
			  if (iteRequestMsg->vctEsm.size() !=0)   //if������Ϣ����ESM��Ϣ
			  {
				  //����ÿ��������Ϣ�е�vctEsm��ÿ����Ϣ
				  for ( re_iteEs = iteRequestMsg->vctEsm.begin(); re_iteEs != iteRequestMsg->vctEsm.end(); re_iteEs++)
				  {
					  //����stUniAll.vctSingleEsm ��ŵ�һ����������
					  for ( iteEs =stUniAll.vctSingleEsm.begin(); iteEs != stUniAll.vctSingleEsm.end(); iteEs++ )
					  {   double dSumCorr = 0.0;
					  Mf_SPA(iteEs->dChongPin,re_iteEs->dChongPin,dcorrChongPin); //Ƶ��
					  VctCorr.push_back(dcorrChongPin);
					  Mf_SPA(iteEs->dMaiKuan,re_iteEs->dMaiKuan,dcorrMaiKuan); //����
					  VctCorr.push_back(dcorrMaiKuan);
					  Mf_SPA(iteEs->dTianXianScan,re_iteEs->dTianXianScan,dcorrTianXianScan); //����ɨ������
					  VctCorr.push_back(dcorrTianXianScan);
					  //�����ϵ����������ȡ���������ݵ�ƽ��ֵ
					  for (iteCorr = VctCorr.begin(); iteCorr != VctCorr.end(); iteCorr++)
					  {
						  dSumCorr = dSumCorr + *iteCorr;  
					  }
					  dAverCorr = dSumCorr/VctCorr.size();  //ȡ���ϵ����ƽ��ֵ
					  //�´δ�ż���ϵ��ǰ�����VctCorr����
					  VctCorr.clear();
					  //����ֵ�Ƚϣ��趨��ֵ�����ϵ������ĳ��ֵʱ����ΪESM�ǿ��Թ����ģ�
					  if (dAverCorr > 0.8) 
					  { //ESM��Ϣ���Թ���������Ϣ����vctBackCooperative������Ϣ������
						  //  memcpy(&sttEsm,&iteEs,sizeof(sttEsm));	
						  stBackMsg.lAutonum = iteEs->lTargetNumber;
						  stBackMsg.vctEsm.push_back(*iteEs);
						  stBackMsg.BackESMN = 1;
						  vctBackCooperative.push_back(stBackMsg);
						  iteRequestMsg->nCorrFlag = 1;
						  break; //�ҵ�������ѭ��
					  }//if
					  
					  }//for  ����stUniAll.vctSingleEsm ��ŵ�һ����������
					  if (iteRequestMsg->nCorrFlag == 1) //��־λ1���������ҵ������Ϣ�������re_iteEs��ѭ����
					  {
						  break;
					  }
				  } //for  ����ÿ��������Ϣ�е�vctEsm��ÿ����Ϣ 
				  
			  } //if������Ϣ����ESM��Ϣ
			  
			  //һ��<3>c.	//����stUniAll.vctSingleCom ��ŵ�һCOM������	
			  if (iteRequestMsg->vctComm.size() !=0)   //if������Ϣ����COM��Ϣ
			  {
				  //����ÿ��������Ϣ�е�vctCom��ÿ����Ϣ
				  for ( re_iteCo = iteRequestMsg->vctComm.begin(); re_iteCo != iteRequestMsg->vctComm.end(); re_iteEs++)
				  {
					  //����stUniAll.vctSingleEsm ��ŵ�һ����������
					  for ( iteCo =stUniAll.vctSingleCom.begin(); iteCo != stUniAll.vctSingleCom.end(); iteCo++ )
					  {
						  double SumCorr = 0.0;
						  Mf_SPA(iteCo->dComZaiPin,re_iteCo->dComZaiPin,dcorrComZaiPin); //��Ƶ
						  VctCorr.push_back(dcorrComZaiPin);
						  Mf_SPA(iteCo->dPulseExtent,re_iteCo->dPulseExtent,dcorrdPulseExtent); //�������
						  VctCorr.push_back(dcorrdPulseExtent);
						  //0909�޸�:����COM�ļ��Է�������:  �������Ƶ����	 
						  Mf_SPA(iteCo->dComBand,re_iteCo->dComBand,dcorrBand);//����
						  VctCorr.push_back(dcorrBand);
						  Mf_SPA(iteCo->dComJPN,re_iteCo->dComJPN,dcorrJPN);//��Ƶ����
						  VctCorr.push_back(dcorrJPN);
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
						  { //ESM��Ϣ���Թ���������Ϣ����vctBackCooperative������Ϣ������
							  // memcpy(&sttCom,&iteCo,sizeof(sttCom));	
							  stBackMsg.lAutonum = iteCo->lTargetNumber;
							  stBackMsg.vctComm.push_back(*iteCo);
							  stBackMsg.BackCOMN =1;
							  vctBackCooperative.push_back(stBackMsg);
							  iteRequestMsg->nCorrFlag = 1;
							  break; //�ҵ�������ѭ��
						  }//if
					  }// for iteCo	
					  if (iteRequestMsg->nCorrFlag == 1) //��־λ1���������ҵ������Ϣ�������re_iteEs��ѭ����
					  {
						  break;
					  }
				  }//for re_iteCo ����ÿ��������Ϣ�е�vctCom��ÿ����Ϣ
			  }//if ������Ϣ����ESM��Ϣ
		  }//if ���� �޺����������δ�ҵ���������δ���������в���
		  
		  
}//  void ReqUnin_COOP_Find_Information_To_MainShip()����


/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/

//������Ϣ���޺����ľ�����Ϣ���ۺ����Ŵ���7000��8000֮��
void ReqNoTraceUnin_COOP_Find_Information_To_MainShip(SHIP_POSITION& stSelfPosi,UNI_All_NUM& stUniAll,VCT_Request_Cooperative_Msg::iterator& iteRequestMsg,/*VCT_Request_Cooperative_Msg& vctRequestCooperative,*/ VCT_BACK_Cooperative_Msg& vctBackCooperative)
{
	double Xt = 0.0;        //�������ʱ����Ҫ������IF ��forѭ���У����嵽�ⲿ����Ϊȫ�ֱ���
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
    double dAverCorr = 0.0; //��������Ϣ�����Է�����ȡƽ��ֵ������ϵ��
	//  TRACKSTATUS_MARK sttTrack;
	ESMSTATUS_MARK sttEsm;
	COMSTATUS_MARK sttCom;
    typedef vector<double> VCT_CORR;
	VCT_CORR VctCorr;      // ��Ź���ϵ��������
	VCT_CORR::iterator iteCorr;
	//  ������յĵ�����
	//  ��vctRequestCooperative�����У��������������ÿ�ഫ������Ϣ���ĵ�����
	//	VCT_TRACE_MSG::iterator iteTrace; //��Ϊÿ���ṹ�������к�����ֻ����һ��������ֱ���ú�����Ϣ�Ľṹ��
	VCT_ESM_MSG::iterator iteEsm;                
	VCT_COMM_MSG::iterator iteCom;
	//�к���
	VCT_UNINUM_MSG::iterator iteUnin;
	//�к��� ����������Esm,Com���ĵ�����
	VCT_ESM_MSG::iterator iteUninEs;
	VCT_ESM_MSG::iterator iteUninEs1;
	VCT_COMM_MSG::iterator iteUninCo;
	VCT_COMM_MSG::iterator iteUninCo1;
	
	//�޺���
	VCT_UNINOTRACE_MSG::iterator iteNoTraceUnin;
	//�޺��� ����������ESM��com���ĵ�����
	VCT_ESM_MSG::iterator iteNoTraceEs;
	VCT_ESM_MSG::iterator iteNoTraceEs1;
	VCT_COMM_MSG::iterator iteNoTraceCo;
//	VCT_COMM_MSG::iterator iteNoTraceCo1;
	
	//δ���� �������������ÿ�ഫ������Ϣ���ĵ�����
	//	VCT_TRACE_MSG::iterator iteTra;
	VCT_ESM_MSG::iterator iteEs;
	VCT_COMM_MSG::iterator iteCo;
	
	VCT_BACK_Cooperative_Msg::iterator iteBackMsg;
	BACK_Cooperative_Msg stBackMsg;
	//	VCT_Request_Cooperative_Msg::iterator iteRequestMsg;
	//������Ϣ�� ESM��COM���������ÿ�ഫ������Ϣ���ĵ�����
	VCT_ESM_MSG::iterator re_iteEs;
	VCT_COMM_MSG::iterator re_iteCo;
	// 
	
	//��� vctBackCooperative
	for (iteBackMsg = vctBackCooperative.begin(); iteBackMsg != vctBackCooperative.end(); iteBackMsg++)
	{	
		//��� vctBackCooperative
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
	{     //���к����ľ�����в��� 
		for ( iteUnin = stUniAll.vctUnin.begin(); iteUnin != stUniAll.vctUnin.end(); iteUnin++)
		{ 
			//�жϾ�����Ϣ��iteUnin���Ƿ���ESM��Ϣ
			if (iteUnin->vctEsm.size() !=0 ) //������Ϣ������ESM��Ϣ
			{
				for (iteUninEs = iteUnin->vctEsm.begin(); iteUninEs != iteUnin->vctEsm.end(); iteUninEs++)
				{
					double SumCorr = 0.0;
					Mf_SPA(iteUninEs->dChongPin,re_iteEs->dChongPin,dcorrChongPin); //Ƶ��
					VctCorr.push_back(dcorrChongPin);
					Mf_SPA(iteUninEs->dMaiKuan,re_iteEs->dMaiKuan,dcorrMaiKuan); //����
					VctCorr.push_back(dcorrMaiKuan);
					Mf_SPA(iteUninEs->dTianXianScan,re_iteEs->dTianXianScan,dcorrTianXianScan); //����ɨ������
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
						//���ҵ���ESM��ͬһ�ۺ������µ�COM��Ϣ����vctBackCooperative������
						stBackMsg.lAutonum = iteRequestMsg->lAutonum;  //��������Ϣ���ۺ����ż�¼�ڷ�����Ϣ��
						//��ESM��Ϣ
						for ( iteUninEs1 = iteUnin->vctEsm.begin();iteUninEs1 !=iteUnin->vctEsm.end(); iteUninEs1++)
						{
							stBackMsg.vctEsm.push_back(*iteUninEs1);
						}
						//�汻����Эͬ���ľ�γ��
						memcpy(&stBackMsg.stBackShipPosi,&stSelfPosi,sizeof(stBackMsg.stBackShipPosi));  //memcpy(&A,&B,sizeof(A)); �ѽṹ��B���ṹ��A
						//�溽����Ϣ
						memcpy(&stBackMsg.stTrace,&iteUnin->structTrace,sizeof(stBackMsg.stTrace));		
						
						//��COM ��Ϣ,com��һ������
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
					} //if AverCorr > 0.8 ����							
				}  //for  iteUninEs	
			}//if  iteUnin->vctEsm.size() !=0 ������Ϣ������ESM��Ϣ
			if (iteRequestMsg->nCorrFlag == 1) //��־λ1���������ҵ������Ϣ�������iteUnin��ѭ����
			{
				break;
			}
		} //for  iteUnin
		if (iteRequestMsg->nCorrFlag == 1) //��־λ1���������ҵ������Ϣ�������re_iteEs ��ѭ����
		{
			break;
		} //������������Ϣ��vctEsm�е���һ��Esm�������е�Esm�Ƚ�
	}//for  re_iteEs
	
	if (iteRequestMsg->nCorrFlag == 0) //������ϢESM ���о�����е���ESM ��Ϣ�Ľṹ����δ�ҵ������Ϣ����ô�ھ�����нṹ���е�COM �бȽϲ���
	{
		if (  iteRequestMsg->vctComm.size() !=0 )
		{
			for ( re_iteCo = iteRequestMsg->vctComm.begin(); re_iteCo != iteRequestMsg->vctComm.end(); re_iteCo++) 
			{     //���к����ľ�����в��� 
				for ( iteUnin = stUniAll.vctUnin.begin(); iteUnin != stUniAll.vctUnin.end(); iteUnin++)
				{ 
					//�жϾ�����Ϣ��iteUnin���Ƿ���Com��Ϣ
					if (iteUnin->vctComm.size() !=0 ) //������Ϣ������COM��Ϣ
					{
						for (iteUninCo = iteUnin->vctComm.begin(); iteUninCo != iteUnin->vctComm.end(); iteUninCo++)
						{
							double SumCorr = 0.0;
							Mf_SPA(iteUninCo->dComZaiPin,re_iteCo->dComZaiPin,dcorrComZaiPin); //��Ƶ
							VctCorr.push_back(dcorrComZaiPin);
							Mf_SPA(iteUninCo->dPulseExtent,re_iteCo->dPulseExtent,dcorrdPulseExtent); //�������
							VctCorr.push_back(dcorrdPulseExtent);
							//0909�޸�:����COM�ļ��Է�������:  �������Ƶ����	 
							Mf_SPA(iteUninCo->dComBand,re_iteCo->dComBand,dcorrBand);//����
							VctCorr.push_back(dcorrBand);
							Mf_SPA(iteUninCo->dComJPN,re_iteCo->dComJPN,dcorrJPN);//��Ƶ����
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
							{ //COM��Ϣ���Թ���������Ϣ����vctBackCooperative������Ϣ������
								stBackMsg.lAutonum = iteRequestMsg->lAutonum;  //��������Ϣ���ۺ����ż�¼�ڷ�����Ϣ��
								//��COM
								for (iteUninCo1 = iteUnin->vctComm.begin();iteUninCo1 !=iteUnin->vctComm.end(); iteUninCo1++)
								{
									stBackMsg.vctComm.push_back(*iteUninCo1);
								}
								//��ESM
								if (iteUnin->vctEsm.size() != 0 )
								{
									for ( iteUninEs = iteUnin->vctEsm.begin();iteUninEs !=iteUnin->vctEsm.end(); iteUninEs++)
									{
										stBackMsg.vctEsm.push_back(*iteUninEs);
									}
								}
								//�汻����Эͬ���ľ�γ��
								memcpy(&stBackMsg.stBackShipPosi,&stSelfPosi,sizeof(stBackMsg.stBackShipPosi));  //memcpy(&A,&B,sizeof(A)); �ѽṹ��B���ṹ��A
								//�溽����Ϣ
								memcpy(&stBackMsg.stTrace,&iteUnin->structTrace,sizeof(stBackMsg.stTrace));	
								//	memcpy(&sttCom,&iteCo,sizeof(sttCom));	
								//									stBackMsg.lAutonum = iteCo->lTargetNumber;
								//									stBackMsg.vctComm.push_back(sttCom);
								
								stBackMsg.BackTrackN = 1;
								stBackMsg.BackESMN = stBackMsg.vctEsm.size();
								stBackMsg.BackCOMN = stBackMsg.vctComm.size();
								vctBackCooperative.push_back(stBackMsg);
								iteRequestMsg->nCorrFlag = 1;
								break; //�ҵ�������ѭ��
							}//if
						}//for iteUninCo
					}// if �������iteUnin������Ľṹ������COM��Ϣ
					
					if (iteRequestMsg->nCorrFlag == 1) //��־λ1���������ҵ������Ϣ�������iteUnin��ѭ����
					{
						break;
					}
				}// for iteUnin
				if (iteRequestMsg->nCorrFlag == 1) //��־λ1���������ҵ������Ϣ�������re_iteCo ��ѭ����
				{
					break;
				} //������������Ϣ��vctCom�е���һ��Com�������е�Com�Ƚ�
			}//for re_iteCo
		 
		}//if ������Ϣ��COM��Ϣ

	}// if �ھ�����еĽṹ������COM��Ϣ
	
	
	
	//����<2>
	if ( iteRequestMsg->nCorrFlag == 0 )
	{   //���޺����ľ�����в���	
		for ( re_iteEs = iteRequestMsg->vctEsm.begin(); re_iteEs != iteRequestMsg->vctEsm.end(); re_iteEs++) 
		{
			for (iteNoTraceUnin = stUniAll.vctNoTraceUnin.begin(); iteNoTraceUnin != stUniAll.vctNoTraceUnin.end(); iteNoTraceUnin++)
			{
				for (iteNoTraceEs = iteNoTraceUnin->vctEsm.begin(); iteNoTraceEs != iteNoTraceUnin->vctEsm.end(); iteNoTraceEs++)	 
				{     
					double SumCorr = 0.0;
				    Mf_SPA(iteNoTraceEs->dChongPin,re_iteEs->dChongPin,dcorrChongPin); //Ƶ��
					VctCorr.push_back(dcorrChongPin);
					Mf_SPA(iteNoTraceEs->dMaiKuan,re_iteEs->dMaiKuan,dcorrMaiKuan); //����
					VctCorr.push_back(dcorrMaiKuan);
					Mf_SPA(iteNoTraceEs->dTianXianScan,re_iteEs->dTianXianScan,dcorrTianXianScan); //����ɨ������
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
						//���ҵ���ESM��ͬһ�ۺ������µ�COM��Ϣ����vctBackCooperative������
						stBackMsg.lAutonum = iteRequestMsg->lAutonum;  //��������Ϣ���ۺ����ż�¼�ڷ�����Ϣ��
						
						//��ESM��Ϣ
						for ( iteNoTraceEs1 = iteNoTraceUnin->vctEsm.begin();iteNoTraceEs1 !=iteNoTraceUnin->vctEsm.end(); iteNoTraceEs1++)
						{
							stBackMsg.vctEsm.push_back(*iteNoTraceEs1);
						}
						
						//��COM ��Ϣ
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
					} //if AverCorr > 0.8 ����
				}// for  iteNoTraceEs 
				if (iteRequestMsg->nCorrFlag == 1) //��־λ1���������ҵ������Ϣ�������iteNoTraceUnin��ѭ����
				{
					break;
				}  
			}// for iteNoTraceUnin
			if (iteRequestMsg->nCorrFlag == 1) //��־λ1���������ҵ������Ϣ�������re_iteEs ��ѭ����
			{
				break;
			} //������������Ϣ��vctEsm�е���һ��Esm�������е�Esm�Ƚ�
			
		} // for re_iteEs
		
	}// if iteRequestMsg->nCorrFlag == 0 
	
	if (iteRequestMsg->nCorrFlag == 0) //������ϢESM ���޺����ľ������ESM ��Ϣ�Ľṹ����δ�ҵ������Ϣ����ô���޺����ľ�����нṹ���е�COM �бȽϲ���
	{ 
		if (  iteRequestMsg->vctComm.size() != 0 )
		{
			for ( re_iteCo = iteRequestMsg->vctComm.begin(); re_iteCo != iteRequestMsg->vctComm.end(); re_iteCo++) 
			{     //���޺����ľ�����в��� 
				for ( iteUnin = stUniAll.vctUnin.begin(); iteUnin != stUniAll.vctUnin.end(); iteUnin++)
				{ 
					if ( iteUnin->vctComm.size() != 0)
					{
						for (iteUninCo = iteUnin->vctComm.begin(); iteUninCo != iteUnin->vctComm.end(); iteUninCo++)
						{
							double SumCorr = 0.0;
							Mf_SPA(iteUninCo->dComZaiPin,re_iteCo->dComZaiPin,dcorrComZaiPin); //��Ƶ
							VctCorr.push_back(dcorrComZaiPin);
							Mf_SPA(iteUninCo->dPulseExtent,re_iteCo->dPulseExtent,dcorrdPulseExtent); //�������
							VctCorr.push_back(dcorrdPulseExtent);
							//0909�޸�:����COM�ļ��Է�������:  �������Ƶ����	 
							Mf_SPA(iteUninCo->dComBand,re_iteCo->dComBand,dcorrBand);//����
							VctCorr.push_back(dcorrBand);
							Mf_SPA(iteUninCo->dComJPN,re_iteCo->dComJPN,dcorrJPN);//��Ƶ����
							VctCorr.push_back(dcorrJPN);
							//�����ϵ����������ȡ���������ݵ�ƽ��ֵ
							for (iteCorr = VctCorr.begin(); iteCorr != VctCorr.end(); iteCorr++)
							{
								SumCorr = SumCorr + *iteCorr;  
							}
							dAverCorr = SumCorr/VctCorr.size();  //ȡ���ϵ����ƽ��ֵ
							//�´δ�ż���ϵ��ǰ�����VctCorr����
							VctCorr.clear();
							//����ֵ�Ƚϣ��趨��ֵ�����ϵ������ĳ��ֵʱ����ΪCom�ǿ��Թ����ģ�
							if (dAverCorr > 0.8) 
							{ //Com��Ϣ���Թ���������Ϣ����vctBackCooperative������Ϣ������
								//										   memcpy(&sttCom,&iteCo,sizeof(sttCom));	
								//										   stBackMsg.lAutonum = iteCo->lTargetNumber;
								//										   stBackMsg.vctComm.push_back(sttCom);
								//���ҵ���ESM��ͬһ�ۺ������µ�COM��Ϣ����vctBackCooperative������
								stBackMsg.lAutonum = iteRequestMsg->lAutonum;  //��������Ϣ���ۺ����ż�¼�ڷ�����Ϣ��
								//��ESM��Ϣ
								for ( iteNoTraceEs = iteNoTraceUnin->vctEsm.begin();iteNoTraceEs !=iteNoTraceUnin->vctEsm.end(); iteNoTraceEs++)
								{
									stBackMsg.vctEsm.push_back(*iteNoTraceEs);
								}
								//��COM ��Ϣ
								for (iteNoTraceCo = iteNoTraceUnin->vctComm.begin();iteNoTraceCo !=iteNoTraceUnin->vctComm.end(); iteNoTraceCo++)
								{
									stBackMsg.vctComm.push_back(*iteNoTraceCo);
								} 
								stBackMsg.BackTrackN = 0;
								stBackMsg.BackESMN = stBackMsg.vctEsm.size();
								stBackMsg.BackCOMN = stBackMsg.vctComm.size();
								vctBackCooperative.push_back(stBackMsg);
								
								iteRequestMsg->nCorrFlag = 1;
								break; //�ҵ�������ѭ��
							}//if
						}//for iteUninCo

					}// �޺���������Ϣ����Com��Ϣ

					if (iteRequestMsg->nCorrFlag == 1) //��־λ1���������ҵ������Ϣ�������iteUnin��ѭ����
					{
						break;
					}
				}// for iteUnin
				if (iteRequestMsg->nCorrFlag == 1) //��־λ1���������ҵ������Ϣ�������re_iteCo ��ѭ����
				{
					break;
				} //������������Ϣ��vctCom�е���һ��Com�������е�Com�Ƚ�
			}//for re_iteCo

		}// ������Ϣ����COM��Ϣ

	}// if �ھ�����нṹ���е�COM �бȽϲ���
	
	
	//����<3>
	if (iteRequestMsg->nCorrFlag == 0)   //if �޺����������δ�ҵ���������δ���������в���
	{   //����stUniAll.vctSingleTrace ��ŵ�һESM������
		//����<3>a. 
	    for ( re_iteEs = iteRequestMsg->vctEsm.begin(); re_iteEs != iteRequestMsg->vctEsm.end(); re_iteEs++) 
		{
		    for (iteEs = stUniAll.vctSingleEsm.begin(); iteEs != stUniAll.vctSingleEsm.end(); iteEs++)
			{
				double SumCorr = 0.0;
				Mf_SPA(iteEs->dChongPin,re_iteEs->dChongPin,dcorrChongPin); //Ƶ��
				VctCorr.push_back(dcorrChongPin);
				Mf_SPA(iteEs->dMaiKuan,re_iteEs->dMaiKuan,dcorrMaiKuan); //����
				VctCorr.push_back(dcorrMaiKuan);
				Mf_SPA(iteEs->dTianXianScan,re_iteEs->dTianXianScan,dcorrTianXianScan); //����ɨ������
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
				{ //ESM��Ϣ���Թ���������Ϣ����vctBackCooperative������Ϣ������
					memcpy(&sttEsm,&(*iteEs),sizeof(sttEsm));	
					stBackMsg.lAutonum = iteEs->lTargetNumber;
					stBackMsg.vctEsm.push_back(sttEsm);
					stBackMsg.BackESMN = 1;
					vctBackCooperative.push_back(stBackMsg);
					iteRequestMsg->nCorrFlag = 1;
					break; //�ҵ�������ѭ��
				}//if     
			}//for iteEs  
			if (iteRequestMsg->nCorrFlag == 1) //��־λ1���������ҵ������Ϣ�������re_iteCo ��ѭ����
			{
				break;
			}
		}// for re_iteEs
		
		//������Ϣ����Comm��Ϣ
		if ( iteRequestMsg->vctComm.size() != 0  )
		{
			for ( re_iteCo = iteRequestMsg->vctComm.begin(); re_iteCo != iteRequestMsg->vctComm.end(); re_iteCo++) 
			{
				for (iteCo = stUniAll.vctSingleCom.begin(); iteCo != stUniAll.vctSingleCom.end(); iteCo++)
				{
					double SumCorr = 0.0;
					Mf_SPA(iteCo->dComZaiPin,re_iteCo->dComZaiPin,dcorrComZaiPin); //��Ƶ
					VctCorr.push_back(dcorrComZaiPin);
					Mf_SPA(iteCo->dPulseExtent,re_iteCo->dPulseExtent,dcorrdPulseExtent); //�������
					VctCorr.push_back(dcorrdPulseExtent);
					//0909�޸�:����COM�ļ��Է�������:  �������Ƶ����	 
					Mf_SPA(iteCo->dComBand,re_iteCo->dComBand,dcorrBand);//����
					VctCorr.push_back(dcorrBand);
					Mf_SPA(iteCo->dComJPN,re_iteCo->dComJPN,dcorrJPN);//��Ƶ����
					VctCorr.push_back(dcorrJPN);
					//�����ϵ����������ȡ���������ݵ�ƽ��ֵ
					for (iteCorr = VctCorr.begin(); iteCorr != VctCorr.end(); iteCorr++)
					{
						SumCorr = SumCorr + *iteCorr;  
					}
					dAverCorr = SumCorr/VctCorr.size();  //ȡ���ϵ����ƽ��ֵ
					//�´δ�ż���ϵ��ǰ�����VctCorr����
					VctCorr.clear();
					//����ֵ�Ƚϣ��趨��ֵ�����ϵ������ĳ��ֵʱ����ΪCom�ǿ��Թ����ģ�
					if (dAverCorr > 0.8) 
					{ //Com��Ϣ���Թ���������Ϣ����vctBackCooperative������Ϣ������
						memcpy(&sttCom,&(*iteCo),sizeof(sttCom));	
						stBackMsg.lAutonum = iteCo->lTargetNumber;
						stBackMsg.vctComm.push_back(sttCom);
						
						stBackMsg.BackCOMN = 1;
						
						vctBackCooperative.push_back(stBackMsg);
						iteRequestMsg->nCorrFlag = 1;
						break; //�ҵ�������ѭ��
					}//if     
				}//for iteEs  
				if (iteRequestMsg->nCorrFlag == 1) //��־λ1���������ҵ������Ϣ�������re_iteCo ��ѭ����
				{
					break;
				}
			}// for re_iteCo
		}
								   
	}// if iteRequestMsg->nCorrFlag == 0
	
}//void ReqNoTraceUnin_COOP_Find_Information_To_MainShip()����

/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/

//������Ϣ��δ����ĺ�����Ϣ�����ۺ����ţ��к�����Ϣ��Ŀ�����ţ�5000��6000

void ReqSingleTrace_COOP_Find_Information_To_MainShip(SHIP_POSITION& stSelfPosi,UNI_All_NUM& stUniAll,VCT_Request_Cooperative_Msg::iterator& iteRequestMsg,/*VCT_Request_Cooperative_Msg& vctRequestCooperative,*/ VCT_BACK_Cooperative_Msg& vctBackCooperative)
{	
	double Xt = 0.0;        //�������ʱ����Ҫ������IF ��forѭ���У����嵽�ⲿ����Ϊȫ�ֱ���
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
	double dAverCorr = 0.0; //��������Ϣ�����Է�����ȡƽ��ֵ������ϵ��
	//  TRACKSTATUS_MARK sttTrack;
	//	ESMSTATUS_MARK sttEsm;
	//	COMSTATUS_MARK sttCom;
	typedef vector<double> VCT_CORR;
	VCT_CORR VctCorr;      // ��Ź���ϵ��������
	VCT_CORR::iterator iteCorr;
	//  ������յĵ�����
	//  ��vctRequestCooperative�����У��������������ÿ�ഫ������Ϣ���ĵ�����
	//	VCT_TRACE_MSG::iterator iteTrace; //��Ϊÿ���ṹ�������к�����ֻ����һ��������ֱ���ú�����Ϣ�Ľṹ��
	VCT_ESM_MSG::iterator iteEsm;                
	VCT_COMM_MSG::iterator iteCom;
	//�к���
	VCT_UNINUM_MSG::iterator iteUnin;
	//�к��� ����������Esm,Com���ĵ�����
	//	VCT_ESM_MSG::iterator iteUninEs;
	//	VCT_COMM_MSG::iterator iteUninCo;
	
	//�޺���
	//	VCT_UNINOTRACE_MSG::iterator iteNoTraceUnin;
	//�޺��� ����������ESM��com���ĵ�����
	//	VCT_ESM_MSG::iterator iteNoTraceEs;
	//	VCT_COMM_MSG::iterator iteNoTraceCo;
	
	//δ���� �������������ÿ�ഫ������Ϣ���ĵ�����
	VCT_TRACE_MSG::iterator iteTra;
	VCT_ESM_MSG::iterator iteEs;
	VCT_COMM_MSG::iterator iteCo;
	
	VCT_BACK_Cooperative_Msg::iterator iteBackMsg;
	BACK_Cooperative_Msg stBackMsg;
	//	VCT_Request_Cooperative_Msg::iterator iteRequestMsg;
	//������Ϣ�� ESM��COM���������ÿ�ഫ������Ϣ���ĵ�����
	//	VCT_ESM_MSG::iterator re_iteEs;
	//	VCT_COMM_MSG::iterator re_iteCo;
	// 

	//��� vctBackCooperative
	for (iteBackMsg = vctBackCooperative.begin(); iteBackMsg != vctBackCooperative.end(); iteBackMsg++)
	{	
		//��� vctBackCooperative
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
	//���к����ľ�����в��� 	
	for ( iteUnin = stUniAll.vctUnin.begin(); iteUnin != stUniAll.vctUnin.end(); iteUnin++)
	{     
		double SumCorr = 0.0;
		Get_Coordinate_Conversion_Module(iteUnin->structTrace.dRange,iteUnin->structTrace.dAzimuth,iteUnin->structTrace.dElevationAngle,
			iteRequestMsg->stTrace.dRange,iteRequestMsg->stTrace.dAzimuth,iteRequestMsg->stTrace.dElevationAngle,
			stSelfPosi.dLati,stSelfPosi.dLonti,stSelfPosi.dHeight,
			iteRequestMsg->stReqShipPosi.dLati,iteRequestMsg->stReqShipPosi.dLonti,iteRequestMsg->stReqShipPosi.dHeight,
			Xt, Yt, Zt, Rdt, Azt, Ezt,dSumCorr_xyz);
		// 			  VctCorr.push_back(dSumCorr_xyz); 
		// 			  //�Ժ����ṹ���еĲ�����Ϣ���м��Է���,���� Vx,Vy,Vz(Ŀ�����ڽ�������ϵ�¸����귽���ϵľ����ٶ���Ҫת������������ϵ�²�������????????)
		//            Mf_SPA(iteUnin->structTrace.dRange,Rdt,dcorrRd);
		// 			  VctCorr.push_back(dcorrRd);
		// 			  Mf_SPA(iteUnin->structTrace.dAzimuth,Azt,dcorrAz);
		// 			  VctCorr.push_back(dcorrAz);
		// 			  Mf_SPA(iteUnin->structTrace.dElevationAngle,Ezt,dcorrEz); 
		// 			  VctCorr.push_back(dcorrEz);
		//�����������µľ����ٶ�Vx,Vy,Vzδת����ֱ�������Է�������
		Mf_SPA(iteUnin->structTrace.dTSpeedX,iteRequestMsg->stTrace.dTSpeedX,dcorrVx);
		VctCorr.push_back(dcorrVx);
		Mf_SPA(iteUnin->structTrace.dTSpeedY,iteRequestMsg->stTrace.dTSpeedY,dcorrVy);
		VctCorr.push_back(dcorrVy);
		Mf_SPA(iteUnin->structTrace.dTSpeedZ,iteRequestMsg->stTrace.dTSpeedZ,dcorrVz);
		VctCorr.push_back(dcorrVz);
		//�����ϵ����������ȡ���������ݵ�ƽ��ֵ
		for (iteCorr = VctCorr.begin(); iteCorr != VctCorr.end(); iteCorr++)
		{
			SumCorr = SumCorr + *iteCorr;  
		}
		dAverCorr = SumCorr/VctCorr.size();  //ȡ���ϵ����ƽ��ֵ
		//�´δ�ż���ϵ��ǰ�����VctCorr����
		VctCorr.clear();
		if (dAverCorr > 0.8)
		{   //������Ϣ���Թ���������Ϣ����vctBackCooperative������Ϣ�����У�
			//��ͬһ�������£�����ͬ��λ�£���һ��������Ϣ������N��ESM��Com��Ϣ����vctBackCooperative��
			stBackMsg.lAutonum = iteRequestMsg->lAutonum; //��������Ϣ���ۺ����Ÿ�ֵ��������Ϣ��
			memcpy(&stBackMsg.stBackShipPosi,&stSelfPosi,sizeof(stBackMsg.stBackShipPosi));  //memcpy(&A,&B,sizeof(A)); �ѽṹ��B���ṹ��A
			//�溽����Ϣ
			memcpy(&stBackMsg.stTrace,&iteUnin->structTrace,sizeof(stBackMsg.stTrace));			
			//��ESM��Ϣ
			if (iteUnin->vctEsm.size() !=0)
			{
				for (iteEs = iteUnin->vctEsm.begin(); iteEs != iteUnin->vctEsm.end(); iteEs++)
				{
					stBackMsg.vctEsm.push_back(*iteEs);
				}
			}
			//��COM ��Ϣ
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
			
			//�����ҵ�����Ϣ����vctBackCooperative������
			vctBackCooperative.push_back(stBackMsg);
			iteRequestMsg->nCorrFlag = 1;
			break;
		}// if(AverCorr > 0.8)
		
	} //for iteUnin  �����к����ľ���� ����

	if (iteRequestMsg->nCorrFlag == 0) //���к����ľ������δ�ҵ�������SingleTrack�в��ң�����δ����������в��ң�
	{  // ��δ����ĺ����в��ң�SingleTrack��
		for ( iteTra = stUniAll.vctSingleTrace.begin(); iteTra != stUniAll.vctSingleTrace.end(); iteTra++)
		{ 
			double dSumCorr = 0.0;
			Get_Coordinate_Conversion_Module(iteTra->dRange,iteTra->dAzimuth,iteTra->dElevationAngle,
				iteRequestMsg->stTrace.dRange,iteRequestMsg->stTrace.dAzimuth,iteRequestMsg->stTrace.dElevationAngle,
				stSelfPosi.dLati,stSelfPosi.dLonti,stSelfPosi.dHeight,
				iteRequestMsg->stReqShipPosi.dLati,iteRequestMsg->stReqShipPosi.dLonti,iteRequestMsg->stReqShipPosi.dHeight,
				Xt, Yt, Zt, Rdt, Azt, Ezt, dSumCorr_xyz);
			// 				  VctCorr.push_back(dSumCorr_xyz); 
			// 				  //�Ժ����ṹ���еĲ�����Ϣ���м��Է���,���� Vx,Vy,Vz(Ŀ�����ڽ�������ϵ�¸����귽���ϵľ����ٶ���Ҫת������������ϵ�²�������????????)
			// 				  Mf_SPA(iteTra->dRange,Rdt,dcorrRd);
			// 				  VctCorr.push_back(dcorrRd);
			// 				  Mf_SPA(iteTra->dAzimuth,Azt,dcorrAz);
			// 				  VctCorr.push_back(dcorrAz);
			// 				  Mf_SPA(iteTra->dElevationAngle,Ezt,dcorrEz); 
			// 				  VctCorr.push_back(dcorrEz);
			//�����������µľ����ٶ�Vx,Vy,Vzδת����ֱ�������Է�������
			Mf_SPA(iteTra->dTSpeedX,iteRequestMsg->stTrace.dTSpeedX,dcorrVx);
			VctCorr.push_back(dcorrVx);
			Mf_SPA(iteTra->dTSpeedY,iteRequestMsg->stTrace.dTSpeedY,dcorrVy);
			VctCorr.push_back(dcorrVy);
			Mf_SPA(iteTra->dTSpeedZ,iteRequestMsg->stTrace.dTSpeedZ,dcorrVz);
			VctCorr.push_back(dcorrVz);
			//�����ϵ����������ȡ���������ݵ�ƽ��ֵ
			for (iteCorr = VctCorr.begin(); iteCorr != VctCorr.end(); iteCorr++)
			{
				dSumCorr = dSumCorr + *iteCorr;  
			}
			dAverCorr = dSumCorr/VctCorr.size();  //ȡ���ϵ����ƽ��ֵ
			//�´δ�ż���ϵ��ǰ�����VctCorr����
			VctCorr.clear();
			//����ֵ�Ƚϣ�����趨��ֵ�����ϵ������ĳ��ֵʱ����Ϊ�����ǿ��Թ�����?????????????????????��
			if (dAverCorr > 0.8) //0.8Ϊ��ֵ������ʱ�ɵ���
			{   //������Ϣ���Թ���������Ϣ����vctBackCooperative������Ϣ�����У�
				//��ͬһ�������£�����ͬ��λ�£���һ��������Ϣ������N��ESM��Com��Ϣ����vctBackCooperative��
				//δ���������ۺ�����
				stBackMsg.lAutonum = iteRequestMsg->stTrace.lAutonum; //���޾���ĺ���������Ϣ�е�Ŀ�����Ÿ�������Ϣ
				memcpy(&stBackMsg.stBackShipPosi,&stSelfPosi,sizeof(stBackMsg.stBackShipPosi));  //memcpy(&A,&B,sizeof(A)); �ѽṹ��B���ṹ��A
				//�溽����Ϣ
				memcpy(&stBackMsg.stTrace,&iteTra,sizeof(stBackMsg.stTrace));	
				stBackMsg.BackTrackN = 1;
				
				//�����ҵ�����Ϣ����vctBackCooperative������
				vctBackCooperative.push_back(stBackMsg);
				iteRequestMsg->nCorrFlag = 1;
				break;//�ҵ�������ѭ�� 
				//���ˣ���δ����ĺ�������ȡ��������Ϣ������vctBackCooperative������ 
			}// if (AverCorr >0.8 )
			
		}// for  iteTra����Ϊ����ĺ����в���
		
	}// if ( iteRequestMsg->nCorrFlag == 0)
	
}//void ReqSingleTrace_COOP_Find_Information_To_MainShip()����



/*******************************************************************************/
/*******      Ŀ���ڽ��۲�ľ��ࡢ��λ������ת������ͬһ����ϵ��ģ��     *******/
//*******     ���룺                                                     *******/
//*******           Ŀ������ڽ�2�ľ��ࡢ��λ������(Rd2,Az2,Ez2)         *******/
/*******            �����������꣨La1,Ba1,Ha1��                         ********/
/*******            �ڽ��������꣨La2,Ba2,Ha2��                         ********/
//*******     �����                                                     *******/
/********           Ŀ����ڽ�ת�������Ĵ���״����ϵ�е�����Xt,Yt,Zt   *******/
/*******************************************************************************/

//���������޺�����Ϣʱ
void Get_NO_SelfTrack_Coordinate_Conversion_Module(double Rd2,double Az2,double Ez2,double La1,double Ba1,double Ha1,
												   double La2,double Ba2,double Ha2,double& Xt,double& Yt,double& Zt)
{
	double x2,y2,z2;
	
	double xg,yg,zg;      //�ڽ��ڱ����е�����
	double Rd,Az,Ez;
	double xxd,yyd,zzd;
	
	double dertH;               //�Ÿ߶Ȳ���
	double G1;                  //�ڽ��뱾��֮��ĵ������
	double ae;
	
	//Ŀ�����ڽ��Ĵ���״�����ϵ�е�ֱ������
	x2=Rd2*cos(Ez2)*sin(Az2);
	y2=Rd2*cos(Ez2)*cos(Az2);
	z2=Rd2*sin(Ez2);
	
	//�ڽ�����ڱ����ľ��ࡢ��λ�͸���
	Object_Radar_Transform(La2,Ba2,Ha2,La1,Ba1,Ha1,Rd,Az,Ez); //�ڽ�λ�ÿ�ֱ�Ӵ�ս���ã���Эͬ����ʱ�ڽ����ĸ���
	
	ae=4*6378130.0/3;                //�����Ч�뾶(m),��Ϊ����뾶������֮��
	G1=2*ae*asin(0.5*Rd/ae);
	
	dertH=0.43*G1*G1/ae;           //�߶Ȳ���(����ڱ���)
	
	//�ڽ�λ���ڱ����е�����
	xg=Rd*cos(Ez)*sin(Az);
	yg=Rd*cos(Ez)*cos(Az);
	zg=Rd*sin(Ez)+dertH;              //�߶Ȳ���(����ڱ���)
	
	//����ϵƽ�ƣ�������Ϊ�����ꡢ�ڽ���Ϊ������
	//Ŀ���ڱ����е�����Ϊ��
	xxd=x2+xg;
	yyd=y2+yg;
	zzd=z2+zg; 
	
	Xt=xxd;       //����Ŀ���ڱ��ڽ���ת������������
	Yt=yyd;
	Zt=zzd;	
}

/*******************************************************************/
/***            Ŀ�����״�����ϵ��λ�ü���ģ��                   ***/
/**                     ���԰�  2011-2-10                        ***/
/********      ���룺Ŀ��ƽ̨λ�ã�Lt,Bt,Ht��                *******/
/********            �״�ƽ̨λ�ã�L0,B0,H0��                *******/
/********      �����Ŀ�����״��ز�������ϵ�еľ��ࡢ��λ������ **/
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
	
	Rd=sqrt(x*x+y*y+z*z);  //��֪����XYZ�����������ϵ�µľ��룬��λ������
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
/*******      Ŀ���ڽ��۲�ľ��ࡢ��λ������ת������ͬһ����ϵ��ģ��     *******/
//*******     ���룺Ŀ����Ա���1�ľ��ࡢ��λ������(Rd1,Az1,Ez1)         *******/
//*******           Ŀ������ڽ�2�ľ��ࡢ��λ������(Rd2,Az2,Ez2)         *******/
/*******            �����������꣨La1,Ba1,Ha1��                         ********/
/*******            �ڽ��������꣨La2,Ba2,Ha2��                         ********/
//*******     �����//Ŀ���ڱ����Ĵ���״����ϵ�е�����x1,y1,z1           *******/
/********           Ŀ����ڽ�ת�������Ĵ���״����ϵ�е�����Xt,Yt,Zt   *******/
/********           Ŀ����ڽ�ת�������Ĵ���״����ϵ�еľ��ࡢ��λ������(Rdt,Azt,Ezt) **/
/********           Ŀ����������۲�ļ����ۺ����ϵ��SumCorr           ********/
/*******************************************************************************/
void Get_Coordinate_Conversion_Module(double Rd1,double Az1,double Ez1,double Rd2,double Az2,double Ez2,double La1,double Ba1,double Ha1,
									  double La2,double Ba2,double Ha2,/*double *x1,double *y1,double *z1,*/
									  double& Xt,double& Yt,double& Zt,double& Rdt,double& Azt,double& Ezt,double& SumCorr_xyz)
{
	double xa,ya,za;
	double x2,y2,z2;
	double xg,yg,zg;      //�ڽ��ڱ����е�����
	double Rd,Az,Ez;
	double xt,yt,zt;
	
	double corr1,corr2,corr3/*,corr4,corr5,corr6*/;   //�ż���ϵ��
    double dertH;               //�Ÿ߶Ȳ���
	double G1;                  //�ڽ��뱾��֮��ĵ������
	double ae;
	
	//Ŀ���ڱ����Ĵ���״�����ϵ�е�ֱ������
	xa=Rd1*cos(Ez1)*sin(Az1);
	ya=Rd1*cos(Ez1)*cos(Az1);
	za=Rd1*sin(Ez1);
	
	// 	*x1=xa;    //����Ŀ���ڱ����е�����
	// 	*y1=ya;
	// 	*z1=za;
	
	//Ŀ�����ڽ��Ĵ���״�����ϵ�е�ֱ������
	x2=Rd2*cos(Ez2)*sin(Az2);
	y2=Rd2*cos(Ez2)*cos(Az2);
	z2=Rd2*sin(Ez2);
	
	//Ŀ������ڱ����ľ��ࡢ��λ�͸���
	Object_Radar_Transform(La2,Ba2,Ha2,La1,Ba1,Ha1,Rd,Az,Ez); //�ڽ�λ�ÿ�ֱ�Ӵ�ս���ã���Эͬ����ʱ�ڽ����ĸ���
	
	ae=4*6378130.0/3;                //�����Ч�뾶(m),��Ϊ����뾶������֮��
	G1=2*ae*asin(0.5*Rd/ae);
    
	dertH=0.43*G1*G1/ae;           //�߶Ȳ���(����ڱ���)
	
	//�ڽ�λ���ڱ����е�����
	xg=Rd*cos(Ez)*sin(Az);
	yg=Rd*cos(Ez)*cos(Az);
	zg=Rd*sin(Ez)+dertH;              //�߶Ȳ���(����ڱ���)
	
	//����ϵƽ�ƣ�������Ϊ�����ꡢ�ڽ���Ϊ������
	//Ŀ���ڱ����е�����Ϊ��
	xt=x2+xg;
	yt=y2+yg;
	zt=z2+zg; 
	
	Xt=xt;       //����Ŀ���ڱ��ڽ���ת������������
	Yt=yt;
	Zt=zt;
	
	//�����Է���ģ��
	Mf_SPA(xa,xt,corr1);
	Mf_SPA(ya,yt,corr2);
	Mf_SPA(za,zt,corr3);
	
	SumCorr_xyz=0.5*corr1+0.3*corr2+0.2*corr3;		
	
	//����ת��������꣬��Ŀ�����ڽ��еľ��෽λ����ת����Ŀ���ڱ����еľ��෽λ����
	Rdt=sqrt(xt*xt+yt*yt+zt*zt);  //��֪����XYZ�����������ϵ�µľ��룬��λ������
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
	
	// 	//�����Է���ģ��
	// 	Mf_SPA(Rd1,Rdt,&corr4);
	// 	Mf_SPA(Az1,Azt,&corr5);
	// 	Mf_SPA(Ez1,Ezt,&corr6);
	// 
	// 	
	// 	*AverCorr=SumCorr_xyz/4+corr4/4+corr5/4+corr6/4;	 //����ϵ�� �д��޸ģ��涨��׼��ʲô????��
	
}
/************************************************************************/
/*                             ���Է�������                             */
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
	
	corr=spa;                 //�����������ϵ��
}
/* ����:�����Ͼ�������Ϣ�ṹ��, ������Ϣ (�ṹ��), ������Ϣ(�ṹ��)*/ 
void CoopFind_Information_To_MainShip(UNI_All_NUM& stUniAll, SendRequest_Msg& stSendRequest, SendBack_Msg& stSendBackMsg)
{
	//��������Ϣ�Ľṹ����ת����С�����Ľṹ��, ���ýṹ�����������push back��vctRequestCooperative������λ����Ϣ�������,
	int i ,j;
    //����������Ϣ�ṹ����ۺ�����,ѡ����Ҫ���õĺ���,�ٽ��Ӻ������õĽ��ת��Ϊ������SendBack_Msg�����������ʽ
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
	//��������Ϣ������ṹ����ת��Ϊ�������Ľṹ��
    stReqCooperMsg.lAutonum = stSendRequest.lAutomn;
    stReqCooperMsg.nCorrFlag = stSendRequest.nCorrFlag;
	stReqCooperMsg.nStampTime = stSendRequest.nStampTime;
    memcpy(&stSelfPosi, &stSendRequest.stReqShipPosi, sizeof(stSelfPosi)); 
	//	cout<<" ��γ��"<< stSelfPosi.dHeight <<endl;
	memcpy(&stReqCooperMsg.stReqShipPosi, &stSendRequest.stReqShipPosi, sizeof(stReqCooperMsg.stReqShipPosi)); //memcpy(&A,&B,sizeof(A)); �ѽṹ��B���ṹ��A
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
	//���vctReqCoopMsg
	//��ת����Ľṹ�����������(push back��vctReqCoopMsg)
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
	{  	//����������Ϣ��ÿ���ṹ�壬
		if (iteRequestMsg1->lAutonum >7999)  //������Ϣ�У��ۺ����Ŵ��ڵ���8000����Ϊ������к�����Ϣ��
		{
			ReqUnin_COOP_Find_Information_To_MainShip(stSelfPosi, stUniAll, iteRequestMsg1, vctBackCooperative1);
		}
		if (iteRequestMsg1->lAutonum < 8000 && iteRequestMsg1->lAutonum > 6999 )//������Ϣ��(�޺�����Ϣ)�ۺ�����Ϊ �������ۺ�������7000--8000֮��
		{
			ReqNoTraceUnin_COOP_Find_Information_To_MainShip(stSelfPosi,stUniAll, iteRequestMsg1, vctBackCooperative1);
		}
		if (iteRequestMsg1->lAutonum < 6000)  //������Ϣ��//�ݶ���δ����ĺ�����Ϣ,Ŀ��������5000��6000֮��  
		{
			ReqSingleTrace_COOP_Find_Information_To_MainShip(stSelfPosi,stUniAll, iteRequestMsg1, vctBackCooperative1);
		}
	}//for  iteRequestMsg1
    // ������Ϣ�����vctBackCooperative1�� ,��������Ϣ�ĸ�ʽת��Ϊ������Ľṹ�� stSendBackMsg
	
	if (vctBackCooperative1.size() == 0)
	{
		//����������û����Ϣ����ʾδ�ҵ������Ϣ
	}
	else
	{
		//�ҵ����Ƶķ�����Ϣ��
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
					stSendBackMsg.dComFre[i] = iteBackMsg->vctComm.at(i).dComFre;// ����Ƶ��(MHz)
					stSendBackMsg.dComBand[i] = iteBackMsg->vctComm.at(i).dComBand;// �źŴ���(MHz)
					stSendBackMsg.dComJPN[i] = iteBackMsg->vctComm.at(i).dComJPN; // ��������
					stSendBackMsg.dComConfidence[i] = iteBackMsg->vctComm.at(i).dConfidence;
					for ( int k = 0; k<32; k++)
					{
						stSendBackMsg.sComPlatType[i][k] = iteBackMsg->vctComm.at(i).sPlatType[k];	
					}
				}
			}
			//�к���
			if (iteBackMsg->lAutonum >= 8000)
			{
				stSendBackMsg.BackTraceN = 1;

				//				cout<< "������Ϣ�ĺ�����Ϣ"<<iteBackMsg->lAutonum<<endl;
				memcpy( &stSendBackMsg.stTrace,&iteBackMsg->stTrace,sizeof(stSendBackMsg.stTrace));
				//			    cout<< "������Ϣ�ĺ�����Ϣ"<<stSendBackMsg.stTrace.sPlatType<<endl;
			}			
		}
	}
}