#include "Pacman.h"
#include <sstream>
#include <time.h>

Pacman::Pacman(int argc, char* argv[]) : Game(argc, argv) { // constructor
	srand(time(NULL)); // seeds rand() with time so that it generates different results each time program is run

	//initialise important values
	_pacman = new Player();
	for (int i = 0; i < MUNCHIECOUNT; i++) {
		_munchies[i] = new Collectable();
	}
	for (int i = 0; i < GHOSTCOUNT; i++) {
		_ghosts[i] = new Enemy();
		_ghosts[i]->speed = 0.1f;
	}
	gameState = GameState::start;
	_pKeyDown = false;
	_pacman->speed = 0.2f;
	_pacman->frameTime = 250;
	_pacman->moving = false;
	_pacman->speedMultiplier = 1.0f;
	_pacman->dead = false;
	_score = 0;
	_shinyMunchieCount = 0;

	//Initialise important Game aspects
	Audio::Initialise();
	Graphics::Initialise(argc, argv, this, 1024, 768, false, 25, 25, "Pacman", 60);
	Input::Initialise();

	// Start the Game Loop - This calls Update and Draw in game loop
	Graphics::StartGameLoop();
}

Pacman::~Pacman() //destructor
{
	delete _pacman->texture;
	delete _pacman->position;
	delete _pacman->sourceRect;
	delete _pacman;

	for (int i = 0; i < MUNCHIECOUNT; i++) {
		delete _munchies[i]->sourceRect;
		delete _munchies[i]->position;
	}
	delete _munchieTexture;
	delete[] _munchies;

	for (int i = 0; i < GHOSTCOUNT; i++) {
		delete _ghosts[i]->sourceRect;
		delete _ghosts[i]->position;
	}
	delete _ghostTexture;
	delete[] _ghosts;

	delete _menuStart;
	delete _menuPause;
	delete _menuGameOver;
	delete _menuWin;
	delete _menuRectangle;

	delete _pop;
}

void Pacman::LoadContent()
{
	// Load Pacman
	_pacman->texture = new Texture2D();
	_pacman->texture->Load("Textures/Pacman.png", false);
	_pacman->position = new Vector2(350.0f, 350.0f); // bottom left corner of pacman
	_pacman->sourceRect = new Rect(0.0f,0.0f, 32, 32);
	_pacman->direction = Direction::right; // use to manipulate source rect
	_pacman->frame = 0;
	_pacman->currentFrameTime = 0;

	// Load Munchie
	_munchieTexture = new Texture2D();
	_munchieTexture->Load("Textures/Cherry.png", true);
	for (int i = 0; i < MUNCHIECOUNT;i++) { // initialise coordinates for horizontal line of munchies at intervals of 32 with margins
		_munchies[i]->sourceRect = new Rect(0.0f, 0.0f, 32, 32);
		_munchies[i]->type = CherryType::regular;
		_munchies[i]->position = new Vector2(12.0f + (64 * i), 450.0f);
		_munchies[i]->currentFrameTime = 0;
		_munchies[i]->frame = rand() % 2;
		_munchies[i]->frameTime = (rand() % 500) + 100;
		_munchies[i]->timesCollected = 0;
	}
	//ghosts
	_ghostTexture = new Texture2D(); //ghosts share a spritesheet, same as munchies
	_ghostTexture->Load("Textures/Ghost.png", true);
	for (int i = 0; i < GHOSTCOUNT; i++) {
		_ghosts[i]->currentFrameTime = 0;
		_ghosts[i]->frame = 0;
		_ghosts[i]->frameTime = 300;
		int typeSeed = rand() % 3;
		switch (typeSeed) {
		case 0:
			_ghosts[i]->type = GhostType::patrolHorizontal;
			_ghosts[i]->sourceRect = new Rect(0.0f, 0.0f, 32, 32);
			_ghosts[i]->direction = Direction::left;
			break;
		case 1:
			_ghosts[i]->type = GhostType::patrolVertical;
			_ghosts[i]->sourceRect = new Rect(64.0f, 0.0f, 32, 32);
			_ghosts[i]->direction = Direction::down;
			break;
		case 2:
			_ghosts[i]->type = GhostType::chase;
			_ghosts[i]->sourceRect = new Rect(128.0f, 0.0f, 32, 32);
			_ghosts[i]->direction = Direction::left;
		}
		bool ghostOverlap = false;
		do {
			_ghosts[i]->position = new Vector2(rand() % (Graphics::GetViewportWidth() - 32), rand() % (Graphics::GetViewportHeight() - 32));
			for (int j = 0; j < MUNCHIECOUNT; j++) { // overlap with munchies
				if (IsColliding(_ghosts[i]->position, _ghosts[i]->sourceRect, _munchies[j]->position, _munchies[j]->sourceRect)) {
					ghostOverlap = true;
				}
			}
			for (int j = 0; j < i - 1; j++) { //overlap with other ghosts
				if (IsColliding(_ghosts[i]->position, _ghosts[i]->sourceRect, &Vector2(_ghosts[j]->position->X + 32, _ghosts[j]->position->Y + 32), _ghosts[j]->sourceRect)) {
					ghostOverlap = true;
				}
			}
		} while (ghostOverlap);
	}

	// set menu params
	_menuStart = new Texture2D();
	_menuPause = new Texture2D();
	_menuGameOver = new Texture2D();
	_menuWin = new Texture2D();
	_menuStart->Load("Textures/screen_start.png", false);
	_menuPause->Load("Textures/screen_pause.png", false);
	_menuGameOver->Load("Textures/screen_gameover.png", false);
	_menuWin->Load("Textures/screen_win.png", false);
	_menuRectangle = new Rect(0.0f, 0.0f, Graphics::GetViewportWidth(), Graphics::GetViewportHeight());
	_menuStringPosition = new Vector2((Graphics::GetViewportWidth()/2.0f)-50.0f,Graphics::GetViewportHeight()/3.0f);

	// Set coordinate string position
	_stringPosition = new Vector2(10.0f, 25.0f);

	//audio
	_pop = new SoundEffect();
	_pop->Load("Sounds/pop.wav");
	_shinyPop = new SoundEffect();
	_shinyPop->Load("Sounds/shinyPop.wav");
}


