/*

  일단 CMainFrame 에 CImage 인스턴스 선언..
  CImage 에서 비트맵 처리 CMainFrame ==> Document ==> View 와 연동 하여 처리

  CBaseBitmap 클래스는 비트맵 을 로드하는 등의
  DIB 비트맵을 처리하는데 사용되는 라이브러리입니다.

  */

// ImageBoardView.cpp : implementation of the CImageBoardView class
//

#include "stdafx.h"
#include "ImageBoard.h"
#include "MainFrm.h"
#include "Image.h"

#include "ImageBoardDoc.h"
#include "ImageBoardView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImageBoardView

IMPLEMENT_DYNCREATE(CImageBoardView, CView)

BEGIN_MESSAGE_MAP(CImageBoardView, CView)
	//{{AFX_MSG_MAP(CImageBoardView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImageBoardView construction/destruction


#define		swap	SWAP
#define		SWAP(x,y,t)	\
			t = x;		\
			x = y;		\
			y = t;

CImageBoardView::CImageBoardView()
{
	m_bLButtonDown = FALSE;
//	m_pDoc = NULL;
//	m_pDoc = GetDocument();
//	if( m_pDoc ->m_pImage == NULL )
//		m_pDoc ->m_pImage = new CImage( this, this ->GetDC() );
}

CImageBoardView::~CImageBoardView()
{
}

BOOL CImageBoardView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CImageBoardView drawing

void CImageBoardView::OnDraw(CDC* pDC)
{
	CImageBoardDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	CPaintDC	dc(this);
	CRect	rt;
	GetClientRect(&rt);

	if( pDoc ->m_pImage == NULL )
	{
		pDoc ->m_pImage = new CImage(this, &dc);
	}

//	dc.SetMapMode(MM_ISOTROPIC);
//	dc.SetWindowExt(1000, 1000);
//	dc.SetViewportExt(rt.Width(), rt.Height());

	if( ((CMainFrame *)AfxGetMainWnd()) ->m_bDraw == CLEAR )
	{
		if( pDoc != NULL )
		{
			CRect	rt;
			GetClientRect( &rt );
			pDoc ->m_pImage ->ClearView( rt );
		}
	}
	else
	{
		if( pDoc != NULL )
		{
			CRect	rt;
			GetClientRect(&rt);
			pDoc ->m_pImage ->BitBlt(0, 0, rt.Width(), rt.Height(), 0, 0, SRCCOPY);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CImageBoardView printing

BOOL CImageBoardView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CImageBoardView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CImageBoardView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CImageBoardView diagnostics

#ifdef _DEBUG
void CImageBoardView::AssertValid() const
{
	CView::AssertValid();
}

void CImageBoardView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CImageBoardDoc* CImageBoardView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageBoardDoc)));
	return (CImageBoardDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CImageBoardView message handlers

void CImageBoardView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CImageBoardDoc *pDoc;
	m_bLButtonDown = TRUE;
	pDoc = GetDocument();
	if( pDoc ->m_pImage == NULL )
	{
		pDoc ->m_pImage = new CImage( this, this ->GetDC() );
	}
	switch( ((CMainFrame*)AfxGetMainWnd()) ->m_bDraw )
	{
	case DRAW_LINE :
		m_pt1 = point;
		break;
	case DRAW_POINT :
		m_pt1 = point;
		pDoc ->m_pImage ->Point(point);
		break;
	case DRAW_RECT :
		m_pt1 = point;
		break;
	case DRAW_CIR :
		m_pt1 = point;
		break;
	case CLEAR :
		break;
	default :
//		MessageBox("Error <0x33D1> : Throw Error Handler");
		break;
	}
	
	CView::OnLButtonDown(nFlags, point);
}

void CImageBoardView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CRect	rt;
	CImageBoardDoc *pDoc = NULL;
	m_bLButtonDown = FALSE;

	pDoc = GetDocument();
	switch( ((CMainFrame*)AfxGetMainWnd()) ->m_bDraw )
	{
	case DRAW_LINE :
		m_pt2 = point;
		pDoc ->m_pImage ->Line( m_pt1, m_pt2 );
		break;
	case DRAW_POINT :
		m_pt2 = point;
		pDoc ->m_pImage ->Point( point );
		break;
	case DRAW_RECT :
		m_pt2 = point;
		m_rt.SetRect( m_pt1, m_pt2 );
		pDoc ->m_pImage ->Rectangle( m_rt );
		break;
	case DRAW_CIR :
		m_pt2 = point;
		m_rt.SetRect( m_pt1, m_pt2 );
		pDoc ->m_pImage ->Circle( m_pt1, m_pt2 );
		break;
	case CLEAR :
		break;
	default :
//		MessageBox("Error <0x33D2> : Throw Error Handler");
		break;
	}

	Invalidate(TRUE);
	CView::OnLButtonUp(nFlags, point);
}

void CImageBoardView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CImageBoardDoc	*pDoc = NULL;
	CClientDC	dc(this);
	CRect	rt(m_pt1, point);
	if( m_bLButtonDown == FALSE )
		return;

	pDoc = GetDocument();

	INT	nRand = 0;
//	srand(1000);
	switch( ((CMainFrame*)AfxGetMainWnd()) ->m_bDraw )
	{
	case DRAW_LINE :
		dc.MoveTo( m_pt1 );
		dc.LineTo( point );
		m_pt2 = point;
		break;
	case DRAW_POINT :
		pDoc ->m_pImage ->Line( m_pt1, point );
		m_pt1 = point;
		m_pt2 = point;
		break;
	case DRAW_RECT :
		dc.Rectangle(rt);
		m_pt2 = point;
		break;
	case DRAW_CIR :
		dc.Ellipse(&rt);
		m_pt2 = point;
		break;
	case CLEAR :
		m_pt2 = point;
		break;
	default :
		break;
	}
	nRand = rand();
	if( nRand % 2 == 1 )
	{
		Invalidate(TRUE);
	}

	CView::OnMouseMove(nFlags, point);
}

BOOL CImageBoardView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
	HCURSOR hCursor;
	switch( ((CMainFrame*)AfxGetMainWnd()) ->m_bDraw )
	{
	case DRAW_LINE :
		hCursor = AfxGetApp() ->LoadCursor(IDC_LINE);
		break;
	case DRAW_POINT :
		hCursor = AfxGetApp() ->LoadCursor(IDC_LINE);
		break;
	case DRAW_RECT :
		hCursor = AfxGetApp() ->LoadCursor(IDC_RECT);
		break;
	case DRAW_CIR :
		hCursor = AfxGetApp() ->LoadCursor(IDC_CIR);
		break;
	case CLEAR :
		hCursor = AfxGetApp() ->LoadCursor(IDC_NODROP);
		break;
	default :
		hCursor = AfxGetApp() ->LoadCursor(IDC_NODROP);
		break;
	}

	::SetCursor(hCursor);

//	return CView::OnSetCursor(pWnd, nHitTest, message);
	return	TRUE;
}