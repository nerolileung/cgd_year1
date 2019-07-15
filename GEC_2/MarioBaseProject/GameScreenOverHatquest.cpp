#include "GameScreenOverHatquest.h"
#include <fstream>

GameScreenOverHatquest::GameScreenOverHatquest(SDL_Renderer* renderer) : GameScreen::GameScreen(renderer){
	mRenderer = renderer;
	mTextParser = new TextParser(renderer);
	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/gameover hatquest.png")) {
		cout << "Failed to load background texture!";
		return;
	}
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
		inFile >> mScore;
		getline(inFile, causeOfDeath);
	}
	inFile.close();
	mState = RUNNING;
}

GameScreenOverHatquest::~GameScreenOverHatquest(){}

void GameScreenOverHatquest::Render() {
	mBackgroundTexture->Render(Vector2D(0, 0), SDL_FLIP_NONE);
	mTextParser->TextToSprite("GAME OVER",3);
	mTextParser->Render(Vector2D(mTextParser->AlignXCentre(), 10));
	mTextParser->TextToSprite("SCORE");
	mTextParser->Render(Vector2D(mTextParser->AlignXCentre(), 62));
	mTextParser->TextToSprite(to_string(mScore));
	mTextParser->Render(Vector2D(mTextParser->AlignXCentre(), 82));
	mTextParser->TextToSprite("CAUSE OF DEATH");
	mTextParser->Render(Vector2D(mTextParser->AlignXCentre(), 114));
	mTextParser->TextToSprite(causeOfDeath);
	mTextParser->Render(Vector2D(mTextParser->AlignXCentre(), 134));
	mTextParser->TextToSprite("PRESS SPACE TO RETURN TO MAIN MENU");
	mTextParser->Render(Vector2D(mTextParser->AlignXCentre(), 320));
	mTextParser->TextToSprite("PRESS ESCAPE TO QUIT");
	mTextParser->Render(Vector2D(mTextParser->AlignXCentre(), 352));
}