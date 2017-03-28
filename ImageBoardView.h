// ImageBoardView.h : interface of the CImageBoardView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMAGEBOARDVIEW_H__9A7CC311_D6E9_11D6_A4DC_00010297914C__INCLUDED_)
#define AFX_IMAGEBOARDVIEW_H__9A7CC311_D6E9_11D6_A4DC_00010297914C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ImageBoardDoc.h"

class CImageBoardView : public CView
{
public:
	// Member Variables
	CPoint	m_pt1, m_pt2;
	CRect	m_rt;
//	CImageBoardDoc	*m_pDoc;
	BOOL	m_bLButtonDown;


protected: // create from serialization only
	CImageBoardView();
	DECLARE_DYNCREATE(CImageBoardView)

// Attributes
public:
	CImageBoardDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImageBoardView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CImageBoardView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CImageBoardView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ImageBoardView.cpp
inline CImageBoardDoc* CImageBoardView::GetDocument()
   { return (CImageBoardDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGEBOARDVIEW_H__9A7CC311_D6E9_11D6_A4DC_00010297914C__INCLUDED_)
