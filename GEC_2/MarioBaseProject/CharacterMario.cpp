#include "CharacterMario.h"

CharacterMario::CharacterMario(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map) : Character(renderer, imagePath, startPosition, map) {
	//everything else gets constructed as per the base character class
	mKeyLeft = SDLK_a;
	mKeyRight = SDLK_d;
	mKeyJump = SDLK_SPACE;
	mMovementSpeed = MOVEMENT_SPEED;
}

CharacterMario::~CharacterMario(){}