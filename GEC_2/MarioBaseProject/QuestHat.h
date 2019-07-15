#pragma once
#include "QuestObject.h"
class QuestHat : public QuestObject{
public:
	QuestHat(SDL_Renderer* renderer, int mapX, int mapY);
	~QuestHat();
};