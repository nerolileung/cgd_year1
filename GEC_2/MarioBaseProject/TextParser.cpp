#include "TextParser.h"
#include "Constants.h"

using namespace std;

TextParser::TextParser(SDL_Renderer* renderer){
	mRenderer = renderer;
	mTexture = new Texture2D(mRenderer);
	mTexture->LoadFromFile("Images/text.png");
	currentXPos = 0;
	textSize = 2;
}

SpriteLetter TextParser::Symbols[] = { 
	{ '0', 9, 0 },
{ '1',8,9 },
{ '2',9,17 },
{ '3',9,26 },
{ '4',9,35 },
{ '5',9,44 },
{ '6',9,53 },
{ '7',9,62 },
{ '8',9,71 },
{ '9',9,80 },
{ ' ',10,89 },
{ 'A',7,99 },
{ 'B',7,106 },
{ 'C',7,113 },
{ 'D',7,120 },
{ 'E',6,127 },
{ 'F',6,133 },
{ 'G',8,139 },
{ 'H',7,147 },
{ 'I',3,154 },
{ 'J',6,157 },
{ 'K',7,163 },
{ 'L',5,170 },
{ 'M',9,175 },
{ 'N',7,184 },
{ 'O',9,191 },
{ 'P',7,200 },
{ 'Q',9,207 },
{ 'R',7,216 },
{ 'S',7,223 },
{ 'T',7,230 },
{ 'U',7,237 },
{ 'V',7,244 },
{ 'W',11,251 },
{ 'X',7,262 },
{ 'Y',7,269 },
{ 'Z',6,276 }
};

TextParser::~TextParser(){
	mRenderer = NULL;
	delete mTexture;
	mTexture = nullptr;
	buffer.clear();
}

void TextParser::TextToSprite(string text) {
	buffer.clear();
	for (int i = 0; i < text.length(); i++) {
		SpriteLetter symbol;
		for (int j = 0; j < 37; j++) {
			if (toupper(text[i]) == Symbols[j].symbol)	symbol = Symbols[j];
		}
		buffer.push_back(symbol);
	}
	textSize = 2;
}
void TextParser::TextToSprite(string text, int size) {
	buffer.clear();
	for (int i = 0; i < text.length(); i++) {
		SpriteLetter symbol;
		for (int j = 0; j < 37; j++) {
			if (toupper(text[i]) == Symbols[j].symbol)	symbol = Symbols[j];
		}
		buffer.push_back(symbol);
	}
	textSize = size;
}
void TextParser::Render(Vector2D position) {
	currentPosition = position;
	int spriteHeight = 16;
	currentXPos = position.x;
	for (int i = 0; i < buffer.size(); i++) {
		SDL_Rect srcRect = { buffer[i].x,0,buffer[i].width,spriteHeight };
		SDL_Rect destRect = { currentXPos,position.y,buffer[i].width*textSize,spriteHeight*textSize };
		mTexture->Render(srcRect, destRect);
		currentXPos += buffer[i].width*textSize;
	}
}
float TextParser::AlignXCentre() {
	currentXPos = 0;
	for (int i = 0; i < buffer.size(); i++) currentXPos += buffer[i].width * textSize;
	currentXPos = (SCREEN_WIDTH - currentXPos) / 2;
	return currentXPos;
}
float TextParser::AlignXRight() {
	currentXPos = 0;
	for (int i = 0; i < buffer.size(); i++) currentXPos += buffer[i].width * textSize;
	currentXPos = SCREEN_WIDTH - currentXPos;
	return currentXPos;
}
Rect2D TextParser::GetTextBox() {
	int height = 16 * textSize;
	return Rect2D(currentPosition.x, currentPosition.y, currentXPos, height);
}