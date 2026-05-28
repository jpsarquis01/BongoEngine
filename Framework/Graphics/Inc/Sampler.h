#pragma once


namespace BongoEngine::Graphics
{
	class Sampler
	{
	public:
		enum class Filter {Point, Linear, Animsotropic};
		enum class AddressMode { Wrap, Mirror, Clamp, Border };

		Sampler() = default;
		~Sampler();

		Sampler(const Sampler&) = delete;
		Sampler(const Sampler&&) = delete;
		Sampler& operator=(const Sampler&) = delete;
		Sampler& operator=(Sampler&&) = delete;

		void Initialize(Filter filter, AddressMode addressMode);
		void Terminate();

		void BindVS(uint32_t slot) const;
		void BindPS(uint32_t slot) const;

	private:
		ID3D11SamplerState* mSampler = nullptr;
	};
}