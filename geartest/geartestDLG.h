// geartestDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "Listener.h"
#include "ProcessThread.h"
#include "myedit.h"

// CgeartestDlg dialog
class CgeartestDlg : public CDialog
{
// Construction
public:
	CgeartestDlg(CWnd* pParent = NULL);	// standard constructor
	~CgeartestDlg();

// Dialog Data
	enum { IDD = IDD_geartest_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()

private:

	CProcessThread *pProcessThreadArray[2];
	CProcessThread *pProcessThread;

public:
	afx_msg void OnBnClickedButtondevice();
	afx_msg void OnBnClickedButtonimagesettings();
private:
	CButton m_cButtonSettings;
	CButton m_cButtonLive;
public:
	afx_msg void OnBnClickedButtonlivevideo();
private:
	CStatic m_cStaticVideoWindowBig;
	CStatic m_cStaticVideoWindowSmall;
public:
	int myCameraInit(void);

	bool InitShapeModel(int gearType);
	int InitEditControl(void);
public:
	CButtonEx m_btnRadio1;
	CButtonEx m_btnRadio2;
	CButtonEx m_btnRadio3;
	CButtonEx m_btnRadio4;
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnBnClickedRadio1();
};
