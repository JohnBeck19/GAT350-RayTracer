#include <string>
#include <iostream>
#include "Renderer.h"
#include "Color.h"
#include "Random.h"
#include "Canvas.h"
#include "Camera.h"
#include "Scene.h"

int main(int , char**)
{
	std::cout << "Hello World!\n";
	seedRandom((uint32_t)time(nullptr));
	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("Ray Tracer", 400, 300);
	
	Canvas canvas(400, 300, renderer);

	float aspectRatio = canvas.GetSize().x / (float)canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 0, 1 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, 70.0f, aspectRatio);

	Scene scene; // sky color could be set with the top and bottom color
	scene.SetCamera(camera);

	bool quit = false;
	while (!quit)
	{

		canvas.Clear({ 0, 0, 0, 1 });
		scene.Render(canvas);
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