#pragma once


namespace BongoEngine
{
	class GraphicsSystem
	{
	public:
		// Singleton setup/manage code
		static void StaticInitialize(HWND window, bool fullScreen);
		static void StaticTerminate();
		static GraphicsSystem* Get();

		// file code 
		GraphicsSystem() = default;
		~GraphicsSystem();

		// remove copu/move constructors/operators
		GraphicsSystem(const GraphicsSystem&) = delete;
		GraphicsSystem(const GraphicsSystem&&) = delete;
		GraphicsSystem& operator=(const GraphicsSystem&) = delete;
		GraphicsSystem& operator=(const GraphicsSystem&&) = delete;

		void Initialize(HWND window, bool fullScreen);
		void Terminate();

		void BegginRender();
		void EndRender();

		void ToggleFullScreen();;
		void Resize(uint32_t width, uint32_t height);

		void ResetRenderTarget();
		void ResetViewpoer();

		// void SetClearColor();
		void SetVSync(bool vsync);

		uint32_t GetBackBufferWidth() const;
		uint32_t GetBackBufferHeight() const;
		float GetBackBufferAspectRatio() const;

		ID3D11Device* GetDevice();
		ID3D11DeviceContext* GetContext();

	private:
		static LRESULT CALLBACK GraphicsSystemMessageHandle(HWND win, UINT msg, WPARAM wParam, LPARAM lParam);

		ID3D11Device* mD3DDevice = nullptr;
		ID3D11DeviceContext* mImmediateContext = nullptr;

		IDXGISwapChain* mSwapChain = nullptr;
		ID3D11RenderTargetView* mRenderTargetView = nullptr;

		ID3D11Texture2D* mDepthStencilBuffer = nullptr;
		ID3D11DepthStencilView* mDepthStencilView = nullptr;

		DXGI_SWAP_CHAIN_DESC mSwapChainDesc {};
		D3D11_VIEWPORT mViewport{};

		// Color mClearColor = Colors::Black;
		UINT mVSync = 1;
	};
}