void Pacman::CheckMovementInput(int elapsedTime, Input::KeyboardState* kState, Input::MouseState* mState) {
	// WASD movement and sprite direction
	float pacmanSpeed = _pacman->speed * elapsedTime * _pacman->speedMultiplier;

	// release key to stop moving, only change direction from standstill, only move if direction matches; this prevents diagonals without creating hierarchy of directions
	if (_pacman->moving) {
		switch (_pacman->direction) {
		case Direction::right:
			if (kState->IsKeyUp(Input::Keys::D))	_pacman->moving = false;
			else _pacman->position->X += pacmanSpeed;
			break;
		case Direction::down:
			if (kState->IsKeyUp(Input::Keys::S))	_pacman->moving = false;
			else _pacman->position->Y += pacmanSpeed;
			break;
		case Direction::left:
			if (kState->IsKeyUp(Input::Keys::A))	_pacman->moving = false;
			else _pacman->position->X -= pacmanSpeed;
			break;
		case Direction::up:
			if (kState->IsKeyUp(Input::Keys::W))	_pacman->moving = false;
			else _pacman->position->Y -= pacmanSpeed;
			break;
		default:
			_pacman->direction = Direction::right;
			break;
		}
	}
	else {
		if (kState->IsKeyDown(Input::Keys::D)) {
			_pacman->position->X += pacmanSpeed;
			_pacman->direction = Direction::right;
			_pacman->moving = true;
		}
		if (kState->IsKeyDown(Input::Keys::A)) {
			_pacman->position->X -= pacmanSpeed;
			_pacman->direction = Direction::left;
			_pacman->moving = true;
		}
		if (kState->IsKeyDown(Input::Keys::W)) {
			_pacman->position->Y -= pacmanSpeed;
			_pacman->direction = Direction::up;
			_pacman->moving = true;
		}
		if (kState->IsKeyDown(Input::Keys::S)) {
			_pacman->position->Y += pacmanSpeed;
			_pacman->direction = Direction::down;
			_pacman->moving = true;
		}
	}
	//sprint!
	if (kState->IsKeyDown(Input::Keys::LEFTSHIFT)) {
		_pacman->speedMultiplier = 2.0f;
	}
	else {
		_pacman->speedMultiplier = 1.0f;
	}
	//mouse movement
	if (mState->LeftButton == Input::ButtonState::PRESSED) {
		if (_pacman->position->X > mState->X) _pacman->direction = Direction::left;
		else if (_pacman->position->Y > mState->Y) _pacman->direction = Direction::up;
		else if (_pacman->position->X < mState->X) _pacman->direction = Direction::right;
		else if (_pacman->position->Y < mState->Y) _pacman->direction = Direction::down;
		// collision detection to prevent diagonal movement
		switch (_pacman->direction) {
		case Direction::left:
			if (_pacman->position->X - pacmanSpeed < mState->X) {
				_pacman->position->X = mState->X;
			}
			else { _pacman->position->X -= pacmanSpeed; }
			break;
		case Direction::right:
			if (_pacman->position->X + pacmanSpeed > mState->X) {
				_pacman->position->X = mState->X;
			}
			else { _pacman->position->X += pacmanSpeed; }
			break;
		case Direction::up:
			if (_pacman->position->Y - pacmanSpeed < mState->Y) {
				_pacman->position->Y = mState->Y;
			}
			else { _pacman->position->Y -= pacmanSpeed; }
			break;
		case Direction::down:
			if (_pacman->position->Y + pacmanSpeed > mState->Y) {
				_pacman->position->Y = mState->Y;
			}
			else { _pacman->position->Y += pacmanSpeed; }
			break;
		}
	}
}

