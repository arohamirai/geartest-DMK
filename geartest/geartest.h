// geartest.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols


// CgeartestApp:
// See geartest.cpp for the implementation of this class.
//

////////   �������ඨ��
enum GEAR_TYPE
{
	BLUE_TYPE_01,
	BLUE_TYPE_02,
	BLUE_TYPE_03,
	YELLOW_TYPE_01,
	YELLOW_TYPE_02,
	// ���������밴�����ʽ���
};


class CgeartestApp : public CWinApp
{
public:
	CgeartestApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CgeartestApp theApp;