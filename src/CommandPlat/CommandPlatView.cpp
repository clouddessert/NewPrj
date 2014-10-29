// CommandPlatView.cpp : implementation of the CCommandPlatView class
//

#include "stdafx.h"
#include "CommandPlat.h"

#include "CommandPlatDoc.h"
#include "CommandPlatView.h"

#include "gs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////
extern CCommandPlatApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CCommandPlatView

IMPLEMENT_DYNCREATE(CCommandPlatView, CView)

BEGIN_MESSAGE_MAP(CCommandPlatView, CView)
	//{{AFX_MSG_MAP(CCommandPlatView)
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	// Standard printing commands
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCommandPlatView construction/destruction

CCommandPlatView::CCommandPlatView()
{
	// TODO: add construction code here

}

CCommandPlatView::~CCommandPlatView()
{
}

BOOL CCommandPlatView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CCommandPlatView drawing

#define LEFT_LONGIT 115.8 //左边经度
#define RIGHT_LONGIT 123.5//右边经度
#define UP_LATI 27.8   //上边纬度
#define DOWN_LATI 21.5//下边纬度

// #define LEFT_LONGIT 115.7 //左边经度
// #define RIGHT_LONGIT 123.3//右边经度
// #define UP_LATI 27.9  //上边纬度
// #define DOWN_LATI 21.1  //下边纬度

// #define LEFT_LONGIT 115.9 //左边经度   
// #define RIGHT_LONGIT 123//右边经度
// #define UP_LATI 27.9   //上边纬度
// #define DOWN_LATI 21//下边纬度

// #define LEFT_LONGIT 115 //左边经度
// #define RIGHT_LONGIT 123.1//右边经度   
// #define UP_LATI 27   //上边纬度
// #define DOWN_LATI 21.8  //下边纬度

// #define LEFT_LONGIT 115.9 //左边经度
// #define RIGHT_LONGIT 123.1//右边经度 ????  
// #define UP_LATI 27.9   //上边纬度    
// #define DOWN_LATI 20.1//下边纬度

// #define LEFT_LONGIT 115.7//左边经度
// #define RIGHT_LONGIT 123.7//右边经度   
// #define UP_LATI 27   //上边纬度
// #define DOWN_LATI 21//下边纬度

// #define LEFT_LONGIT 115.1 //左边经度 
// #define RIGHT_LONGIT 123.4//右边经度??????
// #define UP_LATI 27.9   //上边纬度
// #define DOWN_LATI 21.8//下边纬度    

// #define LEFT_LONGIT 115.8 //左边经度
// #define RIGHT_LONGIT 123.1//右边经度?????
// #define UP_LATI 27.8   //上边纬度
// #define DOWN_LATI 21.1 //下边纬度

// #define LEFT_LONGIT 112.4//左边经度
// #define RIGHT_LONGIT 123.6//右边经度
// #define UP_LATI 27.4  //上边纬度  
// #define DOWN_LATI 21.5//下边纬度

// #define LEFT_LONGIT 115.8 //左边经度
// #define RIGHT_LONGIT 123.5//右边经度
// #define UP_LATI 27.8   //上边纬度
// #define DOWN_LATI 21.5//下边纬度

// #define LEFT_LONGIT 115.8 //左边经度
// #define RIGHT_LONGIT 123.6//右边经度
// #define UP_LATI 27.8   //上边纬度
// #define DOWN_LATI 21.2//下边纬度

// #define LEFT_LONGIT 115.9//左边经度
// #define RIGHT_LONGIT 123.1 //右边经度 ???? 
// #define UP_LATI 27.1  //上边纬度
// #define DOWN_LATI 21.8 //下边纬度

// #define LEFT_LONGIT 115.6 //左边经度
// #define RIGHT_LONGIT 123.5 //右边经度
// #define UP_LATI 30    //上边纬度
// #define DOWN_LATI 21.8   //下边纬度

// #define LEFT_LONGIT 115 //左边经度
// #define RIGHT_LONGIT 123 //右边经度??????????????
// #define UP_LATI 27    //上边纬度
// #define DOWN_LATI 21   //下边纬度

