#include "QuestBlockLong.h"

QuestBlockLong::QuestBlockLong(SDL_Renderer* renderer, int mapX, int mapY) : QuestBlock::QuestBlock(renderer,mapX,mapY){
	if (!mTexture->LoadFromFile("Images/questblocklong.png")) {
		cout << "Failed to load long questblock texture" << endl;
		return;
	}
	mType = LONG;
}

QuestBlockLong::~QuestBlockLong(){}