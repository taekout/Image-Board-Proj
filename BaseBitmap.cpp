// BaseBitmap.cpp: implementation of the CBaseBitmap class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BaseBitmap.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CBaseBitmap::~CBaseBitmap()
{
	::DeleteObject(m_hBitmap); 
	free(m_spBmInfo);
}

BOOL CBaseBitmap::LoadBitmap(LPCTSTR FileName)
{
	HDC		hDC;
	hDC = ::GetDC(NULL);
	HPALETTE	oldhPal = NULL;
	DWORD dwHederSize;
	if(FileName)
	{
		m_lpFileName = FileName;
		SetBitmapInfo();
	}
	CFile	file(m_lpFileName, CFile::modeRead | CFile::typeBinary);
	if(m_hPal)
	{
		oldhPal = ::SelectPalette(hDC,m_hPal,TRUE);
		::RealizePalette(hDC);
	}

	int nColors = (1 << m_spBmInfo->bmiHeader.biBitCount);
	if(nColors > 256)
		nColors = 0;
	
	dwHederSize = sizeof(BITMAPFILEHEADER) + sizeof(m_spBmInfo->bmiHeader) + nColors * sizeof(RGBQUAD);
	
	if(!m_spBmInfo->bmiHeader.biSizeImage)
		m_spBmInfo->bmiHeader.biSizeImage = file.GetLength() - dwHederSize;

	m_hBitmap = CreateDIBSection(hDC, m_spBmInfo, (DWORD)DIB_RGB_COLORS, 
									(void **) &m_vpBitmap, NULL, 0);
	m_hObject = m_hBitmap;
	file.Seek(dwHederSize, CFile::begin);
	file.Read(m_vpBitmap, m_spBmInfo->bmiHeader.biHeight * 
						m_spBmInfo->bmiHeader.biWidth * m_spBmInfo->bmiHeader.biBitCount/8);
	
	::SelectPalette(hDC,oldhPal,TRUE);
	::RealizePalette(hDC);
	ReleaseDC(NULL, hDC);
	if(!m_hBitmap)
		return FALSE;
	return TRUE;
}

void CBaseBitmap::SetBitmapInfo()
{
	BITMAPFILEHEADER	bmpHeader;
	BITMAPINFOHEADER    sBmInfo;

	LOGPALETTE  *lpLogPal;
	
	int		i,j;
	if(m_lpFileName)
	{
		CFile	file(m_lpFileName, CFile::modeRead | CFile::typeBinary);
		
		file.Read(&bmpHeader, sizeof(bmpHeader));
		file.Read(&sBmInfo,sizeof(sBmInfo));
		int	nColors = (1 << sBmInfo.biBitCount);
		if(nColors > 256)
			nColors = 0;
		
		if(nColors)
		{
			m_spBmInfo = (BITMAPINFO*)malloc(sizeof(BITMAPINFO)+sizeof(RGBQUAD)*nColors-1);
			m_spBmInfo->bmiHeader = sBmInfo;
			lpLogPal = (LOGPALETTE*)malloc(sizeof(LOGPALETTE) + 255*sizeof(PALETTEENTRY));
			lpLogPal->palVersion=0x300;
			lpLogPal->palNumEntries=256;
	
			file.Read(m_spBmInfo->bmiColors,sizeof(RGBQUAD)*nColors);
			for(i = j = 0; i < 256; i++, j++)
			{
				lpLogPal->palPalEntry[i].peRed = m_spBmInfo->bmiColors[j].rgbRed;
				lpLogPal->palPalEntry[i].peGreen = m_spBmInfo->bmiColors[j].rgbGreen;
				lpLogPal->palPalEntry[i].peBlue = m_spBmInfo->bmiColors[j].rgbRed;
			}
			m_hPal = CreatePalette(lpLogPal);
			free(lpLogPal);
		}
		else
		{
			m_spBmInfo = (BITMAPINFO*)malloc(sizeof(BITMAPINFOHEADER));
			m_spBmInfo->bmiHeader = sBmInfo;
		}
		
	}
	else
	{
		::GetObject((HGDIOBJ)m_hBitmap,sizeof(m_sBm),(LPSTR)&m_sBm);
		int colors = 1<<(m_sBm.bmPlanes * m_sBm.bmBitsPixel);
		if(colors > 256)
			colors = 0;
		if(colors)
			m_spBmInfo = (BITMAPINFO*)malloc(sizeof(BITMAPINFOHEADER));
		else
			m_spBmInfo = (BITMAPINFO*)malloc(sizeof(BITMAPINFO)+sizeof(RGBQUAD)*colors-1);
		m_spBmInfo->bmiHeader.biSize				= sizeof(BITMAPINFOHEADER);
		m_spBmInfo->bmiHeader.biWidth				= m_sBm.bmWidth;
		m_spBmInfo->bmiHeader.biHeight 				= m_sBm.bmHeight;
		m_spBmInfo->bmiHeader.biPlanes 				= 1;
		m_spBmInfo->bmiHeader.biBitCount			= m_sBm.bmPlanes * m_sBm.bmBitsPixel;
		m_spBmInfo->bmiHeader.biCompression			= BI_RGB;
		m_spBmInfo->bmiHeader.biSizeImage			= 0;
		m_spBmInfo->bmiHeader.biXPelsPerMeter		= 0;
		m_spBmInfo->bmiHeader.biYPelsPerMeter		= 0;
		m_spBmInfo->bmiHeader.biClrUsed				= 0;
		m_spBmInfo->bmiHeader.biClrImportant		= 0;
	}

}