void CCommandPlatView::OnDraw(CDC* pDC)
{
	CCommandPlatDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here	 

	GetClientRect(&ClientRect);
	TaiwanMap.LoadBitmap(IDB_SEA_MAP);
	TaiwanMap.GetObject(sizeof(BITMAP), &bBitMap);
	
	MemDc.CreateCompatibleDC(pDC);
	MemDc.SelectObject(&TaiwanMap);
	TaiwanMap.DeleteObject();
	
	//设置复制模式
	pDC->SetStretchBltMode(HALFTONE);
	pDC->SetBrushOrg(0, 0);

	DrawLines(&MemDc, bBitMap, ClientRect);  //画网格线

    CRect rect;
    GetClientRect(&rect);

 	   if (!theApp.m_Trace_Dat.empty())
	   {
		   for ( pTrace_Dat = theApp.m_Trace_Dat.begin(); pTrace_Dat != theApp.m_Trace_Dat.end(); pTrace_Dat++)
		   {
			   if (strcmp(pTrace_Dat->cPlatName,"飞机1")  == 0)
			   {
				   CDC MemDc123;         //用作缓冲作图的内存DC，定义一个显示位图对象
				   CBitmap bmp/*,bmp2*/;          //内存中承载临时图像的位图,定义位图对象
				   BITMAP bmpInfo/*,bmpInfo2*/;
				   bmp.LoadBitmap(IDB_PLANE);
				   bmp.GetObject(sizeof(bmpInfo), &bmpInfo);
				   MemDc123.CreateCompatibleDC(pDC);  
				   CBitmap* pOldBitmap = MemDc123.SelectObject(&bmp);
				   m_TmpPt.x = (LONG)(bBitMap.bmWidth/*rect.Width()*/*(pTrace_Dat->dLonti-LEFT_LONGIT)/(RIGHT_LONGIT-LEFT_LONGIT));
				   m_TmpPt.y = (LONG)(bBitMap.bmHeight/*rect.Height()*/*(UP_LATI-pTrace_Dat->dLati)/(UP_LATI-DOWN_LATI));
				   MemDc.BitBlt(m_TmpPt.x, m_TmpPt.y, bmpInfo.bmWidth, bmpInfo.bmHeight, &MemDc123, 0, 0, SRCCOPY); 
				   MemDc123.DeleteDC(); 
			   }

			   if (strcmp(pTrace_Dat->cPlatName,"飞机2")  == 0)
			   {   
				   CDC MemDc123;         //用作缓冲作图的内存DC，定义一个显示位图对象
				   CBitmap bmp/*,bmp2*/;          //内存中承载临时图像的位图,定义位图对象
				   BITMAP bmpInfo/*,bmpInfo2*/;
				   bmp.LoadBitmap(IDB_PLANE);
				   bmp.GetObject(sizeof(bmpInfo), &bmpInfo);
				   MemDc123.CreateCompatibleDC(pDC);  
				   CBitmap* pOldBitmap = MemDc123.SelectObject(&bmp);
				   m_TmpPt.x = (LONG)(bBitMap.bmWidth/*rect.Width()*/*(pTrace_Dat->dLonti-LEFT_LONGIT)/(RIGHT_LONGIT-LEFT_LONGIT));
				   m_TmpPt.y = (LONG)(bBitMap.bmHeight/*rect.Height()*/*(UP_LATI-pTrace_Dat->dLati)/(UP_LATI-DOWN_LATI));
				   MemDc.BitBlt(m_TmpPt.x, m_TmpPt.y, bmpInfo.bmWidth, bmpInfo.bmHeight, &MemDc123, 0, 0, SRCCOPY); 
				   MemDc123.DeleteDC(); 
			   }
			   
			   if (strcmp(pTrace_Dat->cPlatName,"导弹")  == 0)
			   {
				   CDC MemDc123;         //用作缓冲作图的内存DC，定义一个显示位图对象
				   CBitmap bmp/*,bmp2*/;          //内存中承载临时图像的位图,定义位图对象
				   BITMAP bmpInfo/*,bmpInfo2*/;
				   bmp.LoadBitmap(IDB_MISSILE);
				   bmp.GetObject(sizeof(bmpInfo), &bmpInfo);
				   MemDc123.CreateCompatibleDC(pDC);  
				   CBitmap* pOldBitmap = MemDc123.SelectObject(&bmp);
				   m_TmpPt.x = (LONG)(bBitMap.bmWidth/*rect.Width()*/*(pTrace_Dat->dLonti-LEFT_LONGIT)/(RIGHT_LONGIT-LEFT_LONGIT));
				   m_TmpPt.y = (LONG)(bBitMap.bmHeight/*rect.Height()*/*(UP_LATI-pTrace_Dat->dLati)/(UP_LATI-DOWN_LATI));
				   MemDc.BitBlt(m_TmpPt.x, m_TmpPt.y, bmpInfo.bmWidth, bmpInfo.bmHeight, &MemDc123, 0, 0, SRCCOPY); 
				   MemDc123.DeleteDC(); 		   
			   }
			   
			   if (strcmp(pTrace_Dat->cPlatName,"舰艇")  == 0)
			   {
				   CDC MemDc123;         //用作缓冲作图的内存DC，定义一个显示位图对象
				   CBitmap bmp/*,bmp2*/;          //内存中承载临时图像的位图,定义位图对象
				   BITMAP bmpInfo/*,bmpInfo2*/;
				   bmp.LoadBitmap(IDB_SHIP1);
				   bmp.GetObject(sizeof(bmpInfo), &bmpInfo);
				   MemDc123.CreateCompatibleDC(pDC);  
				   CBitmap* pOldBitmap = MemDc123.SelectObject(&bmp);
				   m_TmpPt.x = (LONG)(bBitMap.bmWidth/*rect.Width()*/*(pTrace_Dat->dLonti-LEFT_LONGIT)/(RIGHT_LONGIT-LEFT_LONGIT));
				   m_TmpPt.y = (LONG)(bBitMap.bmHeight/*rect.Height()*/*(UP_LATI-pTrace_Dat->dLati)/(UP_LATI-DOWN_LATI));
				   MemDc.BitBlt(m_TmpPt.x, m_TmpPt.y, bmpInfo.bmWidth, bmpInfo.bmHeight, &MemDc123, 0, 0, SRCCOPY); 
				   MemDc123.DeleteDC(); 		   
			   }	  
		   }
	   }

		   for ( pShip_Position = theApp.m_Ship_Position.begin(); pShip_Position != theApp.m_Ship_Position.end(); pShip_Position++)
		   {
				   CDC MemDc4;         //用作缓冲作图的内存DC，定义一个显示位图对象
				   CBitmap bmp2/*,bmp2*/;          //内存中承载临时图像的位图,定义位图对象
				   BITMAP bmpInfo2/*,bmpInfo2*/;
				   bmp2.LoadBitmap(IDB_SHIP1);
				   bmp2.GetObject(sizeof(bmpInfo2), &bmpInfo2);
				   MemDc4.CreateCompatibleDC(pDC);  
				   CBitmap* pOldBitmap = MemDc4.SelectObject(&bmp2);
				   m_TmpPt.x = (LONG)(bBitMap.bmWidth/*rect.Width()*/*(pShip_Position->dLonti-LEFT_LONGIT)/(RIGHT_LONGIT-LEFT_LONGIT));
				   m_TmpPt.y = (LONG)(bBitMap.bmHeight/*rect.Height()*/*(UP_LATI-pShip_Position->dLati)/(UP_LATI-DOWN_LATI));
				   MemDc.BitBlt(m_TmpPt.x, m_TmpPt.y, bmpInfo2.bmWidth, bmpInfo2.bmHeight, &MemDc4, 0, 0, SRCCOPY); 
				   MemDc4.DeleteDC(); 
		   }

	//复制图像
	pDC->StretchBlt(0, 0, ClientRect.Width(), ClientRect.Height(), &MemDc,
		0, 0, bBitMap.bmWidth, bBitMap.bmHeight, SRCCOPY);

	MemDc.DeleteDC();
}

