// CONSTANTIN MIHAI - 336CA

#include "Tema2.h"
#include "Transform3D.h"
#include "Object3D.h"

#include <vector>
#include <string>
#include <iostream>

#include <Core/Engine.h>

using namespace std;

Tema2::Tema2()
{
	// initialize background
	background = glm::vec3(0.678f, 0.847f, 0.9f);

	// initialize pressC
	pressC = false;

	// initialize scale
	scaleX = 0;
	scaleY = 0;
	scaleZ = 0;

	// initialize translate
	translateX = 0;
	translateY = 0;
	translateZ = 0;

	// initialize angularSteps
	angularStepOX = 0;
	angularStepOY = 0;
	angularStepOZ = 0;
	angularStepTeapot = 0;
	angularStep = 0;

	// initialize angularStepCloud
	angularStepCloud = 0;

	// initialize camera
	camera = new AvionCuMotor::Camera();
	camera->Set(glm::vec3(0, 51, 7.5f), glm::vec3(0, 52.5, 0), glm::vec3(0, 1, 0));

	// initialize renderCameraTarget
	renderCameraTarget = false;

	// initialize planeCenter
	planeCenter = glm::vec3(0.25f, 1.f, 0.f);

	// initialize pi
	pi = glm::pi<float>();

	// initialize obstaclePosition
	obstaclePosition = glm::vec3(0, 53, 0);

	// initialize LIVES
	LIVES = 3;

	// initialize finish
	finish = false;

	// initialize COMBUSTIBIL
	COMBUSTIBIL = 100.f;

	// initialize numberOfTeapots
	numberOfTeapots = 0;

	// initialize py
	py = 0.f;

	//Light & material properties - Lab 7
	lightPosition = glm::vec3(7, 70, 0);
	materialShininess = 30;
	materialKd = 0.5;
	materialKs = 0.5;

	// initialize positionZ
	positionZ = 0;
}

Tema2::~Tema2()
{

}

