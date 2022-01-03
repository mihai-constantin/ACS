// CONSTANTIN MIHAI - 336CA

#pragma once

#include <string>
#include <include/glm.h>
#include <Core/GPU/Mesh.h>

namespace Object3D
{
	std::vector<VertexFormat> GetRectangleVertices(glm::vec3 center, float l, float L, glm::vec3 color);
	std::vector<unsigned short> GetRectangleIndices(float L);

}