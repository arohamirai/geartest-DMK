#pragma once


#include "listener.h"
// CProcessThread

class CProcessThread : public CWinThread
{
	DECLARE_DYNCREATE(CProcessThread)

public:
	CProcessThread();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CProcessThread();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

public:
	DShowLib::Grabber		m_cGrabber; // The instance of the Grabber class.
	DShowLib::FrameHandlerSink::tFHSPtr           m_pSink;
	// �������ʱ��ʹ��CListenerSingle�࣬������ʱ��ʹ��CListenerMutil�࣬ ��ʹCProcessThread::CProcessThread()�е������Ч
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


