#include "stdafx.h"
#include "utility.h"

glm::vec2 utility::clamp(glm::vec2 vector, float max)
{
	if (glm::dot(vector, vector) > max*max) {
		return abs(max) * glm::normalize(vector);
	}
	else {
		return vector;
	}
}
