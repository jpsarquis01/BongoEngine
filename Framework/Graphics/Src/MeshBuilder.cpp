#include "Precompiled.h"
#include "MeshBuilder.h"

using namespace BongoEngine;
using namespace BongoEngine::Graphics;

namespace
{
	Color GetNextColor(int& index)
	{
		constexpr Color colorTable[] = {
			Colors::Red,
			Colors::Green,
			Colors::Blue,
			Colors::Yellow,
			Colors::Cyan,
			Colors::Magenta,
			Colors::White,
			Colors::Black,
			Colors::Peru,
			Colors::Pink,
			Colors::Purple,
			Colors::Orange,
			Colors::CornflowerBlue,
			Colors::Lavender
		};

		index = (index + 1) % std::size(colorTable);
		return colorTable[index];
	}

	void CreateCubeIndices(std::vector<uint32_t>& indices)
	{
		indices = {
			// front
			0, 1, 2,
			0, 2, 3,
			// back
			7, 5, 4,
			7, 6, 5,
			// right
			3, 2, 6,
			3, 6, 7,
			// left
			4, 5, 1,
			4, 1, 0,
			// top
			1, 5, 6,
			1, 6, 2,
			// bottom
			0, 3, 7,
			0, 7, 4
		};
	}

	void CreatePlaneIndecies(std::vector<uint32_t>& indices, int numRows, int numColums)
	{
		for (int r = 0; r < numRows; ++r)
		{
			for (int c = 0; c < numColums; ++c)
			{
				int i = (r * (numColums + 1)) + c;
				
				// triangle 0
				indices.push_back(i);
				indices.push_back(i + numColums + 1);
				indices.push_back(i + numColums + 2);

				// triangle 1
				indices.push_back(i);
				indices.push_back(i + numColums + 2);
				indices.push_back(i + 1);
			}
		}
	}
}

MeshPC MeshBuilder::CreateVertexCubePC(float size, const Color& color)
{
	MeshPC mesh;
	const float hs = size * 0.5f;

	// front
	mesh.vertices.push_back({ {-hs, -hs, -hs }, {color } });
	mesh.vertices.push_back({ { hs,  hs, -hs }, {color } });
	mesh.vertices.push_back({ { hs, -hs, -hs }, {color } });
							
	mesh.vertices.push_back({ {-hs, -hs, -hs }, {color } });
	mesh.vertices.push_back({ {-hs,  hs, -hs }, {color } });
	mesh.vertices.push_back({ { hs,  hs, -hs }, {color } });
								
	// back						
	mesh.vertices.push_back({ { hs, -hs,  hs }, {color } });
	mesh.vertices.push_back({ { hs,  hs,  hs }, {color } });
	mesh.vertices.push_back({ {-hs, -hs,  hs }, {color } });
								
	mesh.vertices.push_back({ {-hs, -hs,  hs }, {color } });
	mesh.vertices.push_back({ { hs,  hs,  hs }, {color } });
	mesh.vertices.push_back({ {-hs,  hs,  hs }, {color } });

	return mesh;
}

MeshPC MeshBuilder::CreateCubePC(float size)
{
	MeshPC mesh;
	const float hs = size * 0.5f;
	int index = rand() % 100;

	// front								
	mesh.vertices.push_back({ {-hs, -hs, -hs }, GetNextColor(index) });
	mesh.vertices.push_back({ {-hs,  hs, -hs }, GetNextColor(index) });
	mesh.vertices.push_back({ { hs,  hs, -hs }, GetNextColor(index) });
	mesh.vertices.push_back({ { hs, -hs, -hs }, GetNextColor(index) });
												
	// back										
	mesh.vertices.push_back({ {-hs, -hs,  hs }, GetNextColor(index) });
	mesh.vertices.push_back({ {-hs,  hs,  hs }, GetNextColor(index) });
	mesh.vertices.push_back({ { hs,  hs,  hs }, GetNextColor(index) });
	mesh.vertices.push_back({ { hs, -hs,  hs }, GetNextColor(index) });

	// add indices
	CreateCubeIndices(mesh.indices);
	
	return mesh;
}

