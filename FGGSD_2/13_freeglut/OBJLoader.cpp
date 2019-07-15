#include "OBJLoader.h"
#include <string>

using namespace std;

namespace OBJLoader {
	OBJ* OBJLoader::LoadTextured(char* path) {
		OBJ* object = new OBJ;
		ifstream inFile;
		inFile.open(path);
		if (!inFile.good()) {
			cerr << "Can't open texture file " << path << endl;
			return nullptr;
		}
		//go through file
		char firstWordInLine[24];
		while (inFile >> firstWordInLine) {
			if (strcmp(firstWordInLine, "v") == 0)	LoadVertices(inFile, *object);
			else if (strcmp(firstWordInLine, "vn") == 0)	LoadNormals(inFile, *object);
			else if (strcmp(firstWordInLine, "vt") == 0)	LoadTexCoords(inFile, *object);
			else if (strcmp(firstWordInLine, "f") == 0)	LoadIndices(inFile, *object);
			//else if (strcmp(firstWordInLine,"mtllib") == 0){} //mtl file name
			//else if (strcmp(firstWordInLine,"usemtl")==0){} //material name
		}
		inFile.close();
		CalculateMidpoint(*object);
		return object;
	}
	void OBJLoader::LoadVertices(ifstream& inFile, OBJ& object) {
		Vertex* vertex = new Vertex;
		inFile >> vertex->x;
		inFile >> vertex->y;
		inFile >> vertex->z;
		object.vertices.push_back(vertex);
	}
	void OBJLoader::LoadNormals(ifstream& inFile, OBJ& object) {
		Vector3* normal = new Vector3;
		inFile >> normal->x;
		inFile >> normal->y;
		inFile >> normal->z;
		object.normals.push_back(normal);
	}
	void OBJLoader::LoadTexCoords(ifstream& inFile, OBJ& object) {
		TexCoord* textureCoord = new TexCoord;
		inFile >> textureCoord->u;
		inFile >> textureCoord->v;
		object.texCoords.push_back(textureCoord);
	}
	void OBJLoader::LoadIndices(ifstream& inFile, OBJ& object) { //line is 3-4 sets of vertex/texCoord/normal indices
		Quad* face = new Quad;
		string faceData = "";
		object.triangles = false;
		getline(inFile, faceData);
		//separate line into index sets based on no. of spaces
		int subStrStartPos = 1; // skip the "f " at the beginning of the line
		string indiceSet[4] = { "","","","" };
		int currentEmptySet = 0;
		for (int i = subStrStartPos; i < faceData.size(); i++) {
			if (faceData[i] == ' ' && i != subStrStartPos) {
				int length = i - subStrStartPos;
				indiceSet[currentEmptySet] = faceData.substr(subStrStartPos, length);
				subStrStartPos = i + 1;
				currentEmptySet++;
			}
		}
		//get indices from substrings; separated by "/"
		for (int i = 0; i < 4; i++) {
			if (i == 3 && indiceSet[i] == "") {
				//copy data from third set into fourth set; quad pretending to be tri
				face->vertexIndices[3] = face->vertexIndices[2];
				face->texCoordIndices[3] = face->texCoordIndices[2];
				face->normalIndices[3] = face->normalIndices[2];
				object.triangles = true;
				break;
			}
			subStrStartPos = 0;
			int indexTypeCounter = 0; //0 - vertex, 1 - texCoord, 2 - normal
			for (int j = subStrStartPos; j < indiceSet[i].size(); j++) {
				if (indiceSet[i][j] == '/' || j == indiceSet[i].size() - 1) {
					int length = j - subStrStartPos;
					if (length <= 0) length = 1;
					string indexRaw = indiceSet[i].substr(subStrStartPos, length);
					int index = stoi(indexRaw);
					switch (indexTypeCounter) {
					case 0:
						face->vertexIndices[i] = index-1;
						break;
					case 1:
						face->texCoordIndices[i] = index-1;
						break;
					case 2:
						face->normalIndices[i] = index-1;
						break;
					default:
						cout << "error when filling in face data: index type counter was " << indexTypeCounter << endl;
						break;
					}
					subStrStartPos = j + 1;
					indexTypeCounter++;
				}
			}
		}
		object.faces.push_back(face);
	}
	void OBJLoader::CalculateMidpoint(OBJ& object) {
		Vector3 max = { 0,0,0 };
		Vector3 min = { 0,0,0 };
		for (int i = 0; i < object.vertices.size(); i++) {
			if (object.vertices[i]->x < min.x) min.x = object.vertices[i]->x;
			else if (object.vertices[i]->x > max.x) max.x = object.vertices[i]->x;
			if (object.vertices[i]->y < min.y) min.y = object.vertices[i]->y;
			else if (object.vertices[i]->y > max.y) max.y = object.vertices[i]->y;
			if (object.vertices[i]->z < min.z) min.z = object.vertices[i]->z;
			else if (object.vertices[i]->z> max.z) max.z = object.vertices[i]->z;
		}
		object.midpoint.x = (min.x + max.x) / 2;
		object.midpoint.y = (min.y + max.y) / 2;
		object.midpoint.z = (min.z + max.z) / 2;
	}
}