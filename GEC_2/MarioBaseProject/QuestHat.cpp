#include "QuestHat.h"

QuestHat::QuestHat(SDL_Renderer* renderer, int mapX, int mapY) : QuestObject::QuestObject(renderer, mapX, mapY) {
	mTexture = new Texture2D(renderer);
	if (!mTexture->LoadFromFile("Images/hat.png")) {
		cout << "Failed to load hat texture" << endl;
		return;
	}
}

QuestHat::~QuestHat(){}