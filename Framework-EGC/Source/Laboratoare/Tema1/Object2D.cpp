// CONSTANTIN MIHAI - 336CA

#include "Object2D.h"
#include "Tema1.h"

#include <Core/Engine.h>

#include <iostream>

Mesh* Object2D::CreateSquare(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
{
	//std::cout << "intra si aici tot o data? " << std::endl;
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

Mesh* Object2D::CreateCircle(std::string name, glm::vec3 center, float radius, glm::vec3 color, bool fill)
{
	Mesh* circle = new Mesh(name);

	std::vector<VertexFormat> vertices;
	std::vector<unsigned short> indices;

	int number_of_triangles = 100;

	// add origin
	vertices.push_back(VertexFormat(center, color));

	float step = 2 * glm::pi<float>() / number_of_triangles;
	for (int i = 0; i < number_of_triangles; i++) {
		// add new point
		VertexFormat newVertex = VertexFormat(glm::vec3(radius * cos(step * i) + center.x, radius * sin(step * i) + center.y, 0), color);
		vertices.push_back(newVertex);
	}

	for (int i = 0; i < number_of_triangles - 1; i++) {
		indices.push_back(0);
		indices.push_back(i + 1);
		indices.push_back(i + 2);
	}

	// last triangle
	indices.push_back(0);
	indices.push_back(number_of_triangles);
	indices.push_back(1);

	circle->InitFromData(vertices, indices);
	return circle;
}

Mesh* Object2D::CreateTriangle(std::string name, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 color)
{
	Mesh* triangle = new Mesh(name);

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(p1, color),
		VertexFormat(p2, color),
		VertexFormat(p3, color)
	};
	std::vector<unsigned short> indices = { 0, 1, 2 };

	triangle->InitFromData(vertices, indices);
	return triangle;
}

Mesh* Object2D::CreateBird(std::string name, glm::vec3 birdCenter) {

	Mesh* bird = new Mesh(name);
	std::vector<VertexFormat> vertices;
	std::vector<unsigned short> indices;

	// circle1
	float radius = 40;
	glm::vec3 center = glm::vec3(birdCenter.x - radius, birdCenter.y, 0);
	glm::vec3 color = glm::vec3(0.2f, 0.2f, 1);

	int number_of_triangles = 100;

	// add origin
	vertices.push_back(VertexFormat(center, color));

	float step = 2 * glm::pi<float>() / number_of_triangles;
	for (int i = 0; i < number_of_triangles; i++) {
		// add new point
		VertexFormat newVertex = VertexFormat(glm::vec3(radius * cos(step * i) + center.x, radius * sin(step * i) + center.y, 0), color);
		vertices.push_back(newVertex);
	}

	for (int i = 0; i < number_of_triangles - 1; i++) {
		indices.push_back(0);
		indices.push_back(i + 1);
		indices.push_back(i + 2);
	}

	// last triangle
	indices.push_back(0);
	indices.push_back(number_of_triangles);
	indices.push_back(1);

	// circle 3
	radius = 4;
	center = glm::vec3(birdCenter.x + 31, birdCenter.y + 16, 0);
	color = glm::vec3(0, 0, 0);

	// add origin
	int current_size = vertices.size();
	vertices.push_back(VertexFormat(center, color));

	for (int i = 0; i < number_of_triangles; i++) {
		// add new point
		VertexFormat newVertex = VertexFormat(glm::vec3(radius * cos(step * i) + center.x, radius * sin(step * i) + center.y, 0), color);
		vertices.push_back(newVertex);
	}

	for (int i = 0; i < number_of_triangles - 1; i++) {
		indices.push_back(0 + current_size);
		indices.push_back(i + 1 + current_size);
		indices.push_back(i + 2 + current_size);
	}

	// last triangle
	indices.push_back(current_size);
	indices.push_back(number_of_triangles + current_size);
	indices.push_back(1 + current_size);

	// circle 2
	radius = 25;
	center = glm::vec3(birdCenter.x + 20, birdCenter.y + 5, 0); 
	color = glm::vec3(1, 0.5f, 0);

	// add origin
	current_size = vertices.size();
	vertices.push_back(VertexFormat(center, color));

	for (int i = 0; i < number_of_triangles; i++) {
		// add new point
		VertexFormat newVertex = VertexFormat(glm::vec3(radius * cos(step * i) + center.x, radius * sin(step * i) + center.y, 0), color);
		vertices.push_back(newVertex);
	}

	for (int i = 0; i < number_of_triangles - 1; i++) {
		indices.push_back(0 + current_size);
		indices.push_back(i + 1 + current_size);
		indices.push_back(i + 2 + current_size);
	}

	// last triangle
	indices.push_back(current_size);
	indices.push_back(number_of_triangles + current_size);
	indices.push_back(1 + current_size);

	// triangle1 - cioc
	color = glm::vec3(1, 0, 0);
	glm::vec3 p1 = glm::vec3(birdCenter.x + 40, birdCenter.y + 15, 0);
	glm::vec3 p2 = glm::vec3(birdCenter.x + 40, birdCenter.y - 5, 0);
	glm::vec3 p3 = glm::vec3(birdCenter.x + 70, birdCenter.y + 5, 0);
	
	current_size = vertices.size();

	vertices.push_back(VertexFormat(p1, color));
	vertices.push_back(VertexFormat(p2, color));
	vertices.push_back(VertexFormat(p3, color));

	indices.push_back(current_size);
	indices.push_back(1 + current_size);
	indices.push_back(2 + current_size);

	bird->InitFromData(vertices, indices);
	return bird;	
}

Mesh* Object2D::CreateWings(std::string name, glm::vec3 birdCenter, glm::vec3 color)
{
	Mesh* wings = new Mesh(name);

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(birdCenter.x - 70, birdCenter.y + 50, 0), color), // 0
		VertexFormat(glm::vec3(birdCenter.x - 70, birdCenter.y, 0), color), // 1
		VertexFormat(glm::vec3(birdCenter.x - 35, birdCenter.y + 35, 0), color), // 2

		VertexFormat(glm::vec3(birdCenter.x - 70, birdCenter.y, 0), color), // 3
		VertexFormat(glm::vec3(birdCenter.x - 70, birdCenter.y - 50, 0), color), // 4
		VertexFormat(glm::vec3(birdCenter.x - 35, birdCenter.y - 35, 0), color) // 5

	};

	std::vector<unsigned short> indices = {
		0, 1, 2,
		3, 4, 5
	};

	wings->InitFromData(vertices, indices);
	return wings;
}

