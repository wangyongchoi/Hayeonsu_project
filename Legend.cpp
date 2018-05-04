#include "stdafx.h"
#include "Legend.h"
#include "Hayeonsu.h"
#include "MainFrm.h"
#include "HayeonsuDoc.h"
#include "HayeonsuView.h"

Legend::Legend(int x, int y, int direction) :mPos(x, y), mStep(0), mDirection(direction), mSpeed(5)
{
}

Legend::~Legend()
{
}

int Legend::CollisionWithBaby()
{
	CMainFrame    *pMain = (CMainFrame    *) theApp.GetMainWnd();
	CHayeonsuView *pView = (CHayeonsuView *) pMain->GetActiveView();
	CHayeonsuDoc  *pDoc  = (CHayeonsuDoc  *) pView->GetDocument();
	for (int i = 1; i < pDoc->user.GetLength(); i++){
		Rect baby(pDoc->user.tail[i * 5].tailPos.x + 30, pDoc->user.tail[i * 5].tailPos.y + 40, TURTLEBABYWIDTH / 8, TURTLEBABYHEIGHT / 8);
		if (mValiateAreaLegend.IntersectsWith(baby) == TRUE){
			if (pDoc->info.GetScore() >= 1000 * (pDoc->user.GetLength() - i))
				pDoc->info.IncreaseScore(-1000 * (pDoc->user.GetLength()-i));
			else if (pDoc->info.GetScore() >= 1000)
				pDoc->info.mScore = 0;
			return i;
		}
	}
	return -1;
}
int Legend::GetStep()
{
	return mStep;
}

int Legend::GetDirection()
{
	return mDirection;
}

void Legend::Move()
{
	Step();
	if (mDirection == NORTH)
	{
		if (mPos.y - mSpeed > LIFEAREA_TOP)
			mPos.y -= mSpeed;
		else
			TurnDirection(SOUTH);
	}
	else if (mDirection == EAST)
	{
		if (mPos.x + mSpeed < LIFEAREA_RITE - LEGEND_WIDTH)
			mPos.x += mSpeed;
		else
			TurnDirection(WEST);
	}
	else if (mDirection == WEST)
	{
		if (mPos.x - mSpeed > LIFEAREA_LEFT)
			mPos.x -= mSpeed;
		else
			TurnDirection(EAST);
	}
	else if (mDirection == SOUTH)
	{
		if (mPos.y + mSpeed < LIFEAREA_BOTTOM - LEGEND_HEIGHT)
			mPos.y += mSpeed;
		else
			TurnDirection(NORTH);
	}
}
void Legend::Step()
{
	if (mStep >= 3)
		mStep = 0;
	else
		mStep++;
}
void Legend::TurnDirection(int direction)
{
	mDirection = direction;
}

void Legend::SetValidateArea()
{
	this->mValiateAreaLegend.X      = this->mPos.x + 15;
	this->mValiateAreaLegend.Y      = this->mPos.y + 15;
	this->mValiateAreaLegend.Width  = LEGEND_WIDTH / 2;
	this->mValiateAreaLegend.Height = LEGEND_HEIGHT / 2;
}

void Legend::InitAllData(const int x, const int y, int direction)
{
	mPos = { x, y };
	mValiateAreaLegend = { 0, 0, 0, 0 };
	mDirection = direction;
	mSpeed = 5;
	mStep = 0;
}
