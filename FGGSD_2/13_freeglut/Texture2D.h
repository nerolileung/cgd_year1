#pragma once
#include "Structures.h"

class Texture2D
{
private:
	GLuint _ID; //texture id
	int _width;
	int _height;
public:
	Texture2D();
	~Texture2D();
	bool Load(char* path, int width, int height);
	GLuint GetID() const { return _ID; }
};