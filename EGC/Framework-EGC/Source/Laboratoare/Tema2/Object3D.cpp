// CONSTANTIN MIHAI - 336CA

#include "Object3D.h"
#include "Tema2.h"

#include <Core/Engine.h>
#include <Component/SimpleScene.h>

#include <iostream>

std::vector<VertexFormat> Object3D::GetPlaneVertices()
{
	glm::vec3 normal = glm::vec3(0, 1, 1);

	glm::vec3 tomato = glm::vec3(1, 0.39f, 0.28f);
	glm::vec3 light_salmon = glm::vec3(1, 0.62f, 0.48f);
	glm::vec3 white = glm::vec3(1, 1, 1);
	glm::vec3 pale_pink = glm::vec3(1, 0.85f, 0.86f);
	glm::vec3 brown = glm::vec3(0.5f, 0, 0);

	std::vector<VertexFormat> vertices =
	{
		// corp rosu avion

		VertexFormat(glm::vec3(-0.5, -0.5,  0.5), glm::vec3(0, 1, 1), tomato), // 0
		VertexFormat(glm::vec3(1, -1,  1), glm::vec3(1, 0, 1), tomato), // 1
		VertexFormat(glm::vec3(-0.5,  0.5,  0.5), glm::vec3(1, 0, 0), tomato), // 2
		VertexFormat(glm::vec3(1,  1,  1), glm::vec3(0, 1, 0), tomato), // 3
		VertexFormat(glm::vec3(-0.5, -0.5, -0.5), glm::vec3(1, 1, 1), tomato), // 4
		VertexFormat(glm::vec3(1, -1, -1), glm::vec3(0, 1, 1), tomato), // 5
		VertexFormat(glm::vec3(-0.5,  0.5, -0.5), glm::vec3(1, 1, 0), tomato), // 6
		VertexFormat(glm::vec3(1,  1, -1), glm::vec3(0, 0, 1), tomato), // 7

		VertexFormat(glm::vec3(-0.5,  0.5,  0.5), glm::vec3(1, 0, 0), light_salmon), // 8
		VertexFormat(glm::vec3(1,  1,  1), glm::vec3(0, 1, 0), light_salmon), // 9
		VertexFormat(glm::vec3(1,  1, -1), glm::vec3(0, 0, 1), light_salmon), // 10
		VertexFormat(glm::vec3(-0.5,  0.5, -0.5), glm::vec3(1, 1, 0), light_salmon), // 11

		VertexFormat(glm::vec3(-0.5, -0.5,  0.5), glm::vec3(0, 1, 1), light_salmon), // 12
		VertexFormat(glm::vec3(-0.5, -0.5, -0.5), glm::vec3(1, 1, 1), light_salmon), // 13
		VertexFormat(glm::vec3(1, -1,  1), glm::vec3(1, 0, 1), light_salmon), // 14
		VertexFormat(glm::vec3(1, -1, -1), glm::vec3(0, 1, 1), light_salmon), // 15

		// corp alb avion

		VertexFormat(glm::vec3(1, -1,  1), normal, white), // 16
		VertexFormat(glm::vec3(1,  1,  1), normal, white), // 17
		VertexFormat(glm::vec3(1,  1, -1), normal, white), // 18
		VertexFormat(glm::vec3(1, -1, -1), normal, white), // 19
		VertexFormat(glm::vec3(1.3, -1,  1), normal, white), // 20
		VertexFormat(glm::vec3(1.3,  1,  1), normal, white), // 21
		VertexFormat(glm::vec3(1.3,  1, -1), normal, white), // 22
		VertexFormat(glm::vec3(1.3, -1, -1), normal, white), // 23

		VertexFormat(glm::vec3(1.3,  1,  1), normal, pale_pink), // 24
		VertexFormat(glm::vec3(1.3, -1,  1), normal, pale_pink), // 25
		VertexFormat(glm::vec3(1.3, -1, -1), normal, pale_pink), // 26
		VertexFormat(glm::vec3(1.3,  1, -1), normal, pale_pink), // 27

		// stabilizator elice
		VertexFormat(glm::vec3(1.3, -0.2,  0.2), glm::vec3(0, 1, 1), brown), // 28
		VertexFormat(glm::vec3(1.3,  0.2,  0.2), glm::vec3(0, 1, 1), brown), // 29
		VertexFormat(glm::vec3(1.3,  0.2, -0.2), glm::vec3(0, 1, 1), brown), // 30
		VertexFormat(glm::vec3(1.3, -0.2, -0.2), glm::vec3(0, 1, 1), brown), // 31
		VertexFormat(glm::vec3(1.4, -0.2, 0.2), glm::vec3(0, 1, 1), brown), // 32
		VertexFormat(glm::vec3(1.4,  0.2,  0.2), glm::vec3(0, 1, 1), brown), // 33
		VertexFormat(glm::vec3(1.4,  0.2, -0.2), glm::vec3(0, 1, 1), brown), // 34
		VertexFormat(glm::vec3(1.4, -0.2, -0.2), glm::vec3(0, 1, 1), brown), // 35

		// aripi
		VertexFormat(glm::vec3(0, -0.1,  2.5), glm::vec3(0, 1, 1), tomato), // 0 - 36
		VertexFormat(glm::vec3(0.8, -0.1,  2.5), glm::vec3(1, 0, 1), tomato), // 1 - 37
		VertexFormat(glm::vec3(0,  0.1,  2.5), glm::vec3(1, 0, 0), tomato), // 2 - 38
		VertexFormat(glm::vec3(0.8,  0.1,  2.5), glm::vec3(0, 1, 0), tomato), // 3 - 39
		VertexFormat(glm::vec3(0, -0.1, -2.5), glm::vec3(1, 1, 1), tomato), // 4 - 40
		VertexFormat(glm::vec3(0.8, -0.1, -2.5), glm::vec3(0, 1, 1), tomato), // 5 - 41
		VertexFormat(glm::vec3(0, 0.1, -2.5), glm::vec3(1, 1, 0), tomato), // 6 - 42
		VertexFormat(glm::vec3(0.8, 0.1, -2.5), glm::vec3(0, 0, 1), tomato), // 7 - 43

		VertexFormat(glm::vec3(0,  0.1,  2.5), glm::vec3(1, 0, 0), light_salmon), // 2 - 44
		VertexFormat(glm::vec3(0.8,  0.1,  2.5), glm::vec3(0, 1, 0), light_salmon), // 3 - 45
		VertexFormat(glm::vec3(0, 0.1, -2.5), glm::vec3(1, 1, 0), light_salmon), // 6 - 46
		VertexFormat(glm::vec3(0.8, 0.1, -2.5), glm::vec3(0, 0, 1), light_salmon), // 7 - 47

		VertexFormat(glm::vec3(0, -0.1,  2.5), glm::vec3(0, 1, 1), light_salmon), // 0 - 48
		VertexFormat(glm::vec3(0, -0.1, -2.5), glm::vec3(1, 1, 1), light_salmon), // 4 - 49
		VertexFormat(glm::vec3(0.8, -0.1,  2.5), glm::vec3(1, 0, 1), light_salmon), // 1 - 50
		VertexFormat(glm::vec3(0.8, -0.1, -2.5), glm::vec3(0, 1, 1), light_salmon), // 5 - 51

		// coada avion
		VertexFormat(glm::vec3(-0.7, 0,  0.1), glm::vec3(0, 1, 1), brown), // 0 - 52
		VertexFormat(glm::vec3(-0.3, 0,  0.1), glm::vec3(1, 0, 1), brown), // 1 - 53
		VertexFormat(glm::vec3(-0.7, 1,  0.1), glm::vec3(1, 0, 0), brown), // 2 - 54
		VertexFormat(glm::vec3(-0.3, 1,  0.1), glm::vec3(0, 1, 0), brown), // 3 - 55
		VertexFormat(glm::vec3(-0.7, 0, -0.1), glm::vec3(1, 1, 1), brown), // 4 - 56
		VertexFormat(glm::vec3(-0.3, 0, -0.1), glm::vec3(0, 1, 1), brown), // 5 - 57
		VertexFormat(glm::vec3(-0.7, 1, -0.1), glm::vec3(1, 1, 0), brown), // 6 - 58
		VertexFormat(glm::vec3(-0.3, 1, -0.1), glm::vec3(0, 0, 1), brown), // 7 - 59

		// partea roz din spate - corp rosu avion
		VertexFormat(glm::vec3(-0.5,  0.5,  0.5), glm::vec3(1, 0, 0), pale_pink), // 2 - 60
		VertexFormat(glm::vec3(-0.5,  0.5, -0.5), glm::vec3(1, 1, 0), pale_pink), // 6 - 61
		VertexFormat(glm::vec3(-0.5, -0.5, -0.5), glm::vec3(1, 1, 1), pale_pink), // 4 - 62
		VertexFormat(glm::vec3(-0.5, -0.5,  0.5), glm::vec3(0, 1, 1), pale_pink), // 0 - 63

		// bara de prindere roata spate - avion
		VertexFormat(glm::vec3(-0.3, -1.05, 0.2), glm::vec3(0, 1, 1), tomato), // 0 - 64
		VertexFormat(glm::vec3(-0.25, -1.05, 0.2), glm::vec3(1, 0, 1), tomato), // 1 - 65
		VertexFormat(glm::vec3(-0.2, -0.2, 0.2), glm::vec3(1, 0, 0), tomato), // 2 - 66
		VertexFormat(glm::vec3(-0.1, -0.2, 0.2), glm::vec3(0, 1, 0), tomato), // 3 - 67
		VertexFormat(glm::vec3(-0.3, -1.05, -0.2), glm::vec3(1, 1, 1), tomato), // 4 - 68
		VertexFormat(glm::vec3(-0.25, -1.05, -0.2), glm::vec3(0, 1, 1), tomato), // 5 - 69
		VertexFormat(glm::vec3(-0.2, -0.2, -0.2), glm::vec3(1, 1, 0), tomato), // 6 - 70
		VertexFormat(glm::vec3(-0.1, -0.2, -0.2), glm::vec3(0, 0, 1), tomato), // 7 - 71

	};
	
	return vertices;
}

