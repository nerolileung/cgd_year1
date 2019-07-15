#pragma once
#include "Character.h"

class Collisions{
private:
	Collisions();
	static Collisions* mInstance; // only one instance of this for the collision class ever
public:
	~Collisions();
	static Collisions* Instance();
	bool Circle(Character* entity1, Character* entity2);
	bool Box(Rect2D rect1, Rect2D rect2);
};

