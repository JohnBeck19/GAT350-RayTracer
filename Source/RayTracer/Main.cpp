#include <string>
#include <iostream>
#include "Renderer.h"
#include "Color.h"
#include "Random.h"
#include "Canvas.h"
#include "Camera.h"
#include "Scene.h"
#include "Material.h"
#include "Sphere.h"
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


	Scene scene(20); // sky color could be set with the top and bottom color
	scene.SetCamera(camera);
		

	// create material
	auto lambertian = std::make_shared<Lambertian>(color3_t{ 0, 0, 1 });
	auto metal = std::make_shared<Metal>(color3_t{ 1, 1, 1 }, 0.0f);

	// create objects -> add to scene
	for (int i = 0; i < 10; i++)
	{
		std::shared_ptr<Material> material = (rand()%2) ? std::dynamic_pointer_cast<Material>(lambertian) : std::dynamic_pointer_cast<Material>(metal);
		auto sphere = std::make_unique<Sphere>(randomInUnitSphere(), 0.1, material);
		scene.AddObject(std::move(sphere));
	}

	canvas.Clear({ 0, 0, 0, 1 });
	scene.Render(canvas,50);
	canvas.Update();

	bool quit = false;
	while (!quit)
	{
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