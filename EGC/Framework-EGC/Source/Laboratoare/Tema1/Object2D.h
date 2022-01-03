// CONSTANTIN MIHAI - 336CA

#pragma once

#include <string>
#include <include/glm.h>
#include <Core/GPU/Mesh.h>

namespace Object2D
{
	// Create square
	Mesh* CreateSquare(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);

	// Create circle
	Mesh* CreateCircle(std::string name, glm::vec3 center, float radius, glm::vec3 color, bool fill = false);

	// Create triangle
	Mesh* CreateTriangle(std::string name, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 color);

	// Create rectangle
	Mesh* CreateRectangle(std::string name, glm::vec3 center, int l, int L, glm::vec3 color);

	// Create paralelogram
	Mesh* CreateParalelogram(std::string name, glm::vec3 center, int l, int L, glm::vec3 color);

	// Create bird
	Mesh* CreateBird(std::string name, glm::vec3 birdCenter);

	// Create wings
	Mesh* CreateWings(std::string name, glm::vec3 birdCenter, glm::vec3 color); 

	// Create obstacle up
	Mesh* CreateObstacleUp(std::string name, glm::vec3 center, int l, int L, glm::vec3 color);

	// Create obstacle down
	Mesh* CreateObstacleDown(std::string name, glm::vec3 center, int l, int L, glm::vec3 color);

	// Create cloud
	Mesh* CreateCloud(std::string name, glm::vec3 center, float radius, glm::vec3 color);

	// Create message
	Mesh* CreateMessage(std::string name, glm::vec3 color);

	// CheckCollision
	bool CheckCollision(glm::vec3 circleCenter, float radius, glm::vec3 rectangleCenter, float l, float L); // AABB - Circle collision
}