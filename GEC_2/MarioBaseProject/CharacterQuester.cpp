#include "CharacterQuester.h"

CharacterQuester::CharacterQuester(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map) : Character(renderer, imagePath, startPosition, map){
	mKeyJump = SDLK_SPACE;
	mKeySlide = SDLK_s;
	mSliding = false;
	mSpriteHeight = 32;
	mSpriteWidth = 24;
	frame = 0;
	frameTime = QUESTER_FRAME_TIME;
	currentFrameTime = 0;
	spriteXCoord = 0;
	cutsceneActive = false;
	mMapPosition = Vector2D(0,MAP_HEIGHT-2);
	mJumpForce = 0;
}

CharacterQuester::~CharacterQuester(){
}

void CharacterQuester::Update(float deltaTime, SDL_Event e) {
	//keyboard actions
	if (!cutsceneActive) {
		switch (e.type) {
		case SDL_KEYDOWN:
			if (e.key.keysym.sym == mKeyJump && !mJumping && !mSliding)	Jump();
			else if (e.key.keysym.sym == mKeySlide && !mSliding) Slide();
			break;
		case SDL_KEYUP:
			if (e.key.keysym.sym == mKeySlide && mSliding) Stand();
			break;
		}
	}
	//animation
	if (!mSliding) {
		currentFrameTime += deltaTime;
		if (currentFrameTime >= frameTime) {
			frame++;
			if (frame >= 4)	frame = 0;
			if (frame != 3) spriteXCoord = mSpriteWidth * frame;
			else spriteXCoord = mSpriteWidth;
			currentFrameTime = 0;
		}
	}
	else	spriteXCoord = 24 * 3;
	//going up/down
	if (mJumping) {
		if (mJumpForce>0)	mPosition.y -= LIFDOFF * deltaTime;
		//update map position based on screen position
		if ((mPosition.y + mSpriteHeight) < (mMapPosition.y * HATQUEST_TILE_SIZE)) {
			mMapPosition.y--;
			mJumpForce--;
		}
		if (mJumpForce <= 0) mPosition.y += LIFDOFF * deltaTime;
		if (mPosition.y >= ((mMapPosition.y+1) * HATQUEST_TILE_SIZE)) mMapPosition.y++;
	}
}
void CharacterQuester::Render() {
	int spriteTop = 32 - mSpriteHeight;
	SDL_Rect srcRect = { spriteXCoord,spriteTop,mSpriteWidth,mSpriteHeight };
	SDL_Rect destRect = { (int)mPosition.x,(int)mPosition.y,mSpriteWidth,mSpriteHeight };
	mTexture->Render(srcRect, destRect);
}
void CharacterQuester::Jump() {
	mJumping = true;
	mSpriteHeight = 32;
	mSpriteWidth = 24;
	mPosition.y -= HATQUEST_TILE_SIZE/4;
	mJumpForce = 3; //jump height in blocks
}
Rect2D CharacterQuester::GetCollisionBox() {
	return Rect2D(mPosition.x, mPosition.y, mSpriteWidth, mSpriteHeight);
}
void CharacterQuester::CutsceneRun() {
	if (!cutsceneActive) cutsceneActive = true;
	if (mSliding) Stand();
	if (mPosition.x <= SCREEN_WIDTH - HATQUEST_TILE_SIZE) {
		frameTime -= 0.00001f;
		mPosition.x += 0.01f;
	}
	else if (!mJumping)	Jump();
}
void CharacterQuester::SpeedUp() {
	frameTime -= 0.001f;
}
void CharacterQuester::SetCurrentMapPos(int w, int h) {
	mMapPosition.x = w;
	mMapPosition.y = h;
}
void CharacterQuester::SetGroundCollision(bool colliding) {
	mJumping = !colliding;
}
void CharacterQuester::Slide() {
	if (mJumping) CancelJump();
	mSliding = true;
	mSpriteHeight = 16;
	mSpriteWidth = 28;
	mPosition.y += mSpriteHeight;
}
void CharacterQuester::Stand() {
	mSliding = false;
	mPosition.y -= mSpriteHeight;
	mSpriteHeight = 32;
	mSpriteWidth = 24;
}
void CharacterQuester::CancelJump() {
	mJumpForce = 0;
}