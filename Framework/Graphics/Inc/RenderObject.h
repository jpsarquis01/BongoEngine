#pragma once

#include "MeshBuffer.h"
#include "Transform.h"
#include "Material.h"
#include "TextureManager.h"
#include "ModelManager.h"

namespace BongoEngine::Graphics
{
	class RenderObject
	{
	public:
		void Terminate();

		MeshBuffer meshBuffer;  // shape, verices, indices...
		Transform transform;	// Location/orientation
		Material material;		// Light data
		TextureId diffuseMapId; // Deffuse texture of the object (Lighting color of the object)
		TextureId specMapId;	// Specular texture of the object (Shininess of the object)
		TextureId normMapId;	// Normal texture of the object (extra details added to obj without adding extra geo)
		TextureId bumpMapId;	// Bump texture adds geometry offests to obj
	};

	class RenderGroup
	{
	public:
		void Initialize(const::std::filesystem::path& modelFilePath);
		void Initialize(const Model& model);
		void Terminate();

		ModelId modelId;
		Transform transform;
		std::vector<RenderObject> renderObjects;
	};
}