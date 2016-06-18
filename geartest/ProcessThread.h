#pragma once


#include "listener.h"
// CProcessThread

class CProcessThread : public CWinThread
{
	DECLARE_DYNCREATE(CProcessThread)

public:
	CProcessThread();           // 动态创建所使用的受保护的构造函数
	virtual ~CProcessThread();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

public:
	DShowLib::Grabber		m_cGrabber; // The instance of the Grabber class.
	DShowLib::FrameHandlerSink::tFHSPtr           m_pSink;
	// 单个相机时，使用CListenerSingle类，多个相机时，使用CListenerMutil类， 并使CProcessThread::CProcessThread()中的语句生效
	CListenerSingle m_cListener;
	//CListenerMutil m_cListener;		// Image processing will be done by this object.

	CWnd *pParentWnd;
	CStatic *pShowStatic;

public:
	int OnLive(bool IsLive);
	bool InitShapeModel(int gearType);
	int m_cameraIndex;
	BOOL m_IsBig;

protected:
	DECLARE_MESSAGE_MAP()

};


