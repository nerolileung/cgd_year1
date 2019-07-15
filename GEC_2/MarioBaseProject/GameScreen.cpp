#include "GameScreen.h"

GameScreen::GameScreen(SDL_Renderer* renderer) {
	mRenderer = renderer;
}

GameScreen::~GameScreen() {
	mRenderer = NULL;
	delete mBackgroundTexture;
	mBackgroundTexture = nullptr;
	delete mTextParser;
	mTextParser = nullptr;
}

// expect these to be overridden by specific screens
void GameScreen::Update(float deltaTime, SDL_Event e) {
	switch (e.type) {
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym) {
		case SDLK_SPACE:
			mState = GAMEOVER;
			break;
		}
		break;
	}
}