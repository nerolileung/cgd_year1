#include "Texture2D.h"
#include "CharacterLuigi.h"

CharacterLuigi::CharacterLuigi(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map) : Character(renderer, imagePath, startPosition, map) {
	mKeyLeft = SDLK_LEFT;
	mKeyRight = SDLK_RIGHT;
	mKeyJump = SDLK_UP;
	mMovementSpeed = MOVEMENT_SPEED;
}

CharacterLuigi::~CharacterLuigi(){}

void CharacterLuigi::Render() {
	SDL_RendererFlip flip;
	if (mFacingDirection == FACING_RIGHT)	flip = SDL_FLIP_HORIZONTAL; // why is luigi's sprite flipped by default.
	else flip = SDL_FLIP_NONE;
	mTexture->Render(mPosition, flip);
}