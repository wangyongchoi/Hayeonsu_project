#include "stdafx.h"
#include "User.h"
#include <Mmsystem.h>

User::~User()
{
}
void User::TurnDirection(int direction)
{
	if (userDirection == direction)
		return;
	if (userDirection == EAST){
		if (direction == WEST)
			return;
	}
	else if (userDirection == WEST){
		if (direction == EAST)
			return;
	}
	else if (userDirection == SOUTH){
		if (direction == NORTH)
			return;
	}
	else if (userDirection == NORTH){
		if (direction == SOUTH)
			return;
	}
	userDirection = direction;
	
	return;
}

void User::GrowLength()
{
	if (userLength != MAXLENGTH){
		userLength++;
	}
	else
		return;

	return;
}

void User::InitLength()
{
	if (userLength != 1)
		userLength = 1;
	return;
}
CPoint User::GetUserPos()
{
	return userPos;
}
void User::SetLength(int length)
{
	userLength = length;
}

int User::GetLength()
{
	return userLength;
}
int User::GetDirection()
{
	return userDirection;
}
int User::GetState()
{
	return userState;
}

void User::SetState(int item)
{
	if (userState != item)
		userState = item;
	return;
}

int User::GetSpeed()
{
	return userSpeed;
}

void User::SetSpeed(int speed)
{
	if (userSpeed != speed)
		userSpeed = speed;
	return;
}

void User::MoveUser()
{	
	userLastStep = { userPos, userDirection };

	Step();
	if (userDirection == NORTH)
	{
		userPos.y -= (userSpeed+2);
	}
	else if (userDirection == EAST)
	{
		userPos.x += userSpeed;
	}
	else if (userDirection == WEST)
	{
		userPos.x -= userSpeed;
	}
	else if (userDirection == SOUTH)
	{
		userPos.y += (userSpeed+4);
	}

	if ((userLastStep.tailPos.x != userPos.x || userLastStep.tailPos.y != userPos.y) && GetLength() > 1)
		LeaveTailPos(userLastStep.tailPos.x, userLastStep.tailPos.y, userDirection);
}
int User::GetStep()
{
	return userStep;
}
void User::Step()
{
	if (userStep >= 3)
		userStep = 0;
	else
		userStep++;
}
void User::SetValidateArea()
{
	this->valiateAreaUser.X		 = this->userPos.x + (TURTLEKINGWIDTH / 4);
	this->valiateAreaUser.Y		 = this->userPos.y + (TURTLEKINGWIDTH / 3);
	this->valiateAreaUser.Width  = TURTLEKINGWIDTH  / 2;
	this->valiateAreaUser.Height = TURTLEKINGHEIGHT / 2;
}
#include "Hayeonsu.h"
#include "MainFrm.h"
#include "HayeonsuDoc.h"
#include "HayeonsuView.h"
class object;

bool User::CollisionWithGold(Object *p)
{
	CMainFrame    *pMain = (CMainFrame    *) theApp.GetMainWnd();
	CHayeonsuView *pView  = (CHayeonsuView *) pMain->GetActiveView();
	std::list<Rect>::iterator it;
	for (int i = 0; i < 10; i++){
		for (it = p->validateAreaGold.begin(); it != p->validateAreaGold.end(); ++it){
			
			if (valiateAreaUser.IntersectsWith(*it)==TRUE){
				pView->DeleteCoin(it->X, it->Y);
				return true;
			}
		}
		return false;
	}	
}

bool User::CollisionWithItem(Object *p)
{
	CMainFrame    *pMain = (CMainFrame    *) theApp.GetMainWnd();
	Rect rc(p->itemPos.x + 2, p->itemPos.y + 2, ITEMWIDTH - 3, ITEMHEIGHT - 3);
	if (valiateAreaUser.IntersectsWith(rc) == TRUE)
	{
		p->itemPos.x = -1;
		return true;
	}
	
	return false;
}

