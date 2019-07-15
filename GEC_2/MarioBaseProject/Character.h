#pragma once
#ifndef _CHARACTER_H
#define _CHARACTER_H

#include "SDL.h"
#include "Constants.h"
#include "Commons.h"
#include "LevelMap.h"
#include <iostream>
#include "Texture2D.h"

using namespace std;

class Character {
protected:
	SDL_Renderer* mRenderer;
	Vector2D mPosition;
	Texture2D* mTexture;
	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);
	FACING mFacingDirection;
	bool mMovingLeft; //temp todo streamline ala pacman
	bool mMovingRight;
	virtual void AddGravity(float deltaTime);
	bool mJumping;
	bool mCanJump;
	float mJumpForce;
	virtual void Jump();
	SDL_Keycode mKeyLeft;
	SDL_Keycode mKeyRight;
	SDL_Keycode mKeyJump;
	float mCollisionRadius;
	LevelMap* mCurrentLevelMap;
	int mMovementSpeed;
public:
	Character(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map);
	~Character();
	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
	void SetPosition(Vector2D newPosition);
	Vector2D GetPosition();
	float GetCollisionRadius();
	Rect2D GetCollisionBox();
	bool IsJumping() { return mJumping; };
	virtual void CancelJump();
};

#endif // !_CHARACTER_H