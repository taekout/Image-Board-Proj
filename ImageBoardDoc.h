// ImageBoardDoc.h : interface of the CImageBoardDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMAGEBOARDDOC_H__9A7CC30F_D6E9_11D6_A4DC_00010297914C__INCLUDED_)
#define AFX_IMAGEBOARDDOC_H__9A7CC30F_D6E9_11D6_A4DC_00010297914C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Image.h"


class CImageBoardDoc : public CDocument
{
protected: // create from serialization only
	CImageBoardDoc();
	DECLARE_DYNCREATE(CImageBoardDoc)

// Attributes
public:
	CImage	*m_pImage;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImageBoardDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CImageBoardDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CImageBoardDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGEBOARDDOC_H__9A7CC30F_D6E9_11D6_A4DC_00010297914C__INCLUDED_)
