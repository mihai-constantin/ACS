// CONSTANTIN MIHAI - 336CA

#include "Tema1.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>
#include "Transform2D.h"
#include "Object2D.h"

using namespace std;

Tema1::Tema1() 
{
	// initialize start and finish
	start = false;
	finish = false;

	// initialize tx and ty (the translation steps)
	translateX = 0;
	translateY = 0;

	// initialize sx and sy(the scale factors)
	scaleX = 1;
	scaleY = 1;

	// initialize angularStep
	angularStep = 0;

	// initialize speed
	speed = 0;

	// initialize time
	time = 0;

	// initialize numberOfObstacles
	numberOfObstacles = 5;

	// initialize pi
	pi = glm::pi<float>();

	// initialize radius
	radius = 80;

	// initialize currentScore
	currentScore = 0;

	// initialize displayFinalScore
	displayFinalScore = false;

	// initialize g
	g = 800;

	// create bird mesh
	bird = Object2D::CreateBird("bird", glm::vec3(80, 360, 0));
	bird->setMeshCenter(glm::vec3(80, 360, 0));
	AddMeshToList(bird);

	// create cloud mesh
	cloud = Object2D::CreateCloud("cloud", glm::vec3(350, 500, 0), 40, glm::vec3(1, 1, 1));
	AddMeshToList(cloud);

	// create obstacleUp
	obstacle_up = Object2D::CreateObstacleUp("obstacle_up", glm::vec3(1350, 600, 0), 240, 80, glm::vec3(0.49f, 1.f, 0.f));
	obstacle_up->setMeshCenter(glm::vec3(1350, 600, 0));
	AddMeshToList(obstacle_up);

	// create obstacleDown
	obstacle_down = Object2D::CreateObstacleDown("obstacle_down", glm::vec3(1350, 158, 0), 164, 80, glm::vec3(0.49f, 1.f, 0.f));
	obstacle_down->setMeshCenter(glm::vec3(1350, 138, 0));
	AddMeshToList(obstacle_down);

	// initialize numnberOfFrames
	numberOfFrames = 0;
}

Tema1::~Tema1()
{

}

void Tema1::Init()
{
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	// create rectangle mesh - land
	Mesh* rectangle = Object2D::CreateRectangle("rectangle", glm::vec3(640, 30, 0), 60, 1280, glm::vec3(0.93f, 0.9f, 0.66f));
	AddMeshToList(rectangle);

	// create paralelogram1 mesh - grass
	Mesh* paralelogram1 = Object2D::CreateParalelogram("paralelogram1", glm::vec3(0, 68, 0), 16, 32, glm::vec3(0.19f, 0.8f, 0.19f));
	AddMeshToList(paralelogram1);

	// create paralelogram2 mesh - grass
	Mesh* paralelogram2 = Object2D::CreateParalelogram("paralelogram2", glm::vec3(0, 68, 0), 16, 32, glm::vec3(0.48f, 0.98f, 0));
	AddMeshToList(paralelogram2);

	for (int i = 0; i < numberofParalelograms; i++) {
		grassPositionsX.push_back(32 * i);
	}

	translateGrassX.resize(numberofParalelograms);
	translateGrassX.assign(numberofParalelograms, 0);

	for (int i = 0; i < numberOfObstacles; i++) {
		obstaclePositionsX.push_back(1350 + 280 * i);
	}

	translateObstacleX.resize(numberOfObstacles);
	translateObstacleX.assign(numberOfObstacles, 0);

	heights_down.resize(numberOfObstacles);
	heights_down.assign(numberOfObstacles, 0);
	for (int i = 0; i < numberOfObstacles; i++) {
		heights_down[i] = 400 + (std::rand() % (850 - 400 + 1));
		heights_down[i] /= 1000;
	}

	heights_up.resize(numberOfObstacles);
	heights_up.assign(numberOfObstacles, 0);
	for (int i = 0; i < numberOfObstacles; i++) {
		heights_up[i] = 115 + (std::rand() % (145 - 115 + 1));
		heights_up[i] /= 100;
	}

	// create message mesh
	Mesh* message = Object2D::CreateMessage("message", glm::vec3(1, 1, 1));
	AddMeshToList(message);

	// create wings mesh
	Mesh* wings = Object2D::CreateWings("wings", glm::vec3(80, 360, 0), glm::vec3(1, 0, 0));
	AddMeshToList(wings);

	// initialize scores
	scores.resize(numberOfObstacles);
	scores.assign(numberOfObstacles, 0);
}

