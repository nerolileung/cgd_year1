#include "GameScreenLevel2.h"
#include "Collisions.h"
#include "QuestBlockSpike.h"
#include "QuestBlockLong.h"
#include <fstream>

GameScreenLevel2::GameScreenLevel2(SDL_Renderer* renderer) : GameScreen(renderer){
	mRenderer = renderer;
	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/hatquestbg.png")) {
		cout << "Failed to load background texture!";
	}
	mTextParser = new TextParser(mRenderer);
	mState = RUNNING;
	mScore = 0;
	SetUpLevel();
	playerCharacter = new CharacterQuester(mRenderer, "Images/Quester.png", Vector2D(0, SCREEN_HEIGHT-(2*HATQUEST_TILE_SIZE)),mLevelMap);
	mSpeed = QUESTER_BASE_SPEED;
	mSpeedMultiplier = 1.0f;
	stageCounter = 1;
}

GameScreenLevel2::~GameScreenLevel2(){
	delete playerCharacter;
	playerCharacter = nullptr;
	delete mLevelMap;
	mLevelMap = nullptr;
	mBlocks.clear();
	mStars.clear();
	delete hat;
	hat = nullptr;
}

void GameScreenLevel2::Update(float deltaTime, SDL_Event e) {
	if (playerCharacter->GetCurrentMapPos().x < (HATQUEST_MAP_WIDTH-(SCREEN_WIDTH / HATQUEST_TILE_SIZE))) {
		switch (e.type) {
		case SDL_KEYUP:
			switch (e.key.keysym.sym) {
			case SDLK_TAB:
				if (mState == RUNNING) mState = PAUSED;
				else if (mState == PAUSED) mState = RUNNING;
				break;
			}
			break;
		}
		if (mState == RUNNING) {
			//moving through the map
			mSpeedMultiplier += 1.5;
			mSpeed = QUESTER_BASE_SPEED * mSpeedMultiplier;
			if (mSpeed*deltaTime >= 2) {
				playerCharacter->SetCurrentMapPos(playerCharacter->GetCurrentMapPos().x + 1, playerCharacter->GetCurrentMapPos().y);
				mSpeedMultiplier = 1.0f;
			}
			if (playerCharacter->GetCurrentMapPos().x >= stageCounter * 8) {
				playerCharacter->SpeedUp();
				stageCounter++;
			}
			MoveObjects();
			CollectStars();
			// death by falling
			int tileBelowPlayer = mLevelMap->GetTileAt(playerCharacter->GetCurrentMapPos().y + 1, playerCharacter->GetCurrentMapPos().x);
			if (tileBelowPlayer == 0 || tileBelowPlayer == 7) {
				playerCharacter->SetGroundCollision(false);
				if (playerCharacter->GetPosition().y >= SCREEN_HEIGHT)  EndGame("gravity");
			}
		}
	}
	else {
		MoveObjects();
		MoveHat();
		playerCharacter->CutsceneRun();
		if (Collisions::Instance()->Box(playerCharacter->GetCollisionBox(), hat->GetCollisionBox())) EndGame("win");
	}
	CollideWithBlocks(); // character-world collisions - still needed in cutscene
	playerCharacter->Update(deltaTime, e);
}
void GameScreenLevel2::Render() {
	if (mState == RUNNING) {
		SDL_Rect currentStage = { (playerCharacter->GetCurrentMapPos().x*HATQUEST_TILE_SIZE),0,SCREEN_WIDTH,SCREEN_HEIGHT };
		SDL_Rect screenSize = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
		mBackgroundTexture->Render(currentStage, screenSize);
		for (int i = 0; i <= maxOnScreenBlockIndex; i++)	mBlocks[i]->Render();
		for (int i = 0; i < maxOnScreenStarIndex; i++) mStars[i]->Render();
		playerCharacter->Render();
		hat->Render();
		mTextParser->TextToSprite(to_string(mScore) + " POINTS");
		mTextParser->Render(Vector2D(mTextParser->AlignXCentre(), 0));
	}
	else if (mState == PAUSED) {
		mTextParser->TextToSprite("PAUSED", 6);
		mTextParser->Render(Vector2D(mTextParser->AlignXCentre(), (SCREEN_HEIGHT - 80) / 2));
	}
}
void GameScreenLevel2::SetUpLevel() {
	mLevelMap = new LevelMap("hatquest_map.txt", false);
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < HATQUEST_MAP_WIDTH; j++) {
			if (mLevelMap->GetTileAt(i, j)==1)	mBlocks.push_back(new QuestBlock(mRenderer, j, i));
			else if (mLevelMap->GetTileAt(i, j)==6)	mBlocks.push_back((QuestBlock*)(new QuestBlockLong(mRenderer, j, i)));
			else if (mLevelMap->GetTileAt(i, j) == 7) mStars.push_back(new QuestStar(mRenderer, j, i));
			else if (mLevelMap->GetTileAt(i, j) == 8) hat = new QuestHat(mRenderer, j, i);
			else if (mLevelMap->GetTileAt(i, j) != 0) mBlocks.push_back((QuestBlock*)(new QuestBlockSpike(mRenderer, j, i, mLevelMap->GetTileAt(i, j))));
		}
	}
}
void GameScreenLevel2::MoveObjects() {
	int minMapXPos = playerCharacter->GetCurrentMapPos().x;
	int maxMapXPos = minMapXPos + (SCREEN_WIDTH / HATQUEST_TILE_SIZE);
	//blocks
	int blockToBeDeletedIndex = -1;
	for (int i = 0; i < mBlocks.size(); i++) {
		if (mBlocks[i]->GetMapPosition().x < minMapXPos) { //delete blocks behind player
			delete mBlocks[i];
			mBlocks[i] = nullptr;
			mBlocks.erase(mBlocks.begin() + i);
		}
		else if (mBlocks[i]->GetMapPosition().x <= maxMapXPos) {
			int screenX = (mBlocks[i]->GetMapPosition().x - playerCharacter->GetCurrentMapPos().x)*HATQUEST_TILE_SIZE;
			int screenY = mBlocks[i]->GetMapPosition().y*HATQUEST_TILE_SIZE;
			mBlocks[i]->SetScreenPosition(screenX, screenY);
			maxOnScreenBlockIndex = i;
		}
	}
	//stars
	for (int i = 0; i < mStars.size(); i++) {
		if (mStars[i]->GetMapPosition().x < minMapXPos) {
			delete mStars[i];
			mStars[i] = nullptr;
			mStars.erase(mStars.begin() + i);
		}
		else if (mStars[i]->GetMapPosition().x <= maxMapXPos) {
			int screenX = ((mStars[i]->GetMapPosition().x - playerCharacter->GetCurrentMapPos().x)*HATQUEST_TILE_SIZE) + 12; //offset to put star in centre
			int screenY = (mStars[i]->GetMapPosition().y*HATQUEST_TILE_SIZE) + 16;
			mStars[i]->SetScreenPosition(screenX, screenY);
			maxOnScreenStarIndex = i;
		}
	}
}
void GameScreenLevel2::MoveHat() {
	if (hat->GetMapPosition().x <= playerCharacter->GetCurrentMapPos().x + (SCREEN_WIDTH / HATQUEST_TILE_SIZE)) {
		int screenX = (hat->GetMapPosition().x - playerCharacter->GetCurrentMapPos().x)*HATQUEST_TILE_SIZE + 8;
		int screenY = hat->GetMapPosition().y*HATQUEST_TILE_SIZE;
		hat->SetScreenPosition(screenX, screenY);
	}
}
void GameScreenLevel2::CollideWithBlocks() {
	for (int i = 0; i < maxOnScreenBlockIndex; i++) {
		if (Collisions::Instance()->Box(playerCharacter->GetCollisionBox(), mBlocks[i]->GetCollisionBox())) {
			if (mBlocks[i]->GetBlockType() != REGULAR && mBlocks[i]->GetBlockType() != LONG) {
				EndGame("perforation");
			}
			if (mBlocks[i]->GetMapPosition().y > playerCharacter->GetCurrentMapPos().y) { // block below character
				playerCharacter->SetCurrentMapPos(playerCharacter->GetCurrentMapPos().x, mBlocks[i]->GetMapPosition().y - 1);
				playerCharacter->SetGroundCollision(true);
			}
			else if (mBlocks[i]->GetMapPosition().y < playerCharacter->GetCurrentMapPos().y) { //block above
				if (mBlocks[i]->GetBlockType() == LONG) EndGame("blunt trauma");
				playerCharacter->CancelJump();
				playerCharacter->SetCurrentMapPos(playerCharacter->GetCurrentMapPos().x, mBlocks[i]->GetMapPosition().y + 1);
			}
			else {
				if (mBlocks[i]->GetBlockType() == LONG) EndGame("blunt trauma");
				else EndGame("suffocation");
			}
		}
	}
}
void GameScreenLevel2::CollectStars() {
	for (int i = 0; i < maxOnScreenStarIndex; i++) {
		if (Collisions::Instance()->Box(playerCharacter->GetCollisionBox(), mStars[i]->GetCollisionBox())) {
			mScore += 2;
			delete mStars[i];
			mStars[i] = nullptr;
			mStars.erase(mStars.begin() + i);
		}
	}
}
void GameScreenLevel2::EndGame(string cause) {
	cout << "cause of death: " << cause << endl;
	string mostRecentDeath = to_string(mScore) + " " + cause;
	vector<string> obituaries;
	ifstream inFile;
	inFile.open("hatquest_scores.txt");
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
		while (!inFile.eof()) {
			string line;
			getline(inFile, line);
			obituaries.push_back(line);
		}
	}
	// add most recent score to top
	if (cause.compare("win") == 0) obituaries.insert(obituaries.begin(), to_string(mScore));
	else obituaries.insert(obituaries.begin(), mostRecentDeath);
	inFile.close();
	// clear file, write scores back
	ofstream outFile;
	outFile.open("hatquest_scores.txt", ios::trunc);
	for (int i = 0; i < obituaries.size(); i++) {
		outFile << obituaries[i] << '\n';
	}
	outFile.close();
	if (cause.compare("win") == 0) mState = WIN;
	else mState = GAMEOVER;
}