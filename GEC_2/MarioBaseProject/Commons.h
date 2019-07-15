#ifndef COMMONS_H
#define COMMONS_H

#pragma once

struct Vector2D {
	float x;
	float y;
	Vector2D() {
		x = 0.0f;
		y = 0.0f;
	}
	Vector2D(float initialX, float initialY) {
		x = initialX;
		y = initialY;
	};
};

enum SCREENS {
	SCREEN_MENU = 0,
	SCREEN_LEVEL1,
	SCREEN_GAMEOVER1,
	SCREEN_LEVEL2,
	SCREEN_WIN2,
	SCREEN_GAMEOVER2
};

enum FACING { //rename this later?
	FACING_LEFT = 0,
	FACING_RIGHT
};

struct Rect2D {
	float x;
	float y;
	float width;
	float height;
	Rect2D() {
		x, y, width, height = 0.0f;
	}
	Rect2D(float newX, float newY, float newWidth, float newHeight) {
		x = newX;
		y = newY;
		width = newWidth;
		height = newHeight;
	}
};
enum SCREEN_STATE {
	GAMEOVER = -1,
	PAUSED,
	RUNNING,
	WIN
};
struct SpriteLetter {
	char symbol;
	int width;
	int x;
};

enum BLOCK_TYPE {
	REGULAR = 1,
	SPIKED_SOLO,
	SPIKED_LEFT,
	SPIKED_RIGHT,
	SPIKED_MIDDLE,
	LONG
};

#endif // !COMMONS_H