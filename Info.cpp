#include "stdafx.h"
#include "Info.h"

Info::~Info()
{
}

int Info::GetgoldCount()
{
	return mGoldCount;
}
int Info::GetScore()
{
	return mScore;
}
void Info::IncreaseGoldCount()
{
	mGoldCount++;
}
void Info::IncreaseScore(int value)
{
	mScore += value;
}
void Info::InitGoldCount()
{
	mGoldCount = 0;
}
void Info::InitAllData()
{
	mGoldCount = 0;
	mScore = 0;
}