#include "Character.h"

Character::Character(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map) {
	mRenderer = renderer;
	mTexture = new Texture2D(mRenderer);
	mTexture->LoadFromFile(imagePath);
	SetPosition(startPosition);
	mFacingDirection = FACING_RIGHT;
	mMovingLeft = false;
	mMovingRight = false;
	mCollisionRadius = (mTexture->GetWidth() / 2);
	mCurrentLevelMap = map;
}
Character::~Character() {
	mRenderer = NULL;
	delete mTexture;
	mTexture = nullptr;
	mCurrentLevelMap = NULL;
}
void Character::Render() {
	SDL_RendererFlip flip;
	if (mFacingDirection == FACING_RIGHT)	flip = SDL_FLIP_NONE;
	else flip = SDL_FLIP_HORIZONTAL;
	mTexture->Render(mPosition,flip);
}
void Character::Update(float deltaTime, SDL_Event e) {
	//figure out position
	int centralXPos = (int)(mPosition.x+(mTexture->GetWidth()*0.5f))/TILE_WIDTH;
	int bottomPos = (int)(mPosition.y+mTexture->GetHeight())/TILE_HEIGHT;
	//jumping
	if (mJumping) {
		mPosition.y -= mJumpForce * deltaTime;
		mJumpForce -= JUMP_FORCE_DECREMENT * deltaTime;
		if (mJumpForce <= 0.0f) {
			mJumping = false;
			mCanJump = true;
		}
	}
	if (mCurrentLevelMap->GetTileAt(bottomPos, centralXPos) == 0) { // in open space
		AddGravity(deltaTime);
		mCanJump = false;
	}
	else {
		mCanJump = true;
	}
	//left and right movement
	if (mMovingLeft)	MoveLeft(deltaTime);
	else if (mMovingRight)	MoveRight(deltaTime);

	switch (e.type) {
	case SDL_KEYDOWN:
		if (e.key.keysym.sym == mKeyLeft)	mMovingLeft = true;
		else if (e.key.keysym.sym == mKeyRight)	mMovingRight = true;
		else if (e.key.keysym.sym == mKeyJump) {
			if (mCanJump)	Jump();
		}
		break;
	case SDL_KEYUP:
		if (e.key.keysym.sym == mKeyLeft)	mMovingLeft = false;
		else if (e.key.keysym.sym == mKeyRight)	mMovingRight = false;
		break;
	}
}
void Character::SetPosition(Vector2D newPosition) {
	mPosition = newPosition;
}
Vector2D Character::GetPosition() {
	return mPosition;
}
void Character::MoveLeft(float deltaTime) {
	mPosition.x -= mMovementSpeed*deltaTime;
	mFacingDirection = FACING_LEFT;
}
void Character::MoveRight(float deltaTime) {
	mPosition.x += mMovementSpeed*deltaTime;
	mFacingDirection = FACING_RIGHT;
}
void Character::AddGravity(float deltaTime) {
	mPosition.y += GRAVITY * deltaTime;
	//if (mPosition.y > SCREEN_HEIGHT - mTexture->GetHeight()) mPosition.y = SCREEN_HEIGHT-mTexture->GetHeight();
}
void Character::Jump() {
	mJumpForce = INITIAL_JUMP_FORCE;
	mJumping = true;
	mCanJump = false;
}
float Character::GetCollisionRadius() {
	return mCollisionRadius;
}
Rect2D Character::GetCollisionBox() {
	return Rect2D(mPosition.x, mPosition.y, mTexture->GetWidth(), mTexture->GetHeight());
}
void Character::CancelJump() {
	mJumping = false;
}