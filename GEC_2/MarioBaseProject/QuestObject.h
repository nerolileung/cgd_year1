#pragma once

#include "SDL.h"
#include "Constants.h"
#include "Texture2D.h"

class QuestObject {
public:
	QuestObject(SDL_Renderer* renderer,int mapX, int mapY);
	~QuestObject();
	virtual void Render();
	virtual void SetScreenPosition(int x, int y);
	Vector2D GetMapPosition() { return mMapPosition; };
	Rect2D GetCollisionBox();
protected:
	SDL_Renderer* mRenderer;
	Texture2D* mTexture;
	Vector2D mScreenPosition;
	Vector2D mMapPosition;
};