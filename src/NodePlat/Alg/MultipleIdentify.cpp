#include "MultipleIdentify.h"
#include <StdAfx.h>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/************************************************************************/
/*                             ���Է�������                             */
/************************************************************************/
void Mf_SPA(double s, double t,double& corr);
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

/**************************************************************************/
/***********                 �Ӵ�С����ģ��             *****************/
/***********  ���룺��ǰ���������N                       *****************/
/***********        �ں�����                                  *************/
/***********  ������Ӵ�С����                              *************/
/**************************************************************************/
void Get_Fusion_Data_Order(int N,double *Vsat,int *Seri,double *Deci)
{
	int i,k;
	int max;
	double temp;
	int TN;
	
	for(i=0;i<N-1;i++)  //ѡ��
	{
		max=i;
		
		for(k=i+1;k<N;k++)
		{
			if(Vsat[max]<Vsat[k])
				max=k;
		}//for k
		
		if(i!=max){//��������
			
			//�ӳٵ���
            temp=Vsat[max]; Vsat[max]=Vsat[i]; Vsat[i]=temp;
			TN=Seri[max];Seri[max]=Seri[i];Seri[i]=TN;
		}//if		
		
	}//for i
	
	for(i=0;i<N;i++)
	{
		Deci[i]=Vsat[i];                   //���Ӵ�С����	
	}
}