std::vector<unsigned short> Object3D::GetPlaneIndices()
{
	std::vector<unsigned short> indices =
	{
		// corp rosu avion
		0, 1, 2,		1, 3, 2,
		8, 9, 10,		8, 11, 10,
		1, 7, 3,		1, 5, 7,
		6, 7, 4,		7, 5, 4,
		12, 13, 14,		14, 13, 15,
		//2, 6, 4,		0, 2, 4,
		60, 61, 62,		63, 60, 62,

		// corp alb avion
		17, 16, 20,		17, 20, 21,
		18, 19, 23,		18, 23, 22,
		24, 25, 26,		24, 26, 27,
		17, 21, 22,		17, 22, 18,
		16, 20, 23,		16, 23, 19,

		// stabilizator elice
		29, 28, 32,		29, 32, 33,
		30, 31, 35,		30, 35, 34,
		33, 32, 35,		33, 35, 34,
		29, 33, 34,		29, 34, 30,
		28, 32, 35,		28, 35, 31,

		// aripi
		36, 37, 38,		37, 39, 38,
		44, 45, 47,		44, 47, 46,
		37, 43, 39,		37, 41, 43,
		42, 43, 40,		43, 41, 40,
		48, 49, 50,		50, 49, 51,
		38, 42, 40,		36, 38, 40,

		// coada avion
		52, 53, 54,		53, 55, 54,
		54, 55, 59,		54, 59, 58,
		53, 59, 55,		53, 57, 59,
		58, 59, 56,		59, 57, 56,
		52, 56, 53,		53, 56, 57,
		54, 58, 56,		52, 54, 56,

		// bara sustinere roata spate avion
		64, 65, 66,		65, 67, 66,
		66, 67, 71,		66, 71, 70,
		65, 71, 67,		65, 69, 71,
		70, 71, 68,		71, 69, 68,
		64, 68, 65,		65, 68, 69,
		66, 70, 68,		64, 66, 68

	};

	return indices;
}

