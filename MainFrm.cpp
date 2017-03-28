// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "ImageBoard.h"
#include "ImageBoardDoc.h"
#include "ImageBoardView.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_LINE, OnLine)
	ON_COMMAND(ID_RECTANGLE, OnRectangle)
	ON_COMMAND(ID_CIRCLE, OnCircle)
	ON_UPDATE_COMMAND_UI(ID_LINE, OnUpdateLine)
	ON_UPDATE_COMMAND_UI(ID_RECTANGLE, OnUpdateRectangle)
	ON_UPDATE_COMMAND_UI(ID_CIRCLE, OnUpdateCircle)
	ON_COMMAND(ID_CLEAR, OnClear)
	ON_COMMAND(ID_POINT, OnPoint)
	ON_UPDATE_COMMAND_UI(ID_POINT, OnUpdatePoint)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	m_bDraw = EXCEPT;
//	m_pBaseBitmap = NULL;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::OnLine() 
{
	if( m_bDraw != DRAW_LINE )
		m_bDraw = DRAW_LINE;
	else
		m_bDraw = EXCEPT;
}

void CMainFrame::OnPoint() 
{
	if( m_bDraw != DRAW_POINT )
		m_bDraw = DRAW_POINT;
	else
		m_bDraw = EXCEPT;
}

void CMainFrame::OnRectangle() 
{
	if( m_bDraw != DRAW_RECT )
		m_bDraw = DRAW_RECT;
	else
		m_bDraw = EXCEPT;
}

void CMainFrame::OnCircle() 
{
	if( m_bDraw != DRAW_CIR )
		m_bDraw = DRAW_CIR;
	else
		m_bDraw = EXCEPT;
}

void CMainFrame::OnClear() 
{
	// TODO: Add your command handler code here
	CRect	rt;
	m_bDraw = CLEAR;
	GetClientRect(&rt);
	InvalidateRect( &rt, TRUE );
}

void CMainFrame::OnUpdateLine(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	switch( m_bDraw )
	{
	case DRAW_LINE :
		pCmdUI ->SetCheck( 1 );
		break;
	case DRAW_POINT :
		pCmdUI ->SetCheck( 0 );
		break;
	case DRAW_RECT :
		pCmdUI ->SetCheck( 0 );
		break;
	case DRAW_CIR :
		pCmdUI ->SetCheck( 0 );
		break;
	default :
		pCmdUI ->SetCheck( 0 );
		break;
	}
}

void CMainFrame::OnUpdateRectangle(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	switch( m_bDraw )
	{
	case DRAW_LINE :
		pCmdUI ->SetCheck( 0 );
		break;
	case DRAW_POINT :
		pCmdUI ->SetCheck( 0 );
		break;
	case DRAW_RECT :
		pCmdUI ->SetCheck( 1 );
		break;
	case DRAW_CIR :
		pCmdUI ->SetCheck( 0 );
		break;
	default :
		pCmdUI ->SetCheck( 0 );
		break;
	}
}

void CMainFrame::OnUpdateCircle(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	switch( m_bDraw )
	{
	case DRAW_LINE :
		pCmdUI ->SetCheck( 0 );
		break;
	case DRAW_POINT :
		pCmdUI ->SetCheck( 0 );
		break;
	case DRAW_RECT :
		pCmdUI ->SetCheck( 0 );
		break;
	case DRAW_CIR :
		pCmdUI ->SetCheck( 1 );
		break;
	default :
		pCmdUI ->SetCheck( 0 );
		break;
	}
}

void CMainFrame::OnUpdatePoint(CCmdUI* pCmdUI) 
{
	switch( m_bDraw )
	{
	case DRAW_LINE :
		pCmdUI ->SetCheck( 0 );
		break;
	case DRAW_POINT :
		pCmdUI ->SetCheck( 1 );
		break;
	case DRAW_RECT :
		pCmdUI ->SetCheck( 0 );
		break;
	case DRAW_CIR :
		pCmdUI ->SetCheck( 0 );
		break;
	default :
		pCmdUI ->SetCheck( 0 );
		break;
	}
}

void CMainFrame::OnEditCut() 
{
	//  후일 추가..
	//  ClipBoard 이용하여 CUT 기능 구현..
}

void CMainFrame::OnEditCopy() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnEditPaste() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnFileNew() 
{
	this ->OnClear();
}

void CMainFrame::OnFileOpen() 
{
	/*
	// Constructors
	CFileDialog(BOOL bOpenFileDialog, // TRUE for FileOpen, FALSE for FileSaveAs
		LPCTSTR lpszDefExt = NULL,
		LPCTSTR lpszFileName = NULL,
		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		LPCTSTR lpszFilter = NULL,
		CWnd* pParentWnd = NULL);
	*/
	CFileDialog	dlg(TRUE);
//	dlg.DragAcceptFiles(TRUE);
//	dlg.GetFileTitle();
	CString		str;
	if( dlg.DoModal() == 2 )
		return;
	str = dlg.GetFileName();
	if( ((CImageBoardDoc *)this ->GetActiveDocument())
		->m_pImage == NULL )
	{
		((CImageBoardDoc *)this ->GetActiveDocument())
			->m_pImage = new CImage( (CImageBoardView *)GetActiveView(),
			((CImageBoardView *)GetActiveView()) ->GetDC() );
	}
	((CImageBoardDoc *)this ->GetActiveDocument())
		->m_pImage ->LoadBitmap( CPoint(0,0), SRCCOPY, str );
/*
	if( m_pBaseBitmap == NULL )
	{
		m_pBaseBitmap = new CBaseBitmap;
	}
	m_pBaseBitmap ->LoadBitmap( str );

	CImageBoardView	*pView = NULL;
	CRect		rt;
	GetClientRect(&rt);
	pView = (CImageBoardView *)GetActiveView();
	m_pBaseBitmap ->SetBitmapInfo();

	CClientDC	dc(pView);
//	((CImageBoardDoc *)this ->GetActiveDocument()) ->m_pImage ->SetBitmap( m_pBaseBitmap );
	m_pBaseBitmap ->DrawBitmap(&dc, CPoint(0,0), &rt, &rt);
	*/
}

void CMainFrame::OnFileSave() 
{
}

void CMainFrame::OnFileSaveAs() 
{
	CImage	*pImage = NULL;
	CPalette	*pPal;
	pPal = new CPalette();
	CString	str;
//	LOGPALETTE logPal;
//	pPal ->CreatePalette( &logPal );
	CFileDialog	fileDlg( FALSE );
	if( fileDlg.DoModal() == 2 )
		return;
	str = fileDlg.GetFileName();


	pImage = ((CImageBoardDoc *)this ->GetActiveDocument())-> m_pImage;
	if( pImage == NULL )
	{
		pImage ->WriteDIB( str, pPal );
	}
}