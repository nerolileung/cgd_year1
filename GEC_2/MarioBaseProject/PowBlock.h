#pragma once
#ifndef POWBLOCK_H
#define POWBLOCK_H

#include "Commons.h"
#include "SDL.h"
#include "LevelMap.h"
#include "Texture2D.h"

class PowBlock
{
public:
	PowBlock(SDL_Renderer* _renderer, LevelMap* _levelMap);
	~PowBlock();
	void Render();
	Rect2D GetCollisionBox() { return Rect2D(mPosition.x,mPosition.y,mSingleSpriteWidth,mSingleSpriteHeight); };
	void TakeAHit();
	bool IsAvailable() { return mNumHitsLeft > 0; };
private:
	SDL_Renderer* mRenderer;
	Vector2D mPosition;
	Texture2D* mTexture;
	LevelMap* mLevelMap;
	float mSingleSpriteWidth;
	float mSingleSpriteHeight;
	int mNumHitsLeft;
};

#endif // !POWBLOCK_H

