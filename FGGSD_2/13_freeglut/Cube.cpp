#include "Cube.h"
#include <iostream>

using namespace std;

Cube::Cube(Mesh* mesh) : SceneObject(mesh){
	_position.x = ((rand() % 49) - 25);
	_position.y = ((rand() % 49) - 25);
	_position.z = ((rand() % 49) - 25);
	_rotationChange = 0.5f + ((rand() % 20) - 10);
	_mesh = new TexturedMesh();
	_mesh->vertexCount = mesh->vertexCount;
	_mesh->colourCount = mesh->colourCount;
	_mesh->indexCount = mesh->indexCount;
	_mesh->Vertices = mesh->Vertices;
	_mesh->Colours = mesh->Colours;
	_mesh->Indices = mesh->Indices;
	_faceVertices = 3;
}

Cube::Cube(Mesh* mesh, float x, float y, float z) : SceneObject(mesh){ //need to specify which constructor it inherits from or it complains that no default constructor exists
	_position.x = x;
	_position.y = y;
	_position.z = z;
	_rotation = 0.0f;
	_rotationChange = 0.5f + ((rand() % 20) - 10);
	_mesh = new TexturedMesh();
	_mesh->vertexCount = mesh->vertexCount;
	_mesh->colourCount = mesh->colourCount;
	_mesh->indexCount = mesh->indexCount ;
	_mesh->Vertices = mesh->Vertices;
	_mesh->Colours = mesh->Colours;
	_mesh->Indices = mesh->Indices;
}

Cube::Cube(TexturedMesh* mesh, Material* mat, GLuint texId) : SceneObject(mesh, texId){
	//positioning
	switch (rand() % 3) {
	case 0:
		_position.x = ((rand() % 20) + 50);
		if (rand() % 2 == 0) _position.x = _position.x * -1;
		_position.y = (rand() % 50);
		if (rand() % 2 == 0) _position.y = _position.y * -1;
		_position.z = (rand() % 50);
		if (rand() % 2 == 0) _position.z = _position.z * -1;
		break;
	case 1:
		_position.y = ((rand() % 20) + 50);
		if (rand() % 2 == 0) _position.y = _position.y * -1;
		_position.x = (rand() % 50);
		if (rand() % 2 == 0) _position.x = _position.x * -1;
		_position.z = (rand() % 50);
		if (rand() % 2 == 0) _position.z = _position.z * -1;
		break;
	case 2:
		_position.z = ((rand() % 20) + 50);
		if (rand() % 2 == 0) _position.z = _position.z * -1;
		_position.y = (rand() % 50);
		if (rand() % 2 == 0) _position.y = _position.y * -1;
		_position.x = (rand() % 50);
		if (rand() % 2 == 0) _position.x = _position.x * -1;
		break;
	}
	_rotationChange = 0.5f + ((rand() % 10) - 5);
	_textureId = texId;
	if (mat != nullptr) {
		_mesh = new TexturedMesh();
		_mesh->vertexCount = mesh->vertexCount;
		_mesh->texCoordCount = mesh->texCoordCount;
		_mesh->normalCount = mesh->normalCount;
		_mesh->indexCount = mesh->indexCount;
		_mesh->Vertices = mesh->Vertices;
		_mesh->TexCoords = mesh->TexCoords;
		_mesh->Normals = mesh->Normals;
		_mesh->Indices = mesh->Indices;
		//material setup
		_material = new Material();
		_material->Ambient.x = mat->Ambient.x;
		_material->Ambient.y = mat->Ambient.y;
		_material->Ambient.z = mat->Ambient.z;
		_material->Ambient.w = mat->Ambient.w;
		_material->Diffuse.x = mat->Diffuse.x;
		_material->Diffuse.y = mat->Diffuse.y;
		_material->Diffuse.z = mat->Diffuse.z;
		_material->Diffuse.w = mat->Diffuse.w;
		_material->Specular.x = mat->Specular.x;
		_material->Specular.y = mat->Specular.y;
		_material->Specular.z = mat->Specular.z;
		_material->Specular.w = mat->Specular.w;
		_material->Shininess = mat->Shininess;
	}
	else {
		_mesh = new TexturedMesh();
		_mesh->vertexCount = mesh->vertexCount;
		_mesh->colourCount = mesh->colourCount;
		_mesh->texCoordCount = mesh->texCoordCount;
		_mesh->indexCount = mesh->indexCount;
		_mesh->Vertices = mesh->Vertices;
		_mesh->Colours = mesh->Colours;
		_mesh->TexCoords = mesh->TexCoords;
		_mesh->Indices = mesh->Indices;
	}
	_radius = 0.5f;
	_canRotate = true;
}


Cube::~Cube()
{
	delete _mesh;
	_mesh = nullptr;
	delete _material;
	_material = nullptr;
}

void Cube::Draw() { // translate, rotate, translate, draw
	if (_mesh->texCoordCount > 0) {
		glEnable(GL_TEXTURE_2D);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, _textureId);
		glMaterialfv(GL_FRONT, GL_AMBIENT, &(_material->Ambient.x));
		glMaterialfv(GL_FRONT, GL_DIFFUSE, &(_material->Diffuse.x));
		glMaterialfv(GL_FRONT, GL_SPECULAR, &(_material->Specular.x));
		glMaterialf(GL_FRONT, GL_SHININESS, _material->Shininess);
		glPushMatrix();
		glTranslatef(_position.x, _position.y, _position.z);
		glRotatef(_rotation, 1.0f, 0.0f, 0.0f);
		glBegin(GL_TRIANGLES);
		for (int i = 0; i < _mesh->indexCount; i++) {
			glNormal3fv(&_mesh->Normals[_mesh->Indices[i]].x);
			glTexCoord2fv(&_mesh->TexCoords[_mesh->Indices[i]].u);
			glVertex3fv(&_mesh->Vertices[_mesh->Indices[i]].x);
		}
		glEnd();
		glPopMatrix();
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
		glDisable(GL_TEXTURE_2D);
	}
	else {
		glPushMatrix();
		glTranslatef(_position.x, _position.y, _position.z);
		glRotatef(_rotation, 1.0f, 0.0f, 0.0f);
		glBegin(GL_TRIANGLES);
		for (int i = 0; i < _mesh->indexCount; i++) {
			glColor3fv(&_mesh->Colours[_mesh->Indices[i]].r);
			glVertex3fv(&_mesh->Vertices[_mesh->Indices[i]].x);
		}
		glEnd();
		glPopMatrix();
	}
}