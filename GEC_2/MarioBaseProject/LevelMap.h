#ifndef _LEVELMAP_H
#define _LEVELMAP_H

#pragma once

#include "Constants.h"
#include <string>
#include "Commons.h"

using namespace std;

class LevelMap
{
public:
	LevelMap(int map[MAP_HEIGHT][MARIO_MAP_WIDTH]);
	LevelMap(string filePath, bool marioMap);
	~LevelMap();
	int GetTileAt(unsigned int h, unsigned int w);
	int GetTileAt(Vector2D position);
	void ChangeTileAt(unsigned int h, unsigned int w, unsigned int newValue);
private:
	int** mMap;
	int mHeight;
	int mWidth;
};

#endif