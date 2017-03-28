// Image.cpp: implementation of the CImage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ImageBoard.h"
#include "Image.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CImage::CImage( CWnd *pWnd )
{
	m_pBitmap = NULL;
	m_pWnd = pWnd;
	m_pBaseBitmap = NULL;
//	m_pBaseBitmapMem = NULL;
	if( m_pBaseBitmap == NULL )
	{
		m_pBaseBitmap = new CBaseBitmap;
	}
//	if( m_pBaseBitmapMem == NULL )
//	{
//		m_pBaseBitmapMem = new CBaseBitmap;
//	}
}

CImage::CImage( CWnd *pWnd, CDC *pDC )
{
	CBitmap	*pOldBit;
	m_pWnd = pWnd;
	m_pBitmap = NULL;
	m_pBitmap = new CBitmap;
	m_DC.Attach( pDC ->m_hDC );
	m_memDC.CreateCompatibleDC( &m_DC );
	m_pBitmap ->CreateCompatibleBitmap(&m_memDC, 1024, 768);

	pOldBit = m_memDC.SelectObject(m_pBitmap);
	PatBlt(m_memDC.m_hDC, 0, 0, 1024, 768 , WHITENESS);
	m_memDC.SelectObject(pOldBit);

	m_pBaseBitmap  = new CBaseBitmap;
//	m_pBaseBitmapMem = new CBaseBitmap;
}

CImage::~CImage()
{
	if( m_pBitmap != NULL )
		delete m_pBitmap;
	m_DC.Detach();
	m_memDC.DeleteDC();

	if( m_pBaseBitmap != NULL )
		delete m_pBaseBitmap;
//	if( m_pBaseBitmapMem != NULL )
//		delete m_pBaseBitmapMem;
}

CDC * CImage::GetDC(void)
{
	return	&m_memDC;
}

CDC * CImage::GetMemDC(void)
{
	return	&m_memDC;
}

CBitmap * CImage::GetMemoryBitmap(void)
{
	return	m_pBitmap;
}

BOOL CImage::LoadBitmap(/* CDC *dc , */ POINT Location,
						/* const CRect *WNDRect, const CRect *IMGRect, */
						DWORD dwRop , LPCTSTR szFile )
{
	CRect	rt;
	CBitmap	*pOldBit = NULL;

	m_pBaseBitmap ->LoadBitmap(szFile);
	m_pBaseBitmap ->SetBitmapInfo();
	m_pBaseBitmap ->GetBitmapRect(rt);

	pOldBit = m_memDC.SelectObject(m_pBaseBitmap);
	// Imaging Operation..
	// .. MemDC 에다가 m_pBaseBitmap 의 비트맵을 그려넣어라 ~ !
	// .. 그런 후에 DC 에다가 MemDC 의 비트맵을 카피한다.
	m_DC.BitBlt(rt.left, rt.top, rt.Width(), rt.Height(), &m_memDC, rt.left, rt.top, dwRop);

	m_memDC.SelectObject(pOldBit);

	/*
	CBitmap *pOldBit;
	pOldBit = m_memDC.SelectObject( m_pBitmap );
	m_DC.BitBlt( x, y, nWidth, nHeight, &m_memDC, xSrc, ySrc, dwRop );
	m_memDC.SelectObject( pOldBit );
  */
	return	TRUE;
}

BOOL CImage::WriteDIB(LPCTSTR szFile,CPalette *pPal)
{
	m_pBaseBitmap ->WriteDIB(szFile, pPal);
	return	TRUE;
}

BOOL  CImage::BitBlt( int x, int y, int nWidth, int nHeight
					 , int xSrc, int ySrc, DWORD dwRop )
{
	CBitmap *pOldBit;
	pOldBit = m_memDC.SelectObject( m_pBitmap );
	m_DC.BitBlt( x, y, nWidth, nHeight, &m_memDC, xSrc, ySrc, dwRop );
	m_memDC.SelectObject( pOldBit );
	return	TRUE;
}

BOOL  CImage::ClearView( int x, int y, int nWidth, int nHeight )
{
	CBitmap	*pOldBit;
	pOldBit = m_memDC.SelectObject(m_pBitmap);
	m_DC.PatBlt( x, y, nWidth, nHeight, WHITENESS );
	m_memDC.PatBlt( x, y, nWidth, nHeight, WHITENESS );
	m_memDC.SelectObject(pOldBit);
	return	TRUE;
}

BOOL  CImage::ClearView( CRect rt )
{
	return	ClearView( rt.left, rt.top, rt.Width(), rt.Height() );
}

BOOL CImage::Rectangle( CRect rt )
{
	CBitmap	*pOldBit;
	pOldBit = m_memDC.SelectObject( m_pBitmap );
	m_DC.Rectangle( rt );
	m_memDC.Rectangle( rt );
	m_memDC.SelectObject( pOldBit );
	return	TRUE;
}

BOOL CImage::Rectangle( RECT rt )
{
	CRect	crt( rt );
	Rectangle( crt );
	return	TRUE;
}

BOOL CImage::Rectangle( INT left, INT top, INT right, INT bottom )
{
	CRect	rt( left, top, right, bottom );
	Rectangle(rt);
	return	TRUE;
}

BOOL CImage::Line( POINT pt1, POINT pt2 )
{
	CBitmap	*pOldBit;

	pOldBit = m_memDC.SelectObject( m_pBitmap );
	m_DC.MoveTo( pt1 );
	m_DC.LineTo( pt2 );
	m_memDC.MoveTo( pt1 );
	m_memDC.LineTo( pt2 );
	m_memDC.SelectObject(pOldBit);
	return	TRUE;
}

BOOL CImage::Line( CPoint pt1, CPoint pt2 )
{
	CBitmap *pOldBit;

	pOldBit = m_memDC.SelectObject(m_pBitmap);
	m_DC.MoveTo( pt1 );
	m_DC.LineTo( pt2 );
	m_memDC.MoveTo( pt1 );
	m_memDC.LineTo( pt2 );
	m_memDC.SelectObject(pOldBit);
	return	TRUE;
}

BOOL CImage::Point( CPoint pt )
{
	CBitmap *pOldBit;

	pOldBit = m_memDC.SelectObject(m_pBitmap);
	m_DC.SetPixelV( pt, RGB( 0, 0, 0 ) );
	m_memDC.SetPixelV( pt, RGB( 0, 0, 0 ) );
	m_memDC.SelectObject(pOldBit);
	return	TRUE;
}

BOOL CImage::Point( POINT pt )
{
	Point(pt);
	return	TRUE;
}

BOOL CImage::Circle( CPoint pt1, CPoint pt2 )
{
	CBitmap *pOldBit;
	CRect	rt( pt1, pt2 );

	pOldBit = m_memDC.SelectObject(m_pBitmap);
	m_DC.Ellipse( &rt );
	m_memDC.Ellipse( &rt );
	m_memDC.SelectObject(pOldBit);
	return	TRUE;
}

CImage::operator CWnd *()
{
	return	m_pWnd;
}

CImage::operator HWND()
{
	return	(HWND) m_pWnd;
}

CImage::operator HDC()
{
	return	(HDC)m_pWnd ->GetDC();
}

CImage::operator CClientDC *()
{
	return	(CClientDC *)m_pWnd ->GetDC();
}