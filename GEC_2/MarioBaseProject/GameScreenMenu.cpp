#include "GameScreenMenu.h"
#include "Collisions.h"

GameScreenMenu::GameScreenMenu(SDL_Renderer* renderer) : GameScreen(renderer){
	mRenderer = renderer;
	mTextParser = new TextParser(mRenderer);
	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/mainmenu.png")) {
		cout << "Failed to load background texture!";
		return;
	}
	mState = RUNNING;
}

GameScreenMenu::~GameScreenMenu() {
	delete mTextParser;
	mTextParser = nullptr;
	delete mBackgroundTexture;
	mBackgroundTexture = nullptr;
}

void GameScreenMenu::Update(float deltaTime, SDL_Event e) {
	switch (e.type) {
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym) {
		case SDLK_1: //level 1
			mState = GAMEOVER;
			break;
		case SDLK_2: // level 2
			mState = PAUSED;
			break;
		}
		break;
	case SDL_MOUSEBUTTONDOWN:
		int x, y;
		SDL_GetMouseState(&x, &y);
		Rect2D mouseRect = Rect2D(x, y, 1.0, 1.0);
		if (Collisions::Instance()->Box(mouseRect, option1Box)) mState = GAMEOVER;
		else if (Collisions::Instance()->Box(mouseRect, option2Box))	mState = PAUSED;
		break;
	}
}
void GameScreenMenu::Render() {
	mBackgroundTexture->Render(Vector2D(0, 0), SDL_FLIP_NONE);
	mTextParser->TextToSprite("LEVEL SELECTION",4);
	mTextParser->Render(Vector2D(mTextParser->AlignXCentre(), 0));
	mTextParser->TextToSprite("1  MARIO",3);
	mTextParser->Render(Vector2D(50, (SCREEN_HEIGHT/2)-48));
	option1Box = mTextParser->GetTextBox();
	mTextParser->TextToSprite("2  HATQUEST",3);
	mTextParser->Render(Vector2D(mTextParser->AlignXRight()-50, (SCREEN_HEIGHT/2)+48));
	option2Box = mTextParser->GetTextBox();
}