void Pacman::CheckPaused(Input::KeyboardState* state, Input::Keys pauseKey) {
	if (state->IsKeyDown(pauseKey) && !_pKeyDown) {
		_pKeyDown = true;
		if (gameState == GameState::pause)	gameState = GameState::running;
		else gameState = GameState::pause;
	}
	if (state->IsKeyUp(pauseKey))	_pKeyDown = false;
}

void Pacman::CheckViewportCollision() {
	// wall collision and wrapping. position is bottom left corner of pacman
	if ((_pacman->position->X + _pacman->sourceRect->Width) > Graphics::GetViewportWidth()) { // check if pacman exceeds right wall
		_pacman->position->X = 0.0f;
	}
	if ((_pacman->position->X) < 0) { // left wall
		_pacman->position->X = Graphics::GetViewportWidth() - _pacman->sourceRect->Width; // window size is float, pacman size is int, possible concern?
	}
	if ((_pacman->position->Y) > Graphics::GetViewportHeight() - _pacman->sourceRect->Height) { // bottom
		_pacman->position->Y = 0.0f;
	}
	if ((_pacman->position->Y) < 0) { // top
		_pacman->position->Y = Graphics::GetViewportHeight() - _pacman->sourceRect->Height;
	}
}

bool Pacman::IsColliding(Vector2* position1, Rect* sourceRect1, Vector2* position2, Rect* sourceRect2) {
	bool xTouch = true;
	bool yTouch = true;
	if ((position1->X + sourceRect1->Width < position2->X) || (position1->X > position2->X + sourceRect2->Width)) { //entity 1 is left or right of entity 2
		xTouch = false;
	}
	if ((position1->Y + sourceRect1->Height < position2->Y) || (position1->Y > position2->Y + sourceRect2->Height)) { //entity 1 is above or below of entity 2
		yTouch = false;
	}
	if (xTouch&&yTouch)	return true;
	else return false;
}

void Pacman::CheckMunchieCollision(int munchieIndex){ // if pacman runs into a munchie, randomise its position
	if (IsColliding(_pacman->position,_pacman->sourceRect, _munchies[munchieIndex]->position, _munchies[munchieIndex]->sourceRect)) {
		bool overlap = false;
		switch (_munchies[munchieIndex]->type) {
		case CherryType::shiny: // move off screen
			_munchies[munchieIndex]->position->X = -500;
			_munchies[munchieIndex]->position->Y = -500;
			_score += 10;
			_shinyMunchieCount++;
			Audio::Play(_shinyPop);
			if (_shinyMunchieCount == MUNCHIECOUNT) { // win when final shiny munchie has been collected
				gameState = GameState::win;
				_pacman->dead = true; //use to determine if resetting is needed
			}
			break;
		case CherryType::slimed:
			_munchies[munchieIndex]->type = CherryType::regular;
			_score -= 2;//cumulative total with base +5 makes effective +3 to score
		default:
			Audio::Play(_pop);
			if (_munchies[munchieIndex]->timesCollected > 2) {
				_munchies[munchieIndex]->type = CherryType::shiny;
			}
			do {
				overlap = false;
				int randX = rand() % (Graphics::GetViewportWidth() - _munchies[munchieIndex]->sourceRect->Width);
				int randY = rand() % (Graphics::GetViewportHeight() - _munchies[munchieIndex]->sourceRect->Height);
				_munchies[munchieIndex]->position->X = randX;
				_munchies[munchieIndex]->position->Y = randY;
				for (int i = 0; i < MUNCHIECOUNT; i++) {
					if (i == munchieIndex)	continue;
					if (IsColliding(_munchies[i]->position, _munchies[i]->sourceRect, _munchies[munchieIndex]->position, _munchies[munchieIndex]->sourceRect)) {
						overlap = true;
					}
				}
			} while (overlap);
			_munchies[munchieIndex]->timesCollected++;
			_score += 5;
			break;
		}
	}
}

