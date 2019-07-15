#include "LevelMap.h"
#include <iostream>
#include <fstream>

// 0 = empty space, 1 = occupied space

LevelMap::LevelMap(int map[MAP_HEIGHT][MARIO_MAP_WIDTH]){
	mHeight = MAP_HEIGHT;
	mWidth = MARIO_MAP_WIDTH;
	mMap = new int*[MAP_HEIGHT]; //first layer of arrays
	for (unsigned int i = 0; i < MAP_HEIGHT; i++)	mMap[i] = new int[MARIO_MAP_WIDTH];
	for (unsigned int i = 0; i < MAP_HEIGHT; i++) {
		for (unsigned int j = 0; j < MARIO_MAP_WIDTH; j++)	mMap[i][j] = map[i][j];
	}
}
LevelMap::LevelMap(string filePath, bool marioMap) {
	mHeight = MAP_HEIGHT;
	if (marioMap) mWidth = MARIO_MAP_WIDTH;
	else mWidth = HATQUEST_MAP_WIDTH;
	ifstream inFile;
	inFile.open(filePath);
	if (!inFile.good()) {
		cout << "could not open level map at " << filePath << endl;
		return;
	}
	// check if file is empty
	streampos start = inFile.tellg();
	inFile.seekg(0, ios::end);
	streampos end = inFile.tellg();
	if (start != end) {
		inFile.clear();
		inFile.seekg(0, ios::beg);
		mMap = new int*[mHeight];
		for (unsigned int i = 0; i < mHeight; i++) {
			mMap[i] = new int[mWidth];
			for (unsigned int j = 0; j < mWidth; j++)	inFile >> mMap[i][j];
		}
	}
	else cout << "level map was empty" << endl;
	inFile.close();
}

LevelMap::~LevelMap(){
	for (int i = 0; i < mHeight; i++)	delete[] mMap[i];
	delete[] mMap;
}

int LevelMap::GetTileAt(unsigned int h, unsigned int w) {
	if (h < mHeight && w < mWidth)	return mMap[h][w];
	return 0;
}
int LevelMap::GetTileAt(Vector2D position) {
	if (position.x < mWidth && position.y < mHeight)	return mMap[(int)position.y][(int)position.x];
	else return -1;
}

void LevelMap::ChangeTileAt(unsigned int h, unsigned int w, unsigned int newValue) {
	mMap[h][w] = newValue;
}