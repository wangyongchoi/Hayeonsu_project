#pragma once
#include "Sound.h"
#include <vector>
#include <list>
#include "Wangyong_List.h"
#include "Wangyong_Queue.h"
#include "Wangyong_Stack.h"
#include <fstream>
#include <string>
#include <iterator>
#include <iostream>
#include <functional> 

class CHayeonsuView : public CView
{

public:
	
	int		 debug_mode;
	int		 mMode, mNum, mItemColor, mTimer, mLife, mQuit;
	int		 mRestartButtonShape, mQuitButtonShape;

	int		 mRank1Score, mRank2Score, mRank3Score;
	Image    mBackGround, mIntroBackGround, mQuitBackGround;
	Bitmap   *mAllBmp;
	Bitmap   *mTurtleKingBmp, *mTurtleBabyBmp,
		     *mHeartBmp,      *mCoinBmp,
			 *mItemBmp,       *mTrainerBmp,
			 *mLegend1Bmp,    *mLegend2Bmp,
			 *mLegend3Bmp,    *mDeadBmp,
	         *mFacebookButton,*mQuitButton,
		     *mRestartButton, *mItemApply,
			 *mItemApply2,    *mGoldFull,
			 *mDeadApply,     *mDangerous;

	Graphics *mAllGrfx;
	ImageAttributes imageAttr, imageAttr2; //imageAttr(rgb(255,255,255) 捧疙贸府) , imageAttr2(rgb(0,0,0) 捧疙贸府)
	std::vector<CPoint> mTempGold;

	enum{ WAV = 0, MP3 };

	Sound introBgm, playBgm, endingBgm, itemBgm, itemBgm2,
		  changeWav, coinWav, deadWav, facebookWav, growWav,
	      itemDropWav, keyInputWav, pauseWav, selectWav,
	      itemApplyWav, kkobugiWav;

	CRITICAL_SECTION mSc;

	Wangyong_Queue<int> timer_queue;
	Wangyong_Stack<bool> mode_stack;

	CHayeonsuView();
	DECLARE_DYNCREATE(CHayeonsuView);
	CHayeonsuDoc* GetDocument() const;

	void DeleteCoin(int x, int y);
	void DeleteItem();

	void LoadScore();
	void SaveScore();

	virtual void OnDraw(CDC* pDC);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	virtual ~CHayeonsuView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


	DECLARE_MESSAGE_MAP()
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void OnInitialUpdate();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG
inline CHayeonsuDoc* CHayeonsuView::GetDocument() const
   { return reinterpret_cast<CHayeonsuDoc*>(m_pDocument); }
#endif

UINT __cdecl DrawProc(void *p);
UINT __cdecl CreateCoinProc(void *p);
UINT __cdecl CollisionProc(void *p);
UINT __cdecl TrainerProc(void *p);
UINT __cdecl DrawIntroProc(void *p);
UINT __cdecl DrawQuitProc(void *p);