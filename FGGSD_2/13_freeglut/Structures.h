#pragma once
#include <Windows.h> //required for OpenGL on Windows
#include <gl/GL.h>
#include <gl/GLU.h> //GL Utilities
#include "GL/freeglut.h"
#include "GLUTCallbacks.h"
#include <vector>

using namespace std;

struct Vector3 {
	float x, y, z;
	Vector3() {
		x = 0;
		y = 0;
		z = 0;
	}
	Vector3(float nX, float nY, float nZ) {
		x = nX;
		y = nY;
		z = nZ;
	}
	bool operator==(Vector3 other) {
		if (x == other.x && y == other.y && z == other.z) return true;
		else return false;
	}
};
struct Camera {
	Vector3 eye, center, up;
};
struct Colour {
	GLfloat r, g, b;
};
struct Vertex {
	GLfloat x, y, z;
};
struct Mesh {
	Vertex* Vertices;
	Colour* Colours;
	GLushort* Indices;
	int vertexCount, colourCount, indexCount;
};
struct TexCoord {
	GLfloat u, v;
};
struct TexturedMesh : public Mesh{
	TexCoord* TexCoords;
	int texCoordCount;
	Vector3* Normals;
	int normalCount;
};
struct Vector4 {
	float x, y, z, w;
	bool operator!=(Vector4 other) {
		if (x == other.x && y == other.y && z == other.z && w == other.w) return false;
		else return true;
	}
};
struct Lighting {
	Vector4 Ambient, Diffuse, Specular;
};
struct Material {
	Vector4 Ambient, Diffuse, Specular;
	GLfloat Shininess;
};
class SceneObject;

struct Branch {
	SceneObject* data; //have to use pointer to avoid include loop
	Branch* left;
	Branch* right;
	bool operator==(Branch other) {
		if (data == other.data) return true;
		else return false;
	}
};
struct Node {
	Branch* data;
	Node* next;
};
struct Quad { //triangle will have last two vertices identical
	int vertexIndices[4], texCoordIndices[4], normalIndices[4];
};
struct OBJ {
	vector<Vertex*> vertices;
	vector<TexCoord*> texCoords;
	vector<Vector3*> normals;
	vector<Quad*> faces;
	bool triangles;
	Vector3 midpoint;
};
enum COLOUR_MODE {
	pink = 1,
	changing
};