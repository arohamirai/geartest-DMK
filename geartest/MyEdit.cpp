// MyEdit.cpp : ʵ���ļ�
//

#include "stdafx.h"

#include "MyEdit.h"


// CMyEdit

IMPLEMENT_DYNAMIC(CMyEdit, CEdit)

CMyEdit::CMyEdit()
{
	m_ForeColor = RGB(0,0,0);                         //������ɫ����ɫ��
    m_BackColor = RGB(255,255,255);               //����ɫ����ɫ��
    m_BkBrush.CreateSolidBrush(m_BackColor);    //����ˢ
    p_Font = NULL;                                          //����ָ��
}

CMyEdit::~CMyEdit()
{
	if ( p_Font )    delete p_Font; 
}


BEGIN_MESSAGE_MAP(CMyEdit, CEdit)
	ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()



// CMyEdit ��Ϣ�������




HBRUSH CMyEdit::CtlColor(CDC* pDC, UINT nCtlColor)
{
	// TODO:  �ڴ˸��� DC ���κ�����

	// TODO:  �����Ӧ���ø����Ĵ�������򷵻ط� null ����
	pDC->SetTextColor( m_ForeColor );                //����������ɫ
    pDC->SetBkColor( m_BackColor );                    //���ñ���ɫ
    return (HBRUSH)m_BkBrush.GetSafeHandle();   //���ر���ˢ
	//return NULL;
}


void CMyEdit::SetTextFont(int FontHight,LPCTSTR FontName)
 {
     if ( p_Font )   delete p_Font;                                //ɾ��������
    p_Font = new CFont;                                           //�����������
    p_Font->CreatePointFont( FontHight, FontName );   //��������
    SetFont( p_Font );                                               //���ÿؼ�����
}

void CMyEdit::SetBkColor(COLORREF color)
 {
     m_BackColor = color;
     m_BkBrush.Detach();                                   //����ԭ����ˢ
    m_BkBrush.CreateSolidBrush( m_BackColor );   //��������ˢ
}

void CMyEdit::SetForeColor(COLORREF color)
 {
     m_ForeColor = color;         //����������ɫ
}


// CMyEdit

IMPLEMENT_DYNAMIC(CMyStatic, CStatic)

CMyStatic::CMyStatic()
{
	m_ForeColor = RGB(0,0,0);                         //������ɫ����ɫ��
    m_BackColor = RGB(255,255,255);               //����ɫ����ɫ��
    m_BkBrush.CreateSolidBrush(m_BackColor);    //����ˢ
    p_Font = NULL;                                          //����ָ��
}

CMyStatic::~CMyStatic()
{
	if ( p_Font )    delete p_Font; 
}


BEGIN_MESSAGE_MAP(CMyStatic, CStatic)
	ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()



// CMyEdit ��Ϣ�������




HBRUSH CMyStatic::CtlColor(CDC* pDC, UINT nCtlColor)
{
	// TODO:  �ڴ˸��� DC ���κ�����

	// TODO:  �����Ӧ���ø����Ĵ�������򷵻ط� null ����
	pDC->SetTextColor( m_ForeColor );                //����������ɫ
    pDC->SetBkColor( m_BackColor );                    //���ñ���ɫ
    return (HBRUSH)m_BkBrush.GetSafeHandle();   //���ر���ˢ
	//return NULL;
}


void CMyStatic::SetTextFont(int FontHight,LPCTSTR FontName)
 {
     if ( p_Font )   delete p_Font;                                //ɾ��������
    p_Font = new CFont;                                           //�����������
    p_Font->CreatePointFont( FontHight, FontName );   //��������
    SetFont( p_Font );                                               //���ÿؼ�����
}

void CMyStatic::SetBkColor(COLORREF color)
 {
     m_BackColor = color;
     m_BkBrush.Detach();                                   //����ԭ����ˢ
    m_BkBrush.CreateSolidBrush( m_BackColor );   //��������ˢ
}

void CMyStatic::SetForeColor(COLORREF color)
 {
     m_ForeColor = color;         //����������ɫ
}



// CButtonExt

IMPLEMENT_DYNAMIC(CButtonEx, CButton)

CButtonEx::CButtonEx()
{
	 m_Style =0;               //��ť��״���
     b_InRect =false;           //�������־
     m_strText =_T("");         //��ť���֣�ʹ��Ĭ�����֣�

	m_ForeColor = RGB(0,0,0);                         //������ɫ����ɫ��
    m_BackColor = RGB(243,243,243);               //����ɫ����ɫ��
    m_BkBrush.CreateSolidBrush(m_BackColor);    //����ˢ
	 m_LockForeColor =GetSysColor(COLOR_GRAYTEXT);     //������ť��������ɫ
    p_Font = NULL;                                          //����ָ��
}

CButtonEx::~CButtonEx()
{
	if ( p_Font )    delete p_Font; 
}


BEGIN_MESSAGE_MAP(CButtonEx, CButton)
//	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()



// CButtonEx ��Ϣ�������
//���ð�ť�ı�
void CButtonEx::SetText(CString str)
 {
      m_strText = _T("");
      SetWindowText(str);
 } 

//�����ı���ɫ
void CButtonEx::SetForeColor(COLORREF color)
 {
      m_ForeColor = color;
      Invalidate();
 } 

//���ñ�����ɫ
void CButtonEx::SetBkColor(COLORREF color)
 {
      m_BackColor = color;
      m_BkBrush.Detach();                                   //����ԭ����ˢ
      m_BkBrush.CreateSolidBrush( m_BackColor );   //��������ˢ
      Invalidate();
 } 

//��������(����߶ȡ�������)
void CButtonEx::SetTextFont(int FontHight,LPCTSTR FontName)
 {
      if ( p_Font )  

     delete p_Font;     //ɾ��������
     p_Font = new CFont;
      p_Font->CreatePointFont( FontHight, FontName);     //����������
     SetFont( p_Font);                //��������
}