void Pacman::CheckGhostCollision(int ghostIndex) {
	if (IsColliding(_pacman->position, _pacman->sourceRect, _ghosts[ghostIndex]->position,_ghosts[ghostIndex]->sourceRect)) {
		_pacman->dead = true;
		gameState = GameState::gameOver;
	}
	for (int i = 0; i < MUNCHIECOUNT; i++) {
		if (IsColliding(_ghosts[ghostIndex]->position, _ghosts[ghostIndex]->sourceRect, _munchies[i]->position, _munchies[i]->sourceRect)) {
			if (_munchies[i]->type == CherryType::regular) _munchies[i]->type = slimed;
		}
	}
}

void Pacman::CheckGhostMovement(int elapsedTime, int ghostIndex) {
	int ghostSpeed = _ghosts[ghostIndex]->speed * elapsedTime;

	switch (_ghosts[ghostIndex]->type) {
	case GhostType::patrolHorizontal:
		if (_ghosts[ghostIndex]->direction == Direction::right) { // only moves left and right
			_ghosts[ghostIndex]->position->X += ghostSpeed;
		}
		else if (_ghosts[ghostIndex]->direction == Direction::left) {
			_ghosts[ghostIndex]->position->X -= ghostSpeed;
		}
		// ghosts change direction when they hit an edge
		if (_ghosts[ghostIndex]->position->X + _ghosts[ghostIndex]->sourceRect->Width >= Graphics::GetViewportWidth()) { // right edge
			_ghosts[ghostIndex]->direction = Direction::left;
		}
		else if (_ghosts[ghostIndex]->position->X <= 0) {// left edge
			_ghosts[ghostIndex]->direction = Direction::right;
		}
		break;
	case GhostType::patrolVertical:
		if (_ghosts[ghostIndex]->direction == Direction::down) {
			_ghosts[ghostIndex]->position->Y += ghostSpeed;
		}
		else if (_ghosts[ghostIndex]->direction == Direction::up) {
			_ghosts[ghostIndex]->position->Y -= ghostSpeed;
		}
		// ghosts change direction when they hit an edge
		if (_ghosts[ghostIndex]->position->Y + _ghosts[ghostIndex]->sourceRect->Height >= Graphics::GetViewportHeight()) { // bottom edge
			_ghosts[ghostIndex]->direction = Direction::up;
		}
		else if (_ghosts[ghostIndex]->position->Y <= 0) {// upper edge
			_ghosts[ghostIndex]->direction = Direction::down;
		}
		break;
	case GhostType::chase: // similar logic to pacman following mouse; still a little bit of teleporting when ghosts collide
		if (_ghosts[ghostIndex]->position->X > _pacman->position->X) _ghosts[ghostIndex]->direction = Direction::left;
		else if (_ghosts[ghostIndex]->position->Y > _pacman->position->Y) _ghosts[ghostIndex]->direction = Direction::up;
		else if (_ghosts[ghostIndex]->position->X < _pacman->position->X) _ghosts[ghostIndex]->direction = Direction::right;
		else if (_ghosts[ghostIndex]->position->Y < _pacman->position->Y) _ghosts[ghostIndex]->direction = Direction::down;
		// limit ghost movement: no diagonals, no colliding with other ghosts, no going offscreen
		bool collide = false;
		int colGhostIndex = ghostIndex;
		switch (_ghosts[ghostIndex]->direction) {
		case Direction::left:
			for (int i = 0; i < GHOSTCOUNT; i++) {
				if (ghostIndex == i) continue;
				if (IsColliding(&Vector2(_ghosts[ghostIndex]->position->X - ghostSpeed, _ghosts[ghostIndex]->position->Y), _ghosts[ghostIndex]->sourceRect, _ghosts[i]->position, _ghosts[i]->sourceRect)) {
					collide = true;
					colGhostIndex = i;
				}
			}
			if (_ghosts[ghostIndex]->position->X - ghostSpeed < 0) {
				_ghosts[ghostIndex]->position->X = 0;
			}
			else if (collide){
				_ghosts[ghostIndex]->position->X = _ghosts[colGhostIndex]->position->X + _ghosts[colGhostIndex]->sourceRect->Width;
			}
			else if (_ghosts[ghostIndex]->position->X - ghostSpeed < _pacman->position->X) {
				_ghosts[ghostIndex]->position->X = _pacman->position->X;
			}
			else { _ghosts[ghostIndex]->position->X -= ghostSpeed; }
			break;
		case Direction::right:
			for (int i = 0; i < GHOSTCOUNT; i++) {
				if (ghostIndex == i) continue;
				if (IsColliding(&Vector2(_ghosts[ghostIndex]->position->X + ghostSpeed, _ghosts[ghostIndex]->position->Y), _ghosts[ghostIndex]->sourceRect, _ghosts[i]->position, _ghosts[i]->sourceRect)) {
					collide = true;
					colGhostIndex = i;
				}
			}
			if (_ghosts[ghostIndex]->position->X + ghostSpeed > Graphics::GetViewportWidth()) {
				_ghosts[ghostIndex]->position->X = Graphics::GetViewportWidth() - _ghosts[ghostIndex]->sourceRect->Width;
			}
			else if (collide) {
				_ghosts[ghostIndex]->position->X = _ghosts[colGhostIndex]->position->X - _ghosts[ghostIndex]->sourceRect->Width;
			}
			else if (_ghosts[ghostIndex]->position->X + ghostSpeed > _pacman->position->X) {
				_ghosts[ghostIndex]->position->X = _pacman->position->X;
			}
			else { _ghosts[ghostIndex]->position->X += ghostSpeed; }
			break;
		case Direction::up:
			for (int i = 0; i < GHOSTCOUNT; i++) {
				if (ghostIndex == i) continue;
				if (IsColliding(&Vector2(_ghosts[ghostIndex]->position->X, _ghosts[ghostIndex]->position->Y - ghostSpeed), _ghosts[ghostIndex]->sourceRect, _ghosts[i]->position, _ghosts[i]->sourceRect)) {
					collide = true;
					colGhostIndex = i;
				}
			}
			if (_ghosts[ghostIndex]->position->Y - ghostSpeed < 0) {
				_ghosts[ghostIndex]->position->Y = 0;
			}
			else if (collide) {
				_ghosts[ghostIndex]->position->Y = _ghosts[colGhostIndex]->position->Y + _ghosts[colGhostIndex]->sourceRect->Height;
			}
			else if (_ghosts[ghostIndex]->position->Y - ghostSpeed < _pacman->position->Y) {
				_ghosts[ghostIndex]->position->Y = _pacman->position->Y;
			}
			else { _ghosts[ghostIndex]->position->Y -= ghostSpeed; }
			break;
		case Direction::down:
			for (int i = 0; i < GHOSTCOUNT; i++) {
				if (ghostIndex == i) continue;
				if (IsColliding(&Vector2(_ghosts[ghostIndex]->position->X, _ghosts[ghostIndex]->position->Y + ghostSpeed), _ghosts[ghostIndex]->sourceRect, _ghosts[i]->position, _ghosts[i]->sourceRect)) {
					collide = true;
					colGhostIndex = i;
				}
			}
			if (_ghosts[ghostIndex]->position->Y + ghostSpeed > Graphics::GetViewportHeight()) {
				_ghosts[ghostIndex]->position->Y = Graphics::GetViewportHeight() - _ghosts[ghostIndex]->sourceRect->Height;
			}
			else if (collide) {
				_ghosts[ghostIndex]->position->Y = _ghosts[colGhostIndex]->position->Y - _ghosts[ghostIndex]->sourceRect->Height;
			}
			else if (_ghosts[ghostIndex]->position->Y + ghostSpeed > _pacman->position->Y) {
				_ghosts[ghostIndex]->position->Y = _pacman->position->Y;
			}
			else { _ghosts[ghostIndex]->position->Y += ghostSpeed; }
			break;
		}
	}
}

