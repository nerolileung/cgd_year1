#pragma once
#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H

#include "GameScreen.h"
#include "Character.h"
#include "LevelMap.h"
#include "PowBlock.h"
#include <vector>
#include "CharacterMario.h"
#include "CharacterKoopa.h"
#include "CharacterCoin.h"

// forward declarations
class Texture2D;
class Character;

class GameScreenLevel1 :GameScreen {
private:
	bool SetUpLevel();
	CharacterMario* playerOne;
	Character* playerTwo;
	void SetLevelMap();
	LevelMap* mLevelMap;
	PowBlock* mPowBlock;
	void UpdatePowBlock();
	bool mScreenshake;
	float mScreenshakeTime;
	float mWobble;
	float mBackgroundYPos;
	void DoScreenshake();
	void UpdateEnemies(float deltaTime);
	void CreateKoopa(Vector2D position, FACING direction);
	vector<CharacterKoopa*> mEnemies;
	float koopaTimer;
	vector<CharacterCoin*> mCoins;
	void UpdateCoins(float deltaTime);
	void saveScoreToFile();
	float scoreTimer;
public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();
	void Render();
	void Update(float deltaTime, SDL_Event e);
};

#endif // GAMESCREENLEVEL1_H