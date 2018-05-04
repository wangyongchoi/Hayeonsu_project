#pragma once
class Legend
{
public:
	CPoint mPos;
	Rect   mValiateAreaLegend;
	int    mDirection;
	int    mSpeed;
	int    mStep;

public:
	 Legend(const int x, const int y, int direction);
	~Legend();
	int  CollisionWithBaby();
	void Move();
	void Step();
	int  GetDirection();
	int  GetStep();
	void TurnDirection(int direction);
	void SetValidateArea();
	void InitAllData(const int x, const int y, int direction);
};

