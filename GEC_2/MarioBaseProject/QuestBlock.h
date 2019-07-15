#pragma once
#include "QuestObject.h"
class QuestBlock : 	public QuestObject{
public:
	QuestBlock(SDL_Renderer* renderer, int mapX, int mapY);
	~QuestBlock();
	BLOCK_TYPE GetBlockType() { return mType; };
protected:
	BLOCK_TYPE mType;
};