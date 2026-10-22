#pragma once

namespace BongoEngine::Graphics
{
	struct Model;

	namespace ModelIO
	{
		void SaveModel(std::filesystem::path filepath, const Model& model);
		void LoadModel(std::filesystem::path filepath, Model& model);
	}
}