Mesh* Object2D::CreateObstacleUp(std::string name, glm::vec3 center, int l, int L, glm::vec3 color)
{
	Mesh* obstacle = new Mesh(name);

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(center.x - L / 2, center.y + l / 2, 0), color), // 0
		VertexFormat(glm::vec3(center.x - L / 2, center.y - l / 2, 0), color), // 1
		VertexFormat(glm::vec3(center.x + L / 2, center.y + l / 2, 0), color), // 2
		VertexFormat(glm::vec3(center.x + L / 2, center.y - l / 2, 0), color), // 3

		VertexFormat(glm::vec3(center.x - L / 2 - 3, center.y + l / 2, 0), glm::vec3(0, 0, 0)), // 4
		VertexFormat(glm::vec3(center.x - L / 2 + 3, center.y + l / 2, 0), glm::vec3(0, 0, 0)), // 5
		VertexFormat(glm::vec3(center.x - L / 2 - 3, center.y - l / 2, 0), glm::vec3(0, 0, 0)), // 6
		VertexFormat(glm::vec3(center.x - L / 2 + 3, center.y - l / 2, 0), glm::vec3(0, 0, 0)), // 7

		VertexFormat(glm::vec3(center.x + L/2 - 3, center.y + l/2, 0), glm::vec3(0, 0, 0)), // 8
		VertexFormat(glm::vec3(center.x + L/2 + 3, center.y + l/2, 0), glm::vec3(0, 0, 0)), // 9
		VertexFormat(glm::vec3(center.x + L/2 - 3, center.y - l/2, 0), glm::vec3(0, 0, 0)), // 10
		VertexFormat(glm::vec3(center.x + L/2 + 3, center.y - l/2, 0), glm::vec3(0, 0, 0)), // 11

		VertexFormat(glm::vec3(center.x - L / 2 - 20, center.y - l / 2, 0), color), // 12
		VertexFormat(glm::vec3(center.x - L / 2 - 20, center.y - l / 2 - 50, 0), color), // 13
		VertexFormat(glm::vec3(center.x + L / 2 + 20, center.y - l / 2, 0), color), // 14
		VertexFormat(glm::vec3(center.x + L / 2 + 20, center.y - l / 2 - 50, 0), color), // 15

		VertexFormat(glm::vec3(center.x - L / 2 - 20, center.y - l / 2 + 1, 0), glm::vec3(0, 0, 0)), // 16
		VertexFormat(glm::vec3(center.x - L / 2 - 20, center.y - l / 2 - 1, 0), glm::vec3(0, 0, 0)), // 17
		VertexFormat(glm::vec3(center.x + L / 2 + 20, center.y - l / 2 + 1, 0), glm::vec3(0, 0, 0)), // 18
		VertexFormat(glm::vec3(center.x + L / 2 + 20, center.y - l / 2 - 1, 0), glm::vec3(0, 0, 0)), // 19

		VertexFormat(glm::vec3(center.x - L / 2 - 20 - 3, center.y - l / 2, 0), glm::vec3(0, 0, 0)), // 20
		VertexFormat(glm::vec3(center.x - L / 2 - 20 - 3, center.y - l / 2 - 50, 0), glm::vec3(0, 0, 0)), // 21
		VertexFormat(glm::vec3(center.x - L / 2 - 20 + 3, center.y - l / 2, 0), glm::vec3(0, 0, 0)), // 22
		VertexFormat(glm::vec3(center.x - L / 2 - 20 + 3, center.y - l / 2 - 50, 0), glm::vec3(0, 0, 0)), // 23

		VertexFormat(glm::vec3(center.x + L / 2 + 20 - 3, center.y - l / 2, 0), glm::vec3(0, 0, 0)), // 24
		VertexFormat(glm::vec3(center.x + L / 2 + 20 - 3, center.y - l / 2 - 50, 0), glm::vec3(0, 0, 0)), // 25
		VertexFormat(glm::vec3(center.x + L / 2 + 20 + 3, center.y - l / 2, 0), glm::vec3(0, 0, 0)), // 26
		VertexFormat(glm::vec3(center.x + L / 2 + 20 + 3, center.y - l / 2 - 50, 0), glm::vec3(0, 0, 0)), // 27

		VertexFormat(glm::vec3(center.x - L / 2 - 20, center.y - l / 2 - 50 + 2, 0), glm::vec3(0, 0, 0)), // 28
		VertexFormat(glm::vec3(center.x - L / 2 - 20, center.y - l / 2 - 50 - 2, 0), glm::vec3(0, 0, 0)), // 29
		VertexFormat(glm::vec3(center.x + L / 2 + 20, center.y - l / 2 - 50 + 2, 0), glm::vec3(0, 0, 0)), // 30
		VertexFormat(glm::vec3(center.x + L / 2 + 20, center.y - l / 2 - 50 - 2, 0), glm::vec3(0, 0, 0)) // 31
	};
	std::vector<unsigned short> indices =
	{
		16, 17, 19,
		16, 19, 18,
		0, 1, 2,
		2, 1, 3,
		4, 6, 7,
		4, 7, 5,
		8, 10, 11,
		8, 11, 9,
		12, 13, 15,
		12, 15, 14,
		20, 21, 23,
		20, 23, 22,
		24, 25, 27,
		24, 27, 26,
		28, 29, 31,
		28, 31, 30
	};

	obstacle->InitFromData(vertices, indices);
	return obstacle;
}

