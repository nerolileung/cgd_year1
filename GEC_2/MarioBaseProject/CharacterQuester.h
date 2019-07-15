#pragma once
#include "Character.h"
class CharacterQuester : public Character {
public:
	CharacterQuester(SDL_Renderer* renderer, string imagePath, Vector2D startPosition,LevelMap* map);
	~CharacterQuester();
	void Update(float deltaTime, SDL_Event e);
	void Render();
	Rect2D GetCollisionBox();
	void CutsceneRun();
	void SpeedUp();
	void SetCurrentMapPos(int w, int h);
	Vector2D GetCurrentMapPos() { return mMapPosition; };
	void SetGroundCollision(bool colliding);
	void CancelJump();
private:
	SDL_Keycode mKeySlide;
	bool mSliding;
	void Jump();
	int mSpriteHeight;
	int mSpriteWidth;
	int frame;
	float frameTime;
	float currentFrameTime;
	int spriteXCoord;
	bool cutsceneActive;
	Vector2D mMapPosition;
	void Slide();
	void Stand();
};