bool User::CollisionWithBaby()
{
	CMainFrame    *pMain = (CMainFrame    *) theApp.GetMainWnd();
	CHayeonsuView *pView = (CHayeonsuView *) pMain->GetActiveView();
	CHayeonsuDoc  *pDoc  = (CHayeonsuDoc  *) pView->GetDocument();
	for (int i = 2; i < pDoc->user.GetLength(); i++){
		Rect baby(pDoc->user.tail[i * 5].tailPos.x + 30, pDoc->user.tail[i * 5].tailPos.y + 40, TURTLEBABYWIDTH / 8, TURTLEBABYHEIGHT / 8);
		if (valiateAreaUser.IntersectsWith(baby) == TRUE){
			pView->mLife = DEAD;
			pView->mMode = QUIT;
			return true;
		}
	}
	return false;
}

bool User::CollisionWithTree()
{
	CMainFrame    *pMain = (CMainFrame    *) theApp.GetMainWnd();
	CHayeonsuView *pView = (CHayeonsuView *) pMain->GetActiveView();

	Rect topTree    (LIFEAREA_LEFT,		    	  0,  LIFEAREA_RITE - LIFEAREA_LEFT,			    LIFEAREA_TOP - 0 );
	Rect leftTree   (			 0,    LIFEAREA_TOP,			  LIFEAREA_LEFT - 0,  LIFEAREA_BOTTOM - LIFEAREA_TOP );
	Rect bottomTree (LIFEAREA_LEFT, LIFEAREA_BOTTOM,  LIFEAREA_RITE - LIFEAREA_LEFT,           800 - LIFEAREA_BOTTOM );
	Rect rightTree  (LIFEAREA_RITE,    LIFEAREA_TOP,           1200 - LIFEAREA_RITE,  LIFEAREA_BOTTOM - LIFEAREA_TOP );

	if (valiateAreaUser.IntersectsWith(topTree) || valiateAreaUser.IntersectsWith(leftTree)
		|| valiateAreaUser.IntersectsWith(bottomTree) || valiateAreaUser.IntersectsWith(rightTree) == TRUE){
		pView->mLife = DEAD;
		pView->mMode = QUIT;
		return true;
	}
	return  false;
}


bool User::CollisionWithCastle()
{
	Rect castle(CASTLE_POS_X, CASTLE_POS_Y, CASTLE_WIDTH, CASTLE_HEIGHT);
	return valiateAreaUser.IntersectsWith(castle);
}

bool User::CollisionWithLegend()
{
	CMainFrame    *pMain = (CMainFrame    *) theApp.GetMainWnd();
	CHayeonsuView *pView = (CHayeonsuView *) pMain->GetActiveView();
	CHayeonsuDoc  *pDoc  = (CHayeonsuDoc  *) pView->GetDocument();
	
	if (valiateAreaUser.IntersectsWith(pDoc->legend1.mValiateAreaLegend)
		|| valiateAreaUser.IntersectsWith(pDoc->legend2.mValiateAreaLegend)
		|| valiateAreaUser.IntersectsWith(pDoc->legend3.mValiateAreaLegend) == TRUE){
		pView->mLife = DEAD;
		pView->mMode = QUIT;
		return true;
	}
	
	return false;
}



void User::LeaveTailPos(int x, int y, int direction)
{
	for (int i = userLength*5 - 1; i >= 0; i--)
	{
		tail[i + 1].turnDirection = tail[i].turnDirection;
		tail[i + 1].tailPos.x = tail[i].tailPos.x;
		tail[i + 1].tailPos.y = tail[i].tailPos.y;
	}

	tail[0].turnDirection = direction;
	tail[0].tailPos.x = x;
	tail[0].tailPos.y = y;
}

void User::InitAllData()
{
	userPos					   = {STARTPOSX, STARTPOSY};
	userLastStep.tailPos	   = { -1, -1 };
	userLastStep.turnDirection = -1;
	valiateAreaUser			   = { 0, 0, 0, 0 };
	userLength                 = 1;
	userDirection              = EAST;
	userState                  = NONE;
	userSpeed                  = NORMAL;
	userStep                   = 0;
}
