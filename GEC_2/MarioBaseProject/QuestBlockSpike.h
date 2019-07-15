#pragma once
#include "QuestBlock.h"
class QuestBlockSpike : public QuestBlock {
public:
	QuestBlockSpike(SDL_Renderer* renderer, int mapX, int mapY, int type);
	~QuestBlockSpike();
	void Render();
	void SetScreenPosition(int x, int y);
};