BOOL CBaseBitmap::DrawBitmap(CDC *dc, POINT Location, const CRect *IMGRect)
{
	return DrawBitmap(dc, Location, NULL, IMGRect);
}

BOOL CBaseBitmap::DrawBitmap(CDC *dc, POINT Location, const CRect *WNDRect, 
							 const CRect *IMGRect, DWORD dwRop)
{
	CDC			bitmapDC;
	BOOL		temp;
	CRect		Rect(0,0,0,0);
	HBITMAP		hOldBitmap;
	HPALETTE	oldhPal = NULL;
	bitmapDC.CreateCompatibleDC(dc);
	hOldBitmap = (HBITMAP)::SelectObject(bitmapDC.GetSafeHdc(), m_hBitmap);

	if(IMGRect)
		temp = dc->BitBlt(Location.x, Location.y, IMGRect->Width(), IMGRect->Height(), 
						  &bitmapDC, IMGRect->left, IMGRect->top, dwRop);
	else if(WNDRect)
		temp = dc->BitBlt(Location.x, Location.y, WNDRect->right, 
						  WNDRect->bottom, &bitmapDC, 0, 0, dwRop);
	else
		temp = dc->BitBlt(Location.x, Location.y, m_spBmInfo->bmiHeader.biWidth, 
							m_spBmInfo->bmiHeader.biHeight, &bitmapDC, IMGRect->left, IMGRect->top, dwRop);
	if(!temp)
		return FALSE;
	return TRUE;
}

BOOL CBaseBitmap::WriteDIB(LPCTSTR szFile,CPalette *pPal)
{
	HPALETTE			hPal;
	HDC					hDC;

	if(pPal)
	{
		hPal = (HPALETTE) pPal->GetSafeHandle();
		if(hPal==NULL)
			hPal = (HPALETTE) GetStockObject(DEFAULT_PALETTE);
	}
	

	hDC = GetDC(NULL);
	hPal = SelectPalette(hDC,hPal,FALSE);
	RealizePalette(hDC);
	
	int nColors = (1 << m_spBmInfo->bmiHeader.biBitCount);
	if( nColors > 256 )
		nColors = 0;
	GetDIBits(hDC, m_hBitmap, 0L, (DWORD)m_spBmInfo->bmiHeader.biHeight,
			(LPBYTE)NULL, m_spBmInfo, (DWORD)DIB_RGB_COLORS);
	
	
	
	if (m_spBmInfo->bmiHeader.biSizeImage == 0)
	{
		m_spBmInfo->bmiHeader.biSizeImage = 
			((((m_spBmInfo->bmiHeader.biWidth * m_spBmInfo->bmiHeader.biBitCount) + 31) & ~31) / 8)
																	* m_spBmInfo->bmiHeader.biHeight;

		// If a compression scheme is used the result may infact be larger
		// Increase the size to account for this.
		if (m_spBmInfo->bmiHeader.biCompression != BI_RGB)
			m_spBmInfo->bmiHeader.biSizeImage = (m_spBmInfo->bmiHeader.biSizeImage * 3) / 2;
	}
	if(!m_vpBitmap)
		m_vpBitmap = (LPSTR)malloc(m_spBmInfo->bmiHeader.biSizeImage);
	
	if (!m_vpBitmap)
	{
		SelectPalette(hDC,hPal,FALSE);
		ReleaseDC(NULL,hDC);
		return FALSE;
	}

	BOOL bGotBits = GetDIBits(hDC, m_hBitmap, 0L, (DWORD)m_spBmInfo->bmiHeader.biHeight,
								m_vpBitmap, m_spBmInfo,(DWORD)DIB_RGB_COLORS);
	if( !bGotBits )
	{
		//free(m_vpBitmap);

		SelectPalette(hDC,hPal,FALSE);
		ReleaseDC(NULL,hDC);
		return FALSE;
	}

	SelectPalette(hDC,hPal,FALSE);
	ReleaseDC(NULL,hDC);
	
	if (!m_vpBitmap)
		return FALSE;
	if(!szFile)
	{
		//free(m_vpBitmap);
		return FALSE;
	}
	

	nColors = 1 << m_spBmInfo->bmiHeader.biBitCount;

	if( nColors > 256 ) 
		nColors = 0;

	CFile file;
	BITMAPFILEHEADER	hdr;

	if( !file.Open(szFile, CFile::modeWrite|CFile::modeCreate) )
		return FALSE;
	
	hdr.bfType	= ((WORD) ('M' << 8) | 'B');	// is always "BM"
	hdr.bfSize		= m_spBmInfo->bmiHeader.biSizeImage + sizeof(m_spBmInfo->bmiHeader) + sizeof(hdr) + sizeof(RGBQUAD) * nColors;
	hdr.bfReserved1 = 0;
	hdr.bfReserved2 = 0;
	hdr.bfOffBits	= (DWORD) (sizeof( hdr ) + m_spBmInfo->bmiHeader.biSize + nColors * sizeof(RGBQUAD));
	
	file.Write(&hdr, sizeof(hdr));

	if(nColors)
		file.Write(m_spBmInfo,sizeof(BITMAPINFO)+sizeof(RGBQUAD)*nColors-1);
	else
		file.Write(&(m_spBmInfo->bmiHeader), sizeof(m_spBmInfo->bmiHeader));

	file.Write(m_vpBitmap, m_spBmInfo->bmiHeader.biSizeImage);
	
	//free(m_vpBitmap);
	return TRUE;
}