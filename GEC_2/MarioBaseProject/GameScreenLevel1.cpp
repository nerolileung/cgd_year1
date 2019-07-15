#include "GameScreenLevel1.h"
#include <iostream>
#include "CharacterLuigi.h"
#include "Collisions.h"
#include <fstream>

using namespace std;

class PowBlock;

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer) {
	mLevelMap = nullptr;
	SetUpLevel();
}
GameScreenLevel1::~GameScreenLevel1() {
	delete playerOne;
	playerOne = nullptr;
	delete playerTwo;
	playerTwo = nullptr;
	delete mLevelMap;
	mLevelMap = nullptr;
	delete mPowBlock;
	mPowBlock = nullptr;
	mEnemies.clear();
	mCoins.clear();
}
bool GameScreenLevel1::SetUpLevel() {
	//load bg texture
	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/BackgroundMB.png")) {
		cout << "Failed to load background texture!";
		return false;
	}
	SetLevelMap();
	playerOne = new CharacterMario(mRenderer, "Images/Mario.png", Vector2D(64, 330), mLevelMap);
	playerTwo = new CharacterLuigi(mRenderer, "Images/Luigi.png", Vector2D(16, 330),mLevelMap);
	mPowBlock = new PowBlock(mRenderer,mLevelMap);
	mScreenshake = false;
	mBackgroundYPos = 0.0f;
	CreateKoopa(Vector2D(150, 32), FACING_RIGHT);
	CreateKoopa(Vector2D(325, 32), FACING_LEFT);
	koopaTimer = KOOPA_SPAWN_DELAY;
	for (int i = 0; i < 6; i++) {
		float yPos = 4 * TILE_HEIGHT;
		float xPos = (5+i) * TILE_WIDTH;
		mCoins.push_back(new CharacterCoin(mRenderer, "Images/Coin.png", Vector2D(xPos, yPos), mLevelMap));
	}
	mState = RUNNING;
	mScore = 0;
	scoreTimer = MARIO_SCORE_TIME;
	mTextParser = new TextParser(mRenderer);
	return true;
}
void GameScreenLevel1::Update(float deltaTime, SDL_Event e) {
	switch (e.type) {
	case SDL_KEYUP: // a key has been pressed!
		switch (e.key.keysym.sym) {
		case SDLK_p:
			if (mState == RUNNING) mState = PAUSED;
			else if (mState == PAUSED) mState = RUNNING;
			break;
		}
		break;
	}
	if (mState == RUNNING) {
		koopaTimer -= deltaTime;
		if (koopaTimer <= 0) {
			koopaTimer = KOOPA_SPAWN_DELAY;
			FACING tFacing;
			if (rand() % 2 == 0) tFacing = FACING_LEFT;
			else tFacing = FACING_RIGHT;
			CreateKoopa(Vector2D(130 + (rand() % 200), 32), tFacing);
		}
		scoreTimer -= deltaTime;
		if (scoreTimer <= 0) {
			scoreTimer = MARIO_SCORE_TIME;
			mScore += 1;
		}
		UpdatePowBlock();
		UpdateEnemies(deltaTime);
		UpdateCoins(deltaTime);
		playerOne->Update(deltaTime, e);
		playerTwo->Update(deltaTime, e);
		if (mScreenshake) {
			mScreenshakeTime -= deltaTime;
			mWobble++;
			mBackgroundYPos = (sin(mWobble)) * 3.0f;
			if (mScreenshakeTime <= 0) {
				mScreenshake = false;
				mBackgroundYPos = 0.0f;
			}
		}
	}
}
void GameScreenLevel1::Render() {
	if (mState == RUNNING) {
		mBackgroundTexture->Render(Vector2D(0, mBackgroundYPos), SDL_FLIP_NONE);
		playerOne->Render();
		playerTwo->Render();
		mPowBlock->Render();
		for (int i = 0; i < mEnemies.size(); i++)	mEnemies[i]->Render();
		for (int i = 0; i < mCoins.size(); i++)	mCoins[i]->Render();
		mTextParser->TextToSprite(to_string(mScore) + " POINTS");
		mTextParser->Render(Vector2D(mTextParser->AlignXCentre(), 0));
	}
	else if (mState == PAUSED) {
		mTextParser->TextToSprite("PAUSED",6);
		mTextParser->Render(Vector2D(mTextParser->AlignXCentre(), (SCREEN_HEIGHT - 80) / 2));
	}
}

