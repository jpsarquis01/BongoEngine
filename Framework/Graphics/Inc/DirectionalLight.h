#pragma once

#include "Color.h"

namespace BongoEngine::Graphics
{
	struct DirectionalLight
	{
		Color ambient = Colors::White;					// When no light is present
		Color diffuse = Colors::White;					// main light color
		Color specular = Colors::White;					// when highlights are colored
		Math::Vector3 direction = Math::Vector3::ZAxis; // light direction
		float padding = 0.0f;							// padding to make the struct 16 byte aligned
	};
}