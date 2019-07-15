#include "GameScreenLevel1.h"
#include "GameScreenManager.h"
#include "GameScreenOverMario.h"
#include "GameScreenMenu.h"
#include "GameScreenLevel2.h"
#include "GameScreenOverHatquest.h"
#include "GameScreenWinHatquest.h"

GameScreenManager::GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen) {
	mRenderer = renderer;
	mCurrentScreen = NULL;
	ChangeScreen(startScreen);
}
GameScreenManager::~GameScreenManager() {
	mRenderer = NULL;
	delete mCurrentScreen;
	mCurrentScreen = NULL;
}
void GameScreenManager::Render() {

	mCurrentScreen->Render();
}
void GameScreenManager::Update(float deltaTime, SDL_Event e) {
	if (mCurrentScreen->GetState() == GAMEOVER) { //need to change screens
		switch (mCurrentSceneType) {
		case SCREEN_LEVEL1:
			ChangeScreen(SCREEN_GAMEOVER1);
			break;
		case SCREEN_LEVEL2:
			ChangeScreen(SCREEN_GAMEOVER2);
			break;
		case SCREEN_GAMEOVER1:
		case SCREEN_GAMEOVER2:
		case SCREEN_WIN2:
			ChangeScreen(SCREEN_MENU);
			break;
		case SCREEN_MENU:
			ChangeScreen(SCREEN_LEVEL1);
			break;
		}
	}
	else if (mCurrentSceneType == SCREEN_MENU && mCurrentScreen->GetState() == PAUSED) ChangeScreen(SCREEN_LEVEL2);
	else if (mCurrentSceneType == SCREEN_LEVEL2 && mCurrentScreen->GetState() == WIN) ChangeScreen(SCREEN_WIN2);
	mCurrentScreen->Update(deltaTime, e);
}
void GameScreenManager::ChangeScreen(SCREENS newScreen) {
	if (mCurrentScreen != NULL) { //clear old
		delete mCurrentScreen;
	}
	switch (newScreen) {
	case SCREEN_LEVEL1:
		mCurrentScreen = (GameScreen*)(new GameScreenLevel1(mRenderer)); // type casting to GameScreen
		break;
	case SCREEN_GAMEOVER1:
		mCurrentScreen = (GameScreen*)(new GameScreenOverMario(mRenderer));
		break;
	case SCREEN_LEVEL2:
		mCurrentScreen = (GameScreen*)(new GameScreenLevel2(mRenderer));
		break;
	case SCREEN_GAMEOVER2:
		mCurrentScreen = (GameScreen*)(new GameScreenOverHatquest(mRenderer));
		break;
	case SCREEN_WIN2:
		mCurrentScreen = (GameScreen*)(new GameScreenWinHatquest(mRenderer));
		break;
	case SCREEN_MENU:
		mCurrentScreen = (GameScreen*)(new GameScreenMenu(mRenderer));
		break;
	}
	mCurrentSceneType = newScreen;
}