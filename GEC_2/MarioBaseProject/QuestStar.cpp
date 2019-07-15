#include "QuestStar.h"

QuestStar::QuestStar(SDL_Renderer* renderer, int mapX, int mapY) : QuestObject::QuestObject(renderer, mapX, mapY) {
	mTexture = new Texture2D(renderer);
	if (!mTexture->LoadFromFile("Images/star.png")) {
		cout << "Failed to load star texture" << endl;
		return;
	}
}

QuestStar::~QuestStar(){}