std::vector<VertexFormat> Object3D::GetPropellerVertices()
{
	glm::vec3 normal = glm::vec3(0, 1, 1);
	glm::vec3 black = glm::vec3(0, 0, 0);

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(1.4, -1.2, 0.2), normal, black), // 0
		VertexFormat(glm::vec3(1.4, 1.2, 0.2), normal, black), // 1
		VertexFormat(glm::vec3(1.4, 1.2, -0.2), normal, black), // 2
		VertexFormat(glm::vec3(1.4, -1.2, -0.2), normal, black), // 3

		VertexFormat(glm::vec3(1.45, -1.2, 0.2), normal, black), // 4
		VertexFormat(glm::vec3(1.45, 1.2, 0.2), normal, black), // 5
		VertexFormat(glm::vec3(1.45, 1.2, -0.2), normal, black), // 6
		VertexFormat(glm::vec3(1.45, -1.2, -0.2), normal, black) // 7

	};

	return vertices;
}

std::vector<unsigned short> Object3D::GetPropellerIndices()
{
	std::vector<unsigned short> indices =
	{
		1, 0, 4,		1, 4, 5,
		2, 3, 7,		2, 7, 6,
		5, 4, 7,		5, 7, 6,
		1, 5, 6,		1, 6, 2,
		0, 4, 7,		0, 7, 3,
		1, 0, 3,		1, 3, 2
	};

	return indices;
}