/////////////////////////////////////////////////////////////////////////////
// CCommandPlatView printing

BOOL CCommandPlatView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCommandPlatView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCommandPlatView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CCommandPlatView diagnostics

#ifdef _DEBUG
void CCommandPlatView::AssertValid() const
{
	CView::AssertValid();
}

void CCommandPlatView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCommandPlatDoc* CCommandPlatView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCommandPlatDoc)));
	return (CCommandPlatDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCommandPlatView message handlers

void CCommandPlatView::DrawLines(CDC *pDc, BITMAP &Bm, CRect &Rect)
{
	/*画网格线*/
	CPen Pen;
	CPen *OldPen;//记录原始画笔
	Pen.CreatePen(PS_SOLID, 1, RGB(255, 255, 255));//画笔设置
	OldPen = pDc->SelectObject(&Pen);//将画笔选入设备描述表并记录原画笔

// 	int rectHeight	= Rect.bottom - Rect.top;
// 	int rectWidth = Rect.right - Rect.left;

	int rectHeight = Bm.bmHeight;
	int rectWidth = Bm.bmWidth;

	float longwidth = fabs(RIGHT_LONGIT - LEFT_LONGIT);  //经度跨度
	float latiwidth = fabs(DOWN_LATI - UP_LATI);         //纬度跨度

	float steplongwidth = rectWidth / longwidth;  //每度经度的宽
	float steplatiwidth = rectHeight / latiwidth; //每度纬度的宽

	double leftlongit = LEFT_LONGIT;
	double rightlongit = RIGHT_LONGIT;
	double uplati = UP_LATI;
	double downlati = DOWN_LATI;
	CString str;
	pDc->SetBkMode(TRANSPARENT);//设置背景色为透明
    CFont NewFont;
	NewFont.CreateFont(5,5,0,0,
		FW_DONTCARE,
		FALSE,FALSE,FALSE,
		DEFAULT_CHARSET,
		OUT_CHARACTER_PRECIS,
		CLIP_CHARACTER_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH|FF_DONTCARE,
		//"Times New Roman");  
		//"新宋体");
		"Fixedsys");      //设置字体类型
	
	CFont *pOldFont;
	pOldFont=pDc->SelectObject(&NewFont);
	pDc->SetTextColor(RGB(255, 255, 255));//设置白色字体
	//pDc->SetTextColor(RGB(0, 255, 0));//设置绿色字体

    int wrilongit = (int)leftlongit;
	double zrightlongit = floor (rightlongit); //右经度向下取整
	double zleftlongit = ceil (leftlongit);//左经度向上取整	
	double remainlongit = (zleftlongit - leftlongit)*steplongwidth;

	if (leftlongit != (int)leftlongit) //判断左经度是否为整数，为小数时
	{
		for (int m = 0; m <= zrightlongit - zleftlongit; m++)  //右经度为小数时，显示向下取整之后的数
		{
			pDc->MoveTo((int)(Rect.left + remainlongit + m*steplongwidth),(int)Rect.top );
			pDc->LineTo((int)(Rect.left + remainlongit + m*steplongwidth),Rect.top + rectHeight );
			wrilongit = wrilongit + 1; 
			
			//str.Format("%.1f", (float)wrilongit); //标经度
			str.Format("%d", wrilongit);
			if (m<zrightlongit - zleftlongit )
			{
				pDc->TextOut(Rect.left + remainlongit + m*steplongwidth,Rect.top,str);
		    	pDc->TextOut(Rect.left + remainlongit + m*steplongwidth,Rect.top + rectHeight*0.98,str);
			}
			else
			{
  //标经度  (标最下面一个经度时)
				pDc->TextOut((Rect.left + remainlongit + m*steplongwidth)*0.96,Rect.top,str);
		    	pDc->TextOut((Rect.left + remainlongit + m*steplongwidth)*0.96,Rect.top + rectHeight*0.98,str);
			}		
		}

	}
	else  //左边经度为整数时
	{
		for (int m = 0; m <= zrightlongit - leftlongit +1 ; m++)
		{
			pDc->MoveTo((int)(Rect.left + m*steplongwidth),Rect.top );
			pDc->LineTo((int)(Rect.left + m*steplongwidth),Rect.top + rectHeight );
			wrilongit = wrilongit + 1;		
			//str.Format("%.1f", (float)wrilongit); //标经度
			str.Format("%d", wrilongit); //标经度

			//判断右经度若为小数差值小于0.5，则标最右经度向左移
			if (rightlongit - zrightlongit <= 0.5)
			{
				if(m>=zrightlongit-leftlongit-1)//标最右经度
				{
					pDc->TextOut((int)(Rect.left + (m+1)*steplongwidth)*0.95,Rect.top,str);	
			        pDc->TextOut((int)(Rect.left + (m+1)*steplongwidth)*0.95,Rect.top + rectHeight*0.98 ,str);	
				}
				else   
				{	pDc->TextOut((int)(Rect.left + (m+1)*steplongwidth),Rect.top,str);	
		        	pDc->TextOut((int)(Rect.left + (m+1)*steplongwidth),Rect.top + rectHeight*0.98 ,str);
				}
			}
			else
			{
			pDc->TextOut((int)(Rect.left + (m+1)*steplongwidth),Rect.top,str);	
			pDc->TextOut((int)(Rect.left + (m+1)*steplongwidth),Rect.top + rectHeight*0.98 ,str);	
			}	
		}
	}

	int wriuplati = (int)uplati;
	double zuplati = floor ( uplati); //上纬度向下取整
	double zdownlati = ceil ( downlati);//下纬度向上取整

	if (uplati != (int)uplati) //判断上边纬度是否为整数，为小数时
	{
		double remainlati = (uplati - zuplati)*steplatiwidth;
        wriuplati = wriuplati + 1;
		for (int k = 0; k <= zuplati - zdownlati + 1; k++)
		{
			pDc->MoveTo(Rect.left,Rect.top + remainlati + k*steplatiwidth);
			pDc->LineTo(Rect.left + rectWidth,Rect.top + remainlati + k*steplatiwidth);
			wriuplati = wriuplati - 1; 
			if (k < zuplati - zdownlati ) // 判断是否是最下边纬度，若不为最下边纬度
			{
				//str.Format("%.1f", (float)wriuplati); //标纬度
				str.Format("%d", wriuplati);  //标纬度 
				//判左经度是否为xx.9 xx.8
				if (fabs(leftlongit - zleftlongit) <= 0.29)
				{
				     pDc->TextOut(Rect.left + rectWidth*0.03, Rect.top + remainlati + k*steplatiwidth,str);
				 				if (0.25<=(rightlongit-zrightlongit)&&(rightlongit-zrightlongit)<0.5)
							//	if(0.25<=(rightlongit-zrightlongit)<0.5)
								{ //判断右经度是否为.2 xx.3或xx.4
                                  pDc->TextOut(Rect.left + rectWidth*0.94, Rect.top + remainlati + k*steplatiwidth,str);
								}
								else
								{ 
								  pDc->TextOut(Rect.left + rectWidth*0.97, Rect.top + remainlati+ k*steplatiwidth,str);
								}

				}
 				else //左经度不为xx.9 xx.8
				{
 			    	pDc->TextOut(Rect.left,Rect.top + remainlati + k*steplatiwidth,str);	 
					        //if (0.25<=(rightlongit-zrightlongit)<0.5)  // (rightlongit-zrightlongit)>=0.25&&(rightlongit-zrightlongit)<0.5
						    if(0.25<=(rightlongit-zrightlongit)&&(rightlongit-zrightlongit)<0.5)
							{ //判断右经度是否为.2 xx.3或xx.4
					      	  pDc->TextOut(Rect.left + rectWidth*0.94, Rect.top + remainlati + k*steplatiwidth,str);
							}
				    	    else
							{ 
							  pDc->TextOut(Rect.left + rectWidth*0.97, Rect.top + remainlati+ k*steplatiwidth,str); 
							}
 				}
			}
			else
			{
                str.Format("%d", wriuplati);  //标纬度 (标最下面的左右纬度)
				if (fabs(leftlongit - zleftlongit) <= 0.29) //判断左经度是否为xxx.9  xxx.8
 				{
					pDc->TextOut(Rect.left + rectWidth*0.03, (Rect.top + remainlati + k*steplatiwidth)/**0.98*/,str);	
					//if (0.01<=(rightlongit-zrightlongit)<0.5) //(rightlongit-zrightlongit)>=0.01&&(rightlongit-zrightlongit)<0.5
					if (0.01<=(rightlongit-zrightlongit)&&(rightlongit-zrightlongit)<0.5)
					{ //判断右经度是否为.1.2 xx.3或xx.4
    					pDc->TextOut(Rect.left + rectWidth*0.94, Rect.top + remainlati + k*steplatiwidth/**0.96*/,str);
					}
					else
					{
// 需判断一下是否写最后一个右纬度
// 						if(k+1 < zuplati - zdownlati)
// 						{
//         //                    pDc->TextOut(Rect.left+ rectWidth*0.02, (Rect.top + (k+1)*steplatiwidth)/**0.98*/,str);
// 						}
//  						else
//  						{
//     //					      pDc->TextOut(Rect.left+ rectWidth*0.02, (Rect.top + (k+1)*steplatiwidth)*0.98,str);
// 						}

// 
				  // if( 0.05<(rightlongit-zrightlongit)<0.4 ) //(rightlongit-zrightlongit)>0.05&&(rightlongit-zrightlongit)<0.4
					if( 0.05<(rightlongit-zrightlongit)&&(rightlongit-zrightlongit)<0.4)
					{
						pDc->TextOut(Rect.left + rectWidth*0.97, (Rect.top + remainlati+ k*steplatiwidth)*0.98,str);
					}
					else{
						pDc->TextOut(Rect.left + rectWidth*0.94, (Rect.top + remainlati+ k*steplatiwidth)/**0.98*/,str);}
					}
				}
				else
				{
		        	pDc->TextOut(Rect.left,(Rect.top + remainlati + k*steplatiwidth),str);	
				//	if (0.25<=(rightlongit-zrightlongit)<0.5)//(rightlongit-zrightlongit)>=0.25&&(rightlongit-zrightlongit)<0.5
					if(0.25<=(rightlongit-zrightlongit)&&(rightlongit-zrightlongit)<0.5)
					{ //判断右经度是否为.2 xx.3或xx.4
						pDc->TextOut(Rect.left + rectWidth*0.94, Rect.top + remainlati + k*steplatiwidth,str);
					}
					else
					{
				     	pDc->TextOut(Rect.left + rectWidth*0.97, Rect.top + remainlati+ k*steplatiwidth,str);
					}
				}
			}	
		}
	}
	else  //上纬度为整数
	{		
		double zzdownlati = ceil ( downlati);//下纬度向上取整
		//wriuplati = wriuplati - 1;
		for (int k = 0; k <= uplati - zzdownlati + 1; k++)
		{
			pDc->MoveTo(Rect.left, Rect.top + k*steplatiwidth);
			pDc->LineTo(Rect.left + rectWidth, Rect.top + k*steplatiwidth);
			wriuplati = wriuplati - 1; 
		    str.Format("%d", wriuplati);  //标纬度 
			//判左经度是否为xx.9 xx.8
			if (fabs(leftlongit - zleftlongit) <= 0.2)
			{ //写左边的纬度往右移
			  //判断是否写左边最后一个纬度       
// 需判断一下是否写最后一个纬度 
				     if(k+1 < zuplati - zdownlati)
					 {
						 pDc->TextOut(Rect.left+ rectWidth*0.02, (Rect.top + (k+1)*steplatiwidth),str);
					 }
			         else
					 {
						 pDc->TextOut(Rect.left+ rectWidth*0.02, (Rect.top + (k+1)*steplatiwidth)*0.96,str);
					 }
			  //if (0.25<=(rightlongit-zrightlongit)<0.5) //(rightlongit-zrightlongit)>=0.25&&(rightlongit-zrightlongit)<0.5
			  if(0.25<=(rightlongit-zrightlongit)&&(rightlongit-zrightlongit)<0.5)
			   { //判断右经度是否为xx.2或xx.3或xx.4
//需判断一下是否写最后一个纬度 // pDc->TextOut(Rect.left + rectWidth*0.94, Rect.top + (k+1)*steplatiwidth,str);
				      if(k+1 < zuplati - zdownlati)
				      {
						  pDc->TextOut(Rect.left + rectWidth*0.94, Rect.top + (k+1)*steplatiwidth,str);
					  }
				      else
				      {
						  pDc->TextOut(Rect.left + rectWidth*0.94, (Rect.top + (k+1)*steplatiwidth)*0.96,str);
					  }
			   }
			   else
			   {
//需判断一下是否写最后一个纬度
				 //  pDc->TextOut(Rect.left + rectWidth*0.97, Rect.top + (k+1)*steplatiwidth,str);
				      if(k+1< zuplati - zdownlati)
				      {
						  pDc->TextOut(Rect.left + rectWidth*0.97, (Rect.top + (k+1)*steplatiwidth)/**0.98*/,str);
					  }
				      else
				      {
						  pDc->TextOut(Rect.left + rectWidth*0.97, (Rect.top + (k+1)*steplatiwidth)*0.98,str);
					  }
			   }
			 }
			else
			{//左边经度不为xx.9时，在最左边写左纬度
				pDc->TextOut(Rect.left,(int)(Rect.top + (k+1)*steplatiwidth),str);	
				//if (0.25<=(rightlongit-zrightlongit)<0.5)//(rightlongit-zrightlongit)>=0.25&&(rightlongit-zrightlongit)<0.5
			    if(0.25<=(rightlongit-zrightlongit)&&(rightlongit-zrightlongit)<0.5)
			   { //判断右经度是否为xx.2或xx.3或xx.4
//需判断一下是否写最后一个纬度
				  pDc->TextOut(Rect.left + rectWidth*0.94, (Rect.top + (k+1)*steplatiwidth),str);
			   }
		    	else
				{
//需判断一下是否写最后一个纬度
				  pDc->TextOut(Rect.left + rectWidth*0.97, (Rect.top + (k+1)*steplatiwidth),str);
				}
			}
		}
	}
    pDc->SelectObject(OldPen);//恢复原来的画笔		
}




BOOL CCommandPlatView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	GetClientRect(&ClientRect);
	TaiwanMap.LoadBitmap(IDB_SEA_MAP);
	TaiwanMap.GetObject(sizeof(BITMAP), &bBitMap);
	
	MemDc.CreateCompatibleDC(pDC);
	MemDc.SelectObject(&TaiwanMap);
	TaiwanMap.DeleteObject();
	
	//设置复制模式
	pDC->SetStretchBltMode(HALFTONE);
	pDC->SetBrushOrg(0, 0);

	//复制图像
	pDC->StretchBlt(0, 0, ClientRect.Width(), ClientRect.Height(), &MemDc,
		0, 0, bBitMap.bmWidth, bBitMap.bmHeight, SRCCOPY);

	MemDc.DeleteDC();
	DrawLines(pDC, bBitMap, ClientRect);

	return(TRUE);
}



