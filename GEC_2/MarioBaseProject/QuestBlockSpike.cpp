#include "QuestBlockSpike.h"

QuestBlockSpike::QuestBlockSpike(SDL_Renderer* renderer, int mapX, int mapY, int type) : QuestBlock::QuestBlock(renderer, mapX, mapY){
	mTexture = new Texture2D(renderer);
	switch (type) {
	case 2:
		mType = SPIKED_SOLO;
		if (!mTexture->LoadFromFile("Images/questblockspiked.png")) {
			cout << "Failed to load spiked questblock texture" << endl;
			return;
		}
		mScreenPosition.x -= 4;
		mScreenPosition.y -= 4;
		break;
	case 3:
		mType = SPIKED_LEFT;
		if (!mTexture->LoadFromFile("Images/questblockspikedL.png")) {
			cout << "Failed to load spiked questblock texture" << endl;
			return;
		}
		mScreenPosition.x -= 4;
		break;
	case 4:
		mType = SPIKED_RIGHT;
		if (!mTexture->LoadFromFile("Images/questblockspikedR.png")) {
			cout << "Failed to load spiked questblock texture" << endl;
			return;
		}
		mScreenPosition.x -= 4;
		break;
	case 5:
		mType = SPIKED_MIDDLE;
		if (!mTexture->LoadFromFile("Images/questblockspikedM.png")) {
			cout << "Failed to load spiked questblock texture" << endl;
			return;
		}
		mScreenPosition.y -= 4;
		break;
	}
}

QuestBlockSpike::~QuestBlockSpike(){}

void QuestBlockSpike::Render() {
	mTexture->Render(mScreenPosition, SDL_FLIP_NONE);
}
void QuestBlockSpike::SetScreenPosition(int x, int y) {
	mScreenPosition = Vector2D(x, y);
	//spike offsets
	switch (mType) {
	case SPIKED_SOLO:
	case SPIKED_LEFT:
	case SPIKED_RIGHT:
		mScreenPosition.x -= 4;
	case SPIKED_MIDDLE:
		mScreenPosition.y -= 4;
		break;
	}
}