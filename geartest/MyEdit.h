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
     COLORREF    m_ForeColor;        //�ı���ɫ
    COLORREF    m_BackColor;        //����ɫ
    CBrush      m_BkBrush;             //����ˢ
    CFont*      p_Font;                  //����

// �ӿں���
public:
     void SetForeColor(COLORREF color);      //�����ı���ɫ
    void SetBkColor(COLORREF color);         //���ñ�����ɫ
    void SetTextFont(int FontHight,LPCTSTR FontName);   //��������
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
     COLORREF    m_ForeColor;        //�ı���ɫ
    COLORREF    m_BackColor;        //����ɫ
    CBrush      m_BkBrush;             //����ˢ
    CFont*      p_Font;                  //����

// �ӿں���
public:
     void SetForeColor(COLORREF color);      //�����ı���ɫ
    void SetBkColor(COLORREF color);         //���ñ�����ɫ
    void SetTextFont(int FontHight,LPCTSTR FontName);   //��������
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
     COLORREF    m_ForeColor;        //�ı���ɫ
    COLORREF    m_BackColor;        //����ɫ
    CBrush      m_BkBrush;             //����ˢ


// �ӿں���
public:
     void SetForeColor(COLORREF color);      //�����ı���ɫ
    void SetBkColor(COLORREF color);         //���ñ�����ɫ
    void SetTextFont(int FontHight,LPCTSTR FontName);   //��������
	void SetText(CString str);

private:
     int         m_Style;     //��ť��״��0-������1-��ǰ��2-���£�3-������
     BOOL        b_InRect;            //�������־
     CString     m_strText;           //��ť����
     COLORREF    m_LockForeColor;     //������ť��������ɫ
     CRect       m_ButRect;           //��ť�ߴ�
     CFont*      p_Font;             //����

    void   DrawButton(CDC*pDC);      //�������İ�ť
   

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

// �ӿں���
public:
    
    void SetTextFont(int FontHight,LPCTSTR FontName);   //��������
//	void SetText(CString str);

private:
     CFont*      p_Font;             //����
};



class CMFCMenuButtonEx : public CMFCMenuButton
{
	DECLARE_DYNAMIC(CMFCMenuButtonEx)

public:
	CMFCMenuButtonEx();
	virtual ~CMFCMenuButtonEx();

protected:
	DECLARE_MESSAGE_MAP()

// �ӿں���
public:
    
    void SetTextFont(int FontHight,LPCTSTR FontName);   //��������
//	void SetText(CString str);

private:
     CFont*      p_Font;             //����
};

