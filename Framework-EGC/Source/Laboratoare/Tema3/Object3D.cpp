// CONSTANTIN MIHAI - 336CA

#include "Object3D.h"
#include "Tema3.h"

#include <Core/Engine.h>
#include <Component/SimpleScene.h>

#include <iostream>

std::vector<VertexFormat> Object3D::GetRectangleVertices(glm::vec3 center, float l, float L, glm::vec3 color)
{
	std::vector<VertexFormat> vertices;
	glm::vec3 normal = glm::vec3(1, 1, 1);
	
	int numberOfPoints = (int)L / 2;
	for (float i = 0; i <= numberOfPoints; i++) {
		vertices.push_back(VertexFormat(glm::vec3(center.x - numberOfPoints + i, 1, center.y - l/2), normal, color));
		vertices.push_back(VertexFormat(glm::vec3(center.x - numberOfPoints + i, 1, center.y + l/2), normal, color));
	}

	// jumatatea din dreapta
	for (float i = 1; i <= numberOfPoints; i++) {
		vertices.push_back(VertexFormat(glm::vec3(center.x + i, 1, center.y - l / 2), normal, color));
		vertices.push_back(VertexFormat(glm::vec3(center.x + i, 1, center.y + l / 2), normal, color));
	}

	return vertices;
}

std::vector<unsigned short> Object3D::GetRectangleIndices(float L)
{
	std::vector<unsigned short> indices;
	int numberOfPoints = (int)L / 2;
	for (int i = 0; i < numberOfPoints * 2; i += 2) {
		indices.push_back(i);
		indices.push_back(i + 1);
		indices.push_back(i + 3);
	}

	for (int i = 0; i < numberOfPoints * 2; i += 2) {
		indices.push_back(i);
		indices.push_back(i + 3);
		indices.push_back(i + 2);
	}

	// jumatatea din dreapta
	for (int i = 2 * numberOfPoints; i < numberOfPoints * 4; i += 2) {
		indices.push_back(i);
		indices.push_back(i + 1);
		indices.push_back(i + 3);
	}

	for (int i = 2 * numberOfPoints; i < numberOfPoints * 4; i += 2) {
		indices.push_back(i);
		indices.push_back(i + 3);
		indices.push_back(i + 2);
	}

	return indices;
}