#include "Texture2D.h"
#include <iostream>
#include <fstream>

using namespace std;

Texture2D::Texture2D(){}

Texture2D::~Texture2D(){}

bool Texture2D::Load(char* path, int width, int height) {
	char* tempTextureData;
	int fileSize;
	ifstream inFile;

	_width = width;
	_height = height;

	inFile.open(path, ios::binary);
	if (!inFile.good()) {
		cerr << "Can't open texture file " << path << endl;
		return false;
	}

	inFile.seekg(0, ios::end);
	fileSize = (int)inFile.tellg(); // end position indicates file size
	tempTextureData = new char[fileSize];
	inFile.seekg(0, ios::beg);
	inFile.read(tempTextureData, fileSize);
	inFile.close();

	glGenTextures(1, &_ID); // autogen next texture id 
	glBindTexture(GL_TEXTURE_2D, _ID); //bind texture to id
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, tempTextureData); //auto mipmaps

	delete[] tempTextureData; // don't need to save the texture, just the id
	return true;
}