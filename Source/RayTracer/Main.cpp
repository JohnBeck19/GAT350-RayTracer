#include <string>
#include <iostream>
#include "Renderer.h"
#include "Color.h"
#include "Random.h"
#include "Canvas.h"

int main(int , char**)
{
	std::cout << "Hello World!\n";
	seedRandom((uint32_t)time(nullptr));
	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("Ray Tracer", 400, 300);
	
	Canvas canvas(400, 300, renderer);

	bool quit = false;
	while (!quit)
	{

		for (int i = 0; i < 1000; i++) canvas.DrawPoint({random01()*400,random01()*300}, { random01(),random01(),random01(), 1 });
		canvas.Update();

		renderer.PresentCanvas(canvas);

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