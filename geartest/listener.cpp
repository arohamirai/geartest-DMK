//////////////////////////////////////////////////////////////////////
// Listener.cpp: implementation of the CListenerSingle class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Listener.h"
#include "geartest.h"
//CvFont font;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CListenerSingle::CListenerSingle()
{
	m_pParent = NULL;
	m_pDrawCWnd = NULL;

	////////////////////////
	rb = 0;
	cb = 0;
	rs = 0;
	cs = 0;
	m_min = 3;
	m_max = 10;

	/*try
	{
		m_modelBig.ReadShapeModel(_T("ModelID.shm"));
		m_modelSmall.ReadShapeModel(_T("ModelID1.shm"));
	}
	catch(HException &except)
	{
		if (except.ErrorCode() == H_ERR_FNF)
		{
			MessageBox(NULL,_T("未发现模板文件，请检查并重试!"),NULL,NULL);
			return;

		}
	}
	GetShapeModelContours(&m_modelContoursBig, m_modelBig, 1);
	GetShapeModelContours(&m_modelContoursSmall, m_modelSmall, 1);
	CreateDistanceTransformXld(m_modelContoursBig, "point_to_segment", m_max, &m_distanceTransformBig);
	CreateDistanceTransformXld(m_modelContoursSmall, "point_to_segment", m_max, &m_distanceTransformSmall);*/
}

//////////////////////////////////////////////////////////////////////////

CListenerSingle::~CListenerSingle() 
{
}

//////////////////////////////////////////////////////////////////////////

void CListenerSingle::SetParent( CWnd *pParent)
{
	m_pParent = pParent;
}

//////////////////////////////////////////////////////////////////////////
// Notify parent, device is lost.
//////////////////////////////////////////////////////////////////////////

void CListenerSingle::deviceLost( Grabber& param) 
{
	if( m_pParent != NULL)
		m_pParent->PostMessage(MESSAGEDEVICELOST,0,0);
}

//////////////////////////////////////////////////////////////////////////
// Set the CWnd that will be used to render the resulting image.
//////////////////////////////////////////////////////////////////////////

void CListenerSingle::SetViewCWnd(CWnd *pView)
{
	m_pDrawCWnd = pView;
	RECT r;
	m_pDrawCWnd->GetClientRect(&r);
	m_WindowSize.cx = r.right;
	m_WindowSize.cy = r.bottom;
}
//////////////////////////////////////////////////////////////////////////
// Callback handler.
//////////////////////////////////////////////////////////////////////////

void CListenerSingle::frameReady( Grabber& param, smart_ptr<MemBuffer> pBuffer, DWORD FrameNumber)
{
	pBuffer->lock();
	DoImageProcessing( pBuffer );
	DrawBuffer(pBuffer);
	pBuffer->unlock();
}

