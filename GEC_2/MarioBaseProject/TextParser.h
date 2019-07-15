#pragma once
#include "SDL.h"
#include "Commons.h"
#include "Texture2D.h"
#include <string>
#include <vector>

using namespace std;

class TextParser
{
public:
	TextParser(SDL_Renderer* renderer);
	~TextParser();
	void TextToSprite(string text);
	void TextToSprite(string text, int size);
	void Render(Vector2D position);
	float AlignXCentre();
	float AlignXRight();
	Rect2D GetTextBox();
private:
	SDL_Renderer* mRenderer;
	vector<SpriteLetter> buffer;
	Texture2D* mTexture;
	static SpriteLetter Symbols[37];
	float currentXPos;
	int textSize;
	Vector2D currentPosition;
};