//////////////////////////////////////////////////////////////////////////////
//**************               �������ϵ��ģ��                *************//
//**************����con�����洢���ϵ��������ά����ת��Ϊһά������*********//
//**************             ESM_Data��ʾESM��Ϣ               *************//
//**************             COM_Data��ʾCOM��Ϣ               *************//
//**************            TRACK_Data��ʾTRACK��Ϣ            *************//
//**************             Comb_Data�ϲ��������             *************//
//////////////////////////////////////////////////////////////////////////////
void Coefficient(double *con, VCT_COOPER_MSG::iterator ite_CooperMsg, VCT_sPlatType vctPlatType)
{
	VCT_sPlatType::iterator ite_PlatType;
	VCT_TRACE_MSG::iterator ite_TrackMsg;
	VCT_TRACE_MSG::iterator ite_TrackM;
	VCT_ESM_MSG::iterator ite_EsmMsg;
	VCT_ESM_MSG::iterator ite_EsmM;
	VCT_COMM_MSG::iterator ite_CommMsg;
	VCT_COMM_MSG::iterator ite_CommM;

	typedef vector<double> VCT_CORR;
	VCT_CORR vctCorr;      // ��Ź���ϵ��������
	VCT_CORR::iterator ite_Corr;
   
	int i = 0;
	int j = 0;
	double dcorrAz = 0.0;
	double dMaxCorr = 0.0;
	double dcorrChongPin = 0.0;  //��Ƶ
    double dcorrMaiKuan = 0.0;   //����
	double dcorrTianXianScan = 0.0;  //����ɨ������
	double dcorrComZaiPin = 0.0;   // ��Ƶ
	double dcorrPulseExtent = 0.0; // �������
	double dAverCorr = 0.0;
	double conn[50][50];
	
	//TRACK���ϵ��
	if (0 == ite_CooperMsg->vctTrace.size())
	{
		//�����ں������޺��������ϵ��
	} 
	else
	{
		//�����ϵ��
		//����������vectror
		for (ite_TrackMsg = ite_CooperMsg->vctTrace.begin(); ite_TrackMsg != ite_CooperMsg->vctTrace.end(); ite_TrackMsg++)
		{
            
			for (ite_PlatType = vctPlatType.begin(); ite_PlatType != vctPlatType.end(); ite_PlatType++)
			{
				//������ƽ̨���ͺ�ƽ̨�����е�������ͬ
				if (0 == strcmp(ite_TrackMsg->sPlatType,*ite_PlatType))
				{
					//ֱ��ȡ���Ŷ���Ϊ���ϵ��
					conn[i][j] = ite_TrackMsg->dConfidence;
				} 
				//������ƽ̨���ͺ�ƽ̨�����е����Ͳ���ͬ
				else
				{
					//�������ϵ�� ��ȡ�ú�����Ϣ�ķ�λ�ͺ�����vector��������Ϣ��ʶ���ƽ̨�����еĸ����͵ĺ�����Ϣ��λ�Ƚ�,��δ�ҵ�����Ϊ0
					//��մ�����ϵ��������

					vctCorr.clear();
					//��������vector

					for ( ite_TrackM = ite_CooperMsg->vctTrace.begin(); ite_TrackM != ite_CooperMsg->vctTrace.end();ite_TrackM++)
					{   //�ҳ�ʶ���ƽ̨���͵ĺ�����Ϣ
						if (0 == strcmp(ite_TrackM->sPlatType,*ite_PlatType))
						{
							Mf_SPA(ite_TrackM->dAzimuth, ite_TrackMsg->dAzimuth, dcorrAz);
					    	vctCorr.push_back(dcorrAz);
						}
					}// for
						if (vctCorr.empty())
						{
							conn[i][j] = 0.0;
						}
						//����������Ϊ��
						else
						{
							//ȡ�������������ֵ
							//��������ֻ��һ��ֵ
							if ( vctCorr.size() == 1 )
							{
								conn[i][j] = vctCorr.front(); 
							}
							//�����������ȴ���1
							if ( vctCorr.size() > 1 )
							{
								dMaxCorr = vctCorr.front();
								for(ite_Corr = vctCorr.begin(); ite_Corr != vctCorr.end(); ite_Corr++)
								{
									if ( dMaxCorr < *ite_Corr)
									{
										dMaxCorr = *ite_Corr;
									}
								}//for
								conn[i][j] = dMaxCorr;	
							}  // if �������ȴ���1
						}//else  ����������Ϊ��
				
				}//else  //������ƽ̨���ͺ�ƽ̨�����е����Ͳ���ͬ
			  j++;
			  if ( j == vctPlatType.size()  )
			  {
				  j = 0;
			  }
			} // for ����ƽ̨���͵����� ite_PlatType = vctPlatType.begin()
	      i++;
		} // for �������������� ite_TrackMsg = ite_CooperMsg->vctTrace.begin()
	}

	//ESM���ϵ��
    if ( 0 == ite_CooperMsg->vctEsm.size())
    {
		//������ESM����Esm�����ϵ��
    }
	else
	{
		for ( ite_EsmMsg = ite_CooperMsg->vctEsm.begin(); ite_EsmMsg != ite_CooperMsg->vctEsm.end(); ite_EsmMsg++)
		{  
			for (ite_PlatType = vctPlatType.begin(); ite_PlatType != vctPlatType.end(); ite_PlatType++)
			{
				//Esm��ƽ̨���ͺ�ƽ̨�����е�������ͬ
				if (0 == strcmp(ite_EsmMsg->sPlatType,*ite_PlatType))
				{
					//ֱ��ȡ���Ŷ���Ϊ���ϵ��
					conn[i][j] = ite_EsmMsg->dConfidence;
				} 
				//Esm��ƽ̨���ͺ�ƽ̨�����е����Ͳ�ͬ
				else
				{
					//�������ϵ�� ��ȡ��Esm��Ϣ������������Esm��vector��������Ϣ��ʶ���ƽ̨�����еĸ����͵�Esm��Ϣ�����������Ƚ�,��δ�ҵ�����Ϊ0
					//��մ�����ϵ��������
					vctCorr.clear();
					//����Esm��vector
					
					for ( ite_EsmM = ite_CooperMsg->vctEsm.begin(); ite_EsmM != ite_CooperMsg->vctEsm.end(); ite_EsmM++)
					{   //�ҳ�ʶ���ƽ̨���͵�Esm��Ϣ
						if (0 == strcmp(ite_EsmM->sPlatType, *ite_PlatType))
						{
							Mf_SPA(ite_EsmM->dChongPin, ite_EsmMsg->dChongPin,dcorrChongPin); //Ƶ��
							Mf_SPA(ite_EsmM->dMaiKuan,ite_EsmMsg->dMaiKuan,dcorrMaiKuan); //����
							Mf_SPA(ite_EsmM->dTianXianScan,ite_EsmMsg->dTianXianScan,dcorrTianXianScan); //����ɨ������
							dAverCorr = ( dcorrChongPin + dcorrMaiKuan +dcorrTianXianScan )/3;
							vctCorr.push_back(dAverCorr);
						}
					}// for
						if (vctCorr.empty())
						{
							conn[i][j] = 0.0;
						}
						//����������Ϊ��
						else
						{
							//ȡ�������������ֵ
							//��������ֻ��һ��ֵ
							if ( vctCorr.size() == 1 )
							{
								conn[i][j] = vctCorr.front(); 
							}
							//�����������ȴ���1
							if ( vctCorr.size() > 1 )
							{
								dMaxCorr = vctCorr.front();
								for(ite_Corr = vctCorr.begin(); ite_Corr != vctCorr.end(); ite_Corr++)
								{
									if ( dMaxCorr < *ite_Corr)
									{
										dMaxCorr = *ite_Corr;
									}
								}//for
								conn[i][j] = dMaxCorr;	
							}  // if �������ȴ���1
						}//else  ����������Ϊ��
				
				} //else //Esm��ƽ̨���ͺ�ƽ̨�����е����Ͳ�ͬ
		     j++;
			 if ( j == vctPlatType.size()  )
			 {
				 j = 0;
			 }
			}// for ����ƽ̨���͵�����
         i++;
		}// for ����Esm������
	}//else ��Esm�����ϵ��

	//COMM���ϵ��
	if ( 0 == ite_CooperMsg->vctComm.size())
	{
		//������Com,��Comm�����ϵ��
	}
	else
	{
		//�����ϵ��
		//����Comm������
		for ( ite_CommMsg = ite_CooperMsg->vctComm.begin(); ite_CommMsg != ite_CooperMsg->vctComm.end(); ite_CommMsg++)
		{
			for (ite_PlatType = vctPlatType.begin(); ite_PlatType != vctPlatType.end(); ite_PlatType++)
			{
				//Comm��ƽ̨���ͺ�ƽ̨�����е�������ͬ
				if (0 == strcmp(ite_CommMsg->sPlatType, *ite_PlatType))
				{
					//ֱ��ȡ���Ŷ���Ϊ���ϵ��
					conn[i][j] = ite_CommMsg->dConfidence;
				} 
				//Esm��ƽ̨���ͺ�ƽ̨�����е����Ͳ�ͬ
				else
				{
					//�������ϵ�� ��ȡ��Comm��Ϣ������������Comm��vector��������Ϣ��ʶ���ƽ̨�����еĸ����͵�Comm��Ϣ�����������Ƚ�,��δ�ҵ�����Ϊ0
					//��մ�����ϵ��������
					vctCorr.clear();
					//����Esm��vector
					
					for ( ite_CommM = ite_CooperMsg->vctComm.begin(); ite_CommM != ite_CooperMsg->vctComm.end();ite_CommM++)
					{   //�ҳ�ʶ���ƽ̨���͵�Comm��Ϣ
						if (0 == strcmp(*ite_PlatType, ite_EsmM->sPlatType))
						{
							Mf_SPA(ite_CommM->dComZaiPin, ite_CommMsg->dComZaiPin,dcorrComZaiPin); //��Ƶ
							Mf_SPA(ite_CommM->dPulseExtent,ite_CommMsg->dPulseExtent,dcorrPulseExtent); //�������
							dAverCorr = ( dcorrComZaiPin + dcorrPulseExtent )/2;
							vctCorr.push_back(dAverCorr);
						}
					}// for
					if (vctCorr.empty())
					{
						conn[i][j] = 0.0;
					}					
					else//����������Ϊ��
					{
						//ȡ�������������ֵ
						//��������ֻ��һ��ֵ
						if ( vctCorr.size() == 1 )
						{
							conn[i][j] = vctCorr.front(); 
						}
						//�����������ȴ���1
						if ( vctCorr.size() > 1 )
						{
							dMaxCorr = vctCorr.front();
							for(ite_Corr = vctCorr.begin(); ite_Corr != vctCorr.end(); ite_Corr++)
							{
								if ( dMaxCorr < *ite_Corr)
								{
									dMaxCorr = *ite_Corr;
								}
							}//for
							conn[i][j] = dMaxCorr;	
						}  // if �������ȴ���1
					}//else  ����������Ϊ��
					
				} //else //Esm��ƽ̨���ͺ�ƽ̨�����е����Ͳ�ͬ
				j++;
				if ( j == vctPlatType.size()  )
				{
					j = 0;
				}
			}// for ����ƽ̨���͵�����
			i++;
		}// for ����Esm������
	}//else �����ϵ��
	
	//�����ά����
// 	for ( int t = 0; t< i;t++)
// 	{
// 		for (int k=0; k< vctPlatType.size(); k++)
// 		{
// 			printf("%.8f\t", conn[t][k]);
// 		}
// 		cout<<endl;
// 	}
	
	//����λ����conn[i][j]ת��Ϊһά����con[]
	int a =0;
	int p=0;
	int n=0;

	for ( p = 0 ;p < i; p++)
	{
		for ( n = 0; n < vctPlatType.size() ; n++)
		{
			con[a] = conn[p][n];
			a++;
		}
 	}
	
}

