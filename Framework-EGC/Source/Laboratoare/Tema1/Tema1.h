// CONSTANTIN MIHAI - 336CA

#pragma once

#include <Component/SimpleScene.h>
#include <Core/Engine.h>

#include <string>

class Tema1 : public SimpleScene
{
	public:
		Tema1();
		~Tema1();
		
		void Init() override;

	private:

		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;

	protected:

		bool start;
		bool finish;

		float translateX, translateY;
		float scaleX, scaleY;
		float angularStep;

		float speed;
		float time;
		int currentScore;
		bool displayFinalScore;
		float radius;
		int numberOfObstacles;
		float pi;
		float g;

		glm::mat3 modelMatrix;
		
		Mesh* bird;
		Mesh* cloud;
		Mesh* obstacle_up;
		Mesh* obstacle_down;

		std::vector<float> obstaclePositionsX;
		std::vector<float> translateObstacleX;

		std::vector<float> heights_down;
		std::vector<float> heights_up;

		std::vector<float> grassPositionsX;
		std::vector<float> translateGrassX;
		int numberofParalelograms = 43;

		std::vector<int> scores;

		int numberOfFrames;
		

		
};
