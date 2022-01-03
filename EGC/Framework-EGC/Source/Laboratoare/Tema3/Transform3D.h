// CONSTANTIN MIHAI - 336CA

#pragma once

#include <include/glm.h>

namespace Transform3D
{
	// Translate matrix
	inline glm::mat4 Translate(float translateX, float translateY, float translateZ)
	{
		return glm::transpose(glm::mat4(1, 0, 0, translateX,
			0, 1, 0, translateY,
			0, 0, 1, translateZ,
			0, 0, 0, 1));
	}

	// Scale matrix
	inline glm::mat4 Scale(float scaleX, float scaleY, float scaleZ)
	{
		return glm::mat4(scaleX, 0, 0, 0,
			0, scaleY, 0, 0,
			0, 0, scaleZ, 0,
			0, 0, 0, 1);
	}

	// Rotate matrix relative to the OZ axis
	inline glm::mat4 RotateOZ(float radians)
	{
		float c = cos(radians);
		float s = sin(radians);

		return glm::transpose(glm::mat4(c, -s, 0, 0,
			s, c, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1));
	}

	// Rotate matrix relative to the OY axis
	inline glm::mat4 RotateOY(float radians)
	{
		float c = cos(radians);
		float s = sin(radians);

		return glm::transpose(glm::mat4(c, 0, s, 0,
			0, 1, 0, 0,
			-s, 0, c, 0,
			0, 0, 0, 1));
	}

	// Rotate matrix relative to the OX axis
	inline glm::mat4 RotateOX(float radians)
	{
		float c = cos(radians);
		float s = sin(radians);

		return glm::transpose(glm::mat4(1, 0, 0, 0,
			0, c, -s, 0,
			0, s, c, 0,
			0, 0, 0, 1));

	}
}
