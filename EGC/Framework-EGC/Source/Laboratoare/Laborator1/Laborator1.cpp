#include "Laborator1.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>

using namespace std;

// Order of function calling can be seen in "Source/Core/World.cpp::LoopUpdate()"
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/World.cpp

Laborator1::Laborator1()
{
}

Laborator1::~Laborator1()
{
}

void Laborator1::Init()
{
	// Load a mesh from file into GPU memory
	{
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	
	// Load sphere from file into GPU memory
	{
		Mesh* mesh = new Mesh("sphere");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	// Load teapot from file into GPU memory
	{
		Mesh* mesh = new Mesh("teapot");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "teapot.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	names = { "box", "sphere", "teapot" };
}

void Laborator1::FrameStart()
{

}

void Laborator1::Update(float deltaTimeSeconds)
{
	glm::ivec2 resolution = window->props.resolution;

	// sets the clear color for the color buffer
	glClearColor(bgColor.x, bgColor.y, bgColor.z, 1);

	// clears the color buffer (using the previously set color) and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);

	// render the object
	RenderMesh(meshes["box"], glm::vec3(1, 0.5f, 0), glm::vec3(0.5f));

	// render the object again but with different properties
	RenderMesh(meshes["box"], glm::vec3(pos.x + 5, pos.y, pos.z), glm::vec3(0.5f));

	// render shape object
	// RenderMesh(meshes["sphere"], glm::vec3(-3, 1, 0));

	// render random object
	RenderMesh(meshes[names[idx]], glm::vec3(1, 1, 1), glm::vec3(0.5f));
}

void Laborator1::FrameEnd()
{
	DrawCoordinatSystem();
}

// Read the documentation of the following functions in: "Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void Laborator1::OnInputUpdate(float deltaTime, int mods)
{
	// treat continuous update based on input

	if (window->KeyHold(GLFW_KEY_W)) {
		// go forward on Oz
		pos.z += deltaTime;
	}
	else if (window->KeyHold(GLFW_KEY_A)) {
		// go left on Ox
		pos.x -= deltaTime;
	}
	else if (window->KeyHold(GLFW_KEY_S)) {
		// go back on Oz
		pos.z -= deltaTime;
	}
	else if (window->KeyHold(GLFW_KEY_D)) {
		// go right on Ox
		pos.x += deltaTime;
	}
	else if (window->KeyHold(GLFW_KEY_E)) {
		// go up on Oy
		pos.y += deltaTime;
	}
	else if (window->KeyHold(GLFW_KEY_Q)) {
		// go down on Oy
		pos.y -= deltaTime;
	}
};

void Laborator1::OnKeyPress(int key, int mods)
{
	// add key press event
	if (key == GLFW_KEY_F) {
		bgColor.x = (float)(rand() % 101) / 100;
		bgColor.y = (float)(rand() % 101) / 100;
		bgColor.z = (float)(rand() % 101) / 100;
	}

	if (key == GLFW_KEY_T) {
		idx = (idx + 1) % 3;
	}
};

void Laborator1::OnKeyRelease(int key, int mods)
{
	// add key release event
};

void Laborator1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
};

void Laborator1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
};

void Laborator1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
	// treat mouse scroll event
}

void Laborator1::OnWindowResize(int width, int height)
{
	// treat window resize event
}