//////////////////////////////////////////////////////////////////////////////
//**************                  D-S֤���ںϾ������ģ��      *************//
//**************      ���룺���������򴫸�������DSNum          *************//
//**************            Ŀ��������OBjTypeNum               *************//
//**************            ��ϵ����ADSMetri                 *************//
//**************            ����ԭ���� Seri                  *************//
//**************      ������ۺ����ͺ��ۺ϶ȣ� CPdere          *************//
//////////////////////////////////////////////////////////////////////////////
void D_S(int DSNum, int OBjTypeNum, double *ADSMetri, int *Seri, double *CPdere)
{
	int i, j, k;
	double max, suma, msilt, ksilt, sux;
	double DSMetri[20][21];
	double PossiMetri[20][21];                        //���ʸ�ֵ����
	double fusion1[21], fusion2[21], fusion3[21][21];   //�Ŵ��ںϵ���,�Լ�����ֵ���������ֵ
	double CoopFusion[21];                            //�������ں�ֵ
	double Decision[21];                              //����ֵ

	//����ת��
	for(i = 0; i < DSNum; i++)
	{
		for(j = 0; j < OBjTypeNum; j++)
		{
			DSMetri[i][j] = ADSMetri[i * OBjTypeNum + j];
//			printf("%f  ", DSMetri[i][j]);
		}
//		printf("\n");
	}

	 //��һ�����������ʸ�ֵ����PossiMetri[��ϢԴ��][�����+1]
	 for(i = 0 ; i < DSNum; i++)           //������DSMetri[][]
	 {
		 max = DSMetri[i][0];         
		 suma = DSMetri[i][0];        
		 for(j = 1; j < OBjTypeNum; j++)            //��ѭ�����ۼӲ��ҳ��������ֵ
		 {
			 suma = suma + DSMetri[i][j];         //�����и����ݵ��ۼ�ֵ
			 if(max < DSMetri[i][j])
			 {
				 max=DSMetri[i][j];                //�������ֵ
			 }				 		 
		 }

 	     //������ʸ�ֵ
		 msilt = 1 - max;
		 for(j = 0; j < OBjTypeNum; j++)
		 {
			 PossiMetri[i][j] = DSMetri[i][j] * (1 - msilt) / suma;   //����	 		 
		 }
		 PossiMetri[i][j] = 1 - max;           //���е�����һλ������� 	 
	 }

// 	 printf("���ʸ�ֵ����\n");
// 	 for(i = 0; i < DSNum; i++)
// 	 {
// 		 for(j = 0; j < OBjTypeNum + 1; j++)
// 		 {
// 			 printf("%f  ", PossiMetri[i][j]);
// 		 }
// 		 printf("\n");
// 	 }


	 //�ڶ��������ڴ�����Ϣ���ںϾ��߾������

	 //��21���������ں�	
	 //�ȶ�ȡ���ʸ�ֵ�����һ��,������ںϵ�����fusion1[]��
	 for(j = 0; j < OBjTypeNum + 1; j++)
	 {
          fusion1[j] = PossiMetri[0][j];
	 }

//	 k = 1;//���ƶ�ȡ����
	 for(k = 1 ; k < DSNum ; k++)           //���ںϴ���:DSNum-1
	 {
		 //1��ȡ���ʸ�ֵ�������һ��,������ںϵ�����fusion2[]��
		 for(j = 0; j < OBjTypeNum + 1; j++)
		 {
			 fusion2[j] = PossiMetri[k][j];
		 }
		
		 //2�������е����ֵ
		 for(i = 0; i < OBjTypeNum + 1; i++)             //��ѭ��
		 {
			 for(j = 0; j < OBjTypeNum + 1; j++)         //��ѭ��
			      fusion3[i][j]=fusion2[i]*fusion1[j];			 
		 }

   	     //3�����������ںϵ�ì�̶ܳ�ֵK
		 ksilt = 0;
		 for(i = 0; i < OBjTypeNum; i++)                       //��ѭ��,�����в�����
		 {
			 for(j = 0;j < OBjTypeNum;j++)                    //�����в�����
			 {
				 if(i != j)
		            ksilt = ksilt + fusion3[i][j];
			 }
		 }
		 ksilt = ksilt + fusion3[OBjTypeNum][OBjTypeNum];    //������������е����һ��ֵ
		 ksilt = fabs(1.0 - ksilt);   //���յ�ì�̶ܳ�ֵksilt

		 //4�����������ں�ֵ
		 for(i = 0; i < OBjTypeNum; i++)                     //��ѭ��
		 {
			 //�ҳ����Խ�����Ԫ�أ�������е����һ���͸��е����һ��                 
			 sux = fusion3[i][i] + fusion3[i][OBjTypeNum] + fusion3[OBjTypeNum][i];  
			 CoopFusion[i] = sux / ksilt;  //�ں�ֵ
		 }
		 CoopFusion[OBjTypeNum] = fusion3[OBjTypeNum][OBjTypeNum] / ksilt;  //�����ں�ֵ

		 //5�ں�ֵ������һ�δ��ںϵ�����fusion1[]��
		 for(i = 0; i < OBjTypeNum + 1; i++)
		 {
			  fusion1[i] = CoopFusion[i];           //��ǰ�ں�ֵ����Ϊ�´��ںϵĵ�һ��ֵ		 
		 }
         
//		k++;     //������һ�еĶ�ȡָ��
	 }

	 //��22���������ж�
	 for(i = 0; i < OBjTypeNum + 1; i++)//������
	 {
		 printf("�ں�ֵ=%f  ", CoopFusion[i]);	
		 printf("���ʹ���=%d  ", Seri[i]);
	 }
	 printf("\n");
	 //���ںϽ�����Ӵ�С����
	 Get_Fusion_Data_Order(OBjTypeNum+1,CoopFusion,Seri,Decision);
	 for(i = 0; i < OBjTypeNum + 1; i++)//
	 {
		 printf("�ź��ں�ֵ=%f  ", Decision[i]);//���ֵ��Ӧ�����ͼ�Ϊʶ�������
		 printf("���ʹ���=%d  ", Seri[i]);	 
	 }	 
	 printf("\n");
	 *CPdere=CoopFusion[0];          //�ۺ����Ŷ�Ϊ�����
}






