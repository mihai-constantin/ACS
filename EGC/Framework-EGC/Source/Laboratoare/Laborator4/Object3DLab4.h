// CONSTANTIN MIHAI - 336CA
#pragma once

#include <string>
#include <include/glm.h>
#include <Core/GPU/Mesh.h>

namespace Object3DLab4
{
	// sea - cylinder
	std::vector<VertexFormat> GetSeaVertices(glm::vec3 center, float radius, glm::vec3 color);
	std::vector<unsigned short> GetSeaIndices();

}