std::vector<VertexFormat> Object3D::GetWheelsVertices()
{
	glm::vec3 normal = glm::vec3(0, 1, 1);
	glm::vec3 brown = glm::vec3(0.5f, 0, 0);
	glm::vec3 black = glm::vec3(0, 0, 0);

	std::vector<VertexFormat> vertices =
	{
		// cub maro
		VertexFormat(glm::vec3(-0.5, -1,  0.1), normal, brown), // 0 
		VertexFormat(glm::vec3(-0.3, -1,  0.1), normal, brown), // 1 
		VertexFormat(glm::vec3(-0.5, -0.75,  0.1), normal, brown), // 2 
		VertexFormat(glm::vec3(-0.3, -0.75,  0.1), normal, brown), // 3 
		VertexFormat(glm::vec3(-0.5, -1, -0.1), normal, brown), // 4 
		VertexFormat(glm::vec3(-0.3, -1, -0.1), normal, brown), // 5 
		VertexFormat(glm::vec3(-0.5, -0.75, -0.1), normal, brown), // 6 
		VertexFormat(glm::vec3(-0.3, -0.75, -0.1), normal, brown), // 7 

		// paralelipiped negru

		// sus
		VertexFormat(glm::vec3(-0.5, -0.75,  0.1), normal, black), // 8
		VertexFormat(glm::vec3(-0.3, -0.75,  0.1), normal, black), // 9 
		VertexFormat(glm::vec3(-0.5, -0.7,  0.1), normal, black), // 10 
		VertexFormat(glm::vec3(-0.3, -0.7,  0.1), normal, black), // 11
		VertexFormat(glm::vec3(-0.5, -0.75, -0.1), normal, black), // 12
		VertexFormat(glm::vec3(-0.3, -0.75, -0.1), normal, black), // 13
		VertexFormat(glm::vec3(-0.5, -0.7, -0.1), normal, black), // 14 
		VertexFormat(glm::vec3(-0.3, -0.7, -0.1), normal, black), // 15
			
		// jos
		VertexFormat(glm::vec3(-0.5, -1.05,  0.1), normal, black), // 16
		VertexFormat(glm::vec3(-0.3, -1.05,  0.1), normal, black), // 17
		VertexFormat(glm::vec3(-0.5, -1,  0.1), normal, black), // 18 
		VertexFormat(glm::vec3(-0.3, -1,  0.1), normal, black), // 19
		VertexFormat(glm::vec3(-0.5, -1.05, -0.1), normal, black), // 20
		VertexFormat(glm::vec3(-0.3, -1.05, -0.1), normal, black), // 21
		VertexFormat(glm::vec3(-0.5, -1, -0.1), normal, black), // 22 
		VertexFormat(glm::vec3(-0.3, -1, -0.1), normal, black), // 23

		// stanga
		VertexFormat(glm::vec3(-0.55, -1.05,  0.1), normal, black), // 0 - 24
		VertexFormat(glm::vec3(-0.5, -1.05,  0.1), normal, black), // 1 - 25
		VertexFormat(glm::vec3(-0.55, -0.7,  0.1), normal, black), // 2 - 26
		VertexFormat(glm::vec3(-0.5, -0.7,  0.1), normal, black), // 3 - 27
		VertexFormat(glm::vec3(-0.55, -1.05, -0.1), normal, black), // 4 - 28
		VertexFormat(glm::vec3(-0.5, -1.05, -0.1), normal, black), // 5 - 29
		VertexFormat(glm::vec3(-0.55, -0.7, -0.1), normal, black), // 6 - 30
		VertexFormat(glm::vec3(-0.5, -0.7, -0.1), normal, black), // 7 - 31

		//// dreapta
		VertexFormat(glm::vec3(-0.3, -1.05,  0.1), normal, black), // 0 - 32
		VertexFormat(glm::vec3(-0.25, -1.05,  0.1), normal, black), // 1 - 33
		VertexFormat(glm::vec3(-0.3, -0.7,  0.1), normal, black), // 2 - 34
		VertexFormat(glm::vec3(-0.25, -0.7,  0.1), normal, black), // 3 - 35
		VertexFormat(glm::vec3(-0.3, -1.05, -0.1), normal, black), // 4 - 36
		VertexFormat(glm::vec3(-0.25, -1.05, -0.1), normal, black), // 5 - 37
		VertexFormat(glm::vec3(-0.3, -0.7, -0.1), normal, black), // 6 - 38
		VertexFormat(glm::vec3(-0.25, -0.7, -0.1), normal, black), // 7 - 39
	};

	return vertices;
}

