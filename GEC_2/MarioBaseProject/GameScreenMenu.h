#pragma once
#include "GameScreen.h"

class GameScreenMenu :	public GameScreen
{
public:
	GameScreenMenu(SDL_Renderer* renderer);
	~GameScreenMenu();
	void Render();
	void Update(float deltaTime, SDL_Event e);
private:
	Rect2D option1Box;
	Rect2D option2Box;
};

