#pragma once
#include "Character.h"
class CharacterCoin :
	public Character
{
public:
	CharacterCoin(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map);
	~CharacterCoin();
	void Render();
	void Update(float deltaTime);
private:
	float mFrameDelay;
	int mCurrentFrame;
	float mSpriteWidth;
	float mSpriteHeight;
};

