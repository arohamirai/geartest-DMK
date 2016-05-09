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

////////   齿轮种类定义
enum GEAR_TYPE
{
	BLUE_TYPE_01,
	BLUE_TYPE_02,
	BLUE_TYPE_03,
	YELLOW_TYPE_01,
	YELLOW_TYPE_02,
	// 其他种类请按上面格式添加
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