void CButtonEx::DrawButton(CDC *pDC)
 {
      //����״̬
     if( m_Style==3 ) m_Style = 0;
      if( GetStyle() & WS_DISABLED )
          m_Style =3;     //��ֹ״̬
     //����״̬�����߿���ɫ��������ɫ
     COLORREF bColor, fColor;    //bColorΪ�߿���ɫ��fColorΪ������ɫ
     switch( m_Style )
      {
      case 0: bColor = RGB(192,192,192); fColor =m_ForeColor; break;   //������ť
     case 1: bColor = RGB(255,255,255); fColor =m_ForeColor; break;   //������ʱ��ť
     case 2: bColor = RGB(192,192,192); fColor =m_ForeColor; break;   //���µİ�ť
     case 3: bColor = m_BackColor; fColor =m_LockForeColor; break;    //�����İ�ť
     }
      //���ư�ť����
     CBrush Brush;
      Brush.CreateSolidBrush( m_BackColor);     //����ˢ
     pDC->SelectObject( &Brush );
      CPen Pen;
      Pen.CreatePen(PS_SOLID, 1, bColor );
      pDC->SelectObject( &Pen );
     pDC->RoundRect(&m_ButRect,CPoint(5,5));    //��Բ�Ǿ���
     //���ư�ť����ʱ�ı߿�
     if( m_Style!=2 )
      {
          CRect Rect;
          Rect.SetRect(m_ButRect.left+2, m_ButRect.top+1, m_ButRect.right, m_ButRect.bottom );
          pDC->DrawEdge( &Rect,BDR_RAISEDINNER, BF_RECT );     //���߿�
     }
      //���ư�ť����
     pDC->SetTextColor( fColor);         //������
     pDC->SetBkMode( TRANSPARENT );
      pDC->DrawText( m_strText, &m_ButRect,DT_SINGLELINE | DT_CENTER
          | DT_VCENTER |DT_END_ELLIPSIS);
      //����ӵ�н��㰴ť�����߿�
     if( GetFocus()==this )
      {
          CRect Rect;
          Rect.SetRect(m_ButRect.left+3, m_ButRect.top+2, m_ButRect.right-3, m_ButRect.bottom-2 );
          pDC->DrawFocusRect(&Rect );     //��ӵ�н�������߿�
     }
 } 


void CButtonEx::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{

	// TODO:  ������Ĵ����Ի���ָ����
	CDC *pDC = CDC::FromHandle( lpDrawItemStruct->hDC);
      m_ButRect =lpDrawItemStruct->rcItem;     //��ȡ��ť�ߴ�

     if( m_strText.IsEmpty() )
          GetWindowText( m_strText);           //��ȡ��ť�ı�

     int nSavedDC = pDC->SaveDC();
      VERIFY( pDC );
      DrawButton( pDC);                //���ư�ť
     pDC->RestoreDC( nSavedDC );

}


void CButtonEx::PreSubclassWindow()
{
	// TODO: �ڴ����ר�ô����/����û���
	ModifyStyle( 0, BS_OWNERDRAW);         //���ð�ť����Ϊ�Ի�ʽ
	CButton::PreSubclassWindow();
}


void CButtonEx::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if( !b_InRect || GetCapture()!=this)     //�����밴ť
     {
          b_InRect =true;     //���ý����־
        SetCapture();        //�������
         m_Style =1;         //���ð�ť״̬
        Invalidate();        //�ػ水ť
     }
      else
      {
          if (!m_ButRect.PtInRect(point) )     //����뿪��ť
         {
             b_InRect = false;    //��������־
            ReleaseCapture();    //�ͷŲ�������
            m_Style = 0;         //���ð�ť״̬
            Invalidate();        //�ػ水ť
         }
      }

	CButton::OnMouseMove(nFlags, point);
}


void CButtonEx::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_Style = 2;
     Invalidate();         //�ػ水ť
	CButton::OnLButtonDown(nFlags, point);
}


void CButtonEx::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_Style = 1;
     Invalidate();         //�ػ水ť

	CButton::OnLButtonUp(nFlags, point);
}



IMPLEMENT_DYNAMIC(CMFCButtonEx, CMFCButton)

CMFCButtonEx::CMFCButtonEx()
{	
    p_Font = NULL;                                          //����ָ��
}

CMFCButtonEx::~CMFCButtonEx()
{
	if ( p_Font )    delete p_Font; 
}

BEGIN_MESSAGE_MAP(CMFCButtonEx, CMFCButton)
	//ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()

void CMFCButtonEx::SetTextFont(int FontHight,LPCTSTR FontName)
 {
      if ( p_Font )  

     delete p_Font;     //ɾ��������
     p_Font = new CFont;
      p_Font->CreatePointFont( FontHight, FontName);     //����������
     SetFont( p_Font);                //��������
}


IMPLEMENT_DYNAMIC(CMFCMenuButtonEx, CMFCMenuButton)

CMFCMenuButtonEx::CMFCMenuButtonEx()
{	
    p_Font = NULL;                                          //����ָ��
}

CMFCMenuButtonEx::~CMFCMenuButtonEx()
{
	if ( p_Font )    delete p_Font; 
}

BEGIN_MESSAGE_MAP(CMFCMenuButtonEx, CMFCMenuButton)
	//ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()

void CMFCMenuButtonEx::SetTextFont(int FontHight,LPCTSTR FontName)
 {
      if ( p_Font )  

     delete p_Font;     //ɾ��������
     p_Font = new CFont;
      p_Font->CreatePointFont( FontHight, FontName);     //����������
     SetFont( p_Font);                //��������
}