void GameScreenLevel1::SetLevelMap() {
	if (mLevelMap != NULL)	delete mLevelMap;
	mLevelMap = new LevelMap("mario_map.txt",true);
}
void GameScreenLevel1::UpdatePowBlock() {
	// collides with mario AND powblock exists AND mario hits it from the bottom/side
	if (Collisions::Instance()->Box(playerOne->GetCollisionBox(),mPowBlock->GetCollisionBox())&&mPowBlock->IsAvailable()&&playerOne->IsJumping()) {
		DoScreenshake();
		mPowBlock->TakeAHit();
		playerOne->CancelJump();
	}
}
void GameScreenLevel1::DoScreenshake() {
	mScreenshake = true;
	mScreenshakeTime = SCREENSHAKE_DURATION;
	mWobble = 0.0f;
	if (!mEnemies.empty()) {
		for (unsigned int i = 0; i < mEnemies.size(); i++)	mEnemies[i]->TakeDamage();
	}
}
void GameScreenLevel1::UpdateEnemies(float deltaTime) {
	if (!mEnemies.empty()) {
		int enemyToBeDeletedIndex = -1;
		for (unsigned int i = 0; i < mEnemies.size(); i++) {
			if (mEnemies[i]->GetPosition().y > 300.0f) { //koopa is on ground level
				//kill koopas that are offscreen
				if (mEnemies[i]->GetPosition().x < (float)(-mEnemies[i]->GetCollisionBox().width*0.5f))	mEnemies[i]->SetAlive(false); //left
				else if (mEnemies[i]->GetPosition().x > SCREEN_WIDTH - (float)(mEnemies[i]->GetCollisionBox().width*0.5f))	mEnemies[i]->SetAlive(false); //right
			}
			mEnemies[i]->Update(deltaTime);
			//player collision
			if (Collisions::Instance()->Circle(mEnemies[i], playerOne)) {
				if (mEnemies[i]->IsInjured()) {
					mEnemies[i]->SetAlive(false);
					mScore += 5;
				}
				else {
					cout << "MARIO IS DEAD" << endl;
					saveScoreToFile();
					mState = GAMEOVER;
				}
			}
			//delete dead koopa (one per update)
			if (!mEnemies[i]->GetAlive()) enemyToBeDeletedIndex = i;
		}
		if (enemyToBeDeletedIndex != -1) {
			delete mEnemies[enemyToBeDeletedIndex];
			mEnemies[enemyToBeDeletedIndex] = nullptr;
			mEnemies.erase(mEnemies.begin() + enemyToBeDeletedIndex); // does not automatically delete content
		}
	}
}
void GameScreenLevel1::CreateKoopa(Vector2D position, FACING direction) {
	CharacterKoopa* koopa = new CharacterKoopa(mRenderer, "Images/Koopa.png", position, mLevelMap, direction);
	mEnemies.push_back(koopa);
}
void GameScreenLevel1::UpdateCoins(float deltaTime) {
	if (!mCoins.empty()) {
		for (int i = 0; i < mCoins.size(); i++) {
			bool marioColliding = Collisions::Instance()->Circle(mCoins[i], playerOne);
			bool luigiColliding = Collisions::Instance()->Circle(mCoins[i], playerTwo);
			if (marioColliding || luigiColliding) {
				mScore += 5;
				delete mCoins[i];
				mCoins[i] = nullptr;
				mCoins.erase(mCoins.begin() + i);
			}
			else {
				mCoins[i]->Update(deltaTime);
			}
		}
	}
}
void GameScreenLevel1::saveScoreToFile() {
	int scores[5] = { -1,-1,-1,-1,-1 }; //initialise placeholder. max 5 scores saved
	int scoreCounter = 0;
	// read in scores
	ifstream inFile;
	inFile.open("mario_scores.txt");
	if (!inFile.good()) {
		cout << "could not open scores file" << endl;
		return;
	}
	streampos start = inFile.tellg();
	inFile.seekg(0, ios::end); //set eof to true
	streampos end = inFile.tellg();
	if (start != end) { //there is data in file
		inFile.clear();
		inFile.seekg(0, ios::beg);
		while (scoreCounter<5) {
			inFile >> scores[scoreCounter];
			scoreCounter++;
		}
		//pop off top (oldest) score if already at max scores savable
		if (scoreCounter >= 5) {
			for (int i = 0; i < 4; i++) {
				scores[i] = scores[i+1];
			}
			scoreCounter = 4;
		}
	}
	scores[scoreCounter] = mScore;
	scoreCounter++;
	inFile.close();
	// clear file, write scores back
	ofstream outFile;
	outFile.open("mario_scores.txt", ios::trunc);
	for (int i = 0; i < scoreCounter; i++) {
		if (scores[i] == -1) continue;
		outFile << scores[i] << '\n';
	}
	outFile.close();
}