void Tema1::FrameStart()
{
	// Clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0.52f, 0.8f, 0.98f, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::Update(float deltaTimeSeconds) {
	glLineWidth(10);

	if (finish) {

		// bird
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(3 * bird->getMeshCenter().x, translateY);
		modelMatrix *= Transform2D::Scale(0.8f, 0.8f);
		modelMatrix *= Transform2D::Translate(80, 360);
		modelMatrix *= Transform2D::Rotate(angularStep);
		modelMatrix *= Transform2D::Translate(-80, -360);
		RenderMesh2D(meshes["bird"], shaders["VertexColor"], modelMatrix);

		// wings
		RenderMesh2D(meshes["wings"], shaders["VertexColor"], modelMatrix);

		// rectangle - land
		modelMatrix = Transform2D::Translate(0, 0);
		RenderMesh2D(meshes["rectangle"], shaders["VertexColor"], modelMatrix);

		// paralelogram - banda
		for (int i = 0; i < numberofParalelograms; i++) {
			modelMatrix = Transform2D::Translate(32 * i, 0);

			if (i % 2 == 1) {
				RenderMesh2D(meshes["paralelogram1"], shaders["VertexColor"], modelMatrix);
			}
			else {
				RenderMesh2D(meshes["paralelogram2"], shaders["VertexColor"], modelMatrix);
			}
		}

		glm::vec3 obstacleCenter = obstacle_up->getMeshCenter();
		for (int i = 0; i < numberOfObstacles; i++) {
			if (obstaclePositionsX[i] + translateObstacleX[i] + 40 + 20 < 3) {
				translateObstacleX[i] = 1400 - obstaclePositionsX[i];

				// new height_down for obstacle i
				heights_down[i] = 400 + (std::rand() % (850 - 400 + 1));
				heights_down[i] /= 1000;

				// new height_up for obstacle i
				heights_up[i] = 115 + (std::rand() % (145 - 115 + 1));
				heights_up[i] /= 100;
			}
		}

		for (int i = 0; i < numberOfObstacles; i++) {
			modelMatrix = Transform2D::Translate(translateObstacleX[i] + obstaclePositionsX[i] - obstacleCenter.x, 0)
				* Transform2D::Scale(1.f, heights_up[i]);
			RenderMesh2D(meshes["obstacle_up"], shaders["VertexColor"], modelMatrix); // obstacle up

			modelMatrix = Transform2D::Translate(translateObstacleX[i] + obstaclePositionsX[i] - obstacleCenter.x, 0)
				* Transform2D::Scale(1.f, heights_down[i]);
			RenderMesh2D(meshes["obstacle_down"], shaders["VertexColor"], modelMatrix); // obstacle down
		}

		// clouds
		modelMatrix = Transform2D::Translate(-200, 150);
		RenderMesh2D(meshes["cloud"], shaders["VertexColor"], modelMatrix);

		modelMatrix = Transform2D::Translate(250, 80);
		RenderMesh2D(meshes["cloud"], shaders["VertexColor"], modelMatrix);

		modelMatrix = Transform2D::Translate(600, 0)
			* Transform2D::Scale(1.3f, 1.3f);
		RenderMesh2D(meshes["cloud"], shaders["VertexColor"], modelMatrix);

		if (!displayFinalScore) {
			displayFinalScore = true;
			cout << endl;
			cout << "YOU LOST!" << endl;
			cout << "FINAL SCORE: " << currentScore << endl;
		}
	}
	else {

		if (!start) {
			
			// bird
			modelMatrix = Transform2D::Translate(bird->getMeshCenter().x, 0)
						* Transform2D::Scale(0.8f, 0.8f);
			RenderMesh2D(meshes["bird"], shaders["VertexColor"], modelMatrix);

			// wings
			modelMatrix = Transform2D::Translate(bird->getMeshCenter().x, 0)
				* Transform2D::Scale(0.8f, 0.8f);
			RenderMesh2D(meshes["wings"], shaders["VertexColor"], modelMatrix);

			// rectangle - land
			modelMatrix = Transform2D::Translate(0, 0);
			RenderMesh2D(meshes["rectangle"], shaders["VertexColor"], modelMatrix);

			// paralelogram - banda
			for (int i = 0; i < numberofParalelograms; i++) {
				modelMatrix = Transform2D::Translate(32 * i, 0);

				if (i % 2 == 1) {
					RenderMesh2D(meshes["paralelogram1"], shaders["VertexColor"], modelMatrix);
				}
				else {
					RenderMesh2D(meshes["paralelogram2"], shaders["VertexColor"], modelMatrix);
				}
			}

			// clouds
			modelMatrix = Transform2D::Translate(-200, 150);
			RenderMesh2D(meshes["cloud"], shaders["VertexColor"], modelMatrix);

			modelMatrix = Transform2D::Translate(250, 80);
			RenderMesh2D(meshes["cloud"], shaders["VertexColor"], modelMatrix);

			modelMatrix = Transform2D::Translate(600, 0)
				* Transform2D::Scale(1.3f, 1.3f);
			RenderMesh2D(meshes["cloud"], shaders["VertexColor"], modelMatrix);
			
			// message
			time += deltaTimeSeconds * 2;
			modelMatrix = Transform2D::Translate(50, 100)
						* Transform2D::Translate(825, 200)
						* Transform2D::Scale(sin(time) * 0.1f + 1, sin(time) * 0.1f + 1)
						* Transform2D::Translate(-825, -200);
			RenderMesh2D(meshes["message"], shaders["VertexColor"], modelMatrix);

			if (sin(time) < -.02f) {
				time = 0;
			}
		}
		else {
			
			numberOfFrames++;

			translateX += deltaTimeSeconds * 100;

			for (int i = 0; i < numberOfObstacles; i++) {
				if (currentScore > 10) {
					// increase difficulty
					translateObstacleX[i] += (-1) * deltaTimeSeconds * 150;
				}
				else if (currentScore > 20) {
					translateObstacleX[i] += (-1) * deltaTimeSeconds * 300;
				}
				else if (currentScore > 30) {
					translateObstacleX[i] += (-1) * deltaTimeSeconds * 600;
				}
				else {
					translateObstacleX[i] += (-1) * deltaTimeSeconds * 100;
				}
			}

			for (int i = 0; i < numberofParalelograms; i++) {
				translateGrassX[i] += (-1) * deltaTimeSeconds * 100;
			}

			speed -= g * deltaTimeSeconds;
			translateY += speed * deltaTimeSeconds;
			cout << "translateY = " << translateY << endl;

			if (angularStep > 0 && speed < 0) {
				angularStep -= deltaTimeSeconds * 2;
			}
			else if (angularStep > -pi / 4 && speed < 0) {
				angularStep -= deltaTimeSeconds * 3;
			}
			else if (angularStep > -pi / 2 && speed < 0) {
				angularStep -= deltaTimeSeconds * 4;
			}

			// cercul ce incadreaza pasarea
			int circleX = 3 * bird->getMeshCenter().x;
			int circleY = 288 + translateY;

			// render bird
			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform2D::Translate(3 * bird->getMeshCenter().x, translateY);
			modelMatrix *= Transform2D::Scale(0.8f, 0.8f);
			modelMatrix *= Transform2D::Translate(80, 360);
			modelMatrix *= Transform2D::Rotate(angularStep);
			modelMatrix *= Transform2D::Translate(-80, -360);
			RenderMesh2D(meshes["bird"], shaders["VertexColor"], modelMatrix);
			//render wings
			if (numberOfFrames >= 0 && numberOfFrames <= 7) {
				modelMatrix *= Transform2D::Scale(0.f, 0.f);
			}
			else if (numberOfFrames > 14) {
				numberOfFrames = 0;
			}
			RenderMesh2D(meshes["wings"], shaders["VertexColor"], modelMatrix);

			// check collision for land
			if (Object2D::CheckCollision(glm::vec3(circleX, circleY, 0), radius, glm::vec3(640, 38, 0), 50, 1280)) {
				finish = true;
			}

			// rectangle - land
			modelMatrix = Transform2D::Translate(0, 0);
			RenderMesh2D(meshes["rectangle"], shaders["VertexColor"], modelMatrix);

			// paralelogram - banda
			for (int i = 0; i < numberofParalelograms; i++) {
				if (grassPositionsX[i] + translateGrassX[i] + 20 < 5) {
					translateGrassX[i] = 1280 - grassPositionsX[i];
				}
			}
			for (int i = 0; i < numberofParalelograms; i++) {
				modelMatrix = Transform2D::Translate(translateGrassX[i] + grassPositionsX[i], 0);
				if (i % 2 == 1) {
					RenderMesh2D(meshes["paralelogram1"], shaders["VertexColor"], modelMatrix);
				}
				else {
					RenderMesh2D(meshes["paralelogram2"], shaders["VertexColor"], modelMatrix);
				}
			}

			// obstacle up + down
			glm::vec3 obstacleCenter = obstacle_up->getMeshCenter();
			for (int i = 0; i < numberOfObstacles; i++) {
				if (obstaclePositionsX[i] + translateObstacleX[i] + 40 + 20 < 3) {
					translateObstacleX[i] = 1400 - obstaclePositionsX[i];

					scores[i] = 0;

					// new height_down for obstacle i
					heights_down[i] = 400 + (std::rand() % (999 - 400 + 1));
					heights_down[i] /= 1000;

					// new height_up for obstacle i
					heights_up[i] = 100 + (std::rand() % (145 - 100 + 1));
					heights_up[i] /= 100;
				}
			}

			for (int i = 0; i < numberOfObstacles; i++) {
				if (obstaclePositionsX[i] + translateObstacleX[i] < 240) {
					// update score
					if (!scores[i]) {
						scores[i] = 1;
						currentScore++;
						cout << "score: " << currentScore << endl;
					}
				}
			}

			time += deltaTimeSeconds * 2;
			if (sin(time) < -.02f) {
				time = 0;
			}

			for (int i = 0; i < numberOfObstacles; i++) {
				if (currentScore > 10 && (i == 0 || i == 2 || i == 4)) {
					modelMatrix = Transform2D::Translate(translateObstacleX[i] + obstaclePositionsX[i] - obstacleCenter.x, 0)
						* Transform2D::Scale(1.f, heights_up[i])
						* Transform2D::Translate(translateObstacleX[i] + obstaclePositionsX[i], 600 * heights_up[i])
						* Transform2D::Scale(1.f, sin(time) * 0.1f + 1)
						* Transform2D::Translate(-(translateObstacleX[i] + obstaclePositionsX[i]), -600 * heights_up[i]);
				}
				else {
					modelMatrix = Transform2D::Translate(translateObstacleX[i] + obstaclePositionsX[i] - obstacleCenter.x, 0)
						* Transform2D::Scale(1.f, heights_up[i]);
				}
				RenderMesh2D(meshes["obstacle_up"], shaders["VertexColor"], modelMatrix); // obstacle up

				if (currentScore > 10 && (i == 0 || i == 2 || i == 4)) {
					modelMatrix = Transform2D::Translate(translateObstacleX[i] + obstaclePositionsX[i] - obstacleCenter.x, 0)
						* Transform2D::Scale(1.f, heights_down[i])
						* Transform2D::Translate(translateObstacleX[i] + obstaclePositionsX[i], 138 * heights_down[i])
						* Transform2D::Scale(1.f, sin(time) * 0.1f + 1)
						* Transform2D::Translate(-(translateObstacleX[i] + obstaclePositionsX[i]), -138 * heights_down[i]);
				}
				else {
					modelMatrix = Transform2D::Translate(translateObstacleX[i] + obstaclePositionsX[i] - obstacleCenter.x, 0)
						* Transform2D::Scale(1.f, heights_down[i]);
				}

				RenderMesh2D(meshes["obstacle_down"], shaders["VertexColor"], modelMatrix); // obstacle down
			}

			for (int i = 0; i < numberOfObstacles; i++) {
				// check collision for up obstacles
				if (Object2D::CheckCollision(glm::vec3(circleX, circleY, 0), radius, glm::vec3(translateObstacleX[i] + obstaclePositionsX[i], 600 * heights_up[i], 0), 240 * heights_up[i], 120)) {
					finish = true;
				}
				
				// check collision for down obstacles
				if (Object2D::CheckCollision(glm::vec3(circleX, circleY, 0), radius, glm::vec3(translateObstacleX[i] + obstaclePositionsX[i], 138 * heights_down[i], 0), 124 * heights_down[i], 120)) {
					finish = true;
				}

			}

			// clouds
			modelMatrix = Transform2D::Translate(-200, 150);
			RenderMesh2D(meshes["cloud"], shaders["VertexColor"], modelMatrix);

			modelMatrix = Transform2D::Translate(250, 80);
			RenderMesh2D(meshes["cloud"], shaders["VertexColor"], modelMatrix);

			modelMatrix = Transform2D::Translate(600, 0)
				* Transform2D::Scale(1.3f, 1.3f);
			RenderMesh2D(meshes["cloud"], shaders["VertexColor"], modelMatrix);
		}
	}
}

void Tema1::FrameEnd()
{

}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{

}

void Tema1::OnKeyPress(int key, int mods)
{
	// add key press event
	if (key == GLFW_KEY_SPACE) {
		start = true;

		speed = 400;
		angularStep = pi / 4;
	}
}

void Tema1::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{

}

void Tema1::OnWindowResize(int width, int height)
{

}


