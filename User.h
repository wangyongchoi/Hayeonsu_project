#pragma once
#include "Object.h"

struct TAIL{
	CPoint tailPos;
	int    turnDirection;
};

class Object;
class User
{
private:

	CPoint userPos;
	TAIL   userLastStep;
	Rect   valiateAreaUser;
	int    userLength;
	int    userDirection;
	int    userSpeed;
	int    userStep;

public:
	int    userState;

	TAIL tail[MAXLENGTH*TURTLEBABYWIDTH];

	User() 
	:userPos(STARTPOSX, STARTPOSY)
	,valiateAreaUser(STARTPOSX + (TURTLEKINGWIDTH / 4), STARTPOSY + (TURTLEKINGHEIGHT / 3), TURTLEKINGWIDTH / 2, TURTLEKINGHEIGHT / 2)
	,userLength(1)
	,userDirection(EAST)
	,userStep(0)
	,userSpeed(NORMAL)
	,userState(NONE)
	{}

	~User();
	
	CPoint GetUserPos();
	void  InitAllData();
	int   GetLength();
	int   GetDirection();
	int   GetState();
	int   GetSpeed();
	int   GetStep();
	void  SetState(int item);
	void  SetSpeed(int speed);
	void  SetLength(int length);
	void  SetValidateArea();
	void  Step();
	void  GrowLength();
	void  InitLength();
	void  MoveUser();
	void  TurnDirection(int userDirection);
	bool  CollisionWithGold(Object *p);
	bool  CollisionWithItem(Object *p);
	bool  CollisionWithCastle();
	bool  CollisionWithBaby();
	bool  CollisionWithTree();
	bool  CollisionWithLegend();
	void  LeaveTailPos(int x, int y, int direction);
};