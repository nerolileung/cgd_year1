#ifndef CUBE_H
#define CUBE_H
#pragma once
#include "Structures.h"
#include "SceneObject.h"

class Cube : public SceneObject
{
public:
	Cube(Mesh* mesh);
	Cube(Mesh* mesh, float x, float y, float z);
	Cube(TexturedMesh* mesh, Material* mat, GLuint texId);
	~Cube();
	void Draw();
	//static methods exist without instance of class
};
#endif // !CUBE_H
