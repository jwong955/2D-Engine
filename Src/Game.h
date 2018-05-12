#pragma once


#ifdef __APPLE__
#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#elif _WIN32
#include "SDL.h"
#include "SDL_image.h
#endif

#include <iostream>
#include <vector>

class ColliderComponent;

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	bool running() { return isRunning; }
	void render();
	void clean();

	static void AddTile(int srcX,int srcY, int xpos, int ypos);
	static SDL_Renderer* renderer;
	static SDL_Event event;
	static std::vector<ColliderComponent*> colliders;
	static bool isRunning;
private:
	
	int cnt = 0;
	SDL_Window *window;
};
