#include <iostream>
#include "Window.h"

const uint16_t SCREEN_WIDTH = 640;
const uint16_t SCREEN_HEIGHT = 480;

int main(int argc, char* args[])
{
	Window w(SCREEN_WIDTH, SCREEN_HEIGHT);

	if (!w.LoadAssets())
	{
		return 2;
	}

	w.Loop();
	
	w.Close();
	return 0;
}