Mesh* Object2D::CreateObstacleDown(std::string name, glm::vec3 center, int l, int L, glm::vec3 color)
{
	Mesh* obstacle = new Mesh(name);

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(center.x - L / 2, center.y + l / 2, 0), color), // 0
		VertexFormat(glm::vec3(center.x - L / 2, center.y - l / 2, 0), color), // 1
		VertexFormat(glm::vec3(center.x + L / 2, center.y + l / 2, 0), color), // 2
		VertexFormat(glm::vec3(center.x + L / 2, center.y - l / 2, 0), color), // 3

		VertexFormat(glm::vec3(center.x - L / 2 - 3, center.y + l / 2, 0), glm::vec3(0, 0, 0)), // 4
		VertexFormat(glm::vec3(center.x - L / 2 + 3, center.y + l / 2, 0), glm::vec3(0, 0, 0)), // 5
		VertexFormat(glm::vec3(center.x - L / 2 - 3, center.y - l / 2, 0), glm::vec3(0, 0, 0)), // 6
		VertexFormat(glm::vec3(center.x - L / 2 + 3, center.y - l / 2, 0), glm::vec3(0, 0, 0)), // 7

		VertexFormat(glm::vec3(center.x + L / 2 - 3, center.y + l / 2, 0), glm::vec3(0, 0, 0)), // 8
		VertexFormat(glm::vec3(center.x + L / 2 + 3, center.y + l / 2, 0), glm::vec3(0, 0, 0)), // 9
		VertexFormat(glm::vec3(center.x + L / 2 - 3, center.y - l / 2, 0), glm::vec3(0, 0, 0)), // 10
		VertexFormat(glm::vec3(center.x + L / 2 + 3, center.y - l / 2, 0), glm::vec3(0, 0, 0)), // 11

		VertexFormat(glm::vec3(center.x - L/2 - 20, center.y + l/2 + 50, 0), color), // 12
		VertexFormat(glm::vec3(center.x - L/2 - 20, center.y + l/2, 0), color), // 13
		VertexFormat(glm::vec3(center.x + L/2 + 20, center.y + l/2 + 50, 0), color), // 14
		VertexFormat(glm::vec3(center.x + L/2 + 20, center.y + l/2, 0), color), // 15

		VertexFormat(glm::vec3(center.x - L / 2 - 20, center.y + l / 2, 0), glm::vec3(0, 0, 0)), // 16
		VertexFormat(glm::vec3(center.x - L / 2 - 20, center.y + l / 2 - 3, 0), glm::vec3(0, 0, 0)), // 17
		VertexFormat(glm::vec3(center.x + L / 2 + 20, center.y + l / 2, 0), glm::vec3(0, 0, 0)), // 18
		VertexFormat(glm::vec3(center.x + L / 2 + 20, center.y + l / 2 - 3, 0), glm::vec3(0, 0, 0)), // 19

		VertexFormat(glm::vec3(center.x - L / 2 - 20 - 3, center.y + l / 2 + 50, 0), glm::vec3(0, 0, 0)), // 20
		VertexFormat(glm::vec3(center.x - L / 2 - 20 - 3, center.y + l / 2, 0), glm::vec3(0, 0, 0)), // 21
		VertexFormat(glm::vec3(center.x - L / 2 - 20 + 3, center.y + l / 2 + 50, 0), glm::vec3(0, 0, 0)), // 22
		VertexFormat(glm::vec3(center.x - L / 2 - 20 + 3, center.y + l / 2, 0), glm::vec3(0, 0, 0)), // 23

		VertexFormat(glm::vec3(center.x + L / 2 + 20 - 3, center.y + l / 2 + 50, 0), glm::vec3(0, 0, 0)), // 24
		VertexFormat(glm::vec3(center.x + L / 2 + 20 - 3, center.y + l / 2, 0), glm::vec3(0, 0, 0)), // 25
		VertexFormat(glm::vec3(center.x + L / 2 + 20 + 3, center.y + l / 2 + 50, 0), glm::vec3(0, 0, 0)), // 26
		VertexFormat(glm::vec3(center.x + L / 2 + 20 + 3, center.y + l / 2, 0), glm::vec3(0, 0, 0)), // 27

		VertexFormat(glm::vec3(center.x - L / 2 - 20, center.y + l / 2 + 50 + 3, 0), glm::vec3(0, 0, 0)), // 28
		VertexFormat(glm::vec3(center.x - L / 2 - 20, center.y + l / 2 + 50 - 3, 0), glm::vec3(0, 0, 0)), // 29
		VertexFormat(glm::vec3(center.x + L / 2 + 20, center.y + l / 2 + 50 + 3, 0), glm::vec3(0, 0, 0)), // 30
		VertexFormat(glm::vec3(center.x + L / 2 + 20, center.y + l / 2 + 50 - 3, 0), glm::vec3(0, 0, 0)) // 31
	};

	std::vector<unsigned short> indices =
	{
		16, 17, 19,
		16, 19, 18,
		0, 1, 2,
		2, 1, 3,
		4, 6, 7,
		4, 7, 5,
		8, 10, 11,
		8, 11, 9,
		12, 13, 15,
		12, 15, 14,
		20, 21, 23,
		20, 23, 22,
		24, 25, 27,
		24, 27, 26,
		28, 29, 31,
		28, 31, 30
	};

	obstacle->InitFromData(vertices, indices);
	return obstacle;
}

