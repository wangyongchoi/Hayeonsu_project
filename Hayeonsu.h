
// Hayeonsu.h : Hayeonsu 응용 프로그램에 대한 주 헤더 파일
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'stdafx.h'를 포함합니다."
#endif

#include "resource.h"       // 주 기호입니다.

class CHayeonsuApp : public CWinApp
{
public:
	CHayeonsuApp();

	ULONG_PTR mToken;

	virtual BOOL InitInstance();
	virtual int ExitInstance();


	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CHayeonsuApp theApp;
