
// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이 
// 들어 있는 포함 파일입니다.

#pragma once
#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
#endif
#include "targetver.h"
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 일부 CString 생성자는 명시적으로 선언됩니다.
// MFC의 공통 부분과 무시 가능한 경고 메시지에 대한 숨기기를 해제합니다.
#define _AFX_ALL_WARNINGS
#include <afxwin.h>         // MFC 핵심 및 표준 구성 요소입니다.
#include <afxext.h>         // MFC 확장입니다.
#include <afxdisp.h>        // MFC 자동화 클래스입니다.
#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // Internet Explorer 4 공용 컨트롤에 대한 MFC 지원입니다.
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // Windows 공용 컨트롤에 대한 MFC 지원입니다.
#endif // _AFX_NO_AFXCMN_SUPPORT
#include <afxcontrolbars.h>     // MFC의 리본 및 컨트롤 막대 지원


#include <gdiplus.h>
#include <afxdisp.h>
using namespace Gdiplus;

bool operator==(Rect rc1, Rect rc2);

static HANDLE hIntroMode, hGameMode, hQuitMode;

#define MAXLENGTH 50
#define STEP 7

enum MODE            { INTRO, GAME, QUIT};
enum LIFE            { LIFE, DEAD };
enum DIECCT			 { SOUTH, WEST, EAST, NORTH };
enum ITEMTYPE		 { NONE, FASTITEM, SLOWITEM };
enum SPEED			 { NORMAL = 7, SLOW = 3, FAST = 14};
enum CASTLE			 { CASTLE_POS_X       =  47, CASTLE_POS_Y       =  139, 
					   CASTLE_WIDTH       =  95, CASTLE_HEIGHT      =   93 };
enum LIFEAREA		 { LIFEAREA_LEFT      =  47, LIFEAREA_RITE      = 1123,
					   LIFEAREA_TOP       = 139, LIFEAREA_BOTTOM    =  725 };
enum STATEMESSAGE	 { STATEMESSAGE_X     =  21, STATEMESSAGE_Y     =   17 };
enum COININFO		 { COIN_INFO_X        = 753, COIN_INFO_Y        =   17 };
enum HEARTINFO		 { HEART_INFO_X       = 876, HEART_INFO_Y       =   17 };
enum COIN			 { COINWIDTH	      =  12, COINHEIGHT	        =   16 };
enum TURTLEKING		 { TURTLEKINGWIDTH    =  64, TURTLEKINGHEIGHT   =   64 };
enum TURTLEBABY		 { TURTLEBABYWIDTH    =  64, TURTLEBABYHEIGHT   =   64 };
enum TRAINER		 { TRAINERWIDTH	      =  50, TRAINERHEIGHT      =   63 };
enum ITEM			 { ITEMWIDTH	      =  22, ITEMHEIGHT	        =   21 };
enum DEAD			 { DEADWIDTH	      =  20, DEADHEIGHT	        =   20 };
enum ITEMAPPLY		 { ITEMAPPLYWIDTH     =  28, ITEMAPPLYHEIGHT    =   27 };
enum HEART			 { HEARTWIDTH	      =  28, HEARTHEIGHT        =   25 };
enum STARTPOS		 { STARTPOSX	      = 141, STARTPOSY		    =  654 };
enum BABYTIMER		 { BABYTIMERX	      = 562, BABYTIMERY	        =  -10 };
enum LEGEND          { LEGEND_WIDTH       =  64, LEGEND_HEIGHT      =   65 };
enum BUTTON          { BUTTONWIDTH        = 245, BUTTONHEIGHT       =   50 };
enum LEGEND1STARTPOS { LEGEND1STARTPOS_X  = 930, LEGEND1STARTPOS_Y  =  161 };
enum LEGEND2STARTPOS { LEGEND2STARTPOS_X  = 500, LEGEND2STARTPOS_Y  =  200 };
enum LEGEND3STARTPOS { LEGEND3STARTPOS_X  = 100, LEGEND3STARTPOS_Y  =  799 };
enum RESTARTBUTTONPOS{ RESTARTBUTTONPOS_X = 490, RESTARTBUTTONPOS_Y =  450 };
enum SCOREMESSAGEPOS { SCOREMESSAGEPOS_X  = 520, SCOREMESSAGEPOS_Y  =  270 };
enum RANKPOS		 { RANKPOS_X		  = 520, RANKPOS_Y			=  330 };
enum COLLISIONTYPE	 { NOCOLLISION, CASTLE, STONE, COIN, ITEM, TRAINER, USER, WOOD};

#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


