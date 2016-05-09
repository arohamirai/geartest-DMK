// ProcessThread.cpp : 实现文件
//

#include "stdafx.h"
#include "geartest.h"
#include "ProcessThread.h"
#include "geartestDLG.h"
#include "cameraParmFile.h"
// CProcessThread

IMPLEMENT_DYNCREATE(CProcessThread, CWinThread)

CProcessThread::CProcessThread()
: m_cameraIndex(0)
{
}

CProcessThread::~CProcessThread()
{
}

BOOL CProcessThread::InitInstance()
{
	// TODO: 在此执行任意逐线程初始化

	// Add the CListener object to the the Grabber object.
	
	m_cGrabber.addListener(&m_cListener);

	m_cListener.SetParent(pParentWnd);

	// Pass the video window to the listener, so it can draw in it.
	m_cListener.SetViewCWnd(pShowStatic);
	// Set the sink
	m_pSink = FrameHandlerSink::create(DShowLib::eRGB8,3);
	m_pSink->setSnapMode( false ); // Automatically copy every frame to the sink and call CListener::frameReady().
	m_cGrabber.setSinkType( m_pSink );

	if( m_cGrabber.loadDeviceStateFromFile(PREDEF_CAMERAPARAMFILE[m_cameraIndex]))
	{
		//m_cGrabber.startLive(true);
	}
		
	return TRUE;
}

int CProcessThread::ExitInstance()
{
	// TODO: 在此执行任意逐线程清理
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CProcessThread, CWinThread)
END_MESSAGE_MAP()


// CProcessThread 消息处理程序


int CProcessThread::OnLive(bool IsLive)
{
	if (m_cGrabber.isDevValid())
	{
		if (m_cGrabber.isLive())
		{
			if (!IsLive)
			{
				m_cGrabber.stopLive();
			}
		}
		else
		{
			if (IsLive)
			{
				m_cGrabber.startLive(false);
			}
		}
		
	}
	
	return 0;
}


bool CProcessThread::InitShapeModel(int gearType)
{
	if (m_cameraIndex%2)
	{
		//small
		bool flag = m_cListener.InitShapeModel(gearType, false);
		return flag;
	} 
	else
	{
		//big
		bool flag = m_cListener.InitShapeModel(gearType, true);
		return flag;
	}
}
