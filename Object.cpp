#include "stdafx.h"
#include "Object.h"
#include <stdlib.h>
#include <time.h>
#include <Mmsystem.h>
#include "Hayeonsu.h"
#include "MainFrm.h"
#include "HayeonsuDoc.h"
#include "HayeonsuView.h"

Object::Object() :itemPos(-1,-1)
{
}


Object::~Object()
{	
}

bool Object::CreateItem()
{
	if (this->itemPos.x != -1)
		return false;

	srand((unsigned int)time(NULL));
	do{
		this->itemPos.x = LIFEAREA_LEFT + rand() % ((LIFEAREA_RITE   - LIFEAREA_LEFT) - ITEMWIDTH);
		this->itemPos.y = LIFEAREA_TOP  + rand() % ((LIFEAREA_BOTTOM - LIFEAREA_TOP)  - ITEMHEIGHT);
	} 
	while ((this->itemPos.x >= CASTLE_POS_X && this->itemPos.x <= CASTLE_POS_X + CASTLE_WIDTH)
		&& (this->itemPos.y >= CASTLE_POS_Y && this->itemPos.y <= CASTLE_POS_Y + CASTLE_HEIGHT));
	PlaySound(L"./sound/itemDrop.wav", NULL, SND_FILENAME | SND_ASYNC);
	return true;
}

void Object::CreateGold(int userLength)
{
	if (this->goldPos.size() >= (unsigned int)userLength)
		return;
	else{
		CPoint gold;
		srand((unsigned int)time(NULL));
		while (userLength != this->goldPos.size())
		{
			gold.x = LIFEAREA_LEFT + rand() % ((LIFEAREA_RITE   - LIFEAREA_LEFT) - COINWIDTH);
			gold.y = LIFEAREA_TOP  + rand() % ((LIFEAREA_BOTTOM - LIFEAREA_TOP)  - COINHEIGHT);
			if (!(gold.x >= CASTLE_POS_X && gold.x <= CASTLE_POS_X + CASTLE_WIDTH)
				&& !(gold.y >= CASTLE_POS_Y && gold.y <= CASTLE_POS_Y + CASTLE_HEIGHT))
			{
				this->goldPos.push_back(gold);
				Rect temp(gold.x, gold.y, COINWIDTH, COINHEIGHT);
				this->validateAreaGold.push_back(temp);
			}
		}
	}
	return;
}

void Object::CopyGoldPosToVector(std::vector<CPoint> *v)
{
	std::list<CPoint>::iterator it;
	for (it = goldPos.begin(); it != goldPos.end(); ++it)
	{
		v->push_back(*it);
	}
}

void Object::DeleteGoldPos(CPoint pos)
{
	goldPos.remove(pos);
}
void Object::DeleteValidateGoldPos(CPoint pos)
{
	Rect temp(pos.x, pos.y, COINWIDTH, COINHEIGHT);
	std::list<Rect>::iterator it;
	for (it = validateAreaGold.begin(); it != validateAreaGold.end(); ++it)
	{
		if (temp == *it){
			validateAreaGold.erase(it);
			break;
		}
	}
}

Rect Object::GetValidateAreaGold(int index)
{
	int i = 0;
	std::list<Rect>::iterator it;
	for (it = this->validateAreaGold.begin(); i < index; ++it, ++i);
		return *it;
}

void Object::InitAllData()
{
	itemPos = { -1, -1 };
	goldPos.clear();
	validateAreaGold.clear();
}