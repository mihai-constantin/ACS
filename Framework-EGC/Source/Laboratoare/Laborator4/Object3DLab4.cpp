#include "Object3DLab4.h"
#include "Laborator4.h"

#include <Core/Engine.h>
#include <Component/SimpleScene.h>

#include <iostream>

std::vector<VertexFormat> Object3DLab4::GetSeaVertices(glm::vec3 center, float radius, glm::vec3 color)
{
	int number_of_points = 20;
	glm::vec3 normal = glm::vec3(1, 1, 1);

	std::vector<VertexFormat> vertices;

	// add origin
	vertices.push_back(VertexFormat(center, color));

	float step = 2 * glm::pi<float>() / number_of_points;
	for (int i = 0; i < number_of_points; i++) {
		// add new point
		VertexFormat newVertex = VertexFormat(glm::vec3(radius * cos(step * i) + center.x, 
							radius * sin(step * i) + center.y, 0), normal, color);
		vertices.push_back(newVertex);
	}

	return vertices;
}

std::vector<unsigned short> Object3DLab4::GetSeaIndices()
{
	std::vector<unsigned short> indices;

	int number_of_points = 20;

	for (int i = 0; i < number_of_points - 1; i++) {
		indices.push_back(0);
		indices.push_back(i + 1);
		indices.push_back(i + 2);
	}

	// last triangle
	indices.push_back(0);
	indices.push_back(number_of_points);
	indices.push_back(1);

	return indices;
}