void CCommandPlatView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	std::map<DWORD, SHIP_POSITION>::iterator pxx_tmp;
	
	VCT_ESM_MSG::iterator pESM_Dat;
	VCT_COMM_MSG::iterator pComm_Dat;
	VCT_TRACE_MSG::iterator pTrace_Dat;

	std::map<DWORD, ST_ALL_MSG>::iterator p_tmp_it;

	OriginGEO stRef;
	PositionGEO	stVal;
	PositionPolar stOut;
	
	int tmp_val;

	if (nIDEvent == 5)
	{
		//updata Data
		::EnterCriticalSection(&(theApp.g_cs));
		for (pESM_Dat = theApp.m_ESM_Dat.begin(); pESM_Dat != theApp.m_ESM_Dat.end(); pESM_Dat++)
		{
			tmp_val = pESM_Dat->lAutonum;
			for (pTrace_Dat = theApp.m_Trace_Dat.begin(); pTrace_Dat != theApp.m_Trace_Dat.end(); pTrace_Dat++)
			{
				if ( tmp_val == pTrace_Dat->lTargetNumber )
				{
					break;
				}
			}
			if (pTrace_Dat != theApp.m_Trace_Dat.end())
			{
				pESM_Dat->dElevationAngle = pTrace_Dat->dElevationAngle;
				pESM_Dat->dReachAzimuth = pTrace_Dat->dAzimuth;
			}
		
			tmp_val = rand();
			pESM_Dat->dReachAzimuth += (tmp_val>(RAND_MAX/2)?(0.01*tmp_val/RAND_MAX):(-0.01*tmp_val/RAND_MAX));
			tmp_val = rand();
			pESM_Dat->dElevationAngle += (tmp_val>(RAND_MAX/2)?(0.01*tmp_val/RAND_MAX):(-0.01*tmp_val/RAND_MAX));
			pESM_Dat->lSignalReachTime = pESM_Dat->lSignalReachTime + 1;
		}

		//update data for all ship
		for (p_tmp_it = theApp.m_AllShipMsg.begin(); p_tmp_it != theApp.m_AllShipMsg.end(); p_tmp_it++)
		{
			for (pESM_Dat = p_tmp_it->second.m_ESM_Dat.begin(); pESM_Dat != p_tmp_it->second.m_ESM_Dat.end(); pESM_Dat++)
			{
				tmp_val = pESM_Dat->lAutonum;
				for (pTrace_Dat = p_tmp_it->second.m_Trace_Dat.begin(); pTrace_Dat != p_tmp_it->second.m_Trace_Dat.end(); pTrace_Dat++)
				{
					if ( tmp_val == pTrace_Dat->lTargetNumber )
					{
						break;
					}
				}
				if (pTrace_Dat != theApp.m_Trace_Dat.end())
				{
					pESM_Dat->dElevationAngle = pTrace_Dat->dElevationAngle;
					pESM_Dat->dReachAzimuth = pTrace_Dat->dAzimuth;
				}
				
				tmp_val = rand();
				pESM_Dat->dReachAzimuth += (tmp_val>(RAND_MAX/2)?(0.01*tmp_val/RAND_MAX):(-0.01*tmp_val/RAND_MAX));
				tmp_val = rand();
				pESM_Dat->dElevationAngle += (tmp_val>(RAND_MAX/2)?(0.01*tmp_val/RAND_MAX):(-0.01*tmp_val/RAND_MAX));
				pESM_Dat->lSignalReachTime = pESM_Dat->lSignalReachTime + 1;
			}	
		}
		::LeaveCriticalSection(&(theApp.g_cs));
		theApp.cMsgType = 1;
	}
	else if (nIDEvent == 6)
	{
		//updata Data
		::EnterCriticalSection(&(theApp.g_cs));
		for (pComm_Dat = theApp.m_Comm_Dat.begin(); pComm_Dat != theApp.m_Comm_Dat.end(); pComm_Dat++)
		{
			tmp_val = pComm_Dat->lAutonum;
			for (pTrace_Dat = theApp.m_Trace_Dat.begin(); pTrace_Dat != theApp.m_Trace_Dat.end(); pTrace_Dat++)
			{
				if ( tmp_val == pTrace_Dat->lTargetNumber )
				{
					break;
				}
			}
			
			if (pTrace_Dat != theApp.m_Trace_Dat.end())
			{
				pComm_Dat->dElevationAngle = pTrace_Dat->dElevationAngle;
				pComm_Dat->dReachAzimuth = pTrace_Dat->dAzimuth;
			}
		
			tmp_val = rand();
			pComm_Dat->dReachAzimuth += (tmp_val>(RAND_MAX/2)?(0.01*tmp_val/RAND_MAX):(-0.01*tmp_val/RAND_MAX));
			tmp_val = rand();
			pComm_Dat->dElevationAngle += (tmp_val>(RAND_MAX/2)?(0.01*tmp_val/RAND_MAX):(-0.01*tmp_val/RAND_MAX));
		}

		//update data for all ship
		for (p_tmp_it = theApp.m_AllShipMsg.begin(); p_tmp_it != theApp.m_AllShipMsg.end(); p_tmp_it++)
		{
			for (pComm_Dat = p_tmp_it->second.m_Comm_Dat.begin(); pComm_Dat != p_tmp_it->second.m_Comm_Dat.end(); pComm_Dat++)
			{
				tmp_val = pComm_Dat->lAutonum;
				for (pTrace_Dat = p_tmp_it->second.m_Trace_Dat.begin(); pTrace_Dat != p_tmp_it->second.m_Trace_Dat.end(); pTrace_Dat++)
				{
					if ( tmp_val == pTrace_Dat->lTargetNumber )
					{
						break;
					}
				}

				if (pTrace_Dat != theApp.m_Trace_Dat.end())
				{
					pComm_Dat->dElevationAngle = pTrace_Dat->dElevationAngle;
					pComm_Dat->dReachAzimuth = pTrace_Dat->dAzimuth;
				}

				tmp_val = rand();
				pComm_Dat->dReachAzimuth += (tmp_val>(RAND_MAX/2)?(0.01*tmp_val/RAND_MAX):(-0.01*tmp_val/RAND_MAX));
				tmp_val = rand();
				pComm_Dat->dElevationAngle += (tmp_val>(RAND_MAX/2)?(0.01*tmp_val/RAND_MAX):(-0.01*tmp_val/RAND_MAX));
			}	
		}
		::LeaveCriticalSection(&(theApp.g_cs));
		theApp.cMsgType = 2;
	}
	else if (nIDEvent == 7)
	{
		//updata Data
		::EnterCriticalSection(&(theApp.g_cs));
		for (pTrace_Dat = theApp.m_Trace_Dat.begin(); pTrace_Dat != theApp.m_Trace_Dat.end(); pTrace_Dat++)
		{
			pTrace_Dat->dAzimuth = pTrace_Dat->dAzimuth + 0.00015;
			pTrace_Dat->dLonti  = pTrace_Dat->dLonti  + 0.0015;
			pTrace_Dat->dLati  = pTrace_Dat->dLati  +0.0015;
			pTrace_Dat->dRange = pTrace_Dat->dRange +15.000;
			pTrace_Dat->dElevationAngle = pTrace_Dat->dElevationAngle +0.0015;
			pTrace_Dat->lSignalReachTime = pTrace_Dat->lSignalReachTime +1;
			pTrace_Dat->dTargetAZSpeed = pTrace_Dat->dTargetAZSpeed +0.001;
			pTrace_Dat->dTargetEAngleSpeed =pTrace_Dat->dTargetEAngleSpeed +0.001;
			pTrace_Dat->dTSpeedX = pTrace_Dat->dTSpeedX +0.001;
			pTrace_Dat->dTSpeedY = pTrace_Dat->dTSpeedY +0.001;
			pTrace_Dat->dTSpeedZ = pTrace_Dat->dTSpeedZ +0.001;
			pTrace_Dat->dTX = pTrace_Dat->dTX +0.01;
			pTrace_Dat->dTY = pTrace_Dat->dTY +0.01;
			pTrace_Dat->dTZ = pTrace_Dat->dTZ +0.01;
		}

		//update data for all ship
		for (p_tmp_it = theApp.m_AllShipMsg.begin(); p_tmp_it != theApp.m_AllShipMsg.end(); p_tmp_it++)
		{
			for (pTrace_Dat = p_tmp_it->second.m_Trace_Dat.begin(); pTrace_Dat != p_tmp_it->second.m_Trace_Dat.end(); pTrace_Dat++)
			{
				pTrace_Dat->dAzimuth = pTrace_Dat->dAzimuth + 0.00015;
				pTrace_Dat->dLonti  = pTrace_Dat->dLonti  + 0.0015;
				pTrace_Dat->dLati  = pTrace_Dat->dLati  +0.0015;
				pTrace_Dat->dRange = pTrace_Dat->dRange +15.000;
				pTrace_Dat->dElevationAngle = pTrace_Dat->dElevationAngle +0.0015;
				pTrace_Dat->lSignalReachTime = pTrace_Dat->lSignalReachTime +1;
				pTrace_Dat->dTargetAZSpeed = pTrace_Dat->dTargetAZSpeed +0.001;
				pTrace_Dat->dTargetEAngleSpeed =pTrace_Dat->dTargetEAngleSpeed +0.001;
				pTrace_Dat->dTSpeedX = pTrace_Dat->dTSpeedX +0.001;
				pTrace_Dat->dTSpeedY = pTrace_Dat->dTSpeedY +0.001;
				pTrace_Dat->dTSpeedZ = pTrace_Dat->dTSpeedZ +0.001;
				pTrace_Dat->dTX = pTrace_Dat->dTX +0.01;
				pTrace_Dat->dTY = pTrace_Dat->dTY +0.01;
				pTrace_Dat->dTZ = pTrace_Dat->dTZ +0.01;
				
				//calculate the rd
				pxx_tmp = theApp.m_ShipRelatePlat.find(p_tmp_it->first);
				if (pxx_tmp != theApp.m_ShipRelatePlat.end())
				{
					stRef.dRefLon_ = pxx_tmp->second.dLonti;
					stRef.dRefLat_ = pxx_tmp->second.dLati;
					stRef.dRefAlt_ = pxx_tmp->second.dHeight;
					
					stVal.dLongitude = pTrace_Dat->dLonti;
					stVal.dLatitude = pTrace_Dat->dLati;
					stVal.dAltitude = pTrace_Dat->dObjHeight;	//！！！
					
					stOut = GEO2Polar(stVal, stRef);
					
					pTrace_Dat->dRange = stOut.dRDistance;
					pTrace_Dat->dAzimuth = stOut.dAzimuth;
					pTrace_Dat->dElevationAngle = stOut.dHLowAngle;
				}
			}	
		}
		::LeaveCriticalSection(&(theApp.g_cs));
		theApp.cMsgType = 3;
	}
	else if (nIDEvent == 8)
	{
		//updata Data
		::EnterCriticalSection(&(theApp.g_cs));
		for (pShip_Position = theApp.m_Ship_Position.begin(); pShip_Position != theApp.m_Ship_Position.end(); pShip_Position++)
		{
			pShip_Position->dHeight = pShip_Position->dHeight ;
			pShip_Position->dLonti  = pShip_Position->dLonti  + 0.00001;
			pShip_Position->dLati  = pShip_Position->dLati  + 0.00001;
		}
		::LeaveCriticalSection(&(theApp.g_cs));
		theApp.cMsgType = 4;

		//Update the map
		::EnterCriticalSection(&(theApp.g_cs));
		for (pxx_tmp = theApp.m_ShipRelatePlat.begin(); pxx_tmp != theApp.m_ShipRelatePlat.end(); ++pxx_tmp)
		{
			pxx_tmp->second.dHeight = pxx_tmp->second.dHeight;
			pxx_tmp->second.dLonti  += 0.00001;
			pxx_tmp->second.dLati  += 0.00001;

		}
		::LeaveCriticalSection(&(theApp.g_cs));
	}
	else
	{

	}

	if (theApp.bThreadRun)
	{
		//notify the thread send data
	   ::SetEvent(theApp.hUpdateDataEvent);
	

		//update Map


		//update List
		::PostMessage(theApp.hESM_wmd, WM_ESM_MSG, 0, 0);
		::PostMessage(theApp.hCOMM_wmd, WM_COMM_MSG, 0, 0);
		::PostMessage(theApp.hTRACE_wmd, WM_TRACE_MSG, 0, 0);
	}

	//发送重绘消息
	Invalidate(FALSE);
	//SendMessage(WM_ERASEBKGND, 0, 0);
	
	CView::OnTimer(nIDEvent);
}

void CCommandPlatView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	SetTimer(5, 1000, NULL);	//ESM
	SetTimer(6, 500, NULL);		//Comm
	SetTimer(7, 500, NULL);		//Trace
	SetTimer(8, 500, NULL);     //ShipPosition
}