void Pacman::Update(int elapsedTime)
{
	// Gets the current state of the keyboard
	Input::KeyboardState* keyboardState = Input::Keyboard::GetState();
	Input::MouseState* mouseState = Input::Mouse::GetState();

	switch (gameState) {
	case GameState::pause:
	case GameState::running:
		CheckPaused(keyboardState, Input::Keys::P);
		if (gameState == GameState::pause)	break;
			CheckMovementInput(elapsedTime, keyboardState, mouseState);
			CheckViewportCollision();
			for (int i = 0; i < GHOSTCOUNT; i++) {
				CheckGhostCollision(i);
				CheckGhostMovement(elapsedTime,i);
				UpdateGhost(elapsedTime, i);
			}
			for (int i = 0; i < MUNCHIECOUNT; i++) {
				CheckMunchieCollision(i);
				UpdateMunchie(elapsedTime, i);
			}
			//only continue when not paused
			UpdatePacman(elapsedTime);
		break;
	case GameState::start:
	case GameState::win:
	case GameState::gameOver:
		if (keyboardState->IsKeyDown(Input::Keys::SPACE)) {
			gameState = GameState::running;
			if (_pacman->dead) {
				_score = 0;
				_shinyMunchieCount = 0;
				_pacman->dead = false;
				for (int i = 0; i < GHOSTCOUNT; i++) {
					int typeSeed = rand() % 3;
					switch (typeSeed) {
					case 0:
						_ghosts[i]->type = GhostType::patrolHorizontal;
						_ghosts[i]->sourceRect = new Rect(0.0f, 0.0f, 32, 32);
						_ghosts[i]->direction = Direction::left;
					break;
					case 1:
						_ghosts[i]->type = GhostType::patrolVertical;
						_ghosts[i]->sourceRect = new Rect(64.0f, 0.0f, 32, 32);
						_ghosts[i]->direction = Direction::down;
						break;
					case 2:
						_ghosts[i]->type = GhostType::chase;
						_ghosts[i]->sourceRect = new Rect(128.0f, 0.0f, 32, 32);
						_ghosts[i]->direction = Direction::left;
					}
				}
			}
			//load in positions of munchies, then ghosts, then pacman
			for (int i = 0; i < MUNCHIECOUNT; i++) {
				_munchies[i]->timesCollected = 0;
				_munchies[i]->type = CherryType::regular;
				bool munchieOverlap = false;
				do {
					munchieOverlap = false;
					_munchies[i]->position->X = rand() % (Graphics::GetViewportWidth() - _munchies[i]->sourceRect->Width);;
					_munchies[i]->position->Y = rand() % (Graphics::GetViewportHeight() - _munchies[i]->sourceRect->Height);;
					for (int j = 0; j <	MUNCHIECOUNT; j++) { // check if current munchie would overlap with other munchies
						if (i == j) continue;
						if (IsColliding(_munchies[i]->position, _munchies[i]->sourceRect, _munchies[j]->position, _munchies[j]->sourceRect)) {
							munchieOverlap = true;
						}
					}
				} while (munchieOverlap);
			}
			for (int i = 0; i < GHOSTCOUNT; i++) {
				bool ghostOverlap = false;
				do {
					ghostOverlap = false;
					_ghosts[i]->position = new Vector2(rand() % (Graphics::GetViewportWidth() - 32), rand() % (Graphics::GetViewportHeight() - 32));
					for (int j = 0; j < MUNCHIECOUNT; j++) { // overlap with munchies
						if (IsColliding(_ghosts[i]->position, _ghosts[i]->sourceRect, _munchies[j]->position, _munchies[j]->sourceRect)) {
							ghostOverlap = true;
						}
					}
					for (int j = 0; j < GHOSTCOUNT; j++) { //overlap with other ghosts
						if (i == j) continue;
						if (IsColliding(_ghosts[i]->position, _ghosts[i]->sourceRect, &Vector2(_ghosts[j]->position->X + 32, _ghosts[j]->position->Y + 32), _ghosts[j]->sourceRect)) {
							ghostOverlap = true;
						}
					}
				} while (ghostOverlap);
			}
			bool pacmanGhostOverlap = false;
			do { //prevent spawning on a ghost and getting stuck in a death loop
				_pacman->position->X = rand() % (Graphics::GetViewportWidth() - 32);
				_pacman->position->Y = rand() % (Graphics::GetViewportHeight() - 32);
				for (int i = 0; i < GHOSTCOUNT; i++) {
					if (IsColliding(_ghosts[i]->position, _ghosts[i]->sourceRect, _pacman->position, _pacman->sourceRect)) {
						pacmanGhostOverlap = true;
					}
				}
			} while (pacmanGhostOverlap);
		}
		break;
	}
}

