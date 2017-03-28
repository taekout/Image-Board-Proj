// BaseBitmap.h: interface for the CBaseBitmap class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BASEBITMAP_H__E6CC60B9_F32F_400D_B7E2_42732088EAD5__INCLUDED_)
#define AFX_BASEBITMAP_H__E6CC60B9_F32F_400D_B7E2_42732088EAD5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CBaseBitmap : public CBitmap
{
public:
	BOOL WriteDIB(LPCTSTR szFile, CPalette *pPal);
	virtual BOOL DrawBitmap(CDC *dc, POINT Location, const CRect *WNDRect = NULL, 
							const CRect *IMGRect = NULL, DWORD dwRop  = SRCCOPY);

	virtual BOOL DrawBitmap(CDC *dc, POINT Location, const CRect *IMGRect);
	BOOL LoadBitmap(LPCTSTR FileName = NULL);
	void SetBitmapInfo();
	
	void GetBitmapRect(CRect &rect)
	{
		rect.top = 0;
		rect.left = 0;
		rect.right = m_spBmInfo->bmiHeader.biWidth; 
		rect.bottom = m_spBmInfo->bmiHeader.biHeight;
	};

	
	CBaseBitmap()
	{
		m_vpBitmap = NULL;
		m_lpFileName = NULL;
	};
	CBaseBitmap(LPCTSTR FileName, BOOL LoadBmp = TRUE)
	{
		m_vpBitmap = NULL;
		m_hPal = NULL;
		m_lpFileName = FileName;
		SetBitmapInfo();
		if(LoadBmp)
			LoadBitmap();
	};
	CBaseBitmap(HBITMAP hBitmap)
	{
		m_lpFileName = NULL;
		m_vpBitmap = NULL;
		m_hPal = NULL;
		m_hBitmap = hBitmap ;
		SetBitmapInfo();
	};
	virtual ~CBaseBitmap();

public:
	LPCTSTR	 	m_lpFileName;
	BITMAPINFO	*m_spBmInfo;
	BITMAP		m_sBm;
	HPALETTE	m_hPal;
	void*		m_vpBitmap;

public:
	HBITMAP		m_hBitmap;

};

#endif // !defined(AFX_BASEBITMAP_H__E6CC60B9_F32F_400D_B7E2_42732088EAD5__INCLUDED_)
