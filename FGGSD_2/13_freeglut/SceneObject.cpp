#include "SceneObject.h"
#include <iostream>
using namespace std;

SceneObject::SceneObject(Mesh* _mesh) {}
SceneObject::SceneObject(Mesh* _mesh, GLuint texId){}

SceneObject::SceneObject(OBJ* _obj, GLuint texId) {
	_object = new OBJ;
	_object->vertices = _obj->vertices;
	_object->texCoords = _obj->texCoords;
	_object->normals = _obj->normals;
	_object->faces = _obj->faces;
	_textureId = texId;
	if (_obj->triangles) _faceVertices = 3;
	else _faceVertices = 4;
	_position.x = -30.0f;
	_position.y = -30.0f;
	_position.z = -30.0f;
	_rotation = 0.0f;
	_rotationChange = 0.5f;
	_material = new Material();
	_material->Ambient.x = 1.0;
	_material->Ambient.y = 0.2;
	_material->Ambient.z = 0.8;
	_material->Ambient.w = 1.0;
	_material->Diffuse.x = 1.0;
	_material->Diffuse.y = 1.0;
	_material->Diffuse.z = 1.0;
	_material->Diffuse.w = 1.0;
	_material->Specular.x = 1.0;
	_material->Specular.y = 1.0;
	_material->Specular.z = 1.0;
	_material->Specular.w = 1.0;
	_material->Shininess = 100.0f;
	_radius = 50.0f;
	_canRotate = true;
}

SceneObject::~SceneObject(){
	delete _mesh;
	_mesh = nullptr;
	delete _object;
	_object = nullptr;
	delete _material;
	_material = nullptr;
}

void SceneObject::Draw() {
	DrawStart();
	DrawEnd();
}
void SceneObject::Update(){
	if (_canRotate) _rotation += _rotationChange;
	if (_rotation > 360.0f)	_rotation = 0.0f;
	else if (_rotation < 0.0f) _rotation = 360.0f;
}
void SceneObject::DrawStart() {
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
	glRotatef(_rotation, 0.0f, 1.0f, 0.0f);
	if (_faceVertices == 3) glBegin(GL_TRIANGLES);
	else glBegin(GL_QUADS);
	if (_mesh != nullptr) {
		for (int i = 0; i < _mesh->indexCount; i++) {
			glNormal3fv(&_mesh->Normals[_mesh->Indices[i]].x);
			glTexCoord2fv(&_mesh->TexCoords[_mesh->Indices[i]].u);
			glVertex3fv(&_mesh->Vertices[_mesh->Indices[i]].x);
		}
	}
	else if (_object != nullptr) {
		for (int i = 0; i < _object->faces.size(); i++) {
			for (int j = 0; j < _faceVertices; j++) {
				glNormal3fv(&_object->normals[_object->faces[i]->normalIndices[j]]->x);
				glTexCoord2fv(&_object->texCoords[_object->faces[i]->texCoordIndices[j]]->u);
				glVertex3fv(&_object->vertices[_object->faces[i]->vertexIndices[j]]->x);
			}
		}
	}
	else cout << "no vertex data found" << endl;
	glEnd();
}
void SceneObject::DrawEnd() {
	glPopMatrix();
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glDisable(GL_TEXTURE_2D);
}
bool SceneObject::IsColliding(SceneObject* otherObject) {
	float distanceX = pow((_object->midpoint.x - otherObject->_position.x), 2);
	float distanceY = pow((_object->midpoint.y - otherObject->_position.y), 2);
	float distanceZ = pow((_object->midpoint.z - otherObject->_position.z), 2);;
	float totalDistance = distanceX + distanceY + distanceZ;
	float radiusDistance = pow((_radius + otherObject->_radius), 2);
	if (totalDistance <= radiusDistance) return true;
	else return false;
}
void SceneObject::ChangeMaterial(Material* mat) {
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
void SceneObject::ChangeMaterial(SceneObject* precedent) {
	if (precedent->_material->Ambient.x < 1.0 && _material->Ambient.x < 1.0) _material->Ambient.x = precedent->_material->Ambient.x + 0.2;
	else _material->Ambient.x = precedent->_material->Ambient.x - 0.2;
	if (_material->Ambient.x > 1.0) _material->Ambient.x = 1.0;
	else if (_material->Ambient.x < 0.0) _material->Ambient.x = 0.0;

	if (precedent->_material->Ambient.y < 1.0 && _material->Ambient.y < 1.0) _material->Ambient.y = precedent->_material->Ambient.y + 0.2;
	else _material->Ambient.y = precedent->_material->Ambient.y - 0.2;
	if (_material->Ambient.y > 1.0) _material->Ambient.y = 1.0;
	else if (_material->Ambient.y < 0.0) _material->Ambient.y = 0.0;

	if (precedent->_material->Ambient.z < 1.0 && _material->Ambient.z < 1.0) _material->Ambient.z = precedent->_material->Ambient.z + 0.2;
	else _material->Ambient.z = precedent->_material->Ambient.z - 0.2;
	if (_material->Ambient.z > 1.0) _material->Ambient.z = 1.0;
	else if (_material->Ambient.z < 0.0) _material->Ambient.z = 0.0;

	if (_material->Diffuse != _material->Ambient) _material->Diffuse = _material->Ambient;
}
void SceneObject::AdjustPosition(Vector3 change) {
	_position.x += change.x;
	_position.y += change.y;
	_position.z += change.z;
}
void SceneObject::AdjustColour() {
	if (_material->Ambient.x < 1.0) _material->Ambient.x += 0.01;
	else _material->Ambient.x = 0.0;
	if (_material->Ambient.y < 1.0) _material->Ambient.y += 0.01;
	else _material->Ambient.y = 0.0;
	if (_material->Ambient.z < 1.0) _material->Ambient.z += 0.01;
	else _material->Ambient.z = 0.0;
	if (_material->Diffuse != _material->Ambient) _material->Diffuse = _material->Ambient;
}