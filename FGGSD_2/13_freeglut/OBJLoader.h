#pragma once
#ifndef OBJLOADER_H
#define OBJLOADER_H

#include "Structures.h"
#include <iostream>
#include <fstream>

namespace OBJLoader{
	OBJ* LoadTextured(char* path);
	void LoadVertices(ifstream& inFile, OBJ& object);
	void LoadNormals(ifstream& inFile, OBJ& object);
	void LoadTexCoords(ifstream& inFile, OBJ& object);
	void LoadIndices(ifstream& inFile, OBJ& object);
	void CalculateMidpoint(OBJ& object);
};

#endif // !OBJLOADER_H