// ImageBoardDoc.cpp : implementation of the CImageBoardDoc class
//

#include "stdafx.h"
#include "ImageBoard.h"
#include "ImageBoardView.h"

#include "ImageBoardDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImageBoardDoc

IMPLEMENT_DYNCREATE(CImageBoardDoc, CDocument)

BEGIN_MESSAGE_MAP(CImageBoardDoc, CDocument)
	//{{AFX_MSG_MAP(CImageBoardDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImageBoardDoc construction/destruction

CImageBoardDoc::CImageBoardDoc()
{
	m_pImage = NULL;
//	POSITION  pos = GetFirstViewPosition();
//	CImageBoardView *pView = (CImageBoardView *)GetNextView( pos );
// 아직 View 가 활성화 되지 않은 상태이다..
//	m_pImage = new CImage( pView, pView ->GetDC() );
}

CImageBoardDoc::~CImageBoardDoc()
{
	if( m_pImage != NULL )
		delete m_pImage;
}

BOOL CImageBoardDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CImageBoardDoc serialization

void CImageBoardDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CImageBoardDoc diagnostics

#ifdef _DEBUG
void CImageBoardDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CImageBoardDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CImageBoardDoc commands