//////////////////////////////////////////////////////////////////////////
// Draw the image buffer into the DrawCWnd.
//////////////////////////////////////////////////////////////////////////
///    对原有DrawBuffer函数的改造版本
void CListenerSingle::DrawBuffer( smart_ptr<MemBuffer> pBuffer)
{
	if( m_pDrawCWnd != NULL)
	{
		if( pBuffer != 0 )
		{ 
			
			CDC *pDC = m_pDrawCWnd->GetDC();
			pDC->SetStretchBltMode(COLORONCOLOR);

			smart_ptr<BITMAPINFOHEADER> pInf = pBuffer->getBitmapInfoHeader();

			//创建位图信息头，并用colorimg的图像数据填充该位图
			BITMAPINFOHEADER bitHeader;
			bitHeader.biSize = sizeof(BITMAPINFOHEADER);
			bitHeader.biWidth = colorimg.cols;
			bitHeader.biHeight = -colorimg.rows;
			bitHeader.biPlanes = 1;
			bitHeader.biBitCount = 24;
			bitHeader.biCompression = BI_RGB;
			bitHeader.biSizeImage = 0;  // zero for BI_RGB
			bitHeader.biXPelsPerMeter = pDC->GetDeviceCaps(LOGPIXELSX);
			bitHeader.biYPelsPerMeter = pDC->GetDeviceCaps(LOGPIXELSY);
			bitHeader.biClrUsed = 3;
			bitHeader.biClrImportant = 0; // zero for all use all colors

			BITMAPINFO bitMapInfo;
			bitMapInfo.bmiHeader = bitHeader;

			
			int nLines = StretchDIBits( 	pDC->GetSafeHdc(),// Handle to the device
											0, 
											0,
											m_WindowSize.cx,	// Dest. rectangle width.
											m_WindowSize.cy,	// Dest. rectangle height.
											0,				// X-coordinate of lower-left corner of the source rect.
											0,				// Y-coordinate of lower-left corner of the source rect.
											pInf->biWidth,//colorimg.cols,	// Source rectangle width.
											pInf->biHeight,//colorimg.rows, // Number of scan lines.
											colorimg.data,	// Modified address of array with DIB bits.
											reinterpret_cast<LPBITMAPINFO>( &bitMapInfo ),	// Address of structure with bitmap info.
											DIB_RGB_COLORS,	// RGB or palette indices.
											SRCCOPY
											);
			m_pDrawCWnd->ReleaseDC(pDC);
		}	
	}	
}
//////////////////////////////////////////////////////////////////////////
// The image processing is done here. For the sake of simplicity, the
// image data is inverted by this sample code.
//////////////////////////////////////////////////////////////////////////
//改造后的 DoImageProcessing ，处理过程都在action函数中
void CListenerSingle::DoImageProcessing( smart_ptr<MemBuffer> pBuffer)
{
	// Get the bitmap info header from the membuffer. It contains the bits per pixel,
	// width and height.
	smart_ptr<BITMAPINFOHEADER> pInf = pBuffer->getBitmapInfoHeader();

	BYTE* pImageData = pBuffer->getPtr();
	m_inBuf = pImageData;
	action();
}


