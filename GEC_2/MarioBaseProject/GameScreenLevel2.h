#pragma once
#include "GameScreen.h"
#include "CharacterQuester.h"
#include "LevelMap.h"
#include "QuestBlock.h"
#include <vector>
#include "QuestStar.h"
#include "QuestHat.h"

class GameScreenLevel2 : public GameScreen{
public:
	GameScreenLevel2(SDL_Renderer* renderer);
	~GameScreenLevel2();
	void Update(float deltaTime, SDL_Event e);
	void Render();
private:
	CharacterQuester* playerCharacter;
	LevelMap* mLevelMap;
	float mSpeed;
	float mSpeedMultiplier;
	int stageCounter;
	void SetUpLevel();
	vector<QuestBlock*> mBlocks;
	void MoveObjects();
	int maxOnScreenBlockIndex;
	void CollideWithBlocks();
	vector<QuestStar*> mStars;
	void CollectStars();
	int maxOnScreenStarIndex;
	void EndGame(string cause);
	QuestHat* hat;
	void MoveHat();
};