Mesh* Object2D::CreateCloud(std::string name, glm::vec3 center, float radius, glm::vec3 color)
{
	float initialRadius = radius;
	glm::vec3 initialCenter = center;

	Mesh* circle = new Mesh(name);

	std::vector<VertexFormat> vertices;
	std::vector<unsigned short> indices;

	int number_of_triangles = 100;

	//circle1

	// add origin
	vertices.push_back(VertexFormat(center, color));

	float step = 2 * glm::pi<float>() / number_of_triangles;
	for (int i = 0; i < number_of_triangles; i++) {
		// add new point
		VertexFormat newVertex = VertexFormat(glm::vec3(radius * cos(step * i) + center.x, radius * sin(step * i) + center.y, 0), color);
		vertices.push_back(newVertex);
	}

	for (int i = 0; i < number_of_triangles - 1; i++) {
		indices.push_back(0);
		indices.push_back(i + 1);
		indices.push_back(i + 2);
	}

	// last triangle
	indices.push_back(0);
	indices.push_back(number_of_triangles);
	indices.push_back(1);

	// circle2
	center = glm::vec3(center.x + 1.2 * radius, center.y - 0.6 * radius, 0);
	radius = radius * 0.8;
	// add origin
	int current_size = vertices.size();
	vertices.push_back(VertexFormat(center, color));

	for (int i = 0; i < number_of_triangles; i++) {
		// add new point
		VertexFormat newVertex = VertexFormat(glm::vec3(radius * cos(step * i) + center.x, radius * sin(step * i) + center.y, 0), color);
		vertices.push_back(newVertex);
	}

	for (int i = 0; i < number_of_triangles - 1; i++) {
		indices.push_back(0 + current_size);
		indices.push_back(i + 1 + current_size);
		indices.push_back(i + 2 + current_size);
	}

	// last triangle
	indices.push_back(current_size);
	indices.push_back(number_of_triangles + current_size);
	indices.push_back(1 + current_size);

	//circle3
	center = glm::vec3(initialCenter.x + initialRadius / 4, initialCenter.y - (initialRadius * 0.7), 0);
	radius = initialRadius * 1.2;
	// add origin
	current_size = vertices.size();
	vertices.push_back(VertexFormat(center, color));

	for (int i = 0; i < number_of_triangles; i++) {
		// add new point
		VertexFormat newVertex = VertexFormat(glm::vec3(radius * cos(step * i) + center.x, radius * sin(step * i) + center.y, 0), color);
		vertices.push_back(newVertex);
	}

	for (int i = 0; i < number_of_triangles - 1; i++) {
		indices.push_back(0 + current_size);
		indices.push_back(i + 1 + current_size);
		indices.push_back(i + 2 + current_size);
	}

	// last triangle
	indices.push_back(current_size);
	indices.push_back(number_of_triangles + current_size);
	indices.push_back(1 + current_size);

	// circle4
	center = glm::vec3(initialCenter.x - (initialRadius * 1.1), initialCenter.y - (initialRadius * 1.1), 0);
	radius = initialRadius * 0.8;
	// add origin
	current_size = vertices.size();
	vertices.push_back(VertexFormat(center, color));

	for (int i = 0; i < number_of_triangles; i++) {
		// add new point
		VertexFormat newVertex = VertexFormat(glm::vec3(radius * cos(step * i) + center.x, radius * sin(step * i) + center.y, 0), color);
		vertices.push_back(newVertex);
	}

	for (int i = 0; i < number_of_triangles - 1; i++) {
		indices.push_back(0 + current_size);
		indices.push_back(i + 1 + current_size);
		indices.push_back(i + 2 + current_size);
	}

	// last triangle
	indices.push_back(current_size);
	indices.push_back(number_of_triangles + current_size);
	indices.push_back(1 + current_size);

	//circle5
	center = glm::vec3(initialCenter.x + (initialRadius * 1.3), initialCenter.y - (initialRadius * 1.5), 0);
	radius = initialRadius * 0.5;
	// add origin
	current_size = vertices.size();
	vertices.push_back(VertexFormat(center, color));

	for (int i = 0; i < number_of_triangles; i++) {
		// add new point
		VertexFormat newVertex = VertexFormat(glm::vec3(radius * cos(step * i) + center.x, radius * sin(step * i) + center.y, 0), color);
		vertices.push_back(newVertex);
	}

	for (int i = 0; i < number_of_triangles - 1; i++) {
		indices.push_back(0 + current_size);
		indices.push_back(i + 1 + current_size);
		indices.push_back(i + 2 + current_size);
	}

	// last triangle
	indices.push_back(current_size);
	indices.push_back(number_of_triangles + current_size);
	indices.push_back(1 + current_size);

	//circle6
	center = glm::vec3(initialCenter.x + (initialRadius * 2), initialCenter.y - (initialRadius * 1.1), 0);
	radius = initialRadius * 0.65;
	// add origin
	current_size = vertices.size();
	vertices.push_back(VertexFormat(center, color));

	for (int i = 0; i < number_of_triangles; i++) {
		// add new point
		VertexFormat newVertex = VertexFormat(glm::vec3(radius * cos(step * i) + center.x, radius * sin(step * i) + center.y, 0), color);
		vertices.push_back(newVertex);
	}

	for (int i = 0; i < number_of_triangles - 1; i++) {
		indices.push_back(0 + current_size);
		indices.push_back(i + 1 + current_size);
		indices.push_back(i + 2 + current_size);
	}

	// last triangle
	indices.push_back(current_size);
	indices.push_back(number_of_triangles + current_size);
	indices.push_back(1 + current_size);

	circle->InitFromData(vertices, indices);
	return circle;
}

