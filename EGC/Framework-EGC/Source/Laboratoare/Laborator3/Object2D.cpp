#include "Object2D.h"

#include <Core/Engine.h>

Mesh* Object2D::CreateSquare(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(length, 0, 0), color),
		VertexFormat(corner + glm::vec3(length, length, 0), color),
		VertexFormat(corner + glm::vec3(0, length, 0), color)
	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3 };
	
	if (!fill) {
		square->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		// draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(2);
	}

	square->InitFromData(vertices, indices);
	return square;
}

Mesh* Object2D::CreateRectangle(std::string name, glm::vec3 center, int l, int L, glm::vec3 color)
{
	Mesh* rectangle = new Mesh(name);

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(center.x - L / 2, center.y + l / 2, 0), color),
		VertexFormat(glm::vec3(center.x - L / 2, center.y - l / 2, 0), color),
		VertexFormat(glm::vec3(center.x + L / 2, center.y + l / 2, 0), color),
		VertexFormat(glm::vec3(center.x + L / 2, center.y - l / 2, 0), color)
	};
	std::vector<unsigned short> indices =
	{
		0, 1, 2,
		2, 1, 3
	};

	rectangle->InitFromData(vertices, indices);
	return rectangle;
}