// CONSTANTIN MIHAI - 336CA

#pragma once
#include <Component/SimpleScene.h>
#include <Component/Transform/Transform.h>
#include <Core/GPU/Mesh.h>

#include "Camera.h"

class Tema2 : public SimpleScene
{
	public:
		Tema2();
		~Tema2();

		void Init() override;

		Mesh* CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned short>& indices);

	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color);

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;


	protected:
		glm::vec3 background;

		float translateX, translateY, translateZ;
		float scaleX, scaleY, scaleZ;
		float angularStepOX, angularStepOY, angularStepOZ;
		float angularStepCloud;

		glm::mat4 modelMatrix;
		glm::mat4 modelMatrix1;
		glm::mat4 modelMatrix2;
		glm::mat4 modelMatrix3;

		// camera
		AvionCuMotor::Camera* camera;
		glm::mat4 projectionMatrix;
		bool renderCameraTarget;

		bool isOrtographic = false;
		float fov = 60.f;

		bool pressC;

		// lumina - lab 7
		glm::vec3 lightPosition;
		unsigned int materialShininess;
		float materialKd;
		float materialKs;

		std::vector<float> nr1;
		std::vector<float> nr2;
		std::vector<float> nr3;

		std::vector<float> positionsX;
		std::vector<float> positionsY;
		std::vector<float> positionsZ;
		std::vector<float> posZ = { -1, -0.75, -0.5, -0.25, 0, 0.25, 0.5, 0.75, 1 };

		std::vector<float> positionsObstaclesX;
		std::vector<float> positionsObstaclesY;
		std::vector<float> positionsObstaclesZ;
		std::vector<float> posObstaclesZ = {-1, -0.75, -0.5, -0.25, 0, 0.25, 0.5, 0.75, 1};
		std::vector<bool> brokenObstacles;

		std::vector<float> positionsYellowObstaclesX;
		std::vector<float> positionsYellowObstaclesY;
		std::vector<float> positionsYellowObstaclesZ;
		std::vector<float> posYellowObstaclesZ = { -1, -0.75, -0.5, -0.25, 0, 0.25, 0.5, 0.75, 1 };
		std::vector<bool> brokenYellowObstacles;

		std::vector<float> positionsTeapotX;
		std::vector<float> positionsTeapotY;
		std::vector<float> positionsTeapotZ;
		std::vector<float> posTeapotZ = { -1, -0.75, -0.5, -0.25, 0, 0.25, 0.5, 0.75, 1 };
		std::vector<bool> brokenTeapots;

		glm::vec3 planeCenter;
		float py;
		float angularStep;
		float pi;

		glm::vec3 obstaclePosition;

		float angularStepTeapot;

		int LIVES;
		float COMBUSTIBIL;
		bool finish;
		int numberOfTeapots;

		int positionZ;

};