//void D_S(int DSNum, int OBjTypeNum, double *ADSMetri, int *Seri, double *CPdere)
void MultipleIdentify(VCT_COOPER_MSG& vctCooperMsg, VCT_MIDENTIINFOR_MSG& vctMidentiinforMsg)
{
	
	VCT_COOPER_MSG::iterator iteCoorMsg;
	VCT_COOPER_MSG::iterator iteCoMessage;
	VCT_TRACE_MSG::iterator iteTrack;
	VCT_ESM_MSG::iterator iteEsm;
	VCT_COMM_MSG::iterator iteComm;
	VCT_sPlatType::iterator iteCPType1;
	VCT_sPlatType::iterator iteCPType2;
	VCT_sPlatType vctCooperPlatType; //�ϲ���Ϣ������ƽ̨���� 
	VCT_sPlatType vctPlatType;      //ɸѡ�󣬴�Ų�ͬ��ƽ̨����


	VCT_CON vctcon;                 //��ϵ����洢����
	int NumType,NumMsg;             //�ϲ���Ϣ������ƽ̨��������֤������
	int i;
	int tpflag;
	int Seri[10]={0};
	double con[50];
	double CPdere;      //�ۺ����Ŷ�
	MIDENTIINFOR MidentStr;          //ʶ����

	vctMidentiinforMsg.clear();//�������ʶ����

 

	for (iteCoorMsg = vctCooperMsg.begin(); iteCoorMsg != vctCooperMsg.end();iteCoorMsg++)
	{  
		
		vctCooperPlatType.clear();
		vctPlatType.clear();
		tpflag = 0;
		//��ͬ���źϲ����������Ϣ��ƽ̨���Ͷ��ŵ�ͬһ����1��
        //��������: ���Ժϲ���Ϣ�ĺ���,Comm,ESM����Ϣ����		
	    int TS = iteCoorMsg->vctTrace.size();  //�����ն���ͬ,����Ϣ����Ϊԭ������Ϣ������
		int ES = iteCoorMsg->vctEsm.size();
		int CS = iteCoorMsg->vctComm.size();

		if ( iteCoorMsg->vctTrace.size() != 0 )
		{
			for ( iteTrack = iteCoorMsg->vctTrace.begin(); iteTrack != iteCoorMsg->vctTrace.end(); iteTrack++)
			{
				vctCooperPlatType.push_back(iteTrack->sPlatType);
			} 
		} 			
		if ( iteCoorMsg->vctComm.size() !=0 )
		{
			for ( iteComm = iteCoorMsg->vctComm.begin(); iteComm != iteCoorMsg->vctComm.end(); iteComm++)
			{
				vctCooperPlatType.push_back(iteComm->sPlatType);
			}
		}			
		if (iteCoorMsg->vctEsm.size() !=0 )
		{
			for (iteEsm = iteCoorMsg->vctEsm.begin(); iteEsm != iteCoorMsg->vctEsm.end();iteEsm++)
			{
				vctCooperPlatType.push_back(iteEsm->sPlatType);			
			}			
		}
		//��������1������������a,b ������a��������ƽ̨������������b�����Ƚ�ƽ̨�����е�����a��ǰֵ��֮ǰֵ�Ƿ�����ͬ��
		//����ͬ�ķ���ƽ̨����2�У�ƽ̨����2��������ƽ̨������
		int nsize = vctCooperPlatType.size();
		for ( iteCPType1 = vctCooperPlatType.begin(); iteCPType1 != vctCooperPlatType.end(); iteCPType1++)
		{
			if (iteCPType1 == vctCooperPlatType.begin())
			{
				vctPlatType.push_back(*iteCPType1);
			} 
			else
			{
				for( iteCPType2 = vctPlatType.begin(); iteCPType2 != vctPlatType.end(); iteCPType2++)
				{
					//�жϺϲ�������ǰһ���ͺ�һ����ƽ̨�����Ƿ���ͬ������ͬ������ѭ����ѭ��������������ͬ�����ƽ̨������
					if (iteCPType2 != vctPlatType.end() && (strcmp(*iteCPType1, *iteCPType2) == 0))
					{
						//�ںϲ��������ҵ���ƽ̨���ͣ�ֱ������ѭ��
						break;
					}
					else if (iteCPType2 == vctPlatType.end())
					{
						//�ϲ����������û���ҵ���Ӧ�ðѸ�ƽ̨���ʹ���ϲ��������
						vctPlatType.push_back(*iteCPType2);
					}
				}//����ѭ��δ�ҵ���ͬ��
			}	
		} 
		
		NumType = vctPlatType.size();  //ʶ��������
		//test ����8�в��� ƽ̨��������
		//test
		VCT_sPlatType testVctPlatType;
		VCT_sPlatType::iterator iteCPType3test;
		testVctPlatType.clear();
		 		for ( iteCPType3test = vctPlatType.begin(); iteCPType3test != vctPlatType.end(); iteCPType3test++ )
		 		{
		// 		 	int p = 1;
		 			testVctPlatType.push_back(*iteCPType3test);  	
         		}


		//10.10
		iteCoMessage = iteCoorMsg;
//		NumType = testVctPlatType.size();  //ʶ��������

		NumMsg = iteCoMessage->vctComm.size() + iteCoMessage->vctEsm.size() + iteCoMessage->vctTrace.size();//����Դ֤����
//		NumMsg = iteCoMessage->nTraceN + iteCoMessage->nEsmN + iteCoMessage->nComN;//����Դ֤����
		vctcon.clear(); //��չ�ϵ����洢����
//		copy(vctPlatType.begin(),vctPlatType.end(),testVctPlatType.begin());  //��v1���Ƶ�v2

		Coefficient(con, iteCoMessage, testVctPlatType);//��ϵ����
		for (i = 0; i < NumType; i++)
		{
			Seri[i] = i+1;
		}

		D_S(NumMsg, NumType, con, Seri, &CPdere);//DS֤��ʶ��

		MidentStr.lAutonum = iteCoorMsg->lAutonum;
		MidentStr.dConfidence = CPdere;
        int b = Seri[0] -1;
		MidentStr.sPlatType = vctPlatType[Seri[0]-1];
		vctMidentiinforMsg.push_back(MidentStr);//��������ʶ����
   }

}
