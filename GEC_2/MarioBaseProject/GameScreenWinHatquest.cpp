#include "GameScreenWinHatquest.h"
#include <fstream>

GameScreenWinHatquest::GameScreenWinHatquest(SDL_Renderer* renderer) : GameScreen::GameScreen(renderer){
	mRenderer = renderer;
	mTextParser = new TextParser(renderer);
	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/victory hatquest.png")) {
		cout << "Failed to load background texture!";
		return;
	}
	mScore = 0;
	for (int i = 0; i < 3; i++) deathCounter[i] = 0; //initialisation
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
		string causeOfDeath;
		while (!inFile.eof()) {
			int score;
			inFile >> score; // move file pointer
			getline(inFile, causeOfDeath);
			if (causeOfDeath.compare(" gravity") == 0) deathCounter[0]++;
			else if (causeOfDeath.compare(" perforation") == 0) deathCounter[1]++;
			else if (causeOfDeath.compare(" blunt trauma") == 0) deathCounter[2]++;
			else if (causeOfDeath.compare(" suffocation") == 0) deathCounter[3]++;
		}
	}
	inFile.close();
	// clear saves
	ofstream outFile;
	outFile.open("hatquest_scores.txt", ios::trunc);
	outFile.close();
	mState = RUNNING;
}

GameScreenWinHatquest::~GameScreenWinHatquest(){}

void GameScreenWinHatquest::Render() {
	mBackgroundTexture->Render(Vector2D(0, 0), SDL_FLIP_NONE);
	mTextParser->TextToSprite("YOU WIN", 4);
	mTextParser->Render(Vector2D(mTextParser->AlignXCentre(), 10));
	mTextParser->TextToSprite("FINAL SCORE");
	mTextParser->Render(Vector2D(mTextParser->AlignXCentre(), 62));
	mTextParser->TextToSprite(to_string(mScore));
	mTextParser->Render(Vector2D(mTextParser->AlignXCentre(), 82));
	// left align
	mTextParser->TextToSprite("DEATHS BY");
	mTextParser->Render(Vector2D(10, 144));
	mTextParser->TextToSprite("GRAVITY");
	mTextParser->Render(Vector2D(10, 176));
	mTextParser->TextToSprite(to_string(deathCounter[0]));
	mTextParser->Render(Vector2D(40, 196));
	mTextParser->TextToSprite("PERFORATION");
	mTextParser->Render(Vector2D(10, 228));
	mTextParser->TextToSprite(to_string(deathCounter[1]));
	mTextParser->Render(Vector2D(40, 248));
	//right align
	mTextParser->TextToSprite("DEATHS BY");
	mTextParser->Render(Vector2D(mTextParser->AlignXRight() - 10, 144));
	mTextParser->TextToSprite("BLUNT TRAUMA");
	mTextParser->Render(Vector2D(mTextParser->AlignXRight()-10, 176));
	mTextParser->TextToSprite(to_string(deathCounter[2]));
	mTextParser->Render(Vector2D(mTextParser->AlignXRight() - 40, 196));
	mTextParser->TextToSprite("SUFFOCATION");
	mTextParser->Render(Vector2D(mTextParser->AlignXRight() - 10, 228));
	mTextParser->TextToSprite(to_string(deathCounter[3]));
	mTextParser->Render(Vector2D(mTextParser->AlignXRight() - 40, 248));
	//bottom text
	mTextParser->TextToSprite("PRESS SPACE TO RETURN TO MAIN MENU");
	mTextParser->Render(Vector2D(mTextParser->AlignXCentre(), 320));
	mTextParser->TextToSprite("PRESS ESCAPE TO QUIT");
	mTextParser->Render(Vector2D(mTextParser->AlignXCentre(), 352));
}