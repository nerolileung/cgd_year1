#include "CharacterKoopa.h"

CharacterKoopa::CharacterKoopa(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map, FACING direction) : Character(renderer, imagePath, startPosition, map){
	mKeyLeft = NULL;
	mKeyRight = NULL;
	mKeyJump = NULL;
	mFacingDirection = direction;
	mMovementSpeed = KOOPA_SPEED;
	mInjured = false;
	mInjuredTime = 0.0f;
	mAlive = true;
	mSpriteWidth = mTexture->GetWidth() / 2;
	mSpriteHeight = mTexture->GetHeight();
}


CharacterKoopa::~CharacterKoopa(){}

void CharacterKoopa::Render() {
	int spriteXCoord = 0;
	if (mInjured)	spriteXCoord = mSpriteWidth;
	SDL_Rect srcRect = {spriteXCoord,0,mSpriteWidth,mSpriteHeight};
	SDL_Rect destRect = {(int)mPosition.x,(int)mPosition.y,mSpriteWidth,mSpriteHeight};
	SDL_RendererFlip flip;
	if (mFacingDirection == FACING_RIGHT)	flip = SDL_FLIP_NONE;
	else flip = SDL_FLIP_HORIZONTAL;
	mTexture->Render(srcRect, destRect, flip);
}
void CharacterKoopa::Update(float deltaTime) {
	if (!mInjured) {
		if (mPosition.y <= 300) {
			if (mPosition.x <= 0.0f)	mFacingDirection = FACING_RIGHT;
			else if (mPosition.x >= SCREEN_WIDTH - mTexture->GetWidth())	mFacingDirection = FACING_LEFT;
		}
		switch (mFacingDirection) {
		case FACING_LEFT:
			mMovingLeft = true;
			mMovingRight = false;
			break;
		case FACING_RIGHT:
			mMovingRight = true;
			mMovingLeft = false;
			break;
		}
	}
	else {
		mMovingRight = false;
		mMovingLeft = false;
		mInjuredTime -= deltaTime;
		if (mInjuredTime <= 0)	FlipBackUp();
	}
	int centralXPos = (int)(mPosition.x + (mTexture->GetWidth()*0.5f)) / TILE_WIDTH;
	int bottomPos = (int)(mPosition.y + mTexture->GetHeight()) / TILE_HEIGHT;
	if (mCurrentLevelMap->GetTileAt(bottomPos, centralXPos) == 0) { // in open space
		AddGravity(deltaTime);
	}
	//left and right movement
	if (mMovingLeft)	MoveLeft(deltaTime);
	else if (mMovingRight)	MoveRight(deltaTime);
}
void CharacterKoopa::TakeDamage() {
	mInjured = true;
	mInjuredTime = INJURED_TIME;
	Jump();
}
void CharacterKoopa::Jump() {
	if (!mJumping) {
		mJumpForce = INITIAL_JUMP_FORCE_SMALL;
		mJumping = true;
		mCanJump = false;
	}
}
void CharacterKoopa::FlipBackUp() {
	mInjured = false;
	if (mFacingDirection == FACING_LEFT)	mFacingDirection = FACING_RIGHT;
	else mFacingDirection = FACING_LEFT;
	Jump();
}