#include "Collisions.h"

Collisions* Collisions::mInstance = NULL;

Collisions::Collisions() {}

Collisions::~Collisions()
{
	mInstance = NULL;
}

Collisions* Collisions::Instance() {
	if (!mInstance)	mInstance = new Collisions;
	return mInstance;
}

bool Collisions::Circle(Character* entity1, Character* entity2) {
	//vector separating entities
	float differenceX = entity1->GetPosition().x - entity2->GetPosition().x;
	float differenceY = entity1->GetPosition().y - entity2->GetPosition().y;
	Vector2D vec = Vector2D(differenceX, differenceY);
	double distance = sqrt((vec.x*vec.x)+(vec.y*vec.y)); // distance = vector length
	double totalDistance = (entity1->GetCollisionRadius()+entity2->GetCollisionRadius()); // total distance = total radius
	return (distance < totalDistance);
}

bool Collisions::Box(Rect2D rect1, Rect2D rect2) {
	bool xCollide = true;
	bool yCollide = true;
	if ((rect1.x + rect1.width < rect2.x) || (rect1.x > rect2.x + rect2.width))	xCollide = false; // entity 1 is left or right of entity 2
	if ((rect1.y + rect1.height < rect2.y) || (rect1.y > rect2.y + rect2.height))	yCollide = false; // entity 1 is above or below entity 2
	if (xCollide && yCollide)	return true;
	else return false;
}