#pragma once
#include "stdafx.h"
#ifndef SHARED_HANDLERS
#include "Hayeonsu.h"
#endif
#include "MainFrm.h"
#include "HayeonsuDoc.h"
#include "HayeonsuView.h"
#include <mmsystem.h>
#include "Digitalv.h"
#include <stdlib.h>


#pragma comment(lib,"winmm.lib")

void __stdcall ScoreCounter(HWND, UINT, UINT_PTR, DWORD);
void __stdcall CoinTurnTimer(HWND, UINT, UINT_PTR, DWORD);
void __stdcall GrowLength(HWND, UINT, UINT_PTR, DWORD);
void __stdcall BabyTimer(HWND, UINT, UINT_PTR, DWORD);
void __stdcall Legend1TurnDirectionTimer(HWND, UINT, UINT_PTR, DWORD);
void __stdcall Legend2TurnDirectionTimer(HWND, UINT, UINT_PTR, DWORD);
void __stdcall Legend3TurnDirectionTimer(HWND, UINT, UINT_PTR, DWORD);
void __stdcall ItemApplyTimer(HWND, UINT, UINT_PTR, DWORD);
void __stdcall ItemCreateTimer(HWND, UINT, UINT_PTR, DWORD);

IMPLEMENT_DYNCREATE(CHayeonsuView, CView)
BEGIN_MESSAGE_MAP(CHayeonsuView, CView)
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()
CHayeonsuView::CHayeonsuView()
: mBackGround(L"./image/playBck.jpg")
, mIntroBackGround(L"./image/initBck.jpg")
, mQuitBackGround(L"./image/quitBck.jpg")
, mTimer(9), mMode(INTRO), mLife(LIFE), mQuit(0)
, mRestartButtonShape(0)
, mQuitButtonShape(0)
, mRank1Score(0), mRank2Score(0), mRank3Score(0)
{
	timer_queue.push(9); timer_queue.push(8); timer_queue.push(7);
	timer_queue.push(6); timer_queue.push(5); timer_queue.push(4);
	timer_queue.push(3); timer_queue.push(2); timer_queue.push(1);
	timer_queue.push(0);
	mode_stack.push(true);
	debug_mode = false;
	::InitializeCriticalSection(&mSc);
}

CHayeonsuView::~CHayeonsuView()
{
	::DeleteCriticalSection(&mSc);
}

BOOL CHayeonsuView::PreCreateWindow(CREATESTRUCT& cs)
{

	cs.cx = 1200;
	cs.cy = 800;
	cs.x = 10;
	cs.y = 10;
	return CView::PreCreateWindow(cs);
}
void CHayeonsuView::OnDraw(CDC* pDC)
{
	CHayeonsuDoc *pDoc = (CHayeonsuDoc *)GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
}

