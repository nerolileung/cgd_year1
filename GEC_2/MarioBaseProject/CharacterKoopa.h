#pragma once
#ifndef CHARACTERKOOPA_H
#define CHARACTERKOOPA_H

#include "Character.h"
class CharacterKoopa : public Character {
public:
	CharacterKoopa(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map, FACING direction);
	~CharacterKoopa();
	void Render();
	void Update(float deltaTime);
	void TakeDamage();
	void Jump();
	bool GetAlive() { return mAlive; };
	void SetAlive(bool alive) { mAlive = alive; };
	bool IsInjured() { return mInjured; }
private:
	float mSpriteHeight;
	float mSpriteWidth;
	bool mInjured;
	float mInjuredTime;
	void FlipBackUp();
	bool mAlive;
};

#endif // !CHARACTERKOOPA_H
