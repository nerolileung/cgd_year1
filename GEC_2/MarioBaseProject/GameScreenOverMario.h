#ifndef GAMESCREENOVERMARIO_H
#define GAMESCREENOVERMARIO_H

#pragma once
#include "GameScreen.h"

class GameScreenOverMario : public GameScreen {
public:
	GameScreenOverMario(SDL_Renderer* renderer);
	~GameScreenOverMario();
	void Render();
};

#endif // !GAMESCREENOVERMARIO_H