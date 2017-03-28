// Image.h: interface for the CImage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMAGE_H__9A7CC319_D6E9_11D6_A4DC_00010297914C__INCLUDED_)
#define AFX_IMAGE_H__9A7CC319_D6E9_11D6_A4DC_00010297914C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseBitmap.h"

class CImage  
{
public:
	CImage( CWnd *pWnd );
	CImage( CWnd *pWnd, CDC *pDc );
	virtual ~CImage();

	// DC.
	virtual CDC * GetDC(void);
	virtual CDC * GetMemDC(void);
	virtual CBitmap * GetMemoryBitmap(void);

	// Image Method

	// Bitmap Loader + Drawer => LoadBitmap();
	virtual BOOL LoadBitmap(/* CDC *dc, */ POINT Location,
						/* const CRect *WNDRect, const CRect *IMGRect, */
					DWORD dwRop = SRCCOPY, LPCTSTR szFile = NULL );
	virtual BOOL WriteDIB(LPCTSTR szFile,CPalette *pPal);

	// Blirt
	virtual BOOL BitBlt( int x, int y, int nWidth
						, int nHeight, int xSrc,
						int ySrc, DWORD dwRop );
	// Clear
	virtual BOOL ClearView( int x, int y, int nWidth
						, int nHeight );
	virtual BOOL ClearView( CRect rt );

	// Line
	virtual BOOL Line( POINT pt1, POINT pt2 );
	virtual BOOL Line( CPoint pt1, CPoint pt2 );
//	virtual BOOL Line( CSize sz );

	// Point
	virtual BOOL Point( CPoint pt );
	virtual BOOL Point( POINT pt );

	// Rectangle
	virtual BOOL Rectangle( CRect rt );
	virtual BOOL Rectangle( RECT rt );
	virtual BOOL Rectangle( INT left, INT top, INT right, INT bottom );

	// Circle
//	virtual BOOL Circle( CSize sz );
	virtual BOOL Circle( CPoint pt1, CPoint pt2 );

	// Operator Function
	virtual operator CWnd *();
	virtual operator HWND();
	virtual operator HDC();
	virtual operator CClientDC *();

protected:
	CBitmap	*m_pBitmap;
	CDC		m_DC;
	CDC		m_memDC;
	CWnd	*m_pWnd;

	CBaseBitmap *m_pBaseBitmap;
//	CBaseBitmap *m_pBaseBitmapMem;

};

#endif // !defined(AFX_IMAGE_H__9A7CC319_D6E9_11D6_A4DC_00010297914C__INCLUDED_)