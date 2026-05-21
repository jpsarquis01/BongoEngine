#pragma once


#include "MeshTypes.h"

namespace BongoEngine::Graphics
{
	class MeshBuilder
	{
	public:
		// Cube
		static MeshPC CreateVertexCubePC(float size, const Color& color);
		static MeshPC CreateCubePC(float size);

		// rectangle
		static MeshPC CreateBoxPC(float width, float height, float depth);

		// piramid
		static MeshPC CreatePyramidPC(float size);

		// plane
		static MeshPC CreatePlanePC(int numRows, int numColumns, float spacing, bool horizontal = true);

		// cylinder
		static MeshPC CreateCylinderPC(int slices, int rings);

		//sphere
		static MeshPC CreateSpherePC(int slices, int rings, float radius);
	};
}