
// Hayeonsu.h : Hayeonsu ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.

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