void Tema2::Init()
{
	// avion
	std::vector<VertexFormat> planeVertices = Object3D::GetPlaneVertices();
	std::vector<unsigned short> planeIndices = Object3D::GetPlaneIndices();
	CreateMesh("plane", planeVertices, planeIndices);

	// elice
	std::vector<VertexFormat> propellerVertices = Object3D::GetPropellerVertices();
	std::vector<unsigned short> propellerIndices = Object3D::GetPropellerIndices();
	CreateMesh("elice", propellerVertices, propellerIndices);

	// roti
	std::vector<VertexFormat> wheelsVertices = Object3D::GetWheelsVertices();
	std::vector<unsigned short> wheelsIndices = Object3D::GetWheelsIndices();
	CreateMesh("wheels", wheelsVertices, wheelsIndices);

	// cloud
	std::vector<VertexFormat> cloudVertices = Object3D::GetCloudVertices();
	std::vector<unsigned short> cloudIndices = Object3D::GetCloudIndices();
	CreateMesh("cloud", cloudVertices, cloudIndices);

	// cloud2
	std::vector<VertexFormat> cloud2Vertices = Object3D::GetCloud2Vertices();
	std::vector<unsigned short> cloud2Indices = Object3D::GetCloud2Indices();
	CreateMesh("cloud2", cloud2Vertices, cloud2Indices);

	// sea
	glm::vec3 center = glm::vec3(0, 0, 0);
	float radius = 50.f;
	glm::vec3 color = glm::vec3(1, 0, 0);
	std::vector<VertexFormat> seaVertices = Object3D::GetSeaVertices(center, radius, color);
	std::vector<unsigned short> seaIndices = Object3D::GetSeaIndices();
	CreateMesh("sea", seaVertices, seaIndices);

	// circle1 - score
	center = glm::vec3(-0.9, 0.9, 0);
	radius = 0.065f;
	std::vector<VertexFormat> circleScoreVertices1 = Object3D::GetCircleVertices(center, radius, color);
	std::vector<unsigned short> circleScoreIndices1 = Object3D::GetCircleIndices();
	CreateMesh("circleScore1", circleScoreVertices1, circleScoreIndices1);

	// circle2 - score
	center = glm::vec3(-0.75, 0.9, 0);
	std::vector<VertexFormat> circleScoreVertices2 = Object3D::GetCircleVertices(center, radius, color);
	std::vector<unsigned short> circleScoreIndices2 = Object3D::GetCircleIndices();
	CreateMesh("circleScore2", circleScoreVertices2, circleScoreIndices2);

	// circle3 - score
	center = glm::vec3(-0.6, 0.9, 0);
	std::vector<VertexFormat> circleScoreVertices3 = Object3D::GetCircleVertices(center, radius, color);
	std::vector<unsigned short> circleScoreIndices3 = Object3D::GetCircleIndices();
	CreateMesh("circleScore3", circleScoreVertices3, circleScoreIndices3);

	// circle4 - score
	{
		center = glm::vec3(-0.45, 0.9, 0);
		std::vector<VertexFormat> circleScoreVertices4 = Object3D::GetCircleVertices(center, radius, color);
		std::vector<unsigned short> circleScoreIndices4 = Object3D::GetCircleIndices();
		CreateMesh("circleScore4", circleScoreVertices4, circleScoreIndices4);
	}

	// rectangle - bara combustibil
	center = glm::vec3(0.7, 0.885, 0);
	std::vector<VertexFormat> rectangleVertices = Object3D::GetRectangleVertices(center, 0.125f, 0.5f, color);
	std::vector<unsigned short> rectangleIndices = Object3D::GetRectangleIndices();
	CreateMesh("rectangleCombustibil", rectangleVertices, rectangleIndices);

	// rectangle - bara combustibil contur - stanga
	center = glm::vec3(0.45, 0.885, 0);
	std::vector<VertexFormat> rectangleVertices1 = Object3D::GetRectangleVertices(center, 0.125f, 0.015f, color);
	std::vector<unsigned short> rectangleIndices1 = Object3D::GetRectangleIndices();
	CreateMesh("rectangleCombustibilConturStanga", rectangleVertices1, rectangleIndices1);

	// rectangle - bara combustibil contur - sus
	center = glm::vec3(0.7, 0.9475, 0);
	std::vector<VertexFormat> rectangleVertices2 = Object3D::GetRectangleVertices(center, 0.025f, 0.515f, color);
	std::vector<unsigned short> rectangleIndices2 = Object3D::GetRectangleIndices();
	CreateMesh("rectangleCombustibilConturSus", rectangleVertices2, rectangleIndices2);
	
	// rectangle - bara combustibil contur - jos
	center = glm::vec3(0.7, 0.8225, 0);
	std::vector<VertexFormat> rectangleVertices3 = Object3D::GetRectangleVertices(center, 0.025f, 0.515f, color);
	std::vector<unsigned short> rectangleIndices3 = Object3D::GetRectangleIndices();
	CreateMesh("rectangleCombustibilConturJos", rectangleVertices3, rectangleIndices3);
	
	// rectangle - bara combustibil contur - dreapta
	center = glm::vec3(0.95, 0.885, 0);
	std::vector<VertexFormat> rectangleVertices4 = Object3D::GetRectangleVertices(center, 0.15f, 0.015f, color);
	std::vector<unsigned short> rectangleIndices4 = Object3D::GetRectangleIndices();
	CreateMesh("rectangleCombustibilConturDreapta", rectangleVertices4, rectangleIndices4);

	// create mesh for camera sphere
	{
		Mesh* mesh = new Mesh("sphere");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	// teapot
	{
		Mesh* mesh = new Mesh("teapot");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "teapot.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	// projectionMatrix
	projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);

	// Create a shader program for sea
	{
		Shader* shader = new Shader("ShaderTema2");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	// Create shader for obstacles
	{
		Shader* shader = new Shader("ShaderObstacle");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/VertexShaderObstacle.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/FragmentShaderObstacle.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	// Create shader for score
	{
		Shader* shader = new Shader("ShaderScore");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/VertexShaderScore.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/FragmentShaderScore.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	// Create shader for combustible
	{
		Shader* shader = new Shader("ShaderCombustible");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/VertexShaderCombustibil.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/FragmentShaderCombustibil.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	// Create shader for combustible's frame
	{
		Shader* shader = new Shader("ShaderFrame");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/VertexShaderContur.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/FragmentShaderContur.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	// clouds
	for (int t = 0; t < 360; t += 10) {
		int randomPosition = 512 + (std::rand() % (560 - 512 + 1));
		radius = (float)randomPosition / 10;
		float x = radius * cos(RADIANS(t));
		float y = radius * sin(RADIANS(t));
		int z = 0 + (std::rand() % (8 - 0 + 1));

		positionsX.push_back(x);
		positionsY.push_back(y);
		positionsZ.push_back(posZ[z]);
	}

	// obstacles - spheres
	for (int t = 100; t <= 425; t += 5) {
		int randomPosition = 512 + (std::rand() % (555 - 512 + 1));
		radius = (float)randomPosition / 10;
		float x = radius * cos(RADIANS(t));
		float y = radius * sin(RADIANS(t));
		int z = 0 + (std::rand() % (8 - 0 + 1));

		positionsObstaclesX.push_back(x);
		positionsObstaclesY.push_back(y);
		positionsObstaclesZ.push_back(posObstaclesZ[z]);

		brokenObstacles.push_back(false);
	}

	// combustibil - teapots - 10
	for (int t = 0; t < 360; t += 36) {
		int randomPosition = 512 + (std::rand() % (552 - 512 + 1));
		radius = (float)randomPosition / 10;
		float x = radius * cos(RADIANS(t));
		float y = radius * sin(RADIANS(t));
		int z = 0 + (std::rand() % (8 - 0 + 1));

		positionsTeapotX.push_back(x);
		positionsTeapotY.push_back(y);
		positionsTeapotZ.push_back(posTeapotZ[z]);

		brokenTeapots.push_back(false);
	}

	// obstacles - yellow spheres -- add a life to player
	for (int t = 0; t <= 180; t += 180) {
		int randomPosition = 512 + (std::rand() % (555 - 512 + 1));
		radius = (float)randomPosition / 10;
		float x = radius * cos(RADIANS(t));
		float y = radius * sin(RADIANS(t));
		int z = 0 + (std::rand() % (8 - 0 + 1));

		positionsYellowObstaclesX.push_back(x);
		positionsYellowObstaclesY.push_back(y);
		positionsYellowObstaclesZ.push_back(posYellowObstaclesZ[z]);

		brokenYellowObstacles.push_back(false);
	}
}

Mesh* Tema2::CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned short>& indices)
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

void Tema2::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(background.x, background.y, background.z, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema2::Update(float deltaTimeSeconds)
{
	// lumina - lab7
	lightPosition = glm::vec3(7.5f, translateY + 51.5f, -2.f);

	// combustibil avion
	float time = Engine::GetElapsedTime();
	COMBUSTIBIL = 100 - 2 * time + numberOfTeapots * 15;

	if (isOrtographic) {
		projectionMatrix = glm::ortho(-50.f, 50.f, -50.f, 50.f, 0.01f, 200.f);
	}
	else {
		projectionMatrix = glm::perspective(RADIANS(fov), window->props.aspectRatio, 0.01f, 200.f);
	}

	angularStepOX += deltaTimeSeconds * 20.f;
	angularStepOY += deltaTimeSeconds * 20.f;

	if (time > 40.f) {
		angularStepOZ += deltaTimeSeconds * 0.12f;

	} else if (time > 20.f) {
		angularStepOZ += deltaTimeSeconds * 0.11f;
	}
	else {
		angularStepOZ += deltaTimeSeconds * 0.1f;
	}

	angularStepCloud += deltaTimeSeconds * 5.f;
	angularStepTeapot += deltaTimeSeconds * 5.f;

	// only if i'm alive, i can control the plane
	if (!finish) {
		if (pressC) {
			// first person perspective
			if (py < 0.61 && py > 0.1) {
				// go up
				if (translateY + 51.5f < 55.5f) {
					translateY += deltaTimeSeconds * 3.f;
				}
				if (angularStep < 0.2f) {
					angularStep += deltaTimeSeconds * 0.2f;
				}
			}

			if (py > 0.61) {
				// go down
				if (translateY + 51.5f > 51.f) {
					translateY = translateY - deltaTimeSeconds * 3.f;
				}
				if (angularStep > -0.2f) {
					angularStep -= deltaTimeSeconds * 0.2f;
				}
			}
			 camera->Set(glm::vec3(-1.65f, translateY + 52.5f, 0), glm::vec3(0.25f, translateY + 52.5f, 0), glm::vec3(0, 1, 0));
		}
		else {
			// third person perspective
			if (py < 0.61 && py > 0.1) {
				// go up
				if (translateY + 51.5f < 56) {
					translateY += deltaTimeSeconds * 2.5f;
					if (angularStep < 0.2f) {
						angularStep += deltaTimeSeconds * 0.25f;
					}
				}
			}

			if (py > 0.61) {
				// go down
				if (translateY + 51.5f > 51.f) {
					translateY = translateY - deltaTimeSeconds * 2.5f;
					if (angularStep > -0.2f) {
						angularStep -= deltaTimeSeconds * 0.25f;
					}

				}
			}
		}
	}
	
	if (LIVES <= 0 || COMBUSTIBIL <= 0) {
		finish = true;
	}
	
	// adio, avion
	if (finish) {

		if (pressC) {
			camera->Set(glm::vec3(-1.65f, translateY + 52.5f, 0), glm::vec3(0.25f, translateY + 52.5f, 0), glm::vec3(0, 1, 0));
		}

		if (translateY + 51.f > 49.f) {
			translateY = translateY - deltaTimeSeconds * 1.7f;
			angularStep -= deltaTimeSeconds * 0.3f;
		}

		// Render clouds objects
		for (int i = 0; i < positionsX.size(); i++) {
			modelMatrix = Transform3D::Translate(positionsX[i], positionsY[i], positionsZ[i])
				* Transform3D::Translate(-positionsX[i], -positionsY[i], -positionsZ[i])
				* Transform3D::RotateOZ(angularStepOZ)
				* Transform3D::Translate(positionsX[i], positionsY[i], positionsZ[i])
				* Transform3D::Scale(0.25f, 0.25f, 0.25f)
				* Transform3D::RotateOY(angularStepCloud);

			if (modelMatrix[3].y >= 0 && (modelMatrix[3].x >= -25 && modelMatrix[3].x <= 25)) {
				RenderMesh(meshes["cloud"], shaders["VertexNormal"], modelMatrix, glm::vec3(1, 1, 1));
			}

			modelMatrix *= Transform3D::Translate(-0.1f, 4.f, 0.f)
				* Transform3D::Scale(0.23f, 0.23f, 0.23f)
				* Transform3D::Translate(-1, 5, 0)
				* Transform3D::RotateOX(angularStepCloud)
				* Transform3D::RotateOZ(angularStepCloud)
				* Transform3D::Translate(1, -5, 0);

			if (modelMatrix[3].y >= 0 && (modelMatrix[3].x >= -25 && modelMatrix[3].x <= 25)) {
				RenderMesh(meshes["cloud2"], shaders["VertexNormal"], modelMatrix, glm::vec3(1, 1, 1));
			}
		}

		// Render sea
		modelMatrix = Transform3D::Translate(0.f, 0.f, 0.f);
		RenderMesh(meshes["sea"], shaders["ShaderTema2"], modelMatrix, glm::vec3(0.5, 0.5, 1));

		if (translateY + 51.f > 49.f) {
			// avion
			modelMatrix = Transform3D::Translate(0.f, translateY + 51.5f, 0.f)
				* Transform3D::Scale(2.f, 1.f, 1.f)
				* Transform3D::Scale(0.3f, 0.3f, 0.3f)
				* Transform3D::RotateOZ(angularStep);
			RenderMesh(meshes["plane"], shaders["VertexNormal"], modelMatrix, glm::vec3(1, 1, 1));

			// elice
			modelMatrix *= Transform3D::RotateOX(angularStepOX);
			RenderMesh(meshes["elice"], shaders["VertexNormal"], modelMatrix, glm::vec3(1, 1, 1));

			// roata spate
			modelMatrix = Transform3D::Translate(0.f, translateY + 51.5f, 0.f)
				* Transform3D::Scale(0.4f, 0.4f, 0.4f)
				* Transform3D::Scale(1.f, 0.8f, 1.f)
				* Transform3D::RotateOZ(angularStep);
			RenderMesh(meshes["wheels"], shaders["VertexNormal"], modelMatrix, glm::vec3(1, 1, 1));

			// roti fata
			modelMatrix = Transform3D::Translate(0.5f, translateY + 51.57f, -0.1f)
				* Transform3D::Scale(2.f, 1.f, 1.f)
				* Transform3D::Scale(0.4f, 0.4f, 0.4f)
				* Transform3D::RotateOZ(angularStep);
			RenderMesh(meshes["wheels"], shaders["VertexNormal"], modelMatrix, glm::vec3(1, 1, 1));

			modelMatrix = Transform3D::Translate(0.5f, translateY + 51.57f, 0.1f)
				* Transform3D::Scale(2.f, 1.f, 1.f)
				* Transform3D::Scale(0.4f, 0.4f, 0.4f)
				* Transform3D::RotateOZ(angularStep);
			RenderMesh(meshes["wheels"], shaders["VertexNormal"], modelMatrix, glm::vec3(1, 1, 1));
		}
	}
	else {
		// randare vieti + bara combustibil
		if (LIVES == 4) {
			modelMatrix = glm::mat4(1);
			RenderMesh(meshes["circleScore1"], shaders["ShaderScore"], modelMatrix, glm::vec3(0.8f, 0.1f, 0.2f));
			RenderMesh(meshes["circleScore2"], shaders["ShaderScore"], modelMatrix, glm::vec3(0.8f, 0.1f, 0.2f));
			RenderMesh(meshes["circleScore3"], shaders["ShaderScore"], modelMatrix, glm::vec3(0.8f, 0.1f, 0.2f));
			RenderMesh(meshes["circleScore4"], shaders["ShaderScore"], modelMatrix, glm::vec3(0.8f, 0.1f, 0.2f));
		}
		else if (LIVES == 3) {
			modelMatrix = glm::mat4(1);
			RenderMesh(meshes["circleScore1"], shaders["ShaderScore"], modelMatrix, glm::vec3(0.8f, 0.1f, 0.2f));
			RenderMesh(meshes["circleScore2"], shaders["ShaderScore"], modelMatrix, glm::vec3(0.8f, 0.1f, 0.2f));
			RenderMesh(meshes["circleScore3"], shaders["ShaderScore"], modelMatrix, glm::vec3(0.8f, 0.1f, 0.2f));
		}
		else if (LIVES == 2) {
			modelMatrix = glm::mat4(1);
			RenderMesh(meshes["circleScore1"], shaders["ShaderScore"], modelMatrix, glm::vec3(0.8f, 0.1f, 0.2f));
			RenderMesh(meshes["circleScore2"], shaders["ShaderScore"], modelMatrix, glm::vec3(0.8f, 0.1f, 0.2f));
		}
		else if (LIVES == 1) {
			modelMatrix = glm::mat4(1);
			RenderMesh(meshes["circleScore1"], shaders["ShaderScore"], modelMatrix, glm::vec3(0.8f, 0.1f, 0.2f));
		}
		
		if (!finish) {

			// bara combustibil
			RenderMesh(meshes["rectangleCombustibil"], shaders["ShaderCombustible"], modelMatrix, glm::vec3(1.f, 1.f, 1.f));

			// bara combustibil contur - stanga
			RenderMesh(meshes["rectangleCombustibilConturStanga"], shaders["ShaderScore"], modelMatrix, glm::vec3(0.f, 0.f, 0.f));

			// bara combustibil contur - sus
			RenderMesh(meshes["rectangleCombustibilConturSus"], shaders["ShaderCombustible"], modelMatrix, glm::vec3(0.f, 0.f, 0.f));

			// bara combustibil contur - jos
			RenderMesh(meshes["rectangleCombustibilConturJos"], shaders["ShaderCombustible"], modelMatrix, glm::vec3(0.f, 0.f, 0.f));

			// bara combustibil contur - dreapta
			RenderMesh(meshes["rectangleCombustibilConturDreapta"], shaders["ShaderFrame"], modelMatrix, glm::vec3(0.f, 0.f, 0.f));
		}
		
		// avion
		modelMatrix = Transform3D::Translate(0.f, translateY + 51.5f, 0.f)
			* Transform3D::Scale(2.f, 1.f, 1.f)
			* Transform3D::Scale(0.3f, 0.3f, 0.3f)
			* Transform3D::RotateOZ(angularStep);
		RenderMesh(meshes["plane"], shaders["VertexNormal"], modelMatrix, glm::vec3(1, 1, 1));

		// elice
		modelMatrix *= Transform3D::RotateOX(angularStepOX);
		RenderMesh(meshes["elice"], shaders["VertexNormal"], modelMatrix, glm::vec3(1, 1, 1));

		// roata spate
		modelMatrix = Transform3D::Translate(0.f, translateY + 51.5f, 0.f)
			* Transform3D::Scale(0.4f, 0.4f, 0.4f)
			* Transform3D::Scale(1.f, 0.8f, 1.f)
			* Transform3D::RotateOZ(angularStep);
		RenderMesh(meshes["wheels"], shaders["VertexNormal"], modelMatrix, glm::vec3(1, 1, 1));

		// roti fata
		modelMatrix = Transform3D::Translate(0.5f, translateY + 51.57f, -0.1f)
			* Transform3D::Scale(2.f, 1.f, 1.f)
			* Transform3D::Scale(0.4f, 0.4f, 0.4f)
			* Transform3D::RotateOZ(angularStep);
		RenderMesh(meshes["wheels"], shaders["VertexNormal"], modelMatrix, glm::vec3(1, 1, 1));

		modelMatrix = Transform3D::Translate(0.5f, translateY + 51.57f, 0.1f)
			* Transform3D::Scale(2.f, 1.f, 1.f)
			* Transform3D::Scale(0.4f, 0.4f, 0.4f)
			* Transform3D::RotateOZ(angularStep);
		RenderMesh(meshes["wheels"], shaders["VertexNormal"], modelMatrix, glm::vec3(1, 1, 1));

		// Render sea
		modelMatrix = Transform3D::Translate(0.f, 0.f, 0.f);
		RenderMesh(meshes["sea"], shaders["ShaderTema2"], modelMatrix, glm::vec3(0.5, 0.5, 1));

		// Render clouds objects
		for (int i = 0; i < positionsX.size(); i++) {
			modelMatrix = Transform3D::Translate(positionsX[i], positionsY[i], positionsZ[i])
				* Transform3D::Translate(-positionsX[i], -positionsY[i], -positionsZ[i])
				* Transform3D::RotateOZ(angularStepOZ)
				* Transform3D::Translate(positionsX[i], positionsY[i], positionsZ[i])
				* Transform3D::Scale(0.25f, 0.25f, 0.25f)
				* Transform3D::RotateOY(angularStepCloud);

			if (modelMatrix[3].y >= 0 && (modelMatrix[3].x >= -25 && modelMatrix[3].x <= 25)) {
				RenderMesh(meshes["cloud"], shaders["VertexNormal"], modelMatrix, glm::vec3(1, 1, 1));
			}

			modelMatrix *= Transform3D::Translate(-0.1f, 4.f, 0.f)
				* Transform3D::Scale(0.23f, 0.23f, 0.23f)
				* Transform3D::Translate(-1, 5, 0)
				* Transform3D::RotateOX(angularStepCloud)
				* Transform3D::RotateOZ(angularStepCloud)
				* Transform3D::Translate(1, -5, 0);

			if (modelMatrix[3].y >= 0 && (modelMatrix[3].x >= -25 && modelMatrix[3].x <= 25)) {
				RenderMesh(meshes["cloud2"], shaders["VertexNormal"], modelMatrix, glm::vec3(1, 1, 1));
			}
		}

		// Render sphere obstacles
		for (int i = 0; i < positionsObstaclesX.size(); i++) {
			modelMatrix = Transform3D::Translate(positionsObstaclesX[i], positionsObstaclesY[i], positionsObstaclesZ[i])
						* Transform3D::Translate(-positionsObstaclesX[i], -positionsObstaclesY[i], -positionsObstaclesZ[i])
						* Transform3D::RotateOZ(angularStepOZ)
						* Transform3D::Translate(positionsObstaclesX[i], positionsObstaclesY[i], positionsObstaclesZ[i])
						* Transform3D::Scale(0.35f, 0.35f, 0.35f)
						* Transform3D::RotateOY(angularStepOY);

			if (!pressC) {
				// third person perspective
				bool collision = Object3D::CheckCollision(glm::vec3(modelMatrix[3].x, modelMatrix[3].y, 0), 0.35f,
					glm::vec3(0.25f, translateY + 51.5f, 0), 0.725f, 1.5f);

				if (collision) {
					if (brokenObstacles[i] == false) {
						LIVES--;
					}
					brokenObstacles[i] = true;
				}

				// update the brokenObstacles vector
				if (modelMatrix[3].y < 0) {
					brokenObstacles[i] = false;
				}

				if (modelMatrix[3].y >= 0 && (modelMatrix[3].x >= -25 && modelMatrix[3].x <= 25) && !collision && !brokenObstacles[i]) {
					RenderMesh(meshes["sphere"], shaders["ShaderObstacle"], modelMatrix, glm::vec3(1, 0, 0));
				}
			}
			else {
				// first person perspective
				bool collision = Object3D::CheckCollision(glm::vec3(modelMatrix[3].x, modelMatrix[3].y, modelMatrix[3].z), 0.35f,
					glm::vec3(0.25f, translateY + 51.5f, 0), 0.75f, 1.5f);

				if (collision) {
					if (brokenObstacles[i] == false) {
						LIVES--;
					}
					brokenObstacles[i] = true;
				}

				// update the brokenObstacles vector
				if (modelMatrix[3].y < 0) {
					brokenObstacles[i] = false;
				}

				if (modelMatrix[3].y >= 0 && (modelMatrix[3].x >= -25 && modelMatrix[3].x <= 25 && !collision && !brokenObstacles[i])) {
					RenderMesh(meshes["sphere"], shaders["ShaderObstacle"], modelMatrix, glm::vec3(1, 0, 0));
				}
			}
		}

		// Render yellow spheres obstacles
		for (int i = 0; i < positionsYellowObstaclesX.size(); i++) {
			modelMatrix = Transform3D::Translate(positionsYellowObstaclesX[i], positionsYellowObstaclesY[i], positionsObstaclesZ[i])
						* Transform3D::Translate(-positionsYellowObstaclesX[i], -positionsYellowObstaclesY[i], -positionsYellowObstaclesZ[i])
						* Transform3D::RotateOZ(angularStepOZ)
						* Transform3D::Translate(positionsYellowObstaclesX[i], positionsYellowObstaclesY[i], positionsYellowObstaclesZ[i])
						* Transform3D::Scale(0.35f, 0.35f, 0.35f)
						* Transform3D::RotateOY(angularStepOY);

			if (!pressC) {
				// third person perspective
				bool collision = Object3D::CheckCollision(glm::vec3(modelMatrix[3].x, modelMatrix[3].y, 0), 0.35f,
					glm::vec3(0.25f, translateY + 51.5f, 0), 0.725f, 1.5f);

				if (collision) {
					if (brokenYellowObstacles[i] == false) {
						LIVES++;
					}
					brokenYellowObstacles[i] = true;
				}

				// update the brokenObstacles vector
				if (modelMatrix[3].y < 0) {
					brokenYellowObstacles[i] = false;
				}

				if (modelMatrix[3].y >= 0 && (modelMatrix[3].x >= -25 && modelMatrix[3].x <= 25) && !collision && !brokenYellowObstacles[i] && LIVES < 4) {
					RenderMesh(meshes["sphere"], shaders["ShaderObstacle"], modelMatrix, glm::vec3(1, 1, 0));
				}
			}
			else {
				// first person perspective
				bool collision = Object3D::CheckCollision(glm::vec3(modelMatrix[3].x, modelMatrix[3].y, modelMatrix[3].z), 0.35f,
					glm::vec3(0.25f, translateY + 51.5f, 0), 0.75f, 1.5f);

				if (collision) {
					if (brokenYellowObstacles[i] == false) {
						LIVES++;
					}
					brokenYellowObstacles[i] = true;
				}

				// update the brokenYellowObstacles vector
				if (modelMatrix[3].y < 0) {
					brokenYellowObstacles[i] = false;
				}

				if (modelMatrix[3].y >= 0 && (modelMatrix[3].x >= -25 && modelMatrix[3].x <= 25 && !collision && !brokenYellowObstacles[i]) && LIVES < 4) {
					RenderMesh(meshes["sphere"], shaders["ShaderObstacle"], modelMatrix, glm::vec3(1, 1, 0));
				}
			}
		}

		// Render teapot objects
		for (int i = 0; i < positionsTeapotX.size(); i++) {
			modelMatrix1 = Transform3D::Translate(positionsTeapotX[i], positionsTeapotY[i], positionsTeapotZ[i])
						* Transform3D::Translate(-positionsTeapotX[i], -positionsTeapotY[i], -positionsTeapotZ[i])
						* Transform3D::RotateOZ(angularStepOZ)
						* Transform3D::Translate(positionsTeapotX[i], positionsTeapotY[i], positionsTeapotZ[i])
						* Transform3D::Scale(0.4f, 0.4f, 0.4f)
						* Transform3D::RotateOX(angularStepTeapot);

			modelMatrix2 = Transform3D::Translate(positionsTeapotX[i] + 0.2, positionsTeapotY[i] - 0.2f, positionsTeapotZ[i])
						* Transform3D::Translate(-positionsTeapotX[i] - 0.2, -positionsTeapotY[i] + 0.2f, -positionsTeapotZ[i])
						* Transform3D::RotateOZ(angularStepOZ)
						* Transform3D::Translate(positionsTeapotX[i] + 0.2, positionsTeapotY[i] - 0.2f, positionsTeapotZ[i])
						* Transform3D::Scale(0.4f, 0.4f, 0.4f)
						* Transform3D::RotateOX(angularStepTeapot);

			modelMatrix3 = Transform3D::Translate(positionsTeapotX[i] + 0.4, positionsTeapotY[i] - 0.4f, positionsTeapotZ[i])
						* Transform3D::Translate(-positionsTeapotX[i] - 0.4, -positionsTeapotY[i] + 0.4f, -positionsTeapotZ[i])
						* Transform3D::RotateOZ(angularStepOZ)
						* Transform3D::Translate(positionsTeapotX[i] + 0.4, positionsTeapotY[i] - 0.4f, positionsTeapotZ[i])
						* Transform3D::Scale(0.4f, 0.4f, 0.4f)
						* Transform3D::RotateOX(angularStepTeapot);
			
			if (!pressC) {
				// third person perspective
				bool collision1 = Object3D::CheckCollision(glm::vec3(modelMatrix1[3].x, modelMatrix1[3].y, 0), 0.35f,
					glm::vec3(0.25f, translateY + 51.5f, 0), 0.75f, 1.5f);

				bool collision2 = Object3D::CheckCollision(glm::vec3(modelMatrix2[3].x, modelMatrix2[3].y, 0), 0.35f,
					glm::vec3(0.25f, translateY + 51.5f, 0), 0.75f, 1.5f);

				bool collision3 = Object3D::CheckCollision(glm::vec3(modelMatrix3[3].x, modelMatrix3[3].y, 0), 0.35f,
					glm::vec3(0.25f, translateY + 51.5f, 0), 0.75f, 1.5f);

				if (collision1 || collision2 || collision3) {
					if (brokenTeapots[i] == false) {
						numberOfTeapots++;
					}
					brokenTeapots[i] = true;
				}

				// update the brokenTeapots vector
				if (modelMatrix1[3].y < 0 && modelMatrix2[3].y < 0 && modelMatrix3[3].y < 0) {
					brokenTeapots[i] = false;
				}

				if (modelMatrix1[3].y >= 0 && (modelMatrix1[3].x >= -25 && modelMatrix1[3].x <= 25)
					&& modelMatrix2[3].y >= 0 && (modelMatrix2[3].x >= -25 && modelMatrix2[3].x <= 25)
					&& modelMatrix3[3].y >= 0 && (modelMatrix3[3].x >= -25 && modelMatrix3[3].x <= 25)
					&& !collision1 && !collision2 && !collision3 && !brokenTeapots[i]) {
					RenderMesh(meshes["teapot"], shaders["ShaderObstacle"], modelMatrix1, glm::vec3(0.251f, 0.878f, 0.815f));
					RenderMesh(meshes["teapot"], shaders["ShaderObstacle"], modelMatrix2, glm::vec3(0.251f, 0.878f, 0.815f));
					RenderMesh(meshes["teapot"], shaders["ShaderObstacle"], modelMatrix3, glm::vec3(0.251f, 0.878f, 0.815f));
				}
			}
			else {
				// first person perspective
				bool collision1 = Object3D::CheckCollision(glm::vec3(modelMatrix1[3].x, modelMatrix1[3].y, modelMatrix1[3].z), 0.35f,
					glm::vec3(0.25f, translateY + 51.5f, 0), 0.75f, 1.5f);

				bool collision2 = Object3D::CheckCollision(glm::vec3(modelMatrix2[3].x, modelMatrix2[3].y, modelMatrix2[3].z), 0.35f,
					glm::vec3(0.25f, translateY + 51.5f, 0), 0.75f, 1.5f);

				bool collision3 = Object3D::CheckCollision(glm::vec3(modelMatrix3[3].x, modelMatrix3[3].y, modelMatrix3[3].z), 0.35f,
					glm::vec3(0.25f, translateY + 51.5f, 0), 0.75f, 1.5f);

				if (collision1 || collision2 || collision3) {
					if (brokenTeapots[i] == false) {
						numberOfTeapots++;
					}
					brokenTeapots[i] = true;
				}

				// update the brokenTeapots vector
				if (modelMatrix1[3].y < 0 && modelMatrix2[3].y < 0 && modelMatrix3[3].y < 0) {
					brokenTeapots[i] = false;
				}

				if (modelMatrix1[3].y >= 0 && (modelMatrix1[3].x >= -25 && modelMatrix1[3].x <= 25)
					&& modelMatrix2[3].y >= 0 && (modelMatrix2[3].x >= -25 && modelMatrix2[3].x <= 25)
					&& modelMatrix3[3].y >= 0 && (modelMatrix3[3].x >= -25 && modelMatrix3[3].x <= 25)
					&& !collision1 && !collision2 && !collision3 && !brokenTeapots[i]) {
					RenderMesh(meshes["teapot"], shaders["ShaderObstacle"], modelMatrix1, glm::vec3(0.251f, 0.878f, 0.815f));
					RenderMesh(meshes["teapot"], shaders["ShaderObstacle"], modelMatrix2, glm::vec3(0.251f, 0.878f, 0.815f));
					RenderMesh(meshes["teapot"], shaders["ShaderObstacle"], modelMatrix3, glm::vec3(0.251f, 0.878f, 0.815f));
				}
			}
		}
	}
}

void Tema2::FrameEnd()
{
	DrawCoordinatSystem(camera->GetViewMatrix(), projectionMatrix);
}

void Tema2::RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	// render an object using the specified shader and the specified position
	shader->Use();

	// Set shader uniforms for light & material properties
	// Set light position uniform
	GLint loc_light_position = glGetUniformLocation(shader->program, "light_position");
	glUniform3fv(loc_light_position, 1, glm::value_ptr(lightPosition));

	// Set eye position (camera position) uniform
	glm::vec3 eyePosition = GetSceneCamera()->transform->GetWorldPosition();
	GLint loc_eye_position = glGetUniformLocation(shader->program, "eye_position");
	glUniform3fv(loc_eye_position, 1, glm::value_ptr(eyePosition));
	
	// Set material property uniforms (kd, ks, shininess, object color) 
	GLint loc_kd = glGetUniformLocation(shader->program, "material_kd");  // componenta difuza
	glUniform1f(loc_kd, materialKd);

	GLint loc_ks = glGetUniformLocation(shader->program, "material_ks");  // componenta speculara
	glUniform1f(loc_ks, materialKs);

	GLint loc_material_shininess = glGetUniformLocation(shader->program, "material_shininess");
	glUniform1i(loc_material_shininess, materialShininess);

	//glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	//glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
	glm::mat4 viewMatrix = camera->GetViewMatrix();
	int loc_view_matrix = glGetUniformLocation(shader->program, "View");
	glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	//glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
	int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
	glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	
	GLint loc_color = glGetUniformLocation(shader->program, "object_color");
	glUniform3fv(loc_color, 1, glm::value_ptr(color));

	float time = Engine::GetElapsedTime();
	int timeLocation = glGetUniformLocation(shader->program, "time");
	glUniform1f(timeLocation, time);

	// combustibil
	int combustibleLocation = glGetUniformLocation(shader->program, "combustible");
	glUniform1f(combustibleLocation, COMBUSTIBIL);

	// positionZ
	int positionZLocation = glGetUniformLocation(shader->program, "positionZ");
	glUniform1i(positionZLocation, positionZ);

	mesh->Render();
}

void Tema2::OnInputUpdate(float deltaTime, int mods)
{
	// move the camera only if MOUSE_RIGHT button is pressed
	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		float cameraSpeed = 5.0f;

		if (window->KeyHold(GLFW_KEY_W)) {
			camera->TranslateForward(cameraSpeed * deltaTime);
		}

		if (window->KeyHold(GLFW_KEY_A)) {
			camera->TranslateRight(-cameraSpeed * deltaTime);
		}

		if (window->KeyHold(GLFW_KEY_S)) {
			camera->TranslateForward(-cameraSpeed * deltaTime);
		}

		if (window->KeyHold(GLFW_KEY_D)) {
			camera->TranslateRight(cameraSpeed * deltaTime);
		}

		if (window->KeyHold(GLFW_KEY_Q)) {
			camera->TranslateUpword(-cameraSpeed * deltaTime);
		}

		if (window->KeyHold(GLFW_KEY_E)) {
			camera->TranslateUpword(cameraSpeed * deltaTime);
		}
	}
	else
	{
		//--- lumina
		float speed = 2;
		
		glm::vec3 up = glm::vec3(0, 1, 0);
		glm::vec3 right = GetSceneCamera()->transform->GetLocalOXVector();
		glm::vec3 forward = GetSceneCamera()->transform->GetLocalOZVector();
		forward = glm::normalize(glm::vec3(forward.x, 0, forward.z));

		// Control light position using on W, A, S, D, E, Q
		if (window->KeyHold(GLFW_KEY_W)) lightPosition -= forward * deltaTime * speed;
		if (window->KeyHold(GLFW_KEY_A)) lightPosition -= right * deltaTime * speed;
		if (window->KeyHold(GLFW_KEY_S)) lightPosition += forward * deltaTime * speed;
		if (window->KeyHold(GLFW_KEY_D)) lightPosition += right * deltaTime * speed;
		if (window->KeyHold(GLFW_KEY_E)) lightPosition += up * deltaTime * speed;
		if (window->KeyHold(GLFW_KEY_Q)) lightPosition -= up * deltaTime * speed;
	}

	if (window->KeyHold(GLFW_KEY_M)) {
		fov -= 200.f * deltaTime;
	}

	if (window->KeyHold(GLFW_KEY_N)) {
		fov += 200.f * deltaTime;
	}
}

void Tema2::OnKeyPress(int key, int mods)
{
	// add key press event
	if (key == GLFW_KEY_T)
	{
		renderCameraTarget = !renderCameraTarget;
	}

	if (key == GLFW_KEY_O) {
		isOrtographic = true;
	}

	if (key == GLFW_KEY_P) {
		isOrtographic = false;
	}

	if (key == GLFW_KEY_C && !pressC) {
		// change the camera to the first persone mode
		pressC = true;
		camera->Set(glm::vec3(-1.65f, 52.5f, 0), glm::vec3(0.25f, 52.5f, 0), glm::vec3(0, 1, 0));
	}
	else if(key == GLFW_KEY_C && pressC)
	{
		// change the camero to third persone mode
		pressC = false;
		camera->Set(glm::vec3(0, 51, 7.5f), glm::vec3(0, 52.5, 0), glm::vec3(0, 1, 0));
	}
}

void Tema2::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event

	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		float sensivityOX = 0.001f;
		float sensivityOY = 0.001f;

		if (window->GetSpecialKeyState() == 0) {
			renderCameraTarget = false;
			// rotate the camera in First-person mode around OX and OY using deltaX and deltaY
			// use the sensitivity variables for setting up the rotation speed
			camera->RotateFirstPerson_OX(-sensivityOY * deltaY);
			camera->RotateFirstPerson_OY(-sensivityOX * deltaX);
		}

		if (window->GetSpecialKeyState() && GLFW_MOD_CONTROL) {
			renderCameraTarget = true;
			// rotate the camera in Third-person mode around OX and OY using deltaX and deltaY
			// use the sensitivity variables for setting up the rotation speed
			camera->RotateThirdPerson_OX(-sensivityOX * deltaY);
			camera->RotateThirdPerson_OY(-sensivityOY * deltaX);
		}
	}

	// miscare avion
	glm::ivec2 mousePosition = window->GetCursorPosition();
	glm::ivec2 resolution = window->GetResolution();
	// calculate percentage current mouse position
	py = (float)mousePosition.y / (float)resolution.y;

}

void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{

}

void Tema2::OnWindowResize(int width, int height)
{

}