void Pacman::UpdatePacman(int elapsedTime) {
	_pacman->sourceRect->Y = _pacman->sourceRect->Height * _pacman->direction;
	if (_pacman->speedMultiplier == 1.0f) _pacman->sourceRect->X = _pacman->sourceRect->Width * _pacman->frame; // not sprinting
	else _pacman->sourceRect->X = _pacman->sourceRect->Width * (_pacman->frame + 2);
	
	_pacman->currentFrameTime += elapsedTime;
}

void Pacman::UpdateMunchie(int elapsedTime, int munchieIndex) {
	//spritesheet manipulation
	_munchies[munchieIndex]->sourceRect->X = _munchies[munchieIndex]->sourceRect->Width * _munchies[munchieIndex]->frame;
	_munchies[munchieIndex]->currentFrameTime += elapsedTime;
	_munchies[munchieIndex]->sourceRect->Y = _munchies[munchieIndex]->type * _munchies[munchieIndex]->sourceRect->Height;
}

void Pacman::UpdateGhost(int elapsedTime, int ghostIndex) {
	_ghosts[ghostIndex]->sourceRect->Y = _ghosts[ghostIndex]->sourceRect->Height * _ghosts[ghostIndex]->direction;
	_ghosts[ghostIndex]->sourceRect->X = _ghosts[ghostIndex]->sourceRect->Width * (_ghosts[ghostIndex]->frame + (_ghosts[ghostIndex]->type*2));
	_ghosts[ghostIndex]->currentFrameTime += elapsedTime;
}

