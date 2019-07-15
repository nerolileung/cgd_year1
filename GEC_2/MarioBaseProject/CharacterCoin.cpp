#include "CharacterCoin.h"

CharacterCoin::CharacterCoin(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map) : Character(renderer,imagePath,startPosition,map){
	mKeyLeft = NULL;
	mKeyRight = NULL;
	mKeyJump = NULL;
	mSpriteWidth = mTexture->GetWidth() / 3;
	mSpriteHeight = mTexture->GetHeight();
	mCurrentFrame = 0;
	mFrameDelay = ANIMATION_DELAY;
}


CharacterCoin::~CharacterCoin()
{
}

void CharacterCoin::Render() {
	int spriteXCoord = mSpriteWidth * mCurrentFrame;
	SDL_Rect srcRect = { spriteXCoord,0,mSpriteWidth,mSpriteHeight };
	SDL_Rect destRect = { (int)mPosition.x,(int)mPosition.y,mSpriteWidth,mSpriteHeight };
	mTexture->Render(srcRect, destRect);
}
void CharacterCoin::Update(float deltaTime) {
	mFrameDelay -= deltaTime;
	if (mFrameDelay <= 0.0f) {
		mFrameDelay = ANIMATION_DELAY;
		mCurrentFrame++;
		if (mCurrentFrame > 2)	mCurrentFrame = 0;
	}
}