Mesh* Object2D::CreateMessage(std::string name, glm::vec3 color)
{
	Mesh* message = new Mesh(name);

	std::vector<VertexFormat> vertices =
	{
		// P
		
		VertexFormat(glm::vec3(700, 350, 0), color), // 0
		VertexFormat(glm::vec3(710, 350, 0), color), // 1
		VertexFormat(glm::vec3(700, 250, 0), color), // 2
		VertexFormat(glm::vec3(710, 250, 0), color), // 3

		VertexFormat(glm::vec3(700, 350, 0), color), // 4
		VertexFormat(glm::vec3(750, 350, 0), color), // 5
		VertexFormat(glm::vec3(700, 340, 0), color), // 6
		VertexFormat(glm::vec3(750, 340, 0), color), // 7

		VertexFormat(glm::vec3(740, 350, 0), color), // 8
		VertexFormat(glm::vec3(750, 350, 0), color), // 9
		VertexFormat(glm::vec3(740, 300, 0), color), // 10
		VertexFormat(glm::vec3(750, 300, 0), color), // 11

		VertexFormat(glm::vec3(700, 300, 0), color), // 12
		VertexFormat(glm::vec3(700, 290, 0), color), // 13
		VertexFormat(glm::vec3(750, 300, 0), color), // 14
		VertexFormat(glm::vec3(750, 290, 0), color), // 15

		// r
		VertexFormat(glm::vec3(760, 310, 0), color), // 16
		VertexFormat(glm::vec3(760, 250, 0), color), // 17
		VertexFormat(glm::vec3(770, 310, 0), color), // 18
		VertexFormat(glm::vec3(770, 250, 0), color), // 19

		VertexFormat(glm::vec3(760, 310, 0), color), // 20
		VertexFormat(glm::vec3(760, 300, 0), color), // 21
		VertexFormat(glm::vec3(800, 310, 0), color), // 22
		VertexFormat(glm::vec3(800, 300, 0), color), // 23

		// e
		VertexFormat(glm::vec3(810, 310, 0), color), // 24
		VertexFormat(glm::vec3(810, 300, 0), color), // 25
		VertexFormat(glm::vec3(850, 310, 0), color), // 26
		VertexFormat(glm::vec3(850, 300, 0), color), // 27

		VertexFormat(glm::vec3(810, 310, 0), color), // 28
		VertexFormat(glm::vec3(810, 250, 0), color), // 29
		VertexFormat(glm::vec3(820, 310, 0), color), // 30
		VertexFormat(glm::vec3(820, 250, 0), color), // 31

		VertexFormat(glm::vec3(810, 260, 0), color), // 32
		VertexFormat(glm::vec3(810, 250, 0), color), // 33
		VertexFormat(glm::vec3(850, 260, 0), color), // 34
		VertexFormat(glm::vec3(850, 250, 0), color), // 35

		VertexFormat(glm::vec3(810, 280, 0), color), // 36
		VertexFormat(glm::vec3(810, 270, 0), color), // 37
		VertexFormat(glm::vec3(850, 280, 0), color), // 38
		VertexFormat(glm::vec3(850, 270, 0), color), // 39

		VertexFormat(glm::vec3(840, 310, 0), color), // 40
		VertexFormat(glm::vec3(840, 270, 0), color), // 41
		VertexFormat(glm::vec3(850, 310, 0), color), // 42
		VertexFormat(glm::vec3(850, 270, 0), color), // 43

		// s
		VertexFormat(glm::vec3(860, 310, 0), color), // 44
		VertexFormat(glm::vec3(860, 300, 0), color), // 45
		VertexFormat(glm::vec3(900, 310, 0), color), // 46
		VertexFormat(glm::vec3(900, 300, 0), color), // 47

		VertexFormat(glm::vec3(860, 310, 0), color), // 48
		VertexFormat(glm::vec3(860, 275, 0), color), // 49
		VertexFormat(glm::vec3(870, 310, 0), color), // 50
		VertexFormat(glm::vec3(870, 275, 0), color), // 51

		VertexFormat(glm::vec3(860, 285, 0), color), // 52
		VertexFormat(glm::vec3(860, 275, 0), color), // 53
		VertexFormat(glm::vec3(900, 285, 0), color), // 54
		VertexFormat(glm::vec3(900, 275, 0), color), // 55

		VertexFormat(glm::vec3(890, 280, 0), color), // 56
		VertexFormat(glm::vec3(890, 250, 0), color), // 57
		VertexFormat(glm::vec3(900, 280, 0), color), // 58
		VertexFormat(glm::vec3(900, 250, 0), color), // 59

		VertexFormat(glm::vec3(860, 250, 0), color), // 60
		VertexFormat(glm::vec3(860, 260, 0), color), // 61
		VertexFormat(glm::vec3(900, 250, 0), color), // 62
		VertexFormat(glm::vec3(900, 260, 0), color), // 63

		// s
		VertexFormat(glm::vec3(910, 310, 0), color), // 64
		VertexFormat(glm::vec3(910, 300, 0), color), // 65
		VertexFormat(glm::vec3(950, 310, 0), color), // 66
		VertexFormat(glm::vec3(950, 300, 0), color), // 67

		VertexFormat(glm::vec3(910, 310, 0), color), // 68
		VertexFormat(glm::vec3(910, 275, 0), color), // 69
		VertexFormat(glm::vec3(920, 310, 0), color), // 70
		VertexFormat(glm::vec3(920, 275, 0), color), // 71

		VertexFormat(glm::vec3(910, 285, 0), color), // 72
		VertexFormat(glm::vec3(910, 275, 0), color), // 73
		VertexFormat(glm::vec3(950, 285, 0), color), // 74
		VertexFormat(glm::vec3(950, 275, 0), color), // 75

		VertexFormat(glm::vec3(940, 280, 0), color), // 76
		VertexFormat(glm::vec3(940, 250, 0), color), // 77
		VertexFormat(glm::vec3(950, 280, 0), color), // 78
		VertexFormat(glm::vec3(950, 250, 0), color), // 79

		VertexFormat(glm::vec3(910, 250, 0), color), // 80
		VertexFormat(glm::vec3(910, 260, 0), color), // 81
		VertexFormat(glm::vec3(950, 250, 0), color), // 82
		VertexFormat(glm::vec3(950, 260, 0), color), // 83

		// contur SPACE
		VertexFormat(glm::vec3(495, 230, 0), color), // 84
		VertexFormat(glm::vec3(505, 230, 0), color), // 85
		VertexFormat(glm::vec3(495, 100, 0), color), // 86
		VertexFormat(glm::vec3(505, 100, 0), color), // 87

		VertexFormat(glm::vec3(495, 235, 0), color), // 88
		VertexFormat(glm::vec3(1155, 235, 0), color), // 89
		VertexFormat(glm::vec3(495, 230, 0), color), // 90
		VertexFormat(glm::vec3(1155, 230, 0), color), // 91

		VertexFormat(glm::vec3(495, 105, 0), color), // 92
		VertexFormat(glm::vec3(1155, 105, 0), color), // 93
		VertexFormat(glm::vec3(495, 100, 0), color), // 94
		VertexFormat(glm::vec3(1155, 100, 0), color), // 95

		VertexFormat(glm::vec3(1145, 230, 0), color), // 96
		VertexFormat(glm::vec3(1155, 230, 0), color), // 97
		VertexFormat(glm::vec3(1145, 100, 0), color), // 98
		VertexFormat(glm::vec3(1155, 100, 0), color), // 99

		// S
		VertexFormat(glm::vec3(600, 220, 0), color), // 100
		VertexFormat(glm::vec3(682, 220, 0), color), // 101
		VertexFormat(glm::vec3(600, 215, 0), color), // 102
		VertexFormat(glm::vec3(682, 215, 0), color), // 103

		VertexFormat(glm::vec3(600, 167.5, 0), color), // 104
		VertexFormat(glm::vec3(682, 167.5, 0), color), // 105
		VertexFormat(glm::vec3(600, 162.5, 0), color), // 106
		VertexFormat(glm::vec3(682, 162.5, 0), color), // 107

		VertexFormat(glm::vec3(600, 115, 0), color), // 108
		VertexFormat(glm::vec3(682, 115, 0), color), // 109
		VertexFormat(glm::vec3(600, 110, 0), color), // 110
		VertexFormat(glm::vec3(682, 110, 0), color), // 111

		VertexFormat(glm::vec3(600, 220, 0), color), // 112
		VertexFormat(glm::vec3(600, 165, 0), color), // 113
		VertexFormat(glm::vec3(605, 220, 0), color), // 114
		VertexFormat(glm::vec3(605, 165, 0), color), // 115

		VertexFormat(glm::vec3(677, 165, 0), color), // 116
		VertexFormat(glm::vec3(677, 110, 0), color), // 117
		VertexFormat(glm::vec3(682, 165, 0), color), // 118
		VertexFormat(glm::vec3(682, 110, 0), color), // 119

		VertexFormat(glm::vec3(677, 220, 0), color), // 120
		VertexFormat(glm::vec3(677, 192.5f, 0), color), // 121
		VertexFormat(glm::vec3(682, 220, 0), color), // 122
		VertexFormat(glm::vec3(682, 192.5f, 0), color), // 123

		VertexFormat(glm::vec3(600, 137.5f, 0), color), // 124
		VertexFormat(glm::vec3(600, 110, 0), color), // 125
		VertexFormat(glm::vec3(605, 137.5f, 0), color), // 126
		VertexFormat(glm::vec3(605, 110, 0), color), // 127

		// P

		VertexFormat(glm::vec3(692, 220, 0), color), // 128
		VertexFormat(glm::vec3(692, 215, 0), color), // 129
		VertexFormat(glm::vec3(774, 220, 0), color), // 130
		VertexFormat(glm::vec3(774, 215, 0), color), // 131

		VertexFormat(glm::vec3(692, 167.5, 0), color), // 132
		VertexFormat(glm::vec3(692, 162.5, 0), color), // 133
		VertexFormat(glm::vec3(774, 167.5, 0), color), // 134
		VertexFormat(glm::vec3(774, 162.5, 0), color), // 135

		VertexFormat(glm::vec3(692, 220, 0), color), // 136
		VertexFormat(glm::vec3(692, 110, 0), color), // 137
		VertexFormat(glm::vec3(697, 220, 0), color), // 138
		VertexFormat(glm::vec3(697, 110, 0), color), // 139

		VertexFormat(glm::vec3(769, 220, 0), color), // 140
		VertexFormat(glm::vec3(769, 165, 0), color), // 141
		VertexFormat(glm::vec3(774, 220, 0), color), // 142
		VertexFormat(glm::vec3(774, 165, 0), color), // 143


		// A

		VertexFormat(glm::vec3(784, 220, 0), color), // 144
		VertexFormat(glm::vec3(784, 215, 0), color), // 145
		VertexFormat(glm::vec3(866, 220, 0), color), // 146
		VertexFormat(glm::vec3(866, 215, 0), color), // 147

		VertexFormat(glm::vec3(784, 167.5, 0), color), // 148
		VertexFormat(glm::vec3(784, 162.5, 0), color), // 149
		VertexFormat(glm::vec3(866, 167.5, 0), color), // 150
		VertexFormat(glm::vec3(866, 162.5, 0), color), // 151

		VertexFormat(glm::vec3(784, 220, 0), color), // 152
		VertexFormat(glm::vec3(784, 110, 0), color), // 153
		VertexFormat(glm::vec3(789, 220, 0), color), // 154
		VertexFormat(glm::vec3(789, 110, 0), color), // 155

		VertexFormat(glm::vec3(861, 220, 0), color), // 156
		VertexFormat(glm::vec3(861, 110, 0), color), // 157
		VertexFormat(glm::vec3(866, 220, 0), color), // 158
		VertexFormat(glm::vec3(866, 110, 0), color), // 159

		// C

		VertexFormat(glm::vec3(876, 220, 0), color), // 160
		VertexFormat(glm::vec3(876, 215, 0), color), // 161
		VertexFormat(glm::vec3(958, 220, 0), color), // 162
		VertexFormat(glm::vec3(958, 215, 0), color), // 163

		VertexFormat(glm::vec3(876, 115, 0), color), // 164
		VertexFormat(glm::vec3(876, 110, 0), color), // 165
		VertexFormat(glm::vec3(958, 115, 0), color), // 166
		VertexFormat(glm::vec3(958, 110, 0), color), // 167

		VertexFormat(glm::vec3(876, 220, 0), color), // 168
		VertexFormat(glm::vec3(876, 110, 0), color), // 169
		VertexFormat(glm::vec3(881, 220, 0), color), // 170
		VertexFormat(glm::vec3(881, 110, 0), color), // 171

		VertexFormat(glm::vec3(953, 220, 0), color), // 172
		VertexFormat(glm::vec3(953, 192.5f, 0), color), // 173
		VertexFormat(glm::vec3(958, 220, 0), color), // 174
		VertexFormat(glm::vec3(958, 192.5f, 0), color), // 175

		VertexFormat(glm::vec3(953, 137.5f, 0), color), // 176
		VertexFormat(glm::vec3(953, 110, 0), color), // 177
		VertexFormat(glm::vec3(958, 137.5f, 0), color), // 178
		VertexFormat(glm::vec3(958, 110, 0), color), // 179

		// E

		VertexFormat(glm::vec3(968, 220, 0), color), // 180
		VertexFormat(glm::vec3(968, 215, 0), color), // 181
		VertexFormat(glm::vec3(1050, 220, 0), color), // 182
		VertexFormat(glm::vec3(1050, 215, 0), color), // 183

		VertexFormat(glm::vec3(968, 167.5, 0), color), // 184
		VertexFormat(glm::vec3(968, 162.5, 0), color), // 185
		VertexFormat(glm::vec3(1050, 167.5, 0), color), // 186
		VertexFormat(glm::vec3(1050, 162.5, 0), color), // 187

		VertexFormat(glm::vec3(968, 115, 0), color), // 188
		VertexFormat(glm::vec3(968, 110, 0), color), // 189
		VertexFormat(glm::vec3(1050, 115, 0), color), // 190
		VertexFormat(glm::vec3(1050, 110, 0), color), // 191

		VertexFormat(glm::vec3(968, 220, 0), color), // 192
		VertexFormat(glm::vec3(973, 220, 0), color), // 193
		VertexFormat(glm::vec3(968, 110, 0), color), // 194
		VertexFormat(glm::vec3(973, 110, 0), color), // 195
	};

	std::vector<unsigned short> indices =
	{
		0, 2, 3,
		0, 3, 1,
		4, 6, 7,
		4, 7, 5,
		8, 10, 11,
		8, 11, 9,
		12, 13, 15,
		12, 15, 14,
		16, 17, 19,
		16, 19, 18,
		20, 21, 23,
		20, 23, 22,
		24, 25, 27,
		24, 27, 26,
		28, 29, 31,
		28, 31, 30,
		32, 33, 35,
		32, 35, 34,
		36, 37, 39,
		36, 39, 38,
		40, 41, 43,
		40, 43, 42,
		44, 45, 47,
		44, 47, 46,
		48, 49, 51,
		48, 51, 50,
		52, 53, 55,
		52, 55, 54,
		56, 57, 59,
		56, 59, 58,
		60, 61, 63,
		60, 63, 62,
		64, 65, 67,
		64, 67, 66,
		68, 69, 71,
		68, 71, 70,
		72, 73, 75,
		72, 75, 74,
		76, 77, 79,
		76, 79, 78,
		80, 81, 83,
		80, 83, 82,
		84, 86, 87,
		84, 87, 85,
		96, 98, 99,
		96, 99, 97,
		88, 90, 91,
		88, 91, 89,
		92, 94, 95,
		92, 95, 93,
		100, 102, 103,
		100, 103, 101,
		104, 106, 107,
		104, 107, 105,
		108, 110, 111,
		108, 111, 109,
		112, 113, 115,
		112, 115, 114,
		116, 117, 119,
		116, 119, 118,
		120, 121, 123,
		120, 123, 122,
		124, 125, 127,
		124, 127, 126,
		128, 129, 131,
		128, 131, 130,
		132, 133, 135,
		132, 135, 134,
		136, 137, 139,
		136, 139, 138,
		140, 141, 143,
		140, 143, 142,
		144, 145, 147,
		144, 147, 146,
		148, 149, 151,
		148, 151, 150,
		152, 153, 155,
		152, 155, 154,
		156, 157, 159,
		156, 159, 158,
		160, 161, 163,
		160, 163, 162,
		164, 165, 167,
		164, 167, 166,
		168, 169, 171,
		168, 171, 170,
		172, 173, 175,
		172, 175, 174,
		176, 177, 179,
		176, 179, 178,

		180, 181, 183,
		180, 183, 182,
		184, 185, 187,
		184, 187, 186,
		188, 189, 191,
		188, 191, 190,
		192, 194, 195,
		192, 195, 193
	};

	message->InitFromData(vertices, indices);
	return message;
}

