// MyEdit.cpp : 实现文件
//

#include "stdafx.h"

#include "MyEdit.h"


// CMyEdit

IMPLEMENT_DYNAMIC(CMyEdit, CEdit)

CMyEdit::CMyEdit()
{
	m_ForeColor = RGB(0,0,0);                         //文字颜色（黑色）
    m_BackColor = RGB(255,255,255);               //背景色（白色）
    m_BkBrush.CreateSolidBrush(m_BackColor);    //背景刷
    p_Font = NULL;                                          //字体指针
}

CMyEdit::~CMyEdit()
{
	if ( p_Font )    delete p_Font; 
}


BEGIN_MESSAGE_MAP(CMyEdit, CEdit)
	ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()



// CMyEdit 消息处理程序




HBRUSH CMyEdit::CtlColor(CDC* pDC, UINT nCtlColor)
{
	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果不应调用父级的处理程序，则返回非 null 画笔
	pDC->SetTextColor( m_ForeColor );                //设置文字颜色
    pDC->SetBkColor( m_BackColor );                    //设置背景色
    return (HBRUSH)m_BkBrush.GetSafeHandle();   //返回背景刷
	//return NULL;
}


void CMyEdit::SetTextFont(int FontHight,LPCTSTR FontName)
 {
     if ( p_Font )   delete p_Font;                                //删除旧字体
    p_Font = new CFont;                                           //生成字体对象
    p_Font->CreatePointFont( FontHight, FontName );   //创建字体
    SetFont( p_Font );                                               //设置控件字体
}

void CMyEdit::SetBkColor(COLORREF color)
 {
     m_BackColor = color;
     m_BkBrush.Detach();                                   //分离原背景刷
    m_BkBrush.CreateSolidBrush( m_BackColor );   //建立背景刷
}

void CMyEdit::SetForeColor(COLORREF color)
 {
     m_ForeColor = color;         //设置文字颜色
}


// CMyEdit

IMPLEMENT_DYNAMIC(CMyStatic, CStatic)

CMyStatic::CMyStatic()
{
	m_ForeColor = RGB(0,0,0);                         //文字颜色（黑色）
    m_BackColor = RGB(255,255,255);               //背景色（白色）
    m_BkBrush.CreateSolidBrush(m_BackColor);    //背景刷
    p_Font = NULL;                                          //字体指针
}

CMyStatic::~CMyStatic()
{
	if ( p_Font )    delete p_Font; 
}


BEGIN_MESSAGE_MAP(CMyStatic, CStatic)
	ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()



// CMyEdit 消息处理程序




HBRUSH CMyStatic::CtlColor(CDC* pDC, UINT nCtlColor)
{
	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果不应调用父级的处理程序，则返回非 null 画笔
	pDC->SetTextColor( m_ForeColor );                //设置文字颜色
    pDC->SetBkColor( m_BackColor );                    //设置背景色
    return (HBRUSH)m_BkBrush.GetSafeHandle();   //返回背景刷
	//return NULL;
}


void CMyStatic::SetTextFont(int FontHight,LPCTSTR FontName)
 {
     if ( p_Font )   delete p_Font;                                //删除旧字体
    p_Font = new CFont;                                           //生成字体对象
    p_Font->CreatePointFont( FontHight, FontName );   //创建字体
    SetFont( p_Font );                                               //设置控件字体
}

void CMyStatic::SetBkColor(COLORREF color)
 {
     m_BackColor = color;
     m_BkBrush.Detach();                                   //分离原背景刷
    m_BkBrush.CreateSolidBrush( m_BackColor );   //建立背景刷
}

void CMyStatic::SetForeColor(COLORREF color)
 {
     m_ForeColor = color;         //设置文字颜色
}



// CButtonExt

IMPLEMENT_DYNAMIC(CButtonEx, CButton)

