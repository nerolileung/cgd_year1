#include "SDL.h"
#include "SDL_image.h"
#include "Commons.h"
#include "Texture2D.h"
#include <iostream>

using namespace std;

Texture2D::Texture2D(SDL_Renderer* renderer) {
	mRenderer = renderer;
}
Texture2D::~Texture2D() {
	Free();
	mRenderer = NULL;
}
bool Texture2D::LoadFromFile(string path) {
	Free();
	// load image
	SDL_Surface* pSurface = IMG_Load(path.c_str()); //file path is char array hence c_str() for converting to string
	if (pSurface != NULL) {
		SDL_SetColorKey(pSurface, SDL_TRUE, SDL_MapRGB(pSurface->format, 0, 0xFF, 0xFF));
		mTexture = SDL_CreateTextureFromSurface(mRenderer, pSurface);
		mWidth = pSurface->w;
		mHeight = pSurface->h;
		if (mTexture == NULL)	cout << "Unable to create texture from surface. Error: " << IMG_GetError() << endl;
	}
	return mTexture != NULL;
}
void Texture2D::Free() {
	if (mTexture != NULL) {
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
	}
}
void Texture2D::Render(SDL_RendererFlip flip, double angle) {
	SDL_Rect renderLocation = { 0,0,mWidth,mHeight }; //texture render location
	SDL_RenderCopyEx(mRenderer, mTexture, NULL, &renderLocation, angle, NULL, flip); //render to screen
}
void Texture2D::Render() {
	SDL_Rect renderLocation = { 0,0,mWidth,mHeight };
	SDL_RenderCopyEx(mRenderer, mTexture, NULL, &renderLocation, 0, NULL, SDL_FLIP_NONE);
}

void Texture2D::Render(Vector2D newPosition, SDL_RendererFlip flip) {
	SDL_Rect renderLocation = { (int)newPosition.x,(int)newPosition.y,mWidth,mHeight };  // cast float to int to prevent complaining
	SDL_RenderCopyEx(mRenderer, mTexture, NULL, &renderLocation, 0, NULL, flip);
}
void Texture2D::Render(SDL_Rect srcRect, SDL_Rect destRect, SDL_RendererFlip flip) {
	SDL_RenderCopyEx(mRenderer, mTexture, &srcRect, &destRect, 0, NULL, flip); //srcRect and dRect params take pointers
}
void Texture2D::Render(SDL_Rect srcRect, SDL_Rect destRect) {
	SDL_RenderCopyEx(mRenderer, mTexture, &srcRect, &destRect, 0, NULL, SDL_FLIP_NONE);
}