#pragma once
#include "QuestBlock.h"
class QuestBlockLong :	public QuestBlock{
public:
	QuestBlockLong(SDL_Renderer* renderer, int mapX, int mapY);
	~QuestBlockLong();
};