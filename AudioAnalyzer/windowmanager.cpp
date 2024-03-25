#include "windowmanager.h"
#include <iostream>

WindowManager::WindowManager() {
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("WinManager", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, winWidth, winHeight, 0);
	if (window == NULL) {
		std::cout << "Failed to create window: " << SDL_GetError() << std::endl;
		return;
	}
	renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		std::cout << "Failed to create renderer: " << SDL_GetError() << std::endl;
		return;
	}

	initialized = true;
}

bool WindowManager::IsInitialized() {
	return initialized;
}

void WindowManager::SetSize(int w, int h) {
	winWidth = w;
	winHeight = h;
}

SDL_Window* WindowManager::GetWindow() {
	return window;
}

SDL_Renderer* WindowManager::GetRenderer() {
	return renderer;
}