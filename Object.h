#pragma once
#include <list>
#include <vector>

class Object
{
public:
	CPoint            itemPos;
	std::list<CPoint> goldPos;
	std::list<Rect>   validateAreaGold;

	 Object();
	~Object();

	bool CreateItem();
	void CreateGold(int userLength);
	int  GetGoldCount() { return goldPos.size(); };
	Rect GetValidateAreaGold(int index);
	void CopyGoldPosToVector(std::vector<CPoint> *v);
	void DeleteGoldPos(CPoint pos);
	void DeleteValidateGoldPos(CPoint pos);
	void InitAllData();
};