BOOL CHayeonsuView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}
void CHayeonsuView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}
void CHayeonsuView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}
#ifdef _DEBUG
void CHayeonsuView::AssertValid() const
{
	CView::AssertValid();
}
void CHayeonsuView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
CHayeonsuDoc* CHayeonsuView::GetDocument() const
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHayeonsuDoc)));
	return (CHayeonsuDoc *) m_pDocument;
}
#endif
void CHayeonsuView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CMainFrame    *pMain = (CMainFrame    *) theApp.GetMainWnd();
	CHayeonsuView *pView = (CHayeonsuView *) pMain->GetActiveView();
	CHayeonsuDoc  *pDoc  = GetDocument();
	if (mMode == INTRO){
		introBgm.Stop();
		ResetEvent(hIntroMode);
		mMode = GAME;
		mLife = LIFE;
		PlaySound(L"./sound/legend.wav", NULL, SND_FILENAME | SND_ASYNC);
		playBgm.PlayLoop(this->m_hWnd);
		SetTimer(1,   100,				ScoreCounter);
		SetTimer(2,   250,			   CoinTurnTimer);
		SetTimer(3, 10000,				  GrowLength);
		SetTimer(4,  1000,				   BabyTimer);
		SetTimer(5,  1600, Legend1TurnDirectionTimer);
		SetTimer(6,  1800, Legend2TurnDirectionTimer);
		SetTimer(7,  2000, Legend3TurnDirectionTimer);
		SetTimer(8, 20000,           ItemCreateTimer);
		SetEvent(hGameMode);
	}
	else if (mLife == LIFE && mMode == GAME){
		switch (nChar){

		case VK_LEFT:; break;
		case VK_RIGHT:; break;
		case VK_UP:; break;
		case VK_DOWN:; break;

		}

		if (nChar == VK_LEFT){
			keyInputWav.MoveStartPos();
			keyInputWav.Play(this->m_hWnd);
			pDoc->user.TurnDirection(WEST);
		}
		else if (nChar == VK_RIGHT){
			keyInputWav.MoveStartPos();
			keyInputWav.Play(this->m_hWnd);
			pDoc->user.TurnDirection(EAST);
		}
		else if (nChar == VK_UP){
			keyInputWav.MoveStartPos();
			keyInputWav.Play(this->m_hWnd);
			pDoc->user.TurnDirection(NORTH);
		}
		else if (nChar == VK_DOWN){
			keyInputWav.MoveStartPos();
			keyInputWav.Play(this->m_hWnd);
			pDoc->user.TurnDirection(SOUTH);
		}
		else if(nChar == 'd' || nChar == 'D'){
			
			if (mode_stack.top() == true)
			{
				debug_mode = mode_stack.top();
				mode_stack.pop();
				mode_stack.push(false);
			}
			else
			{
				debug_mode = mode_stack.top();
				mode_stack.pop();
				mode_stack.push(true);
			}
		}
	}
}
int CHayeonsuView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	introBgm.Open(L"./sound/opening.mp3", MP3);
	playBgm.Open(L"./sound/playing.mp3", MP3);
	endingBgm.Open(L"./sound/ending.mp3", MP3);
	keyInputWav.Open(L"./sound/keyInput.wav", WAV);
	kkobugiWav.Open(L"./sound/kkobugi.wav", WAV);

	hIntroMode = CreateEvent(NULL, TRUE, FALSE, NULL);
	hGameMode  = CreateEvent(NULL, TRUE, FALSE, NULL);
	hQuitMode  = CreateEvent(NULL, TRUE, FALSE, NULL);

	SetEvent(hIntroMode);
	introBgm.PlayLoop(this->m_hWnd);

	return 0;
}
void CHayeonsuView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	CHayeonsuDoc *pDoc = GetDocument();

	CRect rc;
	GetClientRect(rc);

	mAllBmp  = new Bitmap(rc.right, rc.bottom);
	mAllGrfx = new Graphics(mAllBmp);

	mTurtleKingBmp  = Bitmap::FromResource(AfxGetInstanceHandle(), (WCHAR*)MAKEINTRESOURCE(IDB_TURTLEKING));
	mTurtleBabyBmp  = Bitmap::FromResource(AfxGetInstanceHandle(), (WCHAR*)MAKEINTRESOURCE(IDB_TURTLEBABY));
	mHeartBmp	    = Bitmap::FromResource(AfxGetInstanceHandle(), (WCHAR*)MAKEINTRESOURCE(IDB_HEART));
	mCoinBmp	    = Bitmap::FromResource(AfxGetInstanceHandle(), (WCHAR*)MAKEINTRESOURCE(IDB_COIN));
	mItemBmp	    = Bitmap::FromResource(AfxGetInstanceHandle(), (WCHAR*)MAKEINTRESOURCE(IDB_ITEM));
	mLegend1Bmp	    = Bitmap::FromResource(AfxGetInstanceHandle(), (WCHAR*)MAKEINTRESOURCE(IDB_LEGEND1));
	mLegend2Bmp     = Bitmap::FromResource(AfxGetInstanceHandle(), (WCHAR*)MAKEINTRESOURCE(IDB_LEGEND2));
	mLegend3Bmp     = Bitmap::FromResource(AfxGetInstanceHandle(), (WCHAR*)MAKEINTRESOURCE(IDB_LEGEND3));
	mDeadBmp	    = Bitmap::FromResource(AfxGetInstanceHandle(), (WCHAR*)MAKEINTRESOURCE(IDB_DEAD));
	mQuitButton     = Bitmap::FromResource(AfxGetInstanceHandle(), (WCHAR*)MAKEINTRESOURCE(IDB_QUITBUTTON));
	mRestartButton  = Bitmap::FromResource(AfxGetInstanceHandle(), (WCHAR*)MAKEINTRESOURCE(IDB_RESTARTBUTTON));
	mItemApply      = Bitmap::FromResource(AfxGetInstanceHandle(), (WCHAR*)MAKEINTRESOURCE(IDB_ITEMAPPLY));
	mItemApply2     = Bitmap::FromResource(AfxGetInstanceHandle(), (WCHAR*)MAKEINTRESOURCE(IDB_ITEMAPPLY2));
	mGoldFull       = Bitmap::FromResource(AfxGetInstanceHandle(), (WCHAR*)MAKEINTRESOURCE(IDB_GOLDFULL));
	mDeadApply      = Bitmap::FromResource(AfxGetInstanceHandle(), (WCHAR*)MAKEINTRESOURCE(IDB_DEADAPPLY));
	mDangerous      = Bitmap::FromResource(AfxGetInstanceHandle(), (WCHAR*)MAKEINTRESOURCE(IDB_DANGEROUS));

	imageAttr. SetColorKey(RGB(255, 255, 255), RGB(255, 255, 255));
	imageAttr2.SetColorKey(RGB(  0,   0,   0), RGB(  0,   0,   0));

	/////////////////////////////////////인트로모드
	
	AfxBeginThread(DrawIntroProc, this);

	/////////////////////////////////////게임모드
	AfxBeginThread(CreateCoinProc, this);
	AfxBeginThread(DrawProc, this);
	AfxBeginThread(CollisionProc, this);
	//////////////////////////////////////종료모드

	AfxBeginThread(DrawQuitProc, this);
}
void CHayeonsuView::OnTimer(UINT_PTR nIDEvent)
{
	playBgm.Stop();
	Sleep(2000);
	endingBgm.PlayLoop(this->m_hWnd);
	KillTimer(9);
}
UINT __cdecl DrawIntroProc(void *p)
{
	CHayeonsuView *pView = (CHayeonsuView *) p;
	CHayeonsuDoc  *pDoc  = pView->GetDocument();
	Graphics grfx(pView->m_hWnd);
	while (pView->mQuit == 0)
	{
		::WaitForSingleObject(hIntroMode, INFINITE);
		Sleep(1);
		pView->mAllGrfx->DrawImage(&pView->mIntroBackGround, 0, 0);
		grfx.DrawImage(pView->mAllBmp, 0, 0);
		Sleep(0);
	}
	return 0;
}
UINT __cdecl DrawProc(void *p)
{
	CHayeonsuView *pView = (CHayeonsuView *) p;
	CHayeonsuDoc  *pDoc = pView->GetDocument();
	Graphics grfx(pView->m_hWnd);
	while (pView->mQuit == 0)
	{
		::WaitForSingleObject(hGameMode, INFINITE);
		KillTimer(pView->m_hWnd,0);
		Sleep(1);
		int p_x = pDoc->user.GetUserPos().x;
		int p_y = pDoc->user.GetUserPos().y;

		pView->mAllGrfx->DrawImage(&pView->mBackGround, 0, 0);

		pView->mAllGrfx->DrawImage(pView->mHeartBmp,
							      Rect(HEART_INFO_X, HEART_INFO_Y, HEARTWIDTH, HEARTHEIGHT),
								  0, 0, HEARTWIDTH, HEARTHEIGHT,
								  UnitPixel,
								  &pView->imageAttr);
		
		pView->mAllGrfx->DrawImage(pView->mTurtleBabyBmp,
								  Rect(BABYTIMERX, BABYTIMERY, TURTLEBABYWIDTH, TURTLEBABYHEIGHT),
								  0, TURTLEBABYHEIGHT*2, TURTLEBABYWIDTH, TURTLEBABYHEIGHT,
								  UnitPixel,
								  &pView->imageAttr);

		CString str1;
		Gdiplus::Font F1(L"HY견고딕", 20, FontStyleRegular, UnitPixel);
		SolidBrush W(Color(255, 255, 255));
		SolidBrush R(Color(255,   0,   0));
		if (pDoc->info.GetgoldCount() != pDoc->user.GetLength())
		{
			str1.Format(L"\"꼬부기와 함께 전설의 포켓몬을 피해 동전을 모으세요!!\"");
		}
		else
		{
			str1.Format(L"\"꼬부기한테는 동전이 너무 무거워요! 성으로 옮겨주세요!\"");
		}
		pView->mAllGrfx->DrawString(str1, -1, &F1, PointF(20, 20), &W);

		CString timer;
		timer.Format(L"%d", pView->mTimer);
		Gdiplus::Font F2(L"Arial", 25, FontStyleBold, UnitPixel);
		pView->mAllGrfx->DrawString(timer, -1, &F2, PointF(627, 20), &W);

		CString coin;
		coin.Format(L"( %d / %d )", pDoc->info.GetgoldCount(), pDoc->user.GetLength());
		Gdiplus::Font F(L"Arial", 20, FontStyleBold, UnitPixel);
		if (pDoc->info.GetgoldCount() == pDoc->user.GetLength())
			pView->mAllGrfx->DrawString(coin, -1, &F, PointF(768, 20), &R);
		else
			pView->mAllGrfx->DrawString(coin, -1, &F, PointF(768, 20), &W);
		CString score;
		score.Format(L"%d point", pDoc->info.GetScore());
		pView->mAllGrfx->DrawString(score, -1, &F, PointF(926, 20), &W);


		std::list<CPoint>::iterator it;
		for (it = pDoc->object.goldPos.begin(); it != pDoc->object.goldPos.end(); ++it)
		{
			pView->mAllGrfx->DrawImage(pView->mCoinBmp,
	             				      Rect(it->x, it->y, COINWIDTH, COINHEIGHT),
									  COINWIDTH*pView->mNum, 0, COINWIDTH, COINHEIGHT,
									  UnitPixel,
									  &pView->imageAttr);
			Sleep(0);
			if (pView->debug_mode == true) {
				//충돌영역테스트//////////////////////////////////////////
				Rect rc(it->x, it->y, COINWIDTH, COINHEIGHT);
				Pen pen(Color::Black);
				pView->mAllGrfx->DrawRectangle(&pen, rc);
				/////////////////////////////////////////////////
			}
		}
		if (p_x <= LIFEAREA_LEFT + TURTLEKINGWIDTH - 20 || p_x >= LIFEAREA_RITE - TURTLEKINGWIDTH - 40 || p_y <= LIFEAREA_TOP + TURTLEKINGHEIGHT - 20 || p_y >= LIFEAREA_BOTTOM - TURTLEKINGHEIGHT - 40){
			Rect lifeArea(LIFEAREA_LEFT, LIFEAREA_TOP, LIFEAREA_RITE - LIFEAREA_LEFT, LIFEAREA_BOTTOM - LIFEAREA_TOP);
			Pen  pen(Color::IndianRed);
			pView->mAllGrfx->DrawRectangle(&pen, lifeArea);

			if (pView->mLife == LIFE){
			if (pDoc->user.GetDirection() == EAST || pDoc->user.GetDirection() == WEST)
				pView->mAllGrfx->DrawImage(pView->mDangerous,
										   Rect(p_x + TURTLEKINGWIDTH / 2 - 5, p_y - 15, ITEMAPPLYWIDTH, ITEMAPPLYHEIGHT),
										   0, 0, ITEMAPPLYWIDTH, ITEMAPPLYHEIGHT, UnitPixel, &pView->imageAttr);
			else if (pDoc->user.GetDirection() == NORTH || pDoc->user.GetDirection() == SOUTH)
				pView->mAllGrfx->DrawImage(pView->mDangerous,
										   Rect(p_x + TURTLEKINGWIDTH / 2 - 15, p_y - 20, ITEMAPPLYWIDTH, ITEMAPPLYHEIGHT),
										   0, 0, ITEMAPPLYWIDTH, ITEMAPPLYHEIGHT, UnitPixel, &pView->imageAttr);
			}
		}
		if (pDoc->object.itemPos.x != -1)
			pView->mAllGrfx->DrawImage(pView->mItemBmp,
									  Rect(pDoc->object.itemPos.x, pDoc->object.itemPos.y,ITEMWIDTH, ITEMHEIGHT),
									  ITEMWIDTH*pView->mItemColor, 0, ITEMWIDTH, ITEMHEIGHT, UnitPixel, &pView->imageAttr);

		if (pView->debug_mode == true) {
			//충돌영역테스트////////////////////////////////////////////////////////////////////////////////////////////////////
			Rect rc1(pDoc->object.itemPos.x+2, pDoc->object.itemPos.y+2, ITEMWIDTH-3, ITEMHEIGHT-3);
			Pen pen(Color::Black);
			pView->mAllGrfx->DrawRectangle(&pen, rc1);
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		}
		if (pView->mLife == LIFE){
			for (int i = 1; i < pDoc->user.GetLength(); i++){
				pView->mAllGrfx->DrawImage(pView->mTurtleBabyBmp,
										  Rect(pDoc->user.tail[i * 5].tailPos.x, pDoc->user.tail[i * 5].tailPos.y, TURTLEBABYWIDTH, TURTLEBABYHEIGHT),
										  TURTLEBABYWIDTH  * pDoc->user.GetStep(),
										  TURTLEBABYHEIGHT * pDoc->user.tail[i * 5].turnDirection,
										  TURTLEBABYWIDTH,
										  TURTLEBABYHEIGHT,
										  UnitPixel,
										  &pView->imageAttr);

				if (pView->debug_mode == true) {
					//충돌영역테스트///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					Rect rc2(pDoc->user.tail[i * 5].tailPos.x+30, pDoc->user.tail[i * 5].tailPos.y+40, TURTLEBABYWIDTH/8, TURTLEBABYHEIGHT/8);
					Pen pen(Color::Black);
					pView->mAllGrfx->DrawRectangle(&pen, rc2);
					///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				}
			}
			pView->mAllGrfx->DrawImage(pView->mTurtleKingBmp,
									  Rect(p_x, p_y, TURTLEKINGWIDTH, TURTLEKINGHEIGHT),
									  TURTLEKINGWIDTH * pDoc->user.GetStep(),
									  TURTLEKINGHEIGHT * pDoc->user.GetDirection(),
									  TURTLEKINGWIDTH,
									  TURTLEKINGHEIGHT,
									  UnitPixel,
									  &pView->imageAttr);

			if (pDoc->user.userState == FASTITEM){
				if (pDoc->user.GetDirection() == EAST || pDoc->user.GetDirection() == WEST)
					pView->mAllGrfx->DrawImage(pView->mItemApply,
											  Rect(p_x + TURTLEKINGWIDTH / 2 - 5, p_y - 15, ITEMAPPLYWIDTH, ITEMAPPLYHEIGHT),
											  0, 0, ITEMAPPLYWIDTH, ITEMAPPLYHEIGHT, UnitPixel, &pView->imageAttr);
				else if (pDoc->user.GetDirection() == NORTH || pDoc->user.GetDirection() == SOUTH)
					pView->mAllGrfx->DrawImage(pView->mItemApply,
											  Rect(p_x + TURTLEKINGWIDTH / 2 - 15, p_y - 20, ITEMAPPLYWIDTH, ITEMAPPLYHEIGHT),
											  0, 0, ITEMAPPLYWIDTH, ITEMAPPLYHEIGHT, UnitPixel, &pView->imageAttr);
			}
			else if (pDoc->user.userState == SLOWITEM){

				if (pDoc->user.GetDirection() == EAST || pDoc->user.GetDirection() == WEST)
					pView->mAllGrfx->DrawImage(pView->mItemApply2,
											  Rect(p_x + TURTLEKINGWIDTH / 2 - 5, p_y - 15, ITEMAPPLYWIDTH, ITEMAPPLYHEIGHT),
											  0, 0, ITEMAPPLYWIDTH, ITEMAPPLYHEIGHT, UnitPixel, &pView->imageAttr);
				else if (pDoc->user.GetDirection() == NORTH || pDoc->user.GetDirection() == SOUTH)
					pView->mAllGrfx->DrawImage(pView->mItemApply2,
											  Rect(p_x + TURTLEKINGWIDTH / 2 - 15, p_y - 20, ITEMAPPLYWIDTH, ITEMAPPLYHEIGHT),
											  0, 0, ITEMAPPLYWIDTH, ITEMAPPLYHEIGHT, UnitPixel, &pView->imageAttr);
			}
			else if (pDoc->user.GetLength() == pDoc->info.GetgoldCount()){

				if (pDoc->user.GetDirection() == EAST || pDoc->user.GetDirection() == WEST)
					pView->mAllGrfx->DrawImage(pView->mGoldFull,
											  Rect(p_x + TURTLEKINGWIDTH / 2 - 5, p_y - 15, ITEMAPPLYWIDTH, ITEMAPPLYHEIGHT),
											  0, 0, ITEMAPPLYWIDTH, ITEMAPPLYHEIGHT, UnitPixel, &pView->imageAttr);
				else if (pDoc->user.GetDirection() == NORTH || pDoc->user.GetDirection() == SOUTH)
					pView->mAllGrfx->DrawImage(pView->mGoldFull,
											  Rect(p_x + TURTLEKINGWIDTH / 2 - 15, p_y - 20, ITEMAPPLYWIDTH, ITEMAPPLYHEIGHT),
											  0, 0, ITEMAPPLYWIDTH, ITEMAPPLYHEIGHT, UnitPixel, &pView->imageAttr);
			}
		}
		else if (pView->mLife == DEAD)
		{
			pView->mAllGrfx->DrawImage(pView->mDeadApply,
				                       Rect(p_x - 4, p_y - 30, ITEMAPPLYWIDTH, ITEMAPPLYHEIGHT),
				                       0, 0, ITEMAPPLYWIDTH, ITEMAPPLYHEIGHT, UnitPixel, &pView->imageAttr);

			pView->mAllGrfx->DrawImage(pView->mDeadBmp,
									   Rect(p_x, p_y, DEADWIDTH, DEADHEIGHT),
									   0, 0, DEADWIDTH, DEADHEIGHT, UnitPixel, &pView->imageAttr);
		}

		if (pView->debug_mode == true) {
			//충돌영역테스트///////////////////////////////////////////////////////////////////////////////////////////////////////
			Rect rc3(p_x + TURTLEKINGWIDTH / 4, p_y + TURTLEKINGHEIGHT / 3, TURTLEKINGWIDTH / 2, TURTLEKINGHEIGHT / 2);
			Pen pen1(Color::Black);
			pView->mAllGrfx->DrawRectangle(&pen1, rc3);
			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		}

		pView->mAllGrfx->DrawImage(pView->mLegend1Bmp,
								  Rect(pDoc->legend1.mPos.x, pDoc->legend1.mPos.y, LEGEND_WIDTH, LEGEND_HEIGHT),
								  LEGEND_WIDTH  * pDoc->legend1.GetStep(),
								  LEGEND_HEIGHT * pDoc->legend1.GetDirection(),
								  LEGEND_WIDTH,
								  LEGEND_HEIGHT,
								  UnitPixel,
								  &pView->imageAttr);

		pView->mAllGrfx->DrawImage(pView->mLegend2Bmp,
								  Rect(pDoc->legend2.mPos.x, pDoc->legend2.mPos.y, LEGEND_WIDTH, LEGEND_HEIGHT),
								  LEGEND_WIDTH  * pDoc->legend2.GetStep(),
								  LEGEND_HEIGHT * pDoc->legend2.GetDirection(),
								  LEGEND_WIDTH,
								  LEGEND_HEIGHT,
								  UnitPixel,
								  &pView->imageAttr);

		pView->mAllGrfx->DrawImage(pView->mLegend3Bmp,
								  Rect(pDoc->legend3.mPos.x, pDoc->legend3.mPos.y, LEGEND_WIDTH, LEGEND_HEIGHT),
								  LEGEND_WIDTH  * pDoc->legend3.GetStep(),
								  LEGEND_HEIGHT * pDoc->legend3.GetDirection(),
								  LEGEND_WIDTH,
								  LEGEND_HEIGHT,
								  UnitPixel,
								  &pView->imageAttr);

		if (pView->debug_mode == true) {
			//충돌영역테스트/////////////////////////////////////////////////////////////////////////////////////////////////
			Rect rc4(pDoc->legend1.mPos.x + 15, pDoc->legend1.mPos.y + 15, LEGEND_WIDTH / 2, LEGEND_HEIGHT / 2);
			Rect rc5(pDoc->legend2.mPos.x + 15, pDoc->legend2.mPos.y + 15, LEGEND_WIDTH / 2, LEGEND_HEIGHT / 2);
			Rect rc6(pDoc->legend3.mPos.x + 15, pDoc->legend3.mPos.y + 15, LEGEND_WIDTH / 2, LEGEND_HEIGHT / 2);
			Pen pen2(Color::Black);
			pView->mAllGrfx->DrawRectangle(&pen2, rc4);
			pView->mAllGrfx->DrawRectangle(&pen2, rc5);
			pView->mAllGrfx->DrawRectangle(&pen2, rc6);
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		}

		if (pView->debug_mode == true) {
			//충돌영역테스트////////////////////////////////////////////////////////////////////////////////////////////////////////
			Rect rc7(LIFEAREA_LEFT,		    	0,  LIFEAREA_RITE - LIFEAREA_LEFT,			      LIFEAREA_TOP - 0 );
			Rect rc8(			   0,    LIFEAREA_TOP,			    LIFEAREA_LEFT - 0,  LIFEAREA_BOTTOM - LIFEAREA_TOP );
			Rect rc9(LIFEAREA_LEFT, LIFEAREA_BOTTOM,  LIFEAREA_RITE - LIFEAREA_LEFT,           800 - LIFEAREA_BOTTOM );
			Rect rc10(LIFEAREA_RITE,    LIFEAREA_TOP,           1200 - LIFEAREA_RITE,  LIFEAREA_BOTTOM - LIFEAREA_TOP );
			Pen pen3(Color::Black);
			pView->mAllGrfx->DrawRectangle(&pen3, rc7);
			pView->mAllGrfx->DrawRectangle(&pen3, rc8);
			pView->mAllGrfx->DrawRectangle(&pen3, rc9);
			pView->mAllGrfx->DrawRectangle(&pen3, rc10);
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		}
		grfx.DrawImage(pView->mAllBmp, 0, 0);

		if (pView->mLife == LIFE){
			pDoc->user.MoveUser();
			pDoc->legend1.Move();
			pDoc->legend2.Move();
			pDoc->legend3.Move();
			Sleep(0);
		}
		else if (pView->mLife == DEAD){
			
			//score load
			pView->LoadScore();
			pView->SaveScore();

			SetTimer(pView->m_hWnd,9,0,NULL);
			Sleep(2500);
			ResetEvent(hGameMode);
			SetEvent(hQuitMode);
		}
	}
	return 0;
}

void CHayeonsuView::LoadScore()
{
	CMainFrame    *pMain = (CMainFrame    *)theApp.GetMainWnd();
	CHayeonsuView *pView = (CHayeonsuView *)pMain->GetActiveView();
	CHayeonsuDoc  *pDoc = GetDocument();

	std::ifstream ifs("./res/rankScoreFile.txt");
	Wangyong_List<int> scoreList;
	std::string line;
	while (!ifs.eof())
	{
		int temp = 0;
		std::getline(ifs, line);
		temp = std::stoi(line);
		scoreList.push_back(temp);
	}

	ifs.close();

	int count = 0;
	int currentScore = pDoc->info.GetScore();
	scoreList.push_back(currentScore);
	scoreList.sort();
	for (int i = 0; i < 3; ++i)
	{
		int score = scoreList.end()->data;
		scoreList.pop_back();
		if (i == 0)
			mRank1Score = score;
		else if (i == 1)
			mRank2Score = score;
		else if (i == 2)
			mRank3Score = score;
	}
}
void CHayeonsuView::SaveScore()
{
	std::ofstream ofs("./res/rankScoreFile.txt");
	std::string score = std::to_string(mRank1Score);
	score.append("\n");
	score.append(std::to_string(mRank2Score));
	score.append("\n");
	score.append(std::to_string(mRank3Score));
	char* charp = new char[score.size() + 1];
	strcpy_s(charp, score.size() + 1, score.c_str());
	ofs.write(charp, score.size());


	ofs.close();
}

UINT __cdecl DrawQuitProc(void *p)
{
	CHayeonsuView *pView = (CHayeonsuView *) p;
	CHayeonsuDoc  *pDoc  = pView->GetDocument();
	Graphics grfx(pView->m_hWnd);
	
	while (pView->mQuit == 0)
	{
		::WaitForSingleObject(hQuitMode, INFINITE);
		Sleep(1);
		pView->mAllGrfx->DrawImage(&pView->mQuitBackGround, 0, 0);

		pView->mAllGrfx->DrawImage(pView->mHeartBmp,
								   Rect(470, 263, HEARTWIDTH, HEARTHEIGHT),
								   0, 0, HEARTWIDTH, HEARTHEIGHT,
								   UnitPixel,
								   &pView->imageAttr);

		
		
		CString score, rank1, rank2, rank3 ;

		Gdiplus::Font F(L"HY견고딕", 20, FontStyleRegular, UnitPixel);
		SolidBrush W(Color(255, 255, 255));
		score.Format(L"%d point 달성!!!", pDoc->info.GetScore());
		rank1.Format(L"1st  : %d point!",pView->mRank1Score);
		rank2.Format(L"2nd : %d point", pView->mRank2Score);
		rank3.Format(L"3rd  : %d point", pView->mRank3Score);

		pView->SaveScore();

		pView->mAllGrfx->DrawString(score, -1, &F, PointF(SCOREMESSAGEPOS_X, SCOREMESSAGEPOS_Y), &W);
		
		pView->mAllGrfx->DrawString(rank1, -1, &F, PointF(RANKPOS_X, RANKPOS_Y), &W);
		pView->mAllGrfx->DrawString(rank2, -1, &F, PointF(RANKPOS_X, RANKPOS_Y + 30), &W);
		pView->mAllGrfx->DrawString(rank3, -1, &F, PointF(RANKPOS_X, RANKPOS_Y + 60), &W);

		pView->mAllGrfx->DrawImage(pView->mRestartButton,
								   Rect(RESTARTBUTTONPOS_X, RESTARTBUTTONPOS_Y, BUTTONWIDTH, BUTTONHEIGHT),
								   72, 56 + (BUTTONHEIGHT + 20)*pView->mRestartButtonShape, BUTTONWIDTH, BUTTONHEIGHT,
								   UnitPixel,
								   &pView->imageAttr2);

		pView->mAllGrfx->DrawImage(pView->mQuitButton,
								   Rect(RESTARTBUTTONPOS_X, RESTARTBUTTONPOS_Y + BUTTONHEIGHT + 20, BUTTONWIDTH, BUTTONHEIGHT),
								   72, 56 + (BUTTONHEIGHT + 20)*pView->mQuitButtonShape, BUTTONWIDTH, BUTTONHEIGHT,
								   UnitPixel,
								   &pView->imageAttr2);
		grfx.DrawImage(pView->mAllBmp, 0, 0);
		Sleep(0);
	}
	return  0;
}
UINT __cdecl CreateCoinProc(void *p)
{
	CHayeonsuView *pView = (CHayeonsuView *)p;
	CHayeonsuDoc  *pDoc  = pView->GetDocument();
	while (pView->mQuit == 0){
		::WaitForSingleObject(hGameMode, INFINITE);
		Sleep(1);
		if (pDoc->object.GetGoldCount() == 0)
		{
			::EnterCriticalSection(&pView->mSc);
			pDoc->object.CreateGold(20);
			pDoc->object.CopyGoldPosToVector(&pView->mTempGold);
			::LeaveCriticalSection(&pView->mSc);
		}
		Sleep(0);
	}
	return 0;
}
UINT __cdecl CollisionProc(void *p)
{
	CHayeonsuView *pView = (CHayeonsuView *)p;
	CHayeonsuDoc  *pDoc  = pView->GetDocument();
	while (pView->mQuit == 0){
		::WaitForSingleObject(hGameMode, INFINITE);
		Sleep(1);
		::EnterCriticalSection(&pView->mSc);
		pDoc->user.SetValidateArea();
		pDoc->legend1.SetValidateArea();
		pDoc->legend2.SetValidateArea();
		pDoc->legend3.SetValidateArea();
		int legend1Collision = pDoc->legend1.CollisionWithBaby();
		int legend2Collision = pDoc->legend2.CollisionWithBaby();
		int legend3Collision = pDoc->legend3.CollisionWithBaby();

		::LeaveCriticalSection(&pView->mSc);
		if (pDoc->user.CollisionWithGold(&pDoc->object) == true)
		{
			if (pDoc->info.GetgoldCount() < pDoc->user.GetLength())
				pDoc->info.IncreaseGoldCount();

			PlaySound(L"./sound/coin.wav", NULL, SND_FILENAME | SND_ASYNC);
		}
		else if (pDoc->user.CollisionWithItem(&pDoc->object) == true)
		{
			pDoc->user.userState = 1 + rand() % 2;
			if      (pDoc->user.userState == FASTITEM)
				pDoc->user.SetSpeed(FAST);
			else if (pDoc->user.userState == SLOWITEM)
				pDoc->user.SetSpeed(SLOW);
			SetTimer(pView->m_hWnd, 8, 10000, ItemApplyTimer);
			PlaySound(L"./sound/itemApply.wav", NULL, SND_FILENAME | SND_ASYNC);
		}
		else if (pDoc->user.CollisionWithBaby() == true)
		{
			PlaySound(L"./sound/dead.wav", NULL, SND_FILENAME | SND_SYNC);
			SetEvent(hQuitMode);
		}
		else if (pDoc->user.CollisionWithCastle() == true)
		{
			while (pDoc->info.GetgoldCount() > 0)
			{
				pDoc->info.mGoldCount--;
				Sleep(100);
				pDoc->info.mScore += 500;
				PlaySound(L"./sound/change.wav", NULL, SND_FILENAME | SND_ASYNC);
			}
		}
		else if (legend1Collision != -1)
		{
			pDoc->user.SetLength(legend1Collision);
			pDoc->info.mGoldCount = legend1Collision;
			PlaySound(L"./sound/legend.wav", NULL, SND_FILENAME | SND_ASYNC);
		}
		else if (legend2Collision != -1)
		{
			pDoc->user.SetLength(legend2Collision);
			pDoc->info.mGoldCount = legend2Collision;
			PlaySound(L"./sound/legend.wav", NULL, SND_FILENAME | SND_ASYNC);
		}
		else if (legend3Collision != -1)
		{
			pDoc->user.SetLength(legend3Collision);
			pDoc->info.mGoldCount = legend3Collision;
			PlaySound(L"./sound/legend.wav", NULL, SND_FILENAME | SND_ASYNC);
		}
		else if (pDoc->user.CollisionWithTree() == true)
		{
			PlaySound(L"./sound/dead.wav", NULL, SND_FILENAME | SND_SYNC);
			SetEvent(hQuitMode);
		}
		else if (pDoc->user.CollisionWithLegend() == true)
		{
			PlaySound(L"./sound/dead.wav", NULL, SND_FILENAME | SND_SYNC);
			SetEvent(hQuitMode);
		}
		Sleep(0);
	}
	return 0;
}

void CHayeonsuView::DeleteCoin(int x, int y)
{
	CHayeonsuDoc *pDoc = GetDocument();
	CPoint pt(x, y);
	pDoc->object.DeleteGoldPos(pt);
	pDoc->object.DeleteValidateGoldPos(pt);
}
void CHayeonsuView::DeleteItem()
{
	CHayeonsuDoc *pDoc = GetDocument();
	pDoc->object.itemPos.x = -1;
}

bool operator==(Rect rc1, Rect rc2)
{
	if (rc1.X == rc2.X && rc1.Y == rc2.Y && rc1.Width == rc2.Width&& rc1.Height == rc2.Height)
		return true;
	return false;
}

void __stdcall Legend1TurnDirectionTimer(HWND, UINT, UINT_PTR, DWORD)
{
	CMainFrame    *pMain = (CMainFrame    *) theApp.GetMainWnd();
	CHayeonsuDoc  *pDoc  = (CHayeonsuDoc  *) pMain->GetActiveDocument();
	CHayeonsuView *pView = (CHayeonsuView *) pMain->GetActiveView();
	if (pView->mMode == GAME){
		int direction;
		while (true){
			direction = rand() % 4;
			if (pDoc->legend1.GetDirection() == NORTH && direction != SOUTH)
				break;
			else if (pDoc->legend1.GetDirection() == SOUTH && direction != NORTH)
				break;
			else if (pDoc->legend1.GetDirection() == WEST && direction != EAST)
				break;
			else if (pDoc->legend1.GetDirection() == EAST && direction != WEST)
				break;
		}
		pDoc->legend1.TurnDirection(direction);
		Sleep(0);
	}
}
void __stdcall Legend2TurnDirectionTimer(HWND, UINT, UINT_PTR, DWORD)
{
	CMainFrame    *pMain = (CMainFrame    *) theApp.GetMainWnd();
	CHayeonsuDoc  *pDoc  = (CHayeonsuDoc  *) pMain->GetActiveDocument();
	CHayeonsuView *pView = (CHayeonsuView *) pMain->GetActiveView();
	if (pView->mMode == GAME){
		int direction;
		while (true){
			direction = rand() % 4;
			if (pDoc->legend2.GetDirection() == NORTH && direction != SOUTH)
				break;
			else if (pDoc->legend2.GetDirection() == SOUTH && direction != NORTH)
				break;
			else if (pDoc->legend2.GetDirection() == WEST && direction != EAST)
				break;
			else if (pDoc->legend2.GetDirection() == EAST && direction != WEST)
				break;
		}
		pDoc->legend2.TurnDirection(direction);
		Sleep(0);
	}
}
void __stdcall Legend3TurnDirectionTimer(HWND, UINT, UINT_PTR, DWORD)
{
	CMainFrame    *pMain = (CMainFrame    *) theApp.GetMainWnd();
	CHayeonsuDoc  *pDoc  = (CHayeonsuDoc  *) pMain->GetActiveDocument();
	CHayeonsuView *pView = (CHayeonsuView *) pMain->GetActiveView();
	if (pView->mMode == GAME){
		int direction;
		while (true){
			direction = rand() % 4;
			if		(pDoc->legend3.GetDirection() == NORTH && direction != SOUTH)
				break;
			else if (pDoc->legend3.GetDirection() == SOUTH && direction != NORTH)
				break;
			else if (pDoc->legend3.GetDirection() == WEST  && direction != EAST )
				break;
			else if (pDoc->legend3.GetDirection() == EAST  && direction != WEST )
				break;
		}
		pDoc->legend3.TurnDirection(direction);
		Sleep(0);
	}
}

void __stdcall ScoreCounter(HWND, UINT, UINT_PTR, DWORD)
{
	CMainFrame    *pMain = (CMainFrame    *) theApp.GetMainWnd();
	CHayeonsuDoc  *pDoc  = (CHayeonsuDoc  *) pMain->GetActiveDocument();
	CHayeonsuView *pView = (CHayeonsuView *) pMain->GetActiveView();
	if (pView->mMode == GAME && pView->mLife == LIFE){
		pDoc->info.IncreaseScore(1);
		Sleep(0);
	}
}
void __stdcall CoinTurnTimer(HWND, UINT, UINT_PTR, DWORD)
{
	CMainFrame    *pMain = (CMainFrame    *) theApp.GetMainWnd();
	CHayeonsuView *pView = (CHayeonsuView *) pMain->GetActiveView();
	if (pView->mMode == GAME && pView->mLife == LIFE){
		pView->mNum = (pView->mNum + 1) % 3;
		Sleep(0);
	}
}
void __stdcall GrowLength(HWND, UINT, UINT_PTR, DWORD)
{
	CMainFrame    *pMain = (CMainFrame    *) theApp.GetMainWnd();
	CHayeonsuView *pView = (CHayeonsuView *) pMain->GetActiveView();
	CHayeonsuDoc  *pDoc  = (CHayeonsuDoc  *) pMain->GetActiveDocument();
	if (pView->mMode == GAME && pView->mLife == LIFE){
		pDoc -> user.GrowLength();
		pView-> kkobugiWav.MoveStartPos();
		pView-> kkobugiWav.Play(pView->m_hWnd);
		Sleep(0);
	}
}
void __stdcall BabyTimer(HWND, UINT, UINT_PTR, DWORD)
{
	CMainFrame    *pMain = (CMainFrame   *) theApp.GetMainWnd();
	CHayeonsuView *pView = (CHayeonsuView*) pMain->GetActiveView();

	if (pView->mMode == GAME && pView->mLife == LIFE){

		pView->mTimer = pView->timer_queue.front();
		pView->timer_queue.pop();
		pView->timer_queue.push(pView->mTimer);
		Sleep(0);
	}
}
void __stdcall ItemCreateTimer(HWND, UINT, UINT_PTR, DWORD)
{
	CMainFrame    *pMain = (CMainFrame    *) theApp.GetMainWnd();
	CHayeonsuView *pView = (CHayeonsuView *) pMain->GetActiveView();
	CHayeonsuDoc  *pDoc  = (CHayeonsuDoc  *) pView->GetDocument();
	if (pView->mMode == GAME && pView->mLife == LIFE){
		if (pDoc->object.CreateItem() == true){
			pView->mItemColor = rand() % 7;
			Sleep(0);
		}
	}
	else
		return;
}
void CHayeonsuView::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (mMode == QUIT && mLife == DEAD)
	{
		if      (point.x >= RESTARTBUTTONPOS_X && point.x <= RESTARTBUTTONPOS_X + BUTTONWIDTH && point.y >= RESTARTBUTTONPOS_Y && point.y <= RESTARTBUTTONPOS_Y + BUTTONHEIGHT)
			mRestartButtonShape = 2;
		else if (point.x >= RESTARTBUTTONPOS_X && point.x <= RESTARTBUTTONPOS_X + BUTTONWIDTH && point.y >= RESTARTBUTTONPOS_Y + BUTTONHEIGHT + 20 && point.y <= RESTARTBUTTONPOS_Y + BUTTONHEIGHT * 2 + 20)
			mQuitButtonShape = 2;
	}
}
void CHayeonsuView::OnLButtonUp(UINT nFlags, CPoint point)
{
	CMainFrame    *pMain = (CMainFrame    *) theApp.GetMainWnd();
	CHayeonsuView *pView = (CHayeonsuView *) pMain->GetActiveView();
	CHayeonsuDoc  *pDoc  = (CHayeonsuDoc  *) pMain->GetActiveDocument();
	if (mMode == QUIT && mLife == DEAD)
	{
		if (point.x >= RESTARTBUTTONPOS_X && point.x <= RESTARTBUTTONPOS_X + BUTTONWIDTH && point.y >= RESTARTBUTTONPOS_Y && point.y <= RESTARTBUTTONPOS_Y + BUTTONHEIGHT){
			::EnterCriticalSection(&mSc);
			mRestartButtonShape = 0;
			PlaySound(L"./sound/select.wav", NULL, SND_FILENAME | SND_ASYNC);
			pDoc->user.InitAllData();
			pDoc->object.InitAllData();
			pDoc->info.InitAllData();
			pDoc->legend1.InitAllData(LEGEND1STARTPOS_X, LEGEND1STARTPOS_Y, WEST);
			pDoc->legend2.InitAllData(LEGEND2STARTPOS_X, LEGEND2STARTPOS_Y, EAST);
			pDoc->legend3.InitAllData(LEGEND3STARTPOS_X, LEGEND3STARTPOS_Y, NORTH);
			mTimer = 9;	mMode = GAME; mLife = LIFE;
			mTempGold.clear();
			KillTimer(0);	KillTimer(1);
			KillTimer(2);	KillTimer(3);
			KillTimer(4);	KillTimer(5);
			KillTimer(6);	KillTimer(7);
			KillTimer(8);
			SetTimer(0, 30000, NULL);						SetTimer(1,   100,              ScoreCounter);
			SetTimer(2,   250,             CoinTurnTimer);	SetTimer(3, 10000,                GrowLength);
			SetTimer(4,  1000,                 BabyTimer);	SetTimer(5,  1600, Legend1TurnDirectionTimer);
			SetTimer(6,  1800, Legend2TurnDirectionTimer);	SetTimer(7,  2000, Legend3TurnDirectionTimer);
			SetTimer(8, 20000,			 ItemCreateTimer);
			::LeaveCriticalSection(&mSc);
			endingBgm.Stop();
			endingBgm.MoveStartPos();
			playBgm.MoveStartPos();
			playBgm.PlayLoop(pView->m_hWnd);
			ResetEvent(hQuitMode);
			SetEvent(hGameMode);
		}
		else if (point.x >= RESTARTBUTTONPOS_X && point.x <= RESTARTBUTTONPOS_X + BUTTONWIDTH && point.y >= RESTARTBUTTONPOS_Y + BUTTONHEIGHT + 20 && point.y <= RESTARTBUTTONPOS_Y + BUTTONHEIGHT * 2 + 20){
			mQuitButtonShape = 0;
			pView->mQuit = 1;
			ResetEvent(hIntroMode);
			ResetEvent(hGameMode);
			ResetEvent(hQuitMode);
			PostQuitMessage(0);
		}
	}
}
void CHayeonsuView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (mMode == QUIT && mLife == DEAD)
	{
		if (point.x >= RESTARTBUTTONPOS_X && point.x <= RESTARTBUTTONPOS_X + BUTTONWIDTH && point.y >= RESTARTBUTTONPOS_Y && point.y <= RESTARTBUTTONPOS_Y + BUTTONHEIGHT){
			mRestartButtonShape = 1;
		}
		else if (point.x >= RESTARTBUTTONPOS_X && point.x <= RESTARTBUTTONPOS_X + BUTTONWIDTH && point.y >= RESTARTBUTTONPOS_Y + BUTTONHEIGHT + 20 && point.y <= RESTARTBUTTONPOS_Y + BUTTONHEIGHT * 2 + 20){
			mQuitButtonShape = 1;
		}
		else{
			mRestartButtonShape = 0; 
			mQuitButtonShape = 0;
		}
	}
}
void __stdcall ItemApplyTimer(HWND, UINT, UINT_PTR, DWORD)
{
	CMainFrame    *pMain = (CMainFrame    *) theApp.GetMainWnd();
	CHayeonsuView *pView = (CHayeonsuView *) pMain->GetActiveView();
	CHayeonsuDoc  *pDoc  = (CHayeonsuDoc  *) pMain->GetActiveDocument();
	pDoc->user.userState = NONE;
	pDoc->user.SetSpeed(NORMAL);
	KillTimer(pView->m_hWnd,8);
}