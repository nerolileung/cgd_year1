#pragma once
#include <Windows.h> //required for OpenGL on Windows
#include <gl/GL.h>
#include <gl/GLU.h> //GL Utilities
#include "Structures.h"
#include "GL/freeglut.h"
#include "GLUTCallbacks.h"
#include "Cube.h"
#include "BinaryTree.h"
#include "OBJLoader.h"
#include "Texture2D.h"

class source {
public:
	source(int argc, char* argv[]);
	~source();
	void Display();
	void Update();
	const int REFRESHRATE = 16;
	void Keyboard(unsigned char key, int x, int y);
	Camera* camera;
	int objectCount = 10;
	BinaryTree* objects;
	void InitObjects();
	void InitGL();
	void InitLight();
	void RenderText(const char* text, Vector3* position, Colour* colour); //DrawText is taken
	void DrawUI();
private:
	Vector4* lightPosition;
	Lighting* lightData;
	int cubeCount;
	bool objectsRotate;
	Texture2D* penguins;
	Texture2D* sand;
	TexturedMesh* cubeTexMesh;
	Material* pinkCubeMat;
	Material* blueCubeMat;
	COLOUR_MODE mode;
	void SetControlledCube();
};