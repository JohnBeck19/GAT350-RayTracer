#include <string>
#include <iostream>
#include "glm/gtx/color_space.hpp"
#include "Renderer.h"
#include "Color.h"
#include "Random.h"
#include "Canvas.h"
#include "Camera.h"
#include "Scene.h"
#include "Material.h"
#include "Sphere.h"
#include "Plane.h"
#include "Triangle.h"
#include "Mesh.h"
void InitScene01(Scene& scene, const Canvas& canvas);
void InitScene02(Scene& scene, const Canvas& canvas);
void InitScene03(Scene& scene, const Canvas& canvas);
int main(int , char**)
{
	const int width = 400;
	const int height = 300;
	const int samples = 500;
	const int depth = 8;


	std::cout << "Hello World!\n";
	seedRandom((uint32_t)time(nullptr));
	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("Ray Tracer", width, height);
	
	Canvas canvas(width, height, renderer);
	Scene scene(glm::vec3{ 1.0f }, glm::vec3{ 0.5f, 0.7f, 1.0f });

	InitScene02(scene, canvas);

	canvas.Clear({ 0, 0, 0, 1 });
	scene.Render(canvas,samples,depth);
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

void InitScene01(Scene& scene, const Canvas& canvas)
{
	float aspectRatio = canvas.GetSize().x / canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 2, 10 }, glm::vec3{ 0, 1, 0 }, glm::vec3{ 0, 1, 0 }, 20.0f, aspectRatio);
	scene.SetCamera(camera);

	// create objects -> add to scene
	for (int x = -2; x < 2; x++)
	{
		for (int z = -2; z < 2; z++)
		{
			std::shared_ptr<Material> material;

			// create random material
			float r = random01();
			if (r < 0.3f)		material = std::make_shared<Lambertian>(glm::rgbColor(glm::vec3{ random(0, 360), 1.0f, 1.0f }));
			else if (r < 0.6f)	material = std::make_shared<Metal>(color3_t{ random(0.5f, 1.0f) }, random(0, 0.5f));
			else if (r < 0.9f)	material = std::make_shared<Dielectric>(color3_t{ 1.0f }, random(1.1f, 2));
			else				material = std::make_shared<Emissive>(glm::rgbColor(glm::vec3{ random(0, 360), 1.0f, 1.0f }), 5.0f);

			// set random sphere radius
			float radius = random(0.2f, 0.3f);
			// create sphere using random radius and material
			auto sphere = std::make_unique<Sphere>(glm::vec3{ x + random(-0.5f, 0.5f), radius, z + random(-0.5f, 0.5f) }, radius, material);
			// add sphere to the scene
			scene.AddObject(std::move(sphere));
		}
	}

	auto plane = std::make_unique<Plane>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, std::make_shared<Lambertian>(color3_t{ 0.2f }));
	scene.AddObject(std::move(plane));
}

void InitScene02(Scene& scene, const Canvas& canvas)
{
	float aspectRatio = canvas.GetSize().x / canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 2, 10 }, glm::vec3{ 0, 1, 0 }, glm::vec3{ 0, 1, 0 }, 45.0f, aspectRatio);
	scene.SetCamera(camera);
	auto plane = std::make_unique<Plane>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, std::make_shared<Lambertian>(color3_t{ 0.2f }));
	scene.AddObject(std::move(plane));


	auto triangle = std::make_unique<Triangle>(glm::vec3{ -3, 0, 4 }, glm::vec3{ -3, 0, 0 }, glm::vec3{ -0.25f, 3.5, 0.25f }, std::make_shared<Metal>(color3_t{ 1, 1, 1 },random(0,0.5f)));
	scene.AddObject(std::move(triangle));

	auto sphere = std::make_unique<Sphere>(glm::vec3{ -1.75f,.5f,2 }, 0.5f, std::make_shared<Dielectric>(glm::vec3{ 1.0f,1.0f,1.0f }, 0.5f));
	scene.AddObject(std::move(sphere));
	auto mesh = std::make_unique<Mesh>(std::make_shared<Lambertian>(color3_t{ 0, 0, 1 }));
	mesh->Load("models/Cube.obj", glm::vec3{ 0, 0.5f, 0 }, glm::vec3{ 0, 45, 0 });
	scene.AddObject(std::move(mesh));
	mesh = std::make_unique<Mesh>(std::make_shared<Lambertian>(color3_t{ 1, 0, 0}));
	mesh->Load("models/Cube.obj", glm::vec3{ -1.0f, 0.5f, 0.5f }, glm::vec3{ 0, 45, 0 });
	scene.AddObject(std::move(mesh));

	mesh = std::make_unique<Mesh>(std::make_shared<Lambertian>(color3_t{ 0, 1, 0 }));
	mesh->Load("models/Cube.obj", glm::vec3{ 1.0f, 0.5f, 0.5f }, glm::vec3{ 0, 45, 0 });
	scene.AddObject(std::move(mesh));

	mesh = std::make_unique<Mesh>(std::make_shared<Lambertian>(color3_t{ 1, 0, 1 }));
	mesh->Load("models/Cube.obj", glm::vec3{ -0.75f, 1.5f, 0.25f }, glm::vec3{ 0, 45, 0 });
	scene.AddObject(std::move(mesh));

	mesh = std::make_unique<Mesh>(std::make_shared<Lambertian>(color3_t{ 1, 1, 0 }));
	mesh->Load("models/Cube.obj", glm::vec3{ .75f, 1.5f, 0.25f }, glm::vec3{ 0, 45, 0 });
	scene.AddObject(std::move(mesh));

	mesh = std::make_unique<Mesh>(std::make_shared<Dielectric>(glm::vec3{ 1.0f,0.0f,1.0f }, 0.2f));
	mesh->Load("models/quad.obj", glm::vec3{ 4.0f, 1.5f, -2.0f }, glm::vec3{ 0, -45, 0 }, glm::vec3{5.0f,5.0f,5.0f});
	scene.AddObject(std::move(mesh));

	mesh = std::make_unique<Mesh>(std::make_shared<Emissive>(color3_t{ 1.0f, 1.0f, 1.0f }, 4.0f));
	mesh->Load("models/Cube.obj", glm::vec3{ 0.0f, 2.5f, 0.0f }, glm::vec3{ 0, 45, 0 });
	scene.AddObject(std::move(mesh));


	for (int x = -5; x < 5; x++)
	{
		for (int z = 3; z < 8; z++)
		{
			std::shared_ptr<Material> material;

			// create random material
			float r = random01();
			if (r < 0.3f)		material = std::make_shared<Lambertian>(glm::rgbColor(glm::vec3{ random(0, 360), 1.0f, 1.0f }));
			else if (r < 0.6f)	material = std::make_shared<Metal>(color3_t{ random(0.5f, 1.0f) }, random(0, 0.5f));
			else if (r < 0.9f)	material = std::make_shared<Dielectric>(color3_t{ 1.0f }, random(1.1f, 2));
			else				material = std::make_shared<Emissive>(glm::rgbColor(glm::vec3{ random(0, 360), 1.0f, 1.0f }), 5.0f);

			// set random sphere radius
			float radius = random(0.2f, 0.3f);
			// create sphere using random radius and material
			auto sphere = std::make_unique<Sphere>(glm::vec3{ x + random(-0.5f, 0.5f), radius, z + random(-0.5f, 0.5f) }, radius, material);
			// add sphere to the scene
			scene.AddObject(std::move(sphere));
		}
	}
}




