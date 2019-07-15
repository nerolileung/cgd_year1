#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "Constants.h"
#include "Commons.h"
#include "Texture2D.h"
#include "GameScreenManager.h"
#include <iostream>

using namespace std;

//globals
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
Texture2D* gTexture = NULL;
GameScreenManager* gameScreenManager = NULL;
Mix_Music* gMusic = NULL;

Uint32 gOldTime; // keeping track of time change

//function prototypes
bool InitSDL();
void CloseSDL();
bool Update();
void Render();
void LoadMusic(string path);

int main(int argc, char*argv[]) {
	if (InitSDL()) { //check if SDL was set up properly before doing things
		gameScreenManager = new GameScreenManager(gRenderer, SCREEN_MENU);
		gOldTime = SDL_GetTicks();
		LoadMusic("Audio/Mario.mp3");
		bool quit = false;
		if (Mix_PlayingMusic() == 0)	Mix_PlayMusic(gMusic, -1);
		//game loop!
		while (!quit) {
			Render();
			quit = Update();
		}
	}
	CloseSDL(); //close window & free resources
	return 0;
}

bool InitSDL() {
	//setup SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) { //returns -1 on failure, 0 on success
		cout << "SDL did not initialise. Error: " << SDL_GetError();
		return false;
	}
	else {
		//attempt to create window
		gWindow = SDL_CreateWindow("Games Engine Creation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL) {
			cout << "Window was not created. Error: " << SDL_GetError();
			return false;
		}
		gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED); //use rendering driver that supports hardware acceleration
		if (gRenderer != NULL) {
			//initialise png loading
			int imageFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imageFlags) & imageFlags)) { //why &
				cout << "SDL_Image initialisation failed. Error: " << IMG_GetError();
				return false;
			}
			gTexture = new Texture2D(gRenderer);
			if (!gTexture->LoadFromFile("Images/BackgroundMB.png")) {
				return false;
			}
			if (gTexture == NULL) return false;
			//initialise mixer
			if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0) {
				cout << "Mixer initialisation failed. Error: " << Mix_GetError();
				return false;
			}
		}
		else {
			cout << "Renderer could not initialise. Error: " << SDL_GetError();
			return false;
		}
		return true;
	}
}

void CloseSDL() {
	//release memory from window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	//release memory from texture and renderer
	delete gTexture;
	gTexture = NULL;
	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;
	//screen manager
	delete gameScreenManager;
	gameScreenManager = NULL;
	Mix_FreeMusic(gMusic);
	gMusic = NULL;
	//quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
	Mix_Quit();
}

bool Update() {
	SDL_Event e; //event handler
	SDL_PollEvent(&e); //poll if events have happened
	Uint32 newTime = SDL_GetTicks();

	switch (e.type) {
	case SDL_QUIT: //window X is clicked
		return true;
		break;
	case SDL_KEYUP: // a key has been pressed!
		switch (e.key.keysym.sym) {
		case SDLK_ESCAPE:
			return true;
			break;
		}
		break;
	}

	gameScreenManager->Update((float)(newTime - gOldTime) / 1000.0f, e);
	gOldTime = newTime;
	return false;
}

void Render() {
	//clear screen
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0x00); // black
	SDL_RenderClear(gRenderer);
	gameScreenManager->Render();
	SDL_RenderPresent(gRenderer); //update screen (present the renderer)
}

void LoadMusic(string path) {
	gMusic = Mix_LoadMUS(path.c_str());
	if (gMusic == NULL) {
		cout << "Failed to load background music. Error: " << Mix_GetError() << endl;
	}
}