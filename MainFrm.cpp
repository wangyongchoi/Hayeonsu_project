#include "stdafx.h"
#include "Hayeonsu.h"
#include "wtypes.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,      
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

CMainFrame::CMainFrame()
{
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	if (cs.hMenu != NULL){
		::DestroyMenu(cs.hMenu);
		cs.hMenu = NULL;
	}

	cs.style &= ~(WS_THICKFRAME | WS_MAXIMIZEBOX); //화면크기 조절 및 최대화 제거.
	cs.style &= ~FWS_ADDTOTITLE;

	SIZE screen_size;
	ZeroMemory(&screen_size, sizeof(SIZE));
	screen_size.cx = (LONG)::GetSystemMetrics(SM_CXFULLSCREEN);
	screen_size.cy = (LONG)::GetSystemMetrics(SM_CYFULLSCREEN);
	//cs.cx = screen_size.cx - 10;
	//cs.cy = screen_size.cx * 0.68907563025210084033613445378151;

	cs.cx = 1190;
	cs.cy = 820;
	cs.x  = 5;
	cs.y  = 5;
	
	return TRUE;
}

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif
