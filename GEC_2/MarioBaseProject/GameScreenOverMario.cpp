#include "GameScreenOverMario.h"
#include <fstream>

using namespace std;

GameScreenOverMario::GameScreenOverMario(SDL_Renderer* renderer):GameScreen(renderer){
	mRenderer = renderer;
	mTextParser = new TextParser(renderer);
	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/gameover mario.png")) {
		cout << "Failed to load background texture!";
		return;
	}
	mState = RUNNING;
	int scores[5] = { -1,-1,-1,-1,-1 };
	int scoreCounter = 0;
	// read in scores
	ifstream inFile;
	inFile.open("mario_scores.txt");
	if (!inFile.good()) {
		cout << "could not open scores file" << endl;
		return;
	}
	streampos start = inFile.tellg();
	inFile.seekg(0, ios::end);
	streampos end = inFile.tellg();
	if (start != end) { //in case no data in file
		inFile.clear();
		inFile.seekg(0, ios::beg);
		while (!inFile.eof()) {
			inFile >> scores[scoreCounter];
			scoreCounter++;
		}
	}
	inFile.close();
	for (int i = 0; i < 5; i++) {
		if (scores[i] == -1) break;
		cout << scores[i] << endl;
		mScore = scores[i];
	}
}

GameScreenOverMario::~GameScreenOverMario(){
	delete mTextParser;
	mTextParser = nullptr;
	delete mBackgroundTexture;
	mBackgroundTexture = nullptr;
}

void GameScreenOverMario::Render() {
	mBackgroundTexture->Render(Vector2D(0,0), SDL_FLIP_NONE);
	mTextParser->TextToSprite("GAME OVER");
	mTextParser->Render(Vector2D(mTextParser->AlignXCentre(), 60));
	mTextParser->TextToSprite("FINAL SCORE");
	mTextParser->Render(Vector2D(mTextParser->AlignXCentre(), 100));
	mTextParser->TextToSprite(to_string(mScore));
	mTextParser->Render(Vector2D(mTextParser->AlignXCentre(), 132));
	mTextParser->TextToSprite("PRESS SPACE TO RETURN TO MAIN MENU");
	mTextParser->Render(Vector2D(mTextParser->AlignXCentre(), 300));
	mTextParser->TextToSprite("PRESS ESCAPE TO QUIT");
	mTextParser->Render(Vector2D(mTextParser->AlignXCentre(), 332));
}