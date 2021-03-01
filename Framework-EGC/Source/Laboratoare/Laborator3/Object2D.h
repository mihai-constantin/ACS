#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

namespace Object2D
{

	// Create square with given bottom left corner, length and color
	Mesh* CreateSquare(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
	
	// Create rectangle
	Mesh* CreateRectangle(std::string name, glm::vec3 center, int l, int L, glm::vec3 color);
}