// true for big model and false for small model
bool CListenerSingle::InitShapeModel(int gearType, bool isBig)
{
	//
	char *strModelBig, *strModelSmall;
	switch (gearType)
	{
	case BLUE_TYPE_01:
		{
			strModelBig = "blue_big_01.shm";
			strModelSmall = "blue_small_01.shm";
			break;
		}
		
	case BLUE_TYPE_02:
		{
			strModelBig ="blue_big_02.shm";
			strModelSmall = "blue_small_02.shm";
			break;
		}

	case BLUE_TYPE_03:
		{
			strModelBig = "blue_big_03.shm";
			strModelSmall = "blue_small_03.shm";
			break;
		}

	case YELLOW_TYPE_01:
		{
			strModelBig = "yellow_big_01.shm";
			strModelSmall = "yellow_small_01.shm";
			break;
		}
		
	case YELLOW_TYPE_02:
		{
			strModelBig = "yellow_big_02.shm";
			strModelSmall = "yellow_small_02.shm";
			break;
		}
		
		//********************************************//
		//********** 其他种类齿轮请自行添加 ***********//
	default:
		{
			strModelBig = "blue_big_01.shm";
			strModelSmall = "blue_small_01.shm";
			break;
		}
	}

	try
	{
		m_modelBig.ReadShapeModel(strModelBig);
		m_modelSmall.ReadShapeModel(strModelSmall);
	}
	catch(HException &except)
	{
		if (except.ErrorCode() == H_ERR_FNF)
		{
			MessageBox(NULL,_T("未发现模板文件，请检查并重试!"),NULL,NULL);
			return false;

		}
	}
	GetShapeModelContours(&m_modelContoursBig, m_modelBig, 1);
	GetShapeModelContours(&m_modelContoursSmall, m_modelSmall, 1);
	CreateDistanceTransformXld(m_modelContoursBig, "point_to_segment", m_max, &m_distanceTransformBig);
	CreateDistanceTransformXld(m_modelContoursSmall, "point_to_segment", m_max, &m_distanceTransformSmall);
	return true;
}
void CListenerSingle::action()
{
	// Local iconic variables
	HObject  ho_ImageSmooth;
	HObject  ho_Edges, ho_TransContours, ho__TransContours;
	HObject  ho_ContourOut, ho_ContourPart, ho__ContourPart;
	HObject  ho_TransContours1, ho__TransContours1;
	HObject  ho_ContourOut1, ho_ContourPart1, ho__ContourPart1;
	HObject  ho_UnionEdges;
	// Local control variables
	HTuple  hv_ModelRow, hv_ModelColumn;
	HTuple  hv_ModelAngle, hv_ModelScale, hv_ModelScore;
	HTuple  hv_HomMat, hv_HomMat2DInvert, hv_ModelRow1, hv_ModelColumn1;
	HTuple  hv_ModelAngle1, hv_ModelScale1, hv_ModelScore1;
	HTuple  hv_HomMat1, hv_HomMat2DInvert1;
	HTuple  hv_BigNum,hv_SmallNum;

	// colorimg 用于显示
	Mat srcimg(480,640,CV_8UC1,m_inBuf);
	cvtColor(srcimg, colorimg, CV_GRAY2RGB );
	
	// src 用于halcon中处理
	HImage src("byte",640,480,m_inBuf);
	SmoothImage(src, &ho_ImageSmooth, "gauss", 0.5);
	EdgesSubPix(ho_ImageSmooth, &ho_Edges, "canny", 1, 20, 40);
	UnionAdjacentContoursXld(ho_Edges,&ho_UnionEdges,10,1,"attr_keep");

	//////////////////////////////////////////////////////   big
	FindScaledShapeModel(ho_ImageSmooth, m_modelBig, HTuple(0).TupleRad(), HTuple(60).TupleRad(), 
		0.85, 1.15, 0.5, 1, 0.5, "least_squares", (HTuple(6).Append(1)), 0.75, &hv_ModelRow, 
		&hv_ModelColumn, &hv_ModelAngle, &hv_ModelScale, &hv_ModelScore);
	//Matching 01: transform the model contours into the detected positions
	if(hv_ModelScore.Length() != 0 )
	{
		rb = hv_ModelRow[0].D();
		cb = hv_ModelColumn[0].D();

		HomMat2dIdentity(&hv_HomMat);
		HomMat2dScale(hv_HomMat, HTuple(hv_ModelScale[0]), HTuple(hv_ModelScale[0]), 
			0, 0, &hv_HomMat);
		HomMat2dRotate(hv_HomMat, HTuple(hv_ModelAngle[0]), 0, 0, &hv_HomMat);
		HomMat2dTranslate(hv_HomMat, HTuple(hv_ModelRow[0]), HTuple(hv_ModelColumn[0]), 
			&hv_HomMat);

		// 显示匹配结果
		AffineTransContourXld(m_modelContoursBig, &ho_TransContours, hv_HomMat);
		xld2vector(colorimg,ho_TransContours,CV_RGB(0,255,0));

		//transate to model and distance transition
		HomMat2dInvert(hv_HomMat, &hv_HomMat2DInvert);
		AffineTransContourXld(ho_UnionEdges, &ho__TransContours, hv_HomMat2DInvert);
		ApplyDistanceTransformXld(ho__TransContours, &ho_ContourOut, m_distanceTransformBig);
		SegmentContourAttribXld(ho_ContourOut, &ho_ContourPart, "distance", "and", m_min, m_max-1);

		AffineTransContourXld(ho_ContourPart, &ho__ContourPart, hv_HomMat);
		//显示大齿轮检测结果
		CountObj(ho__ContourPart,&hv_BigNum);
		if (hv_BigNum.L() > 0)   
		{
			putText(colorimg,"Big is not OK",cvPoint(10,50),FONT_HERSHEY_SIMPLEX, 1.0,CV_RGB(255,0,0));
			xld2vector(colorimg,ho__ContourPart,CV_RGB(255,0,0));
		}
		else
		{
			putText(colorimg,"Big is OK",cvPoint(10,50),FONT_HERSHEY_SIMPLEX, 1.0,CV_RGB(0,255,0));
		}
	}
	else
	{  //若未匹配上，则重置匹配坐标到默认值
		rb = 100;
		cb = 100;
	}

	///////////////////////////////////////////////////////////  small
	FindScaledShapeModel(ho_ImageSmooth, m_modelSmall, HTuple(0).TupleRad(), HTuple(60).TupleRad(), 
		0.85, 1.15, 0.5, 1, 0.5, "least_squares", (HTuple(6).Append(1)), 0.75, &hv_ModelRow1, 
		&hv_ModelColumn1, &hv_ModelAngle1, &hv_ModelScale1, &hv_ModelScore1);
	//Matching 0: transform the model contours into the detected positions
	if(hv_ModelScore1.Length()!= 0)
	{
		rs = hv_ModelRow1[0].D();
		cs = hv_ModelColumn1[0].D();

		HomMat2dIdentity(&hv_HomMat1);
		HomMat2dScale(hv_HomMat1, HTuple(hv_ModelScale1[0]), HTuple(hv_ModelScale1[0]), 
			0, 0, &hv_HomMat1);
		HomMat2dRotate(hv_HomMat1, HTuple(hv_ModelAngle1[0]), 0, 0, 
			&hv_HomMat1);
		HomMat2dTranslate(hv_HomMat1, HTuple(hv_ModelRow1[0]), HTuple(hv_ModelColumn1[0]), 
			&hv_HomMat1);

		//显示匹配结果
		AffineTransContourXld(m_modelContoursSmall, &ho_TransContours1, hv_HomMat1);
		xld2vector(colorimg,ho_TransContours1,CV_RGB(0,255,0));


		//transate to model
		HomMat2dInvert(hv_HomMat1, &hv_HomMat2DInvert1);
		AffineTransContourXld(ho_UnionEdges, &ho__TransContours1, hv_HomMat2DInvert1);
		//distance transition
		ApplyDistanceTransformXld(ho__TransContours1, &ho_ContourOut1, m_distanceTransformSmall);
		SegmentContourAttribXld(ho_ContourOut1, &ho_ContourPart1, "distance", "and", m_min,m_max-1);

		// 显示小齿轮检测结果
		AffineTransContourXld(ho_ContourPart1, &ho__ContourPart1, hv_HomMat1);
		CountObj(ho__ContourPart1,&hv_SmallNum);
		if (hv_SmallNum.L() > 0)
		{
			putText(colorimg,"Small is not OK",cvPoint(10,100),FONT_HERSHEY_SIMPLEX, 1.0,CV_RGB(255,0,0));
			xld2vector(colorimg,ho__ContourPart1,CV_RGB(255,0,0));
		}
		else
		{
			putText(colorimg,"Small is OK",cvPoint(10,100),FONT_HERSHEY_SIMPLEX, 1.0,CV_RGB(0,255,0));
		}
	}
	else
	{
		rs = 100;
		cs = 100;
	}

	// 显示匹配的中心点
	int length = 20;
	line(colorimg,Point(cb- length,rb),Point(cb + length, rb),Scalar(0,0,255),2);
	line(colorimg,Point(cb , rb- length),Point(cb, rb + length),Scalar(0,0,255),2);
	circle(colorimg,Point(cs,rs),10,Scalar(0,255,0),3);	
}

