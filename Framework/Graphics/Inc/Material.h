#pragma once

#include "Color.h"

namespace BongoEngine::Graphics
{
	struct Material
	{
		Color emissive = Colors::Black;	 // When the surface is self illuminated
		Color ambient = Colors::White;		 // When no light is present
		Color diffuse = Colors::White;		 // main light color
		Color specular = Colors::White;		 // when highlights are colored
		float shinines = 10.0f;				 // how shiny the surface is
		float padding[3] = { 0.0f };		 // padding to make the struct 16 byte aligned
	};
}