std::vector<unsigned short> Object3D::GetWheelsIndices()
{
	std::vector<unsigned short> indices =
	{
			0, 1, 2,		1, 3, 2,
			2, 3, 7,		2, 7, 6,
			1, 7, 3,		1, 5, 7,
			6, 7, 4,		7, 5, 4,
			0, 4, 1,		1, 4, 5,
			2, 6, 4,		0, 2, 4,

			8, 9, 10,		9, 11, 10,
			10, 11, 15,		10, 15, 14,
			9, 15, 11,		9, 13, 15,
			14, 15, 12,		15, 13, 12,
			8, 12, 9,		9, 12, 13,
			10, 14, 12,		8, 10, 12,

			16, 17, 18,		17, 19, 18,
			18, 19, 23,		18, 23, 22,
			17, 23, 19,		17, 21, 23,
			22, 23, 20,		23, 21, 20,
			16, 20, 17,		17, 20, 21,
			18, 22, 20,		16, 18, 20,

			24, 25, 26,		25, 27, 26,
			26, 27, 31,		26, 31, 30,
			25, 31, 27,		25, 29, 31,
			30, 31, 28,		31, 29, 28,
			24, 28, 25,		25, 28, 29,
			26, 30, 28,		24, 26, 28,

			32, 33, 34,		33, 35, 34,
			34, 35, 39,		34, 39, 38,
			33, 39, 35,		33, 37, 39,
			38, 39, 36,		39, 37, 36,
			32, 36, 33,		33, 36, 37,
			34, 38, 36,		32, 34, 36

	};

	return indices;
}