void CListenerSingle::xld2vector(Mat &mat, HObject &xld, Scalar color)
{
	vector<vector<Point>> contours;
	HObject ho_xld;
	HTuple hv_Number,hv_Row,hv_Col;
	CountObj(xld, &hv_Number);
	int numObj = hv_Number.L();
	if (numObj > 0)
	{
		for (int i=1; i<=numObj; i++)
		{
			vector<Point> tempVec;
			SelectObj(xld, &ho_xld, i);
			GetContourXld(ho_xld, &hv_Row, &hv_Col);

			int numPoint =  hv_Col.Length();
			for (int j = 0; j < numPoint; j++)
			{
				tempVec.push_back(Point(hv_Col.DArr()[j],hv_Row.DArr()[j]));
			}
			contours.push_back(tempVec);
		}
		for (int i = 0; i < numObj; i ++)
		{
			drawContours(mat,contours,i-1,color);
		}
	}else
		return;
}


///////////////////////////////////////////////////////////////////////////
/*                                多相机版本                            */
/*                               CListenerMutil                         */
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CListenerMutil ::CListenerMutil ()
{
	m_pParent = NULL;
	m_pDrawCWnd = NULL;

	////////////////////////
	r = 0;
	c = 0;
	m_min = 3;
	m_max = 10;
}

