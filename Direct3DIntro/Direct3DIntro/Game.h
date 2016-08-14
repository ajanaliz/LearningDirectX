#pragma once
#include <wrl.h>
#include <windows.graphics.directx.h>

using namespace Microsoft::WRL;
using namespace Windows::UI::Core;


class CGame
{
public:
	ComPtr<ID3D11Device1> device; // the device interface(virtual representation of the video adapter)
	ComPtr<ID3D11DeviceContext1> deviceContext; // the control panel for the GPU
	ComPtr<IDXGISwapChain1> swapChain; // the swap chain interface
	ComPtr<ID3D11RenderTargetView> renderTarget;

	void Initialize(); // starting up code
	void Update(); // code that manipulates the game, such as timer and input
	void Render(); // draw graphics.

};

