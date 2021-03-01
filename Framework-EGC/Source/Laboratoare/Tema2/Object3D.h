// CONSTANTIN MIHAI - 336CA

#pragma once

#include <string>
#include <include/glm.h>
#include <Core/GPU/Mesh.h>

namespace Object3D
{
	// Create plane
	std::vector<VertexFormat> GetPlaneVertices();
	std::vector<unsigned short> GetPlaneIndices();

	// elice
	std::vector<VertexFormat> GetPropellerVertices();
	std::vector<unsigned short> GetPropellerIndices();

	// wheels
	std::vector<VertexFormat> GetWheelsVertices();
	std::vector<unsigned short> GetWheelsIndices();

	// cloud
	std::vector<VertexFormat> GetCloudVertices();
	std::vector<unsigned short> GetCloudIndices();

	// cloud2
	std::vector<VertexFormat> GetCloud2Vertices();
	std::vector<unsigned short> GetCloud2Indices();

	// sea - cylinder
	std::vector<VertexFormat> GetSeaVertices(glm::vec3 center, float radius, glm::vec3 color);
	std::vector<unsigned short> GetSeaIndices();

	// circle - score
	std::vector<VertexFormat> GetCircleVertices(glm::vec3 center, float radius, glm::vec3 color);
	std::vector<unsigned short> GetCircleIndices();

	// rectangle - bara combustibil
	std::vector<VertexFormat> GetRectangleVertices(glm::vec3 center, float l, float L, glm::vec3 color);
	std::vector<unsigned short> GetRectangleIndices();

	// CheckCollision
	bool CheckCollision(glm::vec3 circleCenter, float radius, glm::vec3 rectangleCenter, float l, float L); // AABB - Circle collision


}