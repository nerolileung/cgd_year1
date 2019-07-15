#include "MeshLoader.h"

#include <iostream>
#include <fstream>

using namespace std;

namespace MeshLoader
{
	void LoadVertices(ifstream& inFile, Mesh& mesh);
	void LoadColours(ifstream& inFile, Mesh& mesh);
	void LoadIndices(ifstream& inFile, Mesh& mesh);
	void LoadTexCoords(ifstream& inFile, TexturedMesh& mesh);

	void LoadVertices(ifstream& inFile, Mesh& mesh){
		inFile >> mesh.vertexCount;
		if (mesh.vertexCount > 0){
			mesh.Vertices = new Vertex[mesh.vertexCount];
			for (int i = 0; i < mesh.vertexCount; i++){
				inFile >> mesh.Vertices[i].x;
				inFile >> mesh.Vertices[i].y;
				inFile >> mesh.Vertices[i].z;
			}
		}
	}

	void LoadColours(ifstream& inFile, Mesh& mesh){
		inFile >> mesh.colourCount;
		if (mesh.colourCount > 0) {
			mesh.Colours = new Colour[mesh.colourCount];
			for (int i = 0; i < mesh.colourCount; i++) {
				inFile >> mesh.Colours[i].r;
				inFile >> mesh.Colours[i].g;
				inFile >> mesh.Colours[i].b;
			}
		}
	}

	void LoadIndices(ifstream& inFile, Mesh& mesh){
		inFile >> mesh.indexCount;
		if (mesh.indexCount > 0) {
			mesh.Indices = new GLushort[mesh.indexCount];
			for (int i = 0; i < mesh.indexCount; i++) {
				inFile >> mesh.Indices[i];
			}
		}
	}

	void LoadTexCoords(ifstream& inFile, TexturedMesh& mesh) {
		inFile >> mesh.texCoordCount;
		if (mesh.texCoordCount > 0) {
			mesh.TexCoords = new TexCoord[mesh.texCoordCount];
			for (int i = 0; i < mesh.texCoordCount; i++) {
				inFile >> mesh.TexCoords[i].u;
				inFile >> mesh.TexCoords[i].v;
			}
		}
	}

	void LoadNormals(ifstream& inFile, TexturedMesh& mesh) {
		inFile >> mesh.normalCount;
		if (mesh.normalCount > 0) {
			mesh.Normals = new Vector3[mesh.normalCount];
			for (int i = 0; i < mesh.normalCount; i++) {
				inFile >> mesh.Normals[i].x;
				inFile >> mesh.Normals[i].y;
				inFile >> mesh.Normals[i].z;
			}
		}
	}

	Mesh* MeshLoader::Load(char* path)
	{
		Mesh* mesh = new Mesh();
		ifstream inFile;

		inFile.open(path);
		if (!inFile.good())  
		{
			cerr  << "Can't open texture file " << path << endl;
			return nullptr;
		}

		LoadVertices(inFile, *mesh);
		LoadColours(inFile, *mesh);
		LoadIndices(inFile,*mesh);
		inFile.close();
		return mesh;
	}

	TexturedMesh* MeshLoader::LoadTextured(char* path) {
		TexturedMesh* mesh = new TexturedMesh();
		ifstream inFile;
		inFile.open(path);
		if (!inFile.good()) {
			cerr << "Can't open texture file " << path << endl;
			return nullptr;
		}
		LoadVertices(inFile, *mesh);
		LoadColours(inFile, *mesh);
		LoadTexCoords(inFile, *mesh);
		LoadIndices(inFile, *mesh);
		inFile.close();
		return mesh;
	}

	TexturedMesh* MeshLoader::LoadLit(char* path) {
		TexturedMesh* mesh = new TexturedMesh();
		ifstream inFile;
		inFile.open(path);
		if (!inFile.good()) {
			cerr << "Can't open texture file " << path << endl;
			return nullptr;
		}
		LoadVertices(inFile, *mesh);
		LoadTexCoords(inFile, *mesh);
		LoadNormals(inFile, *mesh);
		LoadIndices(inFile, *mesh);
		inFile.close();
		return mesh;
	}
}