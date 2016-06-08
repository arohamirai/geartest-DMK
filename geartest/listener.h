// Listener.h: interface for the CListener class.
// 
// The CListener class is derived from GrabberListener. It overwrites
// the "frameReady()" method. In the frameReady method, the method
// "saveImage()" is called.
// "saveImage()" saves the specified buffer to a BMP file and calls a "Sleep(250)" 
// to simulate time consuming image processing. "saveImage()" is also called
// by the main() function of this example to save all buffers that have
// not been processed in the frameReady method.
//
// This class also overwrites the overlayCallback method to draw a 
// frame counter.
//
// The CListener object is registered with the parameter 
// eFRAMEREADY|eOVERLAYCALLBACK . 
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LISTENER_H__3E017E1D_6B0A_472C_9F9C_0C5F9A8DFB23__INCLUDED_)
#define AFX_LISTENER_H__3E017E1D_6B0A_472C_9F9C_0C5F9A8DFB23__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "stdafx.h"

#include <stdlib.h>
#include <stdio.h>
#include "include/tisudshl.h"

#include "halconcpp.h"
#include "opencv2/opencv.hpp"
using namespace HalconCpp;
using namespace  cv;

#define MESSAGEDEVICELOST WM_USER+90


using namespace DShowLib;

// ֻ��һ�����ʱ��ʹ�øô�����
class CListenerSingle : public GrabberListener  
{
public:
		void SetViewCWnd( CWnd *pView);
		CListenerSingle();
		virtual ~CListenerSingle();
		virtual void deviceLost( Grabber& param); 
		void SetParent(CWnd* pParent);
		virtual void frameReady( Grabber& param, smart_ptr<MemBuffer> pBuffer, DWORD FrameNumber); 		

protected:
		CWnd* m_pParent;
		CWnd* m_pDrawCWnd;
		SIZE m_WindowSize;		// Size of the window in which to draw the buffer.
		void DrawBuffer( smart_ptr<MemBuffer> pBuffer);
		void DoImageProcessing( smart_ptr<MemBuffer> pBuffer);
				
public:
	// true for big model and false for small model, here the second param is not used
	bool InitShapeModel(int gearType, bool isBig);

	//////////////////////////////////////////////////////////////////////////
	/////////////////////////
private:
	HShapeModel m_modelBig;
	HShapeModel m_modelSmall;
	HObject m_modelContoursBig;
	HObject m_modelContoursSmall;
	HTuple m_distanceTransformBig;
	HTuple m_distanceTransformSmall;
private:
	int rb;
	int cb;
	int rs;
	int cs;
	int m_min;
	int m_max;
	unsigned char *m_inBuf;

	cv::Mat colorimg;

public:
	void xld2vector(cv::Mat &mat, HObject &xld, cv::Scalar color);
	void action(void);

};

//////////////////////////////////////////
//////////////////////////////////////////

//�ж�����ʱ��ʹ�øô�����
class CListenerMutil : public GrabberListener  
{
public:
	void SetViewCWnd( CWnd *pView);
	CListenerMutil();
	virtual ~CListenerMutil();
	virtual void deviceLost( Grabber& param); 
	void SetParent(CWnd* pParent);
	virtual void frameReady( Grabber& param, smart_ptr<MemBuffer> pBuffer, DWORD FrameNumber); 		

protected:
	CWnd* m_pParent;
	CWnd* m_pDrawCWnd;
	SIZE m_WindowSize;		// Size of the window in which to draw the buffer.
	void DrawBuffer( smart_ptr<MemBuffer> pBuffer);
	void DoImageProcessing( smart_ptr<MemBuffer> pBuffer);

public:
	// true for big model and false for small model
	bool InitShapeModel(int gearType, bool isBig);

	//////////////////////////////////////////////////////////////////////////
	/////////////////////////
private:
	HShapeModel m_model;
	HObject m_modelContours;
	HTuple m_distanceTransform;

private:
	int r;
	int c;
	int m_min;
	int m_max;
	unsigned char *m_inBuf;
	cv::Mat colorimg;
	BOOL m_IsBig;

public:
	void xld2vector(cv::Mat &mat, HObject &xld, cv::Scalar color);
	void action(void);

};
#endif // !defined(AFX_LISTENER_H__3E017E1D_6B0A_472C_9F9C_0C5F9A8DFB23__INCLUDED_)
