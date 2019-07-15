#pragma once
#include "GameScreen.h"
class GameScreenWinHatquest : public GameScreen {
public:
	GameScreenWinHatquest(SDL_Renderer* renderer);
	~GameScreenWinHatquest();
	void Render();
private:
	int deathCounter[4];
};