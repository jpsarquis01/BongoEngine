#include "Precompiled.h"
#include "RenderObject.h"

using namespace BongoEngine;
using namespace BongoEngine::Graphics;

void RenderObject::Terminate()
{
	meshBuffer.Terminate();
	TextureManager* tm = TextureManager::Get();
	tm->ReleaseTexture(diffuseMapId);
	tm->ReleaseTexture(specMapId);
	tm->ReleaseTexture(normMapId);
	tm->ReleaseTexture(bumpMapId);
}

void RenderGroup::Initialize(const::std::filesystem::path& modelFilePath)
{
	modelId = ModelManager::Get()->LoadModel(modelFilePath);
	const Model* model = ModelManager::Get()->GetModel(modelId);
	ASSERT(model != nullptr, "RenderGroup: model was not found for s%", modelFilePath.u8string().c_str());
	Initialize(*model);
}

void RenderGroup::Initialize(const Model& model)
{
	for (const Model::MeshData& meshData : model.meshData)
	{
		RenderObject& renderObject = renderObjects.emplace_back();
		renderObject.meshBuffer.Initialize(meshData.mesh);
		if (meshData.materialIndex < model.materialData.size())
		{
			// later
		}
	}
}

void RenderGroup::Terminate()
{
	for (RenderObject& renderObject : renderObjects)
	{
		renderObject.Terminate();
	}
	renderObjects.clear();
}