//////////////////////////////////////////////////////////////////////////

CListenerMutil ::~CListenerMutil () 
{
}

//////////////////////////////////////////////////////////////////////////

void CListenerMutil ::SetParent( CWnd *pParent)
{
	m_pParent = pParent;
}

//////////////////////////////////////////////////////////////////////////
// Notify parent, device is lost.
//////////////////////////////////////////////////////////////////////////

void CListenerMutil ::deviceLost( Grabber& param) 
{
	if( m_pParent != NULL)
		m_pParent->PostMessage(MESSAGEDEVICELOST,0,0);
}

//////////////////////////////////////////////////////////////////////////
// Set the CWnd that will be used to render the resulting image.
//////////////////////////////////////////////////////////////////////////

void CListenerMutil ::SetViewCWnd(CWnd *pView)
{
	m_pDrawCWnd = pView;
	RECT r;
	m_pDrawCWnd->GetClientRect(&r);
	m_WindowSize.cx = r.right;
	m_WindowSize.cy = r.bottom;
}
//////////////////////////////////////////////////////////////////////////
// Callback handler.
//////////////////////////////////////////////////////////////////////////

void CListenerMutil ::frameReady( Grabber& param, smart_ptr<MemBuffer> pBuffer, DWORD FrameNumber)
{
	pBuffer->lock();
	DoImageProcessing( pBuffer );
	DrawBuffer(pBuffer);
	pBuffer->unlock();
}

//////////////////////////////////////////////////////////////////////////
// Draw the image buffer into the DrawCWnd.
//////////////////////////////////////////////////////////////////////////
///    对原有DrawBuffer函数的改造版本
void CListenerMutil ::DrawBuffer( smart_ptr<MemBuffer> pBuffer)
{
	if( m_pDrawCWnd != NULL)
	{
		if( pBuffer != 0 )
		{ 
			
			CDC *pDC = m_pDrawCWnd->GetDC();
			pDC->SetStretchBltMode(COLORONCOLOR);

			smart_ptr<BITMAPINFOHEADER> pInf = pBuffer->getBitmapInfoHeader();

			//创建位图信息头，并用colorimg的图像数据填充该位图
			BITMAPINFOHEADER bitHeader;
			bitHeader.biSize = sizeof(BITMAPINFOHEADER);
			bitHeader.biWidth = colorimg.cols;
			bitHeader.biHeight = -colorimg.rows;
			bitHeader.biPlanes = 1;
			bitHeader.biBitCount = 24;
			bitHeader.biCompression = BI_RGB;
			bitHeader.biSizeImage = 0;  // zero for BI_RGB
			bitHeader.biXPelsPerMeter = pDC->GetDeviceCaps(LOGPIXELSX);
			bitHeader.biYPelsPerMeter = pDC->GetDeviceCaps(LOGPIXELSY);
			bitHeader.biClrUsed = 3;
			bitHeader.biClrImportant = 0; // zero for all use all colors

			BITMAPINFO bitMapInfo;
			bitMapInfo.bmiHeader = bitHeader;

			
			int nLines = StretchDIBits( 	pDC->GetSafeHdc(),// Handle to the device
											0, 
											0,
											m_WindowSize.cx,	// Dest. rectangle width.
											m_WindowSize.cy,	// Dest. rectangle height.
											0,				// X-coordinate of lower-left corner of the source rect.
											0,				// Y-coordinate of lower-left corner of the source rect.
											pInf->biWidth,//colorimg.cols,	// Source rectangle width.
											pInf->biHeight,//colorimg.rows, // Number of scan lines.
											colorimg.data,	// Modified address of array with DIB bits.
											reinterpret_cast<LPBITMAPINFO>( &bitMapInfo ),	// Address of structure with bitmap info.
											DIB_RGB_COLORS,	// RGB or palette indices.
											SRCCOPY
											);
			m_pDrawCWnd->ReleaseDC(pDC);
		}	
	}	
}
//////////////////////////////////////////////////////////////////////////
// The image processing is done here. For the sake of simplicity, the
// image data is inverted by this sample code.
//////////////////////////////////////////////////////////////////////////
//改造后的 DoImageProcessing ，处理过程都在action函数中
void CListenerMutil ::DoImageProcessing( smart_ptr<MemBuffer> pBuffer)
{
	// Get the bitmap info header from the membuffer. It contains the bits per pixel,
	// width and height.
	smart_ptr<BITMAPINFOHEADER> pInf = pBuffer->getBitmapInfoHeader();

	BYTE* pImageData = pBuffer->getPtr();
	m_inBuf = pImageData;

	// 齿轮检测
	action();
}


