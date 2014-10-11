#include "MultipleIdentify.h"
#include <StdAfx.h>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/************************************************************************/
/*                             集对分析算子                             */
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
// 	corr=spa;                 //带回两数相关系数
// }

/**************************************************************************/
/***********                 从大到小排序模块             *****************/
/***********  输入：当前类别数个数N                       *****************/
/***********        融合数组                                  *************/
/***********  输出：从大到小次序                              *************/
/**************************************************************************/
void Get_Fusion_Data_Order(int N,double *Vsat,int *Seri,double *Deci)
{
	int i,k;
	int max;
	double temp;
	int TN;
	
	for(i=0;i<N-1;i++)  //选择法
	{
		max=i;
		
		for(k=i+1;k<N;k++)
		{
			if(Vsat[max]<Vsat[k])
				max=k;
		}//for k
		
		if(i!=max){//交换次序
			
			//延迟调整
            temp=Vsat[max]; Vsat[max]=Vsat[i]; Vsat[i]=temp;
			TN=Seri[max];Seri[max]=Seri[i];Seri[i]=TN;
		}//if		
		
	}//for i
	
	for(i=0;i<N;i++)
	{
		Deci[i]=Vsat[i];                   //按从大到小带回	
	}
}

//////////////////////////////////////////////////////////////////////////////
//**************               计算相关系数模块                *************//
//**************矩阵con用来存储相关系数，将二维矩阵转化为一维矩阵数*********//
//**************             ESM_Data表示ESM信息               *************//
//**************             COM_Data表示COM信息               *************//
//**************            TRACK_Data表示TRACK信息            *************//
//**************             Comb_Data合并后的数据             *************//
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
	VCT_CORR vctCorr;      // 存放关联系数的容器
	VCT_CORR::iterator ite_Corr;
   
	int i = 0;
	int j = 0;
	double dcorrAz = 0.0;
	double dMaxCorr = 0.0;
	double dcorrChongPin = 0.0;  //重频
    double dcorrMaiKuan = 0.0;   //脉宽
	double dcorrTianXianScan = 0.0;  //天线扫描周期
	double dcorrComZaiPin = 0.0;   // 载频
	double dcorrPulseExtent = 0.0; // 脉冲幅度
	double dAverCorr = 0.0;
	double conn[50][50];
	
	//TRACK相关系数
	if (0 == ite_CooperMsg->vctTrace.size())
	{
		//不存在航迹，无航迹的相关系数
	} 
	else
	{
		//求相关系数
		//遍历航迹的vectror
		for (ite_TrackMsg = ite_CooperMsg->vctTrace.begin(); ite_TrackMsg != ite_CooperMsg->vctTrace.end(); ite_TrackMsg++)
		{
            
			for (ite_PlatType = vctPlatType.begin(); ite_PlatType != vctPlatType.end(); ite_PlatType++)
			{
				//航迹的平台类型和平台类型中的类型相同
				if (0 == strcmp(ite_TrackMsg->sPlatType,*ite_PlatType))
				{
					//直接取置信度作为相关系数
					conn[i][j] = ite_TrackMsg->dConfidence;
				} 
				//航迹的平台类型和平台类型中的类型不相同
				else
				{
					//计算相关系数 ，取该航迹信息的方位和航迹的vector的所有信息中识别出平台类型中的该类型的航迹信息方位比较,若未找到则标记为0
					//清空存放相关系数的容器

					vctCorr.clear();
					//遍历航迹vector

					for ( ite_TrackM = ite_CooperMsg->vctTrace.begin(); ite_TrackM != ite_CooperMsg->vctTrace.end();ite_TrackM++)
					{   //找出识别该平台类型的航迹信息
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
						//关联容器不为空
						else
						{
							//取关联容器的最大值
							//关联容器只有一个值
							if ( vctCorr.size() == 1 )
							{
								conn[i][j] = vctCorr.front(); 
							}
							//关联容器长度大于1
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
							}  // if 容器长度大于1
						}//else  关联容器不为空
				
				}//else  //航迹的平台类型和平台类型中的类型不相同
			  j++;
			  if ( j == vctPlatType.size()  )
			  {
				  j = 0;
			  }
			} // for 遍历平台类型的容器 ite_PlatType = vctPlatType.begin()
	      i++;
		} // for 遍历航迹的容器 ite_TrackMsg = ite_CooperMsg->vctTrace.begin()
	}

	//ESM相关系数
    if ( 0 == ite_CooperMsg->vctEsm.size())
    {
		//不存在ESM，无Esm的相关系数
    }
	else
	{
		for ( ite_EsmMsg = ite_CooperMsg->vctEsm.begin(); ite_EsmMsg != ite_CooperMsg->vctEsm.end(); ite_EsmMsg++)
		{  
			for (ite_PlatType = vctPlatType.begin(); ite_PlatType != vctPlatType.end(); ite_PlatType++)
			{
				//Esm的平台类型和平台类型中的类型相同
				if (0 == strcmp(ite_EsmMsg->sPlatType,*ite_PlatType))
				{
					//直接取置信度作为相关系数
					conn[i][j] = ite_EsmMsg->dConfidence;
				} 
				//Esm的平台类型和平台类型中的类型不同
				else
				{
					//计算相关系数 ，取该Esm信息的特征参数和Esm的vector的所有信息中识别出平台类型中的该类型的Esm信息的特征参数比较,若未找到则标记为0
					//清空存放相关系数的容器
					vctCorr.clear();
					//遍历Esm的vector
					
					for ( ite_EsmM = ite_CooperMsg->vctEsm.begin(); ite_EsmM != ite_CooperMsg->vctEsm.end(); ite_EsmM++)
					{   //找出识别该平台类型的Esm信息
						if (0 == strcmp(ite_EsmM->sPlatType, *ite_PlatType))
						{
							Mf_SPA(ite_EsmM->dChongPin, ite_EsmMsg->dChongPin,dcorrChongPin); //频率
							Mf_SPA(ite_EsmM->dMaiKuan,ite_EsmMsg->dMaiKuan,dcorrMaiKuan); //脉宽
							Mf_SPA(ite_EsmM->dTianXianScan,ite_EsmMsg->dTianXianScan,dcorrTianXianScan); //天线扫描周期
							dAverCorr = ( dcorrChongPin + dcorrMaiKuan +dcorrTianXianScan )/3;
							vctCorr.push_back(dAverCorr);
						}
					}// for
						if (vctCorr.empty())
						{
							conn[i][j] = 0.0;
						}
						//关联容器不为空
						else
						{
							//取关联容器的最大值
							//关联容器只有一个值
							if ( vctCorr.size() == 1 )
							{
								conn[i][j] = vctCorr.front(); 
							}
							//关联容器长度大于1
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
							}  // if 容器长度大于1
						}//else  关联容器不为空
				
				} //else //Esm的平台类型和平台类型中的类型不同
		     j++;
			 if ( j == vctPlatType.size()  )
			 {
				 j = 0;
			 }
			}// for 遍历平台类型的容器
         i++;
		}// for 遍历Esm的容器
	}//else 求Esm的相关系数

	//COMM相关系数
	if ( 0 == ite_CooperMsg->vctComm.size())
	{
		//不存在Com,无Comm的相关系数
	}
	else
	{
		//求相关系数
		//遍历Comm的容器
		for ( ite_CommMsg = ite_CooperMsg->vctComm.begin(); ite_CommMsg != ite_CooperMsg->vctComm.end(); ite_CommMsg++)
		{
			for (ite_PlatType = vctPlatType.begin(); ite_PlatType != vctPlatType.end(); ite_PlatType++)
			{
				//Comm的平台类型和平台类型中的类型相同
				if (0 == strcmp(ite_CommMsg->sPlatType, *ite_PlatType))
				{
					//直接取置信度作为相关系数
					conn[i][j] = ite_CommMsg->dConfidence;
				} 
				//Esm的平台类型和平台类型中的类型不同
				else
				{
					//计算相关系数 ，取该Comm信息的特征参数和Comm的vector的所有信息中识别出平台类型中的该类型的Comm信息的特征参数比较,若未找到则标记为0
					//清空存放相关系数的容器
					vctCorr.clear();
					//遍历Esm的vector
					
					for ( ite_CommM = ite_CooperMsg->vctComm.begin(); ite_CommM != ite_CooperMsg->vctComm.end();ite_CommM++)
					{   //找出识别该平台类型的Comm信息
						if (0 == strcmp(*ite_PlatType, ite_EsmM->sPlatType))
						{
							Mf_SPA(ite_CommM->dComZaiPin, ite_CommMsg->dComZaiPin,dcorrComZaiPin); //载频
							Mf_SPA(ite_CommM->dPulseExtent,ite_CommMsg->dPulseExtent,dcorrPulseExtent); //脉冲幅度
							dAverCorr = ( dcorrComZaiPin + dcorrPulseExtent )/2;
							vctCorr.push_back(dAverCorr);
						}
					}// for
					if (vctCorr.empty())
					{
						conn[i][j] = 0.0;
					}					
					else//关联容器不为空
					{
						//取关联容器的最大值
						//关联容器只有一个值
						if ( vctCorr.size() == 1 )
						{
							conn[i][j] = vctCorr.front(); 
						}
						//关联容器长度大于1
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
						}  // if 容器长度大于1
					}//else  关联容器不为空
					
				} //else //Esm的平台类型和平台类型中的类型不同
				j++;
				if ( j == vctPlatType.size()  )
				{
					j = 0;
				}
			}// for 遍历平台类型的容器
			i++;
		}// for 遍历Esm的容器
	}//else 求相关系数
	
	//输出二维矩阵