MeshPC MeshBuilder::CreateBoxPC(float width, float height, float depth)
{
	MeshPC mesh;
	const float hw = width * 0.5f;
	const float hh = height * 0.5f;
	const float hd = depth * 0.5f;
	int index = rand() % 100;

	// front
	mesh.vertices.push_back({ {-hw, -hh, -hd}, GetNextColor(index) });
	mesh.vertices.push_back({ {-hw,  hh, -hd}, GetNextColor(index) });
	mesh.vertices.push_back({ { hw,  hh, -hd}, GetNextColor(index) });
	mesh.vertices.push_back({ { hw, -hh, -hd}, GetNextColor(index) });

	// back
	mesh.vertices.push_back({ {-hw, -hh,  hd }, GetNextColor(index) });
	mesh.vertices.push_back({ {-hw,  hh,  hd }, GetNextColor(index) });
	mesh.vertices.push_back({ { hw,  hh,  hd }, GetNextColor(index) });
	mesh.vertices.push_back({ { hw, -hh,  hd }, GetNextColor(index) });

	CreateCubeIndices(mesh.indices);

	return mesh;
}

MeshPC MeshBuilder::CreatePyramidPC(float size)
{
	MeshPC mesh;
	const float hs = size * 0.5f;
	int index = rand() % 100;

	// top point
	mesh.vertices.push_back({ { 0.0f,  hs, 0.0f }, GetNextColor(index) });

	//bottom
	mesh.vertices.push_back({ {-hs, -hs, -hs }, GetNextColor(index) });
	mesh.vertices.push_back({ {-hs, -hs,  hs }, GetNextColor(index) });
	mesh.vertices.push_back({ { hs, -hs,  hs }, GetNextColor(index) });
	mesh.vertices.push_back({ { hs, -hs, -hs }, GetNextColor(index) });

	mesh.indices = {

		// top point 
		0, 1, 2,
		0, 2, 3,
		0, 3, 4,
		0, 4, 1,

		// bottom
		1, 3, 2,
		1, 4, 3,
	};

	return mesh;
}

MeshPC MeshBuilder::CreatePlanePC(int numRows, int numColumns, float spacing, bool horizontal)
{
	MeshPC mesh;
	int index = rand() % 100;
	const float hpw = static_cast<float>(numColumns) * spacing * 0.5f;
	const float hph = static_cast<float>(numRows) * spacing * 0.5f;

	float w = -hpw;
	float h = -hph;
	for (int r = 0; r <= numRows; ++r)
	{
		for (int c = 0; c <= numColumns; ++c)
		{
			// horizontal is x/z and not horizontal (vertical) is x/y
			Math::Vector3 pos = (horizontal) ? Math::Vector3(w, 0.0f, h) : Math::Vector3(w, h, 0.0f);
			mesh.vertices.push_back({ pos, GetNextColor(index) });
			w += spacing;
		}
		w = -hpw;
		h += spacing;
	}

	CreatePlaneIndecies(mesh.indices, numRows, numColumns);

	return mesh;
}

MeshPC MeshBuilder::CreateCylinderPC(int slices, int rings)
{
	MeshPC mesh;
	int index = rand() % 100;

	const float hh = static_cast<float>(rings) * 0.5f;
	const float fslices = static_cast<float>(slices);
	for (int r = 0; r <= rings; ++r)
	{
		float rF = static_cast<float>(r);
		for (int s = 0; s <= slices; ++s)
		{
			float sF = static_cast<float>(s);
			float rotation = (sF / fslices) * Math::Constants::TwoPi;

			mesh.vertices.push_back({ { sin(rotation), rF - hh, -cos(rotation) }, GetNextColor(index) });
		}
	}

	CreatePlaneIndecies(mesh.indices, rings, slices);

	return mesh;
}

MeshPC MeshBuilder::CreateSpherePC(int slices, int rings, float radius)
{
	MeshPC mesh;
	int index = rand() % 100;

	float verticalRotation = Math::Constants::Pi / static_cast<float>(rings);
	float horizontalRotation = Math::Constants::TwoPi / static_cast<float>(slices);

	for (int r = 0; r <= rings; ++r)
	{
		float rF = static_cast<float>(r);
		float phi = rF * verticalRotation;

		for (int s = 0; s <= slices; ++s)
		{
			float sF = static_cast<float>(s);
			float rotation= sF * horizontalRotation;
			
			mesh.vertices.push_back({ {radius * sin(rotation) * sin(phi),	// x
				radius* cos(phi),											// y
				radius* cos(rotation)* sin(phi)}, GetNextColor(index) });	// z
		}
	}

	CreatePlaneIndecies(mesh.indices, rings, slices);

	return mesh;
}