// true for big model and false for small model
bool CListenerMutil ::InitShapeModel(int gearType, bool isBig)
{
	//
	char *strModel;
	if (isBig)
	{
		switch (gearType)
		{
		case BLUE_TYPE_01:
			{
				strModel = "blue_big_01.shm";
				break;
			}

		case BLUE_TYPE_02:
			{
				strModel ="blue_big_02.shm";
				break;
			}

		case BLUE_TYPE_03:
			{
				strModel = "blue_big_03.shm";
				break;
			}

		case YELLOW_TYPE_01:
			{
				strModel = "yellow_big_01.shm";
				break;
			}

		case YELLOW_TYPE_02:
			{
				strModel = "yellow_big_02.shm";
				break;
			}

			//********************************************//
			//********** 其他种类齿轮请自行添加 ***********//
		default:
			{
				strModel = "blue_big_01.shm";
				break;
			}
		}
	}
	else
	{
		switch (gearType)
		{
		case BLUE_TYPE_01:
			{
				strModel = "blue_small_01.shm";
				break;
			}

		case BLUE_TYPE_02:
			{
				strModel = "blue_small_02.shm";
				break;
			}

		case BLUE_TYPE_03:
			{
				strModel = "blue_small_03.shm";
				break;
			}

		case YELLOW_TYPE_01:
			{
				strModel = "yellow_small_01.shm";
				break;
			}

		case YELLOW_TYPE_02:
			{
				strModel = "yellow_small_02.shm";
				break;
			}

			//********************************************//
			//********** 其他种类齿轮请自行添加 ***********//
		default:
			{
				strModel = "blue_small_01.shm";
				break;
			}
		}
	}
	

	try
	{
		m_model.ReadShapeModel(strModel);
	}
	catch(HException &except)
	{
		if (except.ErrorCode() == H_ERR_FNF)
		{
			MessageBox(NULL,_T("未发现模板文件，请检查并重试!"),NULL,NULL);
			return false;

		}
	}
	GetShapeModelContours(&m_modelContours, m_model, 1);
	CreateDistanceTransformXld(m_modelContours, "point_to_segment", m_max, &m_distanceTransform);
	return true;
}
void CListenerMutil ::action()
{
	// Local iconic variables
	HObject  ho_ImageSmooth;
	HObject  ho_Edges, ho_TransContours, ho__TransContours;
	HObject  ho_ContourOut, ho_ContourPart, ho__ContourPart;
	HObject  ho_UnionEdges;
	// Local control variables
	HTuple  hv_ModelRow, hv_ModelColumn;
	HTuple  hv_ModelAngle, hv_ModelScale, hv_ModelScore;
	HTuple  hv_HomMat, hv_HomMat2DInvert;
	HTuple  hv_Num;

	// colorimg 用于显示
	Mat srcimg(480,640,CV_8UC1,m_inBuf);
	cvtColor(srcimg, colorimg, CV_GRAY2RGB );
	
	// src 用于halcon中处理
	HImage src("byte",640,480,m_inBuf);
	SmoothImage(src, &ho_ImageSmooth, "gauss", 0.5);
	EdgesSubPix(ho_ImageSmooth, &ho_Edges, "canny", 1, 20, 40);
	UnionAdjacentContoursXld(ho_Edges,&ho_UnionEdges,10,1,"attr_keep");

	FindScaledShapeModel(ho_ImageSmooth, m_model, HTuple(0).TupleRad(), HTuple(60).TupleRad(), 
		0.85, 1.15, 0.5, 1, 0.5, "least_squares", (HTuple(6).Append(1)), 0.75, &hv_ModelRow, 
		&hv_ModelColumn, &hv_ModelAngle, &hv_ModelScale, &hv_ModelScore);
	//Matching 01: transform the model contours into the detected positions
	if(hv_ModelScore.Length() != 0 )
	{
		r = hv_ModelRow[0].D();
		c = hv_ModelColumn[0].D();

		HomMat2dIdentity(&hv_HomMat);
		HomMat2dScale(hv_HomMat, HTuple(hv_ModelScale[0]), HTuple(hv_ModelScale[0]), 
			0, 0, &hv_HomMat);
		HomMat2dRotate(hv_HomMat, HTuple(hv_ModelAngle[0]), 0, 0, &hv_HomMat);
		HomMat2dTranslate(hv_HomMat, HTuple(hv_ModelRow[0]), HTuple(hv_ModelColumn[0]), 
			&hv_HomMat);

		//显示匹配结果
		AffineTransContourXld(m_modelContours, &ho_TransContours, hv_HomMat);
		xld2vector(colorimg,ho_TransContours,CV_RGB(0,255,0));

		//transate to model and distance transition
		HomMat2dInvert(hv_HomMat, &hv_HomMat2DInvert);
		AffineTransContourXld(ho_UnionEdges, &ho__TransContours, hv_HomMat2DInvert);
		ApplyDistanceTransformXld(ho__TransContours, &ho_ContourOut, m_distanceTransform);
		SegmentContourAttribXld(ho_ContourOut, &ho_ContourPart, "distance", "and", m_min, m_max-1);

		//显示齿轮检测结果
		AffineTransContourXld(ho_ContourPart, &ho__ContourPart, hv_HomMat);
		CountObj(ho__ContourPart,&hv_Num);
		//显示不合格部分
		if (hv_Num.L()> 0)
		{
			putText(colorimg,"not OK",cvPoint(10,50),FONT_HERSHEY_SIMPLEX, 1.0,CV_RGB(255,0,0));
			xld2vector(colorimg,ho__ContourPart,CV_RGB(255,0,0));
		}
		else
		{
			putText(colorimg,"OK",cvPoint(10,50),FONT_HERSHEY_SIMPLEX, 1.0,CV_RGB(0,255,0));
		}
	}
	else
	{  //若未匹配上，则重置匹配坐标到默认值
		r = 100;
		c = 100;
	}

	// 显示匹配中心位置
	int length = 20;
	line(colorimg,Point(c- length,r),Point(c + length, r),Scalar(0,0,255),2);
	line(colorimg,Point(c , r- length),Point(c, r + length),Scalar(0,0,255),2);
}

void CListenerMutil ::xld2vector(Mat &mat, HObject &xld, Scalar color)
{
	vector<vector<Point>> contours;
	HObject ho_xld;
	HTuple hv_Number,hv_Row,hv_Col;
	CountObj(xld, &hv_Number);
	int numObj = hv_Number.L();
	if (numObj > 0)
	{
		for (int i=1; i<=numObj; i++)
		{
			vector<Point> tempVec;
			SelectObj(xld, &ho_xld, i);
			GetContourXld(ho_xld, &hv_Row, &hv_Col);

			int numPoint =  hv_Col.Length();
			for (int j = 0; j < numPoint; j++)
			{
				tempVec.push_back(Point(hv_Col.DArr()[j],hv_Row.DArr()[j]));
			}
			contours.push_back(tempVec);
		}
		for (int i = 0; i < numObj; i ++)
		{
			drawContours(mat,contours,i-1,color);
		}
	}else
		return;
}