Mesh* Object2D::CreateRectangle(std::string name, glm::vec3 center, int l, int L, glm::vec3 color)
{
	Mesh* rectangle = new Mesh(name);

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(center.x - L/2, center.y + l/2, 0), color),
		VertexFormat(glm::vec3(center.x - L/2, center.y - l/2, 0), color),
		VertexFormat(glm::vec3(center.x + L/2, center.y + l/2, 0), color),
		VertexFormat(glm::vec3(center.x + L/2, center.y - l/2, 0), color)
	};
	std::vector<unsigned short> indices = 
	{ 
		0, 1, 2, 
		2, 1, 3
	};

	rectangle->InitFromData(vertices, indices);
	return rectangle;
}

Mesh* Object2D::CreateParalelogram(std::string name, glm::vec3 center, int l, int L, glm::vec3 color)
{
	Mesh* rectangle = new Mesh(name);

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(center.x - L / 2 + 10, center.y + l / 2, 0), color),
		VertexFormat(glm::vec3(center.x - L / 2, center.y - l / 2, 0), color),
		VertexFormat(glm::vec3(center.x + L / 2 + 10, center.y + l / 2, 0), color),
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

// Resurse: https://learnopengl.com/In-Practice/2D-Game/Collisions/Collision-detection
bool Object2D::CheckCollision(glm::vec3 circleCenter, float radius, glm::vec3 rectangleCenter, float l, float L) // AABB - Circle collision
{
	// Get center point circle first 
	glm::vec2 center = glm::vec2(circleCenter.x, circleCenter.y);
	// Calculate AABB info (center, half-extents)
	glm::vec2 aabb_half_extents(L / 2, l / 2);
	glm::vec2 aabb_center = glm::vec2(rectangleCenter.x, rectangleCenter.y);
	// Get difference vector between both centers
	glm::vec2 difference = center - aabb_center;
	glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
	// Add clamped value to AABB_center and we get the value of box closest to circle
	glm::vec2 closest = aabb_center + clamped;
	// Retrieve vector between center circle and closest point AABB and check if length <= radius
	difference = closest - center;
	return glm::length(difference) < radius;
}