void Pacman::Draw(int elapsedTime)
{
	// Allows us to easily create a string
	std::stringstream stream;
	stream << "Score: " << _score;

	SpriteBatch::BeginDraw(); // Starts Drawing
	std::stringstream menuStream;
	switch (gameState) {
	case GameState::start:
		SpriteBatch::Draw(_menuStart, _menuRectangle, nullptr);
		break;
	case GameState::gameOver:
		SpriteBatch::Draw(_menuGameOver, _menuRectangle, nullptr);
		break;
	case GameState::win:
		SpriteBatch::Draw(_menuWin, _menuRectangle, nullptr);
		menuStream << "FINAL SCORE: " << _score;
		SpriteBatch::DrawString(menuStream.str().c_str(), new Vector2(Graphics::GetViewportWidth()/3,Graphics::GetViewportHeight()/3), Color::Yellow);
		break;
	case GameState::pause:
		SpriteBatch::Draw(_menuPause, _menuRectangle, nullptr);
		break;
	case GameState::running:
		//draw pacman
		if (_pacman->currentFrameTime > _pacman->frameTime) {
			_pacman->frame++;
			if (_pacman->frame >= 2)	_pacman->frame = 0;
			_pacman->currentFrameTime = 0;
		}
		SpriteBatch::Draw(_pacman->texture, _pacman->position, _pacman->sourceRect);
		// munchies
		for (int i = 0; i < MUNCHIECOUNT; i++) {
			if (_munchies[i]->currentFrameTime > _munchies[i]->frameTime) {
				_munchies[i]->frame++;
				if (_munchies[i]->frame >= 2) {
					_munchies[i]->frame = 0;
				}
				_munchies[i]->currentFrameTime = 0;
			}

			SpriteBatch::Draw(_munchieTexture, new Rect(_munchies[i]->position->X, _munchies[i]->position->Y, 32, 32), _munchies[i]->sourceRect, Vector2::Zero, 1.0f, 0.0f, Color::White, SpriteEffect::NONE);
		}

		for (int i = 0; i < GHOSTCOUNT; i++) {
			if (_ghosts[i]->currentFrameTime > _ghosts[i]->frameTime) {
				_ghosts[i]->frame++;
				if (_ghosts[i]->frame >= 2)	_ghosts[i]->frame = 0;
				_ghosts[i]->currentFrameTime = 0;
			}
			SpriteBatch::Draw(_ghostTexture, _ghosts[i]->position, _ghosts[i]->sourceRect, Vector2::Zero, 1.0f, 0.0f, Color::White, SpriteEffect::NONE);
		}

		// Draws position String
		SpriteBatch::DrawString(stream.str().c_str(), _stringPosition, Color::Yellow);
		break;
	}
	SpriteBatch::EndDraw(); // Ends Drawing
}

