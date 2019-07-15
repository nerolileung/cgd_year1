#pragma once

// If Windows and not in Debug, this will run without a console window
// You can use this to output information when debugging using cout or cerr
#ifdef WIN32 
	#ifndef _DEBUG
		#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
	#endif
#endif

// Just need to include main header file
#include "S2D/S2D.h"
#define MUNCHIECOUNT 16
#define GHOSTCOUNT 3

// Reduces the amount of typing by including all classes in S2D namespace
using namespace S2D;

enum Direction {
	right,
	down,
	left,
	up
};

enum GhostType { //ideas: scared ghost that runs away - needs to remain within the screen; bouncer ghost that patrols edges of screen
	patrolHorizontal,
	patrolVertical,
	chase
};

enum GameState {
	running,
	start,
	pause,
	gameOver,
	win
};

enum CherryType {
	regular,
	shiny,
	slimed // worth less than regular - incentive to grab cherries before ghosts hit them
};

// data for player avatar (pacman)
struct Player {
	float speed;
	int frameTime;
	Vector2* position;
	Rect* sourceRect;
	Texture2D* texture;
	Direction direction;
	int frame;
	int currentFrameTime;
	bool moving;
	float speedMultiplier;
	bool dead = false;
};

struct Collectable {
	int frameCount;
	Vector2* position;
	int frameTime;
	int currentFrameTime;
	int frame;
	Rect* sourceRect;
	int timesCollected;
	CherryType type;
};

struct Enemy {
	Vector2* position;
	Rect* sourceRect;
	Direction direction;
	float speed;
	int frameCount;
	int frameTime;
	int currentFrameTime;
	int frame;
	GhostType type;
};

// Declares the Pacman class which inherits from the Game class.
// This allows us to overload the Game class methods to help us
// load content, draw and update our game.
class Pacman : public Game
{
private:
	Player* _pacman; //behold the glory of structs
	Collectable* _munchies[MUNCHIECOUNT];
	Enemy* _ghosts[GHOSTCOUNT];
	Texture2D* _munchieTexture;
	Texture2D* _ghostTexture;
	int _score;
	int _shinyMunchieCount;

	// Data for pause menu
	Texture2D* _menuStart;
	Texture2D* _menuPause;
	Texture2D* _menuGameOver;
	Texture2D* _menuWin;
	Rect* _menuRectangle;
	Vector2* _menuStringPosition;
	bool _pKeyDown;
	GameState gameState;

	// Position for String
	Vector2* _stringPosition;

	//audio
	SoundEffect* _pop;
	SoundEffect* _shinyPop;

	//method prototypes
	void CheckMovementInput(int elapsedTime, Input::KeyboardState* kState, Input::MouseState* mState);
	void CheckPaused(Input::KeyboardState* state, Input::Keys pauseKey);
	void CheckViewportCollision();
	void UpdatePacman(int elapsedTime);
	void UpdateMunchie(int elapsedTime, int munchieIndex);
	void CheckMunchieCollision(int munchieIndex);
	void CheckGhostMovement(int elapsedTime, int ghostIndex);
	void CheckGhostCollision(int ghostIndex);
	void UpdateGhost(int elapsedTime, int ghostIndex);
	bool IsColliding(Vector2* position1, Rect* sourceRect1, Vector2* position2, Rect* sourceRect2);


public:
	/// <summary> Constructs the Pacman class. </summary>
	Pacman(int argc, char* argv[]);

	/// <summary> Destroys any data associated with Pacman class. </summary>
	virtual ~Pacman();

	/// <summary> All content should be loaded in this method. </summary>
	void virtual LoadContent();

	/// <summary> Called every frame - update game logic here. </summary>
	void virtual Update(int elapsedTime);

	/// <summary> Called every frame - draw game here. </summary>
	void virtual Draw(int elapsedTime);
};