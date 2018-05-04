#include "stdafx.h"
#include "Sound.h"
#include "Digitalv.h"

Sound::Sound()
{
	dwID = 0xffff;
}
Sound::~Sound()
{
}
int Sound::Open(LPCTSTR lpszWave,int type)
{
	MCI_OPEN_PARMS mciOpenParms;
	if (type == 0)
		mciOpenParms.lpstrDeviceType = L"WaveAudio";
	else if (type == 1)
		mciOpenParms.lpstrDeviceType = L"MPEGvideo";
	mciOpenParms.lpstrElementName = lpszWave;
	if (mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT,
		(DWORD)&mciOpenParms))
	{
		dwID = 0xffff;
		return 0;
	}
	dwID = mciOpenParms.wDeviceID;
	return 1;
}
void Sound::Close()
{
	if (dwID == 0xffff) return;
	MCI_GENERIC_PARMS mciGenericParms;
	mciSendCommand(dwID, MCI_PAUSE, MCI_WAIT, (DWORD)&mciGenericParms);
	dwID = 0xffff;
}
int Sound::Play(HWND hWnd)
{
	if (dwID == 0xffff) return 0;
	MCI_PLAY_PARMS mciPlayParms;
	mciPlayParms.dwCallback = (DWORD)hWnd;
	if (mciSendCommand(dwID, MCI_PLAY, MCI_NOTIFY, (DWORD)&mciPlayParms))
		return 0;

	return 1;
}
int Sound::PlayLoop(HWND hWnd)
{
	if (dwID == 0xffff) return 0;
	MCI_PLAY_PARMS mciPlayParms;
	mciPlayParms.dwCallback = (DWORD)hWnd;
	if (mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)&mciPlayParms))
		return 0;

	return 1;
}
DWORD Sound::GetPos()
{
	if (dwID == 0xffff) return 0xffff;
	MCI_STATUS_PARMS mciStatusParms;
	mciStatusParms.dwItem = MCI_STATUS_POSITION;
	mciSendCommand(dwID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD)&mciStatusParms);

	return mciStatusParms.dwReturn;
}
void Sound::SetPos(DWORD Pos)
{
	if (dwID == 0xffff) return;
	MCI_SEEK_PARMS mciSeekParms;
	mciSeekParms.dwTo = Pos;
	mciSendCommand(dwID, MCI_SEEK, MCI_TO, (DWORD)&mciSeekParms);

}
void Sound::MoveStartPos()
{
	if (dwID == 0xffff) return;
	MCI_SEEK_PARMS mciSeekParms;
	mciSendCommand(dwID, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)&mciSeekParms);
}
void Sound::MoveEndPos()
{
	if (dwID == 0xffff) return;
	MCI_SEEK_PARMS mciSeekParms;
	mciSendCommand(dwID, MCI_SEEK, MCI_SEEK_TO_END, (DWORD)&mciSeekParms);
}
void Sound::Stop()
{
	if (dwID == 0xffff) return;
	MCI_GENERIC_PARMS mciGenericParms;
	mciSendCommand(dwID, MCI_STOP, MCI_WAIT, (DWORD)&mciGenericParms);
}