#pragma once
#include <wrl.h>
#include <windows.graphics.directx.h>

using namespace Microsoft::WRL;
using namespace Windows::UI::Core;
using namespace Platform;


class CGame
{
public:
	ComPtr<ID3D11Device1> device; // the device interface(virtual representation of the video adapter)
	ComPtr<ID3D11DeviceContext1> deviceContext; // the control panel for the GPU
	ComPtr<IDXGISwapChain1> swapChain; // the swap chain interface
	ComPtr<ID3D11RenderTargetView> renderTarget;
	ComPtr<ID3D11Buffer> vertexBuffer;
	ComPtr<ID3D11VertexShader> vertexShader;
	ComPtr<ID3D11PixelShader> pixelShader;
	ComPtr<ID3D11InputLayout> inputLayout;


	struct VERTEX
	{
		float X, Y, Z;
	};

	void Initialize(); // starting up code
	void InitGraphics();
	void Update(); // code that manipulates the game, such as timer and input
	void Render(); // draw graphics.
	void InitPipeline();
};

