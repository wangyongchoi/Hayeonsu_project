#pragma once
#pragma comment(lib, "winmm.lib")
#include <Windows.h>
#include <mmsystem.h>
class Sound
{
	DWORD dwID;
	
public:
	 Sound();
	~Sound();
	enum{ WAV = 0, MP3 };
	int   Open(LPCTSTR lpszWave, int type = 0); //type�� 0�̸� wav, 1�̸� mp3
	void  Close();
	int   Play(HWND hWnd);
	int   PlayLoop(HWND hWnd);
	DWORD GetPos();
	void  SetPos(DWORD Pos);
	void  MoveStartPos();
	void  MoveEndPos();
	void  Stop();
};