#include "Laborator4.h"
#include "Transform3D.h"
#include "Object3DLab4.h"

#include <vector>
#include <string>
#include <iostream>

#include <Core/Engine.h>

using namespace std;

using namespace std;

Laborator4::Laborator4()
{
}

Laborator4::~Laborator4()
{
}

Mesh* Laborator4::CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned short>& indices)
{
	unsigned int VAO = 0;
	// TODO: Create the VAO and bind it
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// TODO: Create the VBO and bind it
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// TODO: Send vertices data into the VBO buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	// TODO: Crete the IBO and bind it
	unsigned int IBO;
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	// TODO: Send indices data into the IBO buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

	// ========================================================================
	// This section describes how the GPU Shader Vertex Shader program receives data

	// set vertex position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

	// set vertex normal attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

	// set texture coordinate attribute
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

	// set vertex color attribute
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));
	// ========================================================================

	// Unbind the VAO
	glBindVertexArray(0);

	// Check for OpenGL errors
	CheckOpenGLError();

	// Mesh information is saved into a Mesh object
	meshes[name] = new Mesh(name);
	meshes[name]->InitFromBuffer(VAO, static_cast<unsigned short>(indices.size()));
	meshes[name]->vertices = vertices;
	meshes[name]->indices = indices;
	return meshes[name];
}

void Laborator4::Init()
{
	polygonMode = GL_FILL;

	Mesh* mesh = new Mesh("box");
	mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
	meshes[mesh->GetMeshID()] = mesh;

	// initialize tx, ty and tz (the translation steps)
	translateX = 0;
	translateY = 0;
	translateZ = 0;

	// initialize sx, sy and sz (the scale factors)
	scaleX = 1;
	scaleY = 1;
	scaleZ = 1;
	
	// initialize angularSteps
	angularStepOX = 0;
	angularStepOY = 0;
	angularStepOZ = 0;

	// sea
	glm::vec3 center = glm::vec3(0, 0, 0);
	float radius = 2.f;
	glm::vec3 color = glm::vec3(1, 0, 0);
	std::vector<VertexFormat> seaVertices = Object3DLab4::GetSeaVertices(center, radius, color);
	std::vector<unsigned short> seaIndices = Object3DLab4::GetSeaIndices();
	CreateMesh("sea", seaVertices, seaIndices);

	for (int t = 120; t < 360; t += 18) {

		float x = radius * cos(RADIANS(t));
		float y = radius * sin(RADIANS(t));
		int z = 0 + (std::rand() % (4 - 0 + 1));

		// cout << x << " " << y << endl;

		positionsX.push_back(x);
		positionsY.push_back(y);
		positionsZ.push_back(0);
	}
}

void Laborator4::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Laborator4::Update(float deltaTimeSeconds)
{
	glLineWidth(3);
	glPointSize(5);
	glPolygonMode(GL_FRONT_AND_BACK, polygonMode);

	angularStepOX += deltaTimeSeconds * 3.f;
	angularStepOY += deltaTimeSeconds * 3.f;

	translateX += deltaTimeSeconds;
	translateY += deltaTimeSeconds;
	translateZ += deltaTimeSeconds;

	time += deltaTimeSeconds;

	angularStepOZ += deltaTimeSeconds * 0.1f;

	for (int i = 0; i < positionsX.size(); i++) {

		modelMatrix = Transform3D::Translate(positionsX[i], positionsY[i], positionsZ[i])
			* Transform3D::Translate(-positionsX[i], -positionsY[i], -positionsZ[i])
			* Transform3D::RotateOZ(angularStepOZ)
			* Transform3D::Translate(positionsX[i], positionsY[i], positionsZ[i])
			* Transform3D::Scale(0.2f, 0.2f, 0.2f);

		//if (modelMatrix[3].y >= 0) {
			RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);
		//}
		
		//cout << modelMatrix[3].x << " " << modelMatrix[3].y << " " << modelMatrix[3].z << endl;
	}

	/*modelMatrix = Transform3D::Translate(0, sin(time) * 0.5f, 0)
				* Transform3D::Translate(0.0f, 0.5f, -1.5f)
				* Transform3D::Scale(scaleX, scaleY, scaleZ);
	RenderMesh(meshes["box"], shaders["Simple"], modelMatrix);*/

	/*modelMatrix = Transform3D::Translate(2.5f, 0.5f, -1.5f)
				* Transform3D::Scale(sin(time) * 0.25f + 1, sin(time) * 0.25f + 1, sin(time) * 0.25f + 1);

	RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);*/

	/*modelMatrix = Transform3D::Translate(3.5f, 0.5f, 3.5f);
	RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);*/

	modelMatrix = Transform3D::Translate(0.f, 0.f, 0.f);
	RenderMesh(meshes["sea"], shaders["VertexNormal"], modelMatrix);

	/*if (sin(time) < -.02f) {
		time = 0;
	}*/
}

void Laborator4::FrameEnd()
{
	DrawCoordinatSystem();
}

void Laborator4::OnInputUpdate(float deltaTime, int mods)
{
	if (window->KeyHold(GLFW_KEY_1)) {
		angularStepOX += deltaTime;
	}
	if (window->KeyHold(GLFW_KEY_2)) {
		angularStepOY += deltaTime;
	}
	if (window->KeyHold(GLFW_KEY_3)) {
		angularStepOZ += deltaTime;
	}
}

void Laborator4::OnKeyPress(int key, int mods)
{
	// add key press event
	if (key == GLFW_KEY_SPACE)
	{
		switch (polygonMode)
		{
		case GL_POINT:
			polygonMode = GL_FILL;
			break;
		case GL_LINE:
			polygonMode = GL_POINT;
			break;
		default:
			polygonMode = GL_LINE;
			break;
		}
	}
}

void Laborator4::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Laborator4::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
}

void Laborator4::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Laborator4::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator4::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Laborator4::OnWindowResize(int width, int height)
{
}