std::vector<VertexFormat> Object3D::GetCloudVertices()
{
	glm::vec3 tomato = glm::vec3(1, 0.39f, 0.28f);
	glm::vec3 pale_pink = glm::vec3(1, 0.85f, 0.86f);
	glm::vec3 palevioletred = glm::vec3(0.86f, 0.44f, 0.57f);
	glm::vec3 blue = glm::vec3(0, 0.75f, 1);
	glm::vec3 powderblue = glm::vec3(0.4f, 0.88f, 1);

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(-1, 3,  1), glm::vec3(0, 1, 1), tomato), // 0
		VertexFormat(glm::vec3(1, 3,  1), glm::vec3(1, 0, 1), tomato), // 1
		VertexFormat(glm::vec3(-1,  5,  1), glm::vec3(1, 0, 0), tomato), // 2
		VertexFormat(glm::vec3(1,  5,  1), glm::vec3(0, 1, 0), tomato), // 3
		VertexFormat(glm::vec3(-1, 3, -1), glm::vec3(1, 1, 1), tomato), // 4
		VertexFormat(glm::vec3(1, 3, -1), glm::vec3(0, 1, 1), tomato), // 5
		VertexFormat(glm::vec3(-1,  5, -1), glm::vec3(1, 1, 0), tomato), // 6
		VertexFormat(glm::vec3(1,  5, -1), glm::vec3(0, 0, 1), tomato), // 7

		VertexFormat(glm::vec3(-1, 3,  1), glm::vec3(0, 1, 1), pale_pink), // 8
		VertexFormat(glm::vec3(1, 3,  1), glm::vec3(1, 0, 1), pale_pink), // 9
		VertexFormat(glm::vec3(-1,  5,  1), glm::vec3(1, 0, 0), pale_pink), // 10
		VertexFormat(glm::vec3(1,  5,  1), glm::vec3(0, 1, 0), pale_pink), // 11

		VertexFormat(glm::vec3(-1, 3, -1), glm::vec3(1, 1, 1), pale_pink), // 12 - 4
		VertexFormat(glm::vec3(1, 3, -1), glm::vec3(0, 1, 1), pale_pink), // 13 - 5
		VertexFormat(glm::vec3(-1,  5, -1), glm::vec3(1, 1, 0), pale_pink), // 14 - 6
		VertexFormat(glm::vec3(1,  5, -1), glm::vec3(0, 0, 1), pale_pink), // 15 - 7

		VertexFormat(glm::vec3(-1,  5,  1), glm::vec3(1, 0, 0), palevioletred), // 2 - 16
		VertexFormat(glm::vec3(1,  5,  1), glm::vec3(0, 1, 0), palevioletred), // 3 - 17
		VertexFormat(glm::vec3(-1,  5, -1), glm::vec3(1, 1, 0), palevioletred), // 6 - 18
		VertexFormat(glm::vec3(1,  5, -1), glm::vec3(0, 0, 1), palevioletred), // 7 - 19

		VertexFormat(glm::vec3(-1, 3,  1), glm::vec3(0, 1, 1), palevioletred), // 0 - 20
		VertexFormat(glm::vec3(1, 3,  1), glm::vec3(1, 0, 1), palevioletred), // 1 - 21
		VertexFormat(glm::vec3(-1, 3, -1), glm::vec3(1, 1, 1), palevioletred), // 4 - 22
		VertexFormat(glm::vec3(1, 3, -1), glm::vec3(0, 1, 1), palevioletred), // 5 - 23

		// -------
		VertexFormat(glm::vec3(0.5, 2.1,  -0.6), glm::vec3(0, 1, 1), palevioletred), // 0 - 24
		VertexFormat(glm::vec3(1.5, 2.1,  -0.6), glm::vec3(1, 0, 1), palevioletred), // 1 - 25
		VertexFormat(glm::vec3(0.5,  2.8,  0.1), glm::vec3(1, 0, 0), palevioletred), // 2 - 26
		VertexFormat(glm::vec3(1.5,  2.8,  0.1), glm::vec3(0, 1, 0), palevioletred), // 3 - 27
		VertexFormat(glm::vec3(0.5, 2.8, -1.3), glm::vec3(1, 1, 1), palevioletred), // 4 - 28
		VertexFormat(glm::vec3(1.5, 2.8, -1.3), glm::vec3(0, 1, 1), palevioletred), // 5 - 29
		VertexFormat(glm::vec3(0.5,  3.5, -0.6), glm::vec3(1, 1, 0), palevioletred), // 6 - 30
		VertexFormat(glm::vec3(1.5,  3.5, -0.6), glm::vec3(0, 0, 1), palevioletred), // 7 - 31
	
		// ---------
		VertexFormat(glm::vec3(-0.385, 3,  2.065), glm::vec3(0, 1, 1), powderblue), // 0 - 32
		VertexFormat(glm::vec3(0.315, 3,  1.365), glm::vec3(1, 0, 1), powderblue), // 1 - 33
		VertexFormat(glm::vec3(-0.385,  4,  2.065), glm::vec3(1, 0, 0), powderblue), // 2 - 34
		VertexFormat(glm::vec3(0.315,  4,  1.365), glm::vec3(0, 1, 0), powderblue), // 3 - 35
		VertexFormat(glm::vec3(-1.26, 3, 1.19), glm::vec3(1, 1, 1), powderblue), // 4 - 36
		VertexFormat(glm::vec3(-0.56, 3, 0.49), glm::vec3(0, 1, 1), powderblue), // 5 - 37
		VertexFormat(glm::vec3(-1.26,  4, 1.19), glm::vec3(1, 1, 0), powderblue), // 6 - 38
		VertexFormat(glm::vec3(-0.56,  4, 1.19), glm::vec3(0, 0, 1), powderblue) // 7 - 39
	};

	return vertices;
}

