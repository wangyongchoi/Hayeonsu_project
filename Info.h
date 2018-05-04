#pragma once

class Info
{

public:
	int mGoldCount;
	int mScore;

public:
	 Info() :mGoldCount(0), mScore(0){}
	~Info();

	int  GetgoldCount();
	int  GetScore();
	void IncreaseGoldCount();
	void InitGoldCount();
	void IncreaseScore(int value);
	void InitAllData();
};

