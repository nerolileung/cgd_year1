#pragma once
#include "GameScreen.h"
class GameScreenOverHatquest : public GameScreen {
public:
	GameScreenOverHatquest(SDL_Renderer* renderer);
	~GameScreenOverHatquest();
	void Render();
private:
	string causeOfDeath;
};