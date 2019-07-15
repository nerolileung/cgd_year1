#pragma once

#include "QuestObject.h"

class QuestStar : public QuestObject {
public:
	QuestStar(SDL_Renderer* renderer, int mapX, int mapY);
	~QuestStar();
};