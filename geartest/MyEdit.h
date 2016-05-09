#pragma once

#include "afxbutton.h "
#include "afxmenubutton.h "
// CMyEdit

class CMyEdit : public CEdit
{
	DECLARE_DYNAMIC(CMyEdit)

public:
	CMyEdit();
	virtual ~CMyEdit();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH CtlColor(CDC* /*pDC*/, UINT /*nCtlColor*/);
private:
     COLORREF    m_ForeColor;        //文本颜色
    COLORREF    m_BackColor;        //背景色
    CBrush      m_BkBrush;             //背景刷
    CFont*      p_Font;                  //字体

// 接口函数
public:
     void SetForeColor(COLORREF color);      //设置文本颜色
    void SetBkColor(COLORREF color);         //设置背景颜色
    void SetTextFont(int FontHight,LPCTSTR FontName);   //设置字体
};


class CMyStatic : public CStatic
{
	DECLARE_DYNAMIC(CMyStatic)

public:
	CMyStatic();
	virtual ~CMyStatic();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH CtlColor(CDC* /*pDC*/, UINT /*nCtlColor*/);
private:
     COLORREF    m_ForeColor;        //文本颜色
    COLORREF    m_BackColor;        //背景色
    CBrush      m_BkBrush;             //背景刷
    CFont*      p_Font;                  //字体

// 接口函数
public:
     void SetForeColor(COLORREF color);      //设置文本颜色
    void SetBkColor(COLORREF color);         //设置背景颜色
    void SetTextFont(int FontHight,LPCTSTR FontName);   //设置字体
};


// CMyBotton

class CButtonEx : public CButton
{
	DECLARE_DYNAMIC(CButtonEx)

public:
	CButtonEx();
	virtual ~CButtonEx();

protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg HBRUSH CtlColor(CDC* /*pDC*/, UINT /*nCtlColor*/);
private:
     COLORREF    m_ForeColor;        //文本颜色
    COLORREF    m_BackColor;        //背景色
    CBrush      m_BkBrush;             //背景刷


// 接口函数
public:
     void SetForeColor(COLORREF color);      //设置文本颜色
    void SetBkColor(COLORREF color);         //设置背景颜色
    void SetTextFont(int FontHight,LPCTSTR FontName);   //设置字体
	void SetText(CString str);

private:
     int         m_Style;     //按钮形状（0-正常，1-当前，2-按下，3-锁定）
     BOOL        b_InRect;            //鼠标进入标志
     CString     m_strText;           //按钮文字
     COLORREF    m_LockForeColor;     //锁定按钮的文字颜色
     CRect       m_ButRect;           //按钮尺寸
     CFont*      p_Font;             //字体

    void   DrawButton(CDC*pDC);      //画正常的按钮
   

public:
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	virtual void PreSubclassWindow();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};


// CMyBotton

class CMFCButtonEx : public CMFCButton
{
	DECLARE_DYNAMIC(CMFCButtonEx)

public:
	CMFCButtonEx();
	virtual ~CMFCButtonEx();

protected:
	DECLARE_MESSAGE_MAP()

// 接口函数
public:
    
    void SetTextFont(int FontHight,LPCTSTR FontName);   //设置字体
//	void SetText(CString str);

private:
     CFont*      p_Font;             //字体
};



class CMFCMenuButtonEx : public CMFCMenuButton
{
	DECLARE_DYNAMIC(CMFCMenuButtonEx)

public:
	CMFCMenuButtonEx();
	virtual ~CMFCMenuButtonEx();

protected:
	DECLARE_MESSAGE_MAP()

// 接口函数
public:
    
    void SetTextFont(int FontHight,LPCTSTR FontName);   //设置字体
//	void SetText(CString str);

private:
     CFont*      p_Font;             //字体
};

