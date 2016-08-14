#include "pch.h"
#include "Game.h"



// initializes and prepares Direct3D
void CGame::Initialize()
{
	// define temp pointer variables to a device and a device context
	ComPtr<ID3D11Device> tempDevice;
	ComPtr<ID3D11DeviceContext> tempDeviceContext;

	// creating the device and the device context objects
	D3D11CreateDevice(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION,
		&tempDevice, nullptr, &tempDeviceContext);

	// convert the pointers from the DX 11 version to the DX 11.2 version
	tempDevice.As(&device);
	tempDeviceContext.As(&deviceContext);
	
}


// performs updates to the game state
void CGame::Update()
{

}


// renders a single frame of 3D graphics
void CGame::Render()
{

}