CButtonEx::CButtonEx()
{
	 m_Style =0;               //按钮形状风格
     b_InRect =false;           //鼠标进入标志
     m_strText =_T("");         //按钮文字（使用默认文字）

	m_ForeColor = RGB(0,0,0);                         //文字颜色（黑色）
    m_BackColor = RGB(243,243,243);               //背景色（白色）
    m_BkBrush.CreateSolidBrush(m_BackColor);    //背景刷
	 m_LockForeColor =GetSysColor(COLOR_GRAYTEXT);     //锁定按钮的文字颜色
    p_Font = NULL;                                          //字体指针
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



// CButtonEx 消息处理程序
//设置按钮文本
void CButtonEx::SetText(CString str)
 {
      m_strText = _T("");
      SetWindowText(str);
 } 

//设置文本颜色
void CButtonEx::SetForeColor(COLORREF color)
 {
      m_ForeColor = color;
      Invalidate();
 } 

//设置背景颜色
void CButtonEx::SetBkColor(COLORREF color)
 {
      m_BackColor = color;
      m_BkBrush.Detach();                                   //分离原背景刷
      m_BkBrush.CreateSolidBrush( m_BackColor );   //建立背景刷
      Invalidate();
 } 

//设置字体(字体高度、字体名)
void CButtonEx::SetTextFont(int FontHight,LPCTSTR FontName)
 {
      if ( p_Font )  

     delete p_Font;     //删除旧字体
     p_Font = new CFont;
      p_Font->CreatePointFont( FontHight, FontName);     //创建新字体
     SetFont( p_Font);                //设置字体
}



void CButtonEx::DrawButton(CDC *pDC)
 {
      //调整状态
     if( m_Style==3 ) m_Style = 0;
      if( GetStyle() & WS_DISABLED )
          m_Style =3;     //禁止状态
     //根据状态调整边框颜色和文字颜色
     COLORREF bColor, fColor;    //bColor为边框颜色，fColor为文字颜色
     switch( m_Style )
      {
      case 0: bColor = RGB(192,192,192); fColor =m_ForeColor; break;   //正常按钮
     case 1: bColor = RGB(255,255,255); fColor =m_ForeColor; break;   //鼠标进入时按钮
     case 2: bColor = RGB(192,192,192); fColor =m_ForeColor; break;   //按下的按钮
     case 3: bColor = m_BackColor; fColor =m_LockForeColor; break;    //锁定的按钮
     }
      //绘制按钮背景
     CBrush Brush;
      Brush.CreateSolidBrush( m_BackColor);     //背景刷
     pDC->SelectObject( &Brush );
      CPen Pen;
      Pen.CreatePen(PS_SOLID, 1, bColor );
      pDC->SelectObject( &Pen );
     pDC->RoundRect(&m_ButRect,CPoint(5,5));    //画圆角矩形
     //绘制按钮按下时的边框
     if( m_Style!=2 )
      {
          CRect Rect;
          Rect.SetRect(m_ButRect.left+2, m_ButRect.top+1, m_ButRect.right, m_ButRect.bottom );
          pDC->DrawEdge( &Rect,BDR_RAISEDINNER, BF_RECT );     //画边框
     }
      //绘制按钮文字
     pDC->SetTextColor( fColor);         //画文字
     pDC->SetBkMode( TRANSPARENT );
      pDC->DrawText( m_strText, &m_ButRect,DT_SINGLELINE | DT_CENTER
          | DT_VCENTER |DT_END_ELLIPSIS);
      //绘制拥有焦点按钮的虚线框
     if( GetFocus()==this )
      {
          CRect Rect;
          Rect.SetRect(m_ButRect.left+3, m_ButRect.top+2, m_ButRect.right-3, m_ButRect.bottom-2 );
          pDC->DrawFocusRect(&Rect );     //画拥有焦点的虚线框
     }
 } 


void CButtonEx::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{

	// TODO:  添加您的代码以绘制指定项
	CDC *pDC = CDC::FromHandle( lpDrawItemStruct->hDC);
      m_ButRect =lpDrawItemStruct->rcItem;     //获取按钮尺寸

     if( m_strText.IsEmpty() )
          GetWindowText( m_strText);           //获取按钮文本

     int nSavedDC = pDC->SaveDC();
      VERIFY( pDC );
      DrawButton( pDC);                //绘制按钮
     pDC->RestoreDC( nSavedDC );

}


void CButtonEx::PreSubclassWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	ModifyStyle( 0, BS_OWNERDRAW);         //设置按钮属性为自画式
	CButton::PreSubclassWindow();
}


void CButtonEx::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if( !b_InRect || GetCapture()!=this)     //鼠标进入按钮
     {
          b_InRect =true;     //设置进入标志
        SetCapture();        //捕获鼠标
         m_Style =1;         //设置按钮状态
        Invalidate();        //重绘按钮
     }
      else
      {
          if (!m_ButRect.PtInRect(point) )     //鼠标离开按钮
         {
             b_InRect = false;    //清除进入标志
            ReleaseCapture();    //释放捕获的鼠标
            m_Style = 0;         //设置按钮状态
            Invalidate();        //重绘按钮
         }
      }

	CButton::OnMouseMove(nFlags, point);
}


void CButtonEx::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_Style = 2;
     Invalidate();         //重绘按钮
	CButton::OnLButtonDown(nFlags, point);
}


void CButtonEx::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_Style = 1;
     Invalidate();         //重绘按钮

	CButton::OnLButtonUp(nFlags, point);
}



IMPLEMENT_DYNAMIC(CMFCButtonEx, CMFCButton)

CMFCButtonEx::CMFCButtonEx()
{	
    p_Font = NULL;                                          //字体指针
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

     delete p_Font;     //删除旧字体
     p_Font = new CFont;
      p_Font->CreatePointFont( FontHight, FontName);     //创建新字体
     SetFont( p_Font);                //设置字体
}


IMPLEMENT_DYNAMIC(CMFCMenuButtonEx, CMFCMenuButton)

CMFCMenuButtonEx::CMFCMenuButtonEx()
{	
    p_Font = NULL;                                          //字体指针
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

     delete p_Font;     //删除旧字体
     p_Font = new CFont;
      p_Font->CreatePointFont( FontHight, FontName);     //创建新字体
     SetFont( p_Font);                //设置字体
}