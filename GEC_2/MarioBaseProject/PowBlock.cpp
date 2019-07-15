#include "PowBlock.h"
#include <iostream>
#include <string>
#include "Collisions.h"

using namespace std;

PowBlock::PowBlock(SDL_Renderer* _renderer, LevelMap* _levelMap){
	string imagePath = "Images/PowBlock.png";
	mRenderer = _renderer;
	mLevelMap = _levelMap;
	mTexture = new Texture2D(_renderer);
	if (!mTexture->LoadFromFile(imagePath)) {
		cout << "Failed to load texture: " << imagePath << endl;
		return;
	}
	mSingleSpriteWidth = mTexture->GetWidth() / 3;
	mSingleSpriteHeight = mTexture->GetHeight();
	mNumHitsLeft = 3;
	mPosition = Vector2D((SCREEN_WIDTH*0.5f)-mSingleSpriteWidth*0.5f,260);
}


PowBlock::~PowBlock(){
	mRenderer = nullptr;
	delete mTexture;
	mTexture = nullptr;
	mLevelMap = nullptr;
}

void PowBlock::Render() {
	if (mNumHitsLeft > 0) {
		int spriteXCoord = mSingleSpriteWidth * (mNumHitsLeft - 1);
		SDL_Rect srcRect = {spriteXCoord,0,mSingleSpriteWidth,mSingleSpriteHeight};
		SDL_Rect destinationRect = {(int)mPosition.x, (int)mPosition.y,mSingleSpriteWidth,mSingleSpriteHeight};
		mTexture->Render(srcRect, destinationRect,SDL_FLIP_NONE);
	}
}
void PowBlock::TakeAHit() {
	mNumHitsLeft--;
	if (mNumHitsLeft <= 0) {
		mNumHitsLeft = 0;
		mLevelMap->ChangeTileAt(8, 7, 0);
		mLevelMap->ChangeTileAt(8, 8, 0);
	}
}