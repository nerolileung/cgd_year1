//aka HelloGL in tutorials

#include "Structures.h"
#include "source.h"
#include "MeshLoader.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>

using namespace std;

source::source(int argc, char* argv[]){
	srand(time(NULL));
	camera = new Camera();
	camera->eye.x = -100.0f;
	camera->eye.y = -100.0f;
	camera->eye.z = -200.0f;
	camera->center.x = 0.0f;
	camera->center.y = -30.0f;
	camera->center.z = -50.0f;
	camera->up.x = 0.0f;
	camera->up.y = 1.0f;
	camera->up.z = 0.0f;
	mode = COLOUR_MODE::pink;
	GLUTCallbacks::Init(this); // this keyword is pointer to current class instance
	glutInit(&argc, argv);
	InitGL();
	InitObjects();
	InitLight();
	glutMainLoop();
}


source::~source(){
	delete camera;
	camera = nullptr;
	delete objects;
	objects = nullptr;
	delete lightPosition;
	lightPosition = nullptr;
	delete lightData;
	lightData = nullptr;
	delete penguins;
	penguins = nullptr;
	delete sand;
	sand = nullptr;
	delete cubeTexMesh;
	cubeTexMesh = nullptr;
	delete pinkCubeMat;
	pinkCubeMat = nullptr;
	delete blueCubeMat;
	blueCubeMat = nullptr;
}

void source::Display() { // transformation calls are done in reverse order
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	objects->traverseDraw(objects->root);
	DrawUI();
	glFlush(); //flushes scene to graphics card
	glutSwapBuffers(); //double buffering woo
}

void source::Update() {
	glLoadIdentity(); //clear modelview matrix
	// tell opengl where to move camera
	gluLookAt(camera->eye.x, camera->eye.y, camera->eye.z, camera->center.x, camera->center.y, camera->center.z, camera->up.x, camera->up.y, camera->up.z);
	glLightfv(GL_LIGHT0, GL_AMBIENT, &(lightData->Ambient.x));
	glLightfv(GL_LIGHT0, GL_DIFFUSE, &(lightData->Diffuse.x));
	glLightfv(GL_LIGHT0, GL_SPECULAR, &(lightData->Specular.x));
	//fun collision stuff
	if (objects->root->left != nullptr){
		if (objects->root->data->IsColliding(objects->root->left->data)) {
			objects->popLeafAfter(objects->root, objects->root->left);
			cubeCount++;
			if (objects->root->left == nullptr && objects->root->right != nullptr) {
				objects->root->left = objects->root->right;
				objects->root->right = nullptr;
			}
		}
	}
	switch (mode) {
	case changing:
		objects->traverseUpdateColour(objects->root, objectsRotate);
		break;
	default:
		objects->preOrderTraverse(objects->root, objectsRotate);
		break;
	}
	if (objects->root->left != nullptr) SetControlledCube();
	glutPostRedisplay();
}

void source::Keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'e':
		camera->center.x += 10.0f;
		break;
	case 'r':
		camera->center.x -= 10.0f;
		break;
	case 'f':
		camera->center.y += 10.0f;
		break;
	case 'c':
		camera->center.y -= 10.0f;
		break;
	case 'q':
		camera->eye.z += 10.0f;
		break;
	case 'z':
		camera->eye.z -= 10.0f;
		break;
	case 'w':
		camera->eye.y += 10.0f;
		break;
	case 's':
		camera->eye.y -= 10.0f;
		break;
	case 'a':
		camera->eye.x += 10.0f;
		break;
	case 'd':
		camera->eye.x -= 10.0f;
		break;
	case ' ':
		objectsRotate = !objectsRotate;
		break;
	case 'p':
		objects->pushLeaf(objects->root, objects->makeNewBranch(new Cube(cubeTexMesh, pinkCubeMat, penguins->GetID())));
		SetControlledCube();
		break;
	case '1':
		if (mode != COLOUR_MODE::pink) {
			objects->traverseSetColour(objects->root, pinkCubeMat);
			mode = COLOUR_MODE::pink;
		}
		break;
	case '2':
		if (mode != COLOUR_MODE::changing) {
			objects->traverseSetColour(objects->root, objects->root->data);
			mode = mode = COLOUR_MODE::changing;
		}
		break;
	}
	if (objects->root->left != nullptr) {
		switch (key) {
		case 'i':
			objects->root->left->data->AdjustPosition(Vector3(0, 5, 0));
			break;
		case 'k':
			objects->root->left->data->AdjustPosition(Vector3(0, -5, 0));
			break;
		case 'j':
			objects->root->left->data->AdjustPosition(Vector3(5, 0, 0));
			break;
		case 'l':
			objects->root->left->data->AdjustPosition(Vector3(-5, 0, 0));
			break;
		case 'u':
			objects->root->left->data->AdjustPosition(Vector3(0, 0, 5));
			break;
		case 'm':
			objects->root->left->data->AdjustPosition(Vector3(0, 0, -5));
			break;
		}
	}
	
}

void source::InitGL() {
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); //double buffering, colour
	//window stuff
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(500, 0);
	glutCreateWindow("Little Cubes and Tea");
	glutDisplayFunc(GLUTCallbacks::Display);
	glutTimerFunc(REFRESHRATE, GLUTCallbacks::Timer, REFRESHRATE); // 16ms per frame = 60fps
	glutKeyboardFunc(GLUTCallbacks::Keyboard); //let freeglut know keyboard method exists
	 // 3d camera setup
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); //reset projection matrix
	glViewport(0, 0, 800, 800); //viewport = window
	gluPerspective(45, 1, 0.1, 1000);
	glMatrixMode(GL_MODELVIEW); // switch back
	// culling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);
	//lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

