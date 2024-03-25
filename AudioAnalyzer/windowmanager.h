#ifndef _WINMANAGER_
#define _WINMANAGER_
#include <SDL.h>

class WindowManager {
public:
	WindowManager();
	void SetSize(int w, int h);
	bool IsInitialized();
	SDL_Window* GetWindow();
	SDL_Renderer* GetRenderer();
private:
	bool initialized = false;

	int winX = 0;
	int winY = 0;
	int winWidth = 600;
	int winHeight = 400;

	SDL_Window *window;
	SDL_Renderer *renderer;
};

#endif