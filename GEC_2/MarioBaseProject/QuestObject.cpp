#include "QuestObject.h"

QuestObject::QuestObject(SDL_Renderer* renderer, int mapX, int mapY){
	mRenderer = renderer;
	mScreenPosition = Vector2D(-32, -32);
	mMapPosition = Vector2D(mapX, mapY);
}

QuestObject::~QuestObject(){
	mRenderer = nullptr;
	delete mTexture;
	mTexture = nullptr;
}

void QuestObject::Render() {
	mTexture->Render(mScreenPosition,SDL_FLIP_NONE);
}
void QuestObject::SetScreenPosition(int x, int y) {
	mScreenPosition = Vector2D(x, y);
}
Rect2D QuestObject::GetCollisionBox() {
	return Rect2D{(float)mScreenPosition.x,(float)mScreenPosition.y,(float)mTexture->GetWidth(),(float)mTexture->GetHeight()};
}