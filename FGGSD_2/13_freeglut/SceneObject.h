#pragma once
#include "Structures.h"
class SceneObject
{
protected:
	TexturedMesh * _mesh;
	OBJ* _object;
	Vector3 _position;
	GLfloat _rotation;
	float _rotationChange;
	Material* _material;
	GLuint _textureId;
	int _faceVertices;
	float _radius;
	bool _canRotate;
public:
	SceneObject(Mesh* _mesh);
	SceneObject(Mesh* _mesh, GLuint texId);
	SceneObject(OBJ* _obj, GLuint texId);
	~SceneObject();
	virtual void Update();
	virtual void Draw();
	Vector3 GetPosition() { return _position; };
	void DrawStart();
	void DrawEnd();
	bool IsColliding(SceneObject* otherObject);
	void ChangeMaterial(Material* mat);
	void ChangeMaterial(SceneObject* precedent);
	void AdjustColour();
	void AdjustPosition(Vector3 change);
	void SetRotatability(bool rotate) { _canRotate = rotate; };
	void ChangeTexture(GLuint texId) { _textureId = texId; };
};