// 	for ( int t = 0; t< i;t++)
// 	{
// 		for (int k=0; k< vctPlatType.size(); k++)
// 		{
// 			printf("%.8f\t", conn[t][k]);
// 		}
// 		cout<<endl;
// 	}
	
	//将二位矩阵conn[i][j]转化为一维矩阵con[]
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
//**************                  D-S证据融合决策设计模块      *************//
//**************      输入：决策数（或传感器数）DSNum          *************//
//**************            目标类数：OBjTypeNum               *************//
//**************            关系矩阵：ADSMetri                 *************//
//**************            类型原次序： Seri                  *************//
//**************      输出：综合类型和综合度： CPdere          *************//
//////////////////////////////////////////////////////////////////////////////
void D_S(int DSNum, int OBjTypeNum, double *ADSMetri, int *Seri, double *CPdere)
{
	int i, j, k;
	double max, suma, msilt, ksilt, sux;
	double DSMetri[20][21];
	double PossiMetri[20][21];                        //概率赋值矩阵
	double fusion1[21], fusion2[21], fusion3[21][21];   //放待融合的行,以及两行值的两两相乘值
	double CoopFusion[21];                            //放两行融合值
	double Decision[21];                              //排序值

	//矩阵转换
	for(i = 0; i < DSNum; i++)
	{
		for(j = 0; j < OBjTypeNum; j++)
		{
			DSMetri[i][j] = ADSMetri[i * OBjTypeNum + j];
//			printf("%f  ", DSMetri[i][j]);
		}
//		printf("\n");
	}

	 //第一步：建立概率赋值矩阵PossiMetri[信息源数][类别数+1]
	 for(i = 0 ; i < DSNum; i++)           //行运算DSMetri[][]
	 {
		 max = DSMetri[i][0];         
		 suma = DSMetri[i][0];        
		 for(j = 1; j < OBjTypeNum; j++)            //列循环，累加并找出该行最大值
		 {
			 suma = suma + DSMetri[i][j];         //此行中各数据的累加值
			 if(max < DSMetri[i][j])
			 {
				 max=DSMetri[i][j];                //该行最大值
			 }				 		 
		 }

 	     //计算概率赋值
		 msilt = 1 - max;
		 for(j = 0; j < OBjTypeNum; j++)
		 {
			 PossiMetri[i][j] = DSMetri[i][j] * (1 - msilt) / suma;   //计算	 		 
		 }
		 PossiMetri[i][j] = 1 - max;           //该行的最后加一位不明类别 	 
	 }

// 	 printf("概率赋值矩阵：\n");
// 	 for(i = 0; i < DSNum; i++)
// 	 {
// 		 for(j = 0; j < OBjTypeNum + 1; j++)
// 		 {
// 			 printf("%f  ", PossiMetri[i][j]);
// 		 }
// 		 printf("\n");
// 	 }


	 //第二步：对于此批信息，融合决策矩阵计算

	 //第21步：两两融合	
	 //先读取概率赋值矩阵第一行,放入待融合的数组fusion1[]中
	 for(j = 0; j < OBjTypeNum + 1; j++)
	 {
          fusion1[j] = PossiMetri[0][j];
	 }

//	 k = 1;//控制读取的行
	 for(k = 1 ; k < DSNum ; k++)           //总融合次数:DSNum-1
	 {
		 //1读取概率赋值矩阵的下一行,放入待融合的数组fusion2[]中
		 for(j = 0; j < OBjTypeNum + 1; j++)
		 {
			 fusion2[j] = PossiMetri[k][j];
		 }
		
		 //2计算两行的相乘值
		 for(i = 0; i < OBjTypeNum + 1; i++)             //行循环
		 {
			 for(j = 0; j < OBjTypeNum + 1; j++)         //列循环
			      fusion3[i][j]=fusion2[i]*fusion1[j];			 
		 }

   	     //3计算这两行融合的矛盾程度值K
		 ksilt = 0;
		 for(i = 0; i < OBjTypeNum; i++)                       //行循环,不明行不加入
		 {
			 for(j = 0;j < OBjTypeNum;j++)                    //不明列不加入
			 {
				 if(i != j)
		            ksilt = ksilt + fusion3[i][j];
			 }
		 }
		 ksilt = ksilt + fusion3[OBjTypeNum][OBjTypeNum];    //加入最后行与列的最后一个值
		 ksilt = fabs(1.0 - ksilt);   //最终的矛盾程度值ksilt

		 //4计算这两行融合值
		 for(i = 0; i < OBjTypeNum; i++)                     //行循环
		 {
			 //找出主对角线上元素，加入该行的最后一个和该列的最后一个                 
			 sux = fusion3[i][i] + fusion3[i][OBjTypeNum] + fusion3[OBjTypeNum][i];  
			 CoopFusion[i] = sux / ksilt;  //融合值
		 }
		 CoopFusion[OBjTypeNum] = fusion3[OBjTypeNum][OBjTypeNum] / ksilt;  //不明融合值

		 //5融合值放入下一次待融合的数组fusion1[]中
		 for(i = 0; i < OBjTypeNum + 1; i++)
		 {
			  fusion1[i] = CoopFusion[i];           //当前融合值，作为下次融合的第一行值		 
		 }
         
//		k++;     //调整下一行的读取指针
	 }

	 //第22步：决策判断
	 for(i = 0; i < OBjTypeNum + 1; i++)//测试用
	 {
		 printf("融合值=%f  ", CoopFusion[i]);	
		 printf("类型次序=%d  ", Seri[i]);
	 }
	 printf("\n");
	 //对融合结果，从大到小排序
	 Get_Fusion_Data_Order(OBjTypeNum+1,CoopFusion,Seri,Decision);
	 for(i = 0; i < OBjTypeNum + 1; i++)//
	 {
		 printf("排后融合值=%f  ", Decision[i]);//最大值对应的类型即为识别的类型
		 printf("类型次序=%d  ", Seri[i]);	 
	 }	 
	 printf("\n");
	 *CPdere=CoopFusion[0];          //综合置信度为最大者
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
	VCT_sPlatType vctCooperPlatType; //合并信息的所有平台类型 
	VCT_sPlatType vctPlatType;      //筛选后，存放不同的平台类型


	VCT_CON vctcon;                 //关系矩阵存储容器
	int NumType,NumMsg;             //合并信息的所有平台类型数，证据条数
	int i;
	int tpflag;
	int Seri[10]={0};
	double con[50];
	double CPdere;      //综合置信度
	MIDENTIINFOR MidentStr;          //识别结果

	vctMidentiinforMsg.clear();//清空联合识别结果

 

	for (iteCoorMsg = vctCooperMsg.begin(); iteCoorMsg != vctCooperMsg.end();iteCoorMsg++)
	{  
		
		vctCooperPlatType.clear();
		vctPlatType.clear();
		tpflag = 0;
		//将同批号合并后的所有信息的平台类型都放到同一容器1中
        //以下三行: 测试合并信息的航迹,Comm,ESM的信息条数		
	    int TS = iteCoorMsg->vctTrace.size();  //若接收端相同,则信息条数为原请求信息的两倍
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
		//定义容器1的两个迭代器a,b 迭代器a用来遍历平台容器，迭代器b用来比较平台容器中迭代器a当前值和之前值是否有相同的
		//将不同的放入平台容器2中，平台容器2就是所求平台类型数
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
					//判断合并容器中前一个和后一个的平台类型是否相同，有相同，结束循环，循环结束若都不相同则放入平台容器中
					if (iteCPType2 != vctPlatType.end() && (strcmp(*iteCPType1, *iteCPType2) == 0))
					{
						//在合并容器中找到该平台类型，直接跳出循环
						break;
					}
					else if (iteCPType2 == vctPlatType.end())
					{
						//合并后的容器中没有找到，应该把该平台类型存入合并后的容器
						vctPlatType.push_back(*iteCPType2);
					}
				}//结束循环未找到相同的
			}	
		} 
		
		NumType = vctPlatType.size();  //识别类型数
		//test 以下8行测试 平台类型容器
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
//		NumType = testVctPlatType.size();  //识别类型数

		NumMsg = iteCoMessage->vctComm.size() + iteCoMessage->vctEsm.size() + iteCoMessage->vctTrace.size();//发射源证据数
//		NumMsg = iteCoMessage->nTraceN + iteCoMessage->nEsmN + iteCoMessage->nComN;//发射源证据数
		vctcon.clear(); //清空关系矩阵存储容器
//		copy(vctPlatType.begin(),vctPlatType.end(),testVctPlatType.begin());  //将v1复制到v2

		Coefficient(con, iteCoMessage, testVctPlatType);//关系矩阵
		for (i = 0; i < NumType; i++)
		{
			Seri[i] = i+1;
		}

		D_S(NumMsg, NumType, con, Seri, &CPdere);//DS证据识别

		MidentStr.lAutonum = iteCoorMsg->lAutonum;
		MidentStr.dConfidence = CPdere;
        int b = Seri[0] -1;
		MidentStr.sPlatType = vctPlatType[Seri[0]-1];
		vctMidentiinforMsg.push_back(MidentStr);//存入联合识别结果
   }

}
