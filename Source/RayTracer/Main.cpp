#include <string>
#include <iostream>
#include "Renderer.h"

int main(int , char**)
{

	std::cout << "Hello World!";

	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("Ray Tracer", 400, 300);

	bool quit = false;
	while (!quit)
	{
		SDL_Event eventa;
		SDL_PollEvent(&eventa);
		switch (eventa.type)
		{
		case SDL_QUIT:
			quit = true;
			break;

		}
	}

	renderer.Shutdown();

	return 0;
}