#include "QuestBlock.h"

QuestBlock::QuestBlock(SDL_Renderer* renderer, int mapX, int mapY) : QuestObject::QuestObject(renderer,mapX,mapY){
	mTexture = new Texture2D(renderer);
	if (!mTexture->LoadFromFile("Images/questblock.png")) {
		cout << "Failed to load questblock texture" << endl;
		return;
	}
	mType = REGULAR;
}

QuestBlock::~QuestBlock(){}