void InitScene03(Scene& scene, const Canvas& canvas)
{
	float aspectRatio = canvas.GetSize().x / canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 2, 11 }, glm::vec3{ 0, 1, 0 }, glm::vec3{ 0, 1, 0 }, 35.0f, aspectRatio);
	scene.SetCamera(camera);

	std::shared_ptr<Material> material;

	auto plane = std::make_unique<Plane>(glm::vec3{ 0, -1.0f, 0 }, glm::vec3{ 0, 1, 0 }, std::make_shared<Lambertian>(color3_t{ 0.8f }));
	scene.AddObject(std::move(plane));

	plane = std::make_unique<Plane>(glm::vec3{ 0, 4.0f, 0 }, glm::vec3{ 0, 1, 0 }, std::make_shared<Lambertian>(color3_t{ 0.8f }));
	scene.AddObject(std::move(plane));

	//light
	material = std::make_shared<Emissive>(color3_t{ 1.0f, 1.0f, 1.0f }, 4.0f);
	auto mesh = std::make_unique<Mesh>(material);
	mesh->Load("models/cube.obj", glm::vec3{ 0.0f, 4.0f, -2.0f }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 2.0f, 1.0f, 2.0f });
	scene.AddObject(std::move(mesh));

	//sphere
	
	material = std::make_shared<Lambertian>(color3_t{ 1.0f, 1.0f, 1.0f });
	auto sphere = std::make_unique<Sphere>(glm::vec3{ -2.0f, 0.25f, -2.0f  }, 1.25f, material);
	scene.AddObject(std::move(sphere));
	//cube
	mesh = std::make_unique<Mesh>(material);
	mesh->Load("models/cube.obj", glm::vec3{ 2.0f, 0.0f, -1.0f }, glm::vec3{ 0, 45, 0 }, glm::vec3{ 2.0f, 2.0f, 2.0f });
	scene.AddObject(std::move(mesh));

	//back wall
	material = std::make_shared<Lambertian>(color3_t{ 0.8f, 0.8f, 0.8f });
	mesh = std::make_unique<Mesh>(material);
	mesh->Load("models/quad.obj", glm::vec3{ 0.0f, 0.0f, -6.0f }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 12.0f, 12.0f, 0.5f });
	scene.AddObject(std::move(mesh));

	//right wall
	material = std::make_shared<Lambertian>(color3_t{ 0, 1.0f, 0 });
	mesh = std::make_unique<Mesh>(material);
	mesh->Load("models/quad.obj", glm::vec3{ 4.0f, 0.0f, 0.0f }, glm::vec3{0, -90, 0 }, glm::vec3{11.99f, 12.0f, 0.5f });
	scene.AddObject(std::move(mesh));

	//left wall
	material = std::make_shared<Lambertian>(color3_t{ 1.0f, 0, 0 });
	mesh = std::make_unique<Mesh>(material);
	mesh->Load("models/quad.obj", glm::vec3{ -4.0f, 0.0f, 0.0f }, glm::vec3{ 180, 270, 0 }, glm::vec3{ 11.99f, 12.0f, 0.5f });
	scene.AddObject(std::move(mesh));

}

