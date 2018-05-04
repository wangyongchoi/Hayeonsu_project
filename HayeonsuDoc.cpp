#include "stdafx.h"

#ifndef SHARED_HANDLERS
#include "Hayeonsu.h"
#endif

#include "HayeonsuDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CHayeonsuDoc, CDocument)

BEGIN_MESSAGE_MAP(CHayeonsuDoc, CDocument)
END_MESSAGE_MAP()

CHayeonsuDoc::CHayeonsuDoc() 
:legend1(LEGEND1STARTPOS_X, LEGEND1STARTPOS_Y ,WEST )
,legend2(LEGEND2STARTPOS_X, LEGEND2STARTPOS_Y, EAST )
,legend3(LEGEND3STARTPOS_X, LEGEND3STARTPOS_Y, NORTH)
{
	User user;
	Object object;
}

CHayeonsuDoc::~CHayeonsuDoc()
{
}

BOOL CHayeonsuDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}


void CHayeonsuDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CHayeonsuDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CHayeonsuDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CHayeonsuDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif

#ifdef _DEBUG
void CHayeonsuDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CHayeonsuDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif