#pragma once
#ifndef _GAMESCREEN_H
#define _GAMESCREEN_H
#include "SDL.h"
#include "Commons.h"
#include "TextParser.h"

class GameScreen {
protected:
	SDL_Renderer * mRenderer;
	Texture2D * mBackgroundTexture;
	TextParser* mTextParser;
	SCREEN_STATE mState;
	int mScore;
public:
	GameScreen(SDL_Renderer* renderer);
	~GameScreen();
	virtual void Render() = 0;
	virtual void Update(float deltaTime, SDL_Event e);
	SCREEN_STATE GetState() { return mState; };
};

#endif // GAMESCREEN_H