void source::InitObjects() {
	//load cubes
	penguins = new Texture2D();
	penguins->Load((char*)"Penguins.raw", 512, 512);
	cubeTexMesh = MeshLoader::LoadLit((char*)"cube.txt");
	pinkCubeMat = new Material();
	pinkCubeMat->Ambient.x = 1.0;
	pinkCubeMat->Ambient.y = 0.2;
	pinkCubeMat->Ambient.z = 0.8;
	pinkCubeMat->Ambient.w = 1.0;
	pinkCubeMat->Diffuse.x = 1.0;
	pinkCubeMat->Diffuse.y = 1.0;
	pinkCubeMat->Diffuse.z = 1.0;
	pinkCubeMat->Diffuse.w = 1.0;
	pinkCubeMat->Specular.x = 1.0;
	pinkCubeMat->Specular.y = 1.0;
	pinkCubeMat->Specular.z = 1.0;
	pinkCubeMat->Specular.w = 1.0;
	pinkCubeMat->Shininess = 100.0f;
	sand = new Texture2D();
	sand->Load((char*)"blue.raw", 512, 512);
	blueCubeMat = new Material();
	blueCubeMat->Ambient.x = 0.258;
	blueCubeMat->Ambient.y = 0.658;
	blueCubeMat->Ambient.z = 1.0;
	blueCubeMat->Ambient.w = 1.0;
	blueCubeMat->Diffuse.x = 0.5;
	blueCubeMat->Diffuse.y = 0.5;
	blueCubeMat->Diffuse.z = 0.5;
	blueCubeMat->Diffuse.w = 1.0;
	blueCubeMat->Specular.x = 1.0;
	blueCubeMat->Specular.y = 1.0;
	blueCubeMat->Specular.z = 1.0;
	blueCubeMat->Specular.w = 1.0;
	blueCubeMat->Shininess = 80.0f;
	//load teapot
	Texture2D* teapotTex = new Texture2D();
	teapotTex->Load((char*)"pink.raw", 512, 512);
	OBJ* teapotObj = OBJLoader::LoadTextured((char*)"pinkTeapot.obj");
	//put objects in binary tree
	Branch* start = new Branch;
	start->data = new SceneObject(teapotObj, teapotTex->GetID());
	start->left = nullptr;
	start->right = nullptr;
	objects = new BinaryTree(start);
	objects->pushLeaf(start, objects->makeNewBranch(new Cube(cubeTexMesh, blueCubeMat, sand->GetID())));
	for (int i = 2; i < objectCount; i++)	objects->pushLeaf(start,objects->makeNewBranch(new Cube(cubeTexMesh,pinkCubeMat,penguins->GetID())));
	cubeCount = 0;
	objectsRotate = true;
	//loading cleanup
	delete teapotTex;
	teapotTex = nullptr;
	delete teapotObj;
	teapotObj = nullptr;
}

void source::InitLight() {
	lightPosition = new Vector4();
	lightPosition->x = 0.0;
	lightPosition->y = 0.0;
	lightPosition->z = 1.0;
	lightPosition->w = 0.0;

	lightData = new Lighting();
	lightData->Ambient.x = 0.2;
	lightData->Ambient.y = 0.2;
	lightData->Ambient.z = 0.2;
	lightData->Ambient.w = 1.0;
	lightData->Diffuse.x = 0.8;
	lightData->Diffuse.y = 0.8;
	lightData->Diffuse.z = 0.8;
	lightData->Diffuse.w = 1.0;
	lightData->Specular.x = 0.2;
	lightData->Specular.y = 0.2;
	lightData->Specular.z = 0.2;
	lightData->Specular.w = 1.0;
	
}

void source::RenderText(const char* text, Vector3* position, Colour* colour) {
	glLoadIdentity(); // separate text from everything else
	glPushMatrix();
		glDisable(GL_TEXTURE);
		glDisable(GL_LIGHTING);
		glColor3f(colour->r,colour->g,colour->b);
		glTranslatef(position->x, position->y, position->z);
		glRasterPos3f(0.0f, 0.0f,0.0f);
		glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)text);
		glEnable(GL_LIGHTING);
		glEnable(GL_TEXTURE);
	glPopMatrix();
}
void source::DrawUI() {
	// "score"
	Vector3 v = { -5.0f,19.0f,-50.0f };
	Colour c = { 1.0f, 0.321f, 0.635f };
	string cubeText = "Cubes in tea: " + to_string(cubeCount);
	RenderText(cubeText.c_str(), &v, &c);
	// colour mode
	Vector3 topLeft = { -20.0f,19.0f,-50.0f };
	string modeText = "Colours: ";
	switch (mode) {
	case changing:
		modeText += "shifting";
		break;
	default:
		modeText += "default";
		break;
	}
	RenderText(modeText.c_str(), &topLeft, &c);
	if (objects->root->left == nullptr) { //all cubes gone
		Vector3 bottom = { -8.0f,-19.0f,-50.0f };
		string bottomText = "Press P to spawn cubes";
		RenderText(bottomText.c_str(), &bottom, &c);
	}
}
void source::SetControlledCube() {
	objects->root->left->data->ChangeMaterial(blueCubeMat);
	objects->root->left->data->ChangeTexture(sand->GetID());
}