std::vector<unsigned short> Object3D::GetCloudIndices()
{
	std::vector<unsigned short> indices =
	{

		8, 9, 10,		9, 11, 10,
		16, 17, 19,		16, 19, 18,
		1, 7, 3,		1, 5, 7,
		14, 15, 12,		15, 13, 12,
		20, 22, 21,		21, 22, 23,
		2, 6, 4,		0, 2, 4,

		24, 25, 26,		25, 27, 26,
		26, 27, 31,		26, 31, 30,
		25, 31, 27,		25, 29, 31,
		30, 31, 28,		31, 29, 28,
		24, 28, 25,		25, 28, 29,
		26, 30, 28,		24, 26, 28,

		32, 33, 34,		33, 35, 34,
		34, 35, 39,		34, 39, 38,
		33, 39, 35,		33, 37, 39,
		38, 39, 36,		39, 37, 36,
		32, 36, 33,		33, 36, 37,
		34, 38, 36,		32, 34, 36,

	};

	return indices;
}

std::vector<VertexFormat> Object3D::GetCloud2Vertices()
{
	glm::vec3 mediumvioletred = glm::vec3(0.78, 0.08f, 0.52f);

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(-1.75, 4.25, 0.75), glm::vec3(0, 1, 1), mediumvioletred), // 0 - 24
		VertexFormat(glm::vec3(-0.25, 4.25, 0.75), glm::vec3(1, 0, 1), mediumvioletred), // 1 - 25
		VertexFormat(glm::vec3(-1.75, 5.75, 0.75), glm::vec3(1, 0, 0), mediumvioletred), // 2 - 26
		VertexFormat(glm::vec3(-0.25, 5.75, 0.75), glm::vec3(0, 1, 0), mediumvioletred), // 3 - 27
		VertexFormat(glm::vec3(-1.75, 4.25, -0.75), glm::vec3(1, 1, 1), mediumvioletred), // 4 - 28
		VertexFormat(glm::vec3(-0.25, 4.25, -0.75), glm::vec3(0, 1, 1), mediumvioletred), // 5 - 29
		VertexFormat(glm::vec3(-1.75, 5.75, -0.75), glm::vec3(1, 1, 0), mediumvioletred), // 6 - 30
		VertexFormat(glm::vec3(-0.25, 5.75, -0.75), glm::vec3(0, 0, 1), mediumvioletred), // 7 - 31
	};

	return vertices;
}

std::vector<unsigned short> Object3D::GetCloud2Indices()
{
	std::vector<unsigned short> indices =
	{
		0, 1, 2,		1, 3, 2,
		2, 3, 7,		2, 7, 6,
		1, 7, 3,		1, 5, 7,
		6, 7, 4,		7, 5, 4,
		0, 4, 1,		1, 4, 5,
		2, 6, 4,		0, 2, 4,
	};

	return indices;
}

std::vector<VertexFormat> Object3D::GetSeaVertices(glm::vec3 center, float radius, glm::vec3 color)
{
	int number_of_points = 180;
	glm::vec3 normal = glm::vec3(1, 1, 1);

	std::vector<VertexFormat> vertices;

	for (int z = -10; z <= 10; z++) {

		center.z = 0;

		// add origin
		vertices.push_back(VertexFormat(center, color));

		float step = 2 * glm::pi<float>() / number_of_points;
		for (int i = 0; i < number_of_points; i++) {
			// add new point
			VertexFormat newVertex = VertexFormat(glm::vec3(radius * cos(step * i) + center.x, radius * sin(step * i) + center.y, z), normal, color);
			vertices.push_back(newVertex);
		}
	}

	return vertices;
}

std::vector<unsigned short> Object3D::GetSeaIndices()
{
	std::vector<unsigned short> indices;
	int number_of_points = 180;
	int n = 0;

	for (int z = -10; z <= 10; z++) {

		for (int i = 0; i < number_of_points - 1; i++) {
			indices.push_back(0 + n);
			indices.push_back(i + 1 + n);
			indices.push_back(i + 2 + n);
		}

		// last triangle
		indices.push_back(0 + n);
		indices.push_back(number_of_points + n);
		indices.push_back(1 + n);

		n += number_of_points + 1;
	}

	for (int circle = 0; circle < 22; circle++) {

		for (int i = 1; i < number_of_points; i++) {
			indices.push_back(number_of_points * circle + i);
			indices.push_back(number_of_points * circle + number_of_points + i);
			indices.push_back(number_of_points * circle + number_of_points + i + 1);
		}

		for (int i = 1; i < number_of_points; i++) {
			indices.push_back(number_of_points * circle + i);
			indices.push_back(number_of_points * circle + i + 1);
			indices.push_back(number_of_points * circle + number_of_points + i + 1);
		}

		indices.push_back(number_of_points * circle + number_of_points - 1);
		indices.push_back(number_of_points * circle);
		indices.push_back(number_of_points * circle + number_of_points);

		indices.push_back(number_of_points * circle);
		indices.push_back(number_of_points * circle + number_of_points);
		indices.push_back(number_of_points * circle + number_of_points + 1);
	}

	return indices;
}

std::vector<VertexFormat> Object3D::GetCircleVertices(glm::vec3 center, float radius, glm::vec3 color)
{
	int number_of_points = 180;
	glm::vec3 normal = glm::vec3(1, 1, 1);

	std::vector<VertexFormat> vertices;

	// add origin
	vertices.push_back(VertexFormat(center, color));

	float step = 2 * glm::pi<float>() / number_of_points;
	for (int i = 0; i < number_of_points; i++) {
		// add new point
		VertexFormat newVertex = VertexFormat(glm::vec3(radius * cos(step * i) + center.x, radius * sin(step * i) + center.y, 0), normal, color);
		vertices.push_back(newVertex);
	}

	return vertices;
}

std::vector<unsigned short> Object3D::GetCircleIndices()
{
	int number_of_points = 180;
	std::vector<unsigned short> indices;
	
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

std::vector<VertexFormat> Object3D::GetRectangleVertices(glm::vec3 center, float l, float L, glm::vec3 color)
{
	glm::vec3 normal = glm::vec3(1, 1, 1);

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(center.x - L / 2.f, center.y + l / 2.f, 0), normal, color),
		VertexFormat(glm::vec3(center.x - L / 2.f, center.y - l / 2.f, 0), normal, color),
		VertexFormat(glm::vec3(center.x + L / 2.f, center.y + l / 2.f, 0), normal, color),
		VertexFormat(glm::vec3(center.x + L / 2.f, center.y - l / 2.f, 0), normal, color),

	};

	return vertices;
}

std::vector<unsigned short> Object3D::GetRectangleIndices()
{
	std::vector<unsigned short> indices =
	{
		0, 1, 2,
		2, 1, 3
	};

	return indices;
}

// Resurse: https://learnopengl.com/In-Practice/2D-Game/Collisions/Collision-detection
bool Object3D::CheckCollision(glm::vec3 circleCenter, float radius, glm::vec3 